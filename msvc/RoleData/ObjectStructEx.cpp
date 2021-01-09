#include "ObjectStructEx.h"
#include "ReaderClass/CreateDBCmdClass.h"

#ifdef _CLIENT
#include "../mainproc/ObjectDataClass.h"
#endif

string	GameObjDbStructEx::m_tempString;

char* WearEqTypeENUMString[]={
	"無效果",
	"耐久度",
	"屬性 STR 力量",
	"屬性 STA 耐力",			
	"屬性 INT 智力",			
	"屬性 MND 靈力",
	"屬性 AGI 敏捷",			
	"屬性 所有(基本五個屬性)",
	"上限 HP",
	"上限 MP",
	"回復率 HP",
	"回復率 MP",
	"ATK 攻擊力",
	"DEF 防禦力",
	"MDEF 魔法防禦",
	"MATK 魔法攻擊",
	"物理命中",
	"物理迴避",
	"暴擊等級",
	"暴擊威力加強(%)",
	"法術暴擊等級",
	"法術暴擊威力加強(%)",
	"格擋等級",
	"攻擊速度(%)",
	"移動速度(%)",
	"武器威力 所有近戰或遠程(DMG)",
	"抗性 所有",
	"抗性 地",
	"抗性 水",
	"抗性 火",
	"抗性 風",
	"抗性 光",
	"抗性 闇",
	"MP消耗減少(%)",
	"經驗值",
	"掉寶率",
	"副手 命中率",
	"副手 傷害力(DMG%)",
	"防禦加強 鎧甲(%)",
	"防禦加強 鎖甲(%)",
	"防禦加強 皮甲(%)",
	"防禦加強 衣服(%)",
	"防禦加強 長袍(%)",
	"防禦加強 盾(%)",
	"魔法威力 所有(%)",
	"魔法威力 地(%)",
	"魔法威力 水(%)",
	"魔法威力 火(%)",
	"魔法威力 風(%)",
	"魔法威力 光(%)",
	"魔法威力 闇(%)",
	"施法速度 所有(%)",
	"遠程武器威力(%) 所有",
	"遠程武器威力(%) 弓",
	"遠程武器威力(%) 十字弓",
	"遠程武器威力(%) 槍",
	"近戰武器威力(%) 所有",
	"近戰武器威力(%) 空手",
	"近戰武器威力(%) 劍",
	"近戰武器威力(%) 匕首",
	"近戰武器威力(%) 權杖",
	"近戰武器威力(%) 斧",
	"近戰武器威力(%) 鎚棍棒",
	"近戰武器威力(%) 雙手劍",
	"近戰武器威力(%) 杖",
	"近戰武器威力(%) 雙手斧",
	"近戰武器威力(%) 雙手鎚",
	"近戰武器威力(%) 槍(長矛)",
	"遠程武器速度(%) 所有",
	"遠程武器速度(%) 弓",
	"遠程武器速度(%) 十字弓",
	"遠程武器速度(%) 槍", 
	"近戰武器速度(%) 所有",
	"近戰武器速度(%) 空手",
	"近戰武器速度(%) 劍",
	"近戰武器速度(%) 匕首",
	"近戰武器速度(%) 權杖",
	"近戰武器速度(%) 斧",
	"近戰武器速度(%) 鎚棍棒",
	"近戰武器速度(%) 雙手劍",
	"近戰武器速度(%) 杖",
	"近戰武器速度(%) 雙手斧",
	"近戰武器速度(%) 雙手鎚",
	"近戰武器速度(%) 槍(長矛)",
	"裝備能力 空手",
	"裝備能力 劍",	  	  	
	"裝備能力 匕首",
	"裝備能力 權杖",  	
	"裝備能力 斧",	  	
	"裝備能力 鎚棍棒",
	"裝備能力 雙手劍",
	"裝備能力 杖",
	"裝備能力 雙手斧",
	"裝備能力 雙手鎚",
	"裝備能力 槍(長矛)",
	"裝備能力 弓",
	"裝備能力 十字弓",
	"裝備能力 槍",
	"裝備能力 投擲",
	"裝備能力 鎧甲",
	"裝備能力 鎖甲",
	"裝備能力 皮甲",
	"裝備能力 衣服",
	"裝備能力 長袍",
	"裝備能力 盾",
	"裝備能力 手持法器",
	"裝備能力 雙手持",
	"技能上升 Unarmed空手",
	"技能上升 劍",
	"技能上升 匕首",
	"技能上升 權杖",
	"技能上升 斧",
	"技能上升 鎚棍棒",
	"技能上升 雙手劍",
	"技能上升 杖",
	"技能上升 雙手斧",
	"技能上升 雙手鎚",
	"技能上升 槍(長矛)",
	"技能上升 遠程武器 弓",
	"技能上升 遠程武器 十字弓",
	"技能上升 遠程武器 槍",
	"技能上升 防禦",
	"技能上升 打鐵",
	"技能上升 木工",
	"技能上升 製甲",
	"技能上升 裁縫",
	"技能上升 烹飪",
	"技能上升 煉金",
	"HQ品機率上升 打鐵(%)",
	"HQ品機率上升上升 木工(%)",
	"HQ品機率上升上升 製甲(%)",
	"HQ品機率上升上升 裁縫(%)",
	"HQ品機率上升上升 烹飪(%)",
	"HQ品機率上升上升 煉金(%)",	
	"ATK 攻擊力 (%)",
	"DEF 防禦力 (%)",
	"偷竊成功率 (%)",
	"金錢掉落率 (%)",
	"仇恨度增加 (%)",
	"戰士SP 回復加百分比",
	"遊俠SP 回復加百分比",
	"盜賊SP 回復加百分比",
	"魔法吸收率",
	"防禦吸收率",
	"治療吸收率",
	"魔法吸收點數",
	"防禦吸收點數",
	"治療吸收點數",
	"魔法傷害加點",
	"治療威力增加率",
	"治療威力增加點數",
	"遠程武器攻擊距離增加",
	"技能上升 筏木",
	"技能上升 採藥",
	"技能上升 挖礦",
	"技能上升 釣魚",
	"HQ品機率上升 筏木",
	"HQ品機率上升 採藥",
	"HQ品機率上升 挖礦",
	"HQ品機率上升 釣魚",
	"採集成功率",

	"屬性 STR 力量(%)",
	"屬性 STA 耐力(%)",			
	"屬性 INT 智力(%)",			
	"屬性 MND 靈力(%)",
	"屬性 AGI 敏捷(%)",			
	"屬性 所有(%)(基本五個屬性)",
	"上限 HP(%)",
	"上限 MP(%)",
	"騎乘速度(%)",
	"MDEF(%) 魔法防禦",
	"MATK(%) 魔法攻擊",
	"盾擋等級",
	"武器威力 所有近戰或遠程(DMG%)",
	"副職經驗值",
	"TP經驗值",

	"筏木成功率",
	"採藥成功率",
	"挖礦成功率",
	"釣魚成功率",
	"重力修正"  ,

	"兩次攻擊" ,
	"抗暴等擊",
	"法術抗暴等級",
	"地屬性攻擊" ,
	"水屬性攻擊" ,
	"火屬性攻擊" ,
	"風屬性攻擊" ,
	"光屬性攻擊" ,
	"暗屬性攻擊" ,

	"跳躍比率"  ,
	"魔法殤害"	,
	"魔法殤害比率"	,

	"刺穿盾檔",
	"刺穿格擋",

	"魔法命中",
	"魔法閃避",

	"物理命中率",
	"物理閃避率",
	"魔法命中率",
	"魔法閃避率",

	"採集產出量增加率",
	"採集速度增加率",
	"採集經驗值增加率",

	"(攻)攻擊玩家(or玩家寵物)威力加減",
	"(攻)攻擊NPC威力加減",
	"(守)被玩家(or玩家寵物)攻擊威力加減",
	"(守)被NPC攻擊威力加減",
	"(攻)AE法術攻擊威力加減",
	"(守)被AC法術攻擊威力加減",

	"生產速度增加率",
	"生產經驗值增加率",

	"增加劇情給予的經驗值率",
	"增加劇情給予的TP率",

	"戰意消耗減少(%)" ,
	"精力消耗減少(%)" ,
	"專注消耗減少(%)" ,
	"NPC 經驗值修正(%)"	,
	"NPC TP經驗值修正(%)"	,
	"近程武器攻擊距離增加",
	"抗性 所有%",
	"受到地系法術傷害增加%",
	"受到水系法術傷害增加%",
	"受到火系法術傷害增加%",
	"受到風系法術傷害增加%",
	"受到光系法術傷害增加%",
	"受到闇系法術傷害增加%",
	"格擋%",
	"每日任務經驗值加乘",
	"每日任務TP加乘",
};

/*
char* WearEqTypeENUMPositiveString[] = {
	"無效果",
	"耐久度 +",
	"力量 +",
	"耐力 +",			
	"智力 +",			
	"靈力 +",
	"敏捷 +",			
	"所有屬性 +",
	"HP上限 +",
	"MP上限 +",
	"HP回復 +",
	"MP回復率 +",
	"攻擊力 +",
	"防禦力 +",
	"魔法防禦 +",
	"魔法攻擊 +",
	"命中率 +",
	"迴避率 +",
	"致命一擊率 +",
	"致命一擊威力 +",
	"魔法致命一擊率 +",
	"魔法致命一擊威力 +",
	"格擋率 +",
	"攻擊速度 +",
	"移動速度 +",
	"傷害力 +",
	"所有抗性 +",
	"地抗性 +",
	"水抗性 +",
	"火抗性 +",
	"風抗性 +",
	"光抗性 +",
	"闇抗性 +",
	"MP消耗減少率 +",
	"經驗值率 +",
	"掉寶率 +",
	"副手命中率 +",
	"副手傷害率 +",
	"鎧甲防禦加強率 +",
	"鎖甲防禦加強率 +",
	"皮甲防禦加強率 +",
	"衣服防禦加強率 +",
	"長袍防禦加強率 +",
	"盾防禦加強率 +",
	"魔法威力 +",
	"地屬性魔法威力 +",
	"水屬性魔法威力 +",
	"火屬性魔法威力 +",
	"風屬性魔法威力 +",
	"光屬性魔法威力 +",
	"闇屬性魔法威力 +",
	"施法延遲 +",
	"遠程武器傷害率 +",
	"弓傷害率 +",
	"十字弓傷害率 +",
	"槍傷害率 +",
	"近戰武器傷害率 +",
	"空手傷害率 +",
	"劍傷害率 +",
	"匕首傷害率 +",
	"權杖傷害率 +",
	"斧傷害率 +",
	"鎚棍棒傷害率 +",
	"雙手劍傷害率 +",
	"杖傷害率 +",
	"雙手斧傷害率 +",
	"雙手鎚傷害率 +",
	"槍傷害率 +",
	"遠程攻擊延遲 +",
	"弓攻擊延遲 +",
	"十字弓攻擊延遲 +",
	"槍攻擊延遲 +", 
	"近戰武器攻擊延遲 +",
	"空手攻擊延遲 +",
	"劍攻擊延遲 +",
	"匕首攻擊延遲 +",
	"權杖攻擊延遲 +",
	"斧攻擊延遲 +",
	"鎚棍棒攻擊延遲 +",
	"雙手劍攻擊延遲 +",
	"杖攻擊延遲 +",
	"雙手斧攻擊延遲 +",
	"雙手鎚攻擊延遲 +",
	"槍攻擊延遲 +",
	"裝備能力空手 +",
	"裝備能力劍 +",	  	  	
	"裝備能力匕首 +",
	"裝備能力權杖 +",  	
	"裝備能力斧 +",	  	
	"裝備能力鎚棍棒 +",
	"裝備能力雙手劍 +",
	"裝備能力杖 +",
	"裝備能力雙手斧 +",
	"裝備能力雙手鎚 +",
	"裝備能力槍 +",
	"裝備能力弓 +",
	"裝備能力十字弓 +",
	"裝備能力槍 +",
	"裝備能力投擲 +",
	"裝備能力鎧甲 +",
	"裝備能力鎖甲 +",
	"裝備能力皮甲 +",
	"裝備能力衣服 +",
	"裝備能力長袍 +",
	"裝備能力盾 +",
	"裝備能力手持法器 +",
	"裝備能力雙手持 +",
	"空手技能上升 +",
	"劍技能上升 +",
	"匕首技能上升 +",
	"權杖技能上升 +",
	"斧技能上升 +",
	"鎚棍棒技能上升 +",
	"雙手劍技能上升 +",
	"杖技能上升 +",
	"雙手斧技能上升 +",
	"雙手鎚技能上升 +",
	"槍技能上升 +",
	"弓技能上升 +",
	"十字弓技能上升 +",
	"火鎗技能上升 +",
	"防禦技能上升 +",
	"打鐵技能上升 +",
	"木工技能上升 +",
	"製甲技能上升 +",
	"裁縫技能上升 +",
	"烹飪技能上升 +",
	"煉金技能上升 +",
	"打鐵HQ品機率上升率 +",
	"木工HQ品機率上升上升率 +",
	"製甲HQ品機率上升上升率 +",
	"裁縫HQ品機率上升上升率 +",
	"烹飪HQ品機率上升上升率 +",
	"煉金HQ品機率上升上升率 +",	
	"攻擊力增加百分比 +",
	"防禦力增加百分比 +",
	"偷竊成功率 +",
	"金錢掉落率 +",
	"仇恨度增加 +",
	"戰意回復率 +",
	"專注回復率 +",
	"精力回復率 +",
	"魔法吸收率 +",
	"防禦吸收率 +",
	"治療吸收率 +",
	"魔法吸收點數 +",
	"防禦吸收點數 +",
	"治療吸收點數 +",
	"魔法傷害加點 +",
	"治療威力增加率 +",
	"治療威力增加點數 +",
	"遠程武器攻擊距離增加 +",
	"筏木技能上升 +",
	"採藥技能上升 +",
	"挖礦技能上升 +",
	"釣魚技能上升 +",
	"筏木HQ品機率上升 +",
	"採藥HQ品機率上升 +",
	"挖礦HQ品機率上升 +",
	"釣魚HQ品機率上升 +",
	"採集成功率 +",
	"力量增加百分比 +",
	"耐力增加百分比 +",			
	"智力增加百分比 +",			
	"靈力增加百分比 +",
	"敏捷增加百分比 +",			
	"所有基本屬性增加百分比 +",
	"HP上限增加百分比 +",
	"MP上限增加百分比 +",
	"騎乘速度增加百分比 +",
	"魔法防禦增加百分比 +",
	"魔法攻擊增加百分比 +",
	"盾檔率 +",
	"傷害力增加百分比 +",
	"副職經驗值 +",
	"近程武器攻擊距離 +",

};

char* WearEqTypeENUMNegativeString[] = {
	"無效果 -",
	"耐久度 -",
	"力量 -",
	"耐力 -",			
	"智力 -",			
	"靈力 -",
	"敏捷 -",			
	"所有屬性 -",
	"HP上限 -",
	"MP上限 -",
	"HP回復 -",
	"MP回復率 -",
	"攻擊力 -",
	"防禦力 -",
	"魔法防禦 -",
	"魔法攻擊 -",
	"命中率 -",
	"迴避率 -",
	"致命一擊率 -",
	"致命一擊威力 -",
	"魔法致命一擊率 -",
	"魔法致命一擊威力 -",
	"格擋率 -",
	"攻擊速度 -",
	"移動速度 -",
	"傷害力 -",
	"所有抗性 -",
	"地抗性 -",
	"水抗性 -",
	"火抗性 -",
	"風抗性 -",
	"光抗性 -",
	"闇抗性 -",
	"MP消耗減少率 -",
	"經驗值率 -",
	"掉寶率 -",
	"副手命中率 -",
	"副手傷害率 -",
	"鎧甲防禦加強率 -",
	"鎖甲防禦加強率 -",
	"皮甲防禦加強率 -",
	"衣服防禦加強率 -",
	"長袍防禦加強率 -",
	"盾防禦加強率 -",
	"魔法威力 -",
	"地屬性魔法威力 -",
	"水屬性魔法威力 -",
	"火屬性魔法威力 -",
	"風屬性魔法威力 -",
	"光屬性魔法威力 -",
	"闇屬性魔法威力 -",
	"施法延遲 -",
	"遠程武器傷害率 -",
	"弓傷害率 -",
	"十字弓傷害率 -",
	"槍傷害率 -",
	"近戰武器傷害率 -",
	"空手傷害率 -",
	"劍傷害率 -",
	"匕首傷害率 -",
	"權杖傷害率 -",
	"斧傷害率 -",
	"鎚棍棒傷害率 -",
	"雙手劍傷害率 -",
	"杖傷害率 -",
	"雙手斧傷害率 -",
	"雙手鎚傷害率 -",
	"槍傷害率 -",
	"遠程攻擊延遲 -",
	"弓攻擊延遲 -",
	"十字弓攻擊延遲 -",
	"槍攻擊延遲 -", 
	"近戰武器攻擊延遲 -",
	"空手攻擊延遲 -",
	"劍攻擊延遲 -",
	"匕首攻擊延遲 -",
	"權杖攻擊延遲 -",
	"斧攻擊延遲 -",
	"鎚棍棒攻擊延遲 -",
	"雙手劍攻擊延遲 -",
	"杖攻擊延遲 -",
	"雙手斧攻擊延遲 -",
	"雙手鎚攻擊延遲 -",
	"槍攻擊延遲 -",
	"裝備能力空手 -",
	"裝備能力劍 -",	  	  	
	"裝備能力匕首 -",
	"裝備能力權杖 -",  	
	"裝備能力斧 -",	  	
	"裝備能力鎚棍棒 -",
	"裝備能力雙手劍 -",
	"裝備能力杖 -",
	"裝備能力雙手斧 -",
	"裝備能力雙手鎚 -",
	"裝備能力槍 -",
	"裝備能力弓 -",
	"裝備能力十字弓 -",
	"裝備能力槍 -",
	"裝備能力投擲 -",
	"裝備能力鎧甲 -",
	"裝備能力鎖甲 -",
	"裝備能力皮甲 -",
	"裝備能力衣服 -",
	"裝備能力長袍 -",
	"裝備能力盾 -",
	"裝備能力手持法器 -",
	"裝備能力雙手持 -",
	"空手技能上升 -",
	"劍技能上升 -",
	"匕首技能上升 -",
	"權杖技能上升 -",
	"斧技能上升 -",
	"鎚棍棒技能上升 -",
	"雙手劍技能上升 -",
	"杖技能上升 -",
	"雙手斧技能上升 -",
	"雙手鎚技能上升 -",
	"槍技能上升 -",
	"弓技能上升 -",
	"十字弓技能上升 -",
	"火鎗技能上升 -",
	"防禦技能上升 -",
	"打鐵技能上升 -",
	"木工技能上升 -",
	"製甲技能上升 -",
	"裁縫技能上升 -",
	"烹飪技能上升 -",
	"煉金技能上升 -",
	"打鐵HQ品機率上升率 -",
	"木工HQ品機率上升上升率 -",
	"製甲HQ品機率上升上升率 -",
	"裁縫HQ品機率上升上升率 -",
	"烹飪HQ品機率上升上升率 -",
	"煉金HQ品機率上升上升率 -",	
	"攻擊力增加百分比 -",
	"防禦力增加百分比 -",
	"偷竊成功率 -",
	"金錢掉落率 -",
	"仇恨度增加 -",
	"戰意回復率 -",
	"專注回復率 -",
	"精力回復率 -",
	"魔法吸收率 -",
	"防禦吸收率 -",
	"治療吸收率 -",
	"魔法吸收點數 -",
	"防禦吸收點數 -",
	"治療吸收點數 -",
	"魔法傷害加點 -",
	"治療威力增加率 -",
	"治療威力增加點數 -",
	"遠程武器攻擊距離增加 -",
	"筏木技能上升 -",
	"採藥技能上升 -",
	"挖礦技能上升 -",
	"釣魚技能上升 -",
	"筏木HQ品機率上升 -",
	"採藥HQ品機率上升 -",
	"挖礦HQ品機率上升 -",
	"釣魚HQ品機率上升 -",
	"採集成功率 -",
	"力量增加百分比 -",
	"耐力增加百分比 -",			
	"智力增加百分比 -",			
	"靈力增加百分比 -",
	"敏捷增加百分比 -",			
	"所有基本屬性增加百分比 -",
	"HP上限增加百分比 -",
	"MP上限增加百分比 -",
	"騎乘速度增加百分比 -",
	"魔法防禦增加百分比 -",
	"魔法攻擊增加百分比 -",
	"盾檔率 -",
	"傷害力增加百分比 -",
	"副職經驗值 -",	
	"近程武器攻擊距離 --",
};
*/

char* WeaponTypeENUMString[] = {
	"爪",
	"劍",
	"匕首",
	"權杖",
	"斧",
	"鎚棍棒",
	"雙手劍",
	"杖",
	"雙手斧",
	"雙手鎚",
	"長矛",
	"弓",
	"十字弓",
	"槍",
	"箭",
	//"矢",
	"子彈",
	"投擲",
	"伐木",
	"採藥",
	"採礦",
	"釣魚",
};

char* WeaponPosENUMString[] = {
	"主手"					,
	"副手"					,
	"單手"					,
	"雙手"					,
	"子彈"					,
	"弓"					,
	"採集"					,
};

char* ArmorTypeENUMString[] = {
	"鎧甲"					,
	"鎖甲"					,
	"皮甲"					,
	"布衣"					,
	"法袍"					,
	"盾"					,
	"法器"					,
};

char* ArmorPosENUMString[] = {
	"頭載"					,
	"手套"					,
	"足部"					,
	"上身"					,
	"下身"					,
	"背部"					,
	"腰帶"					,
	"肩甲"					,
	"項鍊"					,
	"戒指"					,
	"耳環"					,
	"副手"					,
	"法寶"					,
	"裝飾品"				,
};

char* ItemTypeENUMString[] = {
		"一般",
		"劇情物品",
		"食物",
		"甜食",
		"藥水",
		"礦石",
		"木材",
		"藥草",
		"原料",
		"種子",
		"花盆",
		"作物",
		"魚",
		"採集工具",
		"加工品",
		"配方 打鐵",
		"配方 木工",
		"配方 製甲",
		"配方 裁縫",
		"配方 煉金",
		"配方 烹飪",
		"衝等寶石",
		"效果光球",
		"金錢",
		"符文",
		"位置記錄",
};
/*
char* AddOnPosENUMString[] = {
"頭載"					,
"手套"					,
"足部"					,
"上身"					,
"下身"					,
"背部"					,
"腰帶"					,
"肩甲"					,
"項鍊"					,
"戒指"					,
"耳環"					,
"盾"					,
"武器"					,
};
*/

char* MagicCheckFunctionENUMString[] = {
	"無",									
	"(r, ) r一律代表機率",								
	"若自己有此防具(r,編號)",		
	"若目標有此防具(r,編號)",		
	"若自己有此類武器(r,類型編號)",	
	"若目標有此類武器(r,類型編號)",	
	"若自己有(r,物品or重要物品)",
	"若目標有(r,物品or重要物品)",
	"若自己擁有某buff(r,編號)",		
	"若目標擁有某buff(r,編號)",		
	"沒有作用已移除",		
	"沒有作用已移除",		
	"自己狀態(r,0非戰鬥/1戰鬥)",	
	"目標狀態(r,0非戰鬥/1戰鬥)",	
	"目標的種族是(r,種族編號)",			
	"自己HP低於(r,百分比)",	
	"沒有作用已移除",
	"沒有作用已移除"	,
	"自己有某群組的buff(r,群組編號)"	,
	"目標有某群組的buff(r,群組編號)"	,
	"自己已學會某技能(r,法術集合)"	,
	"若等級超過(r,等級)"	,

};

char* GameObjDbStructEx::GetName()			
{
#ifdef _CLIENT
	if( IsRecipe() != false )
	{
		// 取代原本物品名稱
		char	szReplaceString[512];
		char	szProductKey[512];

		sprintf( szProductKey, "Sys%d_name", Recipe.Item1_Normal.OrgObjID );
		sprintf( szReplaceString, "%s%s", g_ObjectData->GetString("SYS_RECIPE_TITLE"), g_ObjectData->GetString( szProductKey ) );

		m_tempString = szReplaceString;

		return (char*)m_tempString.c_str();
	}
	else
	if( IsCard() != false )
	{
		// 取代原本物品名稱
		char	szReplaceString[512];
		char	szProductKey[512];

		sprintf( szProductKey, "Sys%d_name", Item.CardOrgObjID );
		sprintf( szReplaceString, "%s%s", g_ObjectData->GetString("SYS_CARD_TITLE"), g_ObjectData->GetString( szProductKey ) );

		m_tempString = szReplaceString;

		return (char*)m_tempString.c_str();
	}
#endif
	return Name; 
}

char* GameObjDbStructEx::GetPluralName()		
{ 
	return Name_Plural; 
}


bool GameObjDbStructEx::IsEmpty( )
{
	return ( this == NULL );
}
bool GameObjDbStructEx::IsShop()
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_Shop );
}
bool GameObjDbStructEx::IsQuestNPC( )
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_QuestNPC );
}

bool GameObjDbStructEx::IsQuestDetail()
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_QuestDetail );
}

bool GameObjDbStructEx::IsNPC( )
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_NPC || Classification == EM_ObjectClass_QuestNPC );
}
bool GameObjDbStructEx::IsItem( )
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_Item );
}
bool GameObjDbStructEx::IsItem_Pure( )
{
	if( IsEmpty() )
		return false;

	if( IsItem() && Item.Class == EM_Item_Normal )
		return true;

	return false;
}

bool GameObjDbStructEx::IsWeapon( )
{
	if( IsEmpty() )
		return false;

	if( IsItem() && Item.Class == EM_Item_Weapon )
		return true;

	return false;
}
bool GameObjDbStructEx::IsArmor( )
{
	if( IsEmpty() )
		return false;

	if( IsItem() && Item.Class == EM_Item_Armor )
		return true;

	return false;
}
bool GameObjDbStructEx::IsMagicBase( )
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_MagicBase );
}
bool GameObjDbStructEx::IsMagicCollect( )
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_MagicCollect );
}
bool GameObjDbStructEx::IsSuit( )
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_Suit );
}


bool GameObjDbStructEx::IsKeyItem( )
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_KeyItem );
}
bool GameObjDbStructEx::IsMine( )
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_Mine );
}
bool GameObjDbStructEx::IsAttribute()
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_Attribute );
}

bool GameObjDbStructEx::IsRune()
{
	if( IsEmpty() )
		return false;

	return ( IsItem() && Item.Class == EM_Item_Rune );
}

bool GameObjDbStructEx::IsQuest()
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_QuestDetail );
}

bool GameObjDbStructEx::IsFlagObj()
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_Flag );
}
bool GameObjDbStructEx::IsEquip()
{
	if ( IsArmor() || IsWeapon() )
		return true;
	return false;
}

bool GameObjDbStructEx::IsBody()
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_BodyObj );

}
bool GameObjDbStructEx::IsImage()
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_Image );
}
bool GameObjDbStructEx::IsLearnMagic()
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_LearnMagic);
}
bool GameObjDbStructEx::IsPlayer()
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_Player );
}

bool GameObjDbStructEx::IsTitle()
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_Title );
}

bool GameObjDbStructEx::IsRecipe()
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_Recipe );
}


bool GameObjDbStructEx::IsCamp()
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_Camp );
}

bool GameObjDbStructEx::IsEqRefineAbility()
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_EqRefineAbility );
}

bool GameObjDbStructEx::IsTreasure()
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_Treasure );
}

