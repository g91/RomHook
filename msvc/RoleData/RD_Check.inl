
//------------------------------------------------------------------------------------
//檢查某劇情是否為無效資料
bool CheckAutoPlot();
bool CheckRangePlot();
bool CheckTouchPlot();	
bool CheckDeadPlot();
bool CheckSayPlot();
bool CheckGiveItemPlot();

bool CheckClientAutoPlot();
//------------------------------------------------------------------------------------

bool    IsPlayer();
bool    IsNPC();
bool	IsQuestNPC();
bool    IsItem();
bool    IsFlag();
bool	IsMirror();
bool	IsMine();
bool    IsBodyEmpty( int Pos );
bool    IsBankEmpty( int Pos );

bool    IsAttack();
bool	IsMove();					//移動
bool	IsSit();
//bool	IsSpell();					//施法
bool	IsDead();					//死亡
bool	IsFollow();					//跟隨
bool	IsWalk();					//跑步
bool    IsTrade();
bool    IsAttackMode( );
bool    IsSpell();
bool    IsUnderAttack();
bool	IsDisableClick();
bool	IsDisableQuest();

bool	IsWagon();


void    IsAttack( bool Value ); 
void	IsSit( bool Value );
//void	IsMove( bool Value  );		//移動
//void	IsSpell( bool Value  );		//施法
void	IsDead( bool Value );		//死亡
void	IsFollow( bool Value );		//跟隨
void	IsWalk( bool Value );		//跑步
void    IsTrade( bool Value );
void    IsAttackMode( bool Value );


bool    IsPet( RoleDataEx* PetOwner );
bool    IsGuard( RoleDataEx* GuardOwner );

//是否資料可以寫入(如果換區中 或 要刪除中 或是 Mirror物件 都不可寫入)
bool	IsRoleDataWriteable( );
//************************************************************************************
//攻擊相關資訊
//************************************************************************************
//檢查是否為朋友
bool	CheckFriend( RoleDataEx* Target );

//檢查是否敵對
bool	CheckEnemy( RoleDataEx*	Target );

//檢查是否可幫助
bool	CheckCampHelp( RoleDataEx*	Target );

//檢查此物件是否致能
bool	CheckEnabled( );

//檢查是否要收尋敵人
bool	CheckSearchEnemy( );			

//檢查是否可以反擊
bool	CheckStrikback( );

//檢查是否可以攻擊
bool	CheckAttackable( RoleDataEx* Target );			
bool	CheckAttackable_IgnoreDead( RoleDataEx* Target );			



//檢查是否可以物理攻擊
bool	CheckPhyAttack( RoleDataEx* Target );
//檢查是否可以法術攻擊
bool	CheckMagicAttack( RoleDataEx* Target );


//檢查兩物件距離是否可以攻擊
bool	CheckMainAttackRange( RoleDataEx* Target );
bool	CheckSecAttackRange( RoleDataEx* Target );

//檢查是否要計算仇恨值
bool	CheckCalHate( );

//檢查魔法是否命中
bool    CheckMagicHit( RoleDataEx* Target , GameObjDbStructEx* OrgDB );

//檢查是否Miss 
//ATTACK_DMGTYPE_ENUM	CheckMissType( RoleDataEx* , AttackHandTypeENUM Type );

//檢查某物件是否在視野內
//傳入目標物 可視角度 可視距離
//bool	CheckInSight( RoleDataEx* Target , float Angle , float Len );
bool	CheckInSight( RoleDataEx* Target , float Angle , GameObjDbStructEx* OwnerOrgDB );
bool	CheckInSight( RoleDataEx* Target , float Angle , float Len );

//檢查是否可以要請人入隊伍
bool	CheckInvitable( RoleDataEx* Target );

//簡查是否要停止攻擊
bool	CheckStopAttack();

//檢查是否可以移動
bool	CheckMoveable	( );

//檢查是否可以施法
GameMessageEventENUM	CheckCanSpell( RoleDataEx* Target , float TargetX , float TargetY , float TargetZ , GameObjDbStructEx* Magic );
//第一次施法檢查
GameMessageEventENUM	CheckCanBeginSpell( RoleDataEx* Target , float TargetX , float TargetY , float TargetZ , GameObjDbStructEx* Magic , int MagicLv );

//與目標關係檢查
bool	CheckRelation( RoleDataEx* Target , GameObjectRelationENUM Relation , bool IgnoreDead = false );

//簡查施法必要消費 與 cooldown
bool	CheckSpellMagicCost( RoleDataEx* Target , GameObjDbStructEx* Magic , int MagicLv );
bool	CheckSpellMagicCostBase( RoleDataEx* Target , GameObjDbStructEx* Magic , int MagicLv , MagicSpellCostTypeENUM CostType , int CostValue );

//檢查法術是否對目標有效用效用( 用來處理 NPC AI用)
bool	CheckEffect_SpellMagic( RoleDataEx* Target , GameObjDbStructEx* Magic);

