//************************************************************************************
//		�򥻪���h�����ʧ@
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

// ���o�w��X���~
SellItemFieldStruct* GetSellItem( int Pos );

//���o�w��X���~�ƶq
int		GetSellItemCount();

//�ˬd����ƬO�_�����D
bool    CheckBodyItem( ItemFieldStruct& Item , int Pos );
bool    CheckBankItem( ItemFieldStruct& Item , int Pos );
bool    CheckEQItem( ItemFieldStruct& Item , int Pos );

CheckSetEQResultENUM    CheckSetEQ( int EQPos , GameObjDbStructEx*	BodyOrgDB , bool IgnoreLimitLv , int ImageObjectID );

bool    CheckBaseSetEQ( int EQPos , GameObjDbStructEx*	BodyOrgDB , bool IgnoreLimitLv , int ImageObjectID );
bool    CheckEQSwap ( int Pos1, int Pos2 );

//�ˬd�˳ƭ���
bool	CheckEQLimit( GameObjDbStructEx* BodyOrgDB , bool IgnoreLimitLv );
//************************************************************************************
//�[�@�Ӫ��~��Ȧs��
bool AddItemtoBuf	( ItemFieldStruct& Item );
//�R���Ȧs�Ϫ�����
bool DelItemFromBuf	( ItemFieldStruct& Item );

//Type = 0 Body 1 Bank
bool	CheckItemPosTimeFlag( int Type , int Pos , int ItemObjID = 0 );
bool	CheckPetPosTimeFlag( int Pos );

//��s���
RoleDataResultENUM    SetItemInfo_Body( ItemFieldStruct& Item , int Pos );
RoleDataResultENUM    SetItemInfo_Bank( ItemFieldStruct& Item , int Pos );
RoleDataResultENUM    SetItemInfo_EQ( ItemFieldStruct& Item , int Pos );

//��Ȧs�Ϫ����~���쨭�W
//Item ���T�w�����~���
RoleDataResultENUM GetItemBuftoBody( ItemFieldStruct& Item , int Pos , int Count );

//�[�@�Ӫ��~�쨭�W�Y��m
RoleDataResultENUM AddItemtoBody( ItemFieldStruct& Item , int Pos );
//�R���@�Ө��W���~
RoleDataResultENUM DelItemFromBody( ItemFieldStruct& Item , int Pos );



//�[�@�Ӫ��~��Ȧ�Y��m
RoleDataResultENUM AddItemtoBank( ItemFieldStruct& Item , int Pos );
//�R���@�ӻȦ檫�~
RoleDataResultENUM DelItemFromBank( ItemFieldStruct& Item , int Pos );

//�R���@�Ӹ˳�
RoleDataResultENUM DelItemFromEQ( ItemFieldStruct& Item , int Pos );

//���骫�~�洫
RoleDataResultENUM ExchangeBodyItem(	ItemFieldStruct& Item0 , int Pos0  
                                    ,	ItemFieldStruct& Item1 , int Pos1  );

//�Ȧ檫�~�洫
RoleDataResultENUM ExchangeBankItem(	ItemFieldStruct& Item0 , int Pos0  
                                    ,	ItemFieldStruct& Item1 , int Pos1  );

//����P�Ȧ�洫���~
RoleDataResultENUM ExchangeBodyBankItem(	ItemFieldStruct& BodyItem , int BodyPos  
                                        ,	ItemFieldStruct& BankItem , int BankPos  );

//����P�Ȧ�洫���~
RoleDataResultENUM ExchangeBankBodyItem(	ItemFieldStruct& BankItem , int BankPos 
                                        ,   ItemFieldStruct& BodyItem , int BodyPos  );

//����P�˳ƥ洫���~
RoleDataResultENUM ExchangeBodyEQItem(	    ItemFieldStruct& BodyItem   , int BodyPos 
                                        ,   ItemFieldStruct& EQItem     , int EQPos  
										,	bool IsFromEq );

//�Ȧ�P�˳ƥ洫���~
RoleDataResultENUM ExchangeBankEQItem(	    ItemFieldStruct& BankItem   , int BankPos 
                                        ,   ItemFieldStruct& EQItem     , int EQPos  
										,	bool IsFromEq  );

