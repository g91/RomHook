
//定時處理事件
void OnTimeProc( bool IsSpecialCalculate = false );

// 每 100 毫秒更新
void OnTimeProc_HundredMS();

//0.5每秒處理一次
void OnTimeProc_NPC( );
//0.5每秒處理一次
void OnTimeProc_Player( );

void OnCreate( );
void OnDestroy( );
void OnAddToPartition( );
void OnDelFromPartition( );

void OnDead( RoleDataEx* Dead );

//當打到別人( Type = 0 MainHand , 1 OffHand 2 Magic or Skill )
void OnAttack( RoleDataEx* Target , OnAttackTypeENUM Type , ATTACK_DMGTYPE_ENUM DmgType , int addHP , int magicColID , int magicID );
