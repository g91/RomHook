#ifndef	__ROLEBASEDEF_H_
#define __ROLEBASEDEF_H_
#pragma	warning (disable:4786)
#pragma warning (disable:4949)
//#pragma warning (disable:4807)
#include "RoleBaseInc.h"
#include <time.h>
#include "MyTypeDef.h"
#include "SmallObj/StaticString.h"
#include "SmallObj/StaticFlag.h"
/*
#ifndef _CLIENT
#include "../NetWalker_Member/NetWakerPGEnum.h"
#else
#include "../NetWaker_Member/NetWakerPGEnum.h"
#endif
*/
#pragma unmanaged

#define DF_DAILY_RESET_TIME			6

#define _DEF_BASE_CLOCL_UNIT_		10          //�򥻳B�z���ɶ�
#define	_MAX_LOCALOBJECT_COUNT_		6000        //�ϰ�̦h�����`�q
#define	_MAX_EQ_REFINE_LEVE_		10			//����̰�����
#define	DEF_MAX_DESTROY_ITEM_LOG_COUNT 10		

//�b���̤jSize
#define _MAX_ACCOUNT_SIZE_			64			//�b������
#define _MAX_CREATETIME_SIZE_		28			//�ɶ��r�����
#define _MAX_NAMERECORD_SIZE_		_MAX_OBJ_NAME_STR_SIZE_			//����W�٪���

#define _MAX_DESTORYOBJ_REASON		128

#define _MAX_ROLE_COUNT_			5			//����ƶq
#define _MAX_ZONENAME_SIZE_			32			//����W�٪���
#define	_MAX_LUA_FUNTIONNAMESIZE_	32			//�@���W�ٳ̤j�r��
#define	_MAX_LUA_FUN_ARG_SIZE_		64			//�@���W�ٱa�ѼƳ̤j�r��
#define _MAX_HATELIST_SIZE_			50			//�̤j�i��������W��
#define _MAX_TRADE_ITEM_COUNT_		25
#define _MAX_FRIENDLIST_NOTE_		300			//�n�ͦW�����
#define _MAX_FRIENDLIST_FAMILY_COUNT_		20	//�S�����Y���n��
#define _MAX_FRIENDLIST_COUNT_		100			//�n�ͳ̤j�q
#define _MAX_FRIENDLIST_ALL_COUNT_  (_MAX_FRIENDLIST_COUNT_+_MAX_BAD_FRIENDLIST_COUNT_ +_MAX_HATE_PLAYER_LIST_COUNT_)
#define _MAX_BAD_FRIENDLIST_COUNT_	50			//�n�ͳ̤j�q
#define _MAX_HATE_PLAYER_LIST_COUNT_	20		//�T�H�]�̤j�q
#define _MAX_FRIENDLIST_GROUP_COUNT_	10
#define _MAX_FAMOUS_COUNT_			10			//�W�ͺ���
#define _MAX_REGISTER_COUNT_		10			//�̦h�@���Ȧs�ȼƶq
#define _MAX_LOCATION_SAVE_COUNT_	50			//�̦h���a�i�O�����ǰe��m

#define _MAX_REALTIME_FLAG_			100
#define _MAX_PLAYTIME_FLAG_			100
#define _MAX_LUA_VALUES_FLAG_		1000

#define	_MAX_BASE_ARG_COUNT_		30			//�̦h�򥻰ѼƦU��
#define	_MAX_EFFECTMAGIC_COUNT_		16			//���W�̦h���h�ֻ��U�k�N

#define _MAX_MONEY_COUNT_           999999999	//�����W��
#define _MAX_BONUSMONEY_COUNT_      99999		//�����W��
#define Def_MONEY_OBJID_            200000      //�������󸹽X

#define _MAX_Honor_COIN_COUNT_			25000		//�a�A�I��
#define _MAX_DuelistReward_COIN_COUNT_	20000		//�i�h����
#define _MAX_Relics_COIN_COUNT_			10000		//�j�N��
#define _MAX_PhiriusShell_COIN_COUNT_	1000		//�����Ŷꨩ
#define _MAX_EnergyJusticeCoin_COUNT_	10000



#define _BASE_ATTACK_SPEED_         40			//�򥻧����t��
#define _BASE_MOVE_SPEED_           50			//�򥻲��ʳt��

#define _MAX_ROLE_TOUCH_RANGE_		40			// �Ҧ��t��Ĳ�I�̤j�d��
#define _MAX_ROLE_TOUCH_MAXRANGE_	65			// Ĳ�o�@����, �����Z��

#define	_TIME_CHECKCASTEVENT_		100			// �ˬd�I���B�z���ɶ����j
#define	_TIME_CLICKTOGETITEM		5000		// �I�����Ȫ��~�һݭn���ɶ�
#define	_TIME_QUEST_CLICKTOGETITEM	5000		// �I�����Ȫ��~�һݭn���ɶ�
#define _TIME_DELAYPATROL			30000		// �I������ NPC ����ɶ�


#define _MAX_PARTY_COUNT_			36			//����H�ƤW��
#define _MAX_PARTY_COUNT_PARTY_		6
#define _MAX_PARTY_COUNT_RAID_		36

#define _MAX_PARTY_SHARE_RANGE_		1000		//������ɽd��

#define _MAX_SHARE_COLDOWN_COUNT_	30			//�@��coldonw�W��
#define _MAX_SPEAKDETAIL_SIZE_		1024		//��ܨt�Υ���̦h�r��
#define _MAX_SPEAKOPTION_SIZE_		256			//��ܨt�οﶵ�̦h�r��

#ifdef _LOCAL_SERVER_
	#define _DEF_ATTACK_EVENT_EFFECT_TIME_	4000	//�����ƥ󦳮Įɶ�
#else
	#define _DEF_ATTACK_EVENT_EFFECT_TIME_	3000	//�����ƥ󦳮Įɶ�
#endif

#define _MAX_MOVE_SENDALL_COUNT_	20			//�֩�h�֤H���e
#define _DEF_NPC_FIGHT_RANGE_		400
#define _DEF_ZONE_BASE_COUNT_		1000
#define _DEF_MAX_HOUSE_FURNITURE	500


#define _DEF_GUIDHOUSEITEM_MAX_PAGE_		100		//���|�ܮw���έ���
#define _DEF_GUIDHOUSEITEM_MAX_PAGEITEM_	100		//���|�ܮw���έ���
#define _DEF_GUIDHOUSE_MAX_BUILDING_COUNT_	100		//���|�ؿv�̦h�Ӽ�

#define _DEF_GUIDHOUSEITEM_MAX_FURNITURE_	500		//���|�γ̦h���h�ָ˹��a��
#define _DEF_MAX_DBID_COUNT_		10000000		//DBID�̤j�Ӽ�
#define _MAX_CYCLE_MAGIC_COUNT_		5

#define _MAX_PK_DEAD_SAVE_COUNT_	3

#define _MAX_BuffTimeDesc_COUNT_	20

#define _DEF_MAX_PET_TYPE_			48				//�̦h�d�����X������
#define _MEMORY_CHECK_VALUE_		1234567890
#define MAX_TALK_CONTENT			512
#define _ACCOUNT_FLAG_COUNT_		1024
#define _MAX_CLIENT_SETTING_SIZE_	20	//�S�����Y���n��
#define _MAX_BACKUP_EQ_SET_COUNT_	5

#define _MAX_PET_CARD_COUNT_		256
//-------------------------------------------------------------------------------------
//		 �U�ظ˳���쪺�W���ƶq
//-------------------------------------------------------------------------------------
#define _MAX_BODY_COUNT_			240			//���W���~�̦h���h��
#define _MAX_BODY_EX_COUNT_			50			//�ӫ��]�]�ƶq
#define _MAX_BODY_MAGIC_BOX_COUNT_	10			//����_��
#define _MAX_BODY_BEGIN_POS_		(_MAX_BODY_EX_COUNT_+_MAX_BODY_MAGIC_BOX_COUNT_)

#define _MAX_BANK_COUNT_			300			//���W���~�̦h���h��
#define _MAX_GIVESYSTEM_COUNT_		10			//�����t�γ̦h���h��
#define _MAX_TEMP_COUNT_			20			//�Ȧs�ϰ�̦h���h��(��t�ε����ɩ��x�s���a��)
#define _MAX_BUFF_COUNT_			50			//�̦h�i�H�W��Buff�ƶq
#define _MAX_REFINE_BUFF_COUNT_		20			//�Ͳ�Coldown�̤j�ȳ]�w		
#define _MAX_RENT_COUNT_			50			//�̤j���Ϊ�����

#define _MAX_TITLE_FLAG_COUNT_		2048	
#define _MAX_HOUSES_SHOPFUNCTION_COUNT_	256	
#define _MAX_FLAG_COUNT_			16000
#define _MAX_CARD_COUNT_			2048
#define _MAX_CLIENT_FLAG_COUNT_		256
#define _MAX_CLIENT_DATA_SIZE_		256

#define DF_SKILLID_ATTACK				540000		// ����
#define DF_SKILLID_PORTOL				540001		// �^���N
#define DF_SKILLID_DISENCHANT			540002		// ����
#define DF_SKILLID_PK					540003		// PK
#define DF_SKILLID_BEGINNERPORTOL_BEGIN	540190		// �Ǧ^�s����}�l�ˬd�s��
#define DF_SKILLID_BEGINNERPORTOL_END	540199		// �Ǧ^�s����}�l�ˬd�s��

#define _DEL_ROLE_RESERVE_TIME_		(24*60*60)	//�R���O�d�ɶ�

#define	_DEF_ITEM_ABILITY_DELTA_	500000

#define	Def_AccountMoneyLockTime_Max_Count_ 30
#define	_DEF_MAX_COOL_SUIT_COUNT_	10
#define	_DEF_MAX_COOL_CLOTH_COUNT_	500

#define _DEF_MAX_PET_EXBAG_COUNT_	100
#define _DEF_MAX_HORSE_EXBAG_COUNT_	100

#define DEF_MAX_WEEK_INS_TYPE				5
#define DEF_MAX_WEEK_INS_TYPE_DAY_COUNT		3
//-------------------------------------------------------------------------------------
//		 �U�ظ˳���쪺�W���ƶq
//-------------------------------------------------------------------------------------
#define DF_QUESTDAILY_MAXGROUP		20

//-----------------------------------------------------------------------------------------
#define _DEF_MAX_MONEY_VENTOR_COUNT_	50
//#define _DEF_MAX_BOT_COUNT_				20
//-----------------------------------------------------------------------------------------
//�ˬd�O�_�i�H�m�������˳�
//-----------------------------------------------------------------------------------------
enum CheckSetEQResultENUM
{
	EM_CheckSetEQResult_OK		,
	EM_CheckSetEQResult_OKEx	,	//�D�Ƥ�S��B�z
	EM_CheckSetEQResult_Failed	,
	EM_CheckSetEQResult_Failed_ItemUnique	,
};
//-----------------------------------------------------------------------------------------
//�ƭȦW�٦C�|
//-----------------------------------------------------------------------------------------
enum	RoleValueName_ENUM
{
	EM_RoleValue_HP	= 0		    ,
	EM_RoleValue_MP			    ,
	EM_RoleValue_RACE			,
	EM_RoleValue_VOC  		    ,
	EM_RoleValue_SEX			,
	EM_RoleValue_EXP			,
	EM_RoleValue_LV			    ,

	EM_RoleValue_X			    ,
	EM_RoleValue_Y			    ,
	EM_RoleValue_Z			    ,
	EM_RoleValue_Dir		    ,

    EM_RoleValue_STR            ,
    EM_RoleValue_STA            ,
    EM_RoleValue_INT            ,
    EM_RoleValue_MND            ,
    EM_RoleValue_AGI            ,

    EM_RoleValue_Point          ,
    EM_RoleValue_SkillPoint     ,

    EM_RoleValue_SP			    ,
	EM_RoleValue_SP_Sub		    ,    

    EM_RoleValue_MaxHP		    ,
    EM_RoleValue_MaxMP		    ,
    EM_RoleValue_MaxSP		    ,
	EM_RoleValue_MaxSP_Sub	    ,

    EM_RoleValue_VOC_SUB	    ,
    EM_RoleValue_LV_SUB		    ,

    EM_RoleValue_ThisLVExp	    ,
	EM_RoleValue_LiveTime	    ,

	EM_RoleValue_BodyCount		,		//�������ƶq
	EM_RoleValue_BankCount		,		//�Ȧ����ƶq
	EM_RoleValue_RoomID			,
	EM_RoleValue_TpExp			,		//�ޯ�g����I��


	EM_RoleValue_Money			,		// ���W���ƶq
	EM_RoleValue_Money_Account	,		// ���W���ƶq

	EM_RoleValue_KillRate		,		//���ǳt��
	EM_RoleValue_StomachPoint	,		//�]�w������

	EM_RoleValue_SysFlag		,

	EM_RoleValue_AddExp			,		//�B�~�W�[�g���
	EM_RoleValue_AddTP			,		//�B�~�W�[tp
	EM_RoleValue_PlayTimeQuota	,		//���I�g
	EM_RoleValue_GoodEvil		,		//���c��
	EM_RoleValue_VocCount		,		//¾�~�ƶq�W��
	EM_RoleValue_BoxEnergy		,		//�ĦX�c��q
	EM_RoleValue_MedalCount		,		//�о��I��
	EM_RoleValue_BonusMoney		,		//���Q��
	EM_RoleValue_MaxLv			,		//���ŤW��

	EM_RoleValue_DebtExp		,		//�g��ȭt��
	EM_RoleValue_DebtTP			,		//TP�t��

	EM_RoleValue_FinStr			,		//�p���STR
	EM_RoleValue_FinSta			,		//�p���STA
	EM_RoleValue_FinInt			,		//�p���INT
	EM_RoleValue_FinMnd			,		//�p���MND
	EM_RoleValue_FinAgi			,		//�p���AGI

	EM_RoleValue_Honor			,		//�a�A
	EM_RoleValue_MaxPlantCount	,		//�̦h�i�شӪ��ƶq
	EM_RoleValue_AttackDelay	,		//��������
	EM_RoleValue_TotalTpExp		,		//TP�W����

	EM_RoleValue_CliOk_X	    ,		//�T�{�i�����I
	EM_RoleValue_CliOk_Y	    ,		//�T�{�i�����I
	EM_RoleValue_CliOk_Z	    ,		//�T�{�i�����I

	EM_RoleValue_VIP_Type		,		//VIP Type
	EM_RoleValue_VIP_Flag		,
	EM_RoleValue_UnTrust_Flag	,		//���a�H������(���Ȫ�ܤ��H��)

	EM_RoleValue_Money_AccountLock	,	//��w���b�����ƶq
	EM_RoleValue_TitleID			,	//�ثe�Y�Ϊ�ID
	EM_RoleValue_TitleSys_Famous	,	//�Y�Ψt�ΦW�n
	EM_RoleValue_TitleSys_Lv	  	,	//�Y�Ψt�ε���
	EM_RoleValue_TitleSys_Exp	  	,	//�Y�Ψt�θg���
	EM_RoleValue_TitleSys_TitleID1	,	//�Y�Ψt�θ˳��Y��
	EM_RoleValue_TitleSys_TitleID2	,	//�Y�Ψt�θ˳��Y��
	EM_RoleValue_TitleSys_TitleID3	,	//�Y�Ψt�θ˳��Y��
	EM_RoleValue_TitleSys_TitleID4	,	//�Y�Ψt�θ˳��Y��
	EM_RoleValue_TitleSys_TitleID5	,	//�Y�Ψt�θ˳��Y��
	EM_RoleValue_SoulPoint			,	//�F���
	EM_RoleValue_MoveDelay			,	//move����
	EM_RoleValue_SlotMachineFreeCount,	//���l�Ѫ�K�O����
	EM_RoleValue_DuelistReward		,	//�i�h����
	EM_RoleValue_TrialBadgeCoin		,	//�շ�����
	EM_RoleValue_RelicsCoin			,	//�j�N��
	EM_RoleValue_DreamlandCoin		,	//�ڹҥ����L�O
	EM_RoleValue_PhiriusShellCoin	,	//�����Ŷꨩ
	EM_RoleValue_EnergyJusticeCoin	,	//���q��q
	EM_RoleValue_ProofLegendCoin	,	//�ǻ�����
	EM_RoleValue_VenderCount		,	//���Ӧ^���v��
	EM_RoleValue_LockHP				,	//lockHP
	EM_RoleValue_WeekResetCount		,
	EM_RoleValue_MirrorCoin			,	//������L

	EM_RoleValue_Famous         = 400,  

	EM_RoleValue_Register       = 450,  

	
    EM_RoleValue_KeyItemOn      = 600,
	EM_RoleValue_KeyItemOff     ,

	//EM_RoleValue_SkillValue		= 700 , 

	EM_RoleValue_Skill_Unarmed			= 700,	// Unarmed�Ť�
	EM_RoleValue_Skill_Blade			,		// �C
	EM_RoleValue_Skill_Dagger			,		// �P��
	EM_RoleValue_Skill_Wand				,		// �v��
	EM_RoleValue_Skill_Axe				,		// ��
	EM_RoleValue_Skill_Bludgeon			,		// ��Ҵ�
	EM_RoleValue_Skill_Claymore			,		// ����C
	EM_RoleValue_Skill_Staff			,		// ��
	EM_RoleValue_Skill_2H_Axe			,		// �����
	EM_RoleValue_Skill_2H_Hammer		,		// ������
	EM_RoleValue_Skill_Polearm			,		// �j(����)
	EM_RoleValue_Skill_Bow				,		// ���{�Z�� �}
	EM_RoleValue_Skill_CossBow			,		// ���{�Z�� �Q�r�}
	EM_RoleValue_Skill_Gun				,		// ���{�Z�� �j
	EM_RoleValue_Skill_Define			,		// ���m

	EM_RoleValue_Skill_BlackSmith		,		// ���K
	EM_RoleValue_Skill_Carpenter		,		// ��u
	EM_RoleValue_Skill_MakeArmor		,		// �s��
	EM_RoleValue_Skill_Tailor			,		// ���_
	EM_RoleValue_Skill_Cook				,		// �i��
	EM_RoleValue_Skill_Alchemy			,		// �Ҫ�

	EM_RoleValue_Skill_Mining			,		// ���q
	EM_RoleValue_Skill_Lumbering		,		// ���
	EM_RoleValue_Skill_Herblism			,		// ����
	EM_RoleValue_Skill_Fishing			,		// ����
	EM_RoleValue_Skill_Plant			,		// �ش�
	EM_RoleValue_Skill_CatchPet			,		// �d���ɮ�

	EM_RoleValue_Skill_Fin_Unarmed		= 750,	// Unarmed�Ť�
	EM_RoleValue_Skill_Fin_Blade		,		// �C
	EM_RoleValue_Skill_Fin_Dagger		,		// �P��
	EM_RoleValue_Skill_Fin_Wand			,		// �v��
	EM_RoleValue_Skill_Fin_Axe			,		// ��
	EM_RoleValue_Skill_Fin_Bludgeon		,		// ��Ҵ�
	EM_RoleValue_Skill_Fin_Claymore		,		// ����C
	EM_RoleValue_Skill_Fin_Staff		,		// ��
	EM_RoleValue_Skill_Fin_2H_Axe		,		// �����
	EM_RoleValue_Skill_Fin_2H_Hammer	,		// ������
	EM_RoleValue_Skill_Fin_Polearm		,		// �j(����)
	EM_RoleValue_Skill_Fin_Bow			,		// ���{�Z�� �}
	EM_RoleValue_Skill_Fin_CossBow		,		// ���{�Z�� �Q�r�}
	EM_RoleValue_Skill_Fin_Gun			,		// ���{�Z�� �j
	EM_RoleValue_Skill_Fin_Define		,		// ���m

	EM_RoleValue_Skill_Fin_BlackSmith	,		// ���K
	EM_RoleValue_Skill_Fin_Carpenter	,		// ��u
	EM_RoleValue_Skill_Fin_MakeArmor	,		// �s��
	EM_RoleValue_Skill_Fin_Tailor		,		// ���_
	EM_RoleValue_Skill_Fin_Cook			,		// �i��
	EM_RoleValue_Skill_Fin_Alchemy		,		// �Ҫ�

	EM_RoleValue_Skill_Fin_Mining		,		// ���q
	EM_RoleValue_Skill_Fin_Lumbering	,		// ���
	EM_RoleValue_Skill_Fin_Herblism		,		// ����
	EM_RoleValue_Skill_Fin_Fishing		,		// ����
	EM_RoleValue_Skill_Fin_Plant		,		// �ش�
	EM_RoleValue_Skill_Fin_CatchPet		,		// �d���ɮ�

	EM_RoleValue_SkillMax_Unarmed		= 850,		// Unarmed�Ť�
	EM_RoleValue_SkillMax_Blade			,		// �C
	EM_RoleValue_SkillMax_Dagger		,		// �P��
	EM_RoleValue_SkillMax_Wand			,		// �v��
	EM_RoleValue_SkillMax_Axe			,		// ��
	EM_RoleValue_SkillMax_Bludgeon		,		// ��Ҵ�
	EM_RoleValue_SkillMax_Claymore		,		// ����C
	EM_RoleValue_SkillMax_Staff			,		// ��
	EM_RoleValue_SkillMax_2H_Axe		,		// �����
	EM_RoleValue_SkillMax_2H_Hammer		,		// ������
	EM_RoleValue_SkillMax_Polearm		,		// �j(����)
	EM_RoleValue_SkillMax_Bow			,		// ���{�Z�� �}
	EM_RoleValue_SkillMax_CossBow		,		// ���{�Z�� �Q�r�}
	EM_RoleValue_SkillMax_Gun			,		// ���{�Z�� �j
	EM_RoleValue_SkillMax_Define		,		// ���m

	EM_RoleValue_SkillMax_BlackSmith	,		// ���K
	EM_RoleValue_SkillMax_Carpenter		,		// ��u
	EM_RoleValue_SkillMax_MakeArmor		,		// �s��
	EM_RoleValue_SkillMax_Tailor		,		// ���_
	EM_RoleValue_SkillMax_Cook			,		// �i��
	EM_RoleValue_SkillMax_Alchemy		,		// �Ҫ�

	EM_RoleValue_SkillMax_Mining		,		// ���q
	EM_RoleValue_SkillMax_Lumbering		,		// ���
	EM_RoleValue_SkillMax_Herblism		,		// ����
	EM_RoleValue_SkillMax_Fishing		,		// ����
	EM_RoleValue_SkillMax_Plant			,		// �ش�
	EM_RoleValue_SkillMax_CatchPet		,		// �d���ɮ�


	EM_RoleValue_VOCLV_GM				= 900,	// ¾�~���� ( �̷� Voc_ENUM 900 ( GM ) + 16 ) 
	EM_RoleValue_VOCLV_Warrior		,
	EM_RoleValue_VOCLV_Ranger		,
	EM_RoleValue_VOCLV_Rogue		,
	EM_RoleValue_VOCLV_Wizard		,
	EM_RoleValue_VOCLV_Priest		,
	EM_RoleValue_VOCLV_Knight		,
	EM_RoleValue_VOCLV_RuneDancer	,
	EM_RoleValue_VOCLV_Druid		,

	EM_RoleValue_ClinetSetting		= 950,			//Client �ݳ]�w�ƭȸ��

	EM_RoleValue_FamilyFriendListLv_Pos		= 1000,	//�n�͵���( �@ 20 �� )

	EM_RoleValue_LuaMagicID					= 1100,	//�n�͵���( �@ 20 �� )

	EM_RoleValue_TimeFlag					= 1200,	//200�Ӯɶ��X��

	EM_RoleValue_WeekInstnaces				= 1500, //

	EM_RoleValue_MagicPowerLv_SP			= 2000,
	EM_RoleValue_MagicPowerLv_Normal		= 2200,			
	EM_RoleValue_MagicPowerLv_SubJob		= 2250,

	EM_RoleValue_MagicID_SP					= 2300,
	EM_RoleValue_MagicID_Normal				= 2500,		
	EM_RoleValue_MagicID_SubJob				= 2550,

	EM_RoleValue_CultivatePet_Money			= 2998,
	EM_RoleValue_CultivatePet_NextMergeResetTime = 2999,
	//---------------------------------------------------------------------------------------
	//�d�����( 3000 - 4000 ) �C���d����ư�100 ��
	EM_RoleValue_CultivatePet_Value			= 3000	,	//	
	EM_RoleValue_LuaValueFlag				= 4000,
    //---------------------------------------------------------------------------------------
	EM_RoleValue_Coldown					= 6000, //�N�o�ɶ� 1+200+15+30 = 246��
	//---------------------------------------------------------------------------------------
    //�@���ݭn���ƭ�        
    //---------------------------------------------------------------------------------------
    EM_RoleValue_IsNPC          = 7000,
    EM_RoleValue_IsPlayer       ,
    EM_RoleValue_OrgID          ,
	EM_RoleValue_AttackTargetID ,
	EM_RoleValue_PID			,
	EM_RoleValue_IsWalk			,
	EM_RoleValue_MaxHit			,		// �ثe�糧���y���̤j�ˮ`���H
	EM_RoleValue_DBID			,			
	EM_RoleValue_IsDead			,
	EM_RoleValue_GroupID		,
	EM_RoleValue_GuildID		,
	EM_RoleValue_ZoneID			,		//�Ҧb�ϰ�]�h���y�^
	EM_RoleValue_HouseDBID		,		//�Ыθ��X
	EM_RoleValue_PetID			,		//�d�����X
	EM_RoleValue_IsAttackMode	,
	EM_RoleValue_IsUnholster	,		//client �԰����A
	EM_RoleValue_SpellMagicID	,		//���b�I���k�N
	EM_RoleValue_CampID			,		//�}�縹�X(read only )
	EM_RoleValue_OwnerDBID		,		//�D�H��DBID

	EM_RoleValue_OwnerGUID				,	//�D�H������
	EM_RoleValue_DodgeState				,	//(�̪�)�{��
	EM_RoleValue_MissState				,	//(�̪�)Miss
	EM_RoleValue_ParryState				,	//(�̪�)Parry
	EM_RoleValue_BeParryState			,	//(�̪�)�QParry
	EM_RoleValue_BeDodgeState			,	//(�̪�)�Q�{��
	EM_RoleValue_CritialState			,	//(�̪�)���zCritial
	EM_RoleValue_BeCritialState			,	//(�̪�)�Q���zCritial
	EM_RoleValue_MagicCritialState		,	//(�̪�)�k�NCritial
	EM_RoleValue_BeMagicCritialState	,	//(�̪�)�Q�k�NCritial
	EM_RoleValue_ShieldBlockState		,	//(�̪�)����
	EM_RoleValue_BeShieldBlockState		,	//(�̪�)�Q����	

	EM_RoleValue_LastDHp				,	//�̫�@��HP�ܤƶq
	EM_RoleValue_LastDHpTarget			,	//�̫�@�����ܪ�
	EM_RoleValue_VisitHouseDBID			,	//���[��DBID

	EM_RoleValue_PetID_Cultivate,		//�d�����X	

	EM_RoleValue_Fin_Phy_ATK	,		//�����O
	EM_RoleValue_Fin_Phy_Dmg	,		//�D��ˮ`
	EM_RoleValue_Fin_Phy_Def	,		//���m�O

	EM_RoleValue_Fin_Mag_ATK	,		//�]��
	EM_RoleValue_Fin_Mag_Dmg	,		//�]�k�ˮ`
	EM_RoleValue_Fin_Mag_Def	,		//�]�k���m

	EM_RoleValue_Fin_Phy_DodgeLv,		//�{�׵���
	EM_RoleValue_Fin_Phy_HitLv	,		//���z�R������
	EM_RoleValue_Fin_Mag_HitLv	,		//�]�k�R������

	EM_RoleValue_Fin_Phy_ParryRate,		//���ɲv

	EM_RoleValue_Fin_Phy_CritRate,		//���z�P�R�@���v
	EM_RoleValue_Fin_Phy_CritResistRate,//�ܪ��z�P�R�@���v
	EM_RoleValue_Fin_Phy_CritPower,		//���z�P�R�@���¤O

	EM_RoleValue_Fin_Mag_CritRate,		//�k�N�P�R�@���v
	EM_RoleValue_Fin_Mag_CritResistRate,//�ܪk�N�P�R�@���v
	EM_RoleValue_Fin_Mag_CritPower,		//�k�N�P�R�@���¤O

	EM_RoleValue_CliState		,		//���o�ثe���⪺Cli�ݪ��A

	EM_RoleValue_AroundPlayer	,		//�P�򪱮a����ƶq
	EM_RoleValue_NpcOnMove		,		//npc �O�_���b����

	EM_RoleValue_IncursivePoint	,		//�@�ɰƥ��J�I�ƥ��Z��
	EM_RoleValue_RecalculateAll	,		//�����ƭ��s�p��

	EM_RoleValue_PassengerAttackable ,	//�i��������
	EM_RoleValue_AttachObjGUID	,		//���㪫��ID
	EM_RoleValue_BeginAtkDBID 	,		//���o�Ĥ@�ӱ��Ǫ��H
	EM_RoleValue_DualTargetDBID	,		//���o��ժ��ؼ�
	EM_RoleValue_CastingType	,		//���o�O�_��Client�ϥα�
	EM_RoleValue_SetNPCAttackRange,		//�]�wNPC�����Z��

	EM_RoleValue_LastAttackType			,	//(����)�̫�@�� ��������(OnAttackTypeENUM)
	EM_RoleValue_LastAttackOwnerID		,	//(����)�̫�@�� �Q������
	EM_RoleValue_LastAttackTargetID		,	//(����)�̫�@�� ������
	EM_RoleValue_LastAttackMagColID		,	//(����)�̫�@�� �����k�N���X
	EM_RoleValue_LastAttackMagBaseID	,	//(����)�̫�@�� �����k�N��
	EM_RoleValue_LastAttackDamage		,	//(����)�̫�@�� �����ˮ`�q
	EM_RoleValue_LastAttackDmgType		,	//(����)�̫�@�� �����ˮ`����(ATTACK_DMGTYPE_ENUM)
	EM_RoleValue_CycleMagicID			,	//�ثe�`�����k�N

	EM_RoleValue_BaseEQ_Str				,		//str����Buff���ƭ�
	EM_RoleValue_BaseEQ_Sta				,		//sta����Buff���ƭ�
	EM_RoleValue_BaseEQ_Int				,		//int����Buff���ƭ�
	EM_RoleValue_BaseEQ_Mnd				,		//mnd����Buff���ƭ�
	EM_RoleValue_BaseEQ_Agi				,		//agi����Buff���ƭ�

	EM_RoleValue_RealZoneID				,		//�Ҧb�ϰ�]���h���y�^
	EM_RoleValue_HidePlotOwnerDBID		,		//(DEBIG)���ü@�������DBID
	EM_RoleValue_HidePlotOwnerOrgObjID	,		//(DEBIG)���ü@�������OrgObjID


