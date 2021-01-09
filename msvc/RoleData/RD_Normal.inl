
//int     SelfClock();
void    IncDMove( );
int     MoveTime( float X , float Y , float Z );

//¨ú±oSampleRoleData
void    GetSampleRoleData( SampleRoleData* Data );

//¨ú±oNPCDataªº¸ê®Æ
void    GetNPCData( NPCData* Data );

//Â²¬d®É¶¡  ­n¬O _DEF_BASE_CLOCL_UNIT_ ­¿¼Æ
bool    ClockMod( int Mod );


//­pºâ­±¹ïªº¤è¦V
static float CalDir( float dx , float dz );

float	CalDir( RoleDataEx* Target );

static void	CalDir( float Dir , float& dx , float& dz );

//»P¬Ýªº¤è¦V©Ò§¨ªº¨¤«×
float   CalAngle( RoleDataEx* Target );

//§ðÀ»¥Ø¼Ð(§ðÀ»»PFollow)
bool	AttackTarget( int TargetID );

//°±¤î§ðÀ»
bool	StopAttack();

//²M°£¨Ï¥Î¤¤ªºª««~( ¨Ï¥Î¥¢±Ñ²M°£ )
bool    ClsUseItem();

//§R°£¨Ï¥Îª««~
bool    DelUseItem( );

//¨Ï¥Îªk³N¯Ó·l
void    DelMagicCost( GameObjDbStructEx* Magic , int MagicLv );
void    DelMagicCostBase( GameObjDbStructEx* Magic , int MagicLv , MagicSpellCostTypeENUM CostType , int CostValue );

//°±¤î²¾°Ê
void    StopMove( );
void    StopMoveNow( );

//¦¬´M·T«ëªº¨¤¦â
RoleDataEx*    SearchHate( float Range );
RoleDataEx*    SearchHate( );

//·j´M·sªº¥Ø¼Ð §ä¤£¨ì´N°±¤î§ðÀ»
//bool		FindNewHateTarget( );
//bool		FindNewHateTarget( float Range );
//-------------------------------------------------------------------------------------------
//ªk³N§Þ¯à°tÂI
//-------------------------------------------------------------------------------------------
//ªì©l¤Æ¥D°ÆÂ¾ªk³N¸ê®Æ
bool    InitMagicBook( );

//ÀË¹î¬O§_¥i¥Hªk³N°tÂI
bool    CheckSetMagicPoint( int MagicPos );

//­«³]Â¾·~¸ê®Æ
void    ResetJobSkill( );

//ÀË¬d¬O§_ªk³N»P¦ì¸m¸ê®Æ»P¨¤¦âÂI³N¬Û²Å¦X
bool    CheckRoleMagic( int MagicID , int MagicPos );
//ÀË¬d¬O§_ªk³N»P¦ì¸m¸ê®Æ»P¨¤¦âÂI³N¬Û²Å¦X
bool    CheckRoleSPMagic( int MagicID , int MagicPos );

//­«³]¾Ö¦³ªº³Q°Ê§Þ¯à
void    ReSetPassiveSkill( );
//-------------------------------------------------------------------------------------------
//¨ú±oª«¥ó·½©lªº¥D¤H
RoleDataEx* GetOrgOwner();
//-------------------------------------------------------------------------------------------
//¨ú±o¢Ö¢ß«~ªºÃB¥~¼W¥[¾÷²v
int		GetHQExtraValue( SkillValueTypeENUM SkillType );

//-------------------------------------------------------------------------------------------
//¤U½u¦³­pºâªºBuff or Coldown³B²z
void	ProcOffLineTime();

//¨ú±o OnlinePlayerInfoStruct ªº¸ê®Æ
void	GetOnlinePlayerInfo( OnlinePlayerInfoStruct& Info );

//-------------------------------------------------------------------------------------------
//Å]ªk¬Þ§l¦¬­pºâ ¦^¶Ç§l¦¬¦h¤Ö( ·|³B²z«Ê¥])
int		MagicShieldAbsorbProc( RoleDataEx* Attack , GameObjDbStruct* AtkMagic , int &Damage );