//檢查是否魔法被中斷
bool	CheckMagicInterrupt( );

//檢查被攻擊是否施法中斷
bool	CheckMagicInterrupt_OnAttack( );

//檢查是否可以對目標失法
bool	CheckUseItem(  int TargetID , float TargetX , float TargetY , float TargetZ  , int Pos , int Type , ItemFieldStruct&  Item );

//檢查是否要逃跑
bool    CheckEscape( RoleDataEx* Target );

//檢查時間( G_SysTime  >= Time )表示時間到了
static bool	CheckTime( int Time );

//檢查是否已經有某輔助法術
bool	CheckHasAssistMagic( GameObjDbStructEx* MagicBaseDB );

//檢查是否可裝此頭銜
bool	CheckWearTitle( int TitleID );

bool	CheckGetJobTitle( int TitleID );

//pk檢查  回傳 0 未處理 1 成功 2 失敗
int		CheckPKType( RoleDataEx* Target );

//檢查此寶箱是否能刪除
bool	CheckTreasureDelete( );

//檢查是否有可以底傷的法術盾
bool	CheckDisplayDotAttack( GameObjDbStruct* AtkMagic );

bool	CheckBuff( int buffID );


/*
//檢查AC是否有開啟 , 如果有問題設定成關閉
bool	CheckOpenMenu( EM_RoleOpenMenuType_AC );
//檢查Mail是否有開啟 , 如果有問題設定成關閉
bool	CheckOpenMenu( EM_RoleOpenMenuType_Mail );
//檢查Shop是否有開啟 , 如果有問題設定成關閉
bool	CheckOpenMenu( EM_RoleOpenMenuType_Shop );
//檢查Bank是否有開啟 , 如果有問題設定成關閉
bool	CheckOpenMenu( EM_RoleOpenMenuType_Bank );
//檢查ChangeJob是否有開啟 , 如果有問題設定成關閉
bool	CheckOpenMenu( EM_RoleOpenMenuType_ChangeJob );
//檢查Billboard是否有開啟 , 如果有問題設定成關閉
bool	CheckOpenMenu( EM_RoleOpenMenuType_Billboard );
*/
//檢查是否有獨佔介面
bool	CheckOpenMenu( RoleOpenMenuTypeENUM OpenType );
//清除開起介面資料
void	ClsOpenMenu( );

//檢查是否有開起 AC Mail Shop Bank中任何一個
bool	CheckOpenSomething();

//檢查法術集合內的輔助法術是否
bool	CheckMagicBuffExist( int MagicColID );

//檢查是否有某卡片
bool	CheckCardID( int OrgObjID );

//檢查並清除複製品
void 	CheckAndClearCopyItem( );

//檢查是否可以加符石
static CheckAddRuneResultENUM		CheckAddRune	( ItemFieldStruct* UseItem , ItemFieldStruct* TargetItem );
//檢查是否可以衝等
static CheckEqRefineResultENUM		CheckEqRefine	( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//檢查是否可以修裝
static ChecFixEqResultENUM			CheckFixEq		( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem, unsigned int playerMoney=0xffffffff );
//檢查是否可以拆解物品
static CheckDissolutionResultENUM	CheckDissolution( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//檢查是否可以染色
static CheckColoringResultENUM		CheckColoring	( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//檢查是否可以清除Soulbound
static CheckClsSoulBoundResultENUM	CheckClsSoulBound( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//檢查是否可以清除禁止交易
static CheckClsSoulBoundResultENUM	CheckClsTrade( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );

//檢查是否可以打洞
static CheckDigHoleResultENUM		CheckDigHole( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//檢查是否可以清除所有符文
static CheckClsRuneResultENUM		CheckClsRune( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//檢查是否可以鎖定物品
static CheckItemLockResultENUM		CheckItemLock( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//檢查是否可以解除鎖定物品
static CheckItemUnLockResultENUM	CheckItemUnLock( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//檢查是否可以裝備保護
static CheckEQProtectResultENUM		CheckEQProtect( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//檢查是否可以修裝備上限
static CheckEQLimitMaxResultENUM	CheckEQLimitMax( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//檢查是否可以忽略使用上限
static CheckIgnoreLimitLvMaxResultENUM	CheckIgnoreLimitLv( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//檢查是否可以做PK裝備保護
static CheckPkEqProtectResultENUM	CheckPkEqProtect( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//檢查是否可以清除PK裝備保護
static CheckPkEqProtectcClearResultENUM	CheckPkEqProtectClear( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//建查是否可以清除裝備上的屬性
static CheckClsEqAbilityResultENUM	CheckClsEqAbility( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );


//檢查是否可以移動此物品( 如果是 種植物 並且還沒清空 回傳 false  其它 true  )
static bool CheckMovePlantItem( ItemFieldStruct& houseItem );