
//�w�ɳB�z�ƥ�
void OnTimeProc( bool IsSpecialCalculate = false );

// �C 100 �@���s
void OnTimeProc_HundredMS();

//0.5�C��B�z�@��
void OnTimeProc_NPC( );
//0.5�C��B�z�@��
void OnTimeProc_Player( );

void OnCreate( );
void OnDestroy( );
void OnAddToPartition( );
void OnDelFromPartition( );

void OnDead( RoleDataEx* Dead );

//����O�H( Type = 0 MainHand , 1 OffHand 2 Magic or Skill )
void OnAttack( RoleDataEx* Target , OnAttackTypeENUM Type , ATTACK_DMGTYPE_ENUM DmgType , int addHP , int magicColID , int magicID );
