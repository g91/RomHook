//----------------------------------------------------------------------------------------------------------------------------
static void OnTimeProcAll();
static ReaderClass<PlayerRoleData>*  ReaderBase( );
static ReaderClass<PlayerRoleData>*  ReaderBase_Account( );
//static ReaderClass<RoleDataEx>*  ReaderBaseEx( );
static ReaderClass<NPCData>*  ReaderNPC( );
static ReaderClass<SampleRoleData>*  ReaderSampleRoleData( );
static ReaderClass<DB_ItemFieldStruct>*  ReaderRD_Field( );
static ReaderClass<DB_AbilityStruct>*  ReaderRD_Ability( );
static ReaderClass<DB_BaseFriendStruct>*  ReaderRD_BaseFriendStruct( );
static ReaderClass<DB_MailItemStruct>*  ReaderRD_MailItem( );
static ReaderClass<DB_MailStruct>*  ReaderRD_MailBase( );

static ReaderClass<DB_ACItemStruct>*		ReaderRD_ACBase( );
static ReaderClass<DB_ACItemHistoryStruct>*	ReaderRD_ACHistory( );
static ReaderClass<DB_NPC_MoveBaseStruct>*	ReaderRD_NPC_MoveBase( );
static ReaderClass<DB_BillBoardRoleInfoStruct>*		ReaderRD_BillBoard( );

static ReaderClass<GuildMemberStruct>*	ReaderRD_GuildMember( );
static ReaderClass<GuildBaseStruct>*	ReaderRD_GuildBase( );
static ReaderClass<GuildBoardStruct>*	ReaderRD_GuildBoard( );

static ReaderClass<RoleDataEx>*  ReaderGMTool( );
static ReaderClass<BaseAbilityStruct>*  Reader_Ability_GMTools( );
static ReaderClass<SkillValueStruct>*  Reader_SkillValue_GMTools( );
static ReaderClass<ItemFieldStruct>*  Reader_ItemField_GMTools( );
static ReaderClass<RoleValueData>*  Reader_RoleValueData_GMTools( );

static ReaderClass<HouseBaseDBStruct>*	ReaderRD_HouseBase( );
static ReaderClass<HouseItemDBStruct>*	ReaderRD_HouseItem( );
static ReaderClass<DB_DepartmentStoreBaseInfoStruct>*	ReaderRD_DepartmentStoreItem( );
static ReaderClass<ImportBoardBaseStruct>*	ReaderRD_ImportBoardBase( );

static ReaderClass<GuildHousesInfoStruct>*				ReaderRD_GuildHouseInfo( );
static ReaderClass<GuildHouseBuildingInfoStruct>*		ReaderRD_GuildHouseBuildingInfo( );
static ReaderClass<GuildHouseItemStruct>*				ReaderRD_GuildHouseItem( );
static ReaderClass<GuildHouseFurnitureItemStruct>*		ReaderRD_GuildHouseFurnitureItem( );

static ReaderClass<AccountBagItemFieldDBStruct>*	ReaderRD_AccountBag( );
static ReaderClass<WebShopBagItemFieldDBStruct>*	ReaderRD_WebShopBag( );

static ReaderClass<OfflineMessageDBStruct>*			ReaderRD_OfflineMessage();

static ReaderClass<GuildHouseWarInfoStruct>*		ReaderRD_GuildHouseWarInfo();
static ReaderClass<GuildHouseWarHistoryStruct>*		ReaderRD_GuildHouseWarHistory();
static ReaderClass<ReserverRoleStruct>*				RoleDataEx::ReaderRD_ReserveRole();
static ReaderClass<DB_CultivatePetStruct>*			RoleDataEx::ReaderRD_CultivatePetStruct();
//-------------------------------------------------------------------------------------------------------------------------
/*
typedef int					 (*GenerateItemVersionFunction)     ( int OrgObjID );
typedef	GameObjDbStruct*	 (*GetObjDBFunction)			    ( int OrgID );
typedef	RoleDataEx*			 (*GetRoleDataFunction)		        ( int LocalID );
typedef bool				 (*NewItemInitFunction)		        ( ItemFieldStruct& Item , int OrgObjID  );
typedef void				 (*UpDateEventFunction)		        ( RoleData *player , RoleUpdateEvent );
*/
//----------------------------------------------------------------------------------------------------------------------------
//	外部CallBack函式
//----------------------------------------------------------------------------------------------------------------------------


