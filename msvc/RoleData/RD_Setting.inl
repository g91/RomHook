void    ChangeZoneInit( );

//存取生存期
void    LiveTime( int , const char* cszReason );
int     LiveTime( );

void    WorldGUID( int );
int     WorldGUID( );

void    OwnerGUID( int );
int     OwnerGUID( );
void    OwnerDBID( int );
int     OwnerDBID( );
void    GUID( int );
int     GUID( );
int		GuildID( );

int     ItemID( );

void    SockID( int );
int     SockID( );

void    ProxyID( int );
int     ProxyID(  );

int     ZoneID( );          //區域id(??無接縫要小心看有無問題)
void    ZoneID( int );

void    RoomID( int );
int     RoomID( );

//int     GuildID( );
//void    GuildID( int Value );

int		PartyID();

RolePosStruct*  Pos();
void    Pos( float X , float Y , float Z , float Dir );
float   X();
float   Y();
float   Z();
float   Dir();

void    Account_ID( char* );
const char*   Account_ID( );

int     DBID();

//取出險象所需資料
void    PlayerGraph( PlayerGraphStruct& );

float   MoveSpeed( );

//float   ModelSize( );

void    MoveTarget( float X , float Y , float Z , float Dir );

PathProcStruct* Move( );

void    SecXZ( int X , int Z );
int     SecX( );
int     SecZ( );
int     SecRoomID( );
void    SecRoomID( int );


int     Mode( );
int     MaxHP( );
int     MaxMP( );
int     MaxSP( );
float   HP( );
float   MP( );
float   SP( );

int     Level( );	
int     Level_Sub( );

const char*   RoleName( );
void    RoleName( char* );

void    SetValue(  RoleValueName_ENUM Type , double Value , RoleDataEx* WriteRole = NULL );
void    SetValue(  RoleValueName_ENUM Type , int Value , RoleDataEx* WriteRole = NULL );
void    SetValue(  RoleValueName_ENUM Type , float Value , RoleDataEx* WriteRole = NULL );
//void    SetValue(  RoleValueName_ENUM Type , int Value , RoleDataEx* WriteRole = NULL );

//void    AddValue(  RoleValueName_ENUM Type , int	 Value , RoleDataEx* WriteRole = NULL );
void    AddValue(  RoleValueName_ENUM Type , int  Value , RoleDataEx* WriteRole = NULL );
void    AddValue(  RoleValueName_ENUM Type , float  Value , RoleDataEx* WriteRole = NULL );
void    AddValue(  RoleValueName_ENUM Type , double  Value , RoleDataEx* WriteRole = NULL );


float   GetValue_Float(  RoleValueName_ENUM Type );
int	    GetValue_Int(  RoleValueName_ENUM Type );
double	GetValue(  RoleValueName_ENUM Type );


void    SetInitNPC( GameObjDbStructEx* );
void    SetInitItem( GameObjDbStructEx* );

int     MirrorCount( );

bool    IsDestroy();
void    Destroy( char* Acount_ID );

BaseAbilityStruct*		Ability();
//目前攻擊的目標
int     AttackTargetID();

//設定目標
void	TargetID( int ID );

int     TargetID();
//物件的樣板ID
int     OrgObjID();
//-------------------------------------------------------------------------------------------
//設定跟隨某人
bool    SetFollow( RoleDataEx* Target );
//設定停止攻擊
bool    SetAtkFolOff( );
//設定攻擊某人
bool	SetAttack( RoleDataEx* Target );
bool	SetAttack( int TargetID );

//-------------------------------------------------------------------------------------------
//設定生存死亡
void    Dead( bool Value );
//-------------------------------------------------------------------------------------------

//取得現在職業的經驗值 Exp
int		GetExp( Voc_ENUM Voc );

//取得現在職業升級需要的 Exp
int     GetLVExp( Voc_ENUM Voc );



float	GetBaseDLvExp( int DLV );

float	GetBaseLifeSkillDLvExp( int DLV );

float	GetBaseDLvPlantExp( int DLv );

//計算每打擊一次獲得的技能熟練度
void	AddSkillValue( int TargetLV , SkillValueTypeENUM SkillID , float Exp );
void	AddWeaponSkillValue( int TargetLV , GameObjectWeaponENUM SkillID , float Exp );

//取得武器的技能值
float	GetWeaponSkillValue( GameObjectWeaponENUM SkillID );
//取得技能值
float	GetSkillValue( SkillValueTypeENUM SkillID );

//初始化NPC
void    InitNPCData( );


//設定Coldown
bool	SetMagicColdown( MagicColdownClassENUM	Class , int Type , int Time , int AllMagicTime );

//檢查Coldwon
bool    CheckMagicColdown( MagicColdownClassENUM Class , int Type );

//定時處理Coldown
void	ColdownProc( );
void	RefineColdownProc( );


//設定角色物件模式
void    SetMode( int Mode );

//設定任務物件是否能被作用
void	SetDisableClick( bool bState ) { TempData.Attr.Action.DisableClick = bState; }
void	SetDisableQuest( bool bState ) { TempData.Attr.Action.DisableQuest = bState; }

//////////////////////////////////////////////////////////////////////////
bool	SetPetSkill( );
//-------------------------------------------------------------------------------------------
//int		ZoneKey();		//進入區域設定的Key
//void	SetZoneKey();
//-------------------------------------------------------------------------------------------