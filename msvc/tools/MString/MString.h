#ifndef M_STRING_H_
#define M_STRING_H_

// ------------------------------------------------------------------------
// ����@�r���禡����
typedef int (*pFCompareChar) (char ch);

//-----------------------------------------------------------------------------
// Name: CharAlphabetA()
// Desc: ���o�ڬ���r����
// Arg : const char* inString �ӷ��r��
//		 int iLength �ӷ��r�����
// return : �^�Ǧr�����
//-----------------------------------------------------------------------------
int SeparateStringA(const unsigned char* inString, int iLength);

//-----------------------------------------------------------------------------
// Name: IntToStr()
// Desc: �ƭ��ഫ���r��÷|�Ҽ{�r��ҭn���ͦ�m
// Arg : char *pDest �x�s�ഫ��r����
//		 int iValue ���ഫ���ƭ�
//		 int iPosi ���� printf("%2d")��2d���ĪG,�]�w���ѼƷ|�b�ഫ����r���
//		 �׬O�_�p��iPosi�]�w��,�Y�p��h�ɤW�Ů�
// return : �^�Ǹg�ഫ��ت��r��s�����Ц�m
//-----------------------------------------------------------------------------
char* IntToStrA( char *pDest ,int iValue, int iPosi=0 );

//-----------------------------------------------------------------------------
// Name: CommandAnalytic()
// Desc: �ˬd�r��O�_���ഫ����X
// Arg : const char* string �ӷ��r��
//		 int* piLen �r��e�i�Z��,����X�Ҧ��r���Ӽ�
// return : �^�Ǳ���X����
//-----------------------------------------------------------------------------
int CommandAnalyticA( const char* string, int* piLen );

//-----------------------------------------------------------------------------
// Name: ChangeString()
// Desc: �ഫ�r�ꤤ���S����X�r��
// Arg : char* dest �ت��r��
//		 const char* format_string �ӷ��r��
//		 ... ���w�ѼƭӼ�
// return : 0
//-----------------------------------------------------------------------------
void SwapStringA( char* dest, const char* format_string, ... );
void SwapStringExA( char* dest, const char* format_string, va_list argp );

//-----------------------------------------------------------------------------
// Name: CharDouble()
// Desc: �P�_�O�_�����r����
// Arg : const char* dest �P�_�r��
// return : 0�_ 1�O
//-----------------------------------------------------------------------------
int CharDouble(const char* dest);

//-----------------------------------------------------------------------------
// Name: _m_show_char()
// Desc: �O�_���i���r��(32 ~ 127)
// Arg : unsigned char ch �P�_�r��
// return : 0�_ 1�O
//-----------------------------------------------------------------------------
int _m_show_char(char ch);

//-----------------------------------------------------------------------------
// Name: CopyString()
// Desc: �ƻs���w���צr���ت��r�ꤺ,�åi���w�O�_�����p��Y�Ǧr��
// Arg : char* des �ت��r�����
//		 const char* src �ӷ��r��
//		 iLimit ����ƻs�r����(BYTE)
//		 pfChar �r�����禡,�Y�Ǧ^false�h�Ӧr���|�[�J�ت��r�ꤺ,�����p��Ӧr��
//				����,�D�n�ΥH�N�@�Ǳ���X�ƻs��ت��r�ꤺ,���u�p��i��ܪ��r��
//				����
// return : 0�_ 1�O
//-----------------------------------------------------------------------------
int CopyString(char* des, const char* src, int iLimit, pFCompareChar pfChar);

//-----------------------------------------------------------------------------
// Name: _m_strncpy()
// Desc: �ƻs���w���צr���ت��r�ꤺ,�åi���w�O�_�����p��Y�Ǧr��
// Arg : char* des �ت��r�����
//		 const char* src �ӷ��r��
//		 iLimit ����ƻs�r����(BYTE)
//		 pfChar �r�����禡,�Y�Ǧ^false�h�Ӧr���|�[�J�ت��r�ꤺ,�����p��Ӧr��
//				����,�D�n�ΥH�N�@�Ǳ���X�ƻs��ت��r�ꤺ,���u�p��i��ܪ��r��
//				����
// return : 0�_ 1�O
//-----------------------------------------------------------------------------
int _m_strncpy(char* des, const char* src, int iLimit, pFCompareChar pfChar);


// ----------------------------------------------------------------------------
// �N�r��̫��w�j�p(Byte),�����[�J���w�Ÿ�
int SizeAddChar(char* des, char* src, int iLimit, char ch, pFCompareChar pChar);

// ----------------------------------------------------------------------------
// ������ܦr�ꬰ���w�j�p
int ClipText(char* des, char* src, int iLimit);

// ----------------------------------------------------------------------------
// �Ǧ^�i��ܪ��̤j�r�����,�Y������ܦr������b��,������r����,���s�p��
int _m_show_strlen(char* src);

// ----------------------------------------------------------------------------
// �Ǧ^�i��ܪ��̤j�r�����,�Y������ܦr������b��,������r����,���s�p��
int ShowTextWidth(char* src);

// ----------------------------------------------------------------------------
// �p��r����ܮɼe���j�p
void _m_Show_Text_Dimension(char* pSrc, int* piWidth, int* piHeight);

// ----------------------------------------------------------------------------
// ���N�r�ꤤ���w�r�����t�@�r��
void _m_Replace_Text_Char(char* pText, char cDes, char cSrc);

// ----------------------------------------------------------------------------
// �j�M�r���̫�X�{�b�r�ꪺ��m
int _m_Search_Last_Char(const char* pSrc, char ch);


#endif