static  boost::function< GameObjDbStructEx*(int) >             		St_GetObjDB;
static  boost::function< RoleDataEx*(int) >                    		St_GetRoleData;
static  boost::function< int() >	                            		St_GenerateItemVersion;
static  boost::function< bool(ItemFieldStruct&,int,int) >	     		St_NewItemInit;
static  boost::function< void(RoleDataEx*, RoleUpdateEvent) >  		St_UpDateEvent;
static  boost::function< bool(RoleDataEx*, RoleDataEx*) >      		St_ProcessDead;
static  boost::function< bool(RoleDataEx*,MagicProcInfo*,int) >   		St_SpellMagic;
static  boost::function< int(int,float,float,float,float,int,int ) >	St_CreateObj;
static  boost::function< bool(int,int) >								St_AddToPartition;
static  boost::function< bool(int) >									St_DelFromPartition;
static  boost::function< int(int) >				             		St_GetKeyMagicID;
static  boost::function< void(int) >				             		St_ClearPath;
static  boost::function< void(int) >				             		St_SetPos;
static  boost::function< const char*( RoleDataEx*) >		        	St_GetRoleName;
static  boost::function< SysKeyValueStruct*() >	             		St_SysKeyValue;
static  boost::function< int(const char* ) >		             			St_GetSysKeyValue;
static  boost::function< GameObjDbStructEx*(GameObjDbStructEx*,GameObjDbStructEx*) >	St_RuneExchange;
static  boost::function< GameObjDbStructEx*(GameObjDbStructEx*) >		St_NextRuneLv;
static  boost::function< int(const char*) >							St_GetPCenterID;

//static GameObjDbStructEx*				RuneExchange( GameObjDbStructEx* Rune1 , GameObjDbStructEx* Rune2 );
//----------------------------------------------------------------------------------------------------------------------------
//外部 CallBack空函式
//----------------------------------------------------------------------------------------------------------------------------
static GameObjDbStructEx*	Empty_GetObjDB				        ( int OrgID ){return NULL;};
static RoleDataEx*			Empty_GetRoleData			        ( int LocalID ){return NULL;};
static int  				Empty_GenerateItemVersionFunction	( ){return 0;};
static bool					Empty_NewitemInit					( ItemFieldStruct& Item , int OrgObjID , int NPCObjID ){return false;};
static void					Empty_UpDateEvent					( RoleDataEx *player , RoleUpdateEvent ){};
static bool					Empty_ProcessDead                   ( RoleDataEx*, RoleDataEx* ){return false;};
static bool					Empty_SpellMagic                    ( RoleDataEx*,MagicProcInfo* , int ){ return false;}
static int					Empty_CreateObj						( int ObjID , float x , float y , float z , float dir , int count ,int WorldGuid ){ return -1;}
static bool					Empty_AddToPartition				( int GItemID , int RoomID ){ return false;};
static bool					Empty_DelFromPartition				( int GItemID ){ return false;};
static int					Empty_GetKeyMagicID				    ( int iKeyID ){return 0;};
static void					Empty_ClearPath						( int GItemID ){};
static const char*			Empty_GetRoleName					( RoleDataEx* ){ return ""; };
static SysKeyValueStruct*	Empty_SysKeyValueStruct				() {return NULL;} ;
static GameObjDbStructEx*	Empty_RuneExchange					( GameObjDbStructEx*,GameObjDbStructEx*) { return NULL; };
static GameObjDbStructEx*	Empty_NextRuneLv					( GameObjDbStructEx* Rune ){ return NULL;};
static int					Empty_GetSysKeyValue				( const char* ){return 0;}
static int					Empty_GetPCenterID					( const char* ){return 0;}
//////////////////////////////////////////////////////////////////////////
static int	RareAddLv( int Rare );
//////////////////////////////////////////////////////////////////////////