	EM_RoleValue_SuitSkill_LeanSkillCount = 8000	,	//�ǲߪ��˳Ƨޯ�
	EM_RoleValue_SuitSkill_MaxEqSkillCount			,	//�̤j�i�˪���˧ޯ��

	EM_RoleValue_SuitSkill_EqID			= 8100		,	//�ثe�˳ƪ��ޯ�
	EM_RoleValue_SuitSkill_LeanSkillID	= 8200		,	//�ثe�Ƿ|���ޯ�(200��)

	EM_RoleValue_BG_Return_Value		= 8500		,	//�S��Գ��^�ǭ�

	EM_RoleValue_SPMagic				= 9000 ,   //�k�N����
	EM_RoleValue_NormalMagic			= EM_RoleValue_SPMagic + _MAX_SPSkill_COUNT_ ,   //�k�N����

	EM_RoleValue_SuitWardrobe			= 10000 ,	//�Ǹ˦��o
	EM_RoleValue_PetCard				= 11000	,	//�d���d��
    //---------------------------------------------------------------------------------------
    EM_RoleValueName_EM_FORCE_DWORD   = 0x7fffffff, 

	//(...�U���ޯ�)
};

//----------------------------------------------------------------------------------
// ����޲z����
//----------------------------------------------------------------------------------
enum	ManagementENUM
{
	EM_Management_Nornal		= 0,		//�@�몱�a

	EM_Management_GameVisitor	= 9	 ,		//�C�����[��
	EM_Management_GameService	= 10 ,		//�C���A�Ȫ�
	EM_Management_GameMaster	= 11 ,		//�C���޲z��
	EM_Management_BigGM			= 12 ,		//�jGM
	EM_Management_GameCreator	= 13 ,		//�C���]�p��
};
//----------------------------------------------------------------------------------
// ���A�C�| (�������A��) AI�B�z�C�|
//----------------------------------------------------------------------------------
//��:
// AI1 : Normal -> Spell assist -> Search Enemy -> Attack Enemy  -> Normal
//                                              -> Move          -> Normal
//       under attack -> Attack <-> spell Cure , Atk 
//                    
enum	NPCAIActionTypeENUM
{
    EM_ActionType_NORMAL		= 0	,
    EM_ActionType_MOVE			    ,
    EM_ActionType_SEARCHENEMY       ,
    EM_ActionType_ESCAPE            ,
    EM_ActionType_UNDERATTACK       ,
    EM_ActionType_ATTACK            ,
	EM_ActionType_DEAD              ,

    EM_ActionTypeEM_FORCE_DWORD   = 0x7fffffff, 
};
//-------------------------------------------------------------------------------------
//���c����
enum GoodEvilTypeENUM
{
	EM_GoodEvil_Demon		= -4 ,	
	EM_GoodEvil_Evil3		,	
	EM_GoodEvil_Evil2		,	
	EM_GoodEvil_Evil1		,	
	EM_GoodEvil_Normal		,	
	EM_GoodEvil_Good1		,	
	EM_GoodEvil_Good2		,	
	EM_GoodEvil_Good3		,	
	EM_GoodEvil_Hero		,	
};

//-------------------------------------------------------------------------------------
enum ZoneTypeENUM
{
	EM_ZoneType_NORMAL				= 0,
	EM_ZoneType_DEADZONE			= 1,
	EM_ZoneType_DAMAGEZONE			= 2,
	EM_ZoneType_IMMEDIATEDEATHZONE	= 3,

	EM_ZoneType_FORCE_DWORD			= 0x7FFFFFFF
};
//-------------------------------------------------------------------------------------
//��m��Ʃw�q
struct PlayerPosStruct
{
	int	X , Y , Z;
	int Dir;
	int ProcTime;
	PlayerPosStruct()
	{ memset( this , 0 , sizeof(PlayerPosStruct) ); }
};
//-------------------------------------------------------------------------------------
//�˳Ƹ�ƦC�|
enum	ItemState_ENUM
{
	EM_ItemState_CliDisabled  = -1          ,
    EM_ItemState_NONE       = 0             ,

    EM_USE_ITEM		        = 0x1000		,	//�ϥΪ����~(�]�w���~�ϥΤ�)
    EM_USE_SELSELL          = 0x1001		,	//��ܭn��X��
	EM_USE_SELMAIL			= 0x1002		,	//��ܭn�H�X��(��ܤw�R��)
	EM_USE_GUILDCONTRIBUTION= 0x1003		,	//��ܭn�^�m�����~
	EM_USE_ITEM_GAMBLE		= 0x1004		,	//���~�ݩʽ��

	EM_RECIPE_RESOURCE	    = 0x1100		,	//�t��귽���w

    EM_VENDOR_ONSELL1	    = 0x2000		,	//��ܩ������
    EM_VENDOR_ONSELL2						,
    EM_VENDOR_ONSELL3						,
    EM_VENDOR_ONSELL4						,
    EM_VENDOR_ONSELL5						,
    EM_VENDOR_ONSELL6						,
    EM_VENDOR_ONSELL7						,
    EM_VENDOR_ONSELL8						,

	EM_TRADE_ITEM1	        = 0x3000		,
	EM_TRADE_ITEM2							,
	EM_TRADE_ITEM3							,
	EM_TRADE_ITEM4							,
	EM_TRADE_ITEM5							,
	EM_TRADE_ITEM6							,
	EM_TRADE_ITEM7							,
	EM_TRADE_ITEM8							,
	EM_TRADE_ITEM9							,
	EM_TRADE_ITEM10							,
	EM_TRADE_ITEM11							,
	EM_TRADE_ITEM12							,
	EM_TRADE_ITEM13							,
	EM_TRADE_ITEM14							,
	EM_TRADE_ITEM15							,
	EM_TRADE_ITEM16							,
	EM_TRADE_ITEM17							,
	EM_TRADE_ITEM18							,
	EM_TRADE_ITEM19							,
	EM_TRADE_ITEM20							,
	EM_TRADE_ITEM21							,
	EM_TRADE_ITEM22							,
	EM_TRADE_ITEM23							,
	EM_TRADE_ITEM24							,			  
	EM_TRADE_ITEM25							,

    EM_ItemState_ENUM_FORCE_DWORD   = 0x7fffffff, 

};
//-------------------------------------------------------------------------------------
enum	ItemStateMode_ENUM
{
	EM_ItemStateMode_PickupSoulBound		,		//�ߨ��j�w
	EM_ItemStateMode_None					,		//�@�몫�~
	EM_ItemStateMode_EQSoulBound			,		//�˳ƹL
	EM_ItemStateMode_SoulBound				,		//�˳ƫ�j�w(�|���j�w)
	
};
//-------------------------------------------------------------------------------------
//�۳��d������
enum	SummonPetTypeENUM
{
	EM_SummonPetType_Normal			,	//�@���d��
	EM_SummonPetType_CultivatePet	,	//�i���d��
	EM_SummonPetType_Max			,	//�̤j�d���ƶq
};
//-------------------------------------------------------------------------------------
struct	ItemStateModeStruct
{
	union
	{
		int				_Mode;
		struct
		{
			bool	Trade				:1;			//�i���
			bool    EQSoulBound			:1;         //�˳ƸT��
			bool	ExchangeItemSystem	:1;			//�I���Ӫ����~
			bool	ItemLock			:1;			//���a�αK�X�ꪫ�~
			bool	Protect				:1;			//�˳ƫO�@�A���|�z
			bool	DepartmentStore		:1;			//���ӫ����~�X��
			bool	IgnoreLimitLv		:1;			//�����l�ε���
			bool	HideCount			:1;			//�v�üƶq

			bool	PkProtect			:1;
			bool	ClientCreate		:1;			//�Ⱥݲ��͸��
			bool	SuitSkill			:1;			//�M�˧ޯ�ϥΪ��p
			bool	Reserve11			:1;
			bool	Reserve12			:1;
			bool	Reserve13			:1;
			bool	Reserve14			:1;
			bool	Reserve15			:1;


			//(�Ȯɪ��A)
			bool	EQCannotEquipment	:1;			// true �˳Ƥ��i��(���L�ثe��b���W) false �@�몬�A
			bool	IsHQ				:1;
		};
	};

	ItemStateMode_ENUM Mode()
	{
		return (ItemStateMode_ENUM)(_Mode & 0x11);
	}
};
//-------------------------------------------------------------------------------------
//�d���ͬ���
enum CultivatePetLifeSkillTypeENUM
{
	EM_CultivatePetLifeSkillType_None	= -1 ,
	EM_CultivatePetLifeSkillType_Mining		,
	EM_CultivatePetLifeSkillType_Lumbering	,
	EM_CultivatePetLifeSkillType_Herblism	,
	EM_CultivatePetLifeSkillType_Skill4		,

	EM_CultivatePetLifeSkillType_Max	,
};
//-------------------------------------------------------------------------------------
//���~���w�q
// if OrgObjID == 0 �N��o�����O�Ū�
struct ItemFieldStruct
{
	int				OrgObjID;					//����˪���ID
	int				ImageObjectID;
	int             Serial;						//�Ǹ� ���Ѫ��~�O�_������
	int             CreateTime;					//CreateTime;
    
	int				Count;						//�ƶq

	union
	{
		int			ExValue;
		struct  
		{	
			unsigned char	OrgQuality;		//��l���~��
			unsigned char	Quality;		//�~��
			unsigned char	PowerQuality:5;	//�¤O�~��( 1 �� 10%�j��)
			unsigned char	Rare		:3;	//�B�~�W�[���}����
			unsigned char	Level		:5;	//����
			unsigned char	RuneVolume	:3;	//�Ť�e�q			
		};
	};

	int 			Durable;					//�ثe�@�[��
    ItemState_ENUM  Pos;                        //�Ҧb��m���A

	union
	{
		char		Ability[32];
		int			IntAbility[8];
		//���[��O
		struct  
		{
			short   _Inherent[6];                //�ѥͪ��[��O( �[50000���� )
			short   _Rune[4];                    //�ť�
			int		MainColor;
			int		OffColor;
		};
		
		//���I�O����m
		struct  
		{
			int		ZoneID;						//�ϰ�ID
			int		X , Y , Z ;
			int		MapID;						//�a��ID
		};
		//�ֳz���
		struct  
		{
			int		Index;						//����	
			char	Count;
			char	SelectID[20];
		}Lottery;

		//����
		struct
		{
			int		Money;
		};

		//�y�M�C��
		int		HorseColor[4];					

		//���]�ӫ~��T
		struct  
		{
			unsigned int ItemCount1 : 8;	
			unsigned int ItemID1	: 24;	
			unsigned int ItemCount2 : 8;	
			unsigned int ItemID2	: 24;	
			unsigned int ItemCount3 : 8;	
			unsigned int ItemID3	: 24;	
			unsigned int ItemCount4 : 8;	
			unsigned int ItemID4	: 24;	
			unsigned int ItemCount5 : 8;	
			unsigned int ItemID5	: 24;	
			unsigned int ItemCount6 : 8;	
			unsigned int ItemID6	: 24;	
			unsigned int ItemCount7 : 8;	
			unsigned int ItemID7	: 24;	
			unsigned int ItemCount8 : 8;	
			unsigned int ItemID8	: 24;	
			
		};

		//�°ӫ����~���W�h
		struct
		{
			int  ItemIDList[4];
			int  ItemCountList[4];
		};

		//�شӸ�T(�֤l)
		struct  
		{
			unsigned short	OrgSeedID;			//�쥻���ؤl���X+( Def_ObjectClass_Item )
			unsigned short	SeedID;				// ���[Def_ObjectClass_Item
			int				CreateTime;
			int				LastProcTime;		//�̫�B�z���ɶ�
			short			HealthPoint;		//���d�� (100��)
			short			RarePoint;			//�}���� (100��)
			short			WaterPoint;			//��� (100��)
			short			TopdressPoint;		//�i�� (100��)

			short			DecWaterPoint;		//�O���U���q(100��)	
			short			DecTopdressPoint;	//�ήƤU���q(100��)

			short			GrowRate;
			short			FeedPoint;		//������

			bool			IsLock			:1;	//��w���ܦ����y�ᤣ�|�����A�]�L�k����
			bool			IsDead			:1;

		}Plant;

		//�d�����
		struct
		{
			int CreateTime;
			int PetOrgID;
			int SkillPoint;

			unsigned char PetType;
			char Property;		//�ݩ�(�a���������t)
			unsigned char Lv;
			unsigned char TrainCount;

			unsigned short Talent;
			unsigned short STR , STA , INT , MND , AGI;	
			
			//unsigned char LifeSkill[ EM_CultivatePetLifeSkillType_Max ];
			//char PetTypeFlag[ _DEF_MAX_PET_TYPE_ / 8 ];					
		}Pet;
	};


	ItemStateModeStruct	Mode;					//���~���A

	void Init()
	{
		memset( this , 0 , sizeof(*this));
	}

	bool operator == ( const ItemFieldStruct& P ) const
	{
        //�����ˬd
        if(     OrgObjID    == P.OrgObjID 
            &&  Serial      == P.Serial    
            &&  CreateTime  == P.CreateTime 
            &&  Count       == P.Count     
			&&  Mode._Mode	== P.Mode._Mode )
            return true;

        return false;
	};

	bool operator != ( const ItemFieldStruct& P ) const
	{
		//�����ˬd
		if(     OrgObjID    == P.OrgObjID 
			&&  Serial      == P.Serial    
			&&  CreateTime  == P.CreateTime 
			&&  Count       == P.Count    
			&&  Mode._Mode	== P.Mode._Mode )
			return false;

		return true;
	};  

	//�Ψ��ˬO�_�����ƪ��~
	bool operator < ( const ItemFieldStruct& P ) const
	{
		if( OrgObjID   <  P.OrgObjID )
			return true;
		else if( OrgObjID   >  P.OrgObjID )
			return false;

		if( Serial   <  P.Serial )
			return true;
		else if( Serial   >  P.Serial )
			return false;

		if( CreateTime   <  P.CreateTime )
			return true;
		else if( CreateTime   >  P.CreateTime )
			return false;

		return false;
	};  

	
	bool IsEmpty()
	{   
        if( this == NULL )
            return true;
		if( Count == 0 && OrgObjID )
			Init();
		return OrgObjID == 0 ;
	}

	int GetCount()
	{
		if ( Mode.HideCount )
			return 1;
		return Count;
	}

	int		Inherent( int i )				
	{ 
		if( _Inherent[i] == 0 )
			return 0;
		return _Inherent[i] + _DEF_ITEM_ABILITY_DELTA_; 
	}
	void	Inherent( int i , int Value )	
	{ 
		if( Value == 0 )
			_Inherent[i] = 0;
		else
			_Inherent[i] = Value - _DEF_ITEM_ABILITY_DELTA_; 
	}
	int		Rune( int i )					
	{ 
		if( _Rune[i] == 0 )
			return 0;
		return _Rune[i] + _DEF_ITEM_ABILITY_DELTA_; 
	}
	void	Rune( int i , int Value )		
	{ 
		if( Value == 0 )
			_Rune[i] = 0;
		else
			_Rune[i] = Value - _DEF_ITEM_ABILITY_DELTA_; 
	}

	bool CheckInherent( int Value )
	{
		for( int i = 0 ; i < 6 ; i++ )
		{
			if( Inherent(i) == Value )
				return true;
		}
		return false;
	}
};
//-------------------------------------------------------------------------------------
struct GambleItemStateStruct
{
	int				BodyItemPos;
	int				ItemVersionID;
	int				GambleTableID;
	int				StatePos;
	int				StateID;

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
		GambleTableID = -1;

	};
};

//-------------------------------------------------------------------------------------
//��X���~�Ȧs���c
struct SellItemFieldStruct
{
	ItemFieldStruct Item;
	int				Money;			//��X����

	bool operator == ( const SellItemFieldStruct& P ) const
	{
		//�����ˬd
		if(     Item    == P.Item 
			&&  Money   == P.Money    )
			return true;

		return false;
	};
};
//-------------------------------------------------------------------------------------
// ��ܨt�ε���

struct SpeakOptionStruct
{
	int		iNPCID;
	int		iIconID;
	//char	szOption[64];
	//char	szLuaFunc[64];
	StaticString< _MAX_SPEAKOPTION_SIZE_ > szOption;
	StaticString< _MAX_SPEAKOPTION_SIZE_ > szLuaFunc;
};

struct SpeakStruct
{
	SpeakStruct() { Reset(); }

	void	Reset()			
	{ 
		iSpeakNPCID = 0;
		iLoadQuest	= 0;
		SpeakDetail.Clear();  
		SpeakOption.Clear();
	}

	int		iSpeakNPCID;
	int		iLoadQuest;

	StaticString< _MAX_SPEAKDETAIL_SIZE_ >								SpeakDetail;
	StaticVector< SpeakOptionStruct, _MAX_SPEAKOPTION_COUNT_ >			SpeakOption;
	//vector< SpeakOptionStruct>											SpeakOption;
};	
//-------------------------------------------------------------------------------------
// �۸O�t�θ��
//-------------------------------------------------------------------------------------
struct ScriptBorderStruct
{
	ScriptBorderStruct()
	{
		iQuestID = 0;
	}

	void Init()
	{
		iQuestID	= 0;
		iPageCount	= 0;

		//for( int i = 0; i < _MAX_SPEAKOPTION_COUNT_; i++ )
		//	sBorderPage[i]->Clear();
	};

	int												iQuestID;
	int												iPageCount;
	//StaticString<  _MAX_SPEAKDETAIL_SIZE_ >			sBorderPage[ _MAX_SPEAKOPTION_COUNT_ ];
	//string											sBorderPage;
	StaticString<  _MAX_LUA_FUNTIONNAMESIZE_ >		sTitle;
	StaticString<  _MAX_LUA_FUNTIONNAMESIZE_ >		sTextureFile;

	//StaticString<  _MAX_LUA_FUNTIONNAMESIZE_ >		sLuaAcceptQuest;
	//StaticString<  _MAX_LUA_FUNTIONNAMESIZE_ >		sLuaAfterRead;
};

//-------------------------------------------------------------------------------------
// �@���Υ��ȸ��
//-------------------------------------------------------------------------------------
enum ENUM_SCRIPTSTATUS
{
	EM_SCRIPT_NONE		= 0,
	EM_SCRIPT_RUNNING	= 1,

};
//-------------------------------------------------------------------------------------
enum ENUM_SCRIPTSTATUS_LOCKTYPE
{
	ENUM_SCRIPTSTATUS_LOCKTYPE_NOLOCK	= 0,
	ENUM_SCRIPTSTATUS_LOCKTYPE_PERSONAL = 1,
	ENUM_SCRIPTSTATUS_LOCKTYPE_PARTY	= 2,
	ENUM_SCRIPTSTATUS_LOCKTYPE_RAID		= 3,	
};
//-------------------------------------------------------------------------------------
struct ScriptStruct 
{
	ENUM_SCRIPTSTATUS				emMode;
	
	ENUM_SCRIPTSTATUS_LOCKTYPE		emLockType;		// ���w�S�w�H���ζ���~���I�諸����
	int								iLockDBID;		// ���w�S�w�H���ζ���~���I�諸����N��

};

//-------------------------------------------------------------------------------------
enum	PET_ACTION_ENUM
{
    EM_PET_NONE				,   // �ثe�S�R�O
    EM_PET_STOP				,
    EM_PET_FOLLOW			,
    EM_PET_ATTACK			,
    EM_PET_ATTACKOFF		,
    //EM_PET_PROTECT			,
	EM_PET_STRICKBACK		,
	EM_PET_STRICKBACK_OFF	,
    EM_PET_GUARD			,
	EM_PET_SPELLMAGIC		,


    EM_PET_PROC_STATE_ENUM_FORCE_DWORD   = 0x7fffffff, 
};

struct PetSkillStruct
{
	int		MagicColID;		//�ޯ�
	int		MagicLv;		//�ޯ൥��
	bool	IsActive;		//�۰ʬI�i
	PetSkillStruct()
	{
		MagicColID = 0;
		MagicLv = 0;
		IsActive = false;

	}
};

struct PetStruct
{
//	bool				IsPet;			//��NPC���d��
    PET_ACTION_ENUM		Action;			//�ثe���檺�欰
    int					PetID;			//�d�����X
    int					TargetID;		//�B�z���ؼ�
	int					MagicID;		//���ͪ��k�N

	StaticVector< PetSkillStruct , _MAX_PET_SKILL_COUNT_ >	Skill;	//�d���ޯ�

    PetStruct()
    {
        Init();
    }

    void Init()
    {
		//ActiveSkill = 0;
        PetID = -1;
        TargetID = -1;
		Action	= EM_PET_FOLLOW;
		Skill.Clear();
    }
};

struct SummonPetInfoStruct
{
	//�d�����
	SummonPetTypeENUM		Type;						//�۳�����		(�d������)
	int						MagicBaseID;					
	//�D�H���
	PetStruct				Info[EM_SummonPetType_Max];	//�ۥX�Ӫ��d��	(�D�H����)

	void	Init()
	{
		memset( this , 0 , sizeof(*this) );
	}
};
//-------------------------------------------------------------------------------------
//���͸��
struct RaiseModeStruct
{
	union
	{
		int Mode;
		struct  
		{
			bool	MagicRaiseEnabled : 1;
			bool	ExpProtect		  : 1;
			bool	EqProtect		  : 1;	
		};
	};
};

struct RaiseInfoStruct
{
	RaiseModeStruct	Mode;
	int				ExpRate;		//�^�_exp�����
	int				ZoneID;
	float			RevX;
	float			RevY;
	float			RevZ;

	int 			ExpDownRate;
	int 			DebtExpRate;
	int 			DebtTpRate;

	void Init()
	{
		Mode.Mode = 0;
		ExpRate = 0;
		ExpDownRate = 0;
		DebtExpRate = 0;
		DebtTpRate = 0;
	}
};

//-------------------------------------------------------------------------------------
struct		RoleTableStruct
{
    union
    {
        float	Skill[_MAX_SKILL_COUNT_];
        struct
        {
            float		BeatPro;			
            float		BladePro;		
            float		SwordPro;		
            float		AxeHammerPro;
            float		StickPro;		
            float		PikePro;			
            float		RodPro;			
            float		DaggerPro;		
            float		EctPro;			
            float		BowPro;			
            float		RefinePro;		
            float		MeditationPro;	
        };
    };
    int MaxExp;
};
//-------------------------------------------------------------------------------------
enum	MAGIC_PROC_STATE_ENUM
{
	EM_MAGIC_PROC_STATE_NORMAL				    ,	//�@��D�I�k���A
	EM_MAGIC_PROC_STATE_PERPARE				    ,	//�ǳƬI�k��
	EM_MAGIC_PROC_STATE_SHOOT					,	//�g�X
	EM_MAGIC_PROC_STATE_SPELL				    ,	//�I�k��
	EM_MAGIC_PROC_STATE_INTERRUPT				,	//�I�k���_
	EM_MAGIC_PROC_STATE_ENDSPELL				,	//�I�k�赲��
    EM_MAGIC_PROC_STATE_EM_FORCE_DWORD   = 0x7fffffff, 
};
//-------------------------------------------------------------------------------------
/*
enum	MAGIC_VALUE_TYPE_ENUM
{
	EM_MAGIC_VALUE_NONE			,	//���l��
	EM_MAGIC_VALUE_REPLACE		,	//���N
	EM_MAGIC_VALUE_ADD			,	//�[�W
	EM_MAGIC_VALUE_MUL			,	//��
};
//-------------------------------------------------------------------------------------
//�k�N�@���ƭȳ]�w
struct  MagicScriptValueStruct
{
	float					Value;
	MAGIC_VALUE_TYPE_ENUM	Type;		
};
*/
//-------------------------------------------------------------------------------------
//�I�k�����A��T
struct MagicProcInfo
{
	int						SerialID;			//�k�N�Ǹ�

	MAGIC_PROC_STATE_ENUM	State;
	int						TargetID;			//�ؼ�
	int						MagicCollectID;		//�k�N���XID
	
	int						ProcTime;			//����ɶ�
	int						TotalSpellTime;		//�һݬI�k�ɶ�

	float					BeginX;				//�}�l�I�k����m
	float					BeginY;				//�}�l�I�k����m
	float					BeginZ;				//�}�l�I�k����m
	bool					IsMove;

	float					TargetX;			//�ؼЦ�mx
	float					TargetY;			//�ؼЦ�my
	float					TargetZ;			//�ؼЦ�mz

    int						UseItem;			//�ϥΪ����~
	short					UseItemPos;			//���~����m
    short                   UseItemType;        // 0 ���� 1 �Ȧ� 2 EQ
	//-------------------------------------------
	bool					IsSpellCheckOK;		//�i�H�I�k 
	bool					IsSuccess;			//�I�k���\

	int						SpellCount;			//�٭n�I�i�X��
	int						NextSpellTime;		//�U���I�i���ɶ�

	//-------------------------------------------
	//�k�N�D��i�]�w�ƭ�
	bool					MagicEnabled[_MAX_MAGICCOLLECT_GROUP_COUNT_][_MAX_MAGICCOLLECT_COUNT_];	//���Ǫk�N��Enabled ( ��l���} �@���i���� )
	float					Coldown;
	MagicSpellCostTypeENUM	CostType;
	float					CostValue;
	MagicSpellNeedTypeENUM	NeedType;
	float					NeedValue;
	//�k�N����]�w�ƭ�
	float					SpellTime;			//�I�k�ɶ�
	float					HitRate;			//�R���v(Shooting Average)
	int						MagicLv;			//�k�N����
	float					EffectTime;			//�v�T�ɶ�
	bool					IsSystemMagic;		//
	bool					IsPayCost;			//�w�g���L����
	bool					IsCheckUseItem;		
	bool					IsNoRebound;		
	//----------------------------------------------
	//�ϥΪ����~���]�w���y�X�C��
	int						HorseColor[4];

	int						BaseShootDelayTime;	//�̧C�k�N���橵��( �d�����@�� )

	//�]�w�k�N�Ǹ�
	int SetSerialID()
	{
		static int ID = 0;
		SerialID = ID++;
		return SerialID;
	}

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
		InitMagicEnabled();
	}

	void InitMagicEnabled()
	{
		for( int i = 0 ; i < _MAX_MAGICCOLLECT_GROUP_COUNT_ ; i ++ )
			for( int j = 0 ; j < _MAX_MAGICCOLLECT_COUNT_ ; j ++ )
				MagicEnabled[i][j] = true;
	}

/*
	bool CheckInterrupt( float x , float z)
	{
		if(		State != EM_MAGIC_PROC_STATE_PERPARE 
			&&	State != EM_MAGIC_PROC_STATE_SHOOT )
			return false;

		//if(		abs( int( x - BeginX ) ) > 10 
	//		||	abs( int( z - BeginZ ) ) > 10 )
		if( IsMove )
		{
			State = EM_MAGIC_PROC_STATE_INTERRUPT;
			return true;
		}

		return false;
	};
*/
	void ClsUseItem()
	{
		UseItem		= 0;
		UseItemPos	= -1;
        UseItemType	= -1;
	};
		
	
};
//-------------------------------------------------------------------------------------
#define _DEF_BAG_PAGE3_BEGIN_POS_	(30*2 + _MAX_BODY_EX_COUNT_ + _MAX_BODY_MAGIC_BOX_COUNT_ )
#define _DEF_BAG_PAGE4_BEGIN_POS_	(30 + _DEF_BAG_PAGE3_BEGIN_POS_ )
#define _DEF_BAG_PAGE5_BEGIN_POS_	(30 + _DEF_BAG_PAGE4_BEGIN_POS_ )
#define _DEF_BAG_PAGE6_BEGIN_POS_	(30 + _DEF_BAG_PAGE5_BEGIN_POS_ )

//����P�Ȧ���
struct BodyItemStruct
{
	union
	{
	    ItemFieldStruct     Item[ _MAX_BODY_COUNT_];
		struct
		{
			ItemFieldStruct     ItemEx[ _MAX_BODY_EX_COUNT_ ];						//�ӫ��]
			ItemFieldStruct     ItemMagicBox[ _MAX_BODY_MAGIC_BOX_COUNT_ ];			//����_��
			ItemFieldStruct     ItemBase[ _MAX_BODY_COUNT_ - _MAX_BODY_EX_COUNT_ - _MAX_BODY_MAGIC_BOX_COUNT_ ];	//���W�]
		};
	};
    int                 Count;
    int                 Money;
	int					Money_Account;

    void Init()
    {
        memset( this , 0 , sizeof(*this) );
    };
};
//-------------------------------------------------------------------------------------
#define _DEF_BANK_PAGE2_BEGIN_POS_	( 40 )
#define _DEF_BANK_PAGE3_BEGIN_POS_	( 40*2 )
#define _DEF_BANK_PAGE4_BEGIN_POS_	( 40*3 )
#define _DEF_BANK_PAGE5_BEGIN_POS_	( 40*4 )
#define _DEF_BANK_MALL_BEGIN_POS_	200
#define _DEF_BANK_MALL_COUNT_		100

//����P�Ȧ���
struct BankItemStruct
{
	ItemFieldStruct     Item[ _MAX_BANK_COUNT_];
	int                 Count;
	int                 Money;
	int					Money_Account;

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	};
};
//-------------------------------------------------------------------------------------
//�@���]�w�i�ϥΪk�N
//struct Plot
//-------------------------------------------------------------------------------------
struct TreasureBoxStruct
{
	int	Count;
	int					OwnerDBID[_MAX_BODY_COUNT_];
	ItemFieldStruct     Item[ _MAX_BODY_COUNT_ ];
	bool				Lock[ _MAX_BODY_COUNT_ ];
	int	LiveTime;				//�ଡ�h�[
	int	DeadTime;				//���`���ɶ�
	int TreasureOwnerDBID;		//�֦���
	int	TreasurePartyID;		//����ID
	int	CheckSerialID;			//���a���������ˬd��
	bool IsPetLoot;				//	
	

	TreasureBoxStruct( )
	{
		memset( this , 0 , sizeof( *this ) );
	}
};
//-------------------------------------------------------------------------------------
#define _DEF_EQ_BACKUP_BASE_	100
enum    EQWearPosENUM
{
    EM_EQWearPos_None       = -1 , 
    EM_EQWearPos_Head       ,//0
    EM_EQWearPos_Gloves	    ,//1
    EM_EQWearPos_Shoes		,//2
    EM_EQWearPos_Clothes	,//3
    EM_EQWearPos_Pants		,//4
    EM_EQWearPos_Back		,//5
    EM_EQWearPos_Belt		,//6
    EM_EQWearPos_Shoulder	,//7
    EM_EQWearPos_Necklace   ,//8
    EM_EQWearPos_Ammo       ,//9
	EM_EQWearPos_Bow        ,//10
    EM_EQWearPos_Ring1      ,//11
    EM_EQWearPos_Ring2      ,//12
    EM_EQWearPos_Earring1   ,//13
    EM_EQWearPos_Earring2   ,//14
    EM_EQWearPos_MainHand	,//15
    EM_EQWearPos_SecondHand ,//16
	EM_EQWearPos_Manufactory,//17
	EM_EQWearPos_MagicTool1	,//18
	EM_EQWearPos_MagicTool2	,//19
	EM_EQWearPos_MagicTool3	,//20
	EM_EQWearPos_Ornament	,//21
	EM_EQWearPos_MaxCount	,


