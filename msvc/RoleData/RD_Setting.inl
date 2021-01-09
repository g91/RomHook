void    ChangeZoneInit( );

//�s���ͦs��
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

int     ZoneID( );          //�ϰ�id(??�L���_�n�p�߬ݦ��L���D)
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

//���X�I�H�һݸ��
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
//�ثe�������ؼ�
int     AttackTargetID();

//�]�w�ؼ�
void	TargetID( int ID );

int     TargetID();
//���󪺼˪OID
int     OrgObjID();
//-------------------------------------------------------------------------------------------
//�]�w���H�Y�H
bool    SetFollow( RoleDataEx* Target );
//�]�w�������
bool    SetAtkFolOff( );
//�]�w�����Y�H
bool	SetAttack( RoleDataEx* Target );
bool	SetAttack( int TargetID );

//-------------------------------------------------------------------------------------------
//�]�w�ͦs���`
void    Dead( bool Value );
//-------------------------------------------------------------------------------------------

//���o�{�b¾�~���g��� Exp
int		GetExp( Voc_ENUM Voc );

//���o�{�b¾�~�ɯŻݭn�� Exp
int     GetLVExp( Voc_ENUM Voc );



float	GetBaseDLvExp( int DLV );

float	GetBaseLifeSkillDLvExp( int DLV );

float	GetBaseDLvPlantExp( int DLv );

//�p��C�����@����o���ޯ���m��
void	AddSkillValue( int TargetLV , SkillValueTypeENUM SkillID , float Exp );
void	AddWeaponSkillValue( int TargetLV , GameObjectWeaponENUM SkillID , float Exp );

//���o�Z�����ޯ��
float	GetWeaponSkillValue( GameObjectWeaponENUM SkillID );
//���o�ޯ��
float	GetSkillValue( SkillValueTypeENUM SkillID );

//��l��NPC
void    InitNPCData( );


//�]�wColdown
bool	SetMagicColdown( MagicColdownClassENUM	Class , int Type , int Time , int AllMagicTime );

//�ˬdColdwon
bool    CheckMagicColdown( MagicColdownClassENUM Class , int Type );

//�w�ɳB�zColdown
void	ColdownProc( );
void	RefineColdownProc( );


//�]�w���⪫��Ҧ�
void    SetMode( int Mode );

//�]�w���Ȫ���O�_��Q�@��
void	SetDisableClick( bool bState ) { TempData.Attr.Action.DisableClick = bState; }
void	SetDisableQuest( bool bState ) { TempData.Attr.Action.DisableQuest = bState; }

//////////////////////////////////////////////////////////////////////////
bool	SetPetSkill( );
//-------------------------------------------------------------------------------------------
//int		ZoneKey();		//�i�J�ϰ�]�w��Key
//void	SetZoneKey();
//-------------------------------------------------------------------------------------------