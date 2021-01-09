/* Copyright (c) 2007 by Vivox Inc.
 *
 * Permission to use, copy, modify or distribute this software in binary or source form 
 * for any purpose is allowed only under explicit prior consent in writing from Vivox Inc.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND VIVOX DISCLAIMS
 * ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL VIVOX
 * BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 */

#include "StateManager.h"
#include <iomanip>

#include "VxcErrors.h"

using namespace std;

extern std::string toString(vx_buddy_presence_state state);
extern std::string toString(vx_session_media_state value);
extern std::string toString(vx_session_text_state value);

#define GUID_START 1000        //base number for internal test app requestIDs

StateManager::StateManager()
{
	stateUpdate = 0; // GKy 091215

    guid = GUID_START;
    audioBufferGuid = GUID_START;
    isConnectorInitialized = false;
    isAccountLoggedIn = false;
    connectorHandle = "";
    accountHandle = "";

    listenerHeadingDegrees = 0;
    listenerPosition[0] = 0.0;
    listenerPosition[1] = 0.0;
    listenerPosition[2] = 0.0;
    listenerOrientation[0] = 1.0 * sin(2 * PI *(listenerHeadingDegrees/360.0));
    listenerOrientation[1] = 0.0;
    listenerOrientation[2] = -1.0 * cos(2 * PI * (listenerHeadingDegrees/360.0));
    listenerOrientation[3] = 0.0;
    listenerOrientation[4] = 1.0;
    listenerOrientation[5] = 0.0;

    m_sdkHandle = 0;
}

string StateManager::GenerateID()
{
    guid++;
    stringstream ss;
    ss << guid;
    return ss.str();
}

string StateManager::GenerateAudioBufferId()
{
    audioBufferGuid++;
    stringstream ss;
    ss << audioBufferGuid;
    return ss.str();
}

bool StateManager::SetConnectorInitialized(string p_connectorHandle, string p_version)
{
    if (connectorHandle != p_connectorHandle || !isConnectorInitialized)
    {
        isConnectorInitialized = true;
        connectorHandle = p_connectorHandle;
        accountHandle = "";
        isAccountLoggedIn = false;
        sessionGroups.clear();
        version = p_version;
    }
    return true;
}

void StateManager::SetConnectorUninitialized()
{
    isConnectorInitialized = false;
    connectorHandle = "";
    isAccountLoggedIn = false;
    accountHandle = "";
    this->ClearSessionGroups();
    version.clear();
}

bool StateManager::SetStateAccountLoggedIn(string p_accountHandle)
{
    bool ret = false;
    if (isConnectorInitialized)
    {
        if (accountHandle != p_accountHandle || !isAccountLoggedIn)
        {
            isAccountLoggedIn = true;
            accountHandle = p_accountHandle;
            this->ClearSessionGroups();
        }
        ret = true;
    }
    return ret;
}

void StateManager::SetStateAccountLoggedOut()
{
    isAccountLoggedIn = false;
    accountHandle = "";
    this->ClearSessionGroups();

	////////////////////////////////////////////
	// Ensure Logout Transactions END
	////////////////////////////////////////////
	// GKy 091211 Add additional transaction handle.

	this->txLogOutOK();
}

//////////////////////// tx:transaction //////////////////////////////