	EM_EQWearPos_BK_Head       = _DEF_EQ_BACKUP_BASE_,//0
	EM_EQWearPos_BK_Gloves	    ,//1
	EM_EQWearPos_BK_Shoes		,//2
	EM_EQWearPos_BK_Clothes		,//3
	EM_EQWearPos_BK_Pants		,//4
	EM_EQWearPos_BK_Back		,//5
	EM_EQWearPos_BK_Belt		,//6
	EM_EQWearPos_BK_Shoulder	,//7
	EM_EQWearPos_BK_Necklace   	,//8
	EM_EQWearPos_BK_Ammo       	,//9
	EM_EQWearPos_BK_Bow        	,//10
	EM_EQWearPos_BK_Ring1      	,//11
	EM_EQWearPos_BK_Ring2      	,//12
	EM_EQWearPos_BK_Earring1   	,//13
	EM_EQWearPos_BK_Earring2   	,//14
	EM_EQWearPos_BK_MainHand	,//15
	EM_EQWearPos_BK_SecondHand 	,//16
	EM_EQWearPos_BK_Manufactory	,//17
	EM_EQWearPos_BK_MagicTool1	,//18
	EM_EQWearPos_BK_MagicTool2	,//19
	EM_EQWearPos_BK_MagicTool3	,//20
	EM_EQWearPos_BK_Ornament	,//21

    EM_EQWearPosENUM_FORCE_DWORD   = 0x7fffffff, 
};
//-------------------------------------------------------------------------------------
struct EQStruct
{
	union
	{
        ItemFieldStruct Item[ EM_EQWearPos_MaxCount ];
        
        
		struct 
		{
			ItemFieldStruct Head			;//�Y
			ItemFieldStruct Gloves	    	;//��M
			ItemFieldStruct Shoes			;//�c�l
			ItemFieldStruct Clothes		    ;//�W��
			ItemFieldStruct Pants			;//�Ǥl
			ItemFieldStruct Back			;//�I��
			ItemFieldStruct Belt			;//�y�a
            ItemFieldStruct Shoulder		;//�ӥ�
            ItemFieldStruct Necklace        ;//����
            ItemFieldStruct Ammo            ;//�u��
            ItemFieldStruct Bow             ;//�}

            ItemFieldStruct Ring1;          ;//�٤l
            ItemFieldStruct Ring2;          ;
            ItemFieldStruct Earring1        ;//�չ�	
            ItemFieldStruct Earring2        ;			

            ItemFieldStruct MainHand		;//�D��
            ItemFieldStruct SecondHand		;//�Ƥ�

			ItemFieldStruct Manufacture     ;//�Ͳ��s�y���
			ItemFieldStruct MagicTool1		;
			ItemFieldStruct MagicTool2		;
			ItemFieldStruct MagicTool3		;
			ItemFieldStruct Ornament		;
			
		};
	};

	void	Init()
	{
		memset( &Item , 0 , sizeof(Item) );
	};
};
//-------------------------------------------------------------------------------------
struct DestroyItemLogStruct
{
	ItemFieldStruct ItemList[ DEF_MAX_DESTROY_ITEM_LOG_COUNT ];
	void	Push( ItemFieldStruct Item )
	{
		for( int i = DEF_MAX_DESTROY_ITEM_LOG_COUNT-1 ; i > 0 ; i-- )
			ItemList[i] = ItemList[i-1];
		ItemList[0] = Item;
	};
};
//-------------------------------------------------------------------------------------
struct ShowEQStruct
{
	union
	{
		int _Value;
		struct
		{
			bool Head		:1;//�Y
			bool Gloves	    :1;//��M
			bool Shoes		:1;//�c�l
			bool Clothes	:1;//�W��
			bool Pants		:1;//�Ǥl
			bool Back		:1;//�I��
			bool Belt		:1;//�y�a
			bool Shoulder	:1;//�ӥ�
			bool Necklace   :1;//����
			bool Ammo       :1;//�u��
			bool Bow        :1;//�}
			bool Ring1      :1;//�٤l
			bool Ring2      :1;
			bool Earring1   :1;//�չ�	
			bool Earring2   :1;			

			bool MainHand	:1;//�D��
			bool SecondHand	:1;//�Ƥ�

			bool Manufacture:1;//�Ͳ��s�y���
			bool MagicTool1	:1;
			bool MagicTool2	:1;
			bool MagicTool3	:1;
			bool Ornament	:1;
		};
	};

};
//-------------------------------------------------------------------------------------
#define _DEF_MAX_GOODEVIL_BATTLE_INFO_COUNT_ 30
#define	_DEF_MAX_GOODEVIL_ATK_LIVETIME_		(30*60)
enum GoodEvilAtkInfoTypeENUM
{
	EM_GoodEvilAtkInfoType_Empty	,	//�Ū����
	EM_GoodEvilAtkInfoType_Atk		,	//����
	EM_GoodEvilAtkInfoType_Def		,	//���u

};

struct GoodEvilAtkInfoStruct
{
	int		PlayerDBID;
	int		Time;
	GoodEvilAtkInfoTypeENUM Type;
};
//���c¾�B�z�Ȧs���
struct GoodEvilTempStruct
{
	StaticVector< GoodEvilAtkInfoStruct , _DEF_MAX_GOODEVIL_BATTLE_INFO_COUNT_ >	BattleInfoList;
//	float	GoodEvilPoint;		//�i�W�[�����c���I��
};

//-------------------------------------------------------------------------------------
//�ثe�欰�Ҧ����
//-------------------------------------------------------------------------------------
enum	RoleOpenMenuTypeENUM
{
	EM_RoleOpenMenuType_None			,
	EM_RoleOpenMenuType_Shop			,
	EM_RoleOpenMenuType_Bank			,
	EM_RoleOpenMenuType_AC				,
	EM_RoleOpenMenuType_Mail			,
	EM_RoleOpenMenuType_ChangeJob		,
	EM_RoleOpenMenuType_Billboard		,
	EM_RoleOpenMenuType_CreateNewGuild	,
	EM_RoleOpenMenuType_GuildContribution,
//	EM_RoleOpenMenuType_GuildShop		,
	EM_RoleOpenMenuType_ExchangeLottery ,
	EM_RoleOpenMenuType_BuyLottery		,
	EM_RoleOpenMenuType_VisitHouse		,
	EM_RoleOpenMenuType_EQCombin		,
	EM_RoleOpenMenuType_PlotGiveItem	,
	EM_RoleOpenMenuType_AccountBag		,
	EM_RoleOpenMenuType_VisitGuildHouse	,
	EM_RoleOpenMenuType_EqGamble		,
	EM_RoleOpenMenuType_MagicStoneExchange	,
	EM_RoleOpenMenuType_SuitSkill			,
	EM_RoleOpenMenuType_Rare3EqExchangeItem	,
};

struct		RoleActionStruct
{
	union
	{
		unsigned int		_Action;
        struct      
        {
            short   _LowAction;
            short   _HiAction;
        };
		struct
		{
            //�e16���ܤ��e���
			unsigned int	SrvSetPos			:1;		//Server�M�w����m
			unsigned int	Reserve2			:1;		
			unsigned int	Reserve_Spell		:1;		//�I�k
			unsigned int	Follow	        	:1;		//���H
            unsigned int	Login	        	:1;		//�Ĥ@���n�J
            unsigned int	SendAllZoneObj  	:1;		//�e���쪺����
            unsigned int	ChangeZone      	:1;		//�����ϹL
            unsigned int	NoReturnAttackPoint :1;

			unsigned int	ChangeParallel		:1;
            unsigned int	Reserve9_15			:7;

			unsigned int	OpenType		:5;		//RoleOpenMenuTypeENUM �}�_����������
			unsigned int	Trade			:1;		//���
			unsigned int	Dead			:1;		//���`
			unsigned int	Walk			:1;		//�]�Bor����

            unsigned int 	AttackMode      :1;     //������(Cli���������A)
			unsigned int	Sit				:1;
			unsigned int	DisableClick	:1;		//����@����, �Τ��b�P�બ�A�U. �����\ Client ����ʧ@
			unsigned int	DisableQuest	:1;		// �������� NPC �������Ȫ����A ( ��� NPC ���� SCRIPT ��, �� SCRIPT �����Υ��} )
			unsigned int	PK				:1;		//pk���A
			unsigned int	Attack			:1;		//����
			unsigned int	Unholster		:1;		//���X�Z��
		};
	};
};
//-------------------------------------------------------------------------------------
//���ϰ�w�ɪ��a��s���
struct PlayerBackupInfoStruct
{
	float	LX , LZ;		//�̫��s���y�Ц�m
	int		LHPMPSPSum;		//�̫�@�� MaxHP , MaxMP HP MP SP ���`�M�� , �ΨӽT�w�O�_�n��s�y��
	int		BuffIDCheckSum;	//BuffID ���[�`��
};

//-------------------------------------------------------------------------------------
//���ϥi�d�M�����a���A
//-------------------------------------------------------------------------------------
struct PlayerStateStruct
{
	union
	{
		int		_State;
		struct
		{
			bool	FindParty			:1;			//�䶤��
			bool	AFK					:1;			//���}
			bool	Dig					:1;			//���q

			bool	HasParty			:1;
			bool	Reserve4			:1;
			bool	Reserve5			:1;
			bool	Reserve6			:1;
			bool	Reserve7			:1;
			bool	Reserve8_15			:8;

			//�t�γ]�w
			bool	HonorParty			:1;			//�a�A�ն��Ҧ�
		};
	};
};
//-------------------------------------------------------------------------------------
//�����㹳���
//-------------------------------------------------------------------------------------
struct PlayerGraphStruct
{
	int					                    OrgObjID;						//�����lID
    StaticString< _MAX_NAMERECORD_SIZE_ >   Name;
	ObjectModeStruct                    	Mode;   
	int		                                MaxHP;
	int		                                MaxMP;
	int		                                MaxSP;
	int		                                MaxSP_Sub;
	int		                                HP;
	int		                                MP;
	int		                                SP;
	int		                                SP_Sub;
	float	                                MoveSpeed;
	int				                    	Level;							//���󵥯�
    int                                     NpcQuestID;
    short                                   TouchPlot_Range;
    short                                   RangePlot_Range;
    RoleActionStruct		                Action;			                //�ثe����ʪ��A
	Voc_ENUM								Voc;							//�D¾
	Voc_ENUM								Voc_Sub;						//��¾
	Race_ENUM								Race;

	int										Level_Sub;						//��¾����	
	int										TitleID;						//�Y��
	int										GuildID;						//���|ID
	int										MinimapIcon;
	int										CursorType;						// ��ڤ��P NPC ����, �]�w�������S�����
	float									vX , vY , vZ;					//�����V�V�q
	int										IdleMotionID;				
	int										CliActionID;					//Client �ݪ����A�]�w���
	PlayerStateStruct						AllZoneState;					//���Ϫ��A���
	bool									IsShowTitle;					//�O�_����Y��
	MagicEffectStruct						MagicEffect;
	Sex_ENUM								Sex;
	GoodEvilTypeENUM						GoodEvilType;
//	int										ImageObjID;						//�㹳������
	int										iForceFlagID;					//�j��I�t���X�l
	int										iDefIdleMotion;					//�w�]���̭I�� Idle Motion
	
	SystemFlagStruct						SysFlag;
};
//-----------------------------------------------------------------------------------
// Party ������Ƶ��c
//-----------------------------------------------------------------------------------
struct PartyMemberModeStruct 
{
	union
	{
		int			_Mode;
		struct  
		{
			bool	IsAssistant		: 1;		//�U�z		�i�n�Ъ��a
			bool	IsMainTank		: 1;		//�Z�J
			bool	IsMainAttack	: 1;		//�D���
		};
	};
};

struct PartyMemberInfoStruct
{
	int		MemberID;
	int		PartyNo;			//�p��ID
	StaticString <_MAX_NAMERECORD_SIZE_> Name;	
	union
	{
		int		GItemID;	// -1 �N��U�u���A
		struct
		{
			short   ItemID;            
			short   ZoneID;
		};
	};
	int DBID;

	int				Voc;								//¾�~
	int				Voc_Sub;							//��¾�~
	int				Level;
	int				Level_Sub;
	int				Sex;

	PartyMemberModeStruct Mode;
	PlayerStateStruct	State;		//���⪬�A
	int				ParallelID;

	void Init()
	{
		memset( this , 0 , sizeof(*this));
	}
};

//////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------------------------
enum GroupObjectTypeEnum
{
	EM_GroupObjectType_SysChannel    = 0  ,	//�t��
	EM_GroupObjectType_SysZoneChannel   ,	//�C�Ӱϰ쳣����
	EM_GroupObjectType_PlayerChannel    ,	//���a��
	EM_GroupObjectType_Party            ,	//����
	EM_GroupObjectType_Guild            ,	//�u�|

	EM_GroupObjectType_Count            ,   //���κؼ�
	EM_GroupObjectType_MAX        = 0xffffffff    ,
};

enum	PartyItemShareENUM
{
	EM_PartyItemShare_Roll		,
	EM_PartyItemShare_Assign	,
	EM_PartyItemShare_InOrder	,
};

enum	PartyTypeENUM
{
	EM_PartyType_Party		,
	EM_PartyType_Raid		,
};

struct PartyBaseInfoStruct
{
	int				PartyID;
	PartyTypeENUM	Type;								//��������
	StaticString <_MAX_NAMERECORD_SIZE_> LeaderName;	//����
	StaticString <_MAX_NAMERECORD_SIZE_> AttackName;	//������
	StaticString <_MAX_NAMERECORD_SIZE_> ShareName;		//���t��

	PartyItemShareENUM	ItemShareType;	//���ɪ��Ҧ�
	int					RollTypeLV;		//�ݭn�Y��l������ or ���t����
	bool				Roll_CanUse;	//�i�ϥΪ̤~�i�H�Y��l or ���t����
	short				InstanceLv;		// �ƥ�����

	PartyBaseInfoStruct( )
	{
		PartyID = -1;
		ItemShareType = EM_PartyItemShare_InOrder;
		RollTypeLV = 1;
		Roll_CanUse = false;
		Type = EM_PartyType_Party;
		InstanceLv = 0;
	}
};
//Party ��� 
struct PartyInfoStruct
{
	PartyBaseInfoStruct Info;
	vector< PartyMemberInfoStruct > Member;
};
//-------------------------------------------------------------------------------------
//�����m��Ʃw�N
//-------------------------------------------------------------------------------------
struct RolePosStruct
{
    float   X , Y , Z ;
    float   Dir;
};
//-------------------------------------------------------------------------------------
//����ƭȸ��
//-------------------------------------------------------------------------------------
struct BaseAbilityStruct
{
	int		EXP;
	int		TotalTpExp;			//
	int		TpExp;				//�k�N�ޯ�g����I��
	
	int		DebtExp;			//�g��ȭt��
	int		DebtTP;				//TP�t��
	int		AddExp;								//�B�~�W�[Exp
	int		AddTp;								//�B�~�W�[Tp
	int		Level;

	int		Point;				//�i�t�m�I��
	int		PlayTime;			//�Φ�¾�~�C�����ɶ�(����)

    int 	STR;			    // �O�q
    int 	STA;			    // �@�O
    int 	MND;			    // ���z
	int     INT;                // �o��
    int 	AGI;			    // �ӱ�


	union
	{
		float	AllSkillLv[ _MAX_SPSkill_COUNT_ + _MAX_NormalSkill_COUNT_ ];
		struct  
		{
			float	SPSkill		[ _MAX_SPSkill_COUNT_ ];			//sp�ޯ൥��
			float	NormalSkill	[ _MAX_NormalSkill_COUNT_ ];		//�@��k�N�ޯ൥��
		};
	};


	int		TotalPoint()
	{
		return Point + STR + STA + MND + INT + AGI;
	};
	int		ResetPoint()
	{
		Point = TotalPoint();
		STR = 0;
		STA = 0;
		MND = 0;
		INT = 0;
		AGI = 0;
		return Point;
	};
};
//-------------------------------------------------------------------------------------
// �ثe�ҷ|�k�N���c
//-------------------------------------------------------------------------------------

struct SkillStruct
{
    union
    {
        int AllSkill[ _MAX_SPSkill_COUNT_+_MAX_NormalSkill_COUNT_+_MAX_NormalSkill_COUNT_ +  _MAX_EQ_Skill_COUNT_ + _MAX_Lua_Skill_COUNT_ ];
        struct
        {
			union
			{
				int JobSkill[ _MAX_SPSkill_COUNT_+_MAX_NormalSkill_COUNT_+_MAX_NormalSkill_COUNT_ ];
				struct
				{
					int SP [ _MAX_SPSkill_COUNT_ ];				//¾�~�M�ݧޯ�
					int MainJob[ _MAX_NormalSkill_COUNT_ ] ;	//�D¾�@��ޯ�
					int	SubJob[ _MAX_NormalSkill_COUNT_ ];		//��¾�@��ޯ�
				};
			};
			union
			{
				int	OtherSkill[ _MAX_EQ_Skill_COUNT_ + _MAX_Lua_Skill_COUNT_];
				struct
				{
					int	EqSkill[ _MAX_EQ_Skill_COUNT_ ];		//�]�˳ƩμƭȰʺA�Ӫ��ޯ�
					int LuaSkill[ _MAX_Lua_Skill_COUNT_ ];		//�] �@�� �ʺA�Ӫ��ޯ� (���Ϯ���)
				};
			};

        };
    };   
};
//-------------------------------------------------------------------------------------
//AI ��Ƶ��c
struct  NPC_AI_Struct
{
    NPCAIActionTypeENUM		ActionType;		    //�欰�Ҧ�
    NPCAIActionTypeENUM		LActionType;	    //�欰�Ҧ�

	int		TargetID;				//�����θ��H�ؼ�
	int		LTargetID;				//�̫�@���������ؼ�(�Ψ��˴��O�_�ؼЦ���)
	unsigned int	NextAtkTime;			//�U�@���i�����ɶ�
    int     AttackCount;            //�����ֿn����

    //�ɶ��H0.1�����
    int     AddAtkTime;
    int     NextMainAtk;            //�U�@���D�����
    int     NextSecAtk;             //�U�@���Ƥ����
	int		DoubleAttackCount;

	int		KeepDistance;			//�O���Z��

	CampID_ENUM		CampID;			//���ݰ}��
};
//-------------------------------------------------------------------------------------
//�Ǫ��Q���쪺��T
//(������)
struct  NPCHateStruct
{
	int		DBID;
	int		ItemID;
	float	HitPoint;
	float	HatePoint;
	float	TempHatePoint;
	int		PartyID;

    void Init()
    {
        DBID        = -1;
        ItemID      = -1;
        HitPoint    = 0;
        HatePoint   = 0;
		TempHatePoint = 0;
		PartyID		= -1;
    };

	float TotalHatePoint()
	{
		return HatePoint + TempHatePoint;
	}
};
//-------------------------------------------------------------------------------------
//�Ǫ������T �A �Ǫ� ai �ϥ�
struct NPCHateList
{
    StaticVector< NPCHateStruct , _MAX_HATELIST_SIZE_ >     Hate;
	int     MaxHitPoint;					//�̤j�����O
	int		MaxHitLv;						//�����̳̤j������
	int		BeginAtkPartyID;
	int		BeginAtkDBID;

	void Init( )
	{
		BeginAtkPartyID = -1;
		BeginAtkDBID = -1;
        MaxHitPoint = 0;
		MaxHitLv = 1;
        Hate.Clear();
		//memset( this , -1 , sizeof(*this) );
	}

    NPCHateStruct*     GetMaxHit( )                  //��X����̦h���H
    {
		map< int , int > PartyHitPointMap;

		for( int i = 0 ; i < Hate.Size() ; i++ )
		{
			if( Hate[i].PartyID <=0 )
				continue;
			PartyHitPointMap[ Hate[i].PartyID ] += Hate[i].HitPoint;
		}


        int MaxHit = -1;
        int MaxHitID = -1;
        for( int i = 0 ; i < Hate.Size() ; i++ )
        {
			int HitPoint = Hate[i].HitPoint;
			if( Hate[i].PartyID > 0 )
			{
				HitPoint = PartyHitPointMap[ Hate[i].PartyID ];
			}

            if( HitPoint > MaxHit )
            {
                MaxHit   = Hate[i].HitPoint;
                MaxHitID = i;
            }
        }

        if( MaxHitID == -1 )
            return NULL;

        
        return &Hate[ MaxHitID ];
    
    }

	NPCHateStruct*     GetMaxHate( )                  //��X�̫몺�H
	{
		int MaxHate = -1;
		int MaxHateID = -1;
		for( int i = 0 ; i < Hate.Size() ; i++ )
		{
			if( Hate[i].TotalHatePoint() > MaxHate )
			{
				MaxHate   = Hate[i].TotalHatePoint();
				MaxHateID = i;
			}
		}

		if( MaxHateID == -1 )
			return NULL;

		return &Hate[ MaxHateID ];

	}
    
};
//-------------------------------------------------------------------------------------
// �ݩw�ɳB�z���ƥ�
//( �Y������Ʀ��ܰ� )
//-------------------------------------------------------------------------------------
struct		RoleUpdateEvent
{
	union
	{
		unsigned int		_Event;
		struct
		{
			bool	Bank			:1;		
			bool	Body			:1;		
			bool	Eq				:1;
			bool	Recalculate_Buff:1;		//���s�p��Buff
			bool	Recalculate_All	:1;		//�Ҧ��ƭȭ��s�p��
			bool	ExpChange		:1;
			bool	LvChange		:1;		//Save
			bool	VocChange		:1;		
            bool	ReSetTalbe		:1;
            bool    Trade           :1;
            bool    HPMPSP          :1;
            bool    MoveSpeed       :1;
			bool	AllZoneInfoChange :1;	//���϶��n���D�������Ƨ���

			//--------------------------
			bool	FriendListModify:1;		//�ۤv����T�����ܭn�q��Chat ����q��Client
			bool	SkillKeyItemChange:1;	//�ޯ�����������n���~����
			bool	SkillValueChange:1;		//�ޯ�����������n���~����
			bool	OnAttackPlayer  : 1;	//�������a
			bool	OnKill			: 1;	//��������
			bool	AccountMoneyLockInfoChange:1;//�b������w��Ƨ���
			bool	IsDualDead		: 1;	//��զ��`
        };
	};
	bool	CheckResetItemInfo()
	{
		return Bank|Body|Eq;
	}
};

//-------------------------------------------------------------------------------------
//		�e�����c
//-------------------------------------------------------------------------------------
struct LookStruct
{
    int		FaceID;
    int		HairID;
    int		HairColor;
    int		BodyColor;
	//float	BoneScale[10];
	char	BoneScale[15];
	

    LookStruct()
    {
        memset( this , 0 , sizeof(*this) );
    }

    bool IsEmpty()
    {
        return ( FaceID == 0 && HairID == 0 && HairColor ==0 && BodyColor == 0 );
    }
};
//-------------------------------------------------------------------------------------
//��H������c
struct TradeStruct
{
	int	                Money;
	int					Money_Account;
    int					TargetID;	//����ؼ�
	int					TargetDBID;	//�ؼи�ƮwID
	
	bool	            SelectOK;	//���~��hOK
	bool	            FinalOK;	//�������


	TradeStruct()
	{
		Init();
	};

	void Init()
	{
		memset( this, 0 , sizeof(*this));
		TargetDBID = -1;
		TargetID = -1;
	};
};
//-------------------------------------------------------------------------------------
struct ShopStateStruct
{
    int     TargetID;
    int     ShopObjID;          //�c�檫�~������
    int     ItemCount[30];
	int		LastUpdateTime;		//�̫��s�ƶq���ɶ�

    StaticString< _MAX_LUA_FUNTIONNAMESIZE_> ShopClosePlot;	    //�ө������ɰ��檺�@��

    void Init()
    {
        memset( this , 0 , sizeof(*this) );
    }

};
//-------------------------------------------------------------------------------------
//�i�Q���Ѹ�T
struct StealStruct
{
	ItemFieldStruct	Item;	//�i�Q���Ѫ����~
	int	ItemSuccessRate;	//���\�����v

	int	Money;				//�i�Q���Ѫ�����
	int	MondySuccessRate;	//���\�����v
};
//-------------------------------------------------------------------------------------
//�ϥΤ������~
struct UseItemStruct
{
    short                 Pos;
    short                 Type;

	UseItemStruct()
	{
		Init();
	};

	void Init()
	{
        Pos = -1;
	};
};
//-------------------------------------------------------------------------------------
//�����Ҧ��C�|
enum	ATTACK_MODE_ENUM
{
	EM_ATTACKMODE_LEFTHAND	= 0	,	
	EM_ATTACKMODE_RIGHTHAND		,	
	EM_ATTACKMODE_BOTHHAND		,	
	EM_ATTACKMODE_NONE			,
    EM_ATTACK_MODE_EM_FORCE_DWORD   = 0x7fffffff, 
};
//-------------------------------------------------------------------------------------
//������������C�|
enum	ATTACK_DMGTYPE_ENUM
{
	EM_ATTACK_DMGTYPE_MISS,			    //MISS
    EM_ATTACK_DMGTYPE_DODGE,		    //DODGE
	EM_ATTACK_DMGTYPE_HALF,			    //�Q�j��
	EM_ATTACK_DMGTYPE_NORMAL,			//�@��
	EM_ATTACK_DMGTYPE_DOUBLE,			//�|�ߤ@��
	EM_ATTACK_DMGTYPE_TRIPLE,			//�����@��
	EM_ATTACK_DMGTYPE_HITBACK,          //����
	EM_ATTACK_DMGTYPE_NO_EFFECT,		//�S�ĪG
	EM_ATTACK_DMGTYPE_ABSORB,			//�l��
	EM_ATTACK_DMGTYPE_SHIELD_BLOCK,		//����
    EM_ATTACK_DMGTYPE_EM_FORCE_DWORD   = 0x7fffffff, 
};
//-------------------------------------------------------------------------------------
//�����D�Ƥ�C�|
enum AttackHandTypeENUM
{
	EM_AttackHandType_None		,
	EM_AttackHandType_Main		,
	EM_AttackHandType_Second	,
};
//-------------------------------------------------------------------------------------
//Local Server ���򥻸�T
struct	LocalServerBaseDBInfoStruct
{
	int		ItemVersion;				//�ثe���~���Ǹ�(0 - 9999999) �u�����i���|�����~���Ǹ�
	float	InstanceResetTime;
	float	InstanceNextResetTime;
	int		HouseItemMaxDBID;

	
	LocalServerBaseDBInfoStruct()
	{
		ItemVersion = 0;
		HouseItemMaxDBID = 0;
		InstanceResetTime = 0;
		InstanceNextResetTime = 0;
	}
};
//-------------------------------------------------------------------------------------
enum	SystemVersionENUM
{
	EM_SystemVersion_TW		,
	EM_SystemVersion_CN		,
	EM_SystemVersion_EN		,
	EM_SystemVersion_JP		,
};

//����]�w���
struct	GlobalServerDBInfoStruct
{
	float	QuestTpRate;
	float	QuestExpRate;
	float	ExpRate;
	float	DropTreasureRate;
	float	TpRate;
	float	MoneyRate;
	float	PK_DotRate;
	float	PK_DamageRate;
	int		LearnMagicID;
	SystemVersionENUM	Version;

	
	struct
	{
		StaticString< 256 >   LuaCheck;
		int		TableID;
	}GlobalDropTable[5];

	float	NPC_DamageRate;
	float	EqRefineRate;

	GlobalServerDBInfoStruct()
	{
		Init();
	}
	void Init()
	{
		QuestTpRate			= 1.0f;
		QuestExpRate		= 1.0f;
		ExpRate				= 1.0f;
		DropTreasureRate	= 1.0f;
		TpRate				= 1.0f;
		MoneyRate			= 1.0f;
		PK_DotRate			= 1.0f;
		PK_DamageRate		= 0.5f;
		LearnMagicID		= Def_ObjectClass_LearnMagic; 
		Version				= EM_SystemVersion_TW;

		NPC_DamageRate		= 1.0f;
		EqRefineRate		= 1.0f;
		GlobalDropTable[0].TableID = 0;
		GlobalDropTable[1].TableID = 0;
		GlobalDropTable[2].TableID = 0;
		GlobalDropTable[3].TableID = 0;
		GlobalDropTable[4].TableID = 0;
	}
};

//-------------------------------------------------------------------------------------
//party �������c
/*
struct	PartyMemberStruct
{
	int		DBID;		//��ƮwID
	int		LocalID;	//�ϰ�ID
	int		ZoneID;

    StaticString< _MAX_NAMERECORD_SIZE_ > Name;

	bool	IsEmpty()
	{
        if( this == NULL )
            return true;

		return ( DBID == 0 );
	}
};


//Party���c���
struct	PartyStruct
{
	short Count;				//�����H��
	int	PartyID;			//����ID
	int	LeaderDBID;			//��������ƮwID
	
  	StaticVector< PartyMemberStruct , _MAX_PARTY_COUNT_ > Member;

};
*/
//-------------------------------------------------------------------------------------
struct NPC_RandomMoveStruct
{
	bool				Enable;		//�üƲ��ʭP��	
	int					Active;		//�üƲ��ʿE���� (�@���ˬd�@�� �]�w������v % )

    int 				CountDown;	//�o�ʭ˼� �O���n���쪺�ɶ�

	float				CenterX;	//���ʽd�򤤤��IX
	float				CenterZ;	//���ʽd�򤤤��IZ
	float				MaxRange;	//�̻����ʽd��
	
	float				Dist;		//���ʶZ��������

	NPC_RandomMoveStruct()
	{
		Init();
	};

	void Init()
	{
		Enable		 = false;
		Active		 = 10;
		CenterX      = -1;	    //���ʽd�򤤤��IX
		CenterZ      = -1;	    //���ʽd�򤤤��IZ
		MaxRange     = 500;	    //�̻����ʽd��
	    
		CountDown    = 0;	    //�o�ʭ˼�

		Dist         = 100;	    //���ʶZ��������
		
	};
};
//-------------------------------------------------------------------------------------
enum	NPC_MoveTypeENUM
{
	EM_NPC_MoveType_None		= 0,//���]�w�Τ��e��
	EM_NPC_MoveType_Walk		,//���� 
	EM_NPC_MoveType_Run			,//�]��
	EM_NPC_MoveType_Rand		,//�����ζ]�B
};

