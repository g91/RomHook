//------------------------------------------------------------------------------------------------------
//�p���Y�ؼ��I������
float   Length( float X , float Y , float Z );
float   Length( RoleDataEx* Target );
float   Length( int TargetID );

float   Length3D( float X , float Y , float Z );
float   Length3D( RoleDataEx* Target );
float   Length3D( int TargetID );
//��l�ƨ���p��ƭ�
void	InitCal( );

//�ˬd�����ƬO�_�����D�A�p�G���۰ʧ�
void    InitCheckRoleData( );
bool	CheckAndInitItem( ItemFieldStruct& Field );

//��l���ϸ��
void	InitChangeZone();

//�R���W�L�ͦs�������~
void    CheckItemLiveTime();

//�]�w���~�˳Ƹ�T
void    ResetItemInfo( );

//�O��k�N�P�˳�
//void    ReCalculateMagicAndEQ( );
void    ReCalculateBuff( );

void	ReCalculatePhantom();

//�u�O��򥻯�O
void	ReCalculateEQNoBuff();

//�u���p��˳Ư�O
void	ReCalculateEqOnly();

//�⤣�]�tBuff����O , ����
//void	ReCalculateBase();

//�����w���ˬd�����,(�ΨӤ���Ƥ��P�ɧ�sClient)
void    InitOnTimeCheck( );

//�p���Ҧ�����ƭ� Att.Calculate
void	Calculate( );

//�]�w�Z�����A
void	FixWeaponType();

//�[�W�@�Ӫ��~���ݩ�
bool	WearEQ( ItemFieldStruct* Field , int Pos );
//�[�W�@�Ӫ����ݩ�
bool	WearObject( GameObjDbStructEx* OrgDB , int Pos , float Power  = 1 , int AddRare = 0 );
bool	WearObject( int OrgDBID , int Pos = -1 , float Power = 1 , int AddRare = 0 );
bool	WearMagic( int OrgDBID , int MagicLv );
bool	WearSuit( int SuitID , int Count );
bool	WearBuff( int OrgDBID , int MagicLv );


//�p���H�����Y
float   CalRelation( RoleDataEx* Target );

//�򥻤����
int		BaseHate( RoleData* Target );

//�L�H�v�T �[HP �Υ[MP
void	AddHP( RoleDataEx* Target ,  float DHP , float HateRate = 1 );
void	AddMP( RoleDataEx* Target ,  float DMP , float HateRate = 1 );
void	AddSP( RoleDataEx* Target ,  float DSP , float HateRate = 1 );
void	AddSP_Sub( RoleDataEx* Target ,  float DSP , float HateRate = 1 );
void	AddStomachPoint( int DPoint );

//�W�[�Y�@�ӤH�������( ���Ǫ��Q npc �� pc ��)
//�ð������ؼЪ��ഫ
bool	CalHate( RoleDataEx* Att , int Damage , int HatePoint );
bool	CalTempHate( RoleDataEx* Att , int Damage );
//���s�p�⤳��C��
bool	ReCalhateList( );

void    OnTimeCalHate( );

void    ClearHate();

bool	ClearHate_One( int PlayerID );

//�ˬd�����Ҧ�
ATTACK_DMGTYPE_ENUM CheckAtkDmgType( RoleDataEx* Target , AttackHandTypeENUM Type );

bool	CalAttackTypeInfo( RoleDataEx* Target  , AttackHandTypeENUM Type , int& OutHitRate , int& OutDodge , int& OutMissRate );

//�W�� Exp
void    Addexp( int Exp );

//�W�[�ޯ�g���
void	AddSkillExp( SkillValueTypeENUM Type , int Exp );

//ExpRate ���ʤ���
int		AddPlotExp	( int PlotLv , int ExpRate );
void	AddPlotTP	( int iTP );

//ExpRate ���ʤ���
void	AddPlotMoney( int PlotLv , int MoneyRate );

void	AddTP		( int iTP );

//���o�k�N�����ƭ�
float   GetValue( MagicAttackCalENUM Type );

//�[���U�k�N
BuffBaseStruct*    AssistMagic( RoleDataEx* Target , GameObjDbStructEx* OrgDB , int MagicLv , bool IsPK , int EffectTime  );
BuffBaseStruct*    AssistMagic( RoleDataEx* Target , int MagicID , int MagicLv , bool IsPK , int EffectTime );
int	   CliAddBuf( int MagicOwnerID , int MagicID , int MagicLv , bool IsPK , int EffectTime );

//�M���Ҧ�Buff
void    ClearAllBuff();

//�M��Buff
bool    ClearBuff( int MagicID , int BuffOwnerID );
bool    ClearBuff_NoEvent( int MagicID , int BuffOwnerID );
bool    ClearBuffByPos( int Pos );
void	ClearBuffByEvent( );
void	ClearBuffByEvent( MagicClearTimeStruct ClearEvent );


//�B�zBuf���ɮ�
void    BuffProc( );

//��Q����ɪ�buff �B�z
void	SpecialAttackBuffProc( RoleDataEx* Target , OnAttackTypeENUM Type , ATTACK_DMGTYPE_ENUM  DmgType , int addHP , int magicColID , int magicBaseID );
void	SpecialAttackBuffProc_SelfSpell( RoleDataEx* Target );

//���O�H�� Buff �B�z(�ۤv�P�ؼЪ��B�z)
void	OnAttackBuffProc( RoleDataEx* Target );

//���`��Buff���B�z
void	OnDeadBuffProc( RoleDataEx* Killer );

//���O�H�� Buff �B�z(�ۤv�P�ؼЪ��B�z)
void	OnMagicAttackBuffProc( RoleDataEx* Target );


//�����Z��
int	    MainAttackRange( RoleData* Target );
//�����Z��(
int	    SecAttackRange( RoleData* Target );

//���o��Y�]�k�i��ܩʹB�⵲�G( + �[�� - ���� )
float	CalResistDMG( MagicResistENUM  MagicType , float Damage );

// �p��ͬ��ޯ�ɯŤW��
void	CalLifeSkillMaxValue();

//�p���ݩʻP���Ū����Y
//GameObjectWearEqStruct*	CheckAbilityLevel( GameObjDbStructEx* OrgDB , int Level );
GameObjDbStructEx* GetRefinAblility( GameObjDbStructEx* ItemDB , int Level );

//���o�k�N����
int		GetMagicLv( int MagicPos );
//------------------------------------------------------------------------------------------------------
//�i�y�q���b����
int OkAccountMoney();