void StateManager::txErr(int status_code, const char* status_string)
{
	std::ostringstream ossOut;

#if VVX_DEBUG /////////////////////////////////////////////////////////////
	strOut << "  txErr case="<<VivoxClient::GetCaseEnumName()<<",state="<<VivoxClient::GetStateName()<<" status_code="<<status_code<<" status_string=["<<status_string<<"] ";
#endif ////////////////////////////////////////////////////////////////////

	// GKy 100209 try refine +++++++++++++++++++++++++++++++++++++++++
	switch (status_code)
    {
		//// ERROR NEED PASS //////////////////////////////
		case VX_E_NO_EXIST: //1001 : Status String: The target object of this operation does not exist
#if VVX_DEBUG /////////////////////////////////////////////////////////////
			strOut << "  --case ERROR NEED PASS ";
#endif ////////////////////////////////////////////////////////////////////
			break;

		//// ERROR NEED CLOSE //////////////////////////////
		case VX_E_INVALID_ARGUMENT: // Invalid URL
		case 404: // request Service not found on the Server
		case 10006: // Unknown host
		case VX_E_FAILED_TO_CONNECT_TO_SERVER: // 10007: // Can not connect to Server; GKy 100122
		case 20200: // Password Error
#if VVX_DEBUG /////////////////////////////////////////////////////////////
			strOut << "  --case ERROR NEED CLOSE ";
#endif ////////////////////////////////////////////////////////////////////
			VivoxClient::GetInstance()->Close_With_AppendMessage();
			break;

		//// ERROR SP CASE //////////////////////////////
		case VX_E_FAILED: //1004
		{
#if VVX_DEBUG /////////////////////////////////////////////////////////////
			strOut << "  --case 1004 ";
#endif ////////////////////////////////////////////////////////////////////

			// GKy 100209 need distinguish two sub case:
			/*************************************\

					ERROR in response.  Status Code: 1004
					Status String: Invalid State

					ERROR in response.  Status Code: 1004
					Status String: Object already exists.

			\*************************************/

			std::string strT = status_string;
			if (strT == "Invalid State")
            {
				// Pass
#if VVX_DEBUG /////////////////////////////////////////////////////////////
				strOut << "  --case 1004 Err, Invalid State ";
#endif ////////////////////////////////////////////////////////////////////
			}
			else if (strT == "Object already exists.")
            {
				// reJoin handle
				//// >sgaddsession n URI, URI already add
#if VVX_DEBUG /////////////////////////////////////////////////////////////
				strOut << "  --case 1004 Err, reJoin ";
#endif ////////////////////////////////////////////////////////////////////
				txSessionConnectedHandle();
			}
			else
			{
			}
		}	break; //case VX_E_FAILED: //1004

		case 21600: // Account Not Found, Send Create Acc req.
		{

#if VVX_DEBUG /////////////////////////////////////////////////////////////
			strOut << "  --case 21600: Account Not Found ";
#endif ////////////////////////////////////////////////////////////////////

			// GKy 100122 add, for really Error case? but..
			// GKy 100209 hide. OR try Check to VVXcase..
			// GKy 100209 BUT seems still need for NO Server response case?
			//VivoxClient::close(); // move down reLative to reTry counter?

			// GKy 100209 may be no need switch case? ALL treat as need new Acc? but..
			// GKy 100209 try as no VVXcase check: Final still feel need VVXcase check.

			switch (VivoxClient::GetInstance()->GetCaseEnum())
            {
				case VVX_CASE_ACC_CHECK:
				{
#if VVX_DEBUG /////////////////////////////////////////////////////////////
					strOut << "  case VVX_CASE_ACC_CHECK ";
#endif ////////////////////////////////////////////////////////////////////

					///////////////////////////////////////////////
					// By Retry counter, check if need reTry
					int r = VivoxClient::GetInstance()->GetLoginRetry();

		#if VVX_DEBUG ///////////////////////////////////////////////////////
					strOut << " r=" << r;
		#endif //////////////////////////////////////////////////////////////

					if (r >= 1)
                    {

		#if VVX_DEBUG /////////////////////////////////////////////////////////////
						strOut << "+++ Log Evt +++" << VVX_SELF_EVT_ACC_CREATE_RETRY;
		#endif ////////////////////////////////////////////////////////////////////

						VivoxClient::GetInstance()->Close_Without_Message();
						VivoxClient::GetInstance()->AppendMessage(VVX_SELF_EVT_ACC_CREATE_RETRY);
						--r;
						VivoxClient::GetInstance()->SetLoginRetry(r);
					}
                    else
                    {
						VivoxClient::GetInstance()->Close_With_AppendMessage();
					}
				}	break;

				default: 
#if VVX_DEBUG /////////////////////////////////////////////////////////////
					strOut << "  case default ";
#endif ////////////////////////////////////////////////////////////////////
					VivoxClient::GetInstance()->Close_With_AppendMessage();
					break;
			}//switch
		}	break; // case 21600: // Account Not Found, Send Create Acc req.

		default: // Unknown Error 
#if VVX_DEBUG /////////////////////////////////////////////////////////////
			strOut << "  --case default ";
#endif ////////////////////////////////////////////////////////////////////
			break;
	}//switch

#if VVX_DEBUG ///////////////////////////////////////////////////////////
	//VivoxClient::flushLog( strOut.str().c_str() ); // GKy 100126 // GKy 100202 hide
	g_fVVXout(NULL, strOut.str().c_str() );
#endif //////////////////////////////////////////////////////////////////

}

