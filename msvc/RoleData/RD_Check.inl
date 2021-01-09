
//------------------------------------------------------------------------------------
//�ˬd�Y�@���O�_���L�ĸ��
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
bool	IsMove();					//����
bool	IsSit();
//bool	IsSpell();					//�I�k
bool	IsDead();					//���`
bool	IsFollow();					//���H
bool	IsWalk();					//�]�B
bool    IsTrade();
bool    IsAttackMode( );
bool    IsSpell();
bool    IsUnderAttack();
bool	IsDisableClick();
bool	IsDisableQuest();

bool	IsWagon();


void    IsAttack( bool Value ); 
void	IsSit( bool Value );
//void	IsMove( bool Value  );		//����
//void	IsSpell( bool Value  );		//�I�k
void	IsDead( bool Value );		//���`
void	IsFollow( bool Value );		//���H
void	IsWalk( bool Value );		//�]�B
void    IsTrade( bool Value );
void    IsAttackMode( bool Value );


bool    IsPet( RoleDataEx* PetOwner );
bool    IsGuard( RoleDataEx* GuardOwner );

//�O�_��ƥi�H�g�J(�p�G���Ϥ� �� �n�R���� �άO Mirror���� �����i�g�J)
bool	IsRoleDataWriteable( );
//************************************************************************************
//����������T
//************************************************************************************
//�ˬd�O�_���B��
bool	CheckFriend( RoleDataEx* Target );

//�ˬd�O�_�Ĺ�
bool	CheckEnemy( RoleDataEx*	Target );

//�ˬd�O�_�i���U
bool	CheckCampHelp( RoleDataEx*	Target );

//�ˬd������O�_�P��
bool	CheckEnabled( );

//�ˬd�O�_�n���M�ĤH
bool	CheckSearchEnemy( );			

//�ˬd�O�_�i�H����
bool	CheckStrikback( );

//�ˬd�O�_�i�H����
bool	CheckAttackable( RoleDataEx* Target );			
bool	CheckAttackable_IgnoreDead( RoleDataEx* Target );			



//�ˬd�O�_�i�H���z����
bool	CheckPhyAttack( RoleDataEx* Target );
//�ˬd�O�_�i�H�k�N����
bool	CheckMagicAttack( RoleDataEx* Target );


//�ˬd�⪫��Z���O�_�i�H����
bool	CheckMainAttackRange( RoleDataEx* Target );
bool	CheckSecAttackRange( RoleDataEx* Target );

//�ˬd�O�_�n�p�⤳���
bool	CheckCalHate( );

//�ˬd�]�k�O�_�R��
bool    CheckMagicHit( RoleDataEx* Target , GameObjDbStructEx* OrgDB );

//�ˬd�O�_Miss 
//ATTACK_DMGTYPE_ENUM	CheckMissType( RoleDataEx* , AttackHandTypeENUM Type );

//�ˬd�Y����O�_�b������
//�ǤJ�ؼЪ� �i������ �i���Z��
//bool	CheckInSight( RoleDataEx* Target , float Angle , float Len );
bool	CheckInSight( RoleDataEx* Target , float Angle , GameObjDbStructEx* OwnerOrgDB );
bool	CheckInSight( RoleDataEx* Target , float Angle , float Len );

//�ˬd�O�_�i�H�n�ФH�J����
bool	CheckInvitable( RoleDataEx* Target );

//²�d�O�_�n�������
bool	CheckStopAttack();

//�ˬd�O�_�i�H����
bool	CheckMoveable	( );

//�ˬd�O�_�i�H�I�k
GameMessageEventENUM	CheckCanSpell( RoleDataEx* Target , float TargetX , float TargetY , float TargetZ , GameObjDbStructEx* Magic );
//�Ĥ@���I�k�ˬd
GameMessageEventENUM	CheckCanBeginSpell( RoleDataEx* Target , float TargetX , float TargetY , float TargetZ , GameObjDbStructEx* Magic , int MagicLv );

//�P�ؼ����Y�ˬd
bool	CheckRelation( RoleDataEx* Target , GameObjectRelationENUM Relation , bool IgnoreDead = false );

//²�d�I�k���n���O �P cooldown
bool	CheckSpellMagicCost( RoleDataEx* Target , GameObjDbStructEx* Magic , int MagicLv );
bool	CheckSpellMagicCostBase( RoleDataEx* Target , GameObjDbStructEx* Magic , int MagicLv , MagicSpellCostTypeENUM CostType , int CostValue );

//�ˬd�k�N�O�_��ؼЦ��ĥήĥ�( �ΨӳB�z NPC AI��)
bool	CheckEffect_SpellMagic( RoleDataEx* Target , GameObjDbStructEx* Magic);

//�ˬd�O�_�]�k�Q���_
bool	CheckMagicInterrupt( );

//�ˬd�Q�����O�_�I�k���_
bool	CheckMagicInterrupt_OnAttack( );

//�ˬd�O�_�i�H��ؼХ��k
bool	CheckUseItem(  int TargetID , float TargetX , float TargetY , float TargetZ  , int Pos , int Type , ItemFieldStruct&  Item );

