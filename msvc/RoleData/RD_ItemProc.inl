//************************************************************************************
//		基本物件搬移的動作
//************************************************************************************
int GetBodyItemPos( int OrgID , int Version );
int GetBankItemPos( int OrgID , int Version );
int GetEqItemPos  ( int OrgID , int Version );

int GetBodyRealPos(int index);
int GetBodyItemCount();

ItemFieldStruct* GetBodyVirtualItem( int Pos );
ItemFieldStruct* GetBodyItem( int Pos );
ItemFieldStruct* GetBankItem( int Pos );
ItemFieldStruct* GetEqItem  ( int Pos );

ItemFieldStruct* GetItem  ( int Pos , int Type );   // 0 Body 1 Bank 2 EQ

int     BodyMoney( );
int     BodyMoney_Account( );
int     BankMoeny( );
void    BodyMoney( int );
void    BankMoeny( int );

// 取得已賣出物品
SellItemFieldStruct* GetSellItem( int Pos );

//取得已賣出物品數量
int		GetSellItemCount();

//檢查欄位資料是否有問題
bool    CheckBodyItem( ItemFieldStruct& Item , int Pos );
bool    CheckBankItem( ItemFieldStruct& Item , int Pos );
bool    CheckEQItem( ItemFieldStruct& Item , int Pos );

CheckSetEQResultENUM    CheckSetEQ( int EQPos , GameObjDbStructEx*	BodyOrgDB , bool IgnoreLimitLv , int ImageObjectID );

bool    CheckBaseSetEQ( int EQPos , GameObjDbStructEx*	BodyOrgDB , bool IgnoreLimitLv , int ImageObjectID );
bool    CheckEQSwap ( int Pos1, int Pos2 );

//檢查裝備限制
bool	CheckEQLimit( GameObjDbStructEx* BodyOrgDB , bool IgnoreLimitLv );
//************************************************************************************
//加一個物品到暫存區
bool AddItemtoBuf	( ItemFieldStruct& Item );
//刪除暫存區的物件
bool DelItemFromBuf	( ItemFieldStruct& Item );

//Type = 0 Body 1 Bank
bool	CheckItemPosTimeFlag( int Type , int Pos , int ItemObjID = 0 );
bool	CheckPetPosTimeFlag( int Pos );

//更新資料
RoleDataResultENUM    SetItemInfo_Body( ItemFieldStruct& Item , int Pos );
RoleDataResultENUM    SetItemInfo_Bank( ItemFieldStruct& Item , int Pos );
RoleDataResultENUM    SetItemInfo_EQ( ItemFieldStruct& Item , int Pos );

//把暫存區的物品取到身上
//Item 為確定的物品資料
RoleDataResultENUM GetItemBuftoBody( ItemFieldStruct& Item , int Pos , int Count );

//加一個物品到身上某位置
RoleDataResultENUM AddItemtoBody( ItemFieldStruct& Item , int Pos );
//刪除一個身上物品
RoleDataResultENUM DelItemFromBody( ItemFieldStruct& Item , int Pos );



//加一個物品到銀行某位置
RoleDataResultENUM AddItemtoBank( ItemFieldStruct& Item , int Pos );
//刪除一個銀行物品
RoleDataResultENUM DelItemFromBank( ItemFieldStruct& Item , int Pos );

//刪除一個裝備
RoleDataResultENUM DelItemFromEQ( ItemFieldStruct& Item , int Pos );

//身體物品交換
RoleDataResultENUM ExchangeBodyItem(	ItemFieldStruct& Item0 , int Pos0  
                                    ,	ItemFieldStruct& Item1 , int Pos1  );

//銀行物品交換
RoleDataResultENUM ExchangeBankItem(	ItemFieldStruct& Item0 , int Pos0  
                                    ,	ItemFieldStruct& Item1 , int Pos1  );

//身體與銀行交換物品
RoleDataResultENUM ExchangeBodyBankItem(	ItemFieldStruct& BodyItem , int BodyPos  
                                        ,	ItemFieldStruct& BankItem , int BankPos  );

//身體與銀行交換物品
RoleDataResultENUM ExchangeBankBodyItem(	ItemFieldStruct& BankItem , int BankPos 
                                        ,   ItemFieldStruct& BodyItem , int BodyPos  );

//身體與裝備交換物品
RoleDataResultENUM ExchangeBodyEQItem(	    ItemFieldStruct& BodyItem   , int BodyPos 
                                        ,   ItemFieldStruct& EQItem     , int EQPos  
										,	bool IsFromEq );