// GKy 091217 integrated habdle place.
//void StateManager::txALL(VVX_STATE state_, const char* ChURI )
void StateManager::txALL(const char* ChURI )
{
#if VVX_DEBUG ////////////////////////////////////////////////////////////////
	//strT.Format("txALL case=%d,state=%d", VivoxClient::CASEget(), g_iVVXstate);
	//strT.Format("txALL case=%s,state=%d", VivoxClient::CASEgetName().c_str(), g_iVVXstate);
	strT.Format("txALL case=%s,state=%s", VivoxClient::GetCaseEnumName().c_str(), VivoxClient::GetStateName().c_str() );
	g_fVVXout(NULL, strT);
#endif ///////////////////////////////////////////////////////////////////////

	// Warp Case //// May be Other Case Warp to here!? +++++++++++++++++++++++++++++++
	// GKy 100118!? indeed seems never happened..may be need hide..=w=;
	// GKy 100118 OTL..ensure happen.
	if (VivoxClient::GetInstance()->IsCaseEnumChanged())
    {
        std::ostringstream oss_msg;

        oss_msg << "?????????????? CASEisChange"
                << " PreCase=" << VivoxClient::GetInstance()->GetCaseEnumName(VivoxClient::GetInstance()->GetCaseEnumPrevious())
                << ",NewCase=" << VivoxClient::GetInstance()->GetCaseEnumName();

		VivoxClient::GetInstance()->VivoxOutputPrint(NULL, oss_msg.str().c_str());

		VVX_CASE case_now = VivoxClient::GetInstance()->GetCaseEnum();

		switch (case_now)
        {
            // Need Reset Transaction
			case VVX_CASE_ACC_CHECK: // GKy 100122 
				VivoxClient::GetInstance()->CheckAccount();
				break;

			case VVX_CASE_DISABLE:
                VivoxClient::GetInstance()->DisableWithInitialCase();
				break;

			case VVX_CASE_CH_JOIN_CREATE:
			case VVX_CASE_CH_JOIN_ADD: // seems impossible? No, need for TestJoin use
				VivoxClient::GetInstance()->JoinChannelWithInitialCase(case_now);
				break;

			case VVX_CASE_CH_EXIT_INIT:
				// GKy 100118 fix some S_MSG ChName display problem.
				// GKy 100118 still feel not good enough.
				//VivoxClient::ChannelNamePreviousSet( VivoxClient::ChannelNameCurrentGet().c_str() );
				VivoxClient::GetInstance()->ExitChannelWithInitialCase();
				break;

			default: 
				VivoxClient::GetInstance()->InitialCaseEnum(VVX_CASE_IDLE);
				break;
		}
		return;
	}

	if (VivoxClient::GetInstance()->GetVivoxState() == VVX_STATE_IDLE)
    {
		return;
	}

	//////////////////////////////////////////////////////////////////

	switch (VivoxClient::GetInstance()->GetCaseEnum())
    {
		//case VVX_CASE_ENABLE:
		//	// do nothing, may be exH.
		//	break;

		case VVX_CASE_DISABLE: //
			// ensure shutdown to server, ALL case besides OnShutDown
			switch (VivoxClient::GetInstance()->GetVivoxState())
            {
				case VVX_STATE_SS_REMOVE_OK: // GKy 091221 just show a message
                    txSessionRemovedHandle();
                    break;

				case VVX_STATE_SHUTDOWN_OK: // END +++++++++++++++++++++++++++++++++
					//VivoxClient::m_iVVXcase = VVX_CASE_IDLE;
					VivoxClient::GetInstance()->InitialCaseEnum(VVX_CASE_IDLE);

					// GKy 100128 try add if need run Enable process(AccCheck)
					if (VivoxClient::GetInstance()->IsEnable())
                    {
						//VivoxClient::AccountCheck();
						VivoxClient::GetInstance()->Enable_And_SkipAllCheck();
					}
					break;

				case VVX_STATE_LOGOUT_OK: // GKy 100208 add for void VVXcase_AccCheck txErr 21600 call to VvxCnt::close()
					// VvxCnt::close() will call to disable. AND 21600 also with resp VVX_STATE_LOGOUT_OK.
					// two event seems have no relations and orders.
					break;


				case VVX_STATE_SM_DISCONNECTED:
					break;

				default:
					VivoxClient::GetInstance()->DisableWithInitialCase();
					break;
			}
            break;

		/*****************************************************************
			GKy 091231 Add Account Check case
			GKy 100104 move >updateaccount part to ChJoin Process.

			GKy 100128 as main VvxCnt::enable transaction

			GKy 100525 try add new exception handle: 
			
				if find Svr settings: VivoxLanguage not set("" == m_sVivoxChannelNamePrefix)
				{
					treat as VvxOff(out of service);
				}

				try done in CNetCli_Login_Child::RM_VivoxAccount
		*****************************************************************/
		case VVX_CASE_ACC_CHECK: //
			switch (VivoxClient::GetInstance()->GetVivoxState())
            {
				case VVX_STATE_SHUTDOWN_OK:
					VivoxClient::GetInstance()->ProcessByUpdateState(VVX_STATE_INIT);
					break;

				case VVX_STATE_LOGOUT_OK: // GKy 091231 have BUG? ???????????
				// So..No Acc seems ALso go this state..check..
				// GKy 100104 skip this state seems better? GKy 100127 ensure skip.
					break;

				case VVX_STATE_INIT_OK:
					VivoxClient::GetInstance()->ProcessByUpdateState(VVX_STATE_LOGIN);
					break;

				case VVX_STATE_LOGIN_OK:
					VivoxClient::GetInstance()->ProcessByUpdateState(VVX_STATE_CH_CREATE_ECHO);
					break;

				////////////////////////////////////////////////////////////////////////////
				// GKy 100120 Add Echo_URI update handle. BTW, AnyLogin mode not have this.
				case VVX_STATE_CH_CREATE_OK: // GKy 100120 // +++++++++++++ // END
					VivoxClient::GetInstance()->SetEchoURI( ChURI ); // ChURI
					VivoxClient::GetInstance()->SetLoginMode( VVX_LOGIN_MODE_NOR );
					VivoxClient::GetInstance()->InitialCaseEnum( VVX_CASE_IDLE );

					// GKy 100128 try add if need run Disaable process
					if (!VivoxClient::GetInstance()->IsEnable())
                    {
						 VivoxClient::GetInstance()->Disable_Without_CheckEnable();
					}
                    else
                    {
						VivoxClient::GetInstance()->AppendMessage(VVX_WORLD_EVT_ENABLE_OK);
					}
					break;

				// Warp Handle?
				default:
					break;
			}
			break;

		/*****************************************************************
			GKy 091228 try move this part done by another instance,
				to improve the speed?. BUT..
			GKy 091228 Final try keep two way at first..
		*****************************************************************/
		case VVX_CASE_CH_JOIN_CREATE:
			switch (VivoxClient::GetInstance()->GetVivoxState())
            {
				case VVX_STATE_SHUTDOWN_OK:
					VivoxClient::GetInstance()->ProcessByUpdateState(VVX_STATE_INIT);
					break;

				case VVX_STATE_INIT_OK:
				case VVX_STATE_LOGOUT_OK:
					VivoxClient::GetInstance()->ProcessByUpdateState(VVX_STATE_LOGIN);
					break;

				case VVX_STATE_LOGIN_OK:
				case VVX_STATE_SS_REMOVE_OK: // GKy 100118 add for LoginModeNor speed up
					VivoxClient::GetInstance()->ProcessByUpdateState(VVX_STATE_CH_CREATE);
					break;

				case VVX_STATE_CH_CREATE_OK: //END
					// GKy 091211 set Ch URI
					// GKy 100120 review +++++++++++++++
					VivoxClient::GetInstance()->ChannelURIString() = ChURI;
					VivoxClient::GetInstance()->InitialCaseEnum(VVX_CASE_CH_JOIN_ADD);

					// GKy 091231 Add LoginMode check
					switch (VivoxClient::GetInstance()->GetLoginMode())
                    {
						case VVX_LOGIN_MODE_NOR:
							// Ensure Acc Existed ,Next, Need Set displayName.
							VivoxClient::GetInstance()->ProcessByUpdateState(VVX_STATE_ACC_UPDATE);
							break;

						default:
							break;
					}
					break;

				case VVX_STATE_SM_DISCONNECTED:
#if VVX_DEBUG
					g_fVVXout(NULL, " VVX_CASE_CH_JOIN_CREATE-VVX_STATE_SM_DISCONNECTED ");
#endif
					break;

				default: // AS init
					break;

			}
			break;

		case VVX_CASE_CH_JOIN_ADD:
		//case VVX_CASE_TEST_INIT:
			switch (VivoxClient::GetInstance()->GetVivoxState())
            {
				case VVX_STATE_SHUTDOWN_OK: //START
					VivoxClient::GetInstance()->ProcessByUpdateState(VVX_STATE_INIT);
					break;

				case VVX_STATE_INIT_OK:
				case VVX_STATE_LOGOUT_OK:
					switch (VivoxClient::GetInstance()->GetLoginMode())
                    {
						case VVX_LOGIN_MODE_NOR:
							VivoxClient::GetInstance()->ProcessByUpdateState(VVX_STATE_LOGIN);
							break;

						default:
							break;
					}
					break;

				//case VVX_STATE_LOGIN_OK: //++++ GKy 100120, move to Acc check parts.
				//	// GKy 100120 need get EchoCh URI..due to domain may changed..well..
				//	// GKy 100120 BUT, seems will effect ANY Login? well..ANY indeed need more fix..
				//	g_iVVXstate = VVX_STATE_CH_CREATE_ECHO;
				//	VivoxClient::process( g_iVVXstate );
				//	break;

				//case VVX_STATE_LOGIN_ANY_OK: 
				case VVX_STATE_LOGIN_OK: //++++ OLD
				//case VVX_STATE_CH_CREATE_OK: // GKy 100120, see up

                    // GKy 100118 
					if (VivoxClient::GetInstance()->IsCreate())
                    {
						VivoxClient::GetInstance()->ProcessByUpdateState(VVX_STATE_SS_ADD);
					}
                    else
                    {
						VivoxClient::GetInstance()->ProcessByUpdateState(VVX_STATE_SG_CREATE);
					}
					break;

				////////////////////////////////////////////////////////

				case VVX_STATE_ACC_UPDATE_OK: 
					if (VivoxClient::GetInstance()->IsCreate())
                    {
						VivoxClient::GetInstance()->ProcessByUpdateState(VVX_STATE_SS_ADD);
					}
                    else
                    {
						VivoxClient::GetInstance()->ProcessByUpdateState(VVX_STATE_SG_CREATE);
					}
					break;

				case VVX_STATE_SG_CREATE_OK:
					VivoxClient::GetInstance()->ProcessByUpdateState(VVX_STATE_SS_ADD);
					break;

				case VVX_STATE_SS_ADD_OK: //END+++
				{
					//VivoxClient::CASEini( VVX_CASE_IDLE );
					// GKy 100121 try package this part as fnc, due to txErr 1004 need share here.
					txSessionConnectedHandle();
				}	break;

				case VVX_STATE_SS_REMOVE_OK:
					break;

				case VVX_STATE_SM_DISCONNECTED: // GKy 100107 BUT afraid of repeat happen..
					VivoxClient::GetInstance()->Disconnected();
					break;

				default:
					break;
			}
			break;

		case VVX_CASE_CH_EXIT_INIT:
		//case VVX_CASE_CH_EXIT_NOR:
		//case VVX_CASE_TEST_END_NOR: // merge to UP
			// besides SS_REMOVE_OK case, other cases all perform SS remove;

			switch (VivoxClient::GetInstance()->GetVivoxState())
            {
				case VVX_STATE_SS_REMOVE_OK:
				{
					txSessionRemovedHandle();

					// +++++++++++++++++++++++++++++ reJoin Handle ++++++++++++++++++++++++++++++++
					if (VivoxClient::GetInstance()->IsInChannel())
                    {
                        // GKy 100113+++ both Team->Test->Team OK
						// GKy 100113 need this overALL check to void effect Normal End Case
						/****************************************************************
						Here Only Handle Team->Test->Team case; Test->Test; Team->Team not handle here.

						Afraid of Team->Team case have some crisis..

						GKy 100113 OTL..Team1->Team2 case real have mirage, need Check....
						*****************************************************************/

						if (VivoxClient::GetInstance()->GetChannelNamePrevious(true) != VVX_CH_NAME_TEST)
                        {
							if (VivoxClient::GetInstance()->IsInTest())
                            {
                                // GKy 100113 still check URI, only worked for reJoin case
								VivoxClient::GetInstance()->JoinChannelWithInitialCase( VVX_CASE_CH_JOIN_ADD ); // Team->Test
							}
                            else
                            {
								VivoxClient::GetInstance()->JoinChannelWithInitialCase( VVX_CASE_CH_JOIN_CREATE ); // Team->Team2
							}
						}
                        else
                        {
							VivoxClient::GetInstance()->JoinChannelWithInitialCase( VVX_CASE_CH_JOIN_CREATE ); // Test->Team
						}
					}
                    else
                    {
    					// Nor End Case.
						VivoxClient::GetInstance()->InitialCaseEnum( VVX_CASE_IDLE );
					}

				}	break;

				case VVX_STATE_SM_DISCONNECTED:
					break;

				case VVX_STATE_SS_ADD_OK: // Join then dd leave.
				default: // !? GKy 091218 now as ShutDown..BUT?..
					VivoxClient::GetInstance()->ExitChannelWithInitialCase();
					break;
			}
			break;

		case VVX_CASE_in_TEAM:
		case VVX_CASE_in_TEST:
			switch (VivoxClient::GetInstance()->GetVivoxState())
            {
				case VVX_STATE_SM_DISCONNECTED:
					VivoxClient::GetInstance()->Disconnected();
					break;

				default:
					break;
			}
			break;

		default:
			break;
	}
}

