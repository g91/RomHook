//------------------------------------------------------------------------------------------------------
//計算到某目標點的長度
float   Length( float X , float Y , float Z );
float   Length( RoleDataEx* Target );
float   Length( int TargetID );

float   Length3D( float X , float Y , float Z );
float   Length3D( RoleDataEx* Target );
float   Length3D( int TargetID );
//初始化角色計算數值
void	InitCal( );

//檢查角色資料是否有問題，如果有自動更正
void    InitCheckRoleData( );
bool	CheckAndInitItem( ItemFieldStruct& Field );

//初始換區資料
void	InitChangeZone();

//刪除超過生存期的物品
void    CheckItemLiveTime();

//設定物品裝備資訊
void    ResetItemInfo( );

//記算法術與裝備
//void    ReCalculateMagicAndEQ( );
void    ReCalculateBuff( );

void	ReCalculatePhantom();

//只記算基本能力
void	ReCalculateEQNoBuff();

//只有計算裝備能力
void	ReCalculateEqOnly();

//算不包含Buff的能力 , 算到基本
//void	ReCalculateBase();

//貝份定時檢查的資料,(用來比對資料不同時更新Client)
void    InitOnTimeCheck( );

//計匴所有角色數值 Att.Calculate
void	Calculate( );

//設定武器狀態
void	FixWeaponType();

//加上一個物品的屬性
bool	WearEQ( ItemFieldStruct* Field , int Pos );
//加上一個物件的屬性
bool	WearObject( GameObjDbStructEx* OrgDB , int Pos , float Power  = 1 , int AddRare = 0 );
bool	WearObject( int OrgDBID , int Pos = -1 , float Power = 1 , int AddRare = 0 );
bool	WearMagic( int OrgDBID , int MagicLv );
bool	WearSuit( int SuitID , int Count );
bool	WearBuff( int OrgDBID , int MagicLv );


//計算兩人的關係
float   CalRelation( RoleDataEx* Target );

//基本仇恨值
int		BaseHate( RoleData* Target );

//他人影響 加HP 或加MP
void	AddHP( RoleDataEx* Target ,  float DHP , float HateRate = 1 );
void	AddMP( RoleDataEx* Target ,  float DMP , float HateRate = 1 );
void	AddSP( RoleDataEx* Target ,  float DSP , float HateRate = 1 );
void	AddSP_Sub( RoleDataEx* Target ,  float DSP , float HateRate = 1 );
void	AddStomachPoint( int DPoint );

//增加某一個人的仇恨值( 此怪物被 npc 或 pc 打)
//並做攻擊目標的轉換
bool	CalHate( RoleDataEx* Att , int Damage , int HatePoint );
bool	CalTempHate( RoleDataEx* Att , int Damage );
//重新計算仇恨列表
bool	ReCalhateList( );

void    OnTimeCalHate( );

void    ClearHate();

bool	ClearHate_One( int PlayerID );

//檢查攻擊模式
ATTACK_DMGTYPE_ENUM CheckAtkDmgType( RoleDataEx* Target , AttackHandTypeENUM Type );

bool	CalAttackTypeInfo( RoleDataEx* Target  , AttackHandTypeENUM Type , int& OutHitRate , int& OutDodge , int& OutMissRate );

//增減 Exp
void    Addexp( int Exp );

//增加技能經驗值
void	AddSkillExp( SkillValueTypeENUM Type , int Exp );

//ExpRate 為百分比
int		AddPlotExp	( int PlotLv , int ExpRate );
void	AddPlotTP	( int iTP );

//ExpRate 為百分比
void	AddPlotMoney( int PlotLv , int MoneyRate );

void	AddTP		( int iTP );

//取得法術攻擊數值
float   GetValue( MagicAttackCalENUM Type );

//加輔助法術
BuffBaseStruct*    AssistMagic( RoleDataEx* Target , GameObjDbStructEx* OrgDB , int MagicLv , bool IsPK , int EffectTime  );
BuffBaseStruct*    AssistMagic( RoleDataEx* Target , int MagicID , int MagicLv , bool IsPK , int EffectTime );
int	   CliAddBuf( int MagicOwnerID , int MagicID , int MagicLv , bool IsPK , int EffectTime );

//清除所有Buff
void    ClearAllBuff();

//清除Buff
bool    ClearBuff( int MagicID , int BuffOwnerID );
bool    ClearBuff_NoEvent( int MagicID , int BuffOwnerID );
bool    ClearBuffByPos( int Pos );
void	ClearBuffByEvent( );
void	ClearBuffByEvent( MagicClearTimeStruct ClearEvent );


//處理Buf的時效
void    BuffProc( );

//當被打到時的buff 處理
void	SpecialAttackBuffProc( RoleDataEx* Target , OnAttackTypeENUM Type , ATTACK_DMGTYPE_ENUM  DmgType , int addHP , int magicColID , int magicBaseID );
void	SpecialAttackBuffProc_SelfSpell( RoleDataEx* Target );

//當打別人時 Buff 處理(自己與目標的處理)
void	OnAttackBuffProc( RoleDataEx* Target );

//當死亡時Buff的處理
void	OnDeadBuffProc( RoleDataEx* Killer );

//當打別人時 Buff 處理(自己與目標的處理)
void	OnMagicAttackBuffProc( RoleDataEx* Target );


//攻擊距離
int	    MainAttackRange( RoleData* Target );
//攻擊距離(
int	    SecAttackRange( RoleData* Target );

//取得對某魔法進行抗性運算結果( + 加血 - 扣血 )
float	CalResistDMG( MagicResistENUM  MagicType , float Damage );

// 計算生活技能升級上限
void	CalLifeSkillMaxValue();

//計算屬性與等級的關係
//GameObjectWearEqStruct*	CheckAbilityLevel( GameObjDbStructEx* OrgDB , int Level );
GameObjDbStructEx* GetRefinAblility( GameObjDbStructEx* ItemDB , int Level );

//取得法術等級
int		GetMagicLv( int MagicPos );
//------------------------------------------------------------------------------------------------------
//可流通的帳號幣
int OkAccountMoney();