//�j�M��������(-1) �N��j�M����
//int	 SearchBodyEmptyPos( );
int	 SearchBankEmptyPos( );

int	 SearchBankEmptyPos( const ItemFieldStruct *Item, bool isHeap, int count = 1 );

bool CheckBankItemHeap( const ItemFieldStruct *Item, int position );

//���a�@�ӥi���|���a��
int  SearchBodyFirstFit( const ItemFieldStruct *Item );

//���a�@�ӥi���|���a��
int	 SearchBodyFirstFit( const ItemFieldStruct *Item, bool isHeap, int count = 1 );

// �ˬd�����O�_�i�H�ϥ�(���ήɶ�)
bool CheckBodyItemEnable( int index );

// �ˬd�����O�_�i�H�ϥ�(���ήɶ�)
bool CheckBankItemEnable( int index );

//���M�Y����ID�ҹ��������󤳫����m
//�p�G���e�S�b�̭� �h��@�ӾA�X����m
NPCHateStruct*		GetHatePos( int	ID , int DBID );
NPCHateStruct*		GetHatePos( int	ID );


//���o���W�Y�@�تk�NBuf
BuffBaseStruct*		GetBuff( GameObjectMagicTypeENUM AssistType , int MagicBaseID );

SuitSkllBaseStruct* FindSuitSkill( int SkillID );
bool FindSuitSkill_EQ( int SkillID );