void StateManager::txConnectorCreateOK()
{
    VivoxClient::GetInstance()->SetVivoxState(VVX_STATE_INIT_OK);
	this->txALL();
}

void StateManager::txShutDownOK()
{
	VivoxClient::GetInstance()->SetVivoxState(VVX_STATE_SHUTDOWN_OK);
	this->txALL();
}

void StateManager::txChannelCreateOK( const char* ChURI )
{
	VivoxClient::GetInstance()->SetVivoxState(VVX_STATE_CH_CREATE_OK);
	//VivoxClient::m_sVivoxChannelURI = ChURI; //
	this->txALL(ChURI);
}

//void StateManager::txListCaptureDevs()
void StateManager::txListDevs()
{
	VivoxClient::GetInstance()->VivoxOutputPrint(NULL, "stMgr StateManager::txListDevs");

	switch (VivoxClient::GetInstance()->GetVivoxCase())
    {
		case VVX_CASE_IN_DEV_GET:
		case VVX_CASE_OUT_DEV_GET:
			VivoxClient::GetInstance()->SetVivoxCase(VVX_CASE_IDLE);
			break;

        case VVX_CASE_IN_DEV_SET:
            VivoxClient::GetInstance()->CheckInputDeviceIndexRange();
            VivoxClient::GetInstance()->CC_SetupInputDevice();
            VivoxClient::GetInstance()->SetVivoxCase(VVX_CASE_IDLE);
            break;

		case VVX_CASE_OUT_DEV_SET:
            VivoxClient::GetInstance()->CheckInputDeviceIndexRange();
            VivoxClient::GetInstance()->CC_SetupOutputDevice();
            VivoxClient::GetInstance()->SetVivoxCase(VVX_CASE_IDLE);
            break;

		default:
			VivoxClient::GetInstance()->SetVivoxCase(VVX_CASE_IDLE);
			break;
	}
}

