
// ¨ú±o¥Ø«e¾Ö¦³®e¶q
static int GetAttachRuneCount(ItemFieldStruct* item);

// ¨ú±o²Å¤åÁ`®e¶q
static int	GetRuneTotalVolume(ItemFieldStruct* item);

// ¨ú±oª««~Á`¦W¦r
static bool	GetItemFieldName(ItemFieldStruct* item, char* outName, int size);

// ¨ú±o§Ü©Ê¤W­­­È
int	GetResistanceMaxValue();

// ¨ú±o°ò¥»¼Æ­È
void GetAbilityDetailValues(RoleValueName_ENUM name, int* outAbility);

// ¨ú±oDPS
void GetPlayerDPS(float* outDPS);

// ¨ú±o¬Û¦Pª««~¦b­I¥]¤º³Ì¤j¼Æ¶q
int GetBagItemCount(int objectID);

// ¨ú±o§Þ¯à¨Ï¥Î§Nƒj®É¶¡
static bool GetMagicCooldown(MagicColdownStruct& coldown, int objectID, float* outTime);

// ¨ú±o§Þ¯à¨Ï¥Î§Nƒj®É¶¡
bool GetObjectCooldown(int objectID, float* outTime);

// ÀË¬dª««~­­¨î¬O§_¥i¥H¸Ë³Æ(¦³®Ä)
bool CanWearObject(GameObjDbStruct* itemDB, int slot=-1, bool ignoreLevel=false , int ImageObjID = 0  );

// ÀË¬d­I¥]¤ºª««~¬O§_¥i¥H¨Ï¥Î(true ¥i¥H¥Î, false Âê©w¤¤¤£¯à¥Î)
bool IsActiveBagItem(int index);

// ÀË¬d¸Ë³Æ§Þ¯à
bool CheckEquipmentWearSkill(GameObjDbStruct* itemDB, int slot=-1);

// ¨ú±o§Þ¯à¼ô½mµ¥¯Å
float GetSkillPoint(int magicID);

//¨ú±o¬YBuffªºPowerLv
int GetBuffPowerLv( int magicID );

//¨ú±o¬YÄæ¦ìªº§Þ¯à°tÂIÁ`­È
int	GetTolalSkillPoint( int Pos );

// §PÂ_¬O§_¬°¶Â¦â³æ¨¤¦â
bool CheckIgnoreNameList(const char* name);

//­pºâ­×¸Ë°²¿ú return cost   ¿é¤J  ­×²z«e  , ­×²z«á
static int	CalRepairWeapon( ItemFieldStruct* InItem , ItemFieldStruct* OutItem = NULL );

bool IsEquipSuitSkill(int skillId);

// ÀË¬d¸Ë³ÆÄæ¦ì¬O§_¥¿½T
static bool	CheckEquipmentPos(int pos, ItemFieldStruct* itemField=NULL);


