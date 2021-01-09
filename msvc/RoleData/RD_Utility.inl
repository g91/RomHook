
// ���o�ثe�֦��e�q
static int GetAttachRuneCount(ItemFieldStruct* item);

// ���o�Ť��`�e�q
static int	GetRuneTotalVolume(ItemFieldStruct* item);

// ���o���~�`�W�r
static bool	GetItemFieldName(ItemFieldStruct* item, char* outName, int size);

// ���o�ܩʤW����
int	GetResistanceMaxValue();

// ���o�򥻼ƭ�
void GetAbilityDetailValues(RoleValueName_ENUM name, int* outAbility);

// ���oDPS
void GetPlayerDPS(float* outDPS);

// ���o�ۦP���~�b�I�]���̤j�ƶq
int GetBagItemCount(int objectID);

// ���o�ޯ�ϥΧN�j�ɶ�
static bool GetMagicCooldown(MagicColdownStruct& coldown, int objectID, float* outTime);

// ���o�ޯ�ϥΧN�j�ɶ�
bool GetObjectCooldown(int objectID, float* outTime);

// �ˬd���~����O�_�i�H�˳�(����)
bool CanWearObject(GameObjDbStruct* itemDB, int slot=-1, bool ignoreLevel=false , int ImageObjID = 0  );

// �ˬd�I�]�����~�O�_�i�H�ϥ�(true �i�H��, false ��w�������)
bool IsActiveBagItem(int index);

// �ˬd�˳Ƨޯ�
bool CheckEquipmentWearSkill(GameObjDbStruct* itemDB, int slot=-1);

// ���o�ޯ���m����
float GetSkillPoint(int magicID);

//���o�YBuff��PowerLv
int GetBuffPowerLv( int magicID );

//���o�Y��쪺�ޯ�t�I�`��
int	GetTolalSkillPoint( int Pos );

// �P�_�O�_���¦�樤��
bool CheckIgnoreNameList(const char* name);

//�p��׸˰��� return cost   ��J  �ײz�e  , �ײz��
static int	CalRepairWeapon( ItemFieldStruct* InItem , ItemFieldStruct* OutItem = NULL );

bool IsEquipSuitSkill(int skillId);

// �ˬd�˳����O�_���T
static bool	CheckEquipmentPos(int pos, ItemFieldStruct* itemField=NULL);


