
//int     SelfClock();
void    IncDMove( );
int     MoveTime( float X , float Y , float Z );

//���oSampleRoleData
void    GetSampleRoleData( SampleRoleData* Data );

//���oNPCData�����
void    GetNPCData( NPCData* Data );

//²�d�ɶ�  �n�O _DEF_BASE_CLOCL_UNIT_ ����
bool    ClockMod( int Mod );


//�p�⭱�諸��V
static float CalDir( float dx , float dz );

float	CalDir( RoleDataEx* Target );

static void	CalDir( float Dir , float& dx , float& dz );

//�P�ݪ���V�ҧ�������
float   CalAngle( RoleDataEx* Target );

//�����ؼ�(�����PFollow)
bool	AttackTarget( int TargetID );

//�������
bool	StopAttack();

//�M���ϥΤ������~( �ϥΥ��ѲM�� )
bool    ClsUseItem();

//�R���ϥΪ��~
bool    DelUseItem( );

//�ϥΪk�N�ӷl
void    DelMagicCost( GameObjDbStructEx* Magic , int MagicLv );
void    DelMagicCostBase( GameObjDbStructEx* Magic , int MagicLv , MagicSpellCostTypeENUM CostType , int CostValue );

//�����
void    StopMove( );
void    StopMoveNow( );

//���M�T�몺����
RoleDataEx*    SearchHate( float Range );
RoleDataEx*    SearchHate( );

//�j�M�s���ؼ� �䤣��N�������
//bool		FindNewHateTarget( );
//bool		FindNewHateTarget( float Range );
//-------------------------------------------------------------------------------------------
//�k�N�ޯ�t�I
//-------------------------------------------------------------------------------------------
//��l�ƥD��¾�k�N���
bool    InitMagicBook( );

//�˹�O�_�i�H�k�N�t�I
bool    CheckSetMagicPoint( int MagicPos );

//���]¾�~���
void    ResetJobSkill( );

//�ˬd�O�_�k�N�P��m��ƻP�����I�N�۲ŦX
bool    CheckRoleMagic( int MagicID , int MagicPos );
//�ˬd�O�_�k�N�P��m��ƻP�����I�N�۲ŦX
bool    CheckRoleSPMagic( int MagicID , int MagicPos );

//���]�֦����Q�ʧޯ�
void    ReSetPassiveSkill( );
//-------------------------------------------------------------------------------------------
//���o���󷽩l���D�H
RoleDataEx* GetOrgOwner();
//-------------------------------------------------------------------------------------------
//���o�֢߫~���B�~�W�[���v
int		GetHQExtraValue( SkillValueTypeENUM SkillType );

//-------------------------------------------------------------------------------------------
//�U�u���p�⪺Buff or Coldown�B�z
void	ProcOffLineTime();

//���o OnlinePlayerInfoStruct �����
void	GetOnlinePlayerInfo( OnlinePlayerInfoStruct& Info );

//-------------------------------------------------------------------------------------------
//�]�k�ާl���p�� �^�ǧl���h��( �|�B�z�ʥ])
int		MagicShieldAbsorbProc( RoleDataEx* Attack , GameObjDbStruct* AtkMagic , int &Damage );

//-------------------------------------------------------------------------------------------
//���o�Y�ޯ�W������
int		GetLifeSkillMax( SkillValueTypeENUM Type );
//-------------------------------------------------------------------------------------------
//�M��PK ���
void	SetPKOff( );
//-------------------------------------------------------------------------------------------
//�H�ثe�����Ÿ�ƨ��o�Y��
void	GetTitle( );	
//-------------------------------------------------------------------------------------------
//���o�I�k�ɶ�
float		GetSpellTime( GameObjDbStructEx* MagicDB );
//-------------------------------------------------------------------------------------------
//���o�N�j�ɶ�
float		GetColdownTime( GameObjDbStructEx* MagicDB );
//-------------------------------------------------------------------------------------------
//���]�˳ƪ��@�[��
void		ResetEqDurable();
//�˳ƭ@�[�l�ӳB�z
bool		EqDurableProcess( EQWearPosENUM Pos , int DecDurable );
//-------------------------------------------------------------------------------------------
//�Y�Ǩƥ�W�[Buf�ɶ�
void		OnEventAddBuffTime( );
//-------------------------------------------------------------------------------------------
//�]�w��������
void		SetDelayAttack( int Time );
//-------------------------------------------------------------------------------------------
//��Ҧ�Itme Queue�����F���J���W
void		ItemQueueToBody();
//-------------------------------------------------------------------------------------------
//���c����
GoodEvilTypeENUM	GetGoodEvilType( );

