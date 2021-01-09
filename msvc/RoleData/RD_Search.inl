//搜尋身體空欄位(-1) 代表搜尋不到
//int	 SearchBodyEmptyPos( );
int	 SearchBankEmptyPos( );

int	 SearchBankEmptyPos( const ItemFieldStruct *Item, bool isHeap, int count = 1 );

bool CheckBankItemHeap( const ItemFieldStruct *Item, int position );

//找到地一個可堆疊的地方
int  SearchBodyFirstFit( const ItemFieldStruct *Item );

//找到地一個可堆疊的地方
int	 SearchBodyFirstFit( const ItemFieldStruct *Item, bool isHeap, int count = 1 );

// 檢查該欄位是否可以使用(租用時間)
bool CheckBodyItemEnable( int index );

// 檢查該欄位是否可以使用(租用時間)
bool CheckBankItemEnable( int index );

//收尋某物件ID所對應此物件仇恨表的位置
//如果之前沒在裡面 則找一個適合的位置
NPCHateStruct*		GetHatePos( int	ID , int DBID );
NPCHateStruct*		GetHatePos( int	ID );


//取得身上某一種法術Buf
BuffBaseStruct*		GetBuff( GameObjectMagicTypeENUM AssistType , int MagicBaseID );

SuitSkllBaseStruct* FindSuitSkill( int SkillID );
bool FindSuitSkill_EQ( int SkillID );