//-------------------------------------------------------------------------------------------
//¨ú±o¬Y§Þ¯à¤W­­ª«¥ó
int		GetLifeSkillMax( SkillValueTypeENUM Type );
//-------------------------------------------------------------------------------------------
//²M°£PK ¸ê®Æ
void	SetPKOff( );
//-------------------------------------------------------------------------------------------
//¥H¥Ø«eªºµ¥¯Å¸ê®Æ¨ú±oÀY»Î
void	GetTitle( );	
//-------------------------------------------------------------------------------------------
//¨ú±o¬Iªk®É¶¡
float		GetSpellTime( GameObjDbStructEx* MagicDB );
//-------------------------------------------------------------------------------------------
//¨ú±o§Nƒj®É¶¡
float		GetColdownTime( GameObjDbStructEx* MagicDB );
//-------------------------------------------------------------------------------------------
//­«³]¸Ë³Æªº­@¤[«×
void		ResetEqDurable();
//¸Ë³Æ­@¤[·l¯Ó³B²z
bool		EqDurableProcess( EQWearPosENUM Pos , int DecDurable );
//-------------------------------------------------------------------------------------------
//¬Y¨Ç¨Æ¥ó¼W¥[Buf®É¶¡
void		OnEventAddBuffTime( );
//-------------------------------------------------------------------------------------------
//³]©w§ðÀ»©µ¿ð
void		SetDelayAttack( int Time );
//-------------------------------------------------------------------------------------------
//§â©Ò¦³Itme Queue¤ºªºªF¦è°ï¤J¨­¤W
void		ItemQueueToBody();
//-------------------------------------------------------------------------------------------
//µ½´cµ¥¯Å
GoodEvilTypeENUM	GetGoodEvilType( );

//-------------------------------------------------------------------------------------------
//§R°£¨­¤Wª««~
bool		DelBodyItem_ByPos( int Pos , int Count , ActionTypeENUM Type );

//³Ì°ªµ¥¯Å
int			MaxJobLv();
//////////////////////////////////////////////////////////////////////////
//¸Ë³Æ²Å¤å¿ÄÁå¨t²Î
//////////////////////////////////////////////////////////////////////////
//¸Ë³Æ®e¸Ñ ==> Å]¥Û
static bool	SmeltEqtoMagicStone( ItemFieldStruct* EQ , ItemFieldStruct* Item , ItemFieldStruct* outResultItem );
//ºë·Ò Å]¥Û(¤Éµ¥)
static bool	RefineMagicStone( ItemFieldStruct* Item[3] , ItemFieldStruct* outResultItem );
//¸Ë³Æ »PÅ]¥Ûº²¦X
static bool	CombinEQandMagicStone(  ItemFieldStruct* EQ , ItemFieldStruct* MagicStone[3] , ItemFieldStruct* outResultItem  );
//²Å¤åÂà´«
static bool	RuneTransfer( ItemFieldStruct* Rune1 , ItemFieldStruct* Rune2 , ItemFieldStruct* outResultItem );
//²Å¤å¤Éµ¥
static bool	RefineRune( ItemFieldStruct* Rune , ItemFieldStruct* outResultItem );
//ª««~¿Ä¦X§I´«
static bool	ItemCombine( vector< ItemFieldStruct >& ItemList , ItemFieldStruct* outResultItem );

//////////////////////////////////////////////////////////////////////////
//Å]ªk²°·Ò¤Æ
bool	MagicBoxSmelt(  ItemFieldStruct* outResultItem );
//////////////////////////////////////////////////////////////////////////
static void	SelectAbility( vector<ItemFieldStruct*>& AbilityList , ItemFieldStruct* outResultItem );
//­pºâ¦³´X­ÓªÅ¦ì
int		EmptyPacketCount();
//////////////////////////////////////////////////////////////////////////
void	ResetLockAccountMoney( );

FixFightArgumentStruct&   FixArg();     //©T©w°Ñ¼Æªí

//¨ú±o§ð¨¾¼vÅTµ¥¯Å®t
int CalAddDotMagicLv( RoleDataEx* Target , GameObjDbStructEx* MagicBaseObjDB , int SpellTime , int OrgMagicLv );

//«OÀI³B²z
void	InsureProc();

//§R°£¤@­Óª««~
bool	DelOneItem( int ItemPos , ItemFieldStruct& Item , ActionTypeENUM ActionType );

void	SwapEQ( int posID );

int		JobCount( );

bool	OldUnPacket( ItemFieldStruct *SrvItem );
bool	NewUnPacket( ItemFieldStruct *SrvItem );
bool	UnPacket_DropList( ItemFieldStruct *SrvItem );

//­×¥¿ª««~¸ê®Æ
static void	FixItem( ItemFieldStruct *Item );

int		HPMPSPSum();

//¨ú±oÃdª«¸ê®Æ
PetStruct*	GetPetInfo( RoleDataEx* Pet );

//¨ú±o¨ì¦¹µ¥¯ÅªºTP
static int	GetLvTotalTP( int Lv );

static void	GetRareEffect( GameObjDbStructEx* OrgDB , int AddRare , float& Dmg , float& MDmg , float& Def , float& MDef );

//­pºâ¥i¥H¸ü¦h¤Ö¤H
int		CalCarryCount();

/*
//¼W¥[ª÷¿ú(©Ò¦³Ãþ«¬)
bool	AddMoneyBase( PriceTypeENUM Type , int Money );
//ÀË¬dª÷¿ú(©Ò¦³Ãþ«¬)
bool	CheckMoneyBase( PriceTypeENUM Type , int Money );
*/

void	PhantomEQChangeProc();

static int KeyItemObjToID( int objID );
static int IDtoKeyItemObj( int id );