//�ˬd�O�_�n�k�]
bool    CheckEscape( RoleDataEx* Target );

//�ˬd�ɶ�( G_SysTime  >= Time )��ܮɶ���F
static bool	CheckTime( int Time );

//�ˬd�O�_�w�g���Y���U�k�N
bool	CheckHasAssistMagic( GameObjDbStructEx* MagicBaseDB );

//�ˬd�O�_�i�˦��Y��
bool	CheckWearTitle( int TitleID );

bool	CheckGetJobTitle( int TitleID );

//pk�ˬd  �^�� 0 ���B�z 1 ���\ 2 ����
int		CheckPKType( RoleDataEx* Target );

//�ˬd���_�c�O�_��R��
bool	CheckTreasureDelete( );

//�ˬd�O�_���i�H���˪��k�N��
bool	CheckDisplayDotAttack( GameObjDbStruct* AtkMagic );

bool	CheckBuff( int buffID );


/*
//�ˬdAC�O�_���}�� , �p�G�����D�]�w������
bool	CheckOpenMenu( EM_RoleOpenMenuType_AC );
//�ˬdMail�O�_���}�� , �p�G�����D�]�w������
bool	CheckOpenMenu( EM_RoleOpenMenuType_Mail );
//�ˬdShop�O�_���}�� , �p�G�����D�]�w������
bool	CheckOpenMenu( EM_RoleOpenMenuType_Shop );
//�ˬdBank�O�_���}�� , �p�G�����D�]�w������
bool	CheckOpenMenu( EM_RoleOpenMenuType_Bank );
//�ˬdChangeJob�O�_���}�� , �p�G�����D�]�w������
bool	CheckOpenMenu( EM_RoleOpenMenuType_ChangeJob );
//�ˬdBillboard�O�_���}�� , �p�G�����D�]�w������
bool	CheckOpenMenu( EM_RoleOpenMenuType_Billboard );
*/
//�ˬd�O�_���W������
bool	CheckOpenMenu( RoleOpenMenuTypeENUM OpenType );
//�M���}�_�������
void	ClsOpenMenu( );

//�ˬd�O�_���}�_ AC Mail Shop Bank������@��
bool	CheckOpenSomething();

//�ˬd�k�N���X�������U�k�N�O�_
bool	CheckMagicBuffExist( int MagicColID );

//�ˬd�O�_���Y�d��
bool	CheckCardID( int OrgObjID );

//�ˬd�òM���ƻs�~
void 	CheckAndClearCopyItem( );

//�ˬd�O�_�i�H�[�ť�
static CheckAddRuneResultENUM		CheckAddRune	( ItemFieldStruct* UseItem , ItemFieldStruct* TargetItem );
//�ˬd�O�_�i�H�ĵ�
static CheckEqRefineResultENUM		CheckEqRefine	( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//�ˬd�O�_�i�H�׸�
static ChecFixEqResultENUM			CheckFixEq		( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem, unsigned int playerMoney=0xffffffff );
//�ˬd�O�_�i�H��Ѫ��~
static CheckDissolutionResultENUM	CheckDissolution( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//�ˬd�O�_�i�H�V��
static CheckColoringResultENUM		CheckColoring	( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//�ˬd�O�_�i�H�M��Soulbound
static CheckClsSoulBoundResultENUM	CheckClsSoulBound( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//�ˬd�O�_�i�H�M���T����
static CheckClsSoulBoundResultENUM	CheckClsTrade( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );

//�ˬd�O�_�i�H���}
static CheckDigHoleResultENUM		CheckDigHole( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//�ˬd�O�_�i�H�M���Ҧ��Ť�
static CheckClsRuneResultENUM		CheckClsRune( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//�ˬd�O�_�i�H��w���~
static CheckItemLockResultENUM		CheckItemLock( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//�ˬd�O�_�i�H�Ѱ���w���~
static CheckItemUnLockResultENUM	CheckItemUnLock( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//�ˬd�O�_�i�H�˳ƫO�@
static CheckEQProtectResultENUM		CheckEQProtect( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//�ˬd�O�_�i�H�׸˳ƤW��
static CheckEQLimitMaxResultENUM	CheckEQLimitMax( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//�ˬd�O�_�i�H�����ϥΤW��
static CheckIgnoreLimitLvMaxResultENUM	CheckIgnoreLimitLv( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//�ˬd�O�_�i�H��PK�˳ƫO�@
static CheckPkEqProtectResultENUM	CheckPkEqProtect( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//�ˬd�O�_�i�H�M��PK�˳ƫO�@
static CheckPkEqProtectcClearResultENUM	CheckPkEqProtectClear( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );
//�جd�O�_�i�H�M���˳ƤW���ݩ�
static CheckClsEqAbilityResultENUM	CheckClsEqAbility( ItemFieldStruct* SrcItem , ItemFieldStruct* DestItem );


//�ˬd�O�_�i�H���ʦ����~( �p�G�O �شӪ� �åB�٨S�M�� �^�� false  �䥦 true  )
static bool CheckMovePlantItem( ItemFieldStruct& houseItem );