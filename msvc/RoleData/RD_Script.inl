

int		Quest_Add							( int iQuestID );
void	Quest_Complete						( int iQuestIndex, int iQuestID );
bool	Quest_Delete						( int iQuestField, int iQuestID );
bool	Quest_Failed						( int iQuestID );
int		Quest_Size							();									// �{�b�w�����Ȫ��ƶq
	// ��������, �Ǧ^�ȥN��ĴX�� Quest �����F
int		CheckQuest_IsComplete				( int iQuestIndex, int iQuestID, GameObjectQuestDetail *pQuest );


int		CheckQuest_IsAvailable				( int iQuestID, GameObjectQuestDetail *pQuest, bool bIgnoreLV );
int		CheckQuest_IsAvailable_Base			( int iQuestID, GameObjectQuestDetail *pQuest );
	// ILVMode = 0 ��L�]�w, 1 ��]�w�ˬd�W��, 2 �������ˬd����

int		CheckQuestList_IsGotQuest			( int iQuestID );		// �ˬd�H�����W,���L�֦����w�� Quest
bool	CheckQuestHistory_IsComplete		( int iQuestID );
int		CheckGrayQuest						( int iQuestID, GameObjectQuestDetail *pQuest );

//int		CheckQuest_RequestKill_AddCount		( int iDeadObjID );

//int		CheckQuest_RequestKill_Complete		( int iTempIndex );
	// �ǤJ Add_QuestKillCount �ҶǦ^�� Tempdata ���� index, �Y�� Quest �w����, �h�Ǧ^ QuestField
	// �_�h�N�Ǧ^ -1

//void	CheckQuest_RequestKill_SetTempData	( int iQuestField, GameObjectQuestDetail *pQuest );
	// �ˬd���w���ȬO�_�����w���˥ؼ�, �Y������ �h�b�H�� Tempdata �W�]�w�Ȧs���

//void	CheckQuest_KillToGetItem_SetTempData( int iQuestField, GameObjectQuestDetail *pQuest );
	// �ˬd���w���ȬO�_�����w���˥ؼШ��o���~���, �Y������ �h�b�H�� Tempdata �W�]�w�Ȧs���

//void	CheckQuest_ClickToGetItem_SetTempData( int iQuestField, GameObjectQuestDetail *pQuest );
	// �ˬd���w���ȬO�_�����w���˥ؼШ��o���~���, �Y������ �h�b�H�� Tempdata �W�]�w�Ȧs���

//-------------------------------------------------------------------------------------------------
//�����~��ԧQ�~(Party���T)
bool    Sc_GiveItemToParty( int OrgID , int Count );

//�����~��ӤH TempBuffer(�����X��)
bool    Sc_GiveItemToBuf( int OrgID , int Count , ActionTypeENUM Type, RoleDataEx* FromRole , const char* Note );

//�����~��ӤH���W���ŭI�]���, �n�O�S����, �h�|��^ false
bool    Sc_GiveItemToBodyFreeSlot( int OrgID , int Count , ActionTypeENUM Type, RoleDataEx* FromRole , const char* Note );

int		GetBodyFreeSlot();

int		CountItemFromQueue( int iGUID );
//�R�����~
bool    Sc_DelItemFromBody( int OrgID , int Count , ActionTypeENUM Type );
bool    Sc_DelItem( int OrgID , int Count , ActionTypeENUM Type );

//���W�n( +- )
void    Sc_GiveFame( int Value );
//��Exp ( +- )
void    Sc_GiveExp( int Value );
//����  ( +- )
bool    Sc_GiveMoney( int Value );

//-------------------------------------------------------------------------------------------------
//�ˬd�����~��ԧQ�~(Party���T)
bool    Sc_CheckGiveItemToParty		( int OrgID , int Count );
//�ˬd�����~��ӤH TempBuffer(�����X��)
bool    Sc_CheckGiveItemToBuf		( int OrgID , int Count );

//�ˬd�R�����~
bool    Sc_CheckItemFromBody		( int OrgID , int Count );
bool    Sc_CheckGiveMoney			( int Value );

//-------------------------------------------------------------------------------------------------
bool	Sc_CheckItemFromBank		( int OrgID, int Count );
//-------------------------------------------------------------------------------------------------
bool	Sc_CheckItemFromRole		( int OrgID, int Count );
int		Sc_GetItemNumFromRole		( int OrgID ); 