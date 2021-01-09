

int		Quest_Add							( int iQuestID );
void	Quest_Complete						( int iQuestIndex, int iQuestID );
bool	Quest_Delete						( int iQuestField, int iQuestID );
bool	Quest_Failed						( int iQuestID );
int		Quest_Size							();									// 現在已有任務的數量
	// 完成任務, 傳回值代表第幾格 Quest 完成了
int		CheckQuest_IsComplete				( int iQuestIndex, int iQuestID, GameObjectQuestDetail *pQuest );


int		CheckQuest_IsAvailable				( int iQuestID, GameObjectQuestDetail *pQuest, bool bIgnoreLV );
int		CheckQuest_IsAvailable_Base			( int iQuestID, GameObjectQuestDetail *pQuest );
	// ILVMode = 0 表無設定, 1 表設定檢查上限, 2 表完全不檢查等級

int		CheckQuestList_IsGotQuest			( int iQuestID );		// 檢查人物身上,有無擁有指定的 Quest
bool	CheckQuestHistory_IsComplete		( int iQuestID );
int		CheckGrayQuest						( int iQuestID, GameObjectQuestDetail *pQuest );

//int		CheckQuest_RequestKill_AddCount		( int iDeadObjID );

//int		CheckQuest_RequestKill_Complete		( int iTempIndex );
	// 傳入 Add_QuestKillCount 所傳回的 Tempdata 內的 index, 若該 Quest 已完成, 則傳回 QuestField
	// 否則將傳回 -1

//void	CheckQuest_RequestKill_SetTempData	( int iQuestField, GameObjectQuestDetail *pQuest );
	// 檢查指定任務是否有指定打倒目標, 若有的話 則在人物 Tempdata 上設定暫存資料

//void	CheckQuest_KillToGetItem_SetTempData( int iQuestField, GameObjectQuestDetail *pQuest );
	// 檢查指定任務是否有指定打倒目標取得物品資料, 若有的話 則在人物 Tempdata 上設定暫存資料

//void	CheckQuest_ClickToGetItem_SetTempData( int iQuestField, GameObjectQuestDetail *pQuest );
	// 檢查指定任務是否有指定打倒目標取得物品資料, 若有的話 則在人物 Tempdata 上設定暫存資料

//-------------------------------------------------------------------------------------------------
//給物品到戰利品(Party分響)
bool    Sc_GiveItemToParty( int OrgID , int Count );

//給物品到個人 TempBuffer(任物旗標)
bool    Sc_GiveItemToBuf( int OrgID , int Count , ActionTypeENUM Type, RoleDataEx* FromRole , const char* Note );

//給物品到個人身上的空背包欄位, 要是沒有空, 則會返回 false
bool    Sc_GiveItemToBodyFreeSlot( int OrgID , int Count , ActionTypeENUM Type, RoleDataEx* FromRole , const char* Note );

int		GetBodyFreeSlot();

int		CountItemFromQueue( int iGUID );
//刪除物品
bool    Sc_DelItemFromBody( int OrgID , int Count , ActionTypeENUM Type );
bool    Sc_DelItem( int OrgID , int Count , ActionTypeENUM Type );

//給名聲( +- )
void    Sc_GiveFame( int Value );
//給Exp ( +- )
void    Sc_GiveExp( int Value );
//給錢  ( +- )
bool    Sc_GiveMoney( int Value );

//-------------------------------------------------------------------------------------------------
//檢查給物品到戰利品(Party分響)
bool    Sc_CheckGiveItemToParty		( int OrgID , int Count );
//檢查給物品到個人 TempBuffer(任物旗標)
bool    Sc_CheckGiveItemToBuf		( int OrgID , int Count );

//檢查刪除物品
bool    Sc_CheckItemFromBody		( int OrgID , int Count );
bool    Sc_CheckGiveMoney			( int Value );

//-------------------------------------------------------------------------------------------------
bool	Sc_CheckItemFromBank		( int OrgID, int Count );
//-------------------------------------------------------------------------------------------------
bool	Sc_CheckItemFromRole		( int OrgID, int Count );
int		Sc_GetItemNumFromRole		( int OrgID ); 