void StateManager::txLoginOK()
{
    VivoxClient::GetInstance()->SetVivoxState(VVX_STATE_LOGIN_OK);
	this->txALL();
}

//void StateManager::txLoginAnyOK()
//{
//	g_iVVXstate = VVX_STATE_LOGIN_ANY_OK;
//	this->txALL();
//}

void StateManager::txLogOutOK()
{
	VivoxClient::GetInstance()->SetVivoxState(VVX_STATE_LOGOUT_OK);
	this->txALL();
}

void StateManager::txSessionMediaUpdate()
{

}

void StateManager::txSessionRemoveOK()
{
	VivoxClient::GetInstance()->SetVivoxState(VVX_STATE_SS_REMOVE_OK);
	this->txALL();
}

void StateManager::txSessionConnected()
{
	// GKy 091224 do some reset for create a Channel
	//VivoxClient::m_mParts.clear();
	//VivoxClient::m_mDBid2URI.clear(); // GKy 091230 for zS
	VivoxClient::GetInstance()->GetPartiGroupRef().ClearAll(); // GKy 091230 final solution.

	//VivoxClient::m_sPartnerDisplayNameLast = "";
	VivoxClient::GetInstance()->SetPartnerDBidLast(0);

	VivoxClient::GetInstance()->SetAllVolumn(); // GKy 091225 reset Volume

	VivoxClient::GetInstance()->SetVivoxState(VVX_STATE_SS_ADD_OK);
	this->txALL();
}

void StateManager::txSessionRemovedHandle()
{
	std::ostringstream oss;
	oss << VVX_SELF_EVT_CH_EXIT_OK << " "
        << VivoxClient::GetInstance()->GetChannelNamePrevious(true);
	VivoxClient::GetInstance()->AppendMessage(oss.str().c_str());
	VivoxClient::GetInstance()->AppendMessage(VVX_WORLD_EVT_CH_EXIT); //for kS close speaker panel
	// GKy 100416 #deBug: not this
}

void StateManager::txSessionConnectedHandle()
{
	if (!VivoxClient::GetInstance()->IsInTest())
    {
		VivoxClient::GetInstance()->AppendMessage( VVX_WORLD_EVT_CH_JOIN ); // GKy 100112 main for kS

		std::ostringstream oss;
		oss << VVX_SELF_EVT_CH_JOIN_OK << " "
            << VivoxClient::GetInstance()->GetCurrentChannelName();
		VivoxClient::GetInstance()->AppendMessage(oss.str().c_str());
		VivoxClient::GetInstance()->InitialCaseEnum(VVX_CASE_in_TEAM);
		VivoxClient::GetInstance()->SetChannelNamePrevious(VivoxClient::GetInstance()->GetCurrentChannelName().c_str());

#if VVX_DEBUG /////////////////////////////////////////////////////////////
		if (VivoxClient::GetOutputDebugMessage >= 1)
        {
			VivoxClient::AppendMessage("VVX_CASE_in_TEAM");
        }
#endif //////////////////////////////////////////////////////////////////////

	}
    else
    {
		std::ostringstream oss;
		oss << VVX_SELF_EVT_CH_JOIN_OK
            << " " << VVX_CH_NAME_TEST;
		VivoxClient::GetInstance()->AppendMessage(oss.str().c_str());
		VivoxClient::GetInstance()->InitialCaseEnum(VVX_CASE_in_TEST);
		VivoxClient::GetInstance()->SetChannelNamePrevious(VVX_CH_NAME_TEST);

#if VVX_DEBUG /////////////////////////////////////////////////////////////
		if (VivoxClient::GetOutputDebugMessage() >= 1)
        {
			VivoxClient::AppendMessage("VVX_CASE_in_TEST");
        }
#endif /////////////////////////////////////////////////////////////////////

	}
}

void StateManager::txSessionDisconnected()
{
	// Indeed here can also do some Reset..mu..BUT watch out Error case
	VivoxClient::GetInstance()->SetVivoxState(VVX_STATE_SM_DISCONNECTED);
	this->txALL();
}

void StateManager::txSessionGroupAdded()
{
	VivoxClient::GetInstance()->SetVivoxState(VVX_STATE_SG_CREATE_OK);
	this->txALL();
}

bool StateManager::AddSessionGroup(string session_group_handle)
{
    bool ret = false;
    //if (isAccountLoggedIn && isConnectorInitialized)
    //{
        VxSessionGroup* sg = new VxSessionGroup(session_group_handle);
        this->sessionGroups.insert(make_pair(session_group_handle,sg));
        ret = true;
    //}
    return ret;
}

string StateManager::AddAudioBuffer(void *audioBufferPtr)
{
    string audioBufferId = GenerateAudioBufferId();

    this->audioBuffers.insert(make_pair(audioBufferId, audioBufferPtr));

    return audioBufferId;
}

void StateManager::ListAudioBuffers(ostream *dumpfile) const
{
    map<string,void*>::const_iterator itr;

    stringstream ss;

    ss << "Audio Buffer List: " << endl;

    for (itr = audioBuffers.begin(); itr != audioBuffers.end(); ++itr)
    {
        ss << "audioBufferId = " << itr->first << endl;
    }

    (*dumpfile) << ss.str();
}

void StateManager::RemoveAudioBuffer(std::string audioBufferId)
{
    map<string,void*>::const_iterator itr;
    itr = audioBuffers.find(audioBufferId);
    if (itr != audioBuffers.end())
    {
        void *audioBufferPtr = itr->second;
        vx_free_audioBuffer(&audioBufferPtr);
        audioBuffers.erase(audioBufferId);
    }
}

bool StateManager::ExportAudioBufferToWav(std::string audioBufferId, std::string filePath)
{
    map<string,void*>::const_iterator itr;
    itr = audioBuffers.find(audioBufferId);

    if (itr == audioBuffers.end())
    {
        return false;
    }

    if (vx_export_audioBuffer_to_wav_file(itr->second, filePath.c_str()) != 0)
    {
        return false;
    }

    return true;
}

void StateManager::RemoveSessionGroup(string session_group_handle)
{
    map<string,VxSessionGroup*>::const_iterator itr;
    itr = sessionGroups.find(session_group_handle);
    if (itr != sessionGroups.end())
    {
        VxSessionGroup *tmpGroup = itr->second;
        sessionGroups.erase(session_group_handle);
        delete tmpGroup;
    }
}

VxSessionGroup* StateManager::GetSessionGroup(string session_group_handle)
{
    map<string,VxSessionGroup*>::const_iterator itr;
    itr = sessionGroups.find(session_group_handle);
    if (itr != sessionGroups.end())
        return (VxSessionGroup*)itr->second;
    else
        return NULL;
}

void StateManager::ClearSessionGroups()
{
    map<string,VxSessionGroup*>::const_iterator itr;
    for (itr = sessionGroups.begin(); itr != sessionGroups.end(); ++itr)
    {
        VxSessionGroup *tmpGroup = itr->second;
        delete tmpGroup;
    }
    sessionGroups.clear();
}

bool StateManager::AddSession(string session_group_handle, string session_handle, string uri, int incoming)
{
    bool ret = false;
    if (isAccountLoggedIn && isConnectorInitialized)
    {
        VxSessionGroup* sg = this->GetSessionGroup(session_group_handle);
        if (sg)
        {
            sg->AddSession(session_handle, uri, incoming);
            ret = true;
        }
    }
    return ret;
}