//�˳ƴ����~
RoleDataResultENUM ExchangeEQItem(      ItemFieldStruct& Item1   , int Pos1 
                                  ,     ItemFieldStruct& Item2   , int Pos2  );



//�⨭�W�Y��쪫�~���X�@������t�~�@�����
RoleDataResultENUM ApartBodyItem(	ItemFieldStruct& Item , int PosSrc 
                                 ,	int Count , int PosDes  );


//�ˬd�[���W������
bool CheckAddBodyMoney( int Count );
//�ˬd�[�Ȧ檺����
//bool CheckAddBankMoney( int Count );
//�[���W������
bool AddBodyMoney( int Count , RoleDataEx* FromRole , ActionTypeENUM Type , bool SaveZoneLog );
bool AddBodyMoney( int Count , int FromRoleDBID , int FromNpcDBID , ActionTypeENUM Type , bool SaveZoneLog );
//�[�Ȧ檺����
//bool AddBankMoney( int Count );

//�ˬd�[���W������
bool CheckAddBodyMoney_Account( int Count );

//�[���W������
bool AddBodyMoney_Account( int Count , RoleDataEx* FromRole , ActionTypeENUM Type , bool SaveZoneLog , bool LockMoneyProc = false );
bool AddBodyMoney_Account( int Count , int FromRoleDBID , int FromNpcDBID , ActionTypeENUM Type , bool SaveZoneLog , bool LockMoneyProc = false );

void AddLockAccountMoney( int Count, int LockDay);
void FixLockMoney( int Count );

bool CheckAddMoney_Bonus( int Count );
bool AddMoney_Bonus( int Count , RoleDataEx* FromRole , ActionTypeENUM Type );
//*******************************************************************************************************************
//���~����
bool    BaseGiveItem( ItemFieldStruct& Item );

bool    GiveItem( ItemFieldStruct& Item , ActionTypeENUM Type , RoleDataEx* FromRole , const char* Note );
bool    GiveItem( ItemFieldStruct& Item , ActionTypeENUM Type , int FromRoleDBID , int FromNpcDBID , const char* Note );

bool	GiveItem( int ItemID , int Count , ActionTypeENUM Type, RoleDataEx* FromRole , const char* Note );
//bool	GiveItemLv( int ItemID , int Count , int LV , ActionTypeENUM Type, RoleDataEx* FromRole );

bool	GiveTreasure_Gamble( int OrgObjID  , RoleDataEx* FromRole );




//-----------------------------------------------------------------------------------------------------------------
//�p�������~�ƶq
int		CalTradeItemCount();
//�p�⨭��W��������~���X��
int		CalBodyTradeItemCount();

//�p�⦳�h�֭Ӫ����
//int		CalEmptyItemCount();
//�M���Ҧ�����������~ �� ���~��
void	ClsAllTradeItem();
//�R���Ҧ�����������~
void    DelAllTradeItem();
//-----------------------------------------------------------------------------------------------------------------
//���W���~�ƶq�p��
int     CalBodyItemCountNoLock( int OrgID );
int     CalBodyItemCount( int OrgID , bool ignoreLocked=false);
int     CalBankItemCount( int OrgID );
int     CalEqItemCount( int OrgID );

bool	CheckItemInBody( int OrgID, bool inBank=true, bool inEQ=true);

//-----------------------------------------------------------------------------------------------------------------
// ���o���W�P�Ȧ椺�����~ ObjID
int		GetBodyItemIDByName(const char* name);
int		GetBankItemIDByName(const char* name);

//�R�����W���Y���~
bool    DelBodyItem( int OrgID , int Count , ActionTypeENUM Type );

//�R�����n���~
bool    DelKeyItem( int OrgID );
bool	AddKeyItem( int OrdID );

bool    DelTitle( int OrgID );
bool	AddTitle( int OrdID );

bool    DelCard( int OrgID );
bool	AddCard( int OrdID );
//-----------------------------------------------------------------------------------------------------------------
bool    CheckLimit( LimitStruct& Limit , bool IgnoreLimitLv = false );

//���o�_��
static bool	GetTreasure( int TreasureID , int& ObjID  , int& Count , int DLv = 100 );

//�ˬd�O�_���Y�ӭ��n���~
bool	CheckKeyItem( int KeyItemID );

//////////////////////////////////////////////////////////////////////////
//bool	AddDropItem( int OwnerDBID , ItemFieldStruct& Item );