bool GameObjDbStructEx::IsZone()
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_Zone );
}
bool GameObjDbStructEx::IsCreateRole()
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_CreateRole );
}
bool GameObjDbStructEx::IsCard()
{
	if( IsEmpty() )
		return false;

	if( IsItem() && Item.Class == EM_Item_Card )
		return true;

	return false;
}
bool GameObjDbStructEx::IsPhantom()
{
	if( IsEmpty() )
		return false;

	return ( Classification == EM_ObjectClass_Phantom );
}


bool GameObjDbStructEx::IsRestore()
{
	return false;
}
bool GameObjDbStructEx::IsSpecial()
{
	return false;
}

bool GameObjDbStructEx::IsSeed()
{
	if( IsEmpty() || !IsItem_Pure() || Item.Plant.Seed.Type == EM_SeedType_None )
		return false;

	return true;
}

bool GameObjDbStructEx::IsPot()
{
	if( IsEmpty() || !IsItem_Pure() || Item.Plant.Pot.Mode == 0 )
		return false;

	return true;
}

bool GameObjDbStructEx::IsManure()
{
	if( IsEmpty() || !IsItem_Pure() || Item.Plant.Manure.Type == EM_ManureType_None )
		return false;

	return true;
}

//是輔助法術
bool GameObjDbStructEx::IsAssistMagic( )
{
	if( IsMagicBase() == false )
		return false;

	if( MagicBase.MagicFunc != EM_MAGICFUN_Assist )
		return false;

	return true;
}

ObjectModeStruct  GameObjDbStructEx::GetModeFlag( )
{
	ObjectModeStruct Mode;
	if( IsEmpty() )
		return Mode;

	Mode._Mode	= 0;

	if( IsNPC() )
	{
		Mode.IsAllZoneVisible = NPC.IsAllZoneVisible;
	}

	switch( Classification )
	{
	case EM_ObjectClass_QuestNPC:
		{
			Mode.Show			= true; 	
			Mode.Mark			= true; 	
			Mode.Obstruct		= false;
			Mode.Gravity		= true; 	
			Mode.Save			= false; 	
			Mode.Drag			= true;     


			Mode.Strikback		= false;
			Mode.Move			= true;	
			Mode.Searchenemy	= false;
			Mode.Revive			= true;
			Mode.Fight			= false;			

			if( NPC.iQuestMode == 1 )
			{
				Mode.HideName		= true;	// 隱藏物件頭上名稱
				Mode.ShowRoleHead	= false;	// 隱藏頭像框
			}
			else
			{
				Mode.HideName		= false;
				Mode.ShowRoleHead	= true;				
			}
		
			Mode.IsAllZoneVisible = NPC.IsAllZoneVisible;
			Mode.DisableRotate	  = ( NPC.AutoRotate == false);


		} break;
	case EM_ObjectClass_NPC:
		{
			Mode.Show			= true; 	
			Mode.Mark			= true; 	
			Mode.Obstruct		= false;
			Mode.Gravity		= true; 	
			Mode.Save			= false; 	
			Mode.Drag			= true;     


			Mode.Strikback		= true;
			Mode.Move			= true;	
			Mode.Searchenemy	= true;
			Mode.Revive			= true;
			Mode.Fight			= true;
			Mode.ShowRoleHead	= true;

			Mode.IsAllZoneVisible = NPC.IsAllZoneVisible;
			Mode.DisableRotate	  = ( NPC.AutoRotate == false);


		} break;
	case EM_ObjectClass_Item:
		{
			Mode.Show	        = true; 	
			Mode.Mark	        = true; 	
			Mode.Obstruct       = false;
			Mode.Gravity	    = true; 	
			Mode.Save	        = false; 	
			Mode.Drag           = true;     


			Mode.Strikback	    = false;	
			Mode.Move		    = false;	
			Mode.Searchenemy	= false;	
			Mode.Revive		    = false;	
			Mode.Fight		    = false;
			Mode.ShowRoleHead	= false;
		} break;
	default:
		{
			Mode.Show	        = true; 	
			Mode.Mark	        = true; 	
			Mode.Obstruct       = false;
			Mode.Gravity	    = true; 	
			Mode.Save	        = false; 	
			Mode.Drag           = true;     

			Mode.Strikback	    = false;	
			Mode.Move		    = false;	
			Mode.Searchenemy	= false;	
			Mode.Revive		    = false;	
			Mode.Fight		    = false;
			Mode.ShowRoleHead	= false;
		} break;
	};

	return Mode;
}

char* GameObjDbStructEx::GetWearEqTypeENUMString( WearEqTypeENUM ID )
{
	if( ID >= EM_WearEqType_MaxCount || ID < 0 )
		return "";

	return WearEqTypeENUMString[ ID  ];	
}

char*	GameObjDbStructEx::GetMagicCheckFunctionENUMString( MagicCheckFunctionENUM ID )
{
	if( ID >= EM_MagicCheck_MaxCount || ID < 0 )
		return "";

	return MagicCheckFunctionENUMString[ ID  ];	
}

/*
char* GameObjDbStructEx::GetWearEqTypeENUMNegativeString( WearEqTypeENUM ID )
{
	if( ID >= EM_WearEqType_MaxCount || ID < 0 )
		return "";
	return WearEqTypeENUMNegativeString[ID];
}

char* GameObjDbStructEx::GetWearEqTypeENUMPositiveString( WearEqTypeENUM ID )
{
	if( ID >= EM_WearEqType_MaxCount || ID < 0 )
		return "";
	return WearEqTypeENUMPositiveString[ID];
}
*/

char* GameObjDbStructEx::GetWeaponTypeENUMString( GameObjectWeaponENUM Type )
{
	if ( Type >= EM_Weapon_Unarmed && Type <= EM_Weapon_Fishing )
		return WeaponTypeENUMString[Type];
	return "";
}

char* GameObjDbStructEx::GetWeaponPosENUMString( GameObjectWeaponPosENUM Pos )
{
	if ( Pos >= EM_WeaponPos_MainHand && Pos <= EM_WeaponPos_Manufacture )
		return WeaponPosENUMString[Pos];
	return "";
}

char* GameObjDbStructEx::GetArmorTypeENUMString( GameObjectArmorENUM Type )
{
	if ( Type >= EM_Armor_HeavyArmed && Type <= EM_Armor_Implement )
		return ArmorTypeENUMString[Type];
	return "";
}

char* GameObjDbStructEx::GetArmorPosENUMString( GameObjectArmorPosENUM Pos )
{
	if ( Pos >= EM_ArmorPos_Head && Pos <= EM_ArmorPos_Ornament )
		return ArmorPosENUMString[Pos];
	return "";
}

char* GameObjDbStructEx::GetItemTypeENUMString( ItemType_ENUM Type )
{	
	if ( Type >= EM_ItemType_Normal && Type <= EM_ItemType_Money )
		return ItemTypeENUMString[Type];
	return "";
}

int GameObjDbStructEx::GetWearEqValue( GameObjectWearEqStruct& Ability, WearEqTypeENUM Type, int begin )
{
	int value = 0;
	for ( int i = begin; i < Max_WearEqType_Count; i++ )
	{
		if ( Ability.EqType[i] == Type )
			value += Ability.EqTypeValue[i];
	}
	return value;
}
int GameObjDbStructEx::GetandClearWearEqValue( GameObjectWearEqStruct& Ability, WearEqTypeENUM Type )
{
	int value = 0;
	for ( int i = 0; i < Max_WearEqType_Count; i++ )
	{
		if ( Ability.EqType[i] == Type )
		{			
			value += Ability.EqTypeValue[i];
			Ability.EqType[i] = EM_WearEqType_None;
			Ability.EqTypeValue[i] = 0;
		}
	}
	return value;
}


int GameObjDbStructEx::GetWeaponDMG( GameObjectWearEqStruct& Ability )
{
	return GetWearEqValue(Ability, EM_WearEqType_DMG);
}

int GameObjDbStructEx::GetArmorDEF( GameObjectWearEqStruct& Ability )
{
	return GetWearEqValue(Ability, EM_WearEqType_DEF);
}

int GameObjDbStructEx::GetWeaponAtkSpeed( GameObjectWearEqStruct& Ability )
{
	return GetWearEqValue(Ability, EM_WearEqType_AtkSpeed);	
}

int GameObjDbStructEx::GetWearEqDurable( GameObjectWearEqStruct& Ability )
{
	return GetWearEqValue(Ability, EM_WearEqType_Durable);
}
int GameObjDbStructEx::GetWeaponMATK( GameObjectWearEqStruct& Ability )
{
	return GetWearEqValue(Ability, EM_WearEqType_MATK );	
}

int GameObjDbStructEx::GetArmorMDEF( GameObjectWearEqStruct& Ability )
{
	return GetWearEqValue(Ability, EM_WearEqType_MDEF );
}
/*
char* GameObjDbStructEx::GetAddOnPosENUMString( AddonPosENUM& AddOnPos )
{
if ( AddOnPos >= EM_AddonPos_Head && AddOnPos <= EM_AddonPos_Weapon )
return AddOnPosENUMString[AddOnPos];
return "";
}
*/
//檢查裝置能力與技能是否相符
bool	GameObjDbStructEx::CheckItemAndEqSkill( EqWearSkillStruct EqSkill )
{

	if( IsWeapon() )
	{
		switch( Item.WeaponType )
		{
		case EM_Weapon_None:                  
			break;
		case EM_Weapon_Unarmed:			// Unarmed空手
			if( EqSkill.Unarmed == false  )
				return false;
			break;
		case EM_Weapon_Blade:           // 劍
			if( EqSkill.Blade == false  )
				return false;
			break;
		case EM_Weapon_Dagger:          // 匕首
			if( EqSkill.Dagger == false  )
				return false;
			break;
		case EM_Weapon_Wand:            // 權杖
			if( EqSkill.Wand == false  )
				return false;
			break;
		case EM_Weapon_Axe:             // 斧
			if( EqSkill.Axe == false  )
				return false;
			break;
		case EM_Weapon_Bludgeon:        // 鎚棍棒
			if( EqSkill.Bludgeon == false  )
				return false;
			break;
		case EM_Weapon_Claymore:        // 雙手劍
			if( EqSkill.Claymore == false  )
				return false;
			break;
		case EM_Weapon_Staff:           // 杖
			if( EqSkill.Staff == false  )
				return false;
			break;
		case EM_Weapon_2H_Axe:          // 雙手斧
			if( EqSkill.Axe_2H == false  )
				return false;
			break;
		case EM_Weapon_2H_Hammer:       // 雙手鎚
			if( EqSkill.Hammer_2H == false  )
				return false;
			break;
		case EM_Weapon_Polearm:			// 槍(長矛)
			if( EqSkill.Polearm == false  )
				return false;
			break;
		case EM_Weapon_Bow:				// 遠程武器 弓
		case EM_Weapon_Ammo_Bow:		// 子彈 弓
			if( EqSkill.Bow == false  )
				return false;
			break;
		case EM_Weapon_CossBow:			// 遠程武器 十字弓
//		case EM_Weapon_Ammo_CossBow:	// 子彈 十字弓
			if( EqSkill.CossBow == false  )
				return false;
			break;
		case EM_Weapon_Gun:				// 遠程武器 槍
		case EM_Weapon_Ammo_Gun:		// 子彈 槍
			if( EqSkill.Gun == false  )
				return false;
			break;

		case EM_Weapon_Throw:			// 投擲類武器
			if( EqSkill.Throw == false  )
				return false;
			break;
		case EM_Weapon_Lumbering:		// 筏木
		case EM_Weapon_Herbalism:		// 採藥
		case EM_Weapon_Mining:			// 採礦
		case EM_Weapon_Fishing:			// 釣魚
			return true;
		default:
			return false;
		}
		return true;
	}
	else if( IsArmor() )
	{
		if(		Item.ArmorPos == EM_ArmorPos_Necklace 
			||	Item.ArmorPos == EM_ArmorPos_Ring
			||	Item.ArmorPos == EM_ArmorPos_Earring 
			||	Item.ArmorPos == EM_ArmorPos_Back			
			||	Item.ArmorPos == EM_ArmorPos_MagicTool 
			||	Item.ArmorPos == EM_ArmorPos_Ornament	)
			return true;

		switch( Item.ArmorType )
		{
		case EM_Armor_HeavyArmed:
			if( EqSkill.HeavyArmed == false )
				return false;
			break;
		case EM_Armor_LightArmed:
			if( EqSkill.LightArmed == false )
				return false;
			break;
		case EM_Armor_Leather:
			if( EqSkill.Leather == false )
				return false;
			break;
		case EM_Armor_Clothes:
			if( EqSkill.Clothes == false )
				return false;
			break;
		case EM_Armor_Robe:		
			if( EqSkill.Robe == false )
				return false;
			break;
		case EM_Armor_Shield:	
			if( EqSkill.Shield == false )
				return false;
			break;
		case EM_Armor_Implement:
			if( EqSkill.Implement == false )
				return false;
			break;
		default:
			return false;
		}
		return true;
	}

	return false;

}