void StateManager::RemoveSession(string session_group_handle, string session_handle)
{
    VxSessionGroup* sg = this->GetSessionGroup(session_group_handle);
    if (sg)
        sg->RemoveSession(session_handle);
}

void StateManager::UpdateSession(string session_group_handle, string session_handle, int tx, int focus, int muted, int textmuted, int font_id, int vol)
{
    VxSessionGroup* sg = this->GetSessionGroup(session_group_handle);
    if (sg)
    {
        sg->UpdateSession(session_handle, tx, focus, muted, textmuted, font_id, vol);
    }
}

void StateManager::UpdateMediaStreamState(string session_group_handle, string session_handle, vx_session_media_state state)
{
    VxSessionGroup* sg = this->GetSessionGroup(session_group_handle);
    if (sg)
        sg->UpdateMediaState(session_handle, state);
}

void StateManager::UpdateTextStreamState(string session_group_handle, string session_handle, vx_session_text_state state)
{
    VxSessionGroup* sg = this->GetSessionGroup(session_group_handle);
    if (sg)
        sg->UpdateTextState(session_handle, state);
}

bool StateManager::GetIsConnectorInitialized()
{
    return isConnectorInitialized;
}

string StateManager::GetConnectorHandle()
{
    return connectorHandle;
}

bool StateManager::GetIsAccountLoggedIn()
{
    return isAccountLoggedIn;
}

string StateManager::GetAccountHandle()
{
    return accountHandle;
}

// GKy 091211 improve, if give NULL str means check ALL, exist any ret true
bool StateManager::GetSessionGroupExists(string session_group_handle)
{
    bool found = false;

	if (session_group_handle == "")
    {
		// Check if exist any SessionGroup

		std::set<std::string> sgS; 
		sgS.clear();
		sgS = GetAllSessionGroupHandles();

		if (sgS.size() > 0)
        {
			found = true;
		}
	}
    else
    {
		map<string, VxSessionGroup*>::const_iterator sg_itr;
		sg_itr = sessionGroups.find(session_group_handle);
		if (sg_itr != sessionGroups.end())
        {
			found = true;
        }
	}

    return found;
}

// GKy 091211 old fnc.
//bool StateManager::GetSessionGroupExists(string session_group_handle)
//{
//    bool found = false;
//    map<string,VxSessionGroup*>::const_iterator sg_itr;
//    sg_itr = sessionGroups.find(session_group_handle);
//    if (sg_itr != sessionGroups.end())
//        found = true;
//    return found;
//}

// GKy 091203
std::set<std::string> StateManager::GetAllSessionGroupHandles(void)
{
	std::set<std::string> setRet;
	setRet.clear();

	map<std::string, VxSessionGroup*>::const_iterator sg_itr;

    //sg_itr = sessionGroups.find(session_group_handle);
    //if (sg_itr != sessionGroups.end())
    //    found = true;
	for (sg_itr = sessionGroups.begin(); sg_itr != sessionGroups.end(); ++sg_itr)
    {
		setRet.insert(sg_itr->first);
	}

	return setRet;
}

// GKy 091204
std::set<std::string> StateManager::GetAllSessionHandles(const char* sg_id_)
{
	std::set<std::string> setRet;
	setRet.clear();

	map<std::string, VxSessionGroup*>::const_iterator sg_itr;

	std::string strT = sg_id_;

    sg_itr = sessionGroups.find(strT);
	if (sg_itr != sessionGroups.end())
    {
		setRet = sg_itr->second->GetSessionHandles();
	}

	return setRet;
}

// GKy 091208 GKy 091221 may be obsolete, using evt_participant instead
std::set<std::string> StateManager::GetAllSessionPartnersURI(const char *sg_id_, const char *ss_id_)
{
	std::set<std::string> setRet;
	setRet.clear();

	map<std::string, VxSessionGroup*>::const_iterator sg_itr;

	std::string strT = sg_id_;

    sg_itr = sessionGroups.find(strT);
	if (sg_itr != sessionGroups.end())
    {
		//set<string> VxSessionGroup::GetSessionHandles()
		//setRet = sg_itr->second->GetSessionHandles();
	}

	//////////////////////////////////////////////////////////

	return setRet;
}

int StateManager::GetMediaSessionState(string session_handle)
{
    map<string,VxSessionGroup*>::const_iterator sg_itr;
    for (sg_itr = sessionGroups.begin(); sg_itr != sessionGroups.end(); ++sg_itr)
    {
        VxSessionGroup* sg = (VxSessionGroup*)sg_itr->second;
        VxSession* sess = sg->GetSession(session_handle);
        if (sess)
            return sess->GetMediaState();
    }
    return -1;
}

int StateManager::GetTextSessionState(string session_handle)
{
    map<string,VxSessionGroup*>::const_iterator sg_itr;
    for (sg_itr = sessionGroups.begin(); sg_itr != sessionGroups.end(); ++sg_itr)
    {
        VxSessionGroup* sg = (VxSessionGroup*)sg_itr->second;
        VxSession* sess = sg->GetSession(session_handle);
        if (sess)
            return sess->GetTextState();
    }
    return -1;
}

static std::string FormatCoordinate(double x) {
    if(x < 0.001 && x > -0.001 && x != 0) {
        return "approximately 0";
    } else {
        std::stringstream ss;
        ss << x;
        return ss.str();
    }
}

//Request map keeps track of request/response pairs.
//Session map keep track of session state
void StateManager::DumpStateToFile(ostream* dumpFile)
{
    stringstream ss;

    ss << endl << "version:              " << version << endl << endl;

    ss << "SDK Handle:           " << m_sdkHandle << endl;
    ss << "Connector Handle:     ";
    if (isConnectorInitialized)
        ss << connectorHandle;
    else
        ss << "[none]";
    ss << endl;
    ss << "Account Handle:       ";
    if (isAccountLoggedIn)
        ss << accountHandle;
    else
        ss << "[none]";
    ss << endl;
    ss << "Session Groups:         ";
    if (sessionGroups.size() > 0)
    {
        ss << endl;
        map<string,VxSessionGroup*>::const_iterator itr;
        for (itr = sessionGroups.begin(); itr != sessionGroups.end(); ++itr)
        {
            VxSessionGroup* sg = (VxSessionGroup*)itr->second;
            ss << setw(22) << right << "Group: " << sg->GetSessionGroupHandle() << endl;
            {
                set<string> handles = sg->GetSessionHandles();
                set<string>::const_iterator h_itr;
                if (sg->GetNumberOfSessions() > 0)
                for (h_itr = handles.begin(); h_itr != handles.end(); ++h_itr)
                {
                    VxSession* sess = sg->GetSession(h_itr->data());
                    ss << setw(22) << right << "Session: " << sess->GetSessionHandle() << endl;
                    ss << setw(27) << right << "URI: " << sess->GetSessionURI() << endl;
                    ss << setw(27) << right << "Audio: " << toString(sess->GetMediaState()) << endl;
                    ss << setw(27) << right << "Text: " << toString(sess->GetTextState()) <<endl;
                    ss << setw(27) << right << "Inc: " << sess->GetIsIncoming() << endl;
                    ss << setw(27) << right << "Tx: " << sess->GetIsTransmitting() << endl;
                    ss << setw(27) << right << "Foc: " << sess->GetIsFocused() << endl;
                    ss << setw(27) << right << "Mute: " << sess->GetIsMuted() << endl;
                    ss << setw(27) << right << "TextMute: " << sess->GetIsTextMuted() << endl;
                    ss << setw(27) << right << "Font: " << sess->GetFontID() << endl;
                    ss << setw(27) << right << "Vol: " << sess->GetVolume() << endl << endl;
                }
            }
        }
    }
    else
    {
        ss << "[none]";
    }

    map<string,string>::const_iterator reqs;
    ss << endl;
    ss << "Outstanding Requests:   ";
    if (requests.size() > 0)
    {
        ss << endl;
        for (reqs = requests.begin(); reqs != requests.end(); ++reqs)
        {
            ss << "    Request ID: " << reqs->first << "   Type = " << reqs->second << endl;
        }
    }
    else
    {
        ss << "[none]";
    }

    ss << endl;
    ss << "listenerHeadingDegrees: " << this->listenerHeadingDegrees << endl;
    ss << "listenerPosition:       {" << FormatCoordinate(this->listenerPosition[0]) 
        << ", " << FormatCoordinate(this->listenerPosition[1]) 
        << ", " << FormatCoordinate(this->listenerPosition[2]) << "}" << endl;

    (*dumpFile) << ss.str();
}
//added to help testing harnesses
int StateManager::GetNumOutStandingRequests() 
{
    return(requests.size());
}
string StateManager::GetTime()
{
    return "";      //TODO
}

// Request State ////////////////////////////////////////////////////////////////
void StateManager::InsertCommandReqID(string requestID, string type)
{
    requests.insert(make_pair(requestID,type));
}

void StateManager::DeleteCommandReqID(string requestID)
{
    map<string,string>::const_iterator itr;
    itr = requests.find(requestID);
    if (itr != requests.end())
    {
        requests.erase(requestID);
    }
}

// Positional /////////////////////////////////////////////////////////////////
void StateManager::SetListenerPosition(double *position)
{
    listenerPosition[0] = position[0];
    listenerPosition[1] = position[1];
    listenerPosition[2] = position[2];
}

void StateManager::GetListenerPosition(double *position)
{
    position[0] = listenerPosition[0];
    position[1] = listenerPosition[1];
    position[2] = listenerPosition[2]; 
}

void StateManager::SetListenerOrientation(double *orientation)
{
    listenerOrientation[0] = orientation[0];
    listenerOrientation[1] = orientation[1];
    listenerOrientation[2] = orientation[2];
    listenerOrientation[3] = orientation[3];
    listenerOrientation[4] = orientation[4];
    listenerOrientation[5] = orientation[5];   
}

void StateManager::GetListenerOrientation(double *orientation)
{
    orientation[0] = listenerOrientation[0];
    orientation[1] = listenerOrientation[1];
    orientation[2] = listenerOrientation[2];
    orientation[3] = listenerOrientation[3];
    orientation[4] = listenerOrientation[4];
    orientation[5] = listenerOrientation[5];   
}

void StateManager::GetListenerHeadingDegrees(double *headingDegrees)
{
    *headingDegrees = listenerHeadingDegrees;
}

void StateManager::SetListenerHeadingDegrees(double headingDegrees)
{
    listenerHeadingDegrees = headingDegrees;
}