//銀行與裝備交換物品
RoleDataResultENUM ExchangeBankEQItem(	    ItemFieldStruct& BankItem   , int BankPos 
                                        ,   ItemFieldStruct& EQItem     , int EQPos  
										,	bool IsFromEq  );

//裝備換物品
RoleDataResultENUM ExchangeEQItem(      ItemFieldStruct& Item1   , int Pos1 
                                  ,     ItemFieldStruct& Item2   , int Pos2  );



//把身上某欄位物品分出一部份到另外一個欄位
RoleDataResultENUM ApartBodyItem(	ItemFieldStruct& Item , int PosSrc 
                                 ,	int Count , int PosDes  );


//檢查加身上的金錢
bool CheckAddBodyMoney( int Count );
//檢查加銀行的金錢
//bool CheckAddBankMoney( int Count );
//加身上的金錢
bool AddBodyMoney( int Count , RoleDataEx* FromRole , ActionTypeENUM Type , bool SaveZoneLog );
bool AddBodyMoney( int Count , int FromRoleDBID , int FromNpcDBID , ActionTypeENUM Type , bool SaveZoneLog );
//加銀行的金錢
//bool AddBankMoney( int Count );

//檢查加身上的金錢
bool CheckAddBodyMoney_Account( int Count );

//加身上的金錢
bool AddBodyMoney_Account( int Count , RoleDataEx* FromRole , ActionTypeENUM Type , bool SaveZoneLog , bool LockMoneyProc = false );
bool AddBodyMoney_Account( int Count , int FromRoleDBID , int FromNpcDBID , ActionTypeENUM Type , bool SaveZoneLog , bool LockMoneyProc = false );

void AddLockAccountMoney( int Count, int LockDay);
void FixLockMoney( int Count );

bool CheckAddMoney_Bonus( int Count );
bool AddMoney_Bonus( int Count , RoleDataEx* FromRole , ActionTypeENUM Type );
//*******************************************************************************************************************
//物品給予
bool    BaseGiveItem( ItemFieldStruct& Item );

bool    GiveItem( ItemFieldStruct& Item , ActionTypeENUM Type , RoleDataEx* FromRole , const char* Note );
bool    GiveItem( ItemFieldStruct& Item , ActionTypeENUM Type , int FromRoleDBID , int FromNpcDBID , const char* Note );

bool	GiveItem( int ItemID , int Count , ActionTypeENUM Type, RoleDataEx* FromRole , const char* Note );
//bool	GiveItemLv( int ItemID , int Count , int LV , ActionTypeENUM Type, RoleDataEx* FromRole );

bool	GiveTreasure_Gamble( int OrgObjID  , RoleDataEx* FromRole );




//-----------------------------------------------------------------------------------------------------------------
//計算交易物品數量
int		CalTradeItemCount();
//計算身體上的交易物品有幾個
int		CalBodyTradeItemCount();

//計算有多少個空欄位
//int		CalEmptyItemCount();
//清除所有交易中的物品 至 物品欄
void	ClsAllTradeItem();
//刪除所有交易中的物品
void    DelAllTradeItem();
//-----------------------------------------------------------------------------------------------------------------
//身上物品數量計算
int     CalBodyItemCountNoLock( int OrgID );
int     CalBodyItemCount( int OrgID , bool ignoreLocked=false);
int     CalBankItemCount( int OrgID );
int     CalEqItemCount( int OrgID );

bool	CheckItemInBody( int OrgID, bool inBank=true, bool inEQ=true);

//-----------------------------------------------------------------------------------------------------------------
// 取得身上與銀行內的物品 ObjID
int		GetBodyItemIDByName(const char* name);
int		GetBankItemIDByName(const char* name);

//刪除身上的某物品
bool    DelBodyItem( int OrgID , int Count , ActionTypeENUM Type );

//刪除重要物品
bool    DelKeyItem( int OrgID );
bool	AddKeyItem( int OrdID );

bool    DelTitle( int OrgID );
bool	AddTitle( int OrdID );

bool    DelCard( int OrgID );
bool	AddCard( int OrdID );
//-----------------------------------------------------------------------------------------------------------------
bool    CheckLimit( LimitStruct& Limit , bool IgnoreLimitLv = false );

//取得寶物
static bool	GetTreasure( int TreasureID , int& ObjID  , int& Count , int DLv = 100 );

//檢查是否有某個重要物品
bool	CheckKeyItem( int KeyItemID );

//////////////////////////////////////////////////////////////////////////
//bool	AddDropItem( int OwnerDBID , ItemFieldStruct& Item );