void GameObjDbStructEx::ObjReader_InitBaseCommonObj( DB_GameObjDbStruct*& Pt, ReaderClass< DB_GameObjDbStruct >& Reader)
{
	Reader.SetData( "DirZoneID"         , &Pt->ZoneID					, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
	Reader.SetData( "DirVersionID"      , &Pt->VersionID				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
	Reader.SetData( "DirTagID"			, &Pt->TagID				    , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
	Reader.SetData( "Translate"			, &Pt->Translate			    , ENUM_Type_BitPoint        , 0 , ENUM_Indirect_Address );
}

//-------------------------------------------------------------------------------------------------------------
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_Zone( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;  

	if( IsInit == false )
	{
		char    Buf[256];
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//Reader.SetData( "OutputLanguage"    , &Pt->OutputLanguage			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		Reader.SetData( "MapFile"				, &Pt->GameData.Zone.MapFile				, ENUM_Type_CharString    , 0 , ENUM_Indirect_Address );
		Reader.SetData( "IsEnabledBlockCtrl"	, &Pt->GameData.Zone.IsEnabledBlockCtrl 	, ENUM_Type_BitPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "CtrlMaxZ"          	, &Pt->GameData.Zone.CtrlMaxZ				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "CtrlMaxX"          	, &Pt->GameData.Zone.CtrlMaxX				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "CtrlMinZ"          	, &Pt->GameData.Zone.CtrlMinZ				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "CtrlMinX"          	, &Pt->GameData.Zone.CtrlMinX				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "IsPrivateZone"			, &Pt->GameData.Zone.IsPrivateZone			, ENUM_Type_BitPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "BaseRoomCount"         , &Pt->GameData.Zone.BaseRoomCount			, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PlayRoomCount"         , &Pt->GameData.Zone.PlayRoomCount			, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PrivateZoneType"   	, &Pt->GameData.Zone.PrivateZoneType		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PrivateZoneLiveTime"	, &Pt->GameData.Zone.PrivateZoneLiveTime	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MapID"					, &Pt->GameData.Zone.MapID					, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "CampStatueObjID"		, &Pt->GameData.Zone.CampStatueObjID		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "IsEnabledRevPoint"		, &Pt->GameData.Zone.IsEnabledRevPoint		, ENUM_Type_BitPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "RevX"					, &Pt->GameData.Zone.RevX					, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "RevY"					, &Pt->GameData.Zone.RevY					, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "RevZ"					, &Pt->GameData.Zone.RevZ					, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "RevZoneID"				, &Pt->GameData.Zone.RevZoneID				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ViewBlock"				, &Pt->GameData.Zone.ViewBlock				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MapCount"				, &Pt->GameData.Zone.MapCount				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "LuaInitZone"			, &Pt->GameData.Zone.LuaInitZone			, ENUM_Type_CharString    , 0 , ENUM_Indirect_Address );
		Reader.SetData( "IsEnabledRide"			, &Pt->GameData.Zone.IsEnabledRide			, ENUM_Type_BitPoint      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "IsWorldBattleGround"			, &Pt->GameData.Zone.IsWorldBattleGround				, ENUM_Type_BitPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "iWorldBattleGroundWorldID"		, &Pt->GameData.Zone.iWorldBattleGroundWorldID			, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "IsCountryBattleGround"			, &Pt->GameData.Zone.IsCountryBattleGround				, ENUM_Type_BitPoint      , 0 , ENUM_Indirect_Address );
		
		Reader.SetData( "IsAllowTeamJoin"				, &Pt->GameData.Zone.IsAllowTeamJoin					, ENUM_Type_BitPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "IsEnableBattleGroundQueue"		, &Pt->GameData.Zone.IsEnableBattleGroundQueue			, ENUM_Type_BitPoint      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "IsLimitJoinLevel"				, &Pt->GameData.Zone.IsLimitJoinLevel					, ENUM_Type_BitPoint      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "IsForceGroup"					, &Pt->GameData.Zone.IsForceGroup						, ENUM_Type_BitPoint      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "iMinJoinLevel"				, &Pt->GameData.Zone.iMinJoinLevel				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "iMaxJoinLevel"				, &Pt->GameData.Zone.iMaxJoinLevel				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );


		Reader.SetData( "LuaPreJoinQueueCheck"			, &Pt->GameData.Zone.LuaPreJoinQueueCheck			, ENUM_Type_CharString    , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LuaAssistWorldGroupID"			, &Pt->GameData.Zone.LuaAssistWorldGroupID			, ENUM_Type_CharString    , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		for( int i = 0 ; i < 40 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "MapID%d" , i + 1 );
			Reader.SetData( Buf				, &Pt->GameData.Zone.MapInfoList[i].MapID		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "MapName%d" , i + 1 );
			Reader.SetData( Buf				, &Pt->GameData.Zone.MapInfoList[i].MapName		, ENUM_Type_CharString    , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "IsEabledSave%d" , i + 1 );
			Reader.SetData( Buf				, &Pt->GameData.Zone.MapInfoList[i].IsEnabledSave, ENUM_Type_BitPoint      , 0 , ENUM_Indirect_Address );
		}
		//------------------------------------------------------------------------------------
		for( int i = 0 ; i < 30 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "ZoneIniKey%d" , i );
			Reader.SetData( Buf				, &Pt->GameData.Zone.ZoneIni[i].Key			, ENUM_Type_CharString    , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "ZoneIniValue%d" , i );
			Reader.SetData( Buf				, &Pt->GameData.Zone.ZoneIni[i].Value		, ENUM_Type_CharString    , 0 , ENUM_Indirect_Address );
		}
		//------------------------------------------------------------------------------------
		for( int i = 1 ; i <= 4 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "iCountryWarLinkMap%d" , i );
			Reader.SetData( Buf				, &Pt->GameData.Zone.iCountryWarLinkMap[i]		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		}


		Reader.SetData( "RoomPlayerCount", &Pt->GameData.Zone.RoomPlayerCount			, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "IsAutoJoinEventZone"	, &Pt->GameData.Zone.IsAutoJoinEventZone		, ENUM_Type_BitPoint      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "MirrorInstanceType", &Pt->GameData.Zone.MirrorInstanceType		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MirrorLimitLv"		, &Pt->GameData.Zone.MirrorLimitLv			, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MirrorLimitTime"	, &Pt->GameData.Zone.MirrorLimitTime		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Mirror_X"			, &Pt->GameData.Zone.Mirror_X				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Mirror_Y"			, &Pt->GameData.Zone.Mirror_Y				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Mirror_Z"			, &Pt->GameData.Zone.Mirror_Z				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		
	}

	return &Reader;
}

//-------------------------------------------------------------------------------------------------------------
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_EqRefineAbility( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;  

	if( IsInit == false )
	{
		char    Buf[256];
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		for( int i = 0 ; i < Max_WearEqType_Count ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "EqType%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.EqRefineAttribute.Ability.EqType[i]			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "EqTypeValue%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.EqRefineAttribute.Ability.EqTypeValue[i]	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}
		//------------------------------------------------------------------------------------
		Reader.SetData( "ExEqPowerRate"     , &Pt->GameData.EqRefineAttribute.ExEqPowerRate     , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
	}

	return &Reader;
}

//-------------------------------------------------------------------------------------------------------------
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_AddPower( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;  

	if( IsInit == false )
	{
		char    Buf[256];
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );

//		Reader.SetData( "Rare"		        , &Pt->GameData.Rare			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------

		//------------------------------------------------------------------------------------
//		Reader.SetData( "InheritRate"       , &Pt->GameData.Attirbute.InheritRate       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
//		Reader.SetData( "InheritLV"         , &Pt->GameData.Attirbute.InheritLV         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
//		Reader.SetData( "InheritLV_Range"   , &Pt->GameData.Attirbute.InheritLV_Range   , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "Inc_Magic"             , &Pt->GameData.Attirbute.Inc_Magic             , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Inc_Magic_ActionRate"  , &Pt->GameData.Attirbute.Inc_Magic_ActionRate  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Inc_MagicType"         , &Pt->GameData.Attirbute.Inc_MagicType         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		//		Reader.SetData( "AddPos"            , &Pt->GameData.Attirbute.AddPos._Type              , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "AddOnPos_ArmorPos"    , &Pt->GameData.Attirbute.AddPos._ArmorPos       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "AddOnPos_ArmorType"   , &Pt->GameData.Attirbute.AddPos._ArmorType      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "AddOnPos_WeaponType"  , &Pt->GameData.Attirbute.AddPos._WeaponType     , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "AddOnPos_WeaponPos"   , &Pt->GameData.Attirbute.AddPos.WeaponPosEnum   , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "AddOnPos_Other"       , &Pt->GameData.Attirbute.AddPos._Other	        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "Type"              , &Pt->GameData.Attirbute.Type                      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		for( int i = 0 ; i < Max_WearEqType_Count ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "EqType%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.Attirbute.Ability.EqType[i]      , ENUM_Type_IntPoint         , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "EqTypeValue%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.Attirbute.Ability.EqTypeValue[i]  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}
		Reader.SetData( "EqTypeOnAttackMagicID"   , &Pt->GameData.Attirbute.Ability.OnAttackMagicID		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqTypeOnAttackMagicRank" , &Pt->GameData.Attirbute.Ability.OnAttackMagicRank	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqTypeOnAttackMagicRate" , &Pt->GameData.Attirbute.Ability.OnAttackMagicRate	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );        
		//------------------------------------------------------------------------------------
		Reader.SetData( "IsStandardAbility"	, &Pt->GameData.Attirbute.IsStandardAbility		, ENUM_Type_BitPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "StandardAbility_Lv", &Pt->GameData.Attirbute.StandardAbility_Lv	, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		for( int i = 0 ; i < 5 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "StandardAbility_Arg%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.Attirbute.StandardAbility_Arg[i]      , ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );

			sprintf_s( Buf , sizeof(Buf) , "StandardAbility_ArgType%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.Attirbute.StandardAbility_ArgType[i]  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}
		//------------------------------------------------------------------------------------
		Reader.SetData( "StarValue"       , &Pt->GameData.Attirbute.StarValue	          , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "InherentValue"   , &Pt->GameData.Attirbute.InherentValue	      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "IsBirthAbility"  , &Pt->GameData.Attirbute.IsBirthAbility		  , ENUM_Type_BitPoint		  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Rarity"		  , &Pt->GameData.Attirbute.Rarity				  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
	}

	return &Reader;
}
//-------------------------------------------------------------------------------------------------------------
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_CreateRole( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;  

	if( IsInit == false )
	{
		char    Buf[256];
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		Reader.SetData( "Job"				, &Pt->GameData.CreateRole.Job				, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "BornPosZoneID"		, &Pt->GameData.CreateRole.BornPos.ZoneID	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "BornPosX"			, &Pt->GameData.CreateRole.BornPos.X		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "BornPosY"			, &Pt->GameData.CreateRole.BornPos.Y		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "BornPosZ"			, &Pt->GameData.CreateRole.BornPos.Z		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "BornPosDir"		, &Pt->GameData.CreateRole.BornPos.Dir		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		for( int i = 0 ; i < 18 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "EQ_ID%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.CreateRole.EQ.ID[i]			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}
		for( int i = 0 ; i < 18 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "EQPreview_ID%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.CreateRole.EQPreview.ID[i]	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}
		for( int i = 0 ; i < 10 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "Item_ID%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.CreateRole.ItemID[i]		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}
		for( int i = 0 ; i < 10 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "Item_Count%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.CreateRole.ItemCount[i]		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}
		//------------------------------------------------------------------------------------
		Reader.SetData( "RaceLimit"		, &Pt->GameData.CreateRole.RaceLimit._Race	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
	}

	return &Reader;
}
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_Armor( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char    Buf[256];
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		Reader.SetData( "LimitVoc"          , &Pt->GameData.Limit.Voc._Voc   , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitRace"         , &Pt->GameData.Limit.Race._Race , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitSex"          , &Pt->GameData.Limit.Sex._Sex   , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitLv"           , &Pt->GameData.Limit.Level      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitStr"          , &Pt->GameData.Limit.STR        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitSta"          , &Pt->GameData.Limit.STA        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitInt"          , &Pt->GameData.Limit.INT        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitMnd"          , &Pt->GameData.Limit.MND        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitAgi"          , &Pt->GameData.Limit.AGI        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		Reader.SetData( "Mode"              , &Pt->GameData.Mode._Mode      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ItemType"          , &Pt->GameData.Item.ItemType   , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//        Reader.SetData( "MaxHeap"           , &Pt->GameData.MaxHeap         , ENUM_Type_IntPoint        , ENUM_Indirect_Address );
		Reader.SetData( "GenerateRate"      , &Pt->GameData.GenerateRate    , ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MaxWorldCount"     , &Pt->GameData.MaxWorldCount   , ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Rare"              , &Pt->GameData.Rare            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Cost"              , &Pt->GameData.Cost            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SpecialMoneyCost"  , &Pt->GameData.SpecialMoneyCost, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PricesType"        , &Pt->GameData.PricesType      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SellType"			, &Pt->GameData.SellType		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "IncMagic_Onuse"    , &Pt->GameData.Item.IncMagic_Onuse, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DisappearRate"     , &Pt->GameData.Item.DisappearRate , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DissolutionRate"   , &Pt->GameData.Item.DissolutionRate 	, ENUM_Type_FloatPoint     	, 0 , ENUM_Indirect_Address );
		Reader.SetData( "SrcRecipe"         , &Pt->GameData.Item.SrcRecipe , ENUM_Type_IntPoint         , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Durable"           , &Pt->GameData.Item.Durable    , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SuitID"            , &Pt->GameData.Item.SuitID     , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		for( int i = 2 ; i < Max_WearEqType_Count  ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "EqType%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.Item.Ability.EqType[i]			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "EqTypeValue%d" , i + 1 ); 
			Reader.SetData( Buf     , &Pt->GameData.Item.Ability.EqTypeValue[i]		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}

		Reader.SetData( "EqTypeOnAttackMagicID"   , &Pt->GameData.Item.Ability.OnAttackMagicID		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqTypeOnAttackMagicRank" , &Pt->GameData.Item.Ability.OnAttackMagicRank	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqTypeOnAttackMagicRate" , &Pt->GameData.Item.Ability.OnAttackMagicRate	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );        

		//------------------------------------------------------------------------------------
		Reader.SetData( "ArmorType"         , &Pt->GameData.Item.ArmorType          , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ArmorPos"          , &Pt->GameData.Item.ArmorPos           , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "HoleBase"          , &Pt->GameData.Item.HoleBase          	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "HoleRange"         , &Pt->GameData.Item.HoleRange         	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
//		Reader.SetData( "AddPowerOn"        , &Pt->GameData.Item.AddPowerOn        	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MaxAttrCount"			, &Pt->GameData.Item.MaxAttrCount      		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "BaseAttrCount"			, &Pt->GameData.Item.BaseAttrCount     		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SelectBaseAttrCount"   , &Pt->GameData.Item.SelectBaseAttrCount	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
//		Reader.SetData( "StandardType"      , &Pt->GameData.Item.StandardType       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "UseType"			, &Pt->GameData.Item.UseType			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "CliScript"         , &Pt->GameData.Item.CliScript  		, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SrvScript"         , &Pt->GameData.Item.SrvScript  		, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "CheckUseScript"    , &Pt->GameData.Item.CheckUseScript		, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MagicToolsScript"  , &Pt->GameData.Item.MagicToolsScript	, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LiveTimeType"		, &Pt->GameData.LiveTimeType			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "LiveTime"			, &Pt->GameData.LiveTime				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "IsStandardCost"	, &Pt->GameData.Item.IsStandardCost		, ENUM_Type_BitPoint		, 0 , ENUM_Indirect_Address );
//		Reader.SetData( "IsNoTitle"			, &Pt->GameData.Item.IsNoTitle			, ENUM_Type_BitPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "CardID"			, &Pt->GameData.Item.CardID				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "MagicToolsTime"	, &Pt->GameData.Item.MagicToolsTime		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "MagicToolsColdown"	, &Pt->GameData.Item.MagicToolsColdown	, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "IsFixDurable"      , &Pt->GameData.Item.IsFixDurable		, ENUM_Type_BitPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "StarValue"			, &Pt->GameData.Item.StarValue			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "RuneLimetLv"		, &Pt->GameData.Item.RuneLimetLv		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "MagicToolsTpExpScript"  , &Pt->GameData.Item.MagicToolsTpExpScript	, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ItemUniqueType"	, &Pt->GameData.Item.ItemUniqueType		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		for( int i = 0 ; i < _MAX_DROP_ABILITY_COUNT_ ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "DropAbility%d" , i + 1  );
			Reader.SetData( Buf            , &Pt->GameData.Item.DropItemAbility[i].OrgID       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "DropAbilityRate%d" , i + 1  );
			Reader.SetData( Buf            , &Pt->GameData.Item.DropItemAbility[i].Rate        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}
		Reader.SetData( "RefineTableID"		, &Pt->GameData.Item.RefineTableID		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
	
		Reader.SetData( "DDef"				, &Pt->GameData.Item.DDef				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "DMDef"				, &Pt->GameData.Item.DMDef				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "BodyMaxCount"		, &Pt->GameData.Item.BodyMaxCount		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "RefineLv"			, &Pt->GameData.Item.RefineLv			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "AddPowerQuality"	, &Pt->GameData.Item.AddPowerQuality	, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );


	}

	return &Reader;
}
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_Body( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );        


		Reader.SetData( "LimitSetting"      , &Pt->GameData.BodyObj.Limit.Setting		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitRace"         , &Pt->GameData.BodyObj.Limit.Race._Race    , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitSex"          , &Pt->GameData.BodyObj.Limit.Sex._Sex      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ObjType"			, &Pt->GameData.BodyObj.Type			    , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "Priority"			, &Pt->GameData.BodyObj.Priority		    , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
	}

	return &Reader;
}
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_Flag( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		DB_GameObjDbStruct* Pt = 0;
		//------------------------------------------------------------------------------------------------------------------------
		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint	, 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------------------------------------------
	}

	return &Reader;
}
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_Image( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		DB_GameObjDbStruct* Pt = 0;
		//------------------------------------------------------------------------------------------------------------------------
		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            	, &Pt->IsLock                   					, ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    	, &Pt->LastModifyDate           					, ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" 	, &Pt->LastModifyAccount        					, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"				, &Pt->DataGroup									, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       	, &Pt->LockAccount              					, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          	, &Pt->ProcRate.Rate            					, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"		, &Pt->GameData.LanguageSet							, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              	, &Pt->GameData.GUID            					, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              	, &Pt->GameData.Name            					, ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"			, &Pt->GameData.Name_Plural							, ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           	, &Pt->GameData.ImageID         					, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              	, &Pt->GameData.Note            					, ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         	, &Pt->GameData.ShortNote       					, ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		//----------------------------------	--------------------------------					------------------------------------------------------
		//		Reader.SetData( "MagicType"         	, &Pt->GameData.Image.MagicType 					, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "ActField"          	, &Pt->GameData.Image.ACTField  					, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ActWorld"          	, &Pt->GameData.Image.ACTWorld  					, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Sound"		         	, &Pt->GameData.Image.Sound  						, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ModelSize"         	, &Pt->GameData.Image.ModelSize 					, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageType"         	, &Pt->GameData.Image.ImageType 					, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "BoundRadiusX"          , &Pt->GameData.Image.BoundRadiusX                	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "BoundRadiusY"          , &Pt->GameData.Image.BoundRadiusY                	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "GatherMotion"          , &Pt->GameData.Image.GatherMotion                 	, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GatherParticalPoint1"  , &Pt->GameData.Image.GatherPartical[0].Point      	, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GatherParticalPoint2"  , &Pt->GameData.Image.GatherPartical[1].Point      	, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GatherParticalPoint3"  , &Pt->GameData.Image.GatherPartical[2].Point      	, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "GatherParticalName1"   , &Pt->GameData.Image.GatherPartical[0].Name       	, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GatherParticalName2"   , &Pt->GameData.Image.GatherPartical[1].Name       	, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GatherParticalName3"   , &Pt->GameData.Image.GatherPartical[2].Name       	, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "GatherParticalSound1"  , &Pt->GameData.Image.GatherPartical[0].IsSoundEnabled  , ENUM_Type_BitPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GatherParticalSound2"  , &Pt->GameData.Image.GatherPartical[1].IsSoundEnabled	, ENUM_Type_BitPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GatherParticalSound3"  , &Pt->GameData.Image.GatherPartical[2].IsSoundEnabled  , ENUM_Type_BitPoint      , 0 , ENUM_Indirect_Address );

//		Reader.SetData( "BeginACT"              , &Pt->GameData.Image.BeginACT                     	, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
//		Reader.SetData( "BeginPoint"            , &Pt->GameData.Image.BeginPoint                  	, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );


		Reader.SetData( "ShootMotion"           , &Pt->GameData.Image.ShootMotion                  	, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShootMotionScale"      , &Pt->GameData.Image.ShootMotionScale         		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShootACT"              , &Pt->GameData.Image.ShootACT                     	, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "FlyPoint"              , &Pt->GameData.Image.FlyBeginPoint                	, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShootPoint"            , &Pt->GameData.Image.ShootPoint                  	, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "FlyACT"                , &Pt->GameData.Image.FlyACT                       	, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "TargetPoint"           , &Pt->GameData.Image.TargetPoint                  	, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ExplodeACT"            , &Pt->GameData.Image.ExplodeACT                   	, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ArmorPos"              , &Pt->GameData.Image.ArmorPos                     	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ObjectType"            , &Pt->GameData.Image.ObjectType                   	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "ExtenPoint"            , &Pt->GameData.Image.ExtenPoint					, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ExtendACT"             , &Pt->GameData.Image.ExtendACT                     , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "BuffPoint"             , &Pt->GameData.Image.BuffPoint						, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "BuffACT"               , &Pt->GameData.Image.BuffACT                       , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "BuffACTEx"             , &Pt->GameData.Image.BuffACTEx                     , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------------------------------------------
		Reader.SetData( "PaperdollHairName"     , &Pt->GameData.Image.PaperdollHair.Name            , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollFaceName"     , &Pt->GameData.Image.PaperdollFace.Name            , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollHeadName"     , &Pt->GameData.Image.PaperdollHead.Name            , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollGlovesName"   , &Pt->GameData.Image.PaperdollGloves.Name          , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollShoesName"    , &Pt->GameData.Image.PaperdollShoes.Name           , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollClothesName"  , &Pt->GameData.Image.PaperdollClothes.Name         , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollPantsName"    , &Pt->GameData.Image.PaperdollPants.Name           , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollBackName"     , &Pt->GameData.Image.PaperdollBack.Name            , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollBeltName"     , &Pt->GameData.Image.PaperdollBelt.Name            , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollShouderName"  , &Pt->GameData.Image.PaperdollShouder.Name         , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------------------------------------------
		Reader.SetData( "PaperdollHairMainColor"     , &Pt->GameData.Image.PaperdollHair.MainColor.Color    , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollFaceMainColor"     , &Pt->GameData.Image.PaperdollFace.MainColor.Color    , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollHeadMainColor"     , &Pt->GameData.Image.PaperdollHead.MainColor.Color    , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollGlovesMainColor"   , &Pt->GameData.Image.PaperdollGloves.MainColor.Color  , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollShoesMainColor"    , &Pt->GameData.Image.PaperdollShoes.MainColor.Color   , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollClothesMainColor"  , &Pt->GameData.Image.PaperdollClothes.MainColor.Color , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollPantsMainColor"    , &Pt->GameData.Image.PaperdollPants.MainColor.Color   , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollBackMainColor"     , &Pt->GameData.Image.PaperdollBack.MainColor.Color    , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollBeltMainColor"     , &Pt->GameData.Image.PaperdollBelt.MainColor.Color    , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollShouderMainColor"  , &Pt->GameData.Image.PaperdollShouder.MainColor.Color , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------------------------------------------
		Reader.SetData( "PaperdollHairOffColor"     , &Pt->GameData.Image.PaperdollHair.OffColor.Color    	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollFaceOffColor"     , &Pt->GameData.Image.PaperdollFace.OffColor.Color    	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollHeadOffColor"     , &Pt->GameData.Image.PaperdollHead.OffColor.Color    	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollGlovesOffColor"   , &Pt->GameData.Image.PaperdollGloves.OffColor.Color  	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollShoesOffColor"    , &Pt->GameData.Image.PaperdollShoes.OffColor.Color   	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollClothesOffColor"  , &Pt->GameData.Image.PaperdollClothes.OffColor.Color 	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollPantsOffColor"    , &Pt->GameData.Image.PaperdollPants.OffColor.Color   	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollBackOffColor"     , &Pt->GameData.Image.PaperdollBack.OffColor.Color    	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollBeltOffColor"     , &Pt->GameData.Image.PaperdollBelt.OffColor.Color    	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PaperdollShouderOffColor"  , &Pt->GameData.Image.PaperdollShouder.OffColor.Color 	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------------------------------------------
		Reader.SetData( "ArmorMainColor"			, &Pt->GameData.Image.ArmorMainColor.Color				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ArmorOffColor"				, &Pt->GameData.Image.ArmorOffColor.Color				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------------------------------------------
		Reader.SetData( "SkinColor"					, &Pt->GameData.Image.SkinColor.Color					, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "HairColor"					, &Pt->GameData.Image.HairColor.Color					, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------------------------------------------
		Reader.SetData( "BoneScaleChest"			, &Pt->GameData.Image.BoneScaleChest					, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "BoneScaleButtock"			, &Pt->GameData.Image.BoneScaleButtock					, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "BoneScaleHand"				, &Pt->GameData.Image.BoneScaleHand						, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "BoneScaleLeg"				, &Pt->GameData.Image.BoneScaleLeg						, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "BoneScaleBra"				, &Pt->GameData.Image.BoneScaleBra						, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------------------------------------------
		Reader.SetData( "Alpha"						, &Pt->GameData.Image.Alpha								, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "TipType"					, &Pt->GameData.Image.TipType							, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "IsShowShadow"				, &Pt->GameData.Image.IsShowShadow						, ENUM_Type_BitPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "IsThrowType"				, &Pt->GameData.Image.IsThrowType						, ENUM_Type_BitPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ThrowTypePreviewID"		, &Pt->GameData.Image.ThrowTypePreviewID				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "FlagType"					, &Pt->GameData.Image.Flag.Type							, ENUM_Type_CharString    , sizeof( Pt->GameData.Image.Flag.Type		) , ENUM_Indirect_Address );
		Reader.SetData( "FlagBanner"				, &Pt->GameData.Image.Flag.Banner						, ENUM_Type_CharString    , sizeof( Pt->GameData.Image.Flag.Banner	) , ENUM_Indirect_Address );
		Reader.SetData( "FlagInsignia"				, &Pt->GameData.Image.Flag.Insignia						, ENUM_Type_CharString    , sizeof( Pt->GameData.Image.Flag.Insignia ) , ENUM_Indirect_Address );

		Reader.SetData( "FlagInsigniaColor1"		, &Pt->GameData.Image.Flag.InsigniaColor[0]				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "FlagInsigniaColor2"		, &Pt->GameData.Image.Flag.InsigniaColor[1]				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "FlagBannerColor1"			, &Pt->GameData.Image.Flag.BannerColor[0]				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "FlagBannerColor2"			, &Pt->GameData.Image.Flag.BannerColor[1]				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "LimitSex"					, &Pt->GameData.Image.LimitSex._Sex						, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "IsPolyLineEffect"			, &Pt->GameData.Image.IsPolyLineEffect					, ENUM_Type_BitPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MagicShowType"				, &Pt->GameData.Image.MagicShowType						, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SmallIconType"				, &Pt->GameData.Image.SmallIconType						, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "RideMotion"				, &Pt->GameData.Image.RideMotion						, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PhantomImg"				, &Pt->GameData.Image.PhantomImg					  , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
	}

	return &Reader;
}
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_Item( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char	Buf[512];
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   		, ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , 1 );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           		, ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        		, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        		, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              		, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , 1 );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet				, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , 1 );
		Reader.SetData( "Name"              , &Pt->GameData.Name            		, ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural			    , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            		, ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       		, ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		Reader.SetData( "LimitVoc"          , &Pt->GameData.Limit.Voc._Voc   		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitRace"         , &Pt->GameData.Limit.Race._Race 		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitSex"          , &Pt->GameData.Limit.Sex._Sex   		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitLv"           , &Pt->GameData.Limit.Level      		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitStr"          , &Pt->GameData.Limit.STR        		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitSta"          , &Pt->GameData.Limit.STA        		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitInt"          , &Pt->GameData.Limit.INT        		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitMnd"          , &Pt->GameData.Limit.MND        		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitAgi"          , &Pt->GameData.Limit.AGI        		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		Reader.SetData( "Mode"              , &Pt->GameData.Mode._Mode      		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ItemType"          , &Pt->GameData.Item.ItemType   		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MaxHeap"           , &Pt->GameData.MaxHeap         		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GenerateRate"      , &Pt->GameData.GenerateRate    		, ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MaxWorldCount"     , &Pt->GameData.MaxWorldCount   		, ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Rare"              , &Pt->GameData.Rare            		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Cost"              , &Pt->GameData.Cost            		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PricesType"        , &Pt->GameData.PricesType				, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SpecialMoneyCost"  , &Pt->GameData.SpecialMoneyCost		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SellType"			, &Pt->GameData.SellType				, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "IncMagic_Onuse"    , &Pt->GameData.Item.IncMagic_Onuse		, ENUM_Type_IntPoint     	, 0 , ENUM_Indirect_Address );
		Reader.SetData( "DisappearRate"     , &Pt->GameData.Item.DisappearRate 		, ENUM_Type_IntPoint     	, 0 , ENUM_Indirect_Address );
		Reader.SetData( "DissolutionRate"   , &Pt->GameData.Item.DissolutionRate 	, ENUM_Type_FloatPoint     	, 0 , ENUM_Indirect_Address );
		Reader.SetData( "SrcRecipe"         , &Pt->GameData.Item.SrcRecipe			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address ); 
		Reader.SetData( "BuyUnit"			, &Pt->GameData.BuyUnit					, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "BodyMaxCount"		, &Pt->GameData.Item.BodyMaxCount		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "UseType"			, &Pt->GameData.Item.UseType			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "CliScript"         , &Pt->GameData.Item.CliScript  		, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SrvScript"         , &Pt->GameData.Item.SrvScript  		, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "CheckUseScript"    , &Pt->GameData.Item.CheckUseScript		, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MaxAttrCount"      , &Pt->GameData.Item.MaxAttrCount      	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "BaseAttrCount"			, &Pt->GameData.Item.BaseAttrCount     		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SelectBaseAttrCount"   , &Pt->GameData.Item.SelectBaseAttrCount	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "Coloring_OffColor"	, &Pt->GameData.Item.Coloring_OffColor	, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "Coloring_MainColor", &Pt->GameData.Item.Coloring_MainColor	, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		Reader.SetData( "FixQuality"        , &Pt->GameData.Item.FixQuality			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqRefineType"      , &Pt->GameData.Item.EqRefineType		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqRefineRate_Base" , &Pt->GameData.Item.EqRefineRate_Base	, ENUM_Type_FloatPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqRefineRate_Fix"  , &Pt->GameData.Item.EqRefineRate_Fix	, ENUM_Type_FloatPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqRefineRate_Per"  , &Pt->GameData.Item.EqRefineRate_Per	, ENUM_Type_FloatPoint		, 0 , ENUM_Indirect_Address );

		Reader.SetData( "EqRefineMinLv"     , &Pt->GameData.Item.EqRefineMinLv		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqRefineMaxLv"     , &Pt->GameData.Item.EqRefineMaxLv		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqRefineEqMinLv"   , &Pt->GameData.Item.EqRefineEqMinLv	, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqRefineEqMaxLv"   , &Pt->GameData.Item.EqRefineEqMaxLv	, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );

		Reader.SetData( "EqRefineFailed_LevelDownRate_Base" , &Pt->GameData.Item.EqRefineFailed_LevelDownRate_Base	, ENUM_Type_FloatPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqRefineFailed_LevelDownRate_Fix"  , &Pt->GameData.Item.EqRefineFailed_LevelDownRate_Fix	, ENUM_Type_FloatPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqRefineFailed_LevelDownRate_Per"  , &Pt->GameData.Item.EqRefineFailed_LevelDownRate_Per	, ENUM_Type_FloatPoint		, 0 , ENUM_Indirect_Address );

		Reader.SetData( "EqRefineFailed_ExplodeRate_Base"	, &Pt->GameData.Item.EqRefineFailed_ExplodeRate_Base	, ENUM_Type_FloatPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqRefineFailed_ExplodeRate_Fix"	, &Pt->GameData.Item.EqRefineFailed_ExplodeRate_Fix		, ENUM_Type_FloatPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqRefineFailed_ExplodeRate_Per"	, &Pt->GameData.Item.EqRefineFailed_ExplodeRate_Per		, ENUM_Type_FloatPoint		, 0 , ENUM_Indirect_Address );

		Reader.SetData( "LiveTimeType"		, &Pt->GameData.LiveTimeType		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "LiveTime"			, &Pt->GameData.LiveTime			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "ReferenceLv"		, &Pt->GameData.Item.ReferenceLv		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "IsStandardCost"	, &Pt->GameData.Item.IsStandardCost		, ENUM_Type_BitPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "CardID"			, &Pt->GameData.Item.CardID				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "CastingTime"		, &Pt->GameData.Item.CastingTime		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "GuildContributionValue"		, &Pt->GameData.Item.GuildContributionValue		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		Reader.SetData( "emFurnitureType"		, &Pt->GameData.Item.emFurnitureType		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "emFurnitureEffect"		, &Pt->GameData.Item.emFurnitureEffect		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "iFurnitureStorageSize"	, &Pt->GameData.Item.iFurnitureStorageSize	, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "emFurniturePos"		, &Pt->GameData.Item.emFurniturePos			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "iCraftObjType"			, &Pt->GameData.Item.iCraftObjType			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "iFurnitureSuitID"		, &Pt->GameData.Item.iFurnitureSuitID		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "FurnitureNPCObjID"		, &Pt->GameData.Item.FurnitureNPCObjID		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );

		Reader.SetData( "BlackSmithHQPoint"		, &Pt->GameData.Item.BlackSmithHQPoint		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "CarpenterHQPoint"		, &Pt->GameData.Item.CarpenterHQPoint		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "MakeArmorHQPoint"		, &Pt->GameData.Item.MakeArmorHQPoint		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "TailorHQPoint"			, &Pt->GameData.Item.TailorHQPoint			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "CookHQPoint"			, &Pt->GameData.Item.CookHQPoint			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "AlchemyHQPoint"		, &Pt->GameData.Item.AlchemyHQPoint			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "ExpPoint"				, &Pt->GameData.Item.ExpPoint				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "TpPoint"				, &Pt->GameData.Item.TpPoint				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		Reader.SetData( "DigHoleMaxHoleCount"	, &Pt->GameData.Item.DigHole.MaxHoleCount	, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "DigHoleType"			, &Pt->GameData.Item.DigHole.Type			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "DigHoleRate"			, &Pt->GameData.Item.DigHole.Rate			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "IsUseNeedPassword"		, &Pt->GameData.Item.IsUseNeedPassword		, ENUM_Type_BitPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "SenderRelation"		, &Pt->GameData.Item.SenderRelation			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "TargetRelation"		, &Pt->GameData.Item.TargetRelation			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "StarValue"				, &Pt->GameData.Item.StarValue				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );

		Reader.SetData( "GuildResourceType"		, &Pt->GameData.Item.GuildResourceType		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "GuildResourceValue"	, &Pt->GameData.Item.GuildResourceValue		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );

		for( int i = 0 ; i < _MAX_DROP_ABILITY_COUNT_ ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "DropAbility%d" , i + 1  );
			Reader.SetData( Buf            , &Pt->GameData.Item.DropItemAbility[i].OrgID    , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "DropAbilityRate%d" , i + 1  );
			Reader.SetData( Buf            , &Pt->GameData.Item.DropItemAbility[i].Rate     , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}

		for( int i = 0 ; i < 8 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "AttrValue%d" , i + 1  );
			Reader.SetData( Buf            , &Pt->GameData.Item.AttrValue[i]					, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}
		//------------------------------------------------------------------------------------
		Reader.SetData( "OnDestroyScript"	, &Pt->GameData.Item.OnDestroyScript				, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ItemUseOKScript"	, &Pt->GameData.Item.ItemUseOKScript				, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		Reader.SetData( "Plant_Seed_Type"			, &Pt->GameData.Item.Plant.Seed.Type			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "Plant_Seed_GrowSpeed"		, &Pt->GameData.Item.Plant.Seed.GrowSpeed		, ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
//		Reader.SetData( "Plant_Seed_GrowTable"		, &Pt->GameData.Item.Plant.Seed.GrowTable		, ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Plant_Seed_ModelType"		, &Pt->GameData.Item.Plant.Seed.ModelType		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Plant_Seed_BestWater"		, &Pt->GameData.Item.Plant.Seed.BestWater		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Plant_Seed_BestTopdress"	, &Pt->GameData.Item.Plant.Seed.BestTopdress	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Plant_Seed_RandSeed"		, &Pt->GameData.Item.Plant.Seed.RandSeed		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Plant_DecWater"			, &Pt->GameData.Item.Plant.DecWater				, ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Plant_DecTopdress"			, &Pt->GameData.Item.Plant.DecTopdress			, ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "Plant_Pot_Mode"			, &Pt->GameData.Item.Plant.Pot.Mode				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "Plant_Pot_Type1_Evn1"		, &Pt->GameData.Item.Plant.Pot.EvnPoint[0][0]	, ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Plant_Pot_Type1_Evn2"		, &Pt->GameData.Item.Plant.Pot.EvnPoint[0][1]	, ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Plant_Pot_Type2_Evn1"		, &Pt->GameData.Item.Plant.Pot.EvnPoint[1][0]	, ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Plant_Pot_Type2_Evn2"		, &Pt->GameData.Item.Plant.Pot.EvnPoint[1][1]	, ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Plant_Pot_Type3_Evn1"		, &Pt->GameData.Item.Plant.Pot.EvnPoint[2][0]	, ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Plant_Pot_Type3_Evn2"		, &Pt->GameData.Item.Plant.Pot.EvnPoint[2][1]	, ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Plant_Manure_Type"			, &Pt->GameData.Item.Plant.Manure.Type			, ENUM_Type_IntPoint	    , 0 , ENUM_Indirect_Address );
//		Reader.SetData( "Plant_Manure_Evn1"			, &Pt->GameData.Item.Plant.Manure.EvnPoint[0]	, ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
//		Reader.SetData( "Plant_Manure_Evn2"			, &Pt->GameData.Item.Plant.Manure.EvnPoint[1]	, ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Plant_Manure_AddRare"		, &Pt->GameData.Item.Plant.Manure.AddRare		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Plant_Manure_AddWater"		, &Pt->GameData.Item.Plant.Manure.AddWater		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Plant_Manure_AddTopdress"	, &Pt->GameData.Item.Plant.Manure.AddTopdress	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "Plant_Manure_AddGrow"		, &Pt->GameData.Item.Plant.Manure.AddGrow		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Plant_Manure_AddHealth"	, &Pt->GameData.Item.Plant.Manure.AddHealth		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Plant_Manure_FeedPoint"	, &Pt->GameData.Item.Plant.Manure.FeedPoint		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Plant_Level"				, &Pt->GameData.Item.Plant.Level				, ENUM_Type_IntPoint	    , 0 , ENUM_Indirect_Address );

		Reader.SetData( "Furniture_Type"			, &Pt->GameData.Item.Furniture_Type				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );

		Reader.SetData( "Pet_PetObjID"				, &Pt->GameData.Item.Pet.PetObjID				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "Pet_Lv"					, &Pt->GameData.Item.Pet.Lv						, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "Pet_Property"				, &Pt->GameData.Item.Pet.Property				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "Pet_SkillPoint"			, &Pt->GameData.Item.Pet.SkillPoint				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "Pet_Talent"				, &Pt->GameData.Item.Pet.Talent					, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "Pet_PetType"				, &Pt->GameData.Item.Pet.PetType				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "Pet_Talent"				, &Pt->GameData.Item.Pet.Talent					, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "Pet_Str"					, &Pt->GameData.Item.Pet.STR					, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "Pet_Sta"					, &Pt->GameData.Item.Pet.STA					, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "Pet_Int"					, &Pt->GameData.Item.Pet.INT					, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "Pet_Mnd"					, &Pt->GameData.Item.Pet.MND					, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "Pet_Agi"					, &Pt->GameData.Item.Pet.AGI					, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "Pet_Spirit"				, &Pt->GameData.Item.Pet.Spirit					, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "Pet_LuaEvent"				, &Pt->GameData.Item.Pet.LuaEvent				, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "PetFood_SkillPoint"		, &Pt->GameData.Item.PetFood.SkillPoint			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "PetFood_Spirit"			, &Pt->GameData.Item.PetFood.Spirit				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "PetFood_Loyal"				, &Pt->GameData.Item.PetFood.Loyal				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "PetFood_Talent"			, &Pt->GameData.Item.PetFood.Talent				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "PetFood_Hunger"			, &Pt->GameData.Item.PetFood.Hunger				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "PetFood_Exp"				, &Pt->GameData.Item.PetFood.Exp				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "PetFood_Talent"			, &Pt->GameData.Item.PetFood.Talent				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "PetFood_EffectType"		, &Pt->GameData.Item.PetFood.EffectType			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "PetFood_EffectValue"		, &Pt->GameData.Item.PetFood.EffectValue		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );

		Reader.SetData( "DropListPacket"			, &Pt->GameData.Item.DropListPacket				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );

		Reader.SetData( "TargetLimit_Level"    		, &Pt->GameData.Item.ItemToItemLimit.Level      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "TargetLimit_ArmorPos"    	, &Pt->GameData.Item.ItemToItemLimit._ArmorPos  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "TargetLimit_ArmorType"   	, &Pt->GameData.Item.ItemToItemLimit._ArmorType , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "TargetLimit_WeaponType"   	, &Pt->GameData.Item.ItemToItemLimit._WeaponType, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "TargetLimit_Other"    		, &Pt->GameData.Item.ItemToItemLimit._Other     , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "TargetLimit_WeaponPos"    	, &Pt->GameData.Item.ItemToItemLimit.WeaponPosEnum, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "FurnitureSoundID"    		, &Pt->GameData.Item.FurnitureSoundID			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "ExBagType"    				, &Pt->GameData.Item.ExBagType					, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "ExBagTypeSub" 				, &Pt->GameData.Item.ExBagTypeSub				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "TitleSysFamous"			, &Pt->GameData.Item.TitleSys.Famous			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "TitleSysExp"				, &Pt->GameData.Item.TitleSys.Exp				, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "CollectionNPC"				, &Pt->GameData.Item.CollectionNPC				, ENUM_Type_IntPoint     	, 0 , ENUM_Indirect_Address );

//		Reader.SetData( "RuneSystemTableID"			, &Pt->GameData.Item.RuneSystemTableID			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
	}

	return &Reader;
}
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_KeyItem( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , 1 );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , 1 );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , 1 );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		Reader.SetData( "Type"              , &Pt->GameData.KeyItem.Type				, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "QuestID"           , &Pt->GameData.KeyItem.QuestID				, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "LifeSkillType"     , &Pt->GameData.KeyItem.LifeSkillType      	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LifeSkillLearnLv"  , &Pt->GameData.KeyItem.LifeSkillLearnLV   	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LifeSkillMaxLv"    , &Pt->GameData.KeyItem.LifeSkillMaxLV     	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Cost"				, &Pt->GameData.Cost					   	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
//		Reader.SetData( "PricesType"        , &Pt->GameData.PricesType      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SellType"			, &Pt->GameData.SellType		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		//------------------------------------------------------------------------------------
	}

	return &Reader;
}
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_LearnMagic( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );        

		Reader.SetData( "SPMagicCount"     , &Pt->GameData.LearnMagic.SPSkillCount      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "NormalMagicCount" , &Pt->GameData.LearnMagic.NormalSkillCount  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "SPMagicInfo"		, Pt->GameData.LearnMagic.SPSkill				, ENUM_Type_BinaryData		, sizeof(Pt->GameData.LearnMagic.SPSkill	));
		Reader.SetData( "NormalMagicInfo"	, Pt->GameData.LearnMagic.NormalSkill			, ENUM_Type_BinaryData		, sizeof(Pt->GameData.LearnMagic.NormalSkill	));
		
		/*
		char Buf[256];
		for( int i = 0 ; i < _MAX_Edit_SPSkill_COUNT_ ; i++ )
		{
			sprintf( Buf , "SPMagicID%d" , i + 1);
			Reader.SetData(  Buf           , &Pt->GameData.LearnMagic.SPSkill[i].MagicID       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf( Buf , "SPLearnLV%d" , i + 1);
			Reader.SetData(  Buf           , &Pt->GameData.LearnMagic.SPSkill[i].LearnLV       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf( Buf , "SPKeyItem%d" , i + 1);
			Reader.SetData(  Buf           , &Pt->GameData.LearnMagic.SPSkill[i].KeyItemID     , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

			sprintf( Buf , "SPNeed1MagicID%d" , i + 1);
			Reader.SetData(  Buf           , &Pt->GameData.LearnMagic.SPSkill[i].NeedMagicID[0] , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

			sprintf( Buf , "SPNeed2MagicID%d" , i + 1);
			Reader.SetData(  Buf           , &Pt->GameData.LearnMagic.SPSkill[i].NeedMagicID[1] , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

			sprintf( Buf , "SPNeed1MagicLv%d" , i + 1);
			Reader.SetData(  Buf           , &Pt->GameData.LearnMagic.SPSkill[i].NeedMagicLv[0] , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

			sprintf( Buf , "SPNeed2MagicLv%d" , i + 1);
			Reader.SetData(  Buf           , &Pt->GameData.LearnMagic.SPSkill[i].NeedMagicLv[1] , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

			sprintf( Buf , "SPSaveLvPos%d" , i + 1);
			Reader.SetData(  Buf           , &Pt->GameData.LearnMagic.SPSkill[i].SaveLvPos		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

			sprintf( Buf , "SPInherentLv%d" , i + 1);
			Reader.SetData(  Buf           , &Pt->GameData.LearnMagic.SPSkill[i].InherentLv		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		}

		for( int i = 0 ; i < _MAX_Edit_NormalSkill_COUNT_ ; i++ )
		{
			sprintf( Buf , "NormalMagicID%d" , i + 1);
			Reader.SetData(  Buf           , &Pt->GameData.LearnMagic.NormalSkill[i].MagicID       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf( Buf , "NormalLearnLV%d" , i + 1);
			Reader.SetData(  Buf           , &Pt->GameData.LearnMagic.NormalSkill[i].LearnLV       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf( Buf , "NormalKeyItem%d" , i + 1);
			Reader.SetData(  Buf           , &Pt->GameData.LearnMagic.NormalSkill[i].KeyItemID     , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

			sprintf( Buf , "NormalNeed1MagicID%d" , i + 1);
			Reader.SetData(  Buf           , &Pt->GameData.LearnMagic.NormalSkill[i].NeedMagicID[0] , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

			sprintf( Buf , "NormalNeed2MagicID%d" , i + 1);
			Reader.SetData(  Buf           , &Pt->GameData.LearnMagic.NormalSkill[i].NeedMagicID[1] , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

			sprintf( Buf , "NormalNeed1MagicLv%d" , i + 1);
			Reader.SetData(  Buf           , &Pt->GameData.LearnMagic.NormalSkill[i].NeedMagicLv[0] , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

			sprintf( Buf , "NormalNeed2MagicLv%d" , i + 1);
			Reader.SetData(  Buf           , &Pt->GameData.LearnMagic.NormalSkill[i].NeedMagicLv[1] , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

			sprintf( Buf , "NormalSaveLvPos%d" , i + 1);
			Reader.SetData(  Buf           , &Pt->GameData.LearnMagic.NormalSkill[i].SaveLvPos		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

			sprintf( Buf , "NormalInherentLv%d" , i + 1);
			Reader.SetData(  Buf           , &Pt->GameData.LearnMagic.NormalSkill[i].InherentLv		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}
	*/
	}

	return &Reader;
}
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_MagicBase( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char Buf[256];
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , 1 );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , 1 );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , 1 );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );

		//------------------------------------------------------------------------------------
		Reader.SetData( "EffectType"        , &Pt->GameData.MagicBase.EffectType      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MagicType"         , &Pt->GameData.MagicBase.MagicType       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "AtkCalType"        , &Pt->GameData.MagicBase.AtkCalType      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		//		Reader.SetData( "MagicBase"        , &Pt->GameData.MagicBase.MagicBase        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//		Reader.SetData( "MagicLV"          , &Pt->GameData.MagicBase.MagicLV          , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//		Reader.SetData( "NextMagic"          , &Pt->GameData.MagicBase.NextMagic      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		//------------------------------------------------------------------------------------
		Reader.SetData( "MagicFunc"         , &Pt->GameData.MagicBase.MagicFunc     , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "EffectTime"        , &Pt->GameData.MagicBase.EffectTime    , ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DLV_EffectTime"    , &Pt->GameData.MagicBase.DLV_EffectTime, ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "HateCost"          , &Pt->GameData.MagicBase.HateCost      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "EffectLV"          , &Pt->GameData.MagicBase.EffectLV      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//		Reader.SetData( "BaseHitRate"       , &Pt->GameData.MagicBase.HitRate       , ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		//		Reader.SetData( "DLV_HitRate"       , &Pt->GameData.MagicBase.DLv_HitRate   , ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		//		Reader.SetData( "RangeType"         , &Pt->GameData.MagicBase.RangeType     , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//		Reader.SetData( "TargetType"        , &Pt->GameData.MagicBase.TargetType    , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "AssistType"        , &Pt->GameData.MagicBase.AssistType		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Effect"            , &Pt->GameData.MagicBase.Effect._Value[0]			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Effect1"            , &Pt->GameData.MagicBase.Effect._Value[1]		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OnTimeMagic_Time"  , &Pt->GameData.MagicBase.OnTimeMagic_Time  , ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "OnTimeMagic_Magic" , &Pt->GameData.MagicBase.OnTimeMagic_Magic , ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );

		//		Reader.SetData( "EffectCount"       , &Pt->GameData.MagicBase.EffectCount       , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		//		Reader.SetData( "RangeSelectType"   , &Pt->GameData.MagicBase.RangeSelectType   , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "ChangeID"          , &Pt->GameData.MagicBase.FaceOffID			, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "RideID"			, &Pt->GameData.MagicBase.RideID			, ENUM_Type_IntPoint	  , 0 , ENUM_Indirect_Address );


		Reader.SetData( "EffectAddonType"	, &Pt->GameData.MagicBase.EffectAddonType	, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "OnAttackMagicID"   , &Pt->GameData.MagicBase.OnAttackMagicID	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OnAttackReboundMagicID"	, &Pt->GameData.MagicBase.OnAttackReboundMagicID	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OnMagicAttackReboundMagicID"	, &Pt->GameData.MagicBase.OnMagicAttackReboundMagicID	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OnBuffTimeOutMagicID"		, &Pt->GameData.MagicBase.OnBuffTimeOutMagicID		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OnBuffTimeOutMagicIDEx"		, &Pt->GameData.MagicBase.OnBuffTimeOutMagicIDEx		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OnDeadMagicID"		, &Pt->GameData.MagicBase.OnDeadMagicID		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OnKillMagicID"		, &Pt->GameData.MagicBase.OnKillMagicID		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "AddBuffTime"		, &Pt->GameData.MagicBase.AddBuffTime		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "BuffMaxLv"			, &Pt->GameData.MagicBase.BuffMaxLv		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "TempHateCost"      , &Pt->GameData.MagicBase.TempHateCost		, ENUM_Type_IntPoint    , 0 , ENUM_Indirect_Address );


		//------------------------------------------------------------------------------------
		//攻擊法術
		Reader.SetData( "Atk_AtkType"       , &Pt->GameData.MagicBase.Attack.AtkType     , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Atk_HateRate"      , &Pt->GameData.MagicBase.Attack.HateRate    , ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "Atk_DmgPower"      , &Pt->GameData.MagicBase.Attack.DmgPower    , ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Atk_FixValue"      , &Pt->GameData.MagicBase.Attack.FixValue    , ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Atk_FixType"       , &Pt->GameData.MagicBase.Attack.FixType     , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "Atk_Rand"			, &Pt->GameData.MagicBase.Attack.Rand        , ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Atk_CritialRate"   , &Pt->GameData.MagicBase.Attack.CritialRate , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//		Reader.SetData( "Atk_VampireRate"   , &Pt->GameData.MagicBase.Attack.VampireRate   , ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		//傳送術
		Reader.SetData( "TeleportZoneID"    , &Pt->GameData.MagicBase.Teleport.ZoneID   , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "TeleportX"         , &Pt->GameData.MagicBase.Teleport.X        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "TeleportY"         , &Pt->GameData.MagicBase.Teleport.Y        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "TeleportZ"         , &Pt->GameData.MagicBase.Teleport.Z        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "TeleportDir"       , &Pt->GameData.MagicBase.Teleport.Dir      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		//復活術
		Reader.SetData( "RaiseExpPrecnt"    , &Pt->GameData.MagicBase.Raise.ExpPrecnt   , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		//召喚生物
		Reader.SetData( "SCObjID"           , &Pt->GameData.MagicBase.SummonCreature.ObjID      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SCLevel"           , &Pt->GameData.MagicBase.SummonCreature.Level      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SCRangeLevel"      , &Pt->GameData.MagicBase.SummonCreature.RangeLevel , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SCLiveTime"        , &Pt->GameData.MagicBase.SummonCreature.LiveTime   , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SCSkillLvArg"      , &Pt->GameData.MagicBase.SummonCreature.SkillLvArg , ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SCOwnerPowerRate"  , &Pt->GameData.MagicBase.SummonCreature.OwnerPowerRate , ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "SCType"			, &Pt->GameData.MagicBase.SummonCreature.Type		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SCGroupID"			, &Pt->GameData.MagicBase.SummonCreature.GroupID	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "SCSkillType0"		, &Pt->GameData.MagicBase.SummonCreature.SkillType[0]	, ENUM_Type_IntPoint    , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SCSkillType1"		, &Pt->GameData.MagicBase.SummonCreature.SkillType[1]	, ENUM_Type_IntPoint    , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SCSkillType2"		, &Pt->GameData.MagicBase.SummonCreature.SkillType[2]	, ENUM_Type_IntPoint    , 0 , ENUM_Indirect_Address );

		Reader.SetData( "SCInitLua"			, &Pt->GameData.MagicBase.SummonCreature.InitLua        , ENUM_Type_CharString  , sizeof(Pt->GameData.MagicBase.SummonCreature.InitLua) , ENUM_Indirect_Address );
/*
		for( int i = 0 ; i < 5 ; i++ )
		{
			sprintf( Buf , "SCSkillKeyItem%d" , i+1 );
			Reader.SetData( Buf	, &Pt->GameData.MagicBase.SummonCreature.Skill[i].KeyItemID			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf( Buf , "SCSkillSpellRightTime%d" , i+1 );
			Reader.SetData( Buf	, &Pt->GameData.MagicBase.SummonCreature.Skill[i].SpellRightTime	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf( Buf , "SCSkillTargetType%d" , i+1 );
			Reader.SetData( Buf	, &Pt->GameData.MagicBase.SummonCreature.Skill[i].TargetType		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf( Buf , "SCSkillRate%d" , i+1 );
			Reader.SetData( Buf	, &Pt->GameData.MagicBase.SummonCreature.Skill[i].Rate				, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf( Buf , "SCSkillID%d" , i+1 );
			Reader.SetData( Buf	, &Pt->GameData.MagicBase.SummonCreature.Skill[i].SkillID			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}	
*/
		//------------------------------------------------------------------------------------
		//召喚物品
		Reader.SetData( "SIObjID"           , &Pt->GameData.MagicBase.SummonItem.ObjID          , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		//偷竊
		//		Reader.SetData( "StealClass"        , &Pt->GameData.MagicBase.Steal.Class               , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "StealSuccessRate"  , &Pt->GameData.MagicBase.Steal.SuccessRate         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		//產生物件執行據情
		Reader.SetData( "MIObjID"           , &Pt->GameData.MagicBase.ItemRunPlot.ObjID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MIMode"            , &Pt->GameData.MagicBase.ItemRunPlot.Mode		    , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MIPlotName"        , &Pt->GameData.MagicBase.ItemRunPlot.PlotName      , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MILiveTime"        , &Pt->GameData.MagicBase.ItemRunPlot.LiveTime      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MIUseMagic"        , &Pt->GameData.MagicBase.ItemRunPlot.UseMagic      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MIOnDeadMagic"     , &Pt->GameData.MagicBase.ItemRunPlot.OnDeadMagic   , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MIType"			, &Pt->GameData.MagicBase.ItemRunPlot.Type			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MIGroupID"			, &Pt->GameData.MagicBase.ItemRunPlot.GroupID		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MITargetType"      , &Pt->GameData.MagicBase.ItemRunPlot.TargetType    , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
//		Reader.SetData( "MILevel"			, &Pt->GameData.MagicBase.ItemRunPlot.Level    , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		Reader.SetData( "SettingFlag"       , &Pt->GameData.MagicBase.Setting._Type				, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SettingFlagEx"     , &Pt->GameData.MagicBase.SettingEx._Type			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SpecialAction"     , &Pt->GameData.MagicBase.SpecialAction._Type		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		//執行劇情
		Reader.SetData( "MRPlotName"        , &Pt->GameData.MagicBase.RunPlot.PlotName          , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		for( int i = 0 ; i < Max_WearEqType_Count ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "EqType%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.MagicBase.Ability.EqType[i]       , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "EqTypeValue%d" , i + 1 ); 
			Reader.SetData( Buf     , &Pt->GameData.MagicBase.Ability.EqTypeValue[i]  , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		}

		Reader.SetData( "EqTypeOnAttackMagicID"   , &Pt->GameData.MagicBase.Ability.OnAttackMagicID		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqTypeOnAttackMagicRank" , &Pt->GameData.MagicBase.Ability.OnAttackMagicRank	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqTypeOnAttackMagicRate" , &Pt->GameData.MagicBase.Ability.OnAttackMagicRate	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );        

		//------------------------------------------------------------------------------------
		//dot法術
		Reader.SetData( "DotTime"           , &Pt->GameData.MagicBase.DotMagic.Time   , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DotType"           , &Pt->GameData.MagicBase.DotMagic.Type   , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DotBase"           , &Pt->GameData.MagicBase.DotMagic.Base   , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );        

		Reader.SetData( "MagicClear"        , &Pt->GameData.MagicBase.ClearTime       , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		//法力盾
		Reader.SetData( "MagicShield_Type"  , &Pt->GameData.MagicBase.MagicShield.Type		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MagicShield_Effect", &Pt->GameData.MagicBase.MagicShield.Effect	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MagicShield_Point" , &Pt->GameData.MagicBase.MagicShield.Point		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );        

		//------------------------------------------------------------------------------------
		Reader.SetData( "MagicGroupID"      , &Pt->GameData.MagicBase.MagicGroupID      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "BuffCount"			, &Pt->GameData.MagicBase.BuffCount			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MaxBuffLv"			, &Pt->GameData.MagicBase.MaxBuffLv_Base	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "BuffTimeDesc_Time"	, &Pt->GameData.MagicBase.BuffTimeDesc_Time	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "BuffTimeDesc_Type"	, &Pt->GameData.MagicBase.BuffTimeDesc_Type	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		for( int i = 0 ; i < _MAX_BUFFSKILL_COUNT_ ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "BuffSkill%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.MagicBase.BuffSkill[i]	       , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		}
		//------------------------------------------------------------------------------------
		//技能等級影響
		Reader.SetData( "DotSkillLVArg"			, &Pt->GameData.MagicBase.DotMagic.DotSkillLVArg	, ENUM_Type_FloatPoint        	, 0 , ENUM_Indirect_Address );
		Reader.SetData( "EffectTime_SkillLVArg" , &Pt->GameData.MagicBase.EffectTime_SkillLVArg		, ENUM_Type_FloatPoint        	, 0 , ENUM_Indirect_Address );
		Reader.SetData( "MaxBuffLv_SkillLVArg"  , &Pt->GameData.MagicBase.MaxBuffLv_SkillLVArg		, ENUM_Type_FloatPoint        	, 0 , ENUM_Indirect_Address );
		Reader.SetData( "Ability_SkillLVArg"    , &Pt->GameData.MagicBase.Ability_SkillLVArg		, ENUM_Type_FloatPoint        	, 0 , ENUM_Indirect_Address );
		Reader.SetData( "DmgPower_SkillLVArg"   , &Pt->GameData.MagicBase.Attack.DmgPower_SkillLVArg, ENUM_Type_FloatPoint        	, 0 , ENUM_Indirect_Address );
		Reader.SetData( "FixDmg_SkillLVArg"     , &Pt->GameData.MagicBase.Attack.FixDmg_SkillLVArg	, ENUM_Type_FloatPoint        	, 0 , ENUM_Indirect_Address );
		Reader.SetData( "MagicShield_SkillLVArg", &Pt->GameData.MagicBase.MagicShield.SkillLvArg	, ENUM_Type_FloatPoint        	, 0 , ENUM_Indirect_Address );

		Reader.SetData( "PhyAttackType"			, &Pt->GameData.MagicBase.PhyAttackType				, ENUM_Type_IntPoint			, 0 , ENUM_Indirect_Address );


		//////////////////////////////////////////////////////////////////////////

		Reader.SetData( "IsStandard_Attack"		, &Pt->GameData.MagicBase.IsStandard_Attack			, ENUM_Type_BitPoint			, 0 , ENUM_Indirect_Address );        		
		Reader.SetData( "RefPowerLv_Attack"		, &Pt->GameData.MagicBase.RefPowerLv_Attack			, ENUM_Type_FloatPoint			, 0 , ENUM_Indirect_Address );
		Reader.SetData( "RefPowerRate_Attack"	, &Pt->GameData.MagicBase.RefPowerRate_Attack		, ENUM_Type_FloatPoint			, 0 , ENUM_Indirect_Address );
		//////////////////////////////////////////////////////////////////////////
		Reader.SetData( "ModelSize"				, &Pt->GameData.MagicBase.ModelSize					, ENUM_Type_FloatPoint			, 0 , ENUM_Indirect_Address );
		Reader.SetData( "Revive_SkillLVArg"		, &Pt->GameData.MagicBase.Revive_SkillLVArg			, ENUM_Type_IntPoint			, 0 , ENUM_Indirect_Address );

		Reader.SetData( "MagicGroupSet"			, &Pt->GameData.MagicBase.MagicGroupSet				, ENUM_Type_IntPoint			, 0 , ENUM_Indirect_Address );
		Reader.SetData( "ClearMagicGroupSet"	, &Pt->GameData.MagicBase.ClearMagicGroupSet		, ENUM_Type_IntPoint			, 0 , ENUM_Indirect_Address );
		Reader.SetData( "CheckUseLua"			, &Pt->GameData.MagicBase.CheckUseLua				, ENUM_Type_CharString			, 0 , ENUM_Indirect_Address );

		Reader.SetData( "SpecialMagicEventType"	, &Pt->GameData.MagicBase.SpecialMagicEventType		, ENUM_Type_IntPoint			, 0 , ENUM_Indirect_Address );
		Reader.SetData( "OnSpecialMagicID"		, &Pt->GameData.MagicBase.OnSpecialMagicID			, ENUM_Type_IntPoint			, 0 , ENUM_Indirect_Address );
		Reader.SetData( "EndUseLua"				, &Pt->GameData.MagicBase.EndUseLua					, ENUM_Type_CharString			, 0 , ENUM_Indirect_Address );
		Reader.SetData( "HitBackDist"			, &Pt->GameData.MagicBase.HitBackDist				, ENUM_Type_IntPoint			, 0 , ENUM_Indirect_Address );
		Reader.SetData( "CarryCount"			, &Pt->GameData.MagicBase.CarryCount				, ENUM_Type_IntPoint			, 0 , ENUM_Indirect_Address );

		for( int i = 0 ; i < 4 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "MotionChangeType%d" , i + 1  );
			Reader.SetData( Buf		, &Pt->GameData.MagicBase.MotionChangeType[i]				, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address  );
			sprintf_s( Buf , sizeof(Buf) , "MotionChangeID%d" , i + 1  );
			Reader.SetData( Buf		, &Pt->GameData.MagicBase.MotionChangeID[i]				, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address  );
		}
	}

	return &Reader;
}
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_Mine( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );        
		//------------------------------------------------------------------------------------
		Reader.SetData( "GenerateRate"      , &Pt->GameData.GenerateRate    , ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MaxWorldCount"     , &Pt->GameData.MaxWorldCount   , ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Rare"              , &Pt->GameData.Rare            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "BaseCount"         , &Pt->GameData.Mine.BaseCount  , ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Zone1"             , &Pt->Zone[0]                  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Zone2"             , &Pt->Zone[1]                  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Zone3"             , &Pt->Zone[2]                  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		//------------------------------------------------------------------------------------
		Reader.SetData( "ItemType"          , &Pt->GameData.Mine.Type       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "CreateType"        , &Pt->GameData.Mine.CreateType , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LVLimit"           , &Pt->GameData.Mine.LvLimit    , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "FlagID"	        , &Pt->GameData.Mine.iFlagID    , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "ReduceVal"	        , &Pt->GameData.Mine.iReduceVal , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "szLuaGetItemScript", &Pt->GameData.Mine.szLuaGetItemScript, ENUM_Type_CharString , 0 , ENUM_Indirect_Address );


		char Buf[256];
		for( int i = 0 ; i < 7 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "GetItem%d" , i +1 );
			Reader.SetData( Buf           , &Pt->GameData.Mine.GetItem[i]    , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

			sprintf_s( Buf , sizeof(Buf) , "GetItemRate%d" , i +1 );
			Reader.SetData( Buf           , &Pt->GameData.Mine.GetItemRate[i], ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

			sprintf_s( Buf , sizeof(Buf) , "GetItemCount%d" , i +1 );
			Reader.SetData( Buf           , &Pt->GameData.Mine.GetItemCount[i], ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address );

		}

		for( int i = 0 ; i < 5 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "GenerateObj%d" , i +1 );
			Reader.SetData( Buf           , &Pt->GameData.Mine.iGenerateObj[i]    , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

			sprintf_s( Buf , sizeof(Buf) , "GenerateObjRate%d" , i +1 );
			Reader.SetData( Buf           , &Pt->GameData.Mine.iGenerateObjRate[i], ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}
		//------------------------------------------------------------------------------------
	}

	return &Reader;
}
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_NPC( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Zone1"             , &Pt->Zone[0]                  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Zone2"             , &Pt->Zone[1]                  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Zone3"             , &Pt->Zone[2]                  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ReviveTime"        , &Pt->GameData.ReviveTime      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		//------------------------------------------------------------------------------------
		Reader.SetData( "Race"              , &Pt->GameData.NPC.Race        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Vocation"          , &Pt->GameData.NPC.Vocation    , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Vocation_Sub"      , &Pt->GameData.NPC.Vocation_Sub, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Sex"               , &Pt->GameData.NPC.Sex         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ExpRate"           , &Pt->GameData.NPC.ExpRate     , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "TPRate"            , &Pt->GameData.NPC.TpRate      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Level"             , &Pt->GameData.NPC.Level       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LevelRange"        , &Pt->GameData.NPC.LevelRange  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "STR"               , &Pt->GameData.NPC.STR         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "STA"               , &Pt->GameData.NPC.STA         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "INT"               , &Pt->GameData.NPC.INT         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MND"               , &Pt->GameData.NPC.MND         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "AGI"               , &Pt->GameData.NPC.AGI         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "MoveSpeed"         , &Pt->GameData.NPC.MoveSpeed   , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SearchRange"       , &Pt->GameData.NPC.SearchRange , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "DropMoney_Base"    , &Pt->GameData.NPC.DropMoney_Base , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DropMoney_Rand"    , &Pt->GameData.NPC.DropMoney_Rand , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "Brave"             , &Pt->GameData.NPC.Brave       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LinkType"          , &Pt->GameData.NPC.LinkType    , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "EscapeType"        , &Pt->GameData.NPC.EscapeType  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		char Buf[256];
		for( int i = 0 ; i < _MAX_DROPITEM_COUNT_ ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "DropID%d" , i + 1  );
			Reader.SetData( Buf            , &Pt->GameData.NPC.DropItem[i].OrgID       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "DropRate%d" , i + 1  );
			Reader.SetData( Buf            , &Pt->GameData.NPC.DropItem[i].Rate        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}

		for( int i = 0 ; i < _MAX_DROP_ABILITY_COUNT_ ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "DropAbility%d" , i + 1  );
			Reader.SetData( Buf            , &Pt->GameData.NPC.DropItemAbility[i].OrgID       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "DropAbilityRate%d" , i + 1  );
			Reader.SetData( Buf            , &Pt->GameData.NPC.DropItemAbility[i].Rate        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}


		for( int i = 0 ; i < _MAX_NPC_EQSEL_COUNT_ ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "MainHandEq%d" , i + 1 );
			Reader.SetData( Buf , &Pt->GameData.NPC.MainHandEQ[i] , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "SecHandEq%d" , i + 1 );
			Reader.SetData( Buf , &Pt->GameData.NPC.SecHandEQ[i]  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}

		Reader.SetData( "BowEQ"			, &Pt->GameData.NPC.BowEQ		  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OrnamentEQ"	, &Pt->GameData.NPC.OrnamentEQ	  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "CampID"		, &Pt->GameData.NPC.CampID		  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		/*		for( int i = 0 ; i < 10 ; i++ )
		{
		sprintf( Buf , "Magic%d" , i+1 );
		Reader.SetData( Buf , &Pt->GameData.NPC.NpcMagic[i] , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}
		*/
		for( int i = 0 ; i < _MAX_NPC_SPELL_MAGIC_COUNT_ ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "SpellRightTime%d" , i+1 );
			Reader.SetData( Buf , &Pt->GameData.NPC.Spell[i].RigthTime	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "SpellTarget%d" , i+1 );
			Reader.SetData( Buf , &Pt->GameData.NPC.Spell[i].TargetType , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "SpellRate%d" , i+1 );
			Reader.SetData( Buf , &Pt->GameData.NPC.Spell[i].Rate		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "SpellMagic%d" , i+1 );
			Reader.SetData( Buf , &Pt->GameData.NPC.Spell[i].MagicID	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "SpellMagicLv%d" , i+1 );
			Reader.SetData( Buf , &Pt->GameData.NPC.Spell[i].MagicLv	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "SpellString%d" , i+1 );
			Reader.SetData( Buf , &Pt->GameData.NPC.Spell[i].SpellString , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		}


//		Reader.SetData( "AddPowerLV"       , &Pt->GameData.NPC.AddPowerLV	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "TitleType"        , &Pt->GameData.NPC.TitleType	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DB_ResistID"      , &Pt->GameData.NPC.DB_ResistID  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		for( int i = 0 ; i < _MAX_NPC_STEAL_ITEM_COUNT_ ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "StealItemOrgID%d" , i + 1  );
			Reader.SetData( Buf            , &Pt->GameData.NPC.StealItem[i].OrgID       , ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "StealItemRate%d" , i + 1  );
			Reader.SetData( Buf            , &Pt->GameData.NPC.StealItem[i].Rate        , ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address );
		}
		Reader.SetData( "StealMoney_Base"  , &Pt->GameData.NPC.StealMoney_Base			, ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address );
		Reader.SetData( "StealMoney_Rand"  , &Pt->GameData.NPC.StealMoney_Rand			, ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address );

		for( int i = 0 ; i < _MAX_NPC_AVOID_MAGIC_TYPE_COUNT_ ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "AvoidMagicType%d" , i + 1  );
			Reader.SetData( Buf            , &Pt->GameData.NPC.AvoidMagicType[i]		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		}
		Reader.SetData( "Effect"           , &Pt->GameData.NPC.Effect._Value			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "RaceGroupType"    , &Pt->GameData.NPC.RaceGroupType			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "KeepDistance"     , &Pt->GameData.NPC.KeepDistance				, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OrgWeaponType"    , &Pt->GameData.NPC.OrgWeaponType			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );		
		Reader.SetData( "OrgArmorType"     , &Pt->GameData.NPC.OrgArmorType				, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "FollowRange"      , &Pt->GameData.NPC.FollowRange				, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "RaiseChangeNPCID1", &Pt->GameData.NPC.RaiseChangeNPCID[0]		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "RaiseChangeNPCID2", &Pt->GameData.NPC.RaiseChangeNPCID[1]		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "RaiseChangeRate1" , &Pt->GameData.NPC.RaiseChangeRate[0]		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "RaiseChangeRate2" , &Pt->GameData.NPC.RaiseChangeRate[1]		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "OtherFlag"			, &Pt->GameData.NPC.OtherFlag				, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		

		//------------------------------------------------------------------------------------
		/*
		for( int j = 0 ; j < 2 ; j++ )
		{
			for( int i = 0 ; i < 5 ; i++ )			
			{
				sprintf( Buf , "EqType%d" , i + 1 + j*5 );
				Reader.SetData( Buf     , &Pt->GameData.NPC.Ability[j].EqType[i]       , ENUM_Type_IntPoint         , 0 , ENUM_Indirect_Address );
				sprintf( Buf , "EqTypeValue%d" , i + 1 + j* 5 );
				Reader.SetData( Buf     , &Pt->GameData.NPC.Ability[j].EqTypeValue[i]  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			}
		}
		*/
		for( int i = 0 ; i < Max_WearEqType_Count ; i++ )			
		{
			sprintf_s( Buf , sizeof(Buf) , "EqType%d" , i + 1  );
			Reader.SetData( Buf     , &Pt->GameData.NPC.Ability.EqType[i]       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "EqTypeValue%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.NPC.Ability.EqTypeValue[i]  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "DEqTypeValue%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.NPC.DEqTypeValue[i]			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}

		for( int i = 0 ; i < Max_WearEqType_Count ; i++ )			
		{
			sprintf_s( Buf , sizeof(Buf) , "EqExType%d" , i + 1  );
			Reader.SetData( Buf     , &Pt->GameData.NPC.AbilityEx.EqType[i]       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "EqExTypeValue%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.NPC.AbilityEx.EqTypeValue[i]  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}


		Reader.SetData( "IsAbilityStandard"	, &Pt->GameData.NPC.IsAbilityStandard		, ENUM_Type_BitPoint      , 0 , ENUM_Indirect_Address );        
		Reader.SetData( "AbilityValue1"    , &Pt->GameData.NPC.AbilityValue[0]			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );		
		Reader.SetData( "AbilityValue2"     , &Pt->GameData.NPC.AbilityValue[1]			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			
		/*
		for( int i = 0 ; i < 5 ; i++ )
		{
			sprintf( Buf , "EqType%d" , i + 6 );
			Reader.SetData( Buf     , &Pt->GameData.NPC.Ability.EqType[i]      , ENUM_Type_IntPoint         , 0 , ENUM_Indirect_Address );
			sprintf( Buf , "EqTypeValue%d" , i + 6 );
			Reader.SetData( Buf     , &Pt->GameData.NPC.Ability.EqTypeValue[i]  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}*/

		Reader.SetData( "EqTypeOnAttackMagicID"		, &Pt->GameData.NPC.Ability.OnAttackMagicID		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqTypeOnAttackMagicRank"	, &Pt->GameData.NPC.Ability.OnAttackMagicRank	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqTypeOnAttackMagicRate"	, &Pt->GameData.NPC.Ability.OnAttackMagicRate	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );        
//		Reader.SetData( "IsNoMPSP"					, &Pt->GameData.NPC.IsNoMPSP						, ENUM_Type_BitPoint      , 0 , ENUM_Indirect_Address );        
		Reader.SetData( "TitleName"					, &Pt->GameData.NPC.TitleName			            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );

		Reader.SetData( "PhyResistRate1"      , &Pt->GameData.NPC.PhyResistRate[0]  , ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PhyResistRate2"      , &Pt->GameData.NPC.PhyResistRate[1]  , ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PhyResistRate3"      , &Pt->GameData.NPC.PhyResistRate[2]  , ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		Reader.SetData( "ZoneID"				, &Pt->GameData.NPC.ZoneID				, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "X"						, &Pt->GameData.NPC.X					, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Y"						, &Pt->GameData.NPC.Y					, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Z"						, &Pt->GameData.NPC.Z					, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
//		Reader.SetData( "IsAllZoneVisible"		, &Pt->GameData.NPC.IsAllZoneVisible	, ENUM_Type_BitPoint    , 0 , ENUM_Indirect_Address );        
//		Reader.SetData( "IsShowNpcPos"			, &Pt->GameData.NPC.IsShowNpcPos		, ENUM_Type_BitPoint    , 0 , ENUM_Indirect_Address );  
//		Reader.SetData( "AutoRotate"			, &Pt->GameData.NPC.AutoRotate			, ENUM_Type_BitPoint    , 0 , ENUM_Indirect_Address );        
		Reader.SetData( "ZoneID_Bk"				, &Pt->GameData.NPC.ZoneID_Bk			, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address  );

		Reader.SetData( "KillGroupID"			, &Pt->GameData.NPC.KillGroupID			, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address  );
		Reader.SetData( "szLuaInitScript"		, &Pt->GameData.NPC.szLuaInitScript		, ENUM_Type_CharString		, 0 , ENUM_Indirect_Address );        
		Reader.SetData( "AddPowerLV"			, &Pt->GameData.NPC.AddPowerLV			, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address  );

		Reader.SetData( "LuaEvent_OnAttackMagic", &Pt->GameData.NPC.LuaEvent_OnAttackMagic		, ENUM_Type_CharString		, 0 , ENUM_Indirect_Address );        
		Reader.SetData( "LuaEvent_OnAssistMagic", &Pt->GameData.NPC.LuaEvent_OnAssistMagic		, ENUM_Type_CharString		, 0 , ENUM_Indirect_Address );        
		Reader.SetData( "LuaEvent_OnDead"		, &Pt->GameData.NPC.LuaEvent_OnDead				, ENUM_Type_CharString		, 0 , ENUM_Indirect_Address );        
		Reader.SetData( "LuaEvent_OnKill"		, &Pt->GameData.NPC.LuaEvent_OnKill				, ENUM_Type_CharString		, 0 , ENUM_Indirect_Address );        
		Reader.SetData( "LuaEvent_BeginAttack"	, &Pt->GameData.NPC.LuaEvent_BeginAttack		, ENUM_Type_CharString		, 0 , ENUM_Indirect_Address );        
		Reader.SetData( "LuaEvent_EndAttack"	, &Pt->GameData.NPC.LuaEvent_EndAttack			, ENUM_Type_CharString		, 0 , ENUM_Indirect_Address );        
//		Reader.SetData( "IsShowMaster"			, &Pt->GameData.NPC.IsShowMaster				, ENUM_Type_BitPoint    , 0 , ENUM_Indirect_Address );  
		Reader.SetData( "SpecialDropItemType"	, &Pt->GameData.NPC.SpecialDropItemType			, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address  );
		Reader.SetData( "MinAbilityLv"			, &Pt->GameData.NPC.MinAbilityLv				, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address  );
		Reader.SetData( "NpcMode"				, &Pt->GameData.NPC._NpcMode					, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address  );

		Reader.SetData( "szLuaDisplayScript"	, &Pt->GameData.NPC.szLuaDisplayScript			, ENUM_Type_CharString		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "CarryType"				, &Pt->GameData.NPC.CarryType					, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address  );
		Reader.SetData( "CarryCount"			, &Pt->GameData.NPC.CarryCount					, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address  );
		Reader.SetData( "SearchGroupID"			, &Pt->GameData.NPC.SearchGroupID				, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address  );

		Reader.SetData( "CarryLuaScript"		, &Pt->GameData.NPC.CarryLuaScript				, ENUM_Type_CharString		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "CarryShootRange"		, &Pt->GameData.NPC.CarryShootRange				, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address  );
		Reader.SetData( "CarryShootAngle"		, &Pt->GameData.NPC.CarryShootAngle				, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address  );
		Reader.SetData( "CheckCarryLuaScript"	, &Pt->GameData.NPC.CheckCarryLuaScript			, ENUM_Type_CharString		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "CheckCarryLuaPoint"	, &Pt->GameData.NPC.CheckCarryLuaPoint			, ENUM_Type_CharString		, 0 , ENUM_Indirect_Address );

	}

	return &Reader;
}
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_Player( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0									, ENUM_Indirect_Address	, Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , sizeof( Pt->LastModifyDate )		, ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , sizeof( Pt->LastModifyAccount )	, ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , sizeof( Pt->DataGroup )			, ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , sizeof( Pt->LockAccount )			, ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0									, ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0									, ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , sizeof( Pt->GameData.Name )		, ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0									, ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , sizeof( Pt->GameData.Note )		, ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , sizeof( Pt->GameData.ShortNote )  , ENUM_Indirect_Address );        
	}

	return &Reader;
}
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_QuestDetail( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char    Buf[256];
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );       

		Reader.SetData( "iQuest_Catalog"	, &Pt->GameData.QuestDetail.iQuest_Catalog     , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       

		Reader.SetData( "iQuest_Type"		, &Pt->GameData.QuestDetail.iQuest_Type			, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       

		Reader.SetData( "iCheck_Class_Type"	, &Pt->GameData.QuestDetail.iCheck_Class_Type	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iCheck_Class1"		, &Pt->GameData.QuestDetail.iCheck_Class1       , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iCheck_Class2"		, &Pt->GameData.QuestDetail.iCheck_Class2		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iCheck_LV"			, &Pt->GameData.QuestDetail.iCheck_LV			, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iCheck_LowerLV"	, &Pt->GameData.QuestDetail.iCheck_LowerLV      , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iCheck_HigherLV"	, &Pt->GameData.QuestDetail.iCheck_HigherLV		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iCheck_Title"		, &Pt->GameData.QuestDetail.iCheck_Title		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iCheck_Group"		, &Pt->GameData.QuestDetail.iCheck_Group		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		//Reader.SetData( "iCheck_Time"		, &Pt->GameData.QuestDetail.iCheck_Time			, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "iCheck_Sex"		, &Pt->GameData.QuestDetail.iCheck_Sex			, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		
		Reader.SetData( "iCheck_RepGroup"	, &Pt->GameData.QuestDetail.iCheck_RepGroup		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "iCheck_Rep"		, &Pt->GameData.QuestDetail.iCheck_Rep			, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       

		Reader.SetData( "iCheck_Flag1"		, &Pt->GameData.QuestDetail.iCheck_Flag[0]		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iCheck_Flag2"		, &Pt->GameData.QuestDetail.iCheck_Flag[1]		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iCheck_Flag3"		, &Pt->GameData.QuestDetail.iCheck_Flag[2]      , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       

		Reader.SetData( "iCheck_ObjID1"		, &Pt->GameData.QuestDetail.iCheck_ObjID[0]   , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iCheck_ObjID2"		, &Pt->GameData.QuestDetail.iCheck_ObjID[1]   , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iCheck_ObjID3"		, &Pt->GameData.QuestDetail.iCheck_ObjID[2]   , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iCheck_ObjID4"		, &Pt->GameData.QuestDetail.iCheck_ObjID[3]   , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iCheck_ObjID5"		, &Pt->GameData.QuestDetail.iCheck_ObjID[4]   , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       

		Reader.SetData( "iCheck_ObjVal1"	, &Pt->GameData.QuestDetail.iCheck_ObjVal[0]  , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iCheck_ObjVal2"	, &Pt->GameData.QuestDetail.iCheck_ObjVal[1]  , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iCheck_ObjVal3"	, &Pt->GameData.QuestDetail.iCheck_ObjVal[2]  , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iCheck_ObjVal4"	, &Pt->GameData.QuestDetail.iCheck_ObjVal[3]  , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iCheck_ObjVal5"	, &Pt->GameData.QuestDetail.iCheck_ObjVal[4]  , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       

		Reader.SetData( "iCheck_Loop"		, &Pt->GameData.QuestDetail.iCheck_Loop			, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "bDisableTeam"		, &Pt->GameData.QuestDetail.bDisableTeam		, ENUM_Type_BitPoint      , 0 , ENUM_Indirect_Address );
		



		Reader.SetData( "iAccept_FlagOn1"	, &Pt->GameData.QuestDetail.iAccept_FlagOn[0]   , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iAccept_FlagOn2"	, &Pt->GameData.QuestDetail.iAccept_FlagOn[1]   , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iAccept_FlagOn3"	, &Pt->GameData.QuestDetail.iAccept_FlagOn[2]   , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iAccept_FlagOff1"	, &Pt->GameData.QuestDetail.iAccept_FlagOff[0]  , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iAccept_FlagOff2"	, &Pt->GameData.QuestDetail.iAccept_FlagOff[1]  , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iAccept_FlagOff3"	, &Pt->GameData.QuestDetail.iAccept_FlagOff[2]  , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "iAccept_ItemID1"	, &Pt->GameData.QuestDetail.iAccept_ItemID[0]   , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iAccept_ItemID2"	, &Pt->GameData.QuestDetail.iAccept_ItemID[1]   , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iAccept_ItemID3"	, &Pt->GameData.QuestDetail.iAccept_ItemID[2]   , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iAccept_ItemID4"	, &Pt->GameData.QuestDetail.iAccept_ItemID[3]   , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iAccept_ItemID5"	, &Pt->GameData.QuestDetail.iAccept_ItemID[4]   , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       

		Reader.SetData( "iAccept_ItemVal1"	, &Pt->GameData.QuestDetail.iAccept_ItemVal[0]  , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iAccept_ItemVal2"	, &Pt->GameData.QuestDetail.iAccept_ItemVal[1]  , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iAccept_ItemVal3"	, &Pt->GameData.QuestDetail.iAccept_ItemVal[2]  , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iAccept_ItemVal4"	, &Pt->GameData.QuestDetail.iAccept_ItemVal[3]  , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iAccept_ItemVal5"	, &Pt->GameData.QuestDetail.iAccept_ItemVal[4]  , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       



		Reader.SetData( "iRequest_CoinType"	, &Pt->GameData.QuestDetail.iRequest_CoinType	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iRequest_SpecialCoin", &Pt->GameData.QuestDetail.iRequest_SpecialCoin, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       

		Reader.SetData( "iRequest_Timer"	, &Pt->GameData.QuestDetail.iRequest_Timer		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iRequest_Money"	, &Pt->GameData.QuestDetail.iRequest_Money		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       

		Reader.SetData( "iRequest_QuestID"	, &Pt->GameData.QuestDetail.iRequest_QuestID	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       

		Reader.SetData( "iReward_Money"		, &Pt->GameData.QuestDetail.iReward_Money		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_Exp"		, &Pt->GameData.QuestDetail.iReward_Exp			, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_Honor"		, &Pt->GameData.QuestDetail.iReward_Honor		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_TP"		, &Pt->GameData.QuestDetail.iReward_TP			, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_CoinType"	, &Pt->GameData.QuestDetail.iReward_CoinType	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_SpecialCoin", &Pt->GameData.QuestDetail.iReward_SpecialCoin, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
				
		
		Reader.SetData( "iReward_Rep1"			, &Pt->GameData.QuestDetail.iReward_Rep[0]				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_Rep2"			, &Pt->GameData.QuestDetail.iReward_Rep[1]				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_RepGroup1"		, &Pt->GameData.QuestDetail.iReward_RepGroup[0]			, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_RepGroup2"		, &Pt->GameData.QuestDetail.iReward_RepGroup[1]			, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       

		Reader.SetData( "iReward_ItemID1"		, &Pt->GameData.QuestDetail.iReward_ItemID[0]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "iReward_ItemID2"		, &Pt->GameData.QuestDetail.iReward_ItemID[1]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_ItemID3"		, &Pt->GameData.QuestDetail.iReward_ItemID[2]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_ItemID4"		, &Pt->GameData.QuestDetail.iReward_ItemID[3]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_ItemID5"		, &Pt->GameData.QuestDetail.iReward_ItemID[4]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       

		Reader.SetData( "iReward_ItemVal1"		, &Pt->GameData.QuestDetail.iReward_ItemVal[0]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "iReward_ItemVal2"		, &Pt->GameData.QuestDetail.iReward_ItemVal[1]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_ItemVal3"		, &Pt->GameData.QuestDetail.iReward_ItemVal[2]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_ItemVal4"		, &Pt->GameData.QuestDetail.iReward_ItemVal[3]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_ItemVal5"		, &Pt->GameData.QuestDetail.iReward_ItemVal[4]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       

		Reader.SetData( "iReward_ChoiceID1"		, &Pt->GameData.QuestDetail.iReward_ChoiceID[0]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "iReward_ChoiceID2"		, &Pt->GameData.QuestDetail.iReward_ChoiceID[1]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_ChoiceID3"		, &Pt->GameData.QuestDetail.iReward_ChoiceID[2]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_ChoiceID4"		, &Pt->GameData.QuestDetail.iReward_ChoiceID[3]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_ChoiceID5"		, &Pt->GameData.QuestDetail.iReward_ChoiceID[4]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       

		Reader.SetData( "iReward_ChoiceVal1"	, &Pt->GameData.QuestDetail.iReward_ChoiceVal[0]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "iReward_ChoiceVal2"	, &Pt->GameData.QuestDetail.iReward_ChoiceVal[1]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_ChoiceVal3"	, &Pt->GameData.QuestDetail.iReward_ChoiceVal[2]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_ChoiceVal4"	, &Pt->GameData.QuestDetail.iReward_ChoiceVal[3]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_ChoiceVal5"	, &Pt->GameData.QuestDetail.iReward_ChoiceVal[4]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       

		Reader.SetData( "iReward_Spell1"		, &Pt->GameData.QuestDetail.iReward_Spell[0]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "iReward_Spell2"		, &Pt->GameData.QuestDetail.iReward_Spell[1]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_Spell3"		, &Pt->GameData.QuestDetail.iReward_Spell[2]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_Spell4"		, &Pt->GameData.QuestDetail.iReward_Spell[3]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iReward_Spell5"		, &Pt->GameData.QuestDetail.iReward_Spell[4]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       

		Reader.SetData( "iComplete_ShowQuest"	, &Pt->GameData.QuestDetail.iComplete_ShowQuest		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "iComplete_FlagOn1"		, &Pt->GameData.QuestDetail.iComplete_FlagOn[0]		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iComplete_FlagOn2"		, &Pt->GameData.QuestDetail.iComplete_FlagOn[1]		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iComplete_FlagOn3"		, &Pt->GameData.QuestDetail.iComplete_FlagOn[2]		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iComplete_FlagOff1"	, &Pt->GameData.QuestDetail.iComplete_FlagOff[0]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iComplete_FlagOff2"	, &Pt->GameData.QuestDetail.iComplete_FlagOff[1]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "iComplete_FlagOff3"	, &Pt->GameData.QuestDetail.iComplete_FlagOff[2]	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		

		Reader.SetData( "szQuest_Desc"			, &Pt->GameData.QuestDetail.szQuest_Desc			, ENUM_Type_CharStringPoint      , 0 , ENUM_Indirect_Address );       

		Reader.SetData( "szQuest_Accept_Detail"		, &Pt->GameData.QuestDetail.szQuest_Accept_Detail			, ENUM_Type_CharStringPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "szQuest_UnComplete_Detail"	, &Pt->GameData.QuestDetail.szQuest_UnComplete_Detail		, ENUM_Type_CharStringPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "szQuest_Complete_Detail"	, &Pt->GameData.QuestDetail.szQuest_Complete_Detail			, ENUM_Type_CharStringPoint      , 0 , ENUM_Indirect_Address );





		Reader.SetData( "szScript_OnBegin"			, &Pt->GameData.QuestDetail.szScript_OnBegin		, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );       
		Reader.SetData( "szScript_OnAccept"			, &Pt->GameData.QuestDetail.szScript_OnAccept		, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "szScript_OnComplete"		, &Pt->GameData.QuestDetail.szScript_OnComplete		, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "szScript_OnDelete"			, &Pt->GameData.QuestDetail.szScript_OnDelete		, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "szScript_OnClickObjBegin"	, &Pt->GameData.QuestDetail.szScript_OnClickObjBegin, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "szScript_OnClickObjEnd"	, &Pt->GameData.QuestDetail.szScript_OnClickObjEnd	, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "szScript_RequestString"	, &Pt->GameData.QuestDetail.szScript_RequestString		, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "iQuestGroup"				, &Pt->GameData.QuestDetail.iQuestGroup				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "iControlType"				, &Pt->GameData.QuestDetail.iControlType			, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "iQuestGroupLV"				, &Pt->GameData.QuestDetail.iQuestGroupLV			, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );

		for( int i = 0 ; i < _MAX_SIZE_QUEST_CONDITION ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) ,"iRequest_ItemID%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.QuestDetail.iRequest_ItemID[i]   , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );

			sprintf_s( Buf , sizeof(Buf) ,"iRequest_ItemVal%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.QuestDetail.iRequest_ItemVal[i]   , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );

			sprintf_s( Buf , sizeof(Buf) ,"iRequest_ItemStr%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.QuestDetail.iRequest_ItemStr[i]   , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );

		}

		for( int i = 0 ; i < 10 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) ,"iProcess_ClickToGetItem_ObjID%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.QuestDetail.iProcess_ClickToGetItem_ObjID[i]  , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );

			sprintf_s( Buf , sizeof(Buf) ,"iProcess_ClickToGetItem_ProcPercent%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.QuestDetail.iProcess_ClickToGetItem_ProcPercent[i]   , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );

			sprintf_s( Buf , sizeof(Buf) ,"iProcess_ClickToGetItem_GetItem%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.QuestDetail.iProcess_ClickToGetItem_GetItem[i]   , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );

			sprintf_s( Buf , sizeof(Buf) ,"iProcess_ClickToGetItem_GetItemVal%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.QuestDetail.iProcess_ClickToGetItem_GetItemVal[i]   , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		}

		for( int i = 0 ; i < 10 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) ,"iProcess_KilltoGetItem_ObjID%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.QuestDetail.iProcess_KilltoGetItem_ObjID[i]   , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );

			sprintf_s( Buf , sizeof(Buf) ,"iProcess_KilltoGetItem_ProcPercent%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.QuestDetail.iProcess_KilltoGetItem_ProcPercent[i]   , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );

			sprintf_s( Buf , sizeof(Buf) ,"iProcess_KilltoGetItem_GetItem%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.QuestDetail.iProcess_KilltoGetItem_GetItem[i]   , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );

			sprintf_s( Buf , sizeof(Buf) ,"iProcess_KilltoGetItem_GetItemVal%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.QuestDetail.iProcess_KilltoGetItem_GetItemVal[i]   , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		}


		for( int i = 0 ; i < 5 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) ,"iRequest_KillID%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.QuestDetail.iRequest_KillID[i]   , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );

			sprintf_s( Buf , sizeof(Buf) ,"iRequest_KillVal%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.QuestDetail.iRequest_KillVal[i]   , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );

			sprintf_s( Buf , sizeof(Buf) ,"iRequest_KillStr%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.QuestDetail.iRequest_KillStr[i]   , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		}


		for( int i=0; i < _MAX_SIZE_QUEST_ITEM; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) ,"iDeleteQuestItem%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.QuestDetail.iDeleteQuestItem[i]   , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );

			sprintf_s( Buf , sizeof(Buf) ,"iDeleteQuestItemCount%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.QuestDetail.iDeleteQuestItemCount[i]   , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		}

		for( int i=0; i < _MAX_SIZE_QUEST_ITEM; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) ,"iQuestLinkNPC%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.QuestDetail.iQuestLinkNPC[i]   , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		}

		for( int i=0; i < _MAX_SIZE_QUEST_ITEM; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) ,"iCheck_ObjStatus%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.QuestDetail.iCheck_ObjStatus[i]   , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		}

	}

	return &Reader;
}
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_QuestNPC( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Zone1"             , &Pt->Zone[0]                  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Zone2"             , &Pt->Zone[1]                  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Zone3"             , &Pt->Zone[2]                  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		Reader.SetData( "szQuestNpcText"    , &Pt->GameData.NPC.szQuestNpcText		, ENUM_Type_CharStringPoint      , 0 , ENUM_Indirect_Address );        
		Reader.SetData( "szQuestDoingText"  , &Pt->GameData.NPC.szQuestDoingText	, ENUM_Type_CharStringPoint		, 0 , ENUM_Indirect_Address );        
		Reader.SetData( "szLuaScript"		, &Pt->GameData.NPC.szLuaScript			, ENUM_Type_CharString		, 0 , ENUM_Indirect_Address );        

		Reader.SetData( "iQuestID1"			, &Pt->GameData.NPC.iQuestID[0]			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );     
		Reader.SetData( "iQuestID2"			, &Pt->GameData.NPC.iQuestID[1]			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );     
		Reader.SetData( "iQuestID3"			, &Pt->GameData.NPC.iQuestID[2]			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );     
		Reader.SetData( "iQuestID4"			, &Pt->GameData.NPC.iQuestID[3]			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );     
		Reader.SetData( "iQuestID5"			, &Pt->GameData.NPC.iQuestID[4]			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );     
		Reader.SetData( "iQuestID6"			, &Pt->GameData.NPC.iQuestID[5]			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );     
		Reader.SetData( "iQuestID7"			, &Pt->GameData.NPC.iQuestID[6]			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );     
		Reader.SetData( "iQuestID8"			, &Pt->GameData.NPC.iQuestID[7]			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );     
		Reader.SetData( "iQuestID9"			, &Pt->GameData.NPC.iQuestID[8]			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );     
		Reader.SetData( "iQuestID10"		, &Pt->GameData.NPC.iQuestID[9]			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );     
		Reader.SetData( "iQuestID11"		, &Pt->GameData.NPC.iQuestID[10]		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );     
		Reader.SetData( "iQuestID12"		, &Pt->GameData.NPC.iQuestID[11]		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );     
		Reader.SetData( "iQuestID13"		, &Pt->GameData.NPC.iQuestID[12]		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );     
		Reader.SetData( "iQuestID14"		, &Pt->GameData.NPC.iQuestID[13]		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );     
		Reader.SetData( "iQuestID15"		, &Pt->GameData.NPC.iQuestID[14]		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );     
		Reader.SetData( "iQuestID16"		, &Pt->GameData.NPC.iQuestID[15]		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );     
		Reader.SetData( "iQuestID17"		, &Pt->GameData.NPC.iQuestID[16]		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );     
		Reader.SetData( "iQuestID18"		, &Pt->GameData.NPC.iQuestID[17]		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );     
		Reader.SetData( "iQuestID19"		, &Pt->GameData.NPC.iQuestID[18]		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );     
		Reader.SetData( "iQuestID20"		, &Pt->GameData.NPC.iQuestID[19]		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );    

		Reader.SetData( "iQuestMode"		, &Pt->GameData.NPC.iQuestMode			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );        
		Reader.SetData( "ReviveTime"        , &Pt->GameData.ReviveTime				, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "MainHandEq1"		, &Pt->GameData.NPC.MainHandEQ[0]		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );    
		Reader.SetData( "SecHandEq1"		, &Pt->GameData.NPC.SecHandEQ[0]		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address ); 

		Reader.SetData( "iQuestNPCRefID"	, &Pt->GameData.NPC.iQuestNPCRefID		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address ); 
		Reader.SetData( "iQuestObjType"		, &Pt->GameData.NPC.iQuestObjType		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "TitleName"			, &Pt->GameData.NPC.TitleName			, ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );

		Reader.SetData( "QuestObjCraftMode"	, &Pt->GameData.NPC.QuestObjCraftMode	, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address ); 

		Reader.SetData( "ZoneID"			, &Pt->GameData.NPC.ZoneID				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "X"					, &Pt->GameData.NPC.X					, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Y"					, &Pt->GameData.NPC.Y					, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Z"					, &Pt->GameData.NPC.Z					, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		//Reader.SetData( "IsAllZoneVisible"	, &Pt->GameData.NPC.IsAllZoneVisible	, ENUM_Type_BitPoint    	, 0 , ENUM_Indirect_Address );        
		//Reader.SetData( "IsShowNpcPos"		, &Pt->GameData.NPC.IsShowNpcPos		, ENUM_Type_BitPoint    	, 0 , ENUM_Indirect_Address );        
		//Reader.SetData( "AutoRotate"		, &Pt->GameData.NPC.AutoRotate			, ENUM_Type_BitPoint		, 0 , ENUM_Indirect_Address );        
		Reader.SetData( "ZoneID_Bk"			, &Pt->GameData.NPC.ZoneID_Bk			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address  );
		Reader.SetData( "CampID"			, &Pt->GameData.NPC.CampID				, ENUM_Type_IntPoint       	, 0 , ENUM_Indirect_Address );
		Reader.SetData( "szLuaInitScript"	, &Pt->GameData.NPC.szLuaInitScript		, ENUM_Type_CharString		, 0 , ENUM_Indirect_Address );        
		Reader.SetData( "OtherFlag"			, &Pt->GameData.NPC.OtherFlag			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );        
		Reader.SetData( "NpcMode"			, &Pt->GameData.NPC._NpcMode			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address  );
		Reader.SetData( "szLuaDisplayScript", &Pt->GameData.NPC.szLuaDisplayScript	, ENUM_Type_CharString		, 0 , ENUM_Indirect_Address );        
		Reader.SetData( "OrnamentEQ"		, &Pt->GameData.NPC.OrnamentEQ			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SearchGroupID"		, &Pt->GameData.NPC.SearchGroupID		, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address  );
	}


	return &Reader;
}
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_Recipe( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;



	if( IsInit == false )
	{
		char    Buf[256];
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0, ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0, ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0, ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0, ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0, ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0, ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0, ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0, ENUM_Indirect_Address );        
		Reader.SetData( "Rare"				, &Pt->GameData.Rare			, ENUM_Type_IntPoint		, 0, ENUM_Indirect_Address );        
		//---------------------------------------------------------------------------------------------------------------------------------------------
		for( int i = 0 ; i < 8 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) ,"Source%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.Recipe.Source[i].OrgObjID   , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) ,"SourceCount%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.Recipe.Source[i].Count      , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) ,"SourceReduce%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.Recipe.Source[i].Rate       , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		}

		Reader.SetData( "Item1_Normal"      , &Pt->GameData.Recipe.Item1_Normal.OrgObjID    , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "Item1_NormalCount" , &Pt->GameData.Recipe.Item1_Normal.Count       , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "Item1_NormalRate"  , &Pt->GameData.Recipe.Item1_Normal.Rate        , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );

		Reader.SetData( "Item1_HQ"      , &Pt->GameData.Recipe.Item1_HQ.OrgObjID    , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "Item1_HQCount" , &Pt->GameData.Recipe.Item1_HQ.Count       , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "Item1_HQRate"  , &Pt->GameData.Recipe.Item1_HQ.Rate        , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );

		Reader.SetData( "Item1_Slot1"      , &Pt->GameData.Recipe.Item1_Slot1.OrgObjID    , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "Item1_Slot1Count" , &Pt->GameData.Recipe.Item1_Slot1.Count       , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "Item1_Slot1Rate"  , &Pt->GameData.Recipe.Item1_Slot1.Rate        , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );

		Reader.SetData( "Item1_Slot2"      , &Pt->GameData.Recipe.Item1_Slot2.OrgObjID    , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "Item1_Slot2Count" , &Pt->GameData.Recipe.Item1_Slot2.Count       , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "Item1_Slot2Rate"  , &Pt->GameData.Recipe.Item1_Slot2.Rate        , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );

		Reader.SetData( "Item1_Slot3"      , &Pt->GameData.Recipe.Item1_Slot3.OrgObjID    , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "Item1_Slot3Count" , &Pt->GameData.Recipe.Item1_Slot3.Count       , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "Item1_Slot3Rate"  , &Pt->GameData.Recipe.Item1_Slot3.Rate        , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );

		Reader.SetData( "Item1_Slot4"      , &Pt->GameData.Recipe.Item1_Slot4.OrgObjID    , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "Item1_Slot4Count" , &Pt->GameData.Recipe.Item1_Slot4.Count       , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "Item1_Slot4Rate"  , &Pt->GameData.Recipe.Item1_Slot4.Rate        , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		//---------------------------------------------------------------------------------------------------------------------------------------------
		Reader.SetData( "Item2"            , &Pt->GameData.Recipe.Item2.OrgObjID          , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "Item2_Count"      , &Pt->GameData.Recipe.Item2.Count             , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "Item2_Rate"       , &Pt->GameData.Recipe.Item2.Rate              , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );

		Reader.SetData( "Item3"            , &Pt->GameData.Recipe.Item3.OrgObjID          , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "Item3_Count"      , &Pt->GameData.Recipe.Item3.Count             , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "Item3_Rate"       , &Pt->GameData.Recipe.Item3.Rate              , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );

		Reader.SetData( "Item4"            , &Pt->GameData.Recipe.Item4.OrgObjID          , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "Item4_Count"      , &Pt->GameData.Recipe.Item4.Count             , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "Item4_Rate"       , &Pt->GameData.Recipe.Item4.Rate              , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );

		//---------------------------------------------------------------------------------------------------------------------------------------------
		//需求設定
		Reader.SetData( "RequestSkill"     , &Pt->GameData.Recipe.Request.Skill           , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "RequestSkillLV"   , &Pt->GameData.Recipe.Request.SkillLV         , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "RequestKeyItemID" , &Pt->GameData.Recipe.Request.KeyItemID       , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );

		//-------------------------------------------------------------------------------------------------------------------------------------------
		Reader.SetData( "Coldown"		   , &Pt->GameData.Recipe.Coldown				  , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "Type"			   , &Pt->GameData.Recipe.Type					  , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "RequestCraftObjType", &Pt->GameData.Recipe.RequestCraftObjType	  , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "ExpRate"          , &Pt->GameData.Recipe.ExpRate				  , ENUM_Type_FloatPoint      , 0, ENUM_Indirect_Address );
		
		Reader.SetData( "Cost"			   , &Pt->GameData.Cost							  , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
//		Reader.SetData( "PricesType"       , &Pt->GameData.PricesType					  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SellType"		   , &Pt->GameData.SellType						  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );


		Reader.SetData( "Mode"             , &Pt->GameData.Mode._Mode					  , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );

		Reader.SetData( "LearnFee"         , &Pt->GameData.Recipe.LearnFee				  , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		Reader.SetData( "CraftFee"         , &Pt->GameData.Recipe.CraftFee				  , ENUM_Type_IntPoint        , 0, ENUM_Indirect_Address );
		
	}

	return &Reader;
}
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_Rune( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;    

	if( IsInit == false )
	{
		char    Buf[256];
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );        
		Reader.SetData( "Rare"              , &Pt->GameData.Rare            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
        Reader.SetData( "MaxHeap"           , &Pt->GameData.MaxHeap         , ENUM_Type_IntPoint        , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		Reader.SetData( "DisappearRate"     , &Pt->GameData.Item.DisappearRate   , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DissolutionRate"   , &Pt->GameData.Item.DissolutionRate , ENUM_Type_FloatPoint		 , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Type"              , &Pt->GameData.Item.RuneType        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
//		Reader.SetData( "ColorType"         , &Pt->GameData.Item.ColorType       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Level"             , &Pt->GameData.Item.Level			 , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Volume"            , &Pt->GameData.Item.Volume			 , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "RuneGroup"         , &Pt->GameData.Item.RuneGroup		 , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "AddOnPos_ArmorPos"    , &Pt->GameData.Item.AddPos._ArmorPos       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "AddOnPos_ArmorType"   , &Pt->GameData.Item.AddPos._ArmorType      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "AddOnPos_WeaponType"  , &Pt->GameData.Item.AddPos._WeaponType     , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "AddOnPos_WeaponPos"   , &Pt->GameData.Item.AddPos.WeaponPosEnum   , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "AddOnPos_Other"       , &Pt->GameData.Item.AddPos._Other          , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );


		for( int i = 0 ; i < Max_WearEqType_Count ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "EqType%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.Item.Ability.EqType[i]      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "EqTypeValue%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.Item.Ability.EqTypeValue[i]  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		}
		Reader.SetData( "EqTypeOnAttackMagicID"   , &Pt->GameData.Item.Ability.OnAttackMagicID		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqTypeOnAttackMagicRank" , &Pt->GameData.Item.Ability.OnAttackMagicRank	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqTypeOnAttackMagicRate" , &Pt->GameData.Item.Ability.OnAttackMagicRate	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );        

		Reader.SetData( "ReferenceLv"		, &Pt->GameData.Item.ReferenceLv		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );        		
		Reader.SetData( "IsStandardCost"	, &Pt->GameData.Item.IsStandardCost		, ENUM_Type_BitPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "Cost"              , &Pt->GameData.Cost            		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PricesType"        , &Pt->GameData.PricesType				, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SpecialMoneyCost"  , &Pt->GameData.SpecialMoneyCost		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "CardID"			, &Pt->GameData.Item.CardID				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "StarValue"			, &Pt->GameData.Item.StarValue			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "DrawOutCost"		, &Pt->GameData.Item.DrawOutCost		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		//------------------------------------------------------------------------------------
		Reader.SetData( "IsStandardAbility"	, &Pt->GameData.Item.IsStandardAbility	, ENUM_Type_BitPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "StandardAbility_Lv", &Pt->GameData.Item.StandardAbility_Lv	, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		for( int i = 0 ; i < 5 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "StandardAbility_Arg%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.Item.StandardAbility_Arg[i]      , ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );

			sprintf_s( Buf , sizeof(Buf) , "StandardAbility_ArgType%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.Item.StandardAbility_ArgType[i]  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}
		//------------------------------------------------------------------------------------

	}

	return &Reader;
}

ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_Card( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;    

	if( IsInit == false )
	{
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );        
		Reader.SetData( "Rare"              , &Pt->GameData.Rare            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		
		Reader.SetData( "CardOrgObjID"      , &Pt->GameData.Item.CardOrgObjID       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Cost"              , &Pt->GameData.Cost            		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
//		Reader.SetData( "PricesType"        , &Pt->GameData.PricesType				, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MaxHeap"           , &Pt->GameData.MaxHeap         		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ReferenceLv"		, &Pt->GameData.Item.ReferenceLv		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "IsStandardCost"	, &Pt->GameData.Item.IsStandardCost		, ENUM_Type_BitPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "CardPriorityID"	, &Pt->GameData.Item.CardPriorityID		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );

		Reader.SetData( "StarValue"			, &Pt->GameData.Attirbute.StarValue	    , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "CardAddpower"    			, &Pt->GameData.Item.CardAddpower				, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
	
	}

	return &Reader;
}

ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_PE( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;    

	if( IsInit == false )
	{
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		//------------------------------------------------------------------------------------
		Reader.SetData( "IsLock"            , &Pt->IsLock                   			, ENUM_Type_ShortPoint      , 0 ,	ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           			, ENUM_Type_TimeCharString  , 0 ,	ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        			, ENUM_Type_CharString      , 0 ,	ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        			, ENUM_Type_CharString      , 0 ,	ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              			, ENUM_Type_CharString      , 0 ,	ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            			, ENUM_Type_IntPoint        , 0 ,	ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet					, ENUM_Type_IntPoint        , 0 ,	ENUM_Indirect_Address );
		Reader.SetData( "GUID"				, &Pt->GameData.GUID						, ENUM_Type_IntPoint		, 0	,	ENUM_Indirect_Address , Def_Disabled_Update_Flag);
		Reader.SetData( "Name"				, &Pt->GameData.Name						, ENUM_Type_CharStringPoint	, 0	,	ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural					, ENUM_Type_CharStringPoint , 0 ,	ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID						, ENUM_Type_IntPoint        , 0 ,	ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note						, ENUM_Type_CharStringPoint , 0 ,	ENUM_Indirect_Address ); // as PE Description
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote					, ENUM_Type_CharStringPoint , 0 ,	ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		Reader.SetData( "ParentGUID"		, &Pt->GameData.PE.ParentGUID				, ENUM_Type_IntPoint		, 0	,	ENUM_Indirect_Address );
		Reader.SetData( "Type"				, &Pt->GameData.PE.Type						, ENUM_Type_IntPoint		, 0	,	ENUM_Indirect_Address );
		Reader.SetData( "Flag"				, &Pt->GameData.PE.Flag						, ENUM_Type_IntPoint		, 0	,	ENUM_Indirect_Address );
		Reader.SetData( "Data"				, &Pt->GameData.PE.Data						, ENUM_Type_BinaryData		, sizeof(Pt->GameData.PE.Data)	,	ENUM_Indirect_Address );
		Reader.SetData( "LuaEvent1"			, &Pt->GameData.PE.LuaEvent.All.LuaEvent1	, ENUM_Type_CharString		, 0	,	ENUM_Indirect_Address );
		Reader.SetData( "LuaEvent2"			, &Pt->GameData.PE.LuaEvent.All.LuaEvent2	, ENUM_Type_CharString		, 0	,	ENUM_Indirect_Address );
		Reader.SetData( "LuaEvent3"			, &Pt->GameData.PE.LuaEvent.All.LuaEvent3	, ENUM_Type_CharString		, 0	,	ENUM_Indirect_Address );
		Reader.SetData( "LuaEvent4"			, &Pt->GameData.PE.LuaEvent.All.LuaEvent4	, ENUM_Type_CharString		, 0	,	ENUM_Indirect_Address );
		Reader.SetData( "LuaEvent5"			, &Pt->GameData.PE.LuaEvent.All.LuaEvent5	, ENUM_Type_CharString		, 0	,	ENUM_Indirect_Address );
		Reader.SetData( "LuaEvent6"			, &Pt->GameData.PE.LuaEvent.All.LuaEvent6	, ENUM_Type_CharString		, 0	,	ENUM_Indirect_Address );
		Reader.SetData( "LuaEvent7"			, &Pt->GameData.PE.LuaEvent.All.LuaEvent7	, ENUM_Type_CharString		, 0	,	ENUM_Indirect_Address );
		Reader.SetData( "LuaEvent8"			, &Pt->GameData.PE.LuaEvent.All.LuaEvent8	, ENUM_Type_CharString		, 0	,	ENUM_Indirect_Address );
		Reader.SetData( "LuaEvent9"			, &Pt->GameData.PE.LuaEvent.All.LuaEvent9	, ENUM_Type_CharString		, 0	,	ENUM_Indirect_Address );
		Reader.SetData( "LuaEvent10"		, &Pt->GameData.PE.LuaEvent.All.LuaEvent10	, ENUM_Type_CharString		, 0	,	ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
	}

	return &Reader;
}
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_Phantom( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char	Buf[512];
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   		, ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , 1 );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           		, ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        		, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        		, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              		, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , 1 );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet				, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , 1 );
		Reader.SetData( "Name"              , &Pt->GameData.Name            		, ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural			    , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            		, ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       		, ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		Reader.SetData( "RankUpMaterial"			, &Pt->GameData.Phantom.RankUpMaterial			, ENUM_Type_IntPoint     	, 0 , ENUM_Indirect_Address );
		Reader.SetData( "LevelUpType"				, &Pt->GameData.Phantom.LevelUpType				, ENUM_Type_IntPoint     	, 0 , ENUM_Indirect_Address );

		for( int i = 0 ; i < 5 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "PhantomEqType%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.Phantom.abi_Phantom.EqType[i]			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "PhantomEqValue%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.Phantom.abi_Phantom.EqTypeValue[i]		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}

		//		Reader.SetData( "RuneSystemTableID"			, &Pt->GameData.Item.RuneSystemTableID			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
	}

	return &Reader;
}

ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_Script( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , 1 );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , 1 );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , 1 );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		Reader.SetData( "Type"              , &Pt->ScriptInfo.Type          , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "FuncName"          , &Pt->ScriptInfo.Name          , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "FuncArg"           , &Pt->ScriptInfo.Arg           , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Text"              , &Pt->ScriptInfo.Script        , ENUM_Type_TextData        , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
	}

	return &Reader;
}
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_Shop( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char    Buf[256];
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );        
		//---------------------------------------------------------------------------------------------------------------------------------------------

		Reader.SetData( "BuyRate"         , &Pt->GameData.Shop.BuyRate      , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );        
		Reader.SetData( "SellRate"        , &Pt->GameData.Shop.SellRate     , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );        
		Reader.SetData( "WeaponRepair"    , &Pt->GameData.Shop.WeaponRepair , ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );        

		for( int i = 0 ; i < 30 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) ,"SellItemID%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.Shop.SellItemID[ i ]      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) ,"SellItemMax%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.Shop.SellItemMax[ i ]     , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) ,"SellItemPorduce%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.Shop.SellItemPorduce[ i ] , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

			sprintf_s( Buf , sizeof(Buf) ,"SellCost1_%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.Shop.SellCost[ i ][0] , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) ,"SellCost2_%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.Shop.SellCost[ i ][1] , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

			sprintf_s( Buf , sizeof(Buf) ,"CostType1_%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.Shop.CostType[ i ][0] , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) ,"CostType2_%d", i+1  );
			Reader.SetData( Buf           , &Pt->GameData.Shop.CostType[ i ][1] , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}


		//---------------------------------------------------------------------------------------------------------------------------------------------
	}

	return &Reader;
}
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_Suit( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;  

	if( IsInit == false )
	{
		char    Buf[256];
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		Reader.SetData( "TotalCount"		, &Pt->GameData.Suit.TotalCount	, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address );
		for( int i = 0 ; i < 9 ; i++ )
			for( int j = 0 ; j < 3 ; j++ )
			{
				sprintf_s( Buf , sizeof(Buf) , "BaseType%d_%d" , i+1 , j+1 );
				Reader.SetData( Buf         , &Pt->GameData.Suit.SuitBase[i].EqType[j]		, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address );
				sprintf_s( Buf , sizeof(Buf) , "BaseTypeValue%d_%d" , i+1 , j+1 );
				Reader.SetData( Buf         , &Pt->GameData.Suit.SuitBase[i].EqTypeValue[j]	, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address );			
			}

			//------------------------------------------------------------------------------------

		for( int i = 0 ; i < 10 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "SuitList%d" , i+1 );
			Reader.SetData( Buf , &Pt->GameData.Suit.SuitList[i]	, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address );
		}

		for( int i = 0 ; i < 4 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "SuitISkillD%d" , i+1 );
			Reader.SetData( Buf , &Pt->GameData.Suit.SuitSkillID[i]	, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address );
		}

		Reader.SetData( "SuitSkillMoney"	, &Pt->GameData.Suit.SuitSkillMoney	, ENUM_Type_IntPoint	, 0 , ENUM_Indirect_Address );
	}

	return &Reader;
}
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_Title( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char Buf[256];
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );        
		Reader.SetData( "Mode"				, &Pt->GameData.Mode._Mode      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "Rare"		        , &Pt->GameData.Rare			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		//----------------------------------------------------------------------------------------------------------
		Reader.SetData( "Type"              , &Pt->GameData.Title.Type         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Famous"            , &Pt->GameData.Title.Famous       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MainJob"           , &Pt->GameData.Title.MainJob      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SubJob"            , &Pt->GameData.Title.SubJob       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MainJobLV"         , &Pt->GameData.Title.MainJobLV    , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SubJobLV"          , &Pt->GameData.Title.SubJobLV     , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//----------------------------------------------------------------------------------------------------------
		Reader.SetData( "KillCount_Type"           , &Pt->GameData.Title.KillCount.Type			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "KillCount_KillGroup"      , &Pt->GameData.Title.KillCount.KillGroupID	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "KillCount_Count"          , &Pt->GameData.Title.KillCount.Count		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//----------------------------------------------------------------------------------------------------------

		for( int i = 0 ; i < 5 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "EqType%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.Title.Ability.EqType[i]				, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "EqTypeValue%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.Title.Ability.EqTypeValue[i]		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}

		Reader.SetData( "TitleSysNote"       , &Pt->GameData.Title.TitleSysNote         , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		for( int i = 0 ; i < 5 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "ExEqType%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.Title.AbilityEx.EqType[i]				, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "ExEqTypeValue%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.Title.AbilityEx.EqTypeValue[i]		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}

		Reader.SetData( "EqTypeOnAttackMagicID"   , &Pt->GameData.Title.Ability.OnAttackMagicID		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqTypeOnAttackMagicRank" , &Pt->GameData.Title.Ability.OnAttackMagicRank	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqTypeOnAttackMagicRate" , &Pt->GameData.Title.Ability.OnAttackMagicRate	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );        
		Reader.SetData( "SkillID"				  , &Pt->GameData.Title.SkillID			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SkillLv"				  , &Pt->GameData.Title.SkillLv			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "Classify1"				  , &Pt->GameData.Title.Classify[0]     , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Classify2"				  , &Pt->GameData.Title.Classify[1]     , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LuaEvent"				  , &Pt->GameData.Title.LuaEvent		, ENUM_Type_CharString		, 0 , ENUM_Indirect_Address );        
		Reader.SetData( "TitleSysLuaEvent"		  , &Pt->GameData.Title.TitleSysLuaEvent, ENUM_Type_CharString		, 0 , ENUM_Indirect_Address );        
	}

	return &Reader;
}
ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_Weapon( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char    Buf[256];
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , 1 );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , 1 );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , 1 );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MaxHeap"           , &Pt->GameData.MaxHeap			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		Reader.SetData( "LimitVoc"          , &Pt->GameData.Limit.Voc._Voc   , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitRace"         , &Pt->GameData.Limit.Race._Race , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitSex"          , &Pt->GameData.Limit.Sex._Sex   , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitLv"           , &Pt->GameData.Limit.Level      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitStr"          , &Pt->GameData.Limit.STR        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitSta"          , &Pt->GameData.Limit.STA        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitInt"          , &Pt->GameData.Limit.INT        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitMnd"          , &Pt->GameData.Limit.MND        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitAgi"          , &Pt->GameData.Limit.AGI        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		Reader.SetData( "Mode"              , &Pt->GameData.Mode._Mode          , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ItemType"          , &Pt->GameData.Item.ItemType       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GenerateRate"      , &Pt->GameData.GenerateRate        , ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MaxWorldCount"     , &Pt->GameData.MaxWorldCount       , ENUM_Type_FloatPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Rare"              , &Pt->GameData.Rare                , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Cost"              , &Pt->GameData.Cost                , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SpecialMoneyCost"  , &Pt->GameData.SpecialMoneyCost	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "PricesType"        , &Pt->GameData.PricesType			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SellType"			, &Pt->GameData.SellType			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "IncMagic_Onuse"    , &Pt->GameData.Item.IncMagic_Onuse , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DisappearRate"     , &Pt->GameData.Item.DisappearRate  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DissolutionRate"   , &Pt->GameData.Item.DissolutionRate, ENUM_Type_FloatPoint     	, 0 , ENUM_Indirect_Address );
		Reader.SetData( "SrcRecipe"         , &Pt->GameData.Item.SrcRecipe      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Durable"           , &Pt->GameData.Item.Durable        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "ManuFactureType"   , &Pt->GameData.Item.ManuFactureType, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ManuFactureLV"     , &Pt->GameData.Item.ManuFactureType, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "BuyUnit"			, &Pt->GameData.BuyUnit				, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "BodyMaxCount"		, &Pt->GameData.Item.BodyMaxCount	, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "SuitID"            , &Pt->GameData.Item.SuitID			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "AttackRange"       , &Pt->GameData.Item.AttackRange	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "AttackSpeed"       , &Pt->GameData.Item.AttackSpeed	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		//------------------------------------------------------------------------------------
		
		for( int i = 2 ; i < Max_WearEqType_Count  ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "EqType%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.Item.Ability.EqType[i]      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "EqTypeValue%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.Item.Ability.EqTypeValue[i]  , ENUM_Type_IntPoint       , 0 , ENUM_Indirect_Address );
		}
		
		for( int i = 0 ; i < _MAX_DROP_ABILITY_COUNT_ ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "DropAbility%d" , i + 1  );
			Reader.SetData( Buf            , &Pt->GameData.Item.DropItemAbility[i].OrgID       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "DropAbilityRate%d" , i + 1  );
			Reader.SetData( Buf            , &Pt->GameData.Item.DropItemAbility[i].Rate        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}

		Reader.SetData( "EqTypeOnAttackMagicID"   , &Pt->GameData.Item.Ability.OnAttackMagicID		, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqTypeOnAttackMagicRank" , &Pt->GameData.Item.Ability.OnAttackMagicRank	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "EqTypeOnAttackMagicRate" , &Pt->GameData.Item.Ability.OnAttackMagicRate	, ENUM_Type_IntPoint      , 0 , ENUM_Indirect_Address );        

		//------------------------------------------------------------------------------------
		Reader.SetData( "WeaponType"         , &Pt->GameData.Item.WeaponType         	, ENUM_Type_IntPoint      	, 0 , ENUM_Indirect_Address );
		Reader.SetData( "weaponPos"          , &Pt->GameData.Item.WeaponPos          	, ENUM_Type_IntPoint      	, 0 , ENUM_Indirect_Address );

		Reader.SetData( "HoleBase"           , &Pt->GameData.Item.HoleBase          	, ENUM_Type_IntPoint      	, 0 , ENUM_Indirect_Address );
		Reader.SetData( "HoleRange"          , &Pt->GameData.Item.HoleRange         	, ENUM_Type_IntPoint      	, 0 , ENUM_Indirect_Address );
//		Reader.SetData( "AddPowerOn"         , &Pt->GameData.Item.AddPowerOn        	, ENUM_Type_IntPoint      	, 0 , ENUM_Indirect_Address );
		Reader.SetData( "MaxAttrCount"      , &Pt->GameData.Item.MaxAttrCount		 	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "BaseAttrCount"			, &Pt->GameData.Item.BaseAttrCount     	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SelectBaseAttrCount"   , &Pt->GameData.Item.SelectBaseAttrCount, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
//		Reader.SetData( "StandardType"       , &Pt->GameData.Item.StandardType			, ENUM_Type_IntPoint      	, 0 , ENUM_Indirect_Address );

		Reader.SetData( "UseType"			, &Pt->GameData.Item.UseType				, ENUM_Type_IntPoint	  	, 0 , ENUM_Indirect_Address );
		Reader.SetData( "CliScript"         , &Pt->GameData.Item.CliScript  			, ENUM_Type_CharString    	, 0 , ENUM_Indirect_Address );
		Reader.SetData( "SrvScript"         , &Pt->GameData.Item.SrvScript  			, ENUM_Type_CharString    	, 0 , ENUM_Indirect_Address );
		Reader.SetData( "CheckUseScript"    , &Pt->GameData.Item.CheckUseScript			, ENUM_Type_CharString    	, 0 , ENUM_Indirect_Address );
		Reader.SetData( "LiveTimeType"		, &Pt->GameData.LiveTimeType				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "LiveTime"			, &Pt->GameData.LiveTime					, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "IsStandardCost"	, &Pt->GameData.Item.IsStandardCost			, ENUM_Type_BitPoint		, 0 , ENUM_Indirect_Address );
//		Reader.SetData( "IsNoTitle"			, &Pt->GameData.Item.IsNoTitle				, ENUM_Type_BitPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageEfficacyType"	, &Pt->GameData.Item.ImageEfficacyType		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "CardID"			, &Pt->GameData.Item.CardID					, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "IsFixDurable"      ,&Pt->GameData.Item.IsFixDurable			, ENUM_Type_BitPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "StarValue"			, &Pt->GameData.Item.StarValue				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "RuneLimetLv"		, &Pt->GameData.Item.RuneLimetLv			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "ItemUniqueType"	, &Pt->GameData.Item.ItemUniqueType			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "RefineTableID"		, &Pt->GameData.Item.RefineTableID			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );


		Reader.SetData( "DDmg"				, &Pt->GameData.Item.DDmg					, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "DMDmg"				, &Pt->GameData.Item.DMDmg					, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "BodyMaxCount"		, &Pt->GameData.Item.BodyMaxCount			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "RefineLv"			, &Pt->GameData.Item.RefineLv				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "AddPowerQuality"	, &Pt->GameData.Item.AddPowerQuality		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );

	}

	return &Reader;
}


ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_Camp( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char Buf[256];
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );        
		//----------------------------------------------------------------------------------------------------------
		//----------------------------------------------------------------------------------------------------------

		for( int i = 0 ; i < 15 ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "CampName%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.Camp.CampName[i]     , ENUM_Type_CharString        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "CampRelation%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.Camp.CampInfo[i]	 , ENUM_Type_CharString        , sizeof(Pt->GameData.Camp.CampInfo[i])-1, ENUM_Indirect_Address );

		}
	}

	return &Reader;
}

ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_Treasure( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char Buf[256];
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Cost"				, &Pt->GameData.Cost	        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
//		Reader.SetData( "PricesType"        , &Pt->GameData.PricesType      , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
//		Reader.SetData( "SellType"			, &Pt->GameData.SellType		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		//----------------------------------------------------------------------------------------------------------
		Reader.SetData( "NeedDLv"			, &Pt->GameData.Treasure.NeedDLv	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ItemCount"			, &Pt->GameData.Treasure.ItemCount	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		for( int i = 0 ; i < _MAX_TREASURE_COUNT_ ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "TreasureItem%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.Treasure.Item[i].OrgID		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "TreasureCount%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.Treasure.Item[i].Count		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "TreasureDropCount%d" , i + 1 );
			Reader.SetData( Buf     , &Pt->GameData.Treasure.Item[i].DropCount	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}
		Reader.SetData( "GambleCost"		, &Pt->GameData.Treasure.Gamble.Cost		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GambleHole1Rate"	, &Pt->GameData.Treasure.Gamble.HoleRate[0]	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GambleHole2Rate"	, &Pt->GameData.Treasure.Gamble.HoleRate[1]	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GambleHole3Rate"	, &Pt->GameData.Treasure.Gamble.HoleRate[2] , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GambleHole4Rate"	, &Pt->GameData.Treasure.Gamble.HoleRate[3]	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
//		Reader.SetData( "GambleAddPower"	, &Pt->GameData.Treasure.Gamble.AddPower    , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		for( int i = 0 ; i < _MAX_DROP_ABILITY_COUNT_ ; i++ )
		{
			sprintf_s( Buf , sizeof(Buf) , "GambleDropAbility%d" , i + 1  );
			Reader.SetData( Buf            , &Pt->GameData.Treasure.Gamble.DropItemAbility[i].OrgID       , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			sprintf_s( Buf , sizeof(Buf) , "GambleDropAbilityRate%d" , i + 1  );
			Reader.SetData( Buf            , &Pt->GameData.Treasure.Gamble.DropItemAbility[i].Rate        , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		}

		Reader.SetData( "LuaCheckScript"    , &Pt->GameData.Treasure.LuaCheckScript		, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );

	}

	return &Reader;
}

ReaderClass< DB_GameObjDbStruct >* GameObjDbStructEx::ObjReader_MagicCollect( )
{
	static ReaderClass< DB_GameObjDbStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char Buf[256];
		DB_GameObjDbStruct* Pt = 0;

		IsInit = true;

		ObjReader_InitBaseCommonObj( Pt, Reader );

		Reader.SetData( "IsLock"            , &Pt->IsLock                   , ENUM_Type_ShortPoint      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "LastModifyDate"    , &Pt->LastModifyDate           , ENUM_Type_TimeCharString  , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LastModifyAccount" , &Pt->LastModifyAccount        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DataGroup"			, &Pt->DataGroup		        , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LockAccount"       , &Pt->LockAccount              , ENUM_Type_CharString      , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "ProcRate"          , &Pt->ProcRate.Rate            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "OutputLanguage"    , &Pt->GameData.LanguageSet		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "GUID"              , &Pt->GameData.GUID            , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address , Def_Disabled_Update_Flag );
		Reader.SetData( "Name"              , &Pt->GameData.Name            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Name_Plural"       , &Pt->GameData.Name_Plural     , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ImageID"           , &Pt->GameData.ImageID         , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Note"              , &Pt->GameData.Note            , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShortNote"         , &Pt->GameData.ShortNote       , ENUM_Type_CharStringPoint , 0 , ENUM_Indirect_Address );        
		//----------------------------------------------------------------------------------------------------------
//		Reader.SetData( "MagicBase"         , &Pt->GameData.MagicCol.MagicBase  	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MagicLV"			, &Pt->GameData.MagicCol.MagicLV		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "EffectType"        , &Pt->GameData.MagicCol.EffectType		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "CostType"          , &Pt->GameData.MagicCol.Cost[0].Type  	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "CostValue"         , &Pt->GameData.MagicCol.Cost[0].Value 	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "CostType1"          , &Pt->GameData.MagicCol.Cost[1].Type 	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "CostValue1"         , &Pt->GameData.MagicCol.Cost[1].Value , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "NeedType1"         , &Pt->GameData.MagicCol.Need[0].Type  	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "NeedValue1"        , &Pt->GameData.MagicCol.Need[0].Value  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "NeedType2"         , &Pt->GameData.MagicCol.Need[1].Type  	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "NeedValue2"        , &Pt->GameData.MagicCol.Need[1].Value  , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "TargetType"        , &Pt->GameData.MagicCol.TargetType		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "AttackDistance"    , &Pt->GameData.MagicCol.AttackDistance , ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );

		Reader.SetData( "RangeType"			, &Pt->GameData.MagicCol.RangeType		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "EffectRange"		, &Pt->GameData.MagicCol.EffectRange	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "RangeSelectType"	, &Pt->GameData.MagicCol.RangeSelectType, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "EffectCount"		, &Pt->GameData.MagicCol.EffectCount	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "DecreaseArg"		, &Pt->GameData.MagicCol.DecreaseArg	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );


		Reader.SetData( "SpellTime"			, &Pt->GameData.MagicCol.SpellTime		, ENUM_Type_FloatPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "MagicAttackDelay"	, &Pt->GameData.MagicCol.MagicAttackDelay, ENUM_Type_FloatPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "SpellCount"		, &Pt->GameData.MagicCol.SpellCount		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "NextSpellTime"		, &Pt->GameData.MagicCol.NextSpellTime	, ENUM_Type_FloatPoint        , 0 , ENUM_Indirect_Address );
		//----------------------------------------------------------------------------------------------------------
		//命中率
		Reader.SetData( "HitRateFunc"			, &Pt->GameData.MagicCol.HitRateFunc		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "HitRateArg1"			, &Pt->GameData.MagicCol.HitRateArg[0]		, ENUM_Type_FloatPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "HitRateArg2"			, &Pt->GameData.MagicCol.HitRateArg[1]		, ENUM_Type_FloatPoint        , 0 , ENUM_Indirect_Address );

		//----------------------------------------------------------------------------------------------------------
		Reader.SetData( "ColdownClass"			, &Pt->GameData.MagicCol.Coldown.Class  		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ColdownType"			, &Pt->GameData.MagicCol.Coldown.Type			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ColdownTime"			, &Pt->GameData.MagicCol.Coldown.Time			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ColdownTimeAllMagic"	, &Pt->GameData.MagicCol.Coldown.TimeAllMagic  	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "Flag"					, &Pt->GameData.MagicCol.Flag._Type  			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
		Reader.SetData( "LuaScript"          	, &Pt->GameData.MagicCol.LUAScript				, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		//----------------------------------------------------------------------------------------------------------
		
		for( int i = 0 ; i < 3 ; i++ )
			for( int j = 0 ; j < 4 ; j++ )
			{
				int ID = i * 4 + j + 1;
//				sprintf( Buf , "MagicCheckFlag%d" , ID );
//				Reader.SetData( Buf     , &Pt->GameData.MagicCol.Magic[i][j].CheckFlag		, ENUM_Type_BitPoint        , 0 , ENUM_Indirect_Address );
				sprintf_s( Buf , sizeof(Buf) , "MagicBaseID%d" , ID );
				Reader.SetData( Buf     , &Pt->GameData.MagicCol.Magic[i][j].MagicBaseID	, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
				sprintf_s( Buf , sizeof(Buf) , "MagicCheckFuncType%d" , ID );
				Reader.SetData( Buf     , &Pt->GameData.MagicCol.Magic[i][j].FuncType		, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
				sprintf_s( Buf , sizeof(Buf) , "MagicCheckArg1%d" , ID );
				Reader.SetData( Buf     , &Pt->GameData.MagicCol.Magic[i][j].Arg[0]			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
				sprintf_s( Buf , sizeof(Buf) , "MagicCheckArg2%d" , ID );
				Reader.SetData( Buf     , &Pt->GameData.MagicCol.Magic[i][j].Arg[1]			, ENUM_Type_IntPoint        , 0 , ENUM_Indirect_Address );
			}

		//----------------------------------------------------------------------------------------------------------
		Reader.SetData( "MagicSpellGroupType", &Pt->GameData.MagicCol.MagicSpellGroupType	, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		//----------------------------------------------------------------------------------------------------------
		Reader.SetData( "CheckUseScript"    , &Pt->GameData.MagicCol.CheckUseScript			, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );

		Reader.SetData( "MaxSkillLv"		, &Pt->GameData.MagicCol.MaxSkillLv			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "ExpTableRate"		, &Pt->GameData.MagicCol.ExpTableRate		, ENUM_Type_FloatPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "IsMagicAttackDelay_TargetDist"	, &Pt->GameData.MagicCol.IsMagicAttackDelay_TargetDist 		, ENUM_Type_BitPoint      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ComboType"			, &Pt->GameData.MagicCol.ComboType			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "Mode"				, &Pt->GameData.MagicCol._Mode				, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "NextMagicID"		, &Pt->GameData.MagicCol.NextMagicID		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "PetSkillType"		, &Pt->GameData.MagicCol.PetSkillType		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "MoveDelayTime"		, &Pt->GameData.MagicCol.MoveDelayTime		, ENUM_Type_FloatPoint		, 0 , ENUM_Indirect_Address );

		Reader.SetData( "CliCollisionType"	, &Pt->GameData.MagicCol.CliCollisionType	, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "CliCollisionValue"	, &Pt->GameData.MagicCol.CliCollisionValue	, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "LimitLv"			, &Pt->GameData.MagicCol.LimitLv			, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "SelectTargetScript", &Pt->GameData.MagicCol.SelectTargetScript	, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "ShootTargetScript" , &Pt->GameData.MagicCol.ShootTargetScript	, ENUM_Type_CharString      , 0 , ENUM_Indirect_Address );
		Reader.SetData( "AddSoulPoint"		, &Pt->GameData.MagicCol.AddSoulPoint		, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
		Reader.SetData( "SuitPassiveSkill"	, &Pt->GameData.MagicCol.SuitPassiveSkill	, ENUM_Type_IntPoint		, 0 , ENUM_Indirect_Address );
	}


	return &Reader;
}

//---------------------------------------------------------------------------------------------------------------------
//檢查是否可以附加此能力在這物品上
bool	GameObjDbStructEx::CheckInherentAbility( AddonPosTypeStruct& Pos , bool CheckLv )
{
	if( CheckLv != false && Limit.Level >= Pos.Level )
		return false;

	if( IsArmor() )
	{
		bool IsNeedCheckType = false;
		switch( Item.ArmorPos )
		{
		case EM_ArmorPos_Head:         	//頭
			if( Pos.ArmorPos.Head == false )
				return false;
			IsNeedCheckType = true;
			break;
		case EM_ArmorPos_Gloves:	   	//手套
			if( Pos.ArmorPos.Gloves == false )
				return false;
			IsNeedCheckType = true;
			break;
		case EM_ArmorPos_Shoes:	       	//鞋子
			if( Pos.ArmorPos.Shoes == false )
				return false;
			IsNeedCheckType = true;
			break;
		case EM_ArmorPos_Clothes:	   	//上衣
			if( Pos.ArmorPos.Clothes == false )
				return false;
			IsNeedCheckType = true;
			break;
		case EM_ArmorPos_Pants:	       	//褲子
			if( Pos.ArmorPos.Pants == false )
				return false;
			IsNeedCheckType = true;
			break;
		case EM_ArmorPos_Back:	       	//背部
			if( Pos.Other.Back == false )
				return false;
			break;
		case EM_ArmorPos_Belt:	       	//腰帶
			if( Pos.ArmorPos.Belt == false )
				return false;
			IsNeedCheckType = true;
			break;
		case EM_ArmorPos_Shoulder:     	//肩甲
			if( Pos.ArmorPos.Shoulder == false )
				return false;
			IsNeedCheckType = true;
			break;
		case EM_ArmorPos_Necklace:     	//項鍊 
			if( Pos.Other.Necklace == false )
				return false;
			break;
		case EM_ArmorPos_Ring:         	//戒子
			if( Pos.Other.Ring == false )
				return false;
			break;
		case EM_ArmorPos_Earring:      	//耳飾
			if( Pos.Other.Earring == false )
				return false;
			break;
		case EM_ArmorPos_SecondHand:   	//副手
			if( Item.ArmorType == EM_Armor_Shield && Pos.Other.Shield == false )
				return false;
			if( Item.ArmorType == EM_Armor_Implement && Pos.Other.Implement == false )
				return false;
			break;
		case EM_ArmorPos_MagicTool:		//法寶
			return false;
		case EM_ArmorPos_Ornament:		//裝飾品
			return true;
		}

		if( IsNeedCheckType )
		{
			switch( Item.ArmorType )
			{
			case EM_Armor_HeavyArmed:
				if( Pos.ArmorType.HeavyArmed == false )
					return false;
				break;
			case EM_Armor_LightArmed:
				if( Pos.ArmorType.LightArmed == false )
					return false;
				break;
			case EM_Armor_Leather:
				if( Pos.ArmorType.Leather == false )
					return false;
				break;
			case EM_Armor_Clothes:
				if( Pos.ArmorType.Clothes == false )
					return false;
				break;
			case EM_Armor_Robe:
				if( Pos.ArmorType.Robe == false )
					return false;
				break;
			}
		}
	}
	else if( IsWeapon() )
	{
		switch( Pos.WeaponPosEnum )
		{
		case EM_AddonPos_WeaponLimitPos_None:
			break;
		case EM_AddonPos_WeaponLimitPos_MainHand:
			{
				switch( Item.WeaponPos )
				{
				case EM_WeaponPos_MainHand:     //主手
				case EM_WeaponPos_OneHand:      //雙手都可以裝備
				case EM_WeaponPos_TwoHand:      //兩手
					break;
				default:
					return false;
				}
			}
			break;
		case EM_AddonPos_WeaponLimitPos_OffHand:
			{
				switch( Item.WeaponPos )
				{
				case EM_WeaponPos_SecondHand:   //副手
				case EM_WeaponPos_OneHand:      //雙手都可以裝備
					break;
				default:
					return false;
				}
			}
			break;
		}
		switch( Item.WeaponType )
		{
		case EM_Weapon_Unarmed:			
			if( Pos.WeaponType.Unarmed == false )
				return false;
			break;
		case EM_Weapon_Blade:            
			if( Pos.WeaponType.Blade == false )
				return false;
			break;
		case EM_Weapon_Dagger:           
			if( Pos.WeaponType.Dagger == false )
				return false;
			break;
		case EM_Weapon_Wand:             
			if( Pos.WeaponType.Wand == false )
				return false;
			break;
		case EM_Weapon_Axe:              
			if( Pos.WeaponType.Axe == false )
				return false;
			break;
		case EM_Weapon_Bludgeon:         
			if( Pos.WeaponType.Bludgeon == false )
				return false;
			break;
		case EM_Weapon_Claymore:         
			if( Pos.WeaponType.Claymore == false )
				return false;
			break;
		case EM_Weapon_Staff:            
			if( Pos.WeaponType.Staff == false )
				return false;
			break;
		case EM_Weapon_2H_Axe:           
			if( Pos.WeaponType.Axe_2H == false )
				return false;
			break;
		case EM_Weapon_2H_Hammer:        
			if( Pos.WeaponType.Hammer_2H == false )
				return false;
			break;
		case EM_Weapon_Polearm:			
			if( Pos.WeaponType.Polearm == false )
				return false;
			break;
		case EM_Weapon_Bow:				
			if( Pos.WeaponType.Bow == false )
				return false;
			break;
		case EM_Weapon_CossBow:			
			if( Pos.WeaponType.CossBow == false )
				return false;
			break;
		case EM_Weapon_Gun:				
			if( Pos.WeaponType.Gun == false )
				return false;
			break;

		}
	}
	return true;
}
bool	GameObjDbStructEx::CheckInherentAbility( GameObjDbStructEx* AbilityDB , bool CheckLv )
{
	if( AbilityDB->IsAttribute() == false )
		return false;

//	if( IsArmor() == false && IsWeapon() == false )
//		return false;

	if( Item.MaxAttrCount == 0 )
		return false;

	return CheckInherentAbility( AbilityDB->Attirbute.AddPos , CheckLv );
}

//-----------------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////
//讀取Table表
/*
ReaderClass< CultivatePetBaseTableStruct >* GameObjDbStructEx::ObjReader_CultivatePetBase( )
{
	static ReaderClass< CultivatePetBaseTableStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char Buf[256];
		CultivatePetBaseTableStruct* Pt = 0;
		IsInit = true;

		Reader.SetData( "PetType"       , &Pt->PetType       	, ENUM_Type_IntPoint      );
		Reader.SetData( "BaseStr"		, &Pt->BaseStr       	, ENUM_Type_IntPoint      );
		Reader.SetData( "BaseSta"       , &Pt->BaseSta       	, ENUM_Type_IntPoint      );
		Reader.SetData( "BaseInt"       , &Pt->BaseInt       	, ENUM_Type_IntPoint      );
		Reader.SetData( "BaseMnd"       , &Pt->BaseMnd       	, ENUM_Type_IntPoint      );
		Reader.SetData( "BaseAgi"       , &Pt->BaseAgi			, ENUM_Type_IntPoint      );
		Reader.SetData( "MinTalent"     , &Pt->MinTalent		, ENUM_Type_IntPoint      );
		Reader.SetData( "MaxTalent"		, &Pt->MaxTalent	    , ENUM_Type_IntPoint      );
	}

	return &Reader;
}
*/
ReaderClass< CultivatePetLearnMagicTableStruct >* GameObjDbStructEx::ObjReader_CultivatePetLearnMagic( )
{
	static ReaderClass< CultivatePetLearnMagicTableStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		//char Buf[256];
		CultivatePetLearnMagicTableStruct* Pt = 0;
		IsInit = true;

		Reader.SetData( "MagicID"			, &Pt->MagicID          , ENUM_Type_IntPoint      );
		Reader.SetData( "Limit_PetProperty" , &Pt->Limit.PetProperty, ENUM_Type_IntPoint      );
		Reader.SetData( "Limit_PetType"     , &Pt->Limit.PetType	, ENUM_Type_IntPoint      );
		Reader.SetData( "Limit_Lv"      	, &Pt->Limit.Lv         , ENUM_Type_IntPoint      );
		Reader.SetData( "Limit_Str"      	, &Pt->Limit.Str        , ENUM_Type_IntPoint      );
		Reader.SetData( "Limit_Sta"      	, &Pt->Limit.Sta        , ENUM_Type_IntPoint      );
		Reader.SetData( "Limit_Int"      	, &Pt->Limit.Int        , ENUM_Type_IntPoint      );
		Reader.SetData( "Limit_Mnd"      	, &Pt->Limit.Mnd        , ENUM_Type_IntPoint      );
		Reader.SetData( "Limit_Agi"      	, &Pt->Limit.Agi        , ENUM_Type_IntPoint      );
		Reader.SetData( "KeyItem"      		, &Pt->Limit.KeyItem	, ENUM_Type_IntPoint      );
		Reader.SetData( "PowerLv"      		, &Pt->PowerLv			, ENUM_Type_IntPoint      );
		Reader.SetData( "SkillPoint"      	, &Pt->SkillPoint		, ENUM_Type_IntPoint      );
		Reader.SetData( "Lock"		      	, &Pt->Limit.Lock		, ENUM_Type_IntPoint      );
	}

	return &Reader;
}


/*
//讀取Table表
ReaderClass< CultivatePetBaseTableStruct >* GameObjDbStructEx::ObjReader_CultivatePetBase( )
{
	static ReaderClass< CultivatePetBaseTableStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char Buf[256];
		CultivatePetBaseTableStruct* Pt = 0;
		IsInit = true;

		Reader.SetData( "PetObjID"          , &Pt->PetObjID               , ENUM_Type_IntPoint      );
		Reader.SetData( "BasePetObjID"      , &Pt->BasePetObjID           , ENUM_Type_IntPoint      );
		Reader.SetData( "PetType1"          , &Pt->PetType[0]             , ENUM_Type_IntPoint      );
		Reader.SetData( "PetType2"          , &Pt->PetType[1]             , ENUM_Type_IntPoint      );
		Reader.SetData( "NewSkill1"         , &Pt->NewSkill[0]            , ENUM_Type_IntPoint      );
		Reader.SetData( "NewSkill2"         , &Pt->NewSkill[1]            , ENUM_Type_IntPoint      );
		Reader.SetData( "NewSkill3"         , &Pt->NewSkill[2]            , ENUM_Type_IntPoint      );
		Reader.SetData( "Evolve_RarePoint"  , &Pt->Evolve_RarePoint       , ENUM_Type_IntPoint      );
		Reader.SetData( "Evolve_GrowPoint"  , &Pt->Evolve_GrowPoint       , ENUM_Type_IntPoint      );
		Reader.SetData( "Fix_Sweet"         , &Pt->Fix.Sweet              , ENUM_Type_FloatPoint    );
		Reader.SetData( "Fix_Loyal"         , &Pt->Fix.Loyal              , ENUM_Type_FloatPoint    );
		Reader.SetData( "Fix_Grow"          , &Pt->Fix.Grow               , ENUM_Type_FloatPoint    );
		Reader.SetData( "Fix_Fitness"       , &Pt->Fix.Fitness            , ENUM_Type_FloatPoint    );
		Reader.SetData( "Fix_Hunger"        , &Pt->Fix.Hunger             , ENUM_Type_FloatPoint    );
		Reader.SetData( "Fix_Tired"         , &Pt->Fix.Tired              , ENUM_Type_FloatPoint    );
	}


	return &Reader;
}
ReaderClass< CultivatePetValueEffectTableStruct >* GameObjDbStructEx::ObjReader_CultivatePetValueEffect( )
{
	static ReaderClass< CultivatePetValueEffectTableStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char Buf[256];
		CultivatePetValueEffectTableStruct* Pt = 0;

		Reader.SetData( "MagicBuffID"      , &Pt->MagicBuffID               , ENUM_Type_IntPoint      );
		Reader.SetData( "Low_Sweet"        , &Pt->LimitLow.Sweet            , ENUM_Type_FloatPoint    );
		Reader.SetData( "Low_Loyal"        , &Pt->LimitLow.Loyal            , ENUM_Type_FloatPoint    );
		Reader.SetData( "Low_Grow"         , &Pt->LimitLow.Grow             , ENUM_Type_FloatPoint    );
		Reader.SetData( "Low_Fitness"      , &Pt->LimitLow.Fitness          , ENUM_Type_FloatPoint    );
		Reader.SetData( "Low_Hunger"       , &Pt->LimitLow.Hunger           , ENUM_Type_FloatPoint    );
		Reader.SetData( "Low_Tired"        , &Pt->LimitLow.Tired            , ENUM_Type_FloatPoint    );
		Reader.SetData( "Hi_Sweet"         , &Pt->LimitHi.Sweet             , ENUM_Type_FloatPoint    );
		Reader.SetData( "Hi_Loyal"         , &Pt->LimitHi.Loyal             , ENUM_Type_FloatPoint    );
		Reader.SetData( "Hi_Grow"          , &Pt->LimitHi.Grow              , ENUM_Type_FloatPoint    );
		Reader.SetData( "Hi_Fitness"       , &Pt->LimitHi.Fitness           , ENUM_Type_FloatPoint    );
		Reader.SetData( "Hi_Hunger"        , &Pt->LimitHi.Hunger            , ENUM_Type_FloatPoint    );
		Reader.SetData( "Hi_Tired"         , &Pt->LimitHi.Tired             , ENUM_Type_FloatPoint    );
		IsInit = true;
	}

	return &Reader;
}
ReaderClass< CultivatePetEventTableStruct >* GameObjDbStructEx::ObjReader_CultivatePetEvent( )
{
	static ReaderClass< CultivatePetEventTableStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char Buf[256];
		CultivatePetEventTableStruct* Pt = 0;
		Reader.SetData( "ActionType1"		, &Pt->ActionType[0]            , ENUM_Type_IntPoint		);
		Reader.SetData( "ActionType2"		, &Pt->ActionType[1]            , ENUM_Type_IntPoint		);
		Reader.SetData( "StrKey"			, &Pt->KeyStr					, ENUM_Type_CharString		, sizeof(Pt->KeyStr) , ENUM_Indirect_Address	);
		Reader.SetData( "LuaScript"			, &Pt->LuaScript				, ENUM_Type_CharString		, sizeof(Pt->LuaScript) , ENUM_Indirect_Address );

		Reader.SetData( "Limit_PetType1"	, &Pt->Limit.PetType[0]         , ENUM_Type_IntPoint      );
		Reader.SetData( "Limit_PetType2"	, &Pt->Limit.PetType[1]         , ENUM_Type_IntPoint      );
		Reader.SetData( "Limit_KeyItem"		, &Pt->Limit.KeyItem            , ENUM_Type_IntPoint      );
		Reader.SetData( "Limit_Character"	, &Pt->Limit.Character          , ENUM_Type_IntPoint      );

		Reader.SetData( "Limit_Low_Sweet"   , &Pt->Limit.Low.Sweet          , ENUM_Type_FloatPoint    );
		Reader.SetData( "Limit_Low_Loyal"   , &Pt->Limit.Low.Loyal          , ENUM_Type_FloatPoint    );
		Reader.SetData( "Limit_Low_Grow"    , &Pt->Limit.Low.Grow           , ENUM_Type_FloatPoint    );
		Reader.SetData( "Limit_Low_Fitness" , &Pt->Limit.Low.Fitness        , ENUM_Type_FloatPoint    );
		Reader.SetData( "Limit_Low_Hunger"  , &Pt->Limit.Low.Hunger         , ENUM_Type_FloatPoint    );
		Reader.SetData( "Limit_Low_Tired"   , &Pt->Limit.Low.Tired          , ENUM_Type_FloatPoint    );
		Reader.SetData( "Limit_Hi_Sweet"    , &Pt->Limit.Hi.Sweet           , ENUM_Type_FloatPoint    );
		Reader.SetData( "Limit_Hi_Loyal"    , &Pt->Limit.Hi.Loyal           , ENUM_Type_FloatPoint    );
		Reader.SetData( "Limit_Hi_Grow"     , &Pt->Limit.Hi.Grow            , ENUM_Type_FloatPoint    );
		Reader.SetData( "Limit_Hi_Fitness"  , &Pt->Limit.Hi.Fitness         , ENUM_Type_FloatPoint    );
		Reader.SetData( "Limit_Hi_Hunger"   , &Pt->Limit.Hi.Hunger          , ENUM_Type_FloatPoint    );
		Reader.SetData( "Limit_Hi_Tired"    , &Pt->Limit.Hi.Tired           , ENUM_Type_FloatPoint    );

		Reader.SetData( "Effect_Sweet"    	, &Pt->Effect.Sweet           	, ENUM_Type_FloatPoint    );
		Reader.SetData( "Effect_Loyal"    	, &Pt->Effect.Loyal           	, ENUM_Type_FloatPoint    );
		Reader.SetData( "Effect_Grow"     	, &Pt->Effect.Grow            	, ENUM_Type_FloatPoint    );
		Reader.SetData( "Effect_Fitness"  	, &Pt->Effect.Fitness         	, ENUM_Type_FloatPoint    );
		Reader.SetData( "Effect_Hunger"   	, &Pt->Effect.Hunger          	, ENUM_Type_FloatPoint    );
		Reader.SetData( "Effect_Tired"    	, &Pt->Effect.Tired           	, ENUM_Type_FloatPoint    );
		Reader.SetData( "Effect_Money"    	, &Pt->Money		           	, ENUM_Type_IntPoint	  );

		IsInit = true;
	}

	return &Reader;
}
ReaderClass< CultivatePetTalkTableStruct >* GameObjDbStructEx::ObjReader_CultivatePetTalk( )
{
	static ReaderClass< CultivatePetTalkTableStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char Buf[256];
		CultivatePetTalkTableStruct* Pt = 0;

		Reader.SetData( "KeyStr"			, &Pt->KeyStr					, ENUM_Type_CharString	, sizeof(Pt->KeyStr) , ENUM_Indirect_Address );

		Reader.SetData( "Limit_PetType1"	, &Pt->Limit.PetType[0]         , ENUM_Type_IntPoint      );
		Reader.SetData( "Limit_PetType2"	, &Pt->Limit.PetType[1]         , ENUM_Type_IntPoint      );
		Reader.SetData( "Limit_KeyItem"		, &Pt->Limit.KeyItem            , ENUM_Type_IntPoint      );
		Reader.SetData( "Limit_Character"	, &Pt->Limit.Character          , ENUM_Type_IntPoint      );

		Reader.SetData( "Limit_Low_Sweet"   , &Pt->Limit.Low.Sweet          , ENUM_Type_FloatPoint    );
		Reader.SetData( "Limit_Low_Loyal"   , &Pt->Limit.Low.Loyal          , ENUM_Type_FloatPoint    );
		Reader.SetData( "Limit_Low_Grow"    , &Pt->Limit.Low.Grow           , ENUM_Type_FloatPoint    );
		Reader.SetData( "Limit_Low_Fitness" , &Pt->Limit.Low.Fitness        , ENUM_Type_FloatPoint    );
		Reader.SetData( "Limit_Low_Hunger"  , &Pt->Limit.Low.Hunger         , ENUM_Type_FloatPoint    );
		Reader.SetData( "Limit_Low_Tired"   , &Pt->Limit.Low.Tired          , ENUM_Type_FloatPoint    );
		Reader.SetData( "Limit_Hi_Sweet"    , &Pt->Limit.Hi.Sweet           , ENUM_Type_FloatPoint    );
		Reader.SetData( "Limit_Hi_Loyal"    , &Pt->Limit.Hi.Loyal           , ENUM_Type_FloatPoint    );
		Reader.SetData( "Limit_Hi_Grow"     , &Pt->Limit.Hi.Grow            , ENUM_Type_FloatPoint    );
		Reader.SetData( "Limit_Hi_Fitness"  , &Pt->Limit.Hi.Fitness         , ENUM_Type_FloatPoint    );
		Reader.SetData( "Limit_Hi_Hunger"   , &Pt->Limit.Hi.Hunger          , ENUM_Type_FloatPoint    );
		Reader.SetData( "Limit_Hi_Tired"    , &Pt->Limit.Hi.Tired           , ENUM_Type_FloatPoint    );

		Reader.SetData( "ActionTimeType"    , &Pt->ActionTimeType          	, ENUM_Type_IntPoint	  );
		Reader.SetData( "IntervalTime"		, &Pt->IntervalTime          	, ENUM_Type_IntPoint	  );
		Reader.SetData( "Rate"				, &Pt->Rate          			, ENUM_Type_IntPoint	  );
		IsInit = true;
	}

	return &Reader;
}
ReaderClass< CultivatePetGrowTableStruct >* GameObjDbStructEx::ObjReader_CultivatePetGrow( )
{
	static ReaderClass< CultivatePetGrowTableStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char Buf[256];
		CultivatePetGrowTableStruct* Pt = 0;
		Reader.SetData( "Type"				, &Pt->Type          	, ENUM_Type_IntPoint	  );
		Reader.SetData( "LV"				, &Pt->Lv          		, ENUM_Type_IntPoint	  );
		Reader.SetData( "Policy"			, &Pt->Policy          	, ENUM_Type_IntPoint	  );
		Reader.SetData( "Str"				, &Pt->Str          	, ENUM_Type_IntPoint	  );
		Reader.SetData( "Sta"				, &Pt->Sta          	, ENUM_Type_IntPoint	  );
		Reader.SetData( "Int"				, &Pt->Int          	, ENUM_Type_IntPoint	  );
		Reader.SetData( "Mnd"				, &Pt->Mnd          	, ENUM_Type_IntPoint	  );
		Reader.SetData( "Agi"				, &Pt->Agi          	, ENUM_Type_IntPoint	  );

		IsInit = true;
	}
	return &Reader;
}
*/
ReaderClass< CultivatePetLifeSkillTableStruct >* GameObjDbStructEx::ObjReader_CultivatePetLifeSkill( )
{
	static ReaderClass< CultivatePetLifeSkillTableStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		//char Buf[256];
		CultivatePetLifeSkillTableStruct* Pt = 0;
		Reader.SetData( "Lv"				, &Pt->Lv      			, ENUM_Type_IntPoint	  );
		Reader.SetData( "SkillType"			, &Pt->SkillType    	, ENUM_Type_IntPoint	  );
		Reader.SetData( "NeedSkillLv"		, &Pt->Need.SkillLv    	, ENUM_Type_IntPoint	  );
		Reader.SetData( "NeedToolID"		, &Pt->Need.ToolID     	, ENUM_Type_IntPoint	  );
		Reader.SetData( "NeedItemID"		, &Pt->Need.ItemID     	, ENUM_Type_IntPoint	  );
		Reader.SetData( "NeedItemCount"		, &Pt->Need.ItemCount  	, ENUM_Type_IntPoint	  );
		Reader.SetData( "ProductItemID"		, &Pt->Product.ItemID  	, ENUM_Type_IntPoint	  );
//		Reader.SetData( "ProductCount"		, &Pt->Product.ItemCount, ENUM_Type_IntPoint	  );
//		Reader.SetData( "ProductMaxCount"	, &Pt->Product.ItemMaxCount, ENUM_Type_IntPoint	  );
		Reader.SetData( "EventTime"			, &Pt->EventTime      	, ENUM_Type_IntPoint	  );

		IsInit = true;
	}
	return &Reader;
}

/*
ReaderClass< PlantGrowActionTableStruct >* GameObjDbStructEx::ObjReader_PlantGrowAction( )
{
	static ReaderClass< PlantGrowActionTableStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		//char Buf[256];
		PlantGrowActionTableStruct* Pt = 0;
		Reader.SetData( "Type"				, &Pt->Type          	, ENUM_Type_IntPoint	  );
		Reader.SetData( "GrowRate"			, &Pt->GrowRate      	, ENUM_Type_IntPoint	  );
		Reader.SetData( "Water"				, &Pt->Water          	, ENUM_Type_IntPoint	  );
		Reader.SetData( "Topdress"			, &Pt->Topdress        	, ENUM_Type_IntPoint	  );
		Reader.SetData( "MagicWater"		, &Pt->MagicWater      	, ENUM_Type_IntPoint	  );
		IsInit = true;
	}
	return &Reader;
}
*/
ReaderClass< GuildHouseNpcReplaceTableStruct >*			GameObjDbStructEx::ObjReader_GuildHouseNpcReplace( )
{
	static ReaderClass< GuildHouseNpcReplaceTableStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		//char Buf[256];
		GuildHouseNpcReplaceTableStruct* Pt = 0;
		Reader.SetData( "Type"			, &Pt->Type          	, ENUM_Type_IntPoint	  );
		Reader.SetData( "OrgNpcID"		, &Pt->OrgNpcID      	, ENUM_Type_IntPoint	  );
		Reader.SetData( "NpcID"			, &Pt->NpcID			, ENUM_Type_IntPoint	  );
		IsInit = true;
	}
	return &Reader;
}
ReaderClass< GuildHouseNpcReplaceCostTableStruct >*		GameObjDbStructEx::ObjReader_GuildHouseNpcReplaceCost( )
{
	static ReaderClass< GuildHouseNpcReplaceCostTableStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		//char Buf[256];
		GuildHouseNpcReplaceCostTableStruct* Pt = 0;
		Reader.SetData( "Type"					, &Pt->Type          	, ENUM_Type_IntPoint	  );
		Reader.SetData( "GuildLv"				, &Pt->GuildLv         	, ENUM_Type_IntPoint	  );
		Reader.SetData( "Resource_Gold"			, &Pt->Cost.Gold      	, ENUM_Type_IntPoint	  );
		Reader.SetData( "Resource_BonusGold"	, &Pt->Cost.BonusGold   , ENUM_Type_IntPoint	  );
		Reader.SetData( "Resource_Mine"			, &Pt->Cost.Mine      	, ENUM_Type_IntPoint	  );
		Reader.SetData( "Resource_Wood"			, &Pt->Cost.Wood      	, ENUM_Type_IntPoint	  );
		Reader.SetData( "Resource_Herb"			, &Pt->Cost.Herb      	, ENUM_Type_IntPoint	  );
		Reader.SetData( "Resource_GuildRune"	, &Pt->Cost.GuildRune   , ENUM_Type_IntPoint	  );
		Reader.SetData( "Resource_GuildStone"	, &Pt->Cost.GuildStone  , ENUM_Type_IntPoint	  );

		IsInit = true;
	}
	return &Reader;
}


ReaderClass< PlantProductTableStruct >* GameObjDbStructEx::ObjReader_PlantProduct( )
{
	static ReaderClass< PlantProductTableStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		//char Buf[256];
		PlantProductTableStruct* Pt = 0;
		Reader.SetData( "SeedObjID"			, &Pt->SeedObjID          	, ENUM_Type_IntPoint	  );
		Reader.SetData( "Env_RarePoint"		, &Pt->Env_RarePoint      	, ENUM_Type_IntPoint	  );
		Reader.SetData( "Env_GrowPoint"		, &Pt->Env_GrowPoint        , ENUM_Type_IntPoint	  );
		Reader.SetData( "DropID"			, &Pt->DropID      			, ENUM_Type_IntPoint	  );
		Reader.SetData( "DropID_DLv5"		, &Pt->DropID_DLv5      	, ENUM_Type_IntPoint	  );
		Reader.SetData( "DropID_DLv10"		, &Pt->DropID_DLv10     	, ENUM_Type_IntPoint	  );
		Reader.SetData( "ExpRate"			, &Pt->ExpRate				, ENUM_Type_FloatPoint	  );
		Reader.SetData( "LuaScript"			, &Pt->LuaScript			, ENUM_Type_CharString	  , sizeof( Pt->LuaScript) );
		IsInit = true;
	}
	return &Reader;
}

ReaderClass< GambleItemStateTableStruct >* GameObjDbStructEx::ObjReader_GambleItemState( )
{
	static ReaderClass< GambleItemStateTableStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		//char Buf[256];
		GambleItemStateTableStruct* Pt = 0;
		Reader.SetData( "GambleObjID"		, &Pt->GambleObjID			, ENUM_Type_IntPoint	  );
		Reader.SetData( "FirstTimeCost"		, &Pt->FirstTimeCost		, ENUM_Type_IntPoint	  );
		Reader.SetData( "ContinueCost"		, &Pt->ContinueCost			, ENUM_Type_IntPoint	  );
		Reader.SetData( "MaxLv"				, &Pt->MaxLv      			, ENUM_Type_IntPoint	  );
		Reader.SetData( "MinLv"				, &Pt->MinLv      			, ENUM_Type_IntPoint	  );
		IsInit = true;
	}
	return &Reader;
}

ReaderClass< RuneSystemStruct >*			GameObjDbStructEx::ObjReader_RuneSystem( )
{
	static ReaderClass< RuneSystemStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char Buf[256];
		RuneSystemStruct* Pt = 0;
		Reader.SetData( "GUID"				, &Pt->GUID					, ENUM_Type_IntPoint	  );
		Reader.SetData( "MagicCol"			, &Pt->MagicCol				, ENUM_Type_IntPoint	  );
		Reader.SetData( "MagicColEx"		, &Pt->MagicColEx			, ENUM_Type_IntPoint	  );
		Reader.SetData( "TriggerCount"		, &Pt->TriggerCount			, ENUM_Type_IntPoint	  );
		Reader.SetData( "RuneColor1"		, &Pt->RuneColor[0]			, ENUM_Type_IntPoint	  );
		Reader.SetData( "RuneColor2"		, &Pt->RuneColor[1]			, ENUM_Type_IntPoint	  );
		Reader.SetData( "RuneColor3"		, &Pt->RuneColor[2]			, ENUM_Type_IntPoint	  );
		Reader.SetData( "RuneColor4"		, &Pt->RuneColor[3]			, ENUM_Type_IntPoint	  );
		Reader.SetData( "RuneColor5"		, &Pt->RuneColor[4]			, ENUM_Type_IntPoint	  );
		Reader.SetData( "RuneColor6"		, &Pt->RuneColor[5]			, ENUM_Type_IntPoint	  );

		IsInit = true;
	}
	return &Reader;
}
ReaderClass< PetCollectionTableStruct >*			GameObjDbStructEx::ObjReader_PetCollection( )
{
	static ReaderClass< PetCollectionTableStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char Buf[256];
		PetCollectionTableStruct* Pt = 0;
		Reader.SetData( "GUID"				, &Pt->GUID						, ENUM_Type_IntPoint	  );
		Reader.SetData( "ObjID"				, &Pt->ObjID					, ENUM_Type_IntPoint	  );

		IsInit = true;
	}
	return &Reader;
}

ReaderClass< AbiParametersTableStruct >*			GameObjDbStructEx::ObjReader_AbiParameters( )
{
	static ReaderClass< AbiParametersTableStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char Buf[256];
		AbiParametersTableStruct* Pt = 0;
		Reader.SetData( "GUID"				, &Pt->GUID						, ENUM_Type_IntPoint	  );
		Reader.SetData( "Parameter"			, &Pt->Parameter					, ENUM_Type_FloatPoint	  );

		IsInit = true;
	}
	return &Reader;
}
ReaderClass< PhantomRankTableStruct >*			GameObjDbStructEx::ObjReader_PhantomRank( )
{
	static ReaderClass< PhantomRankTableStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char Buf[256];
		PhantomRankTableStruct* Pt = 0;
		Reader.SetData( "Rank"				, &Pt->Rank						, ENUM_Type_IntPoint	  );
		Reader.SetData( "MaxLevel"			, &Pt->MaxLevel					, ENUM_Type_IntPoint	  );
		Reader.SetData( "NeedFragment"		, &Pt->NeedFragment				, ENUM_Type_IntPoint	  );

		IsInit = true;
	}
	return &Reader;
}
ReaderClass< PhantomLvTableStruct >*			GameObjDbStructEx::ObjReader_PhantomLv( )
{
	static ReaderClass< PhantomLvTableStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char Buf[256];
		PhantomLvTableStruct* Pt = 0;
		Reader.SetData( "LV"				, &Pt->LV					, ENUM_Type_IntPoint	  );
		Reader.SetData( "Type"				, &Pt->Type						, ENUM_Type_IntPoint	  );

		for( int i = 0 ; i < 4 ; i++ )
		{
			sprintf( Buf , "Material%d" , i+1  );
			Reader.SetData( Buf		, &Pt->Material[i]			, ENUM_Type_IntPoint	  );
		}

		IsInit = true;
	}
	return &Reader;
}
ReaderClass< PhantomSkillTableStruct >*			GameObjDbStructEx::ObjReader_PhantomSkill( )
{
	static ReaderClass< PhantomSkillTableStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char Buf[256];
		PhantomSkillTableStruct* Pt = 0;

		for( int i = 0 ; i < 2 ; i++ )
		{
			sprintf( Buf , "Phantom%d" , i+1  );
			Reader.SetData( Buf		, &Pt->Phantom[i]			, ENUM_Type_IntPoint	  );
		}
		Reader.SetData( "SkillID"		, &Pt->SkillID				, ENUM_Type_IntPoint	  );

		IsInit = true;
	}
	return &Reader;
}

ReaderClass< ServantEventTableStruct >*			GameObjDbStructEx::ObjReader_ServantEvent( )
{
	static ReaderClass< ServantEventTableStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char Buf[256];
		ServantEventTableStruct* Pt = 0;
		Reader.SetData( "GUID"				, &Pt->GUID					, ENUM_Type_IntPoint	  );
		Reader.SetData( "EventType1"		, &Pt->EventType[0]			, ENUM_Type_IntPoint	  );
		Reader.SetData( "EventType2"		, &Pt->EventType[1]			, ENUM_Type_IntPoint	  );
		Reader.SetData( "Condition1"		, &Pt->Condition[0]			, ENUM_Type_IntPoint	  );
		Reader.SetData( "Condition2"		, &Pt->Condition[1]			, ENUM_Type_IntPoint	  );
		Reader.SetData( "Condition3"		, &Pt->Condition[2]			, ENUM_Type_IntPoint	  );
		Reader.SetData( "Rate"				, &Pt->Rate					, ENUM_Type_IntPoint	  );
		for( int i = 0 ; i < 8 ; i++ )
		{
			sprintf( Buf , "MinValue%d" , i+1  );
			Reader.SetData( Buf		, &Pt->MinValue[i]			, ENUM_Type_IntPoint	  );
			sprintf( Buf , "MaxValue%d" , i+1  );
			Reader.SetData( Buf		, &Pt->MaxValue[i]			, ENUM_Type_IntPoint	  );
		}
		Reader.SetData( "Motion"			, &Pt->MotionID				, ENUM_Type_IntPoint	  );

		Reader.SetData( "TalkStr"			, &Pt->TalkStr				, ENUM_Type_CharString	  , sizeof( Pt->TalkStr) );
		Reader.SetData( "Voice"				, &Pt->Voice				, ENUM_Type_CharString	  , sizeof( Pt->Voice) );
		Reader.SetData( "SrvLuaScript"		, &Pt->LuaScript			, ENUM_Type_CharString	  , sizeof( Pt->LuaScript) );
		Reader.SetData( "SrvLuaCheckScript"	, &Pt->LuaCheckScript		, ENUM_Type_CharString	  , sizeof( Pt->LuaScript) );

		IsInit = true;
	}
	return &Reader;
}
ReaderClass< ServantHireTableStruct >*			GameObjDbStructEx::ObjReader_ServantHire( )
{
	static ReaderClass< ServantHireTableStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		ServantHireTableStruct* Pt = 0;

		Reader.SetData( "NPCObjID"			, &Pt->NPCObjID			, ENUM_Type_IntPoint	  );
		Reader.SetData( "FaceID"			, &Pt->FaceID			, ENUM_Type_IntPoint	  );
		Reader.SetData( "HairID"			, &Pt->HairID			, ENUM_Type_IntPoint	  );
		Reader.SetData( "SkinColor"			, &Pt->SkinColor		, ENUM_Type_IntPoint	  );
		Reader.SetData( "HairColor"			, &Pt->HairColor		, ENUM_Type_IntPoint	  );
		Reader.SetData( "ClothColor1"		, &Pt->ClothColor1		, ENUM_Type_IntPoint	  );
		Reader.SetData( "ClothColor2"		, &Pt->ClothColor2		, ENUM_Type_IntPoint	  );
		Reader.SetData( "Character"			, &Pt->Character		, ENUM_Type_IntPoint	  );

		IsInit = true;
	}
	return &Reader;
}
ReaderClass< ServantStartValueTableStruct >*	GameObjDbStructEx::ObjReader_ServantStartValue( )
{
	static ReaderClass< ServantStartValueTableStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char Buf[256];
		ServantStartValueTableStruct* Pt = 0;
		Reader.SetData( "NPCObjID"		, &Pt->NPCObjID			, ENUM_Type_IntPoint	  );
//		Reader.SetData( "Character"		, &Pt->Character		, ENUM_Type_IntPoint	  );
		Reader.SetData( "LookNpcObjID"	, &Pt->LookNpcObjID		, ENUM_Type_IntPoint	  );
		
		for( int i = 0 ; i < 8 ; i++ )
		{
			sprintf( Buf , "StartValue%d" , i+1  );
			Reader.SetData( Buf		, &Pt->StartValue[i]		, ENUM_Type_IntPoint	  );
			sprintf( Buf , "MaxValue%d" , i+1  );
			Reader.SetData( Buf		, &Pt->MaxValue[i]			, ENUM_Type_IntPoint	  );
		}
		Reader.SetData( "Sex"		, &Pt->Sex					, ENUM_Type_IntPoint	  );
		Reader.SetData( "Cost"		, &Pt->Cost					, ENUM_Type_IntPoint	  );
		IsInit = true;
	}
	return &Reader;
}

ReaderClass< ItemCombineStruct >*	GameObjDbStructEx::ObjReader_ItemCombine( )
{
	static ReaderClass< ItemCombineStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char Buf[256];
		ItemCombineStruct* Pt = 0;
		Reader.SetData( "ProductID"		, &Pt->ProductID		, ENUM_Type_IntPoint	  );
		Reader.SetData( "ProductCount"	, &Pt->ProductCount		, ENUM_Type_IntPoint	  );

		for( int i = 0 ; i < 5 ; i++ )
		{
			sprintf( Buf , "SourceID%d" , i+1  );
			Reader.SetData( Buf		, &Pt->SourceID[i]			, ENUM_Type_IntPoint	  );
			sprintf( Buf , "SourceCount%d" , i+1  );
			Reader.SetData( Buf		, &Pt->SourceCount[i]		, ENUM_Type_IntPoint	  );
		}

		IsInit = true;
	}
	return &Reader;
}

ReaderClass< RuneExchangeExTableStruct >*	GameObjDbStructEx::ObjReader_RuneExchangeEx( )
{
	static ReaderClass< RuneExchangeExTableStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char Buf[256];
		RuneExchangeExTableStruct* Pt = 0;
		Reader.SetData( "Type1"			, &Pt->Type1		, ENUM_Type_IntPoint	  );
		Reader.SetData( "Type2"			, &Pt->Type2		, ENUM_Type_IntPoint	  );
		Reader.SetData( "ResultType"	, &Pt->ResultType	, ENUM_Type_IntPoint	  );

		IsInit = true;
	}
	return &Reader;
}



ReaderClass< LifeSkillRareExStruct >*	GameObjDbStructEx::ObjReader_LifeSkillRareEx( )
{
	static ReaderClass< LifeSkillRareExStruct > Reader;
	static bool IsInit = false;

	if( IsInit == false )
	{
		char Buf[256];
		LifeSkillRareExStruct* Pt = 0;
		Reader.SetData( "ItemID"		, &Pt->ItemID			, ENUM_Type_IntPoint	  );
		Reader.SetData( "Rare1ItemID"	, &Pt->RareItemID[0]	, ENUM_Type_IntPoint	  );
		Reader.SetData( "Rare2ItemID"	, &Pt->RareItemID[1]	, ENUM_Type_IntPoint	  );
		Reader.SetData( "Rare3ItemID"	, &Pt->RareItemID[2]	, ENUM_Type_IntPoint	  );
		IsInit = true;
	}
	return &Reader;
}