//-------------------------------------------------------------------------------------------
//�R�����W���~
bool		DelBodyItem_ByPos( int Pos , int Count , ActionTypeENUM Type );

//�̰�����
int			MaxJobLv();
//////////////////////////////////////////////////////////////////////////
//�˳ƲŤ����t��
//////////////////////////////////////////////////////////////////////////
//�˳Ʈe�� ==> �]��
static bool	SmeltEqtoMagicStone( ItemFieldStruct* EQ , ItemFieldStruct* Item , ItemFieldStruct* outResultItem );
//��� �]��(�ɵ�)
static bool	RefineMagicStone( ItemFieldStruct* Item[3] , ItemFieldStruct* outResultItem );
//�˳� �P�]�ۺ��X
static bool	CombinEQandMagicStone(  ItemFieldStruct* EQ , ItemFieldStruct* MagicStone[3] , ItemFieldStruct* outResultItem  );
//�Ť��ഫ
static bool	RuneTransfer( ItemFieldStruct* Rune1 , ItemFieldStruct* Rune2 , ItemFieldStruct* outResultItem );
//�Ť�ɵ�
static bool	RefineRune( ItemFieldStruct* Rune , ItemFieldStruct* outResultItem );
//���~�ĦX�I��
static bool	ItemCombine( vector< ItemFieldStruct >& ItemList , ItemFieldStruct* outResultItem );

//////////////////////////////////////////////////////////////////////////
//�]�k���Ҥ�
bool	MagicBoxSmelt(  ItemFieldStruct* outResultItem );
//////////////////////////////////////////////////////////////////////////
static void	SelectAbility( vector<ItemFieldStruct*>& AbilityList , ItemFieldStruct* outResultItem );
//�p�⦳�X�ӪŦ�
int		EmptyPacketCount();
//////////////////////////////////////////////////////////////////////////
void	ResetLockAccountMoney( );

FixFightArgumentStruct&   FixArg();     //�T�w�Ѽƪ�

//���o�𨾼v�T���Ůt
int CalAddDotMagicLv( RoleDataEx* Target , GameObjDbStructEx* MagicBaseObjDB , int SpellTime , int OrgMagicLv );

//�O�I�B�z
void	InsureProc();

//�R���@�Ӫ��~
bool	DelOneItem( int ItemPos , ItemFieldStruct& Item , ActionTypeENUM ActionType );

void	SwapEQ( int posID );

int		JobCount( );

bool	OldUnPacket( ItemFieldStruct *SrvItem );
bool	NewUnPacket( ItemFieldStruct *SrvItem );
bool	UnPacket_DropList( ItemFieldStruct *SrvItem );

//�ץ����~���
static void	FixItem( ItemFieldStruct *Item );

int		HPMPSPSum();

//���o�d�����
PetStruct*	GetPetInfo( RoleDataEx* Pet );

//���o�즹���Ū�TP
static int	GetLvTotalTP( int Lv );

static void	GetRareEffect( GameObjDbStructEx* OrgDB , int AddRare , float& Dmg , float& MDmg , float& Def , float& MDef );

//�p��i�H���h�֤H
int		CalCarryCount();

/*
//�W�[����(�Ҧ�����)
bool	AddMoneyBase( PriceTypeENUM Type , int Money );
//�ˬd����(�Ҧ�����)
bool	CheckMoneyBase( PriceTypeENUM Type , int Money );
*/

void	PhantomEQChangeProc();

static int KeyItemObjToID( int objID );
static int IDtoKeyItemObj( int id );