enum	NPC_DirModeEnum
{
	EM_NPC_DirMode_None			= 0, // ������
	EM_NPC_DirMode_Change		= 1, // ���d�Φ��@���ɧ���
};

//NPC�w�I����
struct NPC_MoveBaseStruct
{
	NPC_MoveBaseStruct()
	{
		X				= 0;
		Y				= 0;
		Z				= 0;
		Dir				= 0;
		Range			= 0;
		MoveType		= EM_NPC_MoveType_None;
		WaitTime_Base	= 0;
		WaitTime_Rand	= 0;
		DirMode			= EM_NPC_DirMode_None;
		ActionType		= -1;
		IsUsePathFind	= true;
		sLuaFunc.Clear();
	}

	float				X , Y , Z;			// ���ʦ�m	
	float				Dir;				// ���V
	float				Range;				// ���ʰ��t�Z��
	NPC_MoveTypeENUM	MoveType;			// ���ʤ覡
	int					WaitTime_Base;		// �򥻵��ݮɶ�(��)
	int					WaitTime_Rand;		// �üƵ��ݮɶ�(��)
											// ���ݮɶ� = Base + Rand( )
	int					ActionType;			// �ʧ@ID ( -1 ����)
	StaticString< _MAX_LUA_FUN_ARG_SIZE_ >	sLuaFunc;	
	// ��F�w�I��, ��Ĳ�o���@��;
	NPC_DirModeEnum		DirMode;			//  ��w�I��, �Y�����d�ɶ��μ@��, �ݤ��ݭn���ܭ��V
	bool				IsUsePathFind;
};

struct DB_NPC_MoveBaseStruct
{
	int		ZoneID;		//�ϰ�ID
	int		NPCDBID;	//NPCDBID
	int		IndexID;	//��m
	NPC_MoveBaseStruct Base;
};

//-------------------------------------------------------------------------------------
// �t�κ޲z������T
//-------------------------------------------------------------------------------------
struct SysManageInfoStruct
{
    int						SaveSerial;					//�x�s���Ǹ��X
    union
    {
        int     GUID;
        struct
        {
            short   ItemID;            
            short   ZoneID;
        };
    };

    union
    {   //�֦���id
        int     OwnerGUID;
        struct
        {
            short   OwnerItemID;            
            short   OwnerZoneID;
        };
    };
	//�P�Ӿ֦��� �C��Group�u�঳�@�Ӫ��� �D�n�Φb���M�P�d��
	//GroupID = 0 ��ܤ�����  
	int						OwnerGroupID;									
	int						OwnerDBID;
    int                     WorldGUID;                  		//�Ҧ��N��P�@�Ӫ��󪺪��󦳬ۦP�� ID

    int						SockID;								//�ʥ]���eId
    int                     ProxyID;                    		//�B�z��Proxy
    int                     SecRoomID;							//�Ҧb�Ŷ� -1�N��S�[�JPartition
    int						SecX,SecZ;							//�Ҧb���ΰϪ���m
    long					CreateTime;							//���󲣥ͪ��ɶ�
    int						LoginProtect;						//�n�J�O�@�A�Ǫ��貣�ͻP�����n�J�ɩǪ����|�D�ʧ���
    int                     MirrorCount;                		//������O�_��Mirror������,���h�֭�(�O�d �ƭȤ��@�w���T )
    int                     LGUID;
    int                     ChangeZoneTime;             		//�i���Ϯɶ�
	int						KillRate;
	
	StaticString< _MAX_DESTORYOBJ_REASON >   DestroyAccount;	//�R������
	union
    {
        int                 _Flag;
        struct
        {
            bool	LuaDebugMsg	    	:1;
            bool	GM_Designed	    	:1;
			bool	OnChangeZone		:1;		//���b���Ϥ�
			bool	OnChangeWorld		:1;		//���@�ɤ�
			bool	WaitLogout			:1;
			bool	WaitChangeParallel	:1;		//������Ŷ���
			bool	WaitWebBagInfo		:1;		//�n�D���J�����ӫ����
			bool	IsPet				:1;
			bool	WaitUnlockPos		:1;		//�d�I�Ѱ�
			bool	PartitionLock		:1;		//�����ʤ��ΰ�
			bool	NeedFixClientPos	:1;		//�y�лݭn��s
        };
    };

    void Init()
    {
        SaveSerial  = 0;
        GUID        = -1;
        SockID      = -1;
        OwnerGUID   = -1;
        SecRoomID   = -1;
        SecX        = -1;
        SecZ        = -1;
        WorldGUID   = -1;
        LGUID       = -1;
        LoginProtect= 15;
        MirrorCount = 0;
        ChangeZoneTime = 0;
        _Flag  = 0;

        _time32( (long *)(&CreateTime) );
        
	}
};
//-------------------------------------------------------------------------------------
// ���|�B�z������T
//-------------------------------------------------------------------------------------
enum	ClientMoveTypeENUM
{
	EM_ClientMoveType_Normal	,
	EM_ClientMoveType_Jump		,
	EM_ClientMoveType_SetPos	,		//���~���ؼ�
	EM_ClientMoveType_Mount		,		//�b�|���ʪ���W(���� �p�q��)
	EM_ClientMoveType_SetPetPos	,		//�b�|���ʪ���W(���� �p�q��),�ץ��d������
	EM_ClientMoveType_WaterWalk	,		//�b���W�樫
	EM_ClientMoveType_OntimeSetCliPos,	//every 0.1 second fix client position
};

struct	PathProcStruct
{
    int			AddeDelay;				//�]���S��ƥ󲣥ͪ����ʼȰ�
    int			ProcDelay;				//�i�H�B�z���ʳѤU���ɶ�
    float		Dx , Dy , Dz;			//���ʦV�q
    float		Tx , Ty , Tz;			//npc�ؼ�

	float			RetX , RetY , RetZ;							//�԰���n�h�^����m

	float			BeginJumpX , BeginJumpY , BeginJumpZ;		
    unsigned int     BeginJumpTime;								//�_���ɶ�

    unsigned int      LastMoveTime;     //�̫Ჾ�ʪ��ɶ�
	ClientMoveTypeENUM	MoveType;		//�O�����a���ʪ��覡
	//----------------------------------------------------------
	//(�Ψ��ˬd�O�_���[�t)
	float		CliX , CliY , CliZ;		//Cli�ݳ̫�@���e�X����m
	float		LOK_CliX , LOK_CliY , LOK_CliZ;

	float		CalMoveLen;				//�����`�p
	unsigned int		CliLastMoveTime;
	int			PacketErrorCount;		//�p�Ⲿ�ʫʥ]���~�ƶq
	int			MoveTotalDistErrCount;	//�����`�q���~����
	//----------------------------------------------------------
	bool		IsLockSetPos;
	float		LockSetPosX , LockSetPosZ;
	int			LockTargetPosX , LockTargetPosZ;	//�ؼЦ�m��w ( PosList Map����m �ΨӳB�z�Ǫ����ʤ����| )
	//----------------------------------------------------------
	int			MoveHeightErrorCount;

	float		LCheckLineX,LCheckLineY,LCheckLineZ;
	float		LCheckDeadZoneX,LCheckDeadZoneY,LCheckDeadZoneZ;
	int			LCheckMovePGDir;

};
//-------------------------------------------------------------------------------------
#define _MAX_RENT_MENBER_RANK_ 20
#define _MAX_RENT_FUNCTION_ ( _MAX_RENT_COUNT_ - _MAX_RENT_MENBER_RANK_ )
struct RentFuncStruct
{
	union
	{
		unsigned RentTime[ _MAX_RENT_COUNT_ ];
		struct  
		{
			unsigned Member[ _MAX_RENT_MENBER_RANK_ ];
			unsigned	Function[ _MAX_RENT_FUNCTION_ ];
		};
	};
};
//-------------------------------------------------------------------------------------
//�n�J�w�ɳB�z���ƥ��T
//-------------------------------------------------------------------------------------
struct SimpleSchedularInfo
{
    int      SearchEnemyID;
    int      MoveID;
    int      AiID;
    int      AttackID;
    int      SpellMagicID;
};
//-------------------------------------------------------------------------------------
enum SmallGameTypeEnum
{
    EM_SmallGameType_None       = 0 ,
    EM_SmallGameType_WaitJoin      ,
    EM_SmallGameType_Big2           ,
};
struct  SmallGameInfoStruct
{
    SmallGameTypeEnum GameType;              //���smallgame ok

     
//    int     TradeMoney;         //��X�h������
};
//-------------------------------------------------------------------------------------
enum ItemFieldTypeENUM
{
	EM_ItemFieldType_Body	= 1		,
	EM_ItemFieldType_Bank			,
	EM_ItemFieldType_EQ				,
	EM_ItemFieldType_DestroyItem	,
	EM_ItemFieldType_TempItem		,
	EM_ItemFieldType_EQBackup		,
	EM_ItemFieldType_Pet			,
};
//-------------------------------------------------------------------------------------
//��Ʈw���~����T
struct DB_ItemFieldStruct
{
	int	DBID;
	int FieldID;
	int	FieldType;

	ItemFieldStruct Info;
};
//-------------------------------------------------------------------------------------
//�����ݩ�
struct DB_AbilityStruct
{
	int	DBID;
	int	Job;

	BaseAbilityStruct Info;
};


//-------------------------------------------------------------------------------------
// ���ȵ��c

enum EM_QUESTCHECK_RESULT
{
	EM_QUESTCHECK_RESULT_OK				= 0,
	EM_QUESTCHECK_RESULT_NOTEXIST		,	// NPC ���s�b
	EM_QUESTCHECK_RESULT_TOOFAR			,	// �Z�� Quest NPC �ӻ�
	EM_QUESTCHECK_RESULT_FULL			,	// Clinet �Ҿ֦��� Quest �M��w��
	EM_QUESTCHECK_RESULT_NOTLIST		,	// Clinet �Ҿ֦��� Quest �M��W�èS���Ӷ� Quest
	EM_QUESTCHECK_RESULT_NOTOK			,	// �ˬd��������ɵo�{�|������
	EM_QUESTCHECK_RESULT_RUNNINGSCRIPT	,	// NPC ���b����@����
	EM_QUESTCHECK_RESULT_ALREADYEXIST	,	// USER �w�g�֦��ӥ���
	EM_QUESTCHECK_RESULT_ALREADYDONE	,	// USER �w�g�����ӥ���
	EM_QUESTCHECK_RESULT_DAILYDONE		,	// USER ���Ѥw�����L�C����ȤF
	EM_QUESTCHECK_RESULT_QUESTERR		,	// ���ȥN�����s�b
	EM_QUESTCHECK_RESULT_GROUPFULL		,	// ���ȸs�դw��
	EM_QUESTCHECK_RESULT_NOQUESTITEM	,	// ���ȻݨD���~����	( CLIENT �@�� )
};


struct QuestStruct
{
	struct QuestInfo
	{
		int		iQuestID;
		BYTE	iMode;			// 0 ��@�����, 1 ����椤����, -1 ����ȥ���( �W�٫᭱�[���� )
		BYTE	iQuestKillCount[_MAX_QUEST_KILLKIND_COUNT_];

	} QuestLog[ _MAX_QUEST_COUNT_ ];		// Client ���W���� Quest �M��

	StaticFlag<_MAX_QUEST_FLAG_COUNT_>			QuestHistory;						// �ثe�̦h 2048 �� Quest , �ΨӬ������� Quest �w����
	//BYTE 										iQuestKillCount[_MAX_QUEST_COUNT_][_MAX_QUEST_KILLKIND_COUNT_];
																					// �����ثe����, �_������  20 Quest, 3 Kind

	// �C�魫�m�����ȳ���
	time_t			LastCompleteTime;								// �W��������Ȫ��ɶ�, �@���W�L�C�骺 24:00 ��, �K�N�����c�M��
	int				iQuestGroup[DF_QUESTDAILY_MAXGROUP];			// �@�@�� 10 �ӲէO, �C�ӲէO���U�۪��p�ƾ�, �t�ιw�] 10, �@�w���� 10 �Ӥ���K����A��

	StaticFlag<_MAX_QUEST_FLAG_COUNT_>			QuestDaily;			// �ثe�̦h 2048 �� Quest , �ΨӬ������ǨC����Ȥw����, ��C�� 24 �ɭ��m

	int	HistoryCount()
	{
		int Count = 0;
		for( int i = 0 ; i < _MAX_QUEST_FLAG_COUNT_ ; i++ )
		{
			if( QuestHistory.GetFlag( i ) != false )
				Count++;
		}
		return Count;
	}

};

struct QuestKillStruct
{
	int		iKillObj		[ _MAX_QUEST_KILLKIND_COUNT_ ];	// ���w���˥ؼЪ��˪��N��
	int		iKillVal		[ _MAX_QUEST_KILLKIND_COUNT_ ];	// ���w���˥ؼЪ��ƶq
	float	fDropPercent	[ _MAX_QUEST_KILLKIND_COUNT_ ];	// ���˫��w�ؼб������v
	int		iDropItem		[ _MAX_QUEST_KILLKIND_COUNT_ ];	// �������~
	int		iDropItemVal	[ _MAX_QUEST_KILLKIND_COUNT_ ];	// �������~�ƶq
};

struct QuestClickStruct
{
	int		iClickObj		[ _MAX_QUEST_CLICKIND_COUNT_ ];
	float	fProcPercent	[ _MAX_QUEST_CLICKIND_COUNT_ ];
	int		iDropItem		[ _MAX_QUEST_KILLKIND_COUNT_ ];	// �������~
	int		iDropItemVal	[ _MAX_QUEST_KILLKIND_COUNT_ ];	// �������~�ƶq
};



/*
struct QuestTempDataStruct
{
	BYTE				QuestKillCount;
	BYTE				QuestKillIndexTable		[ _MAX_QUEST_COUNT_ ];	// �����O�ĴX�� QuestField �����˭p��	
	QuestKillStruct		QuestKill				[ _MAX_QUEST_COUNT_ ];

	BYTE				QuestCollectCount;
	BYTE				QuestCollectIndexTable	[ _MAX_QUEST_COUNT_ ];
	QuestClickStruct	QuestCollect			[ _MAX_QUEST_COUNT_ ];

	int					iQuestResult;
};
*/
enum CastingTypeENUM
{
	EM_CastingType_NULL			=-1		,
	EM_CastingType_NormalUseItem		,
	EM_CastingType_Dissolution			,
	EM_CastingType_SetRune				,
	EM_CastingType_RefineEq				,

	EM_CastingType_OKRESULT		=100	,
//	EM_CastingType_DissolutionOK		,
//	EM_CastingType_SetRuneOK			,
//	EM_CastingType_RefineEqOK			,
};

// ���q, ���o���Ȫ���ɱƵ{�������~������
enum ENUM_CASTINGMODE
{
	EM_CASTING_NONE				= 0,
	EM_CASTING_QUESTOBJ			,
	EM_CASTING_MINE				,
	EM_CASTING_HERB			
};

struct CastingData
{
	void Clear()
	{
		//ZeroMemory( this, sizeof(this) );
		iEventHandle		= -1;
		emMode				= EM_CASTING_NONE;
		iGUID				= 0;
		iLockGUID			= 0;
		//iQuestID			= 0;
		//iClickObj			= 0;
		iClickObjID			= 0;
		iLockTime			= 0;
		iEndTime			= 0;
		iContext			= 0;
		pCastFunc			= NULL;
		bBeHit				= false;

		szLuaEvent			= "";

		ZeroMemory( &SourcePos, sizeof( RolePosStruct ) );
	}

	int					iEventHandle;			// ���J Schedular �Ҳ��ͪ��N�X
	ENUM_CASTINGMODE	emMode;
	int					iGUID;
	int					iLockGUID;				// �Ѩ��ӤH���惡���󲣥Ͱʧ@
	//int					iQuestID;
	int					iContext;				// �U�t�ΥΨӼȦs�����
	int					iClickObj;
	int					iClickObjID;
	int					iClickGetObj;
	int					iLockTime;				// �n�O���ꦺ����, �G�N�N�ɶ��Ԫ�, ���P�@�Ӫ��a����T�w�֦��P�@���q���v�O
	int					iEndTime;				// �����ɶ�

	RolePosStruct		SourcePos;				// �}�l�I�i��, �H�����y��
	PVOID				pCastFunc;				
	bool				bBeHit;					// �I�k�L�{���O�_���Q����
	StaticString< 64 >	szLuaEvent;

};

// �I���t�Υ�, �˴��ƥ�, �ϥΫe���M��, �M���ˬd�U�C�ƥ󦳵L�ܤ�
struct	ScriptEventFlagStruct
{	
	union
	{
		int _Event;
		struct
		{
			bool    bMove							: 1;	// �q�W���]�w���A�Ჾ�ʵo��
			bool    bCastSpell						: 1;	// �q�W���]�w���A��ϥιL�ޯ�
			bool    bHited			  				: 1;	// �q�W���]�w���A��Q�����L
			bool	bUseItem						: 1;	// �q�W���]�w���A�ᦳ�S���ϥιL���~
			bool	bSit							: 1;	// �q�W���]�w���A�ᦳ�S�����U�L
			bool	bMotionChange					: 1;	// �q�W���]�w���A�ᦳ�S�����ܰʰ�
		};
	};

	void Clear() { _Event = 0; }
};

//-------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////
//			���|��Ƴ]�w
//////////////////////////////////////////////////////////////////////////
//���|�\��]�w
struct GuildManageSettingStruct
{
	union
	{
		int		Type;
		struct  
		{
			bool	Invite				: 1;	//�ۦ�
			bool	AdjustRank			: 1;	//�վ㶥��
			bool	SetGuildNote		: 1;	//�]�w���i
			bool	Kick				: 1;	//�𰣷|��
			bool	AdjustGroup			: 1;	//�վ�s��
			bool	EditMemberNote		: 1;	//�]�w��������
			bool	PostMessage			: 1;	//�d��
			bool	ManageMessage		: 1;	//�d���O�޲z
			bool	Building			: 1;	//���|�ؿv
			bool	Furniture			: 1;	//���C�~�\�]
			bool	GuildWarRegister	: 1;	//���U���|��
			bool	SetGuildHouseStyle	: 1;	//�]�w�u�|�μ˦�
		};
	};
};
//-------------------------------------------------------------------------------------
//���|����
enum  GuildRankENUM
{
	EM_GuildRank_0			,
	EM_GuildRank_1			,
	EM_GuildRank_2			,
	EM_GuildRank_3			,
	EM_GuildRank_4			,
	EM_GuildRank_5			,
	EM_GuildRank_6			,
	EM_GuildRank_7			,
	EM_GuildRank_8			,
	EM_GuildRank_Leader		,

	EM_GuildRank_Count		,

};
//-------------------------------------------------------------------------------------
struct GuildStruct;

//���|�������
struct GuildMemberStruct
{
	GuildStruct*			Guild;				//���|����p��

	int						GuildID;
	StaticString< _MAX_NAMERECORD_SIZE_ >   MemberName;
	int						MemberDBID;
	GuildRankENUM			Rank;				//���⤽�|����
	int						GroupID;			//�Ҧb�s��
	StaticString< 256 >   	SelfNote;			//�ۤv����
	StaticString< 256 >   	LeaderNote;			//�|��������
	int						RankTime;			//�N¾�ɶ�
	bool					IsNeedSave;			//�p�G��Ʀ���ʫh�|�� true
	bool					IsOnline;

	Voc_ENUM				Voc;
	Voc_ENUM				Voc_Sub;
	Sex_ENUM				Sex;
	int						LV;
	int						LV_Sub;
	int						LogoutTime;

	GuildMemberStruct()
	{
		memset( this , 0 , sizeof(*this) );
	}
};
//-------------------------------------------------------------------------------------
//���|Rank ���
struct GuildRankBaseInfoStruct
{
	GuildManageSettingStruct				Setting;
	StaticString< _MAX_NAMERECORD_SIZE_ >   RankName;	//�W��
};
//-------------------------------------------------------------------------------------
struct GuildFlagStruct
{
	int InsigniaType;
	int InsigniaMainColor;
	int InsigniaOffColor;
	int BannerType;
	int BannerMainColor;
	int BannerOffColor;
};
//-------------------------------------------------------------------------------------
//²�������|���
struct SimpleGuildInfoStruct
{
	int		GuildID;
	GuildResourceStruct Resource;			//�귽
	/*
	int		WarMyScore;						//�ڤ�n��
	int		WarMyKillCount;
	int		WarEnemyScore;					//�Ĥ�n��
	int		WarEnemyKillCount;
	*/
};
//-------------------------------------------------------------------------------------
struct GuildInfoChangeStruct
{
	union
	{
		int Mode;
		struct
		{
			bool	GuildMessage	: 1;//���|�]�w�ק�
		};
	};
};
//-------------------------------------------------------------------------------------
#define		_MAX_GUILD_GROUP_COUNT_	10
#define		_MAX_GUILD_BUYFUNCTION_COUNT_ 256 
//���|���c
struct GuildBaseStruct
{
	int		GuildID;									//���|ID
	StaticString< _MAX_NAMERECORD_SIZE_ >   GuildName;	//���|�W��
	StaticString< _MAX_NAMERECORD_SIZE_ >   LeaderName;	//�|���W��
	int		LeaderDBID;
	union
	{
		int GuildType;
		struct  
		{
			bool	IsRecruit			:1;						//�O�_�ۥ�
			bool	IsReady				:1;						//�O�_��������
			bool	IsEnabledGuildBoard :1;						//�}�_�d���O�\��
			bool	IsWar				:1;						//�O�_����O�H�ž�
			bool	IsNeedChangeName	:1;						//�ݭn��W
			bool	IsWarPrepare		:1;						//�ǳƶ}��
			bool	IsOwnHouse			:1;						//�֦��Ы�
			bool	IsLockGuildHouse	:1;						//���|�άO�_�i�i�J
		};
	};
	bool	IsNeedUpdateSmipleInfo;			//�ήɧ�s�����
	bool	IsNeedSave;						//�p�G��Ʀ���ʫh�|�� true

	int		Level;							//���|����
	int		Medal;							//����
	int		MaxMemberCount;					//�̦h�i�H���h�ַ|��

	GuildResourceStruct Resource;			//�귽

	int		WarGuildID;						//�Ĺ綠�|
	int		WarMyScore;						//�ڤ�n��
	int		WarMyKillCount;
	int		WarEnemyScore;					//�Ĥ�n��
	int		WarEnemyKillCount;
	int		WarTime;						//�Ԫ������ɶ�

	int		WarWinCount;					//�ӳ�
	int		WarEvenCount;					//����
	int		WarLostCount;					//�ѳ�
	int		WarDeclareTime;					//�žԮɶ�

	struct
	{
		int		WinCount;					//�ӳ�
		int		EvenCount;					//����
		int		LostCount;					//�ѳ�
		int		Score;
		int		NextWarTime;				//�U�@�����|�ξԮɶ�
	}HousesWar;	//���|�ξ�
	
	GuildFlagStruct		GuildFlag;			//���|�X��T

	StaticString< 512 >   Note;				//���i
	StaticString< 512 >   Introduce;		//���|����

	int		RankCount;						//���|���h��
	GuildRankBaseInfoStruct	Rank[ EM_GuildRank_Count ];						//�C�ӵ��Ū��v�� �P�W��
	StaticString< _MAX_NAMERECORD_SIZE_ >   Group[_MAX_GUILD_GROUP_COUNT_];	//�s�զW��
	StaticFlag< _MAX_GUILD_BUYFUNCTION_COUNT_ >	Flag;	
	//int		LastCalRentTime;				//�̫�@���p������O���ɶ�

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
		GuildFlag.BannerMainColor   = 0xffffffff;
		GuildFlag.BannerOffColor    = 0xff000000;
		GuildFlag.InsigniaMainColor = 0xffffffff;
		GuildFlag.InsigniaOffColor  = 0xff000000;
		HousesWar.Score				= 1000;
	}
};
//-------------------------------------------------------------------------------------
//�d�������A
struct GuildBoardModeStruct
{
	union
	{
		int		_Type;
		struct  
		{
			bool	Top : 1;	//�m��
			bool	Del : 1;	//�Q�R��
		};
	};

};

//���|�d���O
struct GuildBoardStruct
{
	int						GUID;		//�Ǹ�
	int						GuildID;	//���|ID
	GuildBoardModeStruct	Type;		//���A
	StaticString< 128 >		Title;		//���D
	StaticString< 512 >		Message;	//�T��
	int						Time;		//�o��ɶ�
	StaticString< _MAX_NAMERECORD_SIZE_ >   PlayerName;	    //�o��H
};

//////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------------
//�k�NBuff��� 
struct BuffBaseStruct
{
    int     OwnerID;
    int     BuffID;         //�]�kID
    int     Time;           //�ѤU�ɶ�(��)
	int		Power;			//�¤O( �]�k�ֿn���� )
	int		Point;			//�I��( �]�k�ޥi���I�� or ����)
	
	union
	{
		int Mode;
		struct
		{
			bool	IsPK	: 1;
			bool	IsErase	: 1;	//�]���S�O��]�M��
		};
	};

	GameObjDbStruct*	Magic;	
};
//-------------------------------------------------------------------------------------
//�k�NBuff���
struct RefineBuffStruct
{
	int RecipeID;
	int	Coldown;
};
//-------------------------------------------------------------------------------------
//�����ƨ���,�Ψӧ�s�P�����Ҹ�T
struct RoleBackupInfo
{
	ObjectModeStruct Mode;
    //�ƭ�
    int     MaxHP;
    int     MaxMP;
    int     MaxSP;
    int     MaxSP_Sub;
    int     HP;
    int     MP;
    int     SP;
	int		SP_Sub;
	int		StomachPoint;

	int		GuildID;		
	int		TitleID;
	bool	IsShowTitle;

	int		LastSkillHitPoint;		//�̫�@���ޯ�ˮ`
	int		LastPhyHitPoint;		//�̫�@���@��ܮ`

	unsigned int	LastCriticalTime;				//�̫�@��Cirtical �ɶ�
	unsigned int	LastBeCriticalTime;				//�̫�@���QCirtical �ɶ�
	unsigned int	LastMagicCriticalTime;			//�̫�@��Cirtical �ɶ�
	unsigned int	LastBeMagicCriticalTime;		//�̫�@���QCirtical �ɶ�

	unsigned int	LastDodgeTime;			//�̫�@��Dodge �ɶ�
	unsigned int	LastMissTime;			//�̫�@��Miss �ɶ�
	unsigned int	LastParryTime;			//�̫�@��Parry �ɶ�
	unsigned int	LastBeParryTime;		//�̫�@���QParry �ɶ�
	unsigned int	LastBeDodgeTime;		//�̫�@���QDodge �ɶ�
	unsigned int	LastShieldBlockTime;	//�̫�@�� ���� �ɶ�
	unsigned int	LastBeShieldBlockTime;	//�̫�@���Q���� �ɶ�

	int		MoveSpeed;

	MagicClearTimeStruct	BuffClearTime;	//�ݭn�M�����k�NBuff
    //���α����_�l
    bool    StartJump;
    float   Y;

	int		LZoneID;	//�̫Ჾ������ΰϪ���m
	float	LX , LZ;	//�̫Ჾ������ΰϪ���m

	float	JumpRate;
	float	Gravity;

	int		HEvent_Ai;
	int		HEvent_Move;


	PlayerBackupInfoStruct	ZonePlayerInfo;
};
//-------------------------------------------------------------------------------------
#define DEF_MAX_COLDOWN_COUNT_JOB_	500
#define DEF_MAX_COLDOWN_COUNT_EQ_	15
#define DEF_MAX_COLDOWN_COUNT_ITEM_	80
#define DEF_MAX_COLDOWN_COUNT_ALL	( DEF_MAX_COLDOWN_COUNT_JOB_ + DEF_MAX_COLDOWN_COUNT_EQ_ + DEF_MAX_COLDOWN_COUNT_ITEM_ + 1 )
#define DEF_COLDOWN_ALL_POS			0
#define DEF_COLDOWN_JOB_POS			1
#define DEF_COLDOWN_EQ_POS			( DEF_COLDOWN_JOB_POS + DEF_MAX_COLDOWN_COUNT_JOB_ )
#define DEF_COLDOWN_ITEM_POS		( DEF_COLDOWN_EQ_POS + DEF_MAX_COLDOWN_COUNT_EQ_ )
//�Ҧ��k�NColdown
struct MagicColdownStruct
{
	union
	{
		int	All[ DEF_MAX_COLDOWN_COUNT_ALL];
		struct  
		{
			int	AllMagic;								//�U���i���k���ɶ� (�Ҧ��k�N)
			int	Job	[ DEF_MAX_COLDOWN_COUNT_JOB_  ];	
			int	Eq	[ DEF_MAX_COLDOWN_COUNT_EQ_   ];	
			int	Item[ DEF_MAX_COLDOWN_COUNT_ITEM_ ];
		};
	};

	//�ݭn��s�ɶ�����m
	StaticVector< short , DEF_MAX_COLDOWN_COUNT_ALL > NeedUpdatePos;

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	}
};
//-------------------------------------------------------------------------------------
enum FriendListTypeENUM
{
	EM_FriendListType_Friend	,
	EM_FriendListType_HateFriend,
	EM_FriendListType_FamilyFriend,
};

enum FriendListInsertResultENUM
{
	EM_FriendListInsertResult_OK		,
	EM_FriendListInsertResult_Modify	,
	EM_FriendListInsertResult_Failed	,
};


//�n�ͦW��
struct BaseFriendStruct
{
	bool	IsSave;
	RelationTypeENUM	Relation;
	int		DBID;							//����dbid
	char	Name[_MAX_NAMERECORD_SIZE_];	//����W��
	float	Lv;								//���Y����



	union
	{
		char	Note[ 60 ];	    //��B�ͪ�����
		struct 
		{
			Race_ENUM			Race;								//�ر�
			Voc_ENUM		    Voc;								//¾�~
			Voc_ENUM		    Voc_Sub;							//��¾�~
			Sex_ENUM			Sex;								//�ʧO
			int					JobLv;
			int					JobLv_Sub;
			int					GuildID;
			int					TitleID;
			int					Time;

			union
			{
				struct //�n�ͥ�struct
				{//client �s��
					int		GroupID : 16;					//��Ƨ����X
		//			int		ClientInfo1;
		//			int		ClientInfo2;
				};

				struct //���H��struct
				{
					int		KillMeCount  : 16; //���ڦ���
					int		RevengeCount : 16; //��������
					bool    top          :  1; //�m��
				};
			};

		};
	};


	bool IsEmpty()
	{
		return ( DBID <= 0 );
	}
	void Clear()
	{
		memset( this , 0 , sizeof(*this) );
	}
};

struct FriendListStruct 
{
	StaticString< _MAX_FRIENDLIST_NOTE_ >   Note;	    //�ۤv����

	union
	{
		BaseFriendStruct	AllFriendList[ _MAX_FRIENDLIST_ALL_COUNT_ ];
		struct
		{
			BaseFriendStruct	FamilyList[ _MAX_FRIENDLIST_FAMILY_COUNT_ ];			//�n���W��
			BaseFriendStruct	FriendList[ _MAX_FRIENDLIST_COUNT_ ];			//�n���W��
			BaseFriendStruct	HateFriendList[ _MAX_HATE_PLAYER_LIST_COUNT_ ];	//����W��C��
		};
	};
	
	union
	{
		char	ClientData[ _MAX_BAD_FRIENDLIST_COUNT_ + _MAX_FRIENDLIST_GROUP_COUNT_ ][_MAX_NAMERECORD_SIZE_ ];
		struct
		{
			char	BadFriendList[ _MAX_BAD_FRIENDLIST_COUNT_ ][_MAX_NAMERECORD_SIZE_];
			char	GroupName[ _MAX_FRIENDLIST_GROUP_COUNT_ ][_MAX_NAMERECORD_SIZE_];
		};
	};

	void	FixupData()
	{
		int maxCount;
		BaseFriendStruct* pList;
		for( int i = 0 ; i < 3 ; i++ )
		{
			vector< BaseFriendStruct > friendList;
			GetListInfo( (FriendListTypeENUM)i , &pList , maxCount );

			for( int i = 0 ; i < maxCount ; i++ )
			{
				if( pList[i].IsEmpty() )
					continue;
				friendList.push_back( pList[i] );
				memset( &pList[i] , 0 , sizeof(BaseFriendStruct) );
			}
			
			for( unsigned i = 0 ; i < friendList.size() ; i++ )
			{
				pList[i] = friendList[i];
			}
		}

	}

	char	GroupSortID[ _MAX_FRIENDLIST_GROUP_COUNT_  ];

	void	GetListInfo( FriendListTypeENUM Type , BaseFriendStruct** pList , int& MaxCount )
	{
		switch( Type )
		{
		case EM_FriendListType_Friend:
			MaxCount = _MAX_FRIENDLIST_COUNT_;
			*pList = FriendList;
			break;
		case EM_FriendListType_HateFriend:
			MaxCount = _MAX_HATE_PLAYER_LIST_COUNT_;
			*pList = HateFriendList;
			break;
		case EM_FriendListType_FamilyFriend:
			MaxCount = _MAX_FRIENDLIST_FAMILY_COUNT_;
			*pList = FamilyList;
			break;
		default:
			MaxCount = -1;
			*pList = NULL;
			break;
		}
	};
	FriendListInsertResultENUM	Insert( FriendListTypeENUM Type , int Pos , BaseFriendStruct& Info )
	{
		BaseFriendStruct*	pList;
		int					MaxCount = -1;
		bool				IsEarse;

		GetListInfo( Type , &pList , MaxCount );
		if( pList == NULL )
			return EM_FriendListInsertResult_Failed;

		if( Pos >= MaxCount || Pos < 0 )
			return EM_FriendListInsertResult_Failed;

		IsEarse = Erase( Type , Info.DBID );

		for( int i = MaxCount-1 ; i > Pos ; i-- )
		{
			pList[i] = pList[i-1];
		}
		pList[Pos] = Info;
		pList[Pos].IsSave = false;

		if( IsEarse )
			return EM_FriendListInsertResult_Modify;

		return EM_FriendListInsertResult_OK;
	};
	bool	Erase( FriendListTypeENUM Type , int DBID )
	{
		BaseFriendStruct*	pList;
		int					MaxCount = -1;

		GetListInfo( Type , &pList , MaxCount );
		if( pList == NULL )
			return false;

		bool IsFind = false;
		for( int i = 0 ; i < MaxCount-1 ; i++ )
		{
			if( IsFind == false && pList[i].DBID != DBID )
				continue;

			IsFind = true;
			pList[i] = pList[i+1];
		}
		pList[MaxCount-1].Clear();

		return IsFind;
	};
	bool	Modify( FriendListTypeENUM Type , BaseFriendStruct& Info )
	{
		BaseFriendStruct*	pList;
		int					MaxCount = -1;

		GetListInfo( Type , &pList , MaxCount );
		if( pList == NULL )
			return false;

		for( int i = 0 ; i< MaxCount ; i++ )
		{
			if( pList[i].DBID == Info.DBID )
			{
				bool IsSave = pList[i].IsSave;
				pList[i] = Info;
				pList[i].IsSave = IsSave;
				return true;
			}
		}
		return false;
	};

	int	FindFriendInfo( FriendListTypeENUM Type , int DBID , BaseFriendStruct** Info )
	{
		BaseFriendStruct*	pList;
		int					MaxCount = -1;

		GetListInfo( Type , &pList , MaxCount );
		if( pList == NULL )
			return false;

		for( int i = 0 ; i< MaxCount ; i++ )
		{
			if( pList[i].DBID == DBID )
			{
				*Info = &(pList[i]);
				return i;
			}
		}

		for( int i = 0 ; i< MaxCount ; i++ )
		{
			if( pList[i].IsEmpty() )
			{
				*Info = &(pList[i]);
				return i;
			}
		}

		return -1;
	}
	
};


//-------------------------------------------------------------------------------------
//�n�ͦW�� (��Ʈw�s����)
struct DB_BaseFriendStruct
{
	int OwnerDBID;
	int FieldID;
	FriendListTypeENUM	Type;
	BaseFriendStruct Info;
};
//-------------------------------------------------------------------------------------
//�Ҧ��u�W���a�򥻸��(�e�����ʥ]�ϥ�)
struct OnlinePlayerInfoStruct
{
	StaticString< _MAX_ACCOUNT_SIZE_	>   Account;    //�b��
	StaticString< _MAX_NAMERECORD_SIZE_ >   Name;	    //����W��	
	int				DBID;
	int				SockID;		//�ʥ]���eId
	int     		ProxyID;    //�B�z��Proxy
	int				GuildID;	//���| ID
	int				RoomID;
	bool			IsShowTitle;
	int				TitleID;
	StaticString< _MAX_NAMERECORD_SIZE_ >   TitleStr;	//�۩w�ٸ�
	StaticString< _MAX_FRIENDLIST_NOTE_ >   Note;	    //�ۤv������	

	union
	{
		struct
		{
			short   ItemID;            
			short   ZoneID;
		};
		int				GUID;							// �ϰ쪫��ID
	};

	Race_ENUM		Race;
	Voc_ENUM		Voc;
	Voc_ENUM		Voc_Sub;
	Sex_ENUM		Sex;
	LookStruct		Look;
	int				LV;
	int				LV_Sub;
	int				ParallelID;

	PlayerStateStruct	State;	//���a���Ϫ��A
};
//-------------------------------------------------------------------------------------
//���|�ξԾ��v���
struct GuildHouseWarHistoryStruct
{

	int		GuildID;
	int		TargetGuildID;
	float	EndFightTime;
	int		Result;
	int		GuildScore;
	int		TargetGuildScore;
	StaticString<_MAX_NAMERECORD_SIZE_> TargetGuildName;		
	GuildHouseWarHistoryStruct()
	{
		memset( this , 0 , sizeof(*this) );
	}
};
//-------------------------------------------------------------------------------------
//���|��Ƶ��c
struct GuildStruct
{
	GuildBaseStruct						Base;
	vector<GuildMemberStruct*>			Member;

	vector<GuildBoardStruct*>			BoardAll;		//�Ҧ����d��
	vector<GuildBoardStruct*>			BoardList;		//�̷s��60�����
	deque<GuildHouseWarHistoryStruct>	GuildWarHistory;


	GuildStruct()
	{
		Base.Init();
	};
	void ClearMemory()
	{
		for( int i = 0 ; i < (int)Member.size() ; i++ )
		{
			delete Member[i];
		}
		Member.clear();

		for( unsigned i = 0 ; i < BoardAll.size() ; i++ )
		{
			delete BoardAll[i];
		}
		BoardAll.clear();
		BoardList.clear();

	};

	//�B�z�m��
	bool	MessageSetTop( int MessageID , bool Flag )
	{

		if( Flag != false )
		{	//�]��Top
			int TopCount = 0;
			for( unsigned i = 0 ; i < BoardList.size() ; i++ )
			{
				GuildBoardStruct* Msg = BoardList[i];
				if( Msg->Type.Top != false )
					TopCount++;

				if( MessageID != Msg->GUID )
					continue;

				if( Msg->Type.Top != false )
					return true;

				Msg->Type.Top = true;
				BoardList.erase( BoardList.begin() + i );
				BoardList.insert( BoardList.begin() + TopCount , Msg );
				return true;
			}

		}
		else
		{
			int TopCount = 0;
			GuildBoardStruct* Msg = NULL;
			int	MsgPos = -1;
			for( unsigned i = 0 ; i < BoardList.size() ; i++ )
			{
				GuildBoardStruct* TempMsg = BoardList[i];

				if( TempMsg->Type.Top == false )
					break;

				TopCount++;
				
				if( MessageID != TempMsg->GUID )
					continue;

				Msg = TempMsg;
				MsgPos = i;
			}

			if( Msg != NULL )
			{
				Msg->Type.Top = false;
				BoardList.erase( BoardList.begin() + MsgPos );
				BoardList.insert( BoardList.begin() + (TopCount - 1) , Msg );
				return true;
			}
		}
		return true;
	}

	
};
//-------------------------------------------------------------------------------------
//�H��I������
enum	MailBackGroundTypeENUM
{
	EM_MailBackGroundType_Gift		= -2,
	EM_MailBackGroundType_System	= -1,
	EM_MailBackGroundType_Normal	= 0,
	EM_MailBackGroundType_Max		= 5,
};

struct MailBaseInfoStruct
{
	ItemFieldStruct		Item[10];	//���²�d
	int		Money;
	int		Money_Account;
	int		Money_Bonus;

	bool	IsSendMoney;		//true �H�e���� false ���I��
	bool	IsSystem;			//�O�_���t�ΫH��
	bool	IsRead;
	bool	IsSendBack;			//�O�_���h�^�H��
	bool	IsGift;				//�O�e�z���

	int		AcDBID;				//�p�G���O0 , �h��ܬOAC�o�X�Ӫ��H��

	StaticString <_MAX_NAMERECORD_SIZE_>	OrgSendName;
	StaticString <_MAX_NAMERECORD_SIZE_>	OrgTargetName;

	StaticString <_MAX_NAMERECORD_SIZE_>	Title;
	int		LiveTime;				//�ͦs�ɶ�( ���(����) )
	MailBackGroundTypeENUM PaperType;

	void initItem()
	{
		memset( Item , 0 , sizeof(Item) );
	};

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	};
};
//-------------------------------------------------------------------------------------
//Mail ��Ƶ��c
struct DB_MailStruct
{
	int		GUID;
//	int		ItemGUID;
	int		OwnerDBID;
	int		OrgSendDBID;			//��l�e���
	
	MailBaseInfoStruct	MailBase;
	StaticString<2048>	Content;

	void Init()
	{
		GUID = -1;
//		ItemGUID = -1;
		OwnerDBID = -1;
		OrgSendDBID = -1;			
		Content.Clear();
	};

	DB_MailStruct()
	{
		Init();
	};
};
//--------------------------------------------------------------------------------------------
struct DB_MailItemStruct
{
	int				MailBaseGUID;		//Mail DB ���X
	ItemFieldStruct Item;
};
//--------------------------------------------------------------------------------------------
enum	ACItemStateENUM
{
	EM_ACItemState_Normal	,
	EM_ACItemState_BuyOut	,
	EM_ACItemState_Cancel	,
};

struct DB_ACItemStruct
{
	int		GUID;					//�bAC����ƮwID
	StaticString <_MAX_NAMERECORD_SIZE_>	SellerName;		//���W�r
	StaticString <_MAX_NAMERECORD_SIZE_>	BuyerName;		//�R��W�r

	int		NowPrices;
	int		BuyOutPrices;
	PriceTypeENUM PricesType;
	int		BuyerDBID;
	int		SellerDBID;
	int		LiveTime;				//�i�ͦs�ɶ�
	int		ItemLevel;				//���~����

	ItemFieldStruct		Item;		//�檺�F��
	StaticString <_MAX_NAMERECORD_SIZE_>	ItemName;		//���~�W��
	int		ItemType[3];			//���~����
	int		Rare;
	int		RuneVolume;

	SexFlagStruct				SexType;			//�ʧO				
	RaceFlagStruct				RaceType;			//�ر�			
	VocationFlagStruct			JobType;			//¾�~
	EqWearSkillStruct			EQType;				//�˳�����
	
	ACItemStateENUM				State;
	int							ImportAcItemGUID;
};
//--------------------------------------------------------------------------------------------
struct  DB_ACItemHistoryStruct
{
	int		GUID;
	StaticString <_MAX_NAMERECORD_SIZE_>	SellerName;		//���W�r
	StaticString <_MAX_NAMERECORD_SIZE_>	BuyerName;		//�R��W�r

	int		Date;	//��X�ɶ�
	int		Prices;
	int		BuyerDBID;
	int		SellerDBID;
	PriceTypeENUM PricesType;

	ItemFieldStruct		Item;	//�檺�F��
};
//-------------------------------------------------------------------------------------
//Server�ƥ�T���C�|
enum	GameMessageEventENUM
{
	EM_GameMessageEvent_OK								,	//�S�����D
	EM_GameMessageEvent_Failed							,	//�@�륢��

	EM_GameMessageEvent_FightNoLogout					,	//�԰������i�n�X
	EM_GameMessageEvent_ChanageZoneError_PraviteZoneFull,	//�W�߰ϰ캡�F
	EM_GameMessageEvent_ChanageZoneError_Failed			,	//���ϥ���
	EM_GameMessageEvent_MoveSpeedDataError				,	//���ʸ�Ʀ����D
	EM_GameMessageEvent_MoveSpeedToFastError			,	//���ʥ[�t??
	EM_GameMessageEvent_TotalMoveSpeedToFastError		,	//�����`�q�[�t??
	EM_GameMessageEvent_MoveVectorError					,	//���ʦV�q�L�j
	EM_GameMessageEvent_NoMove							,	//�ثe�Q�I�i�w���k�N�A���i����
	EM_GameMessageEvent_CharacterNotFound				,	//���⤣�s�b
	EM_GameMessageEvent_TalkDisable						,	//�T����
	EM_GameMessageEvent_ItemLock						,	//���~�Q�K�X���A����ϥ�
	EM_GameMessageEvent_NeedSysChannelItem				,	//�ʤֵo�e�t���W�D�����~
	EM_GameMessageEvent_SecondPasswordError				,	//�G���K�X��J���~
	EM_GameMessageEvent_ZoneChannelLevelErr				,	//�P�֭n���@��¾�~���ŶW�L12�šA�~�i�ϥΰ��W
	EM_GameMessageEvent_PKItemProtect					,	//PK���~�g�@�O�@
	EM_GameMessageEvent_VisitGuildHouse_OpenYet			,	//���[���|�Τ����}�Ҥ�
	EM_GameMessageEvent_TellCharacterNotFound			,	//���⤣�b�u�W�A�i��|�����즹�T��
	EM_GameMessageEvent_Mail_RoleLvError				,	//���ⵥ�Ť����A�L�k�H�H
	EM_GameMessageEvent_TargetHasParty					,	//�ؼФw�[�J����

	EM_GameMessageEvent_Party_AssistPlayerDBID_Error	,	//���w���a���b�u�W

	EM_GameMessageEvent_DepartmentBagFull				,	//�ӫ��]�w���A���~�L�k���o
	
	EM_GameMessageEvent_BuffTimeDesc_Time0				,	//���k�N�ȮɦA�ؼФW���ͧK�̮ĪG
	EM_GameMessageEvent_ExchangeItem_DataErr			,	//�I�����~�]�w����Ʀ����D�A�гq���x��
	EM_GameMessageEvent_House_TooManyUnCheckItem		,	//�L�h���~log �٨S�d��
	EM_GameMessageEvent_ClientDataError					,	//�Ȥ�ݸ�Ʋ��`,�^���A�Ⱦ�
	EM_GameMessageEvent_ChanageZoneError_InstanceKeyErr	,	//�A�M����ƥ��i�פ��ŦX,�L�k�i�J�ƥ�
	EM_GameMessageEvent_ChanageZoneError_InstanceKey	,	//�M���ͪ��ƥ��i�פ��P�L�k�i�J
	EM_GameMessageEvent_ChanageZoneError_InstanceKeyDuplicate,//�w����L����ϥΦ��i�׶i��C��

	EM_GameMessageEvent_SuitSkill_OpenYet				,	//�M�˧ޯ�f�������}�Ҥ�


	EM_GameMessageEvent_HonorParty_NumLimit = 40		,	//�a�A�ն��W��2�H

	//�԰�
	EM_GameMessageEvent_AttackError_TargetTooFar = 50	,	//�����ؼйL��
	EM_GameMessageEvent_AttackError_Dir					,	//�������V�����D
	EM_GameMessageEvent_AttackError_TargetDead			,	//�ؼЦ��`
	EM_GameMessageEvent_AttackError_Target				,	//�ؼФ��i����

	EM_GameMessageEvent_AttackError_PhyDisable			,	//���i���z����
	EM_GameMessageEvent_AttackError_MagicDisable		,	//���i�k�N����



	//�I�k
	EM_GameMessageEvent_MagicError_OnSpell		 = 100	,	//�w�b�I�k��
	EM_GameMessageEvent_MagicError_TargetTooFar			,	//�I�k�Z���L��
	EM_GameMessageEvent_MagicError_Request				,	//�k�N�ݨD�����D
	EM_GameMessageEvent_MagicError_Target				,	//�k�N�ؼЦ����D
	EM_GameMessageEvent_MagicError_Back					,	//�n�b�ؼЭI��~�i�I�i
	EM_GameMessageEvent_MagicError_Front				,	//�n�b�ؼЫe���~�i�I�i
	EM_GameMessageEvent_MagicError_LookAt				,	//�n�ݵۥؼФ~�i�I�i
	EM_GameMessageEvent_MagicError_Coldown				,	//�N�o��

	EM_GameMessageEvent_MagicError_MagicIDError			,	//MagicID�����D
	EM_GameMessageEvent_MagicError_CreateObjectError	,	//��ߪ��󥢱�
	EM_GameMessageEvent_MagicError_HPNotEnough			,	//HP����
	EM_GameMessageEvent_MagicError_MPNotEnough			,	//MP����
	EM_GameMessageEvent_MagicError_WarriorSPNotEnough	,	//�ԤhSP����
	EM_GameMessageEvent_MagicError_RangerSPNotEnough	,	//�C�LSP����
	EM_GameMessageEvent_MagicError_ThiefSPNotEnough		,	//�s��SP����
	EM_GameMessageEvent_MagicError_StomachFull			,	//�Y���U
	EM_GameMessageEvent_MagicError_CostItemError		,	//���Ӫ��~�����D
	EM_GameMessageEvent_MagicError_NoGun				,	//�S�j
	EM_GameMessageEvent_MagicError_NoBow				,	//�S�}
	EM_GameMessageEvent_MagicError_NoCossBow			,	//�S�Q�r�}
	EM_GameMessageEvent_MagicError_NoGunAmmo			,	//�S�l�u
	EM_GameMessageEvent_MagicError_NoBowAmmo			,	//�S�b
	EM_GameMessageEvent_MagicError_NoCossBowAmmo		,	//�S��
	EM_GameMessageEvent_MagicError_NoThrowAmmo			,	//�S���Y��
	EM_GameMessageEvent_MagicError_NoAllLongWeapon		,	//�S���{�Z��
	EM_GameMessageEvent_MagicError_NoAmmo				,	//�S�u��
	EM_GameMessageEvent_MagicError_NeedWeaponError		,	//�Z���L�k�I�i���ۦ�
	EM_GameMessageEvent_MagicError_NeedBuffError		,	//�ʤ֫e�m�����U�k�N
	EM_GameMessageEvent_MagicError_NeedNoBuffError		,	//�ܻ��U�٨S������
	EM_GameMessageEvent_MagicError_NeedTargetNoBuffError,	//�ؼЧܻ��U�٨S������
	EM_GameMessageEvent_MagicError_NeedUnarmed			,	//�ݭn�Ť�~�i�I�i
	EM_GameMessageEvent_MagicError_NeedBlade			,	//�ݭn�D�⮳���C�~�i�I�i
	EM_GameMessageEvent_MagicError_NeedDagger			,	//�ݭn�D�⮳�P���~�i�I�i
	EM_GameMessageEvent_MagicError_NeedWand				,	//�ݭn�D�⮳�v���~�i�I�i
	EM_GameMessageEvent_MagicError_NeedAxe				,	//�ݭn�D�⮳����~�i�I�i
	EM_GameMessageEvent_MagicError_NeedBludgeon			,	//�ݭn���ҴΤ~�i�I�i
	EM_GameMessageEvent_MagicError_NeedClaymore			,	//�ݭn������C�~�i�I�i
	EM_GameMessageEvent_MagicError_NeedStaff			,	//�ݭn��������~�i�I�i
	EM_GameMessageEvent_MagicError_Need2HAxe			,	//�ݭn�������~�i�I�i
	EM_GameMessageEvent_MagicError_Need2HHammer			,	//�ݭn��������~�i�I�i
	EM_GameMessageEvent_MagicError_NeedPolearm			,	//�ݭn�����٤~�i�I�i
	EM_GameMessageEvent_MagicError_NeedSwordType		,	//�ݭn���C���~�i�I�i
	EM_GameMessageEvent_MagicError_NeedAxeType			,	//�ݭn����~�i�I�i
	EM_GameMessageEvent_MagicError_NeedShield			,	//�ݭn���ޤ~�i�I�i
	EM_GameMessageEvent_MagicError_NeedDistance			,	//�ݭn�Z������
	EM_GameMessageEvent_MagicError_NeedNoAttack			,	//�ݭn�ۤv�D�԰�
	EM_GameMessageEvent_MagicError_NeedAttack			,	//�ݭn�԰��~�i�ϥ�
	EM_GameMessageEvent_MagicError_NeedCritical			,	//�z����~�i�ϥ�
	EM_GameMessageEvent_MagicError_NeedBeCritical		,	//�Q�z����~�i�ϥ�
	EM_GameMessageEvent_MagicError_NeedDodge			,	//�{�׫�~�i�ϥ�
	EM_GameMessageEvent_MagicError_NeedMiss				,	//Miss��~�i�ϥ�
	EM_GameMessageEvent_MagicError_NeedParry			,	//���ɫ�~�i�ϥ�
	EM_GameMessageEvent_MagicError_NeedBeParry			,	//�Q���ɫ�~�i�ϥ�
	EM_GameMessageEvent_MagicError_NeedTargetNoAttack	,	//�ؼЫD�԰��~�i�ϥ�
	EM_GameMessageEvent_MagicError_NeedTargetAttack		,	//�ؼо԰��~�i�ϥ�
	EM_GameMessageEvent_MagicError_NeedBeDodge			,	//�Q�{�פ~�i�ϥ�
	EM_GameMessageEvent_MagicError_NeedHPSmallerPercent	,	//HP�L�h�L�k�ϥ�
	EM_GameMessageEvent_MagicError_NeedHPGreaterPercent	,	//HP�L�ֵL�k�ϥ�
	EM_GameMessageEvent_MagicError_NeedJob				,	//��¾�~�L�k�I�i
	EM_GameMessageEvent_MagicError_NeedLongDistWeapon	,	//�ݭn�����Z���Z���~�i�ϥ�
	EM_GameMessageEvent_MagicError_NeedHammerType		,	//�ݭn�������Z���~�i�ϥ�
	EM_GameMessageEvent_MagicError_Need2HWeapon			,	//�ݭn������Z���~�i�ϥ�
	EM_GameMessageEvent_MagicError_PetNotFound			,	//�䤣���d��

	EM_GameMessageEvent_MagicError_UseItemtoItem		,	//�ϥΪ��~��
	EM_GameMessageEvent_MagicError_CanNotMove			,	//���i���ʬI�k
	EM_GameMessageEvent_MagicError_IsSit				,	//���U���i�I�k

	EM_GameMessageEvent_MagicError_TargetLineNotClear	,	//�L�k�ݨ�ؼ�
	EM_GameMessageEvent_MagicError_Ride					,	//�M������ϥ�
	EM_GameMessageEvent_MagicError_Need1HWeapon			,	//�ݭn�����Z���~�i�ϥ�

	EM_GameMessageEvent_MagicError_NeedMagicCritical	,	//�k�N�z����~�i�ϥ�
	EM_GameMessageEvent_MagicError_NeedBeMagicCritical	,	//�Q�k�N�z����~�i�ϥ�
	EM_GameMessageEvent_MagicError_Normal				,	//�I�k����
	EM_GameMessageEvent_MagicError_InWater				,	//�������i�ϥ�
	EM_GameMessageEvent_MagicError_NotInWater			,	//�����~�i�H�ϥ�
	EM_GameMessageEvent_MagicError_SoulPointNotEnough	,	//SoulPoint����

	//�ө�
	EM_GameMessageEvent_Shop_NotCloseYet		= 200	,	//������A�S�Ѱ�
	EM_GameMessageEvent_Shop_ACOpenYet					,	//����ҥ��b�}�Ҥ�
	EM_GameMessageEvent_Shop_MailOpenYet				,	//�l�󥿦b�}�Ҥ�
	EM_GameMessageEvent_Shop_ShopOpenYet				,	//�ө����b�}�Ҥ�
	EM_GameMessageEvent_Shop_BankOpenYet				,	//�Ȧ楿�b�}�Ҥ�
	EM_GameMessageEvent_Shop_ChangeJobOpenYet			,	//�����������b�}�Ҥ�
	EM_GameMessageEvent_Shop_BillBoardOpenYet			,	//�Ʀ�]�������b�}�Ҥ�

	EM_GameMessageEvent_Shop_ACNoOpen					,	//������٨S�}��
	EM_GameMessageEvent_Shop_MailNoOpen					,	//�l���٨S�}��
	EM_GameMessageEvent_Shop_ShopNoOpen					,	//�ө��٨S�}��
	EM_GameMessageEvent_Shop_BankNoOpen					,	//�Ȧ��٨S�}��
	EM_GameMessageEvent_Shop_ChangeJobNoOpen			,	//�����٨S�}��
	EM_GameMessageEvent_Shop_BillBoardNoOpen			,	//�Ʀ�]�٨S�}��

	EM_GameMessageEvent_Shop_ItemNotSell				,	//�S�榹���~
	EM_GameMessageEvent_Shop_CountTooMany				,	//�ʶR�L�h	
	EM_GameMessageEvent_Shop_ItemNotExist				,	//�����~���s�b
	EM_GameMessageEvent_Shop_CountError					,	//�ʶR�ƶq�����D
	EM_GameMessageEvent_Shop_NoSellAccountItem			,	//���i�ʶR�I�ưӫ~
	EM_GameMessageEvent_Shop_MomeyNotEnought			,	//���B����
	EM_GameMessageEvent_Shop_BagFull					,	//�]�q���F
	EM_GameMessageEvent_Shop_SellDataError				,	//���~��Ƥ���
	EM_GameMessageEvent_Shop_SellItemOnUse				,	//���~�٦b�ϥΤ�
	EM_GameMessageEvent_Shop_CanNotSell					,	//�����~���i��
	EM_GameMessageEvent_Shop_PepairDataError			,	//���~��Ƥ���

	EM_GameMessageEvent_Shop_CreateNewGuildOpenYet		,	//�إ߳s�p���|�}�Ҥ�
	EM_GameMessageEvent_Shop_GuildContributionOpenYet	,	//���|�^�m�}�Ҥ�
	EM_GameMessageEvent_Shop_GuildShopOpenYet			,	//���|�ө��}�Ҥ�

	EM_GameMessageEvent_Shop_LotteryBuyShopOpenYet		,	//�m���ө��}�Ҥ�
	EM_GameMessageEvent_Shop_LotteryExchangeShopOpenYet	,	//�m���I���}�Ҥ�

	EM_GameMessageEvent_Shop_VisitHousesOpenYet			,	//�Ыΰ��[�����}�Ҥ�	


	//�˳�
	EM_GameMessageEvent_EQError_WearPos_Body	=250	,	//�˳Ʀ�m�����D
	EM_GameMessageEvent_EQError_DataInfo_Body			,	//�˳Ƹ�Ʀ����D
	EM_GameMessageEvent_EQError_OrgObjID_Body			,	//�˳ƪ��󦳰��D

	EM_GameMessageEvent_EQError_WearPos_Bank			,	//�˳Ʀ�m�����D
	EM_GameMessageEvent_EQError_DataInfo_Bank			,	//�˳Ƹ�Ʀ����D
	EM_GameMessageEvent_EQError_OrgObjID_Bank			,	//�˳ƪ��󦳰��D

	EM_GameMessageEvent_EQError_WearPos_EQ				,	//�˳Ʀ�m�����D
	EM_GameMessageEvent_EQError_DataInfo_EQ				,	//�˳Ƹ�Ʀ����D
	EM_GameMessageEvent_EQError_OrgObjID_EQ				,	//�˳ƪ��󦳰��D

	EM_GameMessageEvent_EQError_PKProtectCountError		,	//�˳ƫO�@�����W�L8��
	EM_GameMessageEvent_EQError_WearPos_ItemUnique		,	//�P�@�������k�_���i�H�˳ƨ�ӥH�W

	//�n���W��
	EM_GameMessageEvent_FriendList_DelError		=300	,	//�R���n�ͦ����D

	//���|
	EM_GameMessageEvent_Guild_GuildNoFound		=350	,	//�ۤv�S�����|
	EM_GameMessageEvent_Guild_NoGuild					,	//�S�����|
	EM_GameMessageEvent_Guild_GuildIsReady				,	//�w�g�O�������|
	EM_GameMessageEvent_Guild_NotLeader					,	//�D���|�|��
	EM_GameMessageEvent_Guild_TargetNotOnline			,	//���H���b�u�W
	EM_GameMessageEvent_Guild_LeaderNotOnline			,	//���|�|�����b�u�W
	EM_GameMessageEvent_Guild_GuildIsNotReady			,	//�٦b�s�p��
	EM_GameMessageEvent_Guild_NoInviteRight				,	//�S���ܽХ[�J���v��
	EM_GameMessageEvent_Guild_InviterNotOnline			,	//�ܽЪ̤��b�u�W
	EM_GameMessageEvent_Guild_MaxMember					,	//���|�w��H�ƤW��
	EM_GameMessageEvent_Guild_HasGuild					,	//�w�֦����|
	EM_GameMessageEvent_GuildWar_PlayerCountFull		,	//�Գ��H�Ƥw��
	EM_GameMessageEvent_GuildWar_CantInvite				,	//�{�b���b�i�椽�|���ԡA����s�W�����I

	//���~
	EM_GameMessageEvent_Item_OrgObjIDError		=400	,	//�����Ʀ����D
	EM_GameMessageEvent_Item_NotItem					,	//�D���~
	EM_GameMessageEvent_Item_PosError					,	//�n�D�񪺦�m�����D
	EM_GameMessageEvent_Item_Queue_PosError				,	//�n�D�񪺦�m�����D
	EM_GameMessageEvent_Item_Queue_BufferEmpty			,	//���~�ǦC���O�Ū�
	EM_GameMessageEvent_Item_Queue_DataError			,	//���~��ƿ��~
	EM_GameMessageEvent_Item_Queue_CountError			,	//���~�ƶq���~
	EM_GameMessageEvent_Item_DelError					,	//��ƧR�����~
	EM_GameMessageEvent_Item_ExchangeError				,	//���~�洫�����D
	EM_GameMessageEvent_Item_BankOpenError				,	//�Ȧ�}�Ҫ��p�����D
	EM_GameMessageEvent_Item_BankTooFar					,	//�Ȧ�Z���L��
	EM_GameMessageEvent_Item_ExchangeMoneyError			,	//�����洫�����D
	EM_GameMessageEvent_Item_CountError					,	//�ƶq�����D
	EM_GameMessageEvent_Item_DisableTrade				,	//����\��Q�T��
	EM_GameMessageEvent_Item_ColoringFailed				,	//�V�⥢��
	EM_GameMessageEvent_Item_ResetAbilityFailed			,	//�����O�t�I�w���]
	EM_GameMessageEvent_Item_ResetSkillPointFailed		,	//����ޯ�t�I�w���]
	EM_GameMessageEvent_Item_EmptyPacketErr				,	//�]�q�Ŧ줣��
	EM_GameMessageEvent_Item_MagicDisableUseItem		,	//���~�ϥθT�
	EM_GameMessageEvent_Item_TargetDisableTrade			,	//�ؼХ���\��Q�T��
	EM_GameMessageEvent_Item_ItemUniqueErr				,	//�R�����ƨ��o���ߤ@���~
	EM_GameMessageEvent_Item_ItemLock					,	//���~�K�X��O�@��
	EM_GameMessageEvent_Item_LimitErr					,	//�ϥα��󤣲ŦX

	//PK
	EM_GameMessageEvent_PK_PKError				=450	,	//PK�B�z�����D
	EM_GameMessageEvent_PK_InviteError					,	//�w�n�Ш�L�ؼ�
	EM_GameMessageEvent_PK_Prepar						,	//�w�bPK�ǳƤ�
	EM_GameMessageEvent_PK_Begin						,	//�w�bPK��
	EM_GameMessageEvent_PK_TargetNotExist				,	//�ؼФ��s�b
	EM_GameMessageEvent_PK_TargetTooFar					,	//�ؼйL��
	EM_GameMessageEvent_PK_TargetInviteOther			,	//�ؼЭn�Ш�L�H
	EM_GameMessageEvent_PK_TargetPK						,	//�ؼ�PK��
	EM_GameMessageEvent_PK_PKInviteResultError			,	//PK�^����Ʀ����D

	//Trade
	EM_GameMessageEvent_Trade_ItemError			=500	,	//������~�����D
	EM_GameMessageEvent_Trade_CanNotTrade				,	//���~���i���
	EM_GameMessageEvent_Trade_CanNotModify				,	//����T�w�ᤣ�i�ק�
	EM_GameMessageEvent_Trade_PosError					,	//��m��m�����D
	EM_GameMessageEvent_Trade_PosOnLock					,	//���~��w��
	EM_GameMessageEvent_Trade_MoneyError				,	//�������t��
	EM_GameMessageEvent_Trade_AccountError				,	//�Ť�����t��
	EM_GameMessageEvent_Trade_MoneyNotEnough			,	//��������
	EM_GameMessageEvent_Trade_AccountNotEnough			,	//�I�Ƥ���
	EM_GameMessageEvent_Trade_Error						,	//�������
	EM_GameMessageEvent_Trade_RelationItemError			,	//���Y���~�u���W���
	EM_GameMessageEvent_Trade_RelationErr				,	//���Y�إߥ���
	EM_GameMessageEvent_Trade_RelationOK				,	//���߷s���Y


	//�I���T��
	EM_GameMessageEvent_ItemExchange_IsUse		=550	,	//�I�����~�w�Q�ϥ�
	EM_GameMessageEvent_ItemExchange_NotFound			,	//�䤣�즹���~


	//���s
	EM_GameMessageEvent_Socal_AddFriendNoPeople		= 600,	// �s�W�n�ͥ����\�A���w���u
	EM_GameMessageEvent_Socal_AddFriendNoOwner		,		// �s�W�n�ͥ����\�A�ܽФH�w���u
	EM_GameMessageEvent_Socal_AddFriendRefuse		,		// ���ڵ��A���n���ܽ�

	//�˳ƦX��
	EM_GameMessageEvent_EQCombin_OpenYet			= 650,	//�˳ƦX�������}�Ҥ�
	EM_GameMessageEvent_AccountBag_OpenYet			,		//�b���I�]�����}�Ҥ�

	//�]�w�����v���T��
	EM_GameMessageEvent_Role_Right_NoSpeak			= 700,	//GM��A �ä[�T��
	EM_GameMessageEvent_Role_Right_Speak			,		//GM��A �Ѱ��T��
	EM_GameMessageEvent_Role_Right_NoTrade			,		//GM��A �ä[�T����
	EM_GameMessageEvent_Role_Right_Trade			,		//GM��A �Ѱ��T����
	EM_GameMessageEvent_Role_Untrust				,		//�A���b���ثe�L�k�ϥΦ��\��

	//Chat�T��		
	EM_GameMessageEvent_Mail_BagFull				= 750,	//�I�]�w��,�L�k�����H��

	//���|�θ�T
	EM_GameMessageEvent_GuildHouse_GuildInfoError	= 800 ,	//�D�ۤv���ݤ��|
	EM_GameMessageEvent_GuildHouse_RightError			,	//�S���s�����v��
	EM_GameMessageEvent_GuildHouse_ItemNoTrade			,	//�����~�����J���|�ܮw
	EM_GameMessageEvent_GuildHouse_ItemCountError		,	//�s�����|�ܮw���~�L�q
	EM_GameMessageEvent_GuildHouse_FurnitureFull		,	//�a�Ѥw��
	EM_GameMessageEvent_GuildHouse_FurnitureError		,	//�����~������|���\�]�~
	EM_GameMessageEvent_GuildHouse_FurnitureNotYours	,	//�����~���O�ݩ�A��
	EM_GameMessageEvent_GuildHouse_TooNearBuilding		,	//�ؿv�ɤӾa��ت��A�Ǩ줽�|�J�f�B

	//�Գ�
	EM_GameMessageEvent_BattleGround_RoomAndDataExist		= 850,	//�W�@���Գ���������, �A���ݵ��ݾԳ�������i�i�J


	EM_GameMessageEvent_Pet_Hunger_Full				= 900	,	//�d���w�Y��
	EM_GameMessageEvent_Pet_Loyal_Full						,	//�d�����۫פw��
	EM_GameMessageEvent_Pet_BagFull							,	//�I�]�w��,�L�k����
};

enum	GameMessageEventDataENUM
{	
	//�ө�
	EM_GameMessageEventData_None						,
	EM_GameMessageEventData_ShopBuy						,	//�ө��R [�ʶR %sx%d �@%d��]
	EM_GameMessageEventData_ShopSell					,	//�ө��� [�c�� %sx%d ��o%d��]
	EM_GameMessageEventData_ZoneChannelLevelErr			,	//�ܤ֭n���@��¾�~���ŶW�L %d �šA�~�i�ϥΰϰ��W�D�I
	EM_GameMessageEventData_Guild_TargetCanNotInvite	,	//���ܽЪ����a�h�X�e���|�ɶ� %d:%d �C1�p�ɤ����o�[�J���|�I

};
//-------------------------------------------------------------------------------------
//�w�q�����MP �٬O SP
enum	GameRoleMPSPUseTypeENUM
{
	EM_GameRoleMPSPUseType_None		,	//���S��
	EM_GameRoleMPSPUseType_MP		,	//��mp
	EM_GameRoleMPSPUseType_SP		,	//��sp

};
//-------------------------------------------------------------------------------------
//���a�欰��ưO��
struct PlayerActionMode
{
	union
	{
		int	_Mode;
		struct  
		{
			bool	Fight		:1;
			bool	Trade		:1;
			bool	Mail		:1;
			bool	AC			:1;
			bool	Shop		:1;
			bool	ChangeJob	:1;
			bool	DailyQuest	:1;
			bool	DailyFlag	:1;
		};
	};
};

struct PlayerActionLogStruct
{
	PlayerActionMode ActionMode;

	int	DeadCount;			//���`����
	int	KillCount;			//��������
	int	Exp;				//�o�_�ɶ����g���
	int	Exp_TP;
	int	LastMoney;			//�̫��x�s������
	int	SavePlayTime;		//�̫��x�s���ɶ�
	int	LastMoney_Account;	//�̫��x�s���b����r
	void Init()
	{
		memset( this , 0 , sizeof(*this));
	}
};
//--------------------------------------------------------------------------------------------
//�Ʀ�]
//--------------------------------------------------------------------------------------------
//�浧�Ʀ���
struct DB_BillBoardRoleInfoStruct
{
	int					Rank_Money;
	int					Rank_Title;				
	int					Rank_PKScore;				

	union
	{
		int				Rank_Job[8];
		struct  
		{
			int					Rank_Job_Warrior;		
			int					Rank_Job_Ranger;			
			int					Rank_Job_Rogue;			
			int					Rank_Job_Wizard;			
			int					Rank_Job_Priest;			
			int					Rank_Job_Knight;			
			int					Rank_Job_RuneDancer;		
			int					Rank_Job_Druid;			
		};
	};

	union
	{
		int				JobLv[8];
		struct  
		{
			int					JobLv_Warrior;		
			int					JobLv_Ranger;			
			int					JobLv_Rogue;			
			int					JobLv_Wizard;			
			int					JobLv_Priest;			
			int					JobLv_Knight;			
			int					JobLv_RuneDancer;		
			int					JobLv_Druid;			
		};
	};

	bool				IsAnonymous;	//�ΦW

	StaticString< _MAX_NAMERECORD_SIZE_ > RoleName;
	int					DBID;			//��ƮwID

	Voc_ENUM		    Voc;			//¾�~
	Voc_ENUM		    Voc_Sub;		//��¾�~
//	int					Lv;				//¾�~����
//	int					Lv_Sub;			//��¾�~����

	int 				Money;
	int					TitleCount;		//�Y�μƶq
	int					PKScore;		

	int					GetJobLv( int JobID )
	{
		if( JobID <= 0 || JobID >= 8 )
			return 0;
		return JobLv[ JobID ];
	}
};
//--------------------------------------------------------------------------------------------------------------------
//  AC�������
//--------------------------------------------------------------------------------------------------------------------
enum AcActionTypeENUM
{
	EM_AcActionType_Unknow = -1 		,	
	EM_AcActionType_Sell				,	//��J
	EM_AcActionType_Cancel				,	//����
	EM_AcActionType_Bid					,	//�U��
	EM_AcActionType_BuyOut				,	//����
	EM_AcActionType_DrawBack			,	//(�Q�H�v�� or �����)
	EM_AcActionType_Deal				,	//����
	EM_AcActionType_NoDeal				,	//�S����
	EM_AcActionType_SendMoneytoSeller	,	//��������H�e
};

//--------------------------------------------------------------------------------------------------------------------
//  ���~�������
//--------------------------------------------------------------------------------------------------------------------
enum ActionTypeENUM
{
	EM_ActionType_Unknow				,
	EM_ActionType_LevelUp				,//�ɯ�
	EM_ActionType_EnterWorld			,//�J�C��
	EM_ActionType_LeaveWorld			,//���}�C��
	EM_ActionType_Buy					,//�R
	EM_ActionType_Buy_Record			,//�R �L�h�汼��
	EM_ActionType_Sell					,//��
	EM_ActionType_Tran					,//���a���
	EM_ActionType_Get					,//�ߨ��a�W
	EM_ActionType_Drop					,//���a�W
	EM_ActionType_GMGive				,//GM����
	EM_ActionType_PlotGive				,//�@������
	EM_ActionType_PlotDestory			,//�@���R��
	EM_ActionType_KillMonster			,//���Ǫ�
	EM_ActionType_DestroyItem			,//���~����
	EM_ActionType_ErrorDestory			,//���~�M��
	EM_ActionType_MagicSummonItem		,//�]�k�l�ꪫ�~
	EM_ActionType_MagicDestory			,//�]�k�ݨD�Ĥ�	
	EM_ActionType_UseItemGive			,//���~�ϥε���
	EM_ActionType_UseItemDestroy		,//���~�ϥή���
	EM_ActionType_OffLienDestory		,//���u����
	EM_ActionType_ChangeZoneDestory		,//���Ϯ���
	EM_ActionType_GiveSystem			,//���ػP�t�ε����~
	EM_ActionType_CombineGet			,//�һs�o��
	EM_ActionType_CombineDestory		,//�һs���h
	EM_ActionType_Steal					,//����
	EM_ActionType_ToAC					,//������
	EM_ActionType_ToACError				,//�����Ұh�^(�����~)
	EM_ActionType_ToMail				,//������
	EM_ActionType_ToMailError			,//�����Ұh�^(�����~)
	EM_ActionType_FromMail				,//��Mail���o
	EM_ActionType_FromParty				,//��Party����
	EM_ActionType_Dissolution			,//����
	EM_ActionType_ACTex					,//�ϥΩ��ҩһ�
	EM_ActionType_ACBuy					,//���ҶR�F��
	EM_ActionType_Money					,//�Ȳ�
	EM_ActionType_Card					,//�d��
	EM_ActionType_Gamble				,//���
	EM_ActionType_ItemExchange			,//�I�����~
	EM_ActionType_Buy_Account			,//�I�ưӫ~�ʶR
	EM_ActionType_Buy_Lottery			,//�R�m��
	EM_ActionType_Gather				,//�Ķ�
	EM_ActionType_EqBroken				,//�˳Ʒl�a
	EM_ActionType_SysChannel			,//�t���W�D���Ӫ��~
	EM_ActionType_ColoringShop_Player	,//�V��ө�(�󴫷ӫ�)
	EM_ActionType_Lottery_Prize			,//�m��
	EM_ActionType_CreateGuild			,//�إߤ��|
	EM_ActionType_FixEQ					,//�׸˳�
	EM_ActionType_BuyHouseEnergy		,//�R�Ыί�q
	EM_ActionType_ImportAccountMoney	,//�פJ�b����		
	EM_ActionType_QuestComplete			,//��������
	EM_ActionType_Exp					,//�g��ȧ���
	EM_ActionType_PlayerDead			,//���a���`
	EM_ActionType_MonsterDead			,//�Ǫ����`
	EM_ActionType_RefineFailedDestroy	,//����ɵ����Ѯ��� 
	EM_ActionType_EQCombineDestroy		,//�˳ƦX������ 	
	EM_ActionType_GuildWarDeclare		,//���|�žԪ���
	EM_ActionType_RefineLvUp			,//����ɵ�
	EM_ActionType_RefineLvDn			,//���孰��
	EM_ActionType_RefineNone			,//����S����
	EM_ActionType_RefineProtect			,//����O�@
	EM_ActionType_Reserve				,//(�O�d)
	EM_ActionType_PKItemProtect			,//PK���~�g�v�O�@
	EM_ActionType_PKDropItem			,//PK����
	EM_ActionType_Loot					,//�˫�
	EM_ActionType_MagicBox				,//�_�c�ĦX
	EM_ActionType_GuildContribution		,//���|�^�m
	EM_ActionType_SellMailGroup			,//�s�o�H��
	EM_ActionType_TimeUp				,//�ɶ���R��
	EM_ActionType_GuildStoreHouse_Put	,//���|�ܮw(��J)
	EM_ActionType_GuildHouse_Funiture_Put,//���|�\�](��J)
	EM_ActionType_OpenPacket			,//���}�ӫ����]
	EM_ActionType_ColoringShop_Horse	,//�V��ө�(���M�V��)
	EM_ActionType_Rent_BackPacket		,//���έI�]���
	EM_ActionType_Rent_BankPacket		,//���λȦ����
	EM_ActionType_Rent_Bank				,//�����H���Ȧ�
	EM_ActionType_Rent_Mail				,//�����H���H�c
	EM_ActionType_Rent_AC				,//�����H�������
	EM_ActionType_Buy_Account_Gift		,//�ʶR�ӫ�§��
	EM_ActionType_Buy_Account_Bonus		,//�ӫ����Q���ʶR
	EM_ActionType_Buy_Account_Free		,//�ӫ������B	�ʶR
	EM_ActionType_Plant_Product			,//�ش�(����)
	EM_ActionType_Plant_Destroy			,//�ش�(�R��)
	EM_ActionType_GuildStoreHouse_Get	,//���|�ܮw(���X)
	EM_ActionType_GuildHouse_Funiture_Get,//���|�\�](���X)
	EM_ActionType_Card_Destroy			,//�d����J
	EM_ActionType_MagicBox_Destroy		,//�]���_���R��
	EM_ActionType_PetRetrain_Destroy	,//�d��������R��
	EM_ActionType_Attribute_Gamble		,//���~�ݩʽ��
	EM_ActionType_GMDestroy				,//GM�R��
	EM_ActionType_BodyShop				,//�ק鶴��
	EM_ActionType_QuestDelete			,//�R������
	EM_ActionType_EQCombineResult		,//���~�X�����G
	EM_ActionType_MagicBoxResult		,//�]���_���X�����G
	EM_ActionType_ItemtoItemResult		,//���~�磌�~�ϥε��G
	EM_ActionType_MagicStoneShop		,//�]�ۧI���ө�
	EM_ActionType_ServantHire			,//���Τk��
	EM_ActionType_SuitSkillCost			,//�M�˧ޯ���O����
	EM_ActionType_DestroyItem_Buy		,//�ʶR����
	EM_ActionType_DestroyItem_PetTriMerge		,//�d���ĦX����
	EM_ActionType_DestroyItem_DrawOutRune		,//���X�Ť�
	EM_ActionType_DestroyItem_CoolSuit			,//�M�˦��d
	EM_ActionType_DestroyItem_CloneItem			,//�ìO�ƻs���~�R��
	EM_ActionType_DestroyItem_ErrItem			,//���D���~�R��
	EM_ActionType_Rare3EqExchangeItem			,//�}���פT�����~�I���R��
	EM_ActionType_DestroyItem_CloneItem_House	,//�ìO�ƻs���~�R��(�Ы�)
	EM_ActionType_PetBag_In						,//��J�d���]
	EM_ActionType_PetBag_Out					,//���X�d���]
	EM_ActionType_HorseBag_In					,//��J���M�]
	EM_ActionType_HorseBag_Out					,//���X���M�]
	EM_ActionType_ClsItemAttribute				,//
	EM_ActionType_PutItemToWarDrobe				,//��F���J���o�ݨD��
	EM_ActionType_BG_IndependenceGame			,//�Գ��W�߹C��
	EM_ActionType_SlotMachine					,//���l�Ѫ��

	EM_ActionType_BUY_COOLSUITPAGE				,//�R�]�k���o
	EM_ActionType_BUY_COOLSUITSET				,//�R�Ÿ˳]�w

	EM_ActionType_Item_ClsAttribute				,//�ϥ��ݩʲM���
	EM_ActionType_Item_DrawAttribute			,//�ϥ��ݩʩ����
	EM_ActionType_WeekInstReset					,//���m�C��ƥ�����
	EM_ActionType_LuaSetItemInfo				,//Lua�ק磌�~��T
	EM_ActionType_LoginBonus					,//�C��n�J§
};
//-------------------------------------------------------------------------------------
//���|log����
enum GuildActionTypeENUM
{
	EM_GuildActionType_CreateNewGuild	,//�إ߷s���|
	EM_GuildActionType_JoinNewGuild		,//�[�J�p�ݤ��|
	EM_GuildActionType_LeaveNewGuild	,//���}�p�ݤ��|
	EM_GuildActionType_DestroyNewGuild	,//�R���p�ݤ��|
	EM_GuildActionType_RegularGuild		,//�����������|
	EM_GuildActionType_Destroy			,//�R�����|
	EM_GuildActionType_Join				,//�[�J���|
	EM_GuildActionType_Leave			,//���}���|
	EM_GuildActionType_AddScore			,//�W�[���|�n��
	EM_GuildActionType_BuyFuntion		,//�R���|�\��
	EM_GuildActionType_ChangeLeader		,//�󴫷|��
};
//-------------------------------------------------------------------------------------
//����S������
enum SpecialEfficacyTypeENUM
{
	EM_SpecialEfficacyType_ChangeJob	,	//��¾�~
	EM_SpecialEfficacyType_Unknow		,
};
//-------------------------------------------------------------------------------------
enum	PKStateENUM
{
	EM_PKState_None				,		//�@�몬�A
	EM_PKState_Invite			,		//�n��
	EM_PKState_Prepare			,		//�ǳ�PK
	EM_PKState_Begin			,		//�}�lPK
	EM_PKState_Begin_OutRange	,		//�}�lPK �W�L�d��
	EM_PKState_End				,		
};
//pk���
struct PKInfoStruct
{
	int				TargetID;
	int				TargetDBID;
	PKStateENUM		State;
	int				Clock;			//�ɶ�
	float			X ,Y, Z;		//�n�Ц�m

	void Init()
	{
		memset( this , 0 , sizeof( *this ) );
	}
};
//-------------------------------------------------------------------------------------
struct AttachObjInfoStruct
{
	int		ItemID;		//�s��������
	int		Type;		//�s������
	string	ItemPos;	//�s����m
	string	WagonPos;

	void Init()
	{
		ItemID = -1;
		Type = 0;
		ItemPos.clear();
		WagonPos.clear();
	}
	bool IsEmpty()
	{
		return ItemID == -1;
	}
};
//-------------------------------------------------------------------------------------
//���ϸ�T
struct ChangeZoneInfoStruct
{
	int		CopyRoomID;		//�n�Ҩ����ж�
};
//-------------------------------------------------------------------------------------
//���ϸ�T
struct BattleGroundInfoStruct
{
	//int		CopyRoomID;		//�n�Ҩ����ж�
	int			iKillVal;		// �����ĤH����
	int			iDeadVal;		// ���`����
	int			iDamageVal;		// ���\�y���ˮ`���ƶq
	int			iHealVal;		// ���\�v���q	
	
	int			iForceFlagID;	// �j��I�t�X�l�N��
	int			iCampID;		// �]�w�}�窺�N��
	int			iDefVal;		// ���m�q
	//int			iTemp_3_Val;	// �Ȯɥ��O�d
};
//-------------------------------------------------------------------------------------
//�Ť��ˬd���G
enum CheckAddRuneResultENUM
{
	EM_CheckAddRuneResult_OK				,	//OK
	EM_CheckAddRuneResult_TargetItemErr		,	//�ؼЪ��~�����D
	EM_CheckAddRuneResult_NotRune			,	//���O�Ť�
	EM_CheckAddRuneResult_RuneVolumeErr		,	//�Ť�e�q����
	EM_CheckAddRuneResult_WeaponErr			,	//�^�O�Z�����������D
	EM_CheckAddRuneResult_ArmorErr			,	//�^�O�������������D
	EM_CheckAddRuneResult_Unknow			,	//�������~
	EM_CheckAddRuneResult_RuneDuplicate		,	//�Ť孫�_
	EM_CheckAddRuneResult_RuneFull			,	//�Ť庡��
	EM_CheckAddRuneResult_LevelError		,	//�ϥΪ����Ŧ����D
};
//-------------------------------------------------------------------------------------
//�˳ƽĵ��ˬd���G
enum CheckEqRefineResultENUM
{
	EM_CheckEqRefineResult_OK					,	//OK
	EM_CheckEqRefineResult_DataErr				,	//��Ʀ����D
	EM_CheckEqRefineResult_MaxLevel				,	//�w�쵥�ŤW��
	EM_CheckEqRefineResult_NotWeapon			,	//�u�����Z������
	EM_CheckEqRefineResult_NotArmor				,	//�u����娾������
	EM_CheckEqRefineResult_NotJewels			,	//�u����孺������
	EM_CheckEqRefineResult_ItemLimitMinLevel	,	//�i����Z�����ŤӧC���D
	EM_CheckEqRefineResult_ItemLimitMaxLevel	,	//�i����Z�����Ťw�F�W��
	EM_CheckEqRefineResult_NotOrnament			,	//�u��˹��~����
	EM_CheckEqRefineResult_CantRefine			,	//����ĵ�
};
//-------------------------------------------------------------------------------------
//�׸��ˬd���G
enum ChecFixEqResultENUM
{
	EM_CheckFixEqResult_OK				,	//OK
	EM_CheckFixEqResult_DataErr			,	//��Ʀ����D
	EM_CheckFixEqResult_NotFix			,	//���~����ײz
	EM_CheckFixEqResult_NotEQ			,	//�D�˳�
	EM_CheckFixEqResult_NewOne			,	//���~�S�l�a
	EM_CheckFixEqResult_NotEnoughMoney	,	//��������
};
//-------------------------------------------------------------------------------------
//��Ѫ��~�ˬd���G
enum CheckDissolutionResultENUM
{
	EM_CheckDissolutionResult_OK		,	//OK
	EM_CheckDissolutionResult_Err		,	//�����~���i���
};
//-------------------------------------------------------------------------------------
//���~�V���ˬd���G
enum CheckColoringResultENUM
{
	EM_CheckColoringResult_OK		,	//OK
	EM_CheckColoringResult_Err		,	//�����~���i�V��
};
//-------------------------------------------------------------------------------------
//���~�O�_�i�H�M��Soulbond
enum CheckClsSoulBoundResultENUM
{
	EM_CheckClsSoulBoundResult_OK					,	//OK
	EM_CheckClsSoulBoundResult_Err					,	//�����~���i�M��Soulbond
	EM_CheckClsSoulBoundResult_Err_NoSoulBound		,	//�����~�ثe�SSoulbond
	EM_CheckClsSoulBoundResult_Err_NoEqSoulBound	,	//�D�˳Ƹj�w����Ѱ�
};
//-------------------------------------------------------------------------------------
//�O�_�i�H���}
enum CheckDigHoleResultENUM
{
	EM_CheckDigHoleResult_OK				,	//OK
	EM_CheckDigHoleResult_TargetErr			,	//���i�惡���~���}
	EM_CheckDigHoleResult_SrcErr			,	//�ϥΪ��~�����D
	EM_CheckDigHoleResult_WeaponOnly		,	//�u���Z���ϥ�
	EM_CheckDigHoleResult_ArmorOnly			,	//�u��慨��ϥ�
	EM_CheckDigHoleResult_OrnamentOnly		,	//�u��﹢�~�ϥ�
	EM_CheckDigHoleResult_HoleErr			,	//�}�ƹL�h
	EM_CheckDigHoleResult_NotJewels		,	//�u��﹢�~�ϥ�
};
//-------------------------------------------------------------------------------------
//�O�_�i�H�M���Ť�
enum CheckClsRuneResultENUM
{
	EM_CheckClsRuneResult_OK				,	//OK
	EM_CheckClsRuneResult_TargetErr			,	//���i�惡���~���}
	EM_CheckClsRuneResult_SrcErr			,	//�ϥΪ��~�����D
};
//-------------------------------------------------------------------------------------
//�O�_�i�H���~�W��
enum CheckItemLockResultENUM
{
	EM_CheckItemLockResult_OK				,	//OK
	EM_CheckItemLockResult_TargetErr		,	//���i�惡���~���}
	EM_CheckItemLockResult_SrcErr			,	//�ϥΪ��~�����D
};
//-------------------------------------------------------------------------------------
//�O�_�i�H���~����
enum CheckItemUnLockResultENUM
{
	EM_CheckItemUnLockResult_OK				,	//OK
	EM_CheckItemUnLockResult_TargetErr		,	//
	EM_CheckItemUnLockResult_SrcErr			,	//
};
//-------------------------------------------------------------------------------------
//�˳Ƹj�w���G
enum CheckEQProtectResultENUM
{
	EM_CheckEQProtectResult_OK				,	//OK
	EM_CheckEQProtectResult_TargetErr		,	//
	EM_CheckEQProtectResult_SrcErr			,	//
};
//-------------------------------------------------------------------------------------
//
enum CheckEQLimitMaxResultENUM
{
	EM_CheckEQLimitMaxResult_OK				,	//OK
	EM_CheckEQLimitMaxResult_TargetErr		,	//
	EM_CheckEQLimitMaxResult_SrcErr			,	//
};
//-------------------------------------------------------------------------------------
//
enum CheckIgnoreLimitLvMaxResultENUM
{
	EM_CheckIgnoreLimitLvMaxResult_OK		,	//OK
	EM_CheckIgnoreLimitLvMaxResult_TargetErr,	//
	EM_CheckIgnoreLimitLvMaxResult_SrcErr	,	//
};
//-------------------------------------------------------------------------------------
//
enum CheckPkEqProtectResultENUM
{
	EM_CheckPkEqProtectResult_OK		,	//OK
	EM_CheckPkEqProtectResult_TargetErr,	//
	EM_CheckPkEqProtectResult_SrcErr	,	//
};
//-------------------------------------------------------------------------------------
//
enum CheckPkEqProtectcClearResultENUM
{
	EM_CheckPkEqProtectClearResult_OK		,	//OK
	EM_CheckPkEqProtectClearResult_TargetErr,	//
	EM_CheckPkEqProtectClearResult_SrcErr	,	//
};
//-------------------------------------------------------------------------------------
//
enum CheckClsEqAbilityResultENUM
{
	EM_CheckClsEqAbilityResult_OK		,	//OK
	EM_CheckClsEqAbilityResult_TargetErr,	//
	EM_CheckClsEqAbilityResult_SrcErr	,	//
};
//-------------------------------------------------------------------------
//���~�\�]���
struct House3DLayoutStruct
{
	union
	{
		int	Mode;
		struct
		{
			bool	IsShow : 1;
			bool	IsFriend_Put  : 1;	//�n�ͥi�s
			bool	IsFriend_Get  : 1;	//�n�ͥi��
			bool	IsFriend_Show : 1;	//�n�ͥi��
 			bool	IsSound : 1;	//�d�n��
		};
	};

	float X, Y, Z;       //��m
	float UpX, UpY, UpZ; //�W��V�q
	float Angle;         //���ਤ��

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	}
};
//////////////////////////////////////////////////////////////////////////
//�ЫΨt��
//////////////////////////////////////////////////////////////////////////
#define MAX_HOUSE_CLIENT_DATA_SIZE_	2048
#define MAX_HOUSE_STRING_SIZE	256

#define MAX_HOUSE_ITEM_LOG_COUNT 100
struct HouseFriendItemLogStruct
{
	int		Time;
	int		FriendDBID;
	int		ItemID;
	int		Count;
};

#define MAX_SERVANT_COUNT	6
#define MAX_SERVANT_FLAG	256

enum HouseServantValueTypeENUM
{
	EM_HouseServantValueType_NPCObjID	,
	EM_HouseServantValueType_Character	,
	EM_HouseServantValueType_Sex		,
	EM_HouseServantValueType_Tired		,	//�h�Ϋ�
	EM_HouseServantValueType_Value0		,	// 0-7 �򥻼ƭ�
	EM_HouseServantValueType_Value1		,
	EM_HouseServantValueType_Value2		,
	EM_HouseServantValueType_Value3		,
	EM_HouseServantValueType_Value4		,
	EM_HouseServantValueType_Value5		,
	EM_HouseServantValueType_Value6		,
	EM_HouseServantValueType_Value7		,
	EM_HouseServantValueType_MaxValue0	,	// 0-7 �̤j�򥻼ƭ�
	EM_HouseServantValueType_MaxValue1	,
	EM_HouseServantValueType_MaxValue2	,
	EM_HouseServantValueType_MaxValue3	,
	EM_HouseServantValueType_MaxValue4	,
	EM_HouseServantValueType_MaxValue5	,
	EM_HouseServantValueType_MaxValue6	,
	EM_HouseServantValueType_MaxValue7	,
	EM_HouseServantValueType_ClothColor0,	// 0-1 ��A�C��
	EM_HouseServantValueType_ClothColor1,
	EM_HouseServantValueType_Flag		= 1000,	// 0-255 �k���M�ݺX��	
};

struct HouseServantStruct
{	
//	bool		IsSave;										//��ƬO�_�w�s�b
	union
	{
		int		Mode;
		struct
		{
			bool IsSave : 1;		//�O�_�x�s
			bool IsHire : 1;		//�O�_�Q����
		};
	};

	StaticString< _MAX_NAMERECORD_SIZE_ >	Name;			//�W��
	int CreateTime;
	int NPCObjID;
	int	MaxValue[8];
	int	Value[8];
	int	ClothColor[2];
	int	Character;											//����ө�
	int	Sex;												//0 �k 1 �k 2 �Ǫ�
	int	Cost;
	int	Tired;												//�h�Ϋ�

	StaticFlag<MAX_SERVANT_FLAG>	Flag;		//
	LookStruct Look;
	House3DLayoutStruct	Layout;

	HouseServantStruct()
	{
		Init();
	};
	void Init()
	{
		memset( this , 0 , sizeof(*this));
	}

	int		ReadValue( HouseServantValueTypeENUM Type )
	{
		int ID = Type - EM_HouseServantValueType_Flag;

		if( (unsigned)ID < MAX_SERVANT_FLAG )
		{
			return (int)Flag.GetFlag( ID );
		}
		
		switch( Type )
		{
		case EM_HouseServantValueType_NPCObjID:
			return NPCObjID;
		case EM_HouseServantValueType_Character:
			return Character;
		case EM_HouseServantValueType_Sex:
			return Sex;
		case EM_HouseServantValueType_Tired:
			return Tired;
		case EM_HouseServantValueType_Value0:	// 0-7 �򥻼ƭ�
		case EM_HouseServantValueType_Value1:
		case EM_HouseServantValueType_Value2:
		case EM_HouseServantValueType_Value3:
		case EM_HouseServantValueType_Value4:
		case EM_HouseServantValueType_Value5:
		case EM_HouseServantValueType_Value6:
		case EM_HouseServantValueType_Value7:
			return Value[ Type - EM_HouseServantValueType_Value0 ];
		case EM_HouseServantValueType_MaxValue0:	// 0-7 �̤j�򥻼ƭ�
		case EM_HouseServantValueType_MaxValue1:
		case EM_HouseServantValueType_MaxValue2:
		case EM_HouseServantValueType_MaxValue3:
		case EM_HouseServantValueType_MaxValue4:
		case EM_HouseServantValueType_MaxValue5:
		case EM_HouseServantValueType_MaxValue6:
		case EM_HouseServantValueType_MaxValue7:
			return MaxValue[ Type - EM_HouseServantValueType_MaxValue0 ];
		case EM_HouseServantValueType_ClothColor0:	// 0-1 ��A�C��
			return ClothColor[0];
		case EM_HouseServantValueType_ClothColor1:
			return ClothColor[1];
		}
		return 0;
	}

	bool	WriteValue(	HouseServantValueTypeENUM Type , int V )
	{
		int ID = Type - EM_HouseServantValueType_Flag;

		if( (unsigned)ID < MAX_SERVANT_FLAG )
		{
			if( V == 0 )
				Flag.SetFlagOff( ID );
			else
				Flag.SetFlagOn( ID );
			return true;
		}

		switch( Type )
		{
		case EM_HouseServantValueType_NPCObjID:
//			NPCObjID = V;
			return false;
		case EM_HouseServantValueType_Character:
			Character = V;
			return true;
		case EM_HouseServantValueType_Sex:
			Sex = V;
			return true;
		case EM_HouseServantValueType_Tired:
			Tired = V;
			return true;
		case EM_HouseServantValueType_Value0:	// 0-7 �򥻼ƭ�
		case EM_HouseServantValueType_Value1:
		case EM_HouseServantValueType_Value2:
		case EM_HouseServantValueType_Value3:
		case EM_HouseServantValueType_Value4:
		case EM_HouseServantValueType_Value5:
		case EM_HouseServantValueType_Value6:
		case EM_HouseServantValueType_Value7:
			Value[ Type - EM_HouseServantValueType_Value0 ] = V;
			return true;
		case EM_HouseServantValueType_MaxValue0:	// 0-7 �̤j�򥻼ƭ�
		case EM_HouseServantValueType_MaxValue1:
		case EM_HouseServantValueType_MaxValue2:
		case EM_HouseServantValueType_MaxValue3:
		case EM_HouseServantValueType_MaxValue4:
		case EM_HouseServantValueType_MaxValue5:
		case EM_HouseServantValueType_MaxValue6:
		case EM_HouseServantValueType_MaxValue7:
			MaxValue[ Type - EM_HouseServantValueType_MaxValue0 ] = V;
			return true;
		case EM_HouseServantValueType_ClothColor0:	// 0-1 ��A�C��
			ClothColor[0] = V;
			return true;
		case EM_HouseServantValueType_ClothColor1:
			ClothColor[1] = V;
			return true;
		}
		return false;
	}
	
};


//�Ыθ�Ʈw��T
struct HouseBaseDBStruct
{
	int			HouseDBID;	
	int			MaxItemCount;
	int			EnergyPoint;
	int			HouseType;
	unsigned	LastRantelTime;										//�̫�@�������������ɶ�
	int			OwnerDBID;
	StaticString< _MAX_NAMERECORD_SIZE_ >		Password;
	StaticFlag<_MAX_HOUSES_SHOPFUNCTION_COUNT_>	ShopFunction;		//�ϥΪ��\�બ�A
	StaticString< _MAX_NAMERECORD_SIZE_ >		HouseName;			//�ЫΦW��

	union
	{
		char		ClientData[MAX_HOUSE_CLIENT_DATA_SIZE_];
		struct
		{
			char Friend_Enter[MAX_HOUSE_STRING_SIZE]; //�n�Ͷi�J�p�ΰݭԻy
			char Friend_Leave[MAX_HOUSE_STRING_SIZE]; //�n�����}�p�ΰݭԻy
			char Friend_Use  [MAX_HOUSE_STRING_SIZE]; //�n�ͨϥήa��ݭԻy
		};
	};

	int			ItemLogPos;
	int			UnCheckItemLogCount;
	HouseFriendItemLogStruct ItemLog[ MAX_HOUSE_ITEM_LOG_COUNT ];

	//////////////////////////////////////////////////////////////////////////
	//�k�����
	//////////////////////////////////////////////////////////////////////////
	unsigned	LastServantProcTime;
	HouseServantStruct Servant[ MAX_SERVANT_COUNT ];



	void Init()
	{
		memset( this , 0 , sizeof(*this) );
		HouseDBID = -1;		
	}

	void	AddItemLog( HouseFriendItemLogStruct& AddItemLog )
	{
		if( unsigned(ItemLogPos) >= MAX_HOUSE_ITEM_LOG_COUNT )
			ItemLogPos = 0;

		ItemLog[ ItemLogPos ] = AddItemLog;
		ItemLogPos++;
		UnCheckItemLogCount++;
	}
	void ClearItemLog()
	{
		memset( ItemLog , 0 , sizeof(ItemLog) );
		ItemLogPos = 0;
		UnCheckItemLogCount = 0;
	}
};

//-------------------------------------------------------------------------
/*
struct HousePosStruct
{
	union
	{
		unsigned int Value;
		struct  
		{
			char Lv[4];		//-1��ܨS��
		};
	};

	int RelativePos( )
	{
		for( int i = 1 ; i < 4 ; i++ )
		{
			if( Lv[i] == -1 )
				return Lv[i-1];				
		}
		return Lv[0];
	}

	int	Level()
	{
		for( int i = 1 ; i < 4 ; i++ )
		{
			if( Lv[i] == -1 )
				return i;
		}
		return 3;
	}
};
*/

//���~����Ʈw��T
struct HouseItemDBStruct
{
	int					HouseDBID;
	int					ItemDBID;
	int					ParentItemDBID;

	int					Pos;
	ItemFieldStruct		Item;
	House3DLayoutStruct	Layout;
	void Init()
	{
		memset( this , 0 , sizeof(*this) );
		HouseDBID = -1;
		ItemDBID = -1;
		ParentItemDBID = -1;
	}
};
//-------------------------------------------------------------------------
//�ӫ����~��T
struct DepartmentStoreBaseInfoStruct
{
	int					GUID;
	int					NeedMemberID;
	int					SellType[3];
	int					SortNumber;
	ItemFieldStruct		Item;
	wchar_t				ItemName[32];
	wchar_t				Note[256];
	struct  
	{
		float				BeginTime;
		float				EndTime;
		int					Count;
		int					OrgCount;		//��l�w�c��q
		int					MaxCount;
		int					Cost;			//����
		int					Cost_Bonus;		//�ݭn���Q��
		int					Cost_Free;		//�����B��
		int					Get_Bonus;		//�ݭn���Q��
		int					Icon;
	}Sell;

	struct
	{
		short	Count;
		short	Rate[8];
	}Gamble;

	DepartmentStoreBaseInfoStruct()
	{
		memset( this , 0 , sizeof(*this) );
		GUID = -1;
	}
};

struct DB_DepartmentStoreBaseInfoStruct
{
	int ItemIDList[8];
	int ItemCountList[8];
	DepartmentStoreBaseInfoStruct Item;
};


/*
struct DepartmentStoreBaseInfoStruct
{
	int					GUID;
	int					NeedMemberID;
	int					SellType[3];
	int					SortNumber;
	struct
	{
		int		DisplayObjID;
		char	Name[32]
		int		OrgObjID[5];
		int		Count[5];		
	}Item;

	struct  
	{
		float				BeginTime;
		float				EndTime;
		int					Count;
		int					OrgCount;		//��l�w�c��q
		int					MaxCount;
		int					Cost;			//����
		int					Cost_Bonus;		//�ݭn���Q��
		int					Get_Bonus;		//�ݭn���Q��
		int					Icon;
	}Sell;

	DepartmentStoreBaseInfoStruct()
	{
		memset( this , 0 , sizeof(*this) );
		GUID = -1;
	}
	};
*/
//////////////////////////////////////////////////////////////////////////
enum   PKTypeENUM
{
	EM_PK_Normal            ,	//�DPK��
	EM_PK_All	            ,	//�j�ð�
	EM_PK_Party	            ,	//�PParty���ब��
	EM_PK_Party_Guild		,	//�PParty �P���| ���ब��
};
//////////////////////////////////////////////////////////////////////////
struct UntrustFlagStruct
{
	union
	{
		int _Flag;
		struct
		{
			bool DisableMail					: 1;	//�L�k�ϥΫH�c
			bool DisableDepartmentStoreMailGift : 1;	//�L�k�ӫ��e§
			bool DisableOpenAC					: 1;	//�L�k�ϥΩ���
			bool DisablePlayerTrade				: 1;	//�L�k�P���a���
			bool DisablePlayerChannelTalk		: 1;	//�L�k�ϥαK�y
			bool DisableSysChannelTalk			: 1;	//�L�k�ϥΥ@���W�D
			bool DisableZoneChannelTalk			: 1;	//�L�k�ϥΰϰ��W�D
		};
	};
};
//////////////////////////////////////////////////////////////////////////
//�b���򥻸��
struct PlayerAccountBaseInfoStruct
{
	int	 AccountMoney;
	int	 BonusMoney;
	int  ManageLv;
	char Password[33];
	int	 PlayTimeQuota;
	int	 LockAccountTime;
	int  LockAccountMoney[ Def_AccountMoneyLockTime_Max_Count_ ];	
	int  LockAccountMoney_Forever;
	StaticFlag< _ACCOUNT_FLAG_COUNT_ >	AccountFlag;		//�b����ƺX��

	int		 VipMemberType;
	float	VipMemberTerm;
	int		VipMemberFlag;	

	UntrustFlagStruct		UntrustFlag;

	int		CoolClothList[ _DEF_MAX_COOL_CLOTH_COUNT_ ];

	int		CheckFailedTimes;
	int		LastCheckTime;

	PlayerAccountBaseInfoStruct()
	{
		memset( this , 0 , sizeof(*this) );
	};
};
//////////////////////////////////////////////////////////////////////////
//���i��T����
struct ImportBoardBaseStruct
{
	float	UpdateTime;
	int		SortNumber;
	char	Title[ 256 ];
	char	Content[2048];

	bool	IsHot;
	bool	IsRed;
	float	BeginTime;
	float	EndTime;
	int		Item[5];
	int		ItemCount[5];
	int		Money;
	int		Money_Account;
	ImportBoardBaseStruct()
	{
		memset( this , 0 , sizeof(*this) );
	}
};
//////////////////////////////////////////////////////////////////////////
//Client �ݨt�θ�T
struct ClientComputerInfoStruct
{
	int CPU;
	int RAM_Total;
	int RAM_Free;
	int RAM_Game;
	int Ping;
	int FPS;
	int ZoneID;
	int IPNum;
};
//////////////////////////////////////////////////////////////////////////
//client �n�D�ʥ]²�d����
enum ClientPacketCheckTypeENUM
{
	EM_ClientPacketCheckType_HateList	,	
	EM_ClientPacketCheckType_Move		,	
	EM_ClientPacketCheckType_Talk		,
	EM_ClientPacketCheckType_Mail		,
	EM_ClientPacketCheckType_ACSerch	,

	EM_ClientPacketCheckType_Max		=30	,
};

//////////////////////////////////////////////////////////////////////////
//���� Log ����
enum TalkLogTypeENUM
{
	EM_TalkLogType_Talk			,//�K�y
	EM_TalkLogType_Party		,//�����W�D
	EM_TalkLogType_Range		,//�d��
	EM_TalkLogType_ZoneChannel	,//���W�D
	EM_TalkLogType_SystemChannel,//�t���W�D
	EM_TalkLogType_Guild		,//���|�W�D
	EM_TalkLogType_PlayerChannel,//���a�W�D
};
//////////////////////////////////////////////////////////////////////////
struct MineCheckStruct
{
	float X , Y , Z;
	int	  Count;
};
//////////////////////////////////////////////////////////////////////////
struct AccountBagItemFieldDBStruct
{
	int				ItemDBID;
	ItemFieldStruct Item;

	void Init()
	{
		ItemDBID = -1;
		Item.Init();
	}
};

struct WebShopBagItemFieldDBStruct
{
	int				ItemDBID;
	ItemFieldStruct Item;
	char			Message[256];
	void Init()
	{
		ItemDBID = -1;
		Item.Init();
	}

};

//////////////////////////////////////////////////////////////////////////
struct ChangeWorldStruct
{
	int						WorldID;				//�n�J�t�~�@�ɪ�ID	
	int						WorldNetID;			
	RolePosStruct			RetPos;
	int						RetZoneID;
};
//////////////////////////////////////////////////////////////////////////
enum ItemTimeoutPosENUM
{
	EM_ItemTimeoutPos_Body	,
	EM_ItemTimeoutPos_Bank	,
	EM_ItemTimeoutPos_EQ	,
};
//////////////////////////////////////////////////////////////////////////
//�O�����ǰe�I
struct LocationSaveStruct
{
	int		IconType;		//0 ��ܨS���
	char	Note[64];	    //����
	int		ZoneID;
	float	X , Y , Z;

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	}
};
//////////////////////////////////////////////////////////////////////////
/*
//�b�����פJ�ɶ�
struct AccountMoneyLockTimeStruct
{
	int		Time;
	int		AccountMoney;
};
*/
//////////////////////////////////////////////////////////////////////////
//�ӸO��T
struct TombStruct
{
	int	ItemGUID;		//�p�G�ͦs�_�٨S�����A�i�O�䤣�쪫��A�N���s���͹ӸO
	int	CreateTime;
	int ZoneID;
	float X , Y , Z;
	int	DebtExp;
	int	DebtTp;
	int Exp;

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	};
};
//////////////////////////////////////////////////////////////////////////
enum LuaPlotClockTypeENUM
{
	EM_LuaPlotClockType_Close	,
	EM_LuaPlotClockType_Open	,
	EM_LuaPlotClockType_Stop	,

};
//�@���έp�ɾ�
struct LuaPlotClockStruct
{
	LuaPlotClockTypeENUM	Type;
	int		CheckValue;		
	int		BeginTime;
	int		EndTime;
	int		NowTime;
	StaticString< _MAX_LUA_FUNTIONNAMESIZE_> ChangeZonePlot;
	StaticString< _MAX_LUA_FUNTIONNAMESIZE_> TimeUpPlot;

};
//////////////////////////////////////////////////////////////////////////
//Client ���A��T
struct ClientStateStruct
{
	union
	{
		int _Mode;
		struct
		{
			bool	InWater	:1;	//�b����
		};
	};
};
//////////////////////////////////////////////////////////////////////////
#define		MAX_CultivatePet_SkillCount		10
#define		MAX_CultivatePet_Count			6
#define		MAX_CultivatePet_Product_Count_	3
//#define MAX_CultivatePet_EQ_Count	7
enum CultivatePetEQTypeENUM
{
	EM_CultivatePetEQType_Tools		,
	EM_CultivatePetEQType_Source	,
	EM_CultivatePetEQType_Product1	,
	EM_CultivatePetEQType_Product2	,
	EM_CultivatePetEQType_Product3	,
	EM_CultivatePetEQType_Other0 	,
	EM_CultivatePetEQType_Other1	,
	EM_CultivatePetEQType_Other2	,
	EM_CultivatePetEQType_Other3	,
	EM_CultivatePetEQType_MAX		,
};


struct CultivatePetMode
{
	union
	{
		int _Mode;
		struct  
		{
			bool IsSummon	:1;
			bool IsTravail	:1;

			//�ͬ���
			bool BlackSmith :1;
			bool Carpenter  :1;
			bool MakeArmor	:1;
			bool Tailor		:1;
			bool Cook		:1;
			bool Alchemy	:1;
			bool Mining		:1;
			bool Lumbering	:1;
			bool Herblism	:1;
			bool Fishing	:1;
		};
	};
};

enum CultivatePetCommandTypeENUM
{
	EM_CultivatePetCommandType_None			,	//�S���A(����ͬ��ޯ�)
	EM_CultivatePetCommandType_OnTimeEvent	,	//client �ݨC10��q��Server �ݨ����d��(�B�z����or�S�O�ƥ�)
	EM_CultivatePetCommandType_Summon		,	//�l���d��
	EM_CultivatePetCommandType_Feed			,	//����
	EM_CultivatePetCommandType_Travel		,	//�Ȧ�
	EM_CultivatePetCommandType_Free			,	//���
	EM_CultivatePetCommandType_Train		,	//�S�V
	EM_CultivatePetCommandType_Return		,	//�l��X���d���^��
	//////////////////////////////////////////////////////////////////////////
	EM_CultivatePetCommandType_LiftSkill		,
	/*
	EM_CultivatePetCommandType_LiftSkill_BlackSmith	=100,	// ���K
	EM_CultivatePetCommandType_LiftSkill_Carpenter	,	// ��u
	EM_CultivatePetCommandType_LiftSkill_MakeArmor	,	// �s��
	EM_CultivatePetCommandType_LiftSkill_Tailor		,	// ���_
	EM_CultivatePetCommandType_LiftSkill_Cook		,	// �i��
	EM_CultivatePetCommandType_LiftSkill_Alchemy	,	// �Ҫ�
	EM_CultivatePetCommandType_LiftSkill_Mining		,	// ���q
	EM_CultivatePetCommandType_LiftSkill_Lumbering	,	// ���
	EM_CultivatePetCommandType_LiftSkill_Herblism	,	// ����
	EM_CultivatePetCommandType_LiftSkill_Fishing	,	// ����
	EM_CultivatePetCommandType_LiftSkill_Plant		,	// �ش�
*/
};

enum CultivatePetStructValueTypeENUM
{
	EM_CultivatePetStructValueType_ItemOrgID	,
	EM_CultivatePetStructValueType_CreateTime	,
	EM_CultivatePetStructValueType_OrgObjID		,	//( + Pos*100 )
	EM_CultivatePetStructValueType_Lv			,
	EM_CultivatePetStructValueType_PetType		,
	EM_CultivatePetStructValueType_EventColdown	,		//�ƥ�N�o
	EM_CultivatePetStructValueType_EventType	,		//�ƥ�����
	EM_CultivatePetStructValueType_LifeSkillTablePos,
	EM_CultivatePetStructValueType_Exp			,
	EM_CultivatePetStructValueType_SKillPoint	,
	EM_CultivatePetStructValueType_TotalSkillPoint,	
	EM_CultivatePetStructValueType_Loyal		,
	EM_CultivatePetStructValueType_Hunger		,
	EM_CultivatePetStructValueType_Talent		,
	EM_CultivatePetStructValueType_Spirit		,
	EM_CultivatePetStructValueType_Mode			,
	EM_CultivatePetStructValueType_Str			,
	EM_CultivatePetStructValueType_Sta			,
	EM_CultivatePetStructValueType_Agi			,
	EM_CultivatePetStructValueType_Int			,
	EM_CultivatePetStructValueType_Mnd			,
	EM_CultivatePetStructValueType_Property		,
	EM_CultivatePetStructValueType_TrainCount	,
	EM_CultivatePetStructValueType_MagicID0		,		
	EM_CultivatePetStructValueType_MagicID1		,
	EM_CultivatePetStructValueType_MagicID2		,
	EM_CultivatePetStructValueType_MagicID3		,
	EM_CultivatePetStructValueType_MagicID4		,
	EM_CultivatePetStructValueType_MagicID5		,
	EM_CultivatePetStructValueType_MagicID6		,
	EM_CultivatePetStructValueType_MagicID7		,
	EM_CultivatePetStructValueType_MagicID8		,
	EM_CultivatePetStructValueType_MagicID9		,
	EM_CultivatePetStructValueType_MagicLv0		,		
	EM_CultivatePetStructValueType_MagicLv1		,
	EM_CultivatePetStructValueType_MagicLv2		,
	EM_CultivatePetStructValueType_MagicLv3		,
	EM_CultivatePetStructValueType_MagicLv4		,
	EM_CultivatePetStructValueType_MagicLv5		,
	EM_CultivatePetStructValueType_MagicLv6		,
	EM_CultivatePetStructValueType_MagicLv7		,
	EM_CultivatePetStructValueType_MagicLv8		,
	EM_CultivatePetStructValueType_MagicLv9		,
	EM_CultivatePetStructValueType_MagicCount	,
	EM_CultivatePetStructValueType_LifeSkill1	,
	EM_CultivatePetStructValueType_LifeSkill2	,
	EM_CultivatePetStructValueType_LifeSkill3	,
	EM_CultivatePetStructValueType_LifeSkill4	,
	EM_CultivatePetStructValueType_MergeCount	,
	EM_CultivatePetStructValueType_Max			,
};

struct MagicBaseStruct
{
	int ID;
	int Lv;
};

#define _MAX_PET_SKILLPOINT_	10000
#define _MAX_PET_UNDERGOPOINT_	10000
#define _MAX_PET_HUNGER_		100
#define _MAX_PET_LOYAL_			100
#define _MAX_PET_TALENT_		100

//�i���d��
struct CultivatePetStruct
{
	StaticString< _MAX_NAMERECORD_SIZE_ >   Name;
	union
	{
		int			_Value[ EM_CultivatePetStructValueType_Max ];
		float		_FloatValue[ EM_CultivatePetStructValueType_Max ];
		struct  
		{
			int		ItemOrgID;				//�d���J���~
			int		CreateTime;				//���ͮɶ�
			int		PetOrgID;
			int		Lv;
			int		PetType;

			int								EventColdown;			//�ƥ�N�o
			CultivatePetCommandTypeENUM		EventType;				//�ƥ�����
			int		LifeSkillTablePos;
			int		Exp;
			int		SkillPoint;
			int		TotalSkillPoint;
			int		Loyal;		//�˱K��
			int		Hunger;		//������
			float	Talent;		//�Ѹ�
			int		Spirit;		//���O(�אּ���m)
			CultivatePetMode	Mode;
			float				STR,STA,AGI,INT,MND;
			MagicResistENUM		Property;
			int		TrainCount;

			StaticVector< MagicBaseStruct , MAX_CultivatePet_SkillCount > Magic;

			float	LifeSkill[ EM_CultivatePetLifeSkillType_Max ];		

			int		DayMergeCount;		//���ѿĦX����
		};
	};

	union
	{
		ItemFieldStruct		EQ[ EM_CultivatePetEQType_MAX ];
		struct  
		{
			ItemFieldStruct	Tools;			//�d���u��
			ItemFieldStruct Source;			//���󪫫~
			ItemFieldStruct Product[MAX_CultivatePet_Product_Count_];
			ItemFieldStruct Other[4];		//�d���\�]�~		
		};
	};
/*
	bool CheckPetFlag( int ID )
	{
		if( unsigned( ID ) >= _DEF_MAX_PET_TYPE_ )
			return false;

		int Pos1 = ID % 8;
		int Pos2 = ID / 8;

		return ( PetFlagType[ Pos2 ] && ( 1<< Pos1 ) != 0 );		
	};
	void SetPetFlag( int ID , bool Value )
	{
		if( unsigned( ID ) >= _DEF_MAX_PET_TYPE_ )
			return;

		int Pos1 = ID % 8;
		int Pos2 = ID / 8;

		PetFlagType[ Pos2 ] |= ( 1<< Pos1 );
	};
*/
	void init( )
	{
		memset( this , 0 , sizeof(CultivatePetStruct) );
	
		for( int i = 0 ; i < EM_CultivatePetLifeSkillType_Max ;i ++ )
			LifeSkill[i] = 1;
	};
	bool IsEmpty()
	{
		if( PetOrgID == 0 )
			return true;
		return false;
	}

	bool CheckEqEmpty()
	{
		for( int i = 0 ; i < EM_CultivatePetEQType_MAX ; i++ )
		{
			if( EQ[i].IsEmpty() == false )
				return false;
		}
		return true;
	};
/*
	void TranAccept( )
	{
		STR += LastTran.STR; LastTran.STR = 0;
		STA += LastTran.STA; LastTran.STA = 0;
		INT += LastTran.INT; LastTran.INT = 0;
		MND += LastTran.MND; LastTran.MND = 0;
		AGI += LastTran.AGI; LastTran.AGI = 0;
		TrainCheckCount = 0;
	}
	*/

	float AssistPower( int Type );
};

struct DB_CultivatePetStruct
{
	int	PlayerDBID;
	int	Pos;
	CultivatePetStruct Info;
};
//////////////////////////////////////////////////////////////////////////
struct RolePetStruct
{
	CultivatePetStruct	Base[ MAX_CultivatePet_Count ];
	int			Money;				//�d����
	int			NextMergeResetTime;	//�U�@���ĦX��s
};
//////////////////////////////////////////////////////////////////////////
//���|�ξԪ��A
enum GuildHouseWarStateENUM
{
	EM_GuildHouseWarState_None			,	//����
	EM_GuildHouseWarState_Appointment	,	//�w��
	EM_GuildHouseWarState_Prepare		,	//�ǳ�
	EM_GuildHouseWarState_Failed		,	//�S���t�춤
	EM_GuildHouseWarState_Fight			,	//�Ԫ���
	EM_GuildHouseWarState_FightEnd		,	//�Ԫ�����
	EM_GuildHouseWarState_FightEnd_Even	,	//�Ԫ�����
	EM_GuildHouseWarState_FightEnd_Win	,	//�Ԫ��ӧQ
	EM_GuildHouseWarState_FightEnd_Lost	,	//�Ԫ�����
};

struct GuildHouseWarInfoStruct
{
	int		ZoneGroupID;
	int		GuildID;			//�w���Ԫ����|
	int		Score;				//�n��
	int		EnemyGuildID;		//��Ԥ��|(-1��ܨS��)
	int		GuildLv;
	bool	IsAcceptAssignment;	//�P�N����


	GuildHouseWarStateENUM State;
	StaticString< _MAX_NAMERECORD_SIZE_ >   GuildName;

	GuildHouseWarInfoStruct( )
	{
		memset( this , 0 , sizeof(*this) );
		//ZoneGroupID = RoleDataEx::G_ZoneID / 1000;
	}
	
	bool operator <  ( const GuildHouseWarInfoStruct& P ) const
	{	
		/*
		int S = Score;
		int PS = P.Score;
		if( EnemyGuildID )
			S = -1000;
		if( P.EnemyGuildID )
			PS = -1000;

		return PS < S;	
		*/
		if( GuildLv == P.GuildLv)
			return P.Score < Score;
		return P.GuildLv < GuildLv;
	}

};

enum GuildHouseWarResultENUM
{
	EM_GuildHouseWarResultENUM_Win		,	
	EM_GuildHouseWarResultENUM_Lost		,	
	EM_GuildHouseWarResultENUM_Even		,	
};
//////////////////////////////////////////////////////////////////////////
//���|�� ���|�򥻸�T
struct GuildHouseWarFightBaseStruct
{
	int GuildID;
	int Score;
	int	Energy;
//	map< int , int > ValueMap;
	GuildHouseWarFightBaseStruct()
	{
		Score = 5000;
		GuildID = 0;
		Energy = 0;
	}
};

//���|�Ը�T
struct GuildHouseWarFightStruct
{
//	float BeginTime;
//	float EndTime;

	GuildHouseWarFightBaseStruct	Base[2];

	bool IsReady;
	bool IsEndWar;
	bool IsAssignment;		//���w���

	GuildHouseWarFightStruct()
	{
		//memset( this , 0 , sizeof(GuildHouseWarFightStruct) );
//		BeginTime = 0;
//		EndTime = 0;
		IsEndWar = false;
//		Base[0].Score = 5000;
//		Base[1].Score = 5000;
	}
	/*
	bool AddWarValue(int GuildID , int Type , int Value )
	{
		map< int , int >* ValueMap ;
		if( GuildID == Base[0].GuildID )
			ValueMap = &Base[0].ValueMap;
		else if( GuildID == Base[1].GuildID )
			ValueMap = &Base[1].ValueMap;
		else return false;

		(*ValueMap)[Type] += Value;
		return true;
	}
	int GetWarValue(int GuildID , int Type )
	{
		map< int , int >* ValueMap ;
		if( GuildID == Base[0].GuildID )
			ValueMap = &Base[0].ValueMap;
		else if( GuildID == Base[1].GuildID )
			ValueMap = &Base[1].ValueMap;
		else return 0;

		return (*ValueMap)[Type];		
	}
	*/
	int	GetScore( int GuildID )
	{
		if( Base[0].GuildID == GuildID )
			return Base[0].Score;
		else if( Base[1].GuildID == GuildID )
			return Base[1].Score;
		return 0;
	}

	bool AddScore( int GuildID , int Value )
	{
		if( Base[0].Score == 0 || Base[1].Score == 0 )
			return false;

		if( Base[0].GuildID == GuildID )
		{
			Base[0].Score += Value;
			Base[1].Score -= Value;

			if(		Base[0].Score < 0 
				||	Base[1].Score > 10000 )
			{
				Base[0].Score = 0;
				Base[1].Score = 10000;
			}
			if(		Base[0].Score > 10000 
				||	Base[1].Score < 0 )
			{
				Base[0].Score = 10000;
				Base[1].Score = 0;
			}
			return true;
		}

		if( Base[1].GuildID == GuildID )
		{
			Base[1].Score += Value;
			Base[0].Score -= Value;

			if(		Base[1].Score < 0 
				||	Base[0].Score > 10000 )
			{
				Base[1].Score = 0;
				Base[0].Score = 10000;
			}
			if(		Base[1].Score > 10000 
				||	Base[0].Score < 0 )
			{
				Base[1].Score = 10000;
				Base[0].Score = 0;
			}
			return true;
		}

		return false;
	}

	bool AddEnergy( int GuildID , int Value )
	{
		GuildHouseWarFightBaseStruct*	BaseInfo = NULL;
		if( Base[0].GuildID == GuildID )
			BaseInfo = &Base[0];
		else if( Base[1].GuildID == GuildID )
			BaseInfo = &Base[1];
		else 
			return false;

		BaseInfo->Energy += Value;
		if( Value < 0 ) 
			Value = 0 ;

		return true;
	}
	int	 GetEnergy( int GuildID )
	{
		GuildHouseWarFightBaseStruct*	BaseInfo = NULL;
		if( Base[0].GuildID == GuildID )
			BaseInfo = &Base[0];
		else if( Base[1].GuildID == GuildID )
			BaseInfo = &Base[1];
		else 
			return 0;

		return BaseInfo->Energy;
	}
};
//////////////////////////////////////////////////////////////////////////
enum	GuildWarPlayerValueENUM
{
	EM_GuildWarPlayerValue_KillPoint	,		//���}��
	EM_GuildWarPlayerValue_HitPoint		,		//�ˮ`�q
	EM_GuildWarPlayerValue_DefPoint		,		//���m�q
	EM_GuildWarPlayerValue_HealPoint	,		//�v���q
	EM_GuildWarPlayerValue_WarScore		,		//���Z���o
	EM_GuildWarPlayerValue_EnergyPoint	,		//�෽���o
	EM_GuildWarPlayerValue_OccupyPoint	,		//������I
	EM_GuildWarPlayerValue_TotalScore	,		//�`��

	EM_GuildWarPlayerValue_Max			,
};


//���|�ξԪ��a���ԨƸ��
struct GuildWarPlayerInfoStruct
{
	int		PlayerDBID;
	int		GuildID;
	StaticString< _MAX_NAMERECORD_SIZE_ >   RoleName;

	union
	{
		int _Score[ EM_GuildWarPlayerValue_Max ];
		struct
		{
			int	KillPoint;			//���}��
			int	HitPoint;			//�ˮ`�q
			int	DefPoint;			//���m�q
			int HealPoint;			//�v���q
			int WarScore;			//���Z���o
			int EnergyPoint;		//�෽���o
			int OccupyPoint;		//������I
			int TotalScore;			//�`��
		};
	};

//	Voc_ENUM		    Voc;								//¾�~
//	Voc_ENUM		    Voc_Sub;							//��¾�~
//	int					Level;
//	int					Level_Sub;	

	GuildWarPlayerInfoStruct()
	{
		memset( this , 0 , sizeof(*this));
	}

	bool IsEmpty()
	{
		if( PlayerDBID==0 )
			return true;
		return false;
	}
};
//////////////////////////////////////////////////////////////////////////
#define _MAX_MONSTERHUNT_COUNT_	200
struct MonsterHunterStruct
{
	unsigned short	KillCount[ _MAX_MONSTERHUNT_COUNT_ ];
	unsigned short	DeadCount[ _MAX_MONSTERHUNT_COUNT_ ];
	int		TotalKillCount_Player;
	int		TotalKillCount_NPC;
	int		TotalDeadCount_Player;
	int		TotalDeadCount_NPC;
};
//////////////////////////////////////////////////////////////////////////
struct OfflineMessageDBStruct
{
	float	Time;
	int		Type;
	int		ToPlayerDBID;
	int		FromPlayerDBID;
	int		ManageLv;
	StaticString <32> FromName;
	StaticString <32> ToName;
	StaticString <512>  Content;
};
//////////////////////////////////////////////////////////////////////////
struct CheckKeyAddressStruct
{
	char		Key[64];
	int			Address;
};
//////////////////////////////////////////////////////////////////////////
struct SysKeyValueStruct
{
	vector<int>		GlobalItemDrop;
	vector<int>		GlobalItemDrop_BigMonster;
	vector<int>		GlobalItemDrop_King;
	vector<int>		GlobalItemDrop_WorldKing;
	vector<int>		GlobalItemDrop_DepartmentStore;
	int				Money_GoldObjID;
	int				Money_AccountObjID;	
	int				Money_BonusObjID;
	int				TreasureBaseObjID;
	int				PK_Revive_ZoneID;
	float			PK_Revive_X;
	float			PK_Revive_Y;
	float			PK_Revive_Z;
	int				PK_ProtectEq_ItemID;

	int				MagicStoneCount;			//�]�ۺ���
	int				MagicStoneStart;			//�]�۶}�l��m
	int				Teleport_PointObjID;
	int				MagicBoxOpenKeyItemID;

	int				GoodEvilBuf[9];

	int				GamebleItemState_LockItemID;	//�ݩʽ����w���~

	struct  
	{
		int	ItemWeapon[10][20];
		int	ItemArmor[10][20];
		int	DLvClothes;
		int	DLvPants;
		int	DLvWeapon_OneHand;
		int	DLvWeapon_TwoHand;
		int	DLvOther;
	}Dissolution;

	int			SysQuestColor_NPC;
	int			SysQuestColor_ITEM;
	int			SysQuestColor_ZONE;

	int			TombObjID;
	int			HouseBuff;
	int			Pet_PopItemID;
	int			Pet_ReTrainItemID;
//	int			KeyItem_EQBackup;

	union
	{
		int		ElementPowerMagicID[EM_MagicResist_MAXCOUNT];
		struct  
		{
			int			EarthPowerMagicID;
			int			WaterPowerMagicID;
			int			FirePowerMagicID;
			int			WindPowerMagicID;
			int			LightPowerMagicID;
			int			DarkPowerMagicID;
		};
	};

	struct
	{
		int FruitsExp;
		int FeedPointDec;
//		int MagicWater;
//		int Topdress;
//		int Water;
	}Plant;

	vector<int>		MagicStoneShopAbilityList;
	PriceTypeENUM	MagicStoneShopCostType[2];


	float	TitleSys_FamouseDesc_Min;

	
	SysKeyValueStruct()
	{
		Init();
	};
	void	Init()
	{
		GlobalItemDrop.clear();
		GlobalItemDrop_BigMonster.clear();
		GlobalItemDrop_King.clear();
		GlobalItemDrop_WorldKing.clear();
		GlobalItemDrop_DepartmentStore.clear();
		Money_GoldObjID = 0;
		Money_AccountObjID = 0;
		Money_BonusObjID = 0;
		TreasureBaseObjID = 0;		
	};
};
//////////////////////////////////////////////////////////////////////////
enum	GuildHouseItemInfoStateENUM
{
	EM_GuildHouseItemInfoState_None		,
	EM_GuildHouseItemInfoState_Insert	,
	EM_GuildHouseItemInfoState_Update	,
};
//----------------------------------------------------------------------------------------------
enum	GuildBuildingTypeENUM
{
	EM_GuildBuildingType_None		,
	EM_GuildBuildingType_Building	,
	EM_GuildBuildingType_Furniture	,
};
//----------------------------------------------------------------------------------------------
//���|�Ϊ��~
struct GuildHouseItemStruct
{
	int		GuildID;
	int		ItemDBID;
	int		PageID;
	int		PosID;

	GuildHouseItemInfoStateENUM	State;
	ItemFieldStruct	Item;
};
//----------------------------------------------------------------------------------------------
//���~����Ʈw��T
struct GuildHouseFurnitureItemStruct
{
	int					GuildID;
	int					OwnerDBID;
	int					ItemDBID;
	int					Pos;
	ItemFieldStruct		Item;
	House3DLayoutStruct	Layout;
	GuildHouseItemInfoStateENUM	State;
	void Init()
	{
		memset( this , 0 , sizeof(*this) );
		GuildID = -1;
		ItemDBID = -1;
	}
};
//----------------------------------------------------------------------------------------------
enum	GuildHouseBuildingInfoStateENUM
{
	EM_GuildHouseBuildingInfoState_None		,
	EM_GuildHouseBuildingInfoState_Insert	,
	EM_GuildHouseBuildingInfoState_Update	,
};
//���|�ؿv���
struct GuildHouseBuildingInfoStruct
{
	int		GuildID;
	int		BuildingDBID;
	int		ParentDBID;
	int		BuildingID;
	char	PointStr[32];
	float	Dir;
	union
	{
		int		Value[4];
		struct  
		{
			union
			{
				int _Mode;
				struct  
				{
					bool	IsActive : 1;
					bool	Revive1  : 1;
					bool	Revive2  : 1;
					bool	Revive3  : 1;
					bool	Revive4  : 1;
					bool	Revive5  : 1;
					bool	Revive6  : 1;
					bool	Revive7  : 1;
					bool	Revive8  : 1;
				};
			};
			int Value1;
			int Value2;
			int Value3;
		};
	};

	GuildHouseBuildingInfoStateENUM State;

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	};
};
//----------------------------------------------------------------------------------------------
//���|�θ�T
struct GuildHousesInfoStruct
{
	int		GuildID;
	int		ItemMaxPageCount;
	int		FurnitureMaxCount;
	int		LastCalRentTime;		//�̫�@���p������O���ɶ�
	int		GuildStyle;				//�u�|�˦�
	int		GuildStyleRight;		//�i�H�ϥΪ��u�|�˦�
//	int		Money;					//���|����
//	int		PageRight_Get[ _DEF_GUIDHOUSEITEM_MAX_PAGE_ ];	
//	int		PageRight_Push[ _DEF_GUIDHOUSEITEM_MAX_PAGE_ ];	
};
//----------------------------------------------------------------------------------------------
//�ܮw�s���v���]�w
struct GuildStorehouseRightStruct
{
	int	GuildID;
	int	PageID;
	struct 
	{
		union
		{
			int	_Right;			//�v��
			struct  
			{
				bool	View : 1;
				bool	Put	 : 1;
				bool	Get	 : 1;
			};
		};
		int GetCount;		//�������
	}Rank[EM_GuildRank_Count];

	GuildStorehouseRightStruct()
	{
		memset( this , 0 , sizeof(*this) );
		for( int i =0 ; i < EM_GuildRank_Count ; i++ )
		{
			Rank[i].View = true;
		}
	}
};
//-------------------------------------------------------------------------
enum GuildHouseLootTypeENUM
{
	EM_GuildHouseLootType_Put	,		
	EM_GuildHouseLootType_Get	,		
	EM_GuildHouseLootType_Move	,
};

//���|�ܮw�s��Log
struct GuildItemStoreLogStruct
{
	int GuildID;
	int PageID;
	int	Time;
	GuildHouseLootTypeENUM Type;
	int	PlayerDBID;
	int	ItemOrgID;
	int	ItemCount;
	int	FromPageID;
	int ToPageID;
};


//////////////////////////////////////////////////////////////////////////
//�����I����
struct MoneyExchangeKeyValueStruct
{
	char	KeyStr[32];
	int		Value[4];

	MoneyExchangeKeyValueStruct()
	{
		memset( this , 0 , sizeof(*this) );
	};
};
//////////////////////////////////////////////////////////////////////////
//��B�Ӧr��ק��
struct SysKeyStrChangeStruct
{
	StaticString< 32 > KeyStr; 
	StaticString< 256 > Content; 

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	};
};
//////////////////////////////////////////////////////////////////////////
//�p�ɺX�l �N��\��C�|
enum	TimeFlagEffectENUM
{
	//0-99		�u��ɶ�

	EM_TimeFlagEffect_BagPage3			= 0 ,	//--�I�]3
	EM_TimeFlagEffect_BagPage4				,	//--�I�]4
	EM_TimeFlagEffect_BagPage5				,	//--�I�]3
	EM_TimeFlagEffect_BagPage6				,	//--�I�]4

	EM_TimeFlagEffect_BankBag2			= 10,	//�Ȧ�I�] �}��
	EM_TimeFlagEffect_BankBag3				,	//�Ȧ�I�] �}��
	EM_TimeFlagEffect_BankBag4				,	//�Ȧ�I�] �}��
	EM_TimeFlagEffect_BankBag5				,	//�Ȧ�I�] �}��

	EM_TimeFlagEffect_HonorParty		= 20,	//�a�A�ն�
	EM_TimeFlagEffect_MailPaper				,	//�l��H��	
	EM_TimeFlagEffect_DailyFlag				,	//�C�魫�n���~�M������	
	EM_TimeFlagEffect_MailMultiItem			,	//�l��榸�ǰe�h�Ӫ��~
	EM_TimeFlagEffect_HandyBank				,	//�H���Ȧ�
	EM_TimeFlagEffect_HandyAuction			,	//�H��AC
	EM_TimeFlagEffect_HandyMail				,	//�H���H�c

	EM_TimeFlagEffect_PetPage3			= 30,	//�d���ĤT��
	EM_TimeFlagEffect_PetPage4				,	//�d���ĤT��
	EM_TimeFlagEffect_PetPage5				,	//�d���ĤT��
	EM_TimeFlagEffect_PetPage6				,	//�d���ĤT��

	//100-199	�C���ɶ�
};

//////////////////////////////////////////////////////////////////////////
//�e�ʥ]��Client ���Ҧ�
struct SendPacketModeStruct
{
	union
	{
		int Mode;
		struct  
		{
			bool ReducePlayerMove		: 1;	//���a���ʳ������� �C��~�|�e�@��
			bool IgnorePlayerMove		: 1;	//�Ҧ����ʩ���
			bool IgnoreAllMove			: 1;	//�����Ҧ�����( ���a�PNPC�����ʫʥ]�����e)
		};
	};
};
//////////////////////////////////////////////////////////////////////////
//�O�d������
struct ReserverRoleStruct
{
	bool		IsAutoCreate;
	StaticString< _MAX_NAMERECORD_SIZE_ > RoleName;
	int			Sex;
	int			Race;
	int			Job;
	LookStruct	Look;
//	int			GiftItemID;
};
//////////////////////////////////////////////////////////////////////////
struct BattleArraryStruct
{
	int		GItemID;
	float	Angle;
	float	Dist;
	bool	UsePathFind;
};
//////////////////////////////////////////////////////////////////////////
#define _MAX_INSTANCE_SETTING_COUNT_	100
struct InstanceSettingStruct
{
/*
	struct
	{
		int		 KeyID;
		unsigned LiveTime;	
	}Setting[ _MAX_INSTANCE_SETTING_COUNT_ ];
*/
	int		 KeyID		[ _MAX_INSTANCE_SETTING_COUNT_ ];
	unsigned LiveTime	[ _MAX_INSTANCE_SETTING_COUNT_ ];	
	unsigned ExtendTime	[ _MAX_INSTANCE_SETTING_COUNT_ ];	//�i���ɶ�
	

};
//////////////////////////////////////////////////////////////////////////
#define _MAX_EX_SKILL_COUNT_	10
//�@���]�w�i�ϥΧޯ�
struct ExSkillBaseStruct
{
	int		SpellerID;		//�I�k��ID
	int		SkillID;		//�k�NID
	int		SkillLv;		//�k�N����
	bool operator == ( const ExSkillBaseStruct& P ) const
	{
		return (	P.SpellerID == SpellerID
				&& P.SkillID == SkillID
				&& P.SkillLv == SkillLv	);
	}
};
//////////////////////////////////////////////////////////////////////////
//���ɵ��G
enum GameResultENUM
{
	EM_GameResult_Win	,
	EM_GameResult_Lost	,
	EM_GameResult_Even	,
};
//////////////////////////////////////////////////////////////////////////
//�Ʀ�] �Ʀ�����
enum BillbaordSortTypeENUM
{
	EM_BillboardSortType_Money					,//�֦�������    
	EM_BillboardSortType_Money_Account			,//�֦������p    
	EM_BillboardSortType_Money_Bonus			,//�֦������p    
	EM_BillboardSortType_STR					,//�O�q           
	EM_BillboardSortType_AGI					,//�ӱ�           
	EM_BillboardSortType_STA					,//�@�O           
	EM_BillboardSortType_INT					,//���z           
	EM_BillboardSortType_MND					,//�믫           
	EM_BillboardSortType_ATK					,//�����j��       
	EM_BillboardSortType_MATK					,//�k�N�j��       
	EM_BillboardSortType_DEF					,//���z���m       
	EM_BillboardSortType_MDEF					,//�k�N���m      
	EM_BillboardSortType_Honor					,//�a�A�I��      
	EM_BillboardSortType_TitleCount				,//���쪺�ٸ��ƶq      
	EM_BillboardSortType_QuestCompleteCount		,//�w�g���������ȼƶq  
};
//////////////////////////////////////////////////////////////////////////
//�̫�@���B�z���~�T��
enum RoleErrorMsgENUM
{
	EM_RoleErrorMsg_None	,

	EM_RoleErrorMsg_SpellExSkill_SkillNotFind		,//���|���ޯ�
	EM_RoleErrorMsg_SpellExSkill_SpellerNotExist	,//�I�k�̤��s�b
	EM_RoleErrorMsg_SpellExSkill_MagicColErr		,//�k�N��Ʀ����D
	EM_RoleErrorMsg_SpellExSkill_OnSpellErr			,//���b�I�k��
	EM_RoleErrorMsg_SpellExSkill_TargetLineNotClear	,//������
	EM_RoleErrorMsg_SpellExSkill_ExplodeTimeErr		,//�z���ɶ������D
};
//////////////////////////////////////////////////////////////////////////
struct MagicStoneExchange
{
	int MagicStoneID;
	int Lv;
	int Money[2];
};
//////////////////////////////////////////////////////////////////////////
#define _MAX_SUIT_SKILL_COUNT_		200
#define	_MAX_SUIT_SKILL_EQ_COUNT_	10
//�M�˧ޯ�
struct SuitSkllBaseStruct
{
	int			SkillID;
};

struct SuitSkillStruct
{	
	int		LeanSkillCount;
	SuitSkllBaseStruct LeanSkillList[_MAX_SUIT_SKILL_COUNT_];
	int		MaxEqSkillCount;
	int		EQ[_MAX_SUIT_SKILL_EQ_COUNT_];

};
//////////////////////////////////////////////////////////////////////////
struct VipMemberStruct
{
	int		Type;
	float	Term;
	union
	{
		int	_Flag;
		struct  
		{
			bool	Flag_Teleport_Save	: 1;		//�ǰe���� �K�O�O�I
			bool	Flag_Teleport		: 1;		//�ǰe���� �K�O�ǰe
			bool	Flag_2		  		: 1;
			bool	Flag_3		  		: 1;
			bool	Flag_4		  		: 1;
			bool	Flag_5		  		: 1;
			bool	Flag_6		  		: 1;
			bool	Flag_7		  		: 1;
		};
	};

	UntrustFlagStruct UntrustFlag;
};	

//////////////////////////////////////////////////////////////////////////
/*
enum BillboardSortTypeENUM
{
	EM_BillboardSortType_STR					,//�O�q           
	EM_BillboardSortType_AGI					,//�ӱ�           
	EM_BillboardSortType_STA					,//�@�O           
	EM_BillboardSortType_INT					,//���z           
	EM_BillboardSortType_MND					,//�믫           
	EM_BillboardSortType_ATK					,//�����j��       
	EM_BillboardSortType_MATK					,//�k�N�j��       
	EM_BillboardSortType_DEF					,//���z���m       
	EM_BillboardSortType_Phy_ParryRate			,//���ɵ���       
	EM_BillboardSortType_Phy_DodgeLv			,//�{������      
	EM_BillboardSortType_MDEF					,//�k�N���m      
	EM_BillboardSortType_Honor					,//�a�A�I��      
	EM_BillboardSortType_Gold					,//�֦�������    
	EM_BillboardSortType_Gold_Account			,//�֦������p    
	EM_BillboardSortType_Gold_Bonus				,//�֦������p    
	EM_BillboardSortType_TitleCount				,//���쪺�ٸ��ƶq      
	EM_BillboardSortType_QuestCompleteCount		,//�w�g���������ȼƶq  
	
};
*/
//////////////////////////////////////////////////////////////////////////
//�Ÿ˸��
struct CoolClothBase
{
	int		ImageObjectID;
	int		MainColor;
	int		OffColor;		

	bool IsEmpty()
	{
		return (ImageObjectID == 0);
	}
};
//�ŸˮM�˳]�w���
struct CoolSuitBase
{
	union
	{
		CoolClothBase	Item[9];
		struct  
		{
			CoolClothBase Head;
			CoolClothBase Gloves;	   
			CoolClothBase Shoes;	
			CoolClothBase Clothes;	   
			CoolClothBase Pants;	
			CoolClothBase Back;		   
			CoolClothBase Belt;		   
			CoolClothBase Shoulder;	   
			CoolClothBase Ornament;
		};
	};

	ShowEQStruct ShowEQ;

	void Init()
	{
		memset( this , 0 , sizeof(*this) );
		ShowEQ._Value = -1;
	}
};

struct HorseExBagBase
{
	int	ItemID;
	int HorseColor[4];
};

//////////////////////////////////////////////////////////////////////////
//�p�Ϊ��ʧ@log
enum HouseActionTypeENUM
{
	EM_HouseActionType_Item_BagToFurniture = 0	,//00���~_�I�]����í�(�t�íѡB�k��)
	EM_HouseActionType_Item_FurnitureToBag		,//01���~_�ò���I�](�t�íѡB�k��)
	EM_HouseActionType_Item_EqToFurniture		,//02���~_�˳Ʋ���í�(�t�íѡB�k��)
	EM_HouseActionType_Item_FurnitureToEq		,//03���~_�íѲ���˳�(�t�íѡB�k��)
	EM_HouseActionType_Item_BagToBank			,//04���~_�I�]����Ȧ�
	EM_HouseActionType_Item_BankToBag			,//05���~_�Ȧ沾��I�]
	EM_HouseActionType_Item_EqToBank			,//06���~_�˳Ʋ���Ȧ�
	EM_HouseActionType_Item_BankToEq			,//07���~_�Ȧ沾��˳�

	EM_HouseActionType_IntoHouse				,//08�i�J�p��
	EM_HouseActionType_LeaveHouse				,//09���}�p��
	EM_HouseActionType_ChangeHouseName			,//10�ק�p�ΦW��
	EM_HouseActionType_ChangePassWord			,//11�ק�p�αK�X
	EM_HouseActionType_ChangeVoc				,//12�ק�¾�~
	EM_HouseActionType_EnergyIntro				,//13��q�ɥR
	EM_HouseActionType_SpaceIntro				,//14�Ŷ��X�R
	EM_HouseActionType_Furniture_Appear			,//15�í��\�]���(�t�íѡB�k��)
	EM_HouseActionType_Furniture_Disappear		,//16�í��\�]����(�t�íѡB�k��)
	EM_HouseActionType_ChangeHouseType			,//17�槽�ܧ�
	EM_HouseActionType_AddFriend				,//18�W�[�ЫΦn��
	EM_HouseActionType_DeleteFriend				,//19�R���ЫΦn��
	EM_HouseActionType_HouseGreet				,//20�n�ͰݭԻy

	EM_HouseActionType_Servant_Fire				,//21�k��_�}��
	EM_HouseActionType_Servant_Employ			,//21�k��_����
	EM_HouseActionType_Servant_Talk				,//22�k��_���
	EM_HouseActionType_Servant_MagicCourse		,//23�k��_�]�k�ҵ{
	EM_HouseActionType_Servant_AttackCourse		,//24�k��_�����ҵ{
	EM_HouseActionType_Servant_DefendCourse		,//25�k��_�u�@�ҵ{
	EM_HouseActionType_Servant_CookCourse		,//26�k��_�i���ҵ{
	EM_HouseActionType_Servant_CraftCourse		,//27�k��_�u���ҵ{
};
//////////////////////////////////////////////////////////////////////////
//�˳ƨt��
#define  _MAX_TITLESYS_TITLE_COUNT_	4
struct TitleSysStruct
{
	int			Lv;
	int			Exp;
	float		Famous;
	int			TitleID[_MAX_TITLESYS_TITLE_COUNT_ ];
	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	}
};
//////////////////////////////////////////////////////////////////////////
enum OnAttackTypeENUM
{
	EM_OnAttackType_None	= -1 ,
	EM_OnAttackType_MainHand	,
	EM_OnAttackType_OffHand		,
	EM_OnAttackType_Skill		,
	EM_OnAttackType_Magic		,

};
//����Ĳ�o��T
struct OnAttackInfoStruct
{
	OnAttackTypeENUM	Type;
	int					OwnerID;
	int					TargetID;
	int					MagColID;
	int					MagBaseID;
	int					Damage;	
	ATTACK_DMGTYPE_ENUM	DmgType;
	OnAttackInfoStruct()
	{
		Init();
	};
	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	}
};

#define		MAX_BG_REGISTER_COUNT_	10
enum	BGIndependenceGameProcENUM
{
	EM_BGIndependenceGameProc_None		,	//���a�^�h
	EM_BGIndependenceGameProc_Rewrite	,	//�Ƽg
	EM_BGIndependenceGameProc_Merge		,	//�X��
};
//�Գ��^�Ǹ�T
struct BattleGroundReturnValueStruct
{
	bool	IsIndependenceGame;
	BGIndependenceGameProcENUM	MoneyProcType;
	BGIndependenceGameProcENUM	ItemProcType;
	BGIndependenceGameProcENUM	KeyItemProcType;
	BGIndependenceGameProcENUM	TitleProcType;
	BGIndependenceGameProcENUM	CardProcType;

	float	Register[ MAX_BG_REGISTER_COUNT_ ];
	StaticString<  _MAX_LUA_FUNTIONNAMESIZE_ >	RetLua;

	
	void Init()
	{
		memset( this , 0 , sizeof(*this) );
	}
};

//�۰ʦ^�������D��������
enum AutoReportPossibleCheaterENUM
{
	EM_AutoReportPossibleCheater_ThroughtWall	,	//����
	EM_AutoReportPossibleCheater_Teleport		,	//�ǰe
	EM_AutoReportPossibleCheater_Floating		,	//�B��
};

//�۰ʦ^�������D�����T
struct AutoReportBaseInfoStruct
{
	int		GUID;
	float	X,Y,Z;
};

#define _MAX_SLOT_MACHINE_HISTROY_COUNT_ 10
#define _MAX_SLOT_MACHINE_PRIZES_COUNT_ 10
//��l�Ѫ����T(���v��T)
struct SlotMachineHistoryBase
{
	int		Time;	//���~�ɶ�
	int		ItemID;
	int		Count;
};


//��l�Ѫ����T
struct SlotMachineInfo
{
	StaticVector< SlotMachineHistoryBase , _MAX_SLOT_MACHINE_HISTROY_COUNT_ > History;
	short	RandSeed[_MAX_SLOT_MACHINE_PRIZES_COUNT_];	//�üƺؤl
	int		FreeCount;	//�K�O����
	int		ItemID;
	int		ItemCount;
};

struct LuaHideInfoStruct
{
	//�@�����ø�T
	StaticString< _MAX_LUA_FUNTIONNAMESIZE_>	PlotStr;	//Ĳ�o���ê��@��
	int											OwnerDBID;	//�����
	int											OwnerOrgID;	//����̪���ID
	void Init()
	{
		memset( this , 0 , sizeof(*this));
	}
};

//���|�� ���|���
struct GuildWarBaseInfoStruct
{
	int		Guild;
	int		Score;
	StaticString<_MAX_NAMERECORD_SIZE_> GuildName;	
	bool	IsAssignment;
};
/*
//�J��t�Ψ����T
struct RuneSystemBaseStruct
{
	int	RuneSetItemID;	//�J��@��ժ��~ID
	int	MagicCol[2];
	int	RuneItem[6];	
};

#define _MAX_RUNESYSTEM_GROUP_COUNT_ 10
struct RuneSystemGroupStruct
{
	int	Count;
	RuneSystemBaseStruct Set[_MAX_RUNESYSTEM_GROUP_COUNT_];
	};
*/
enum PlayerMoveErrTypeENUM
{
	EM_PlayerMoveErrType_VecterErr				,	//���ʦV�q���~
	EM_PlayerMoveErrType_MoveDistErr			,	//���������~
	EM_PlayerMoveErrType_TotalMoveDistErr		,	//�����`�Z�����~
};

struct WeekZoneStruct
{
	int Day;
	int ZoneGroupID;
};

#define MAX_PHANTOM_COUNT	50
struct PhantomBase
{
	int	Lv;			//0 ��ܨS�����
	int Rank;
	int	Reserve[4];	//�O�d���
};

struct PhantomStruct
{
	PhantomBase	Info[ MAX_PHANTOM_COUNT ];	//�x�s��m�� �ۼv������ID%1000
	int	EQ[2];		//�ۼv������ID
	int SkillID;	//�i�ϥΧޯ�
	int SkillLv;	//�i�ϥΧޯ൥��
};

/*
struct PhantomRankTable
{
	int Rank;
	int	MaxLevel;
	int	NeedFragment;
};
struct PhantomLvTable
{
	int	Lv;
	int Type;
	int Material[4];
};
*/
struct BuffScheduleStruct
{
	int		ZoneID;
	float	EndTime;
	int		BuffID;
	int		BuffLv;
};

#pragma managed


#endif
