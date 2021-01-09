#ifndef		_ERROR_MESSAGE_OUPUT_2003_8_6
#define		_ERROR_MESSAGE_OUPUT_2003_8_6
#pragma warning (disable:4949)

#include    <boost/function.hpp>
#include    <boost/bind.hpp>
#include    <functional>
#include	<vector>
#pragma unmanaged

using	namespace std;

//-------------------------------------------------------------------------------------------------
#define Def_PrintLV1     1	// �T����X
#define Def_PrintLV2     2	// �S��T��
#define Def_PrintLV3     3	// ���i��|�o�ͪ����~, �p���a�o�e���~�ʥ]
#define Def_PrintLV4     4	// �������i�ಣ�ͪ����D
#define Def_PrintLV5     5	// �|��
#define Def_PrintLV6	 6	// ���nĵ�i�T��

#define LV1				1	// �T����X
#define LV2				2	// �S��T��
#define LV3				3	// ���i��|�o�ͪ����~, �p���a�o�e���~�ʥ]
#define LV4				4	// �������i�ಣ�ͪ����D
#define LV5				5	// �|��
#define LV6				6	// ���nĵ�i�T��
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
class	MassageOuputClass
{
	string	_FileName;
public:
	MassageOuputClass( char* File );
	void	Print(char* format,...);
};
//-------------------------------------------------------------------------------------------------
#define BaseOutputFunction  boost::function< void ( int LV , const char* Title , const char* Context ) >

class PrintClass
{
    int                 _PrintDisplayLV;
    int                 _OuputLV;
	int					_FileOutputLV;
	int                 _ControllerOuputLV;
    BaseOutputFunction  _OutputFunc;
	BaseOutputFunction  _ControllerOutputFunc;

	string				_OutputFile;
	string				_OutputField;		//�ؿ�
	string				_OutputPath;

	int					_TimeClock;

	void				_MakePath();

	vector<string>		_OutputMsgList;		//�n�g�ɪ��T��
	int					_LastOutputTime;
public:
    PrintClass();
    ~PrintClass();
    void Init( BaseOutputFunction fp );
    void Release( );
//	void OpenFile( );
//	void CloseFile( );

    void operator() ( int LV , const char* Title , const char* format , ... );
	void Print( int LV , const char* Title , const char* format , va_list Marker );
    void SetPrintLV( int LV )											{ _PrintDisplayLV = LV;};
    void SetOutputLV( int LV )											{ _OuputLV = LV; _ControllerOuputLV = LV;};
	void SetControllerOutputFunc( BaseOutputFunction Func )				{ _ControllerOutputFunc = Func;};
	void SetControllerOutputLV( int LV )								{ _ControllerOuputLV = LV;};

	void SetFileOutputLV( int LV )										{ _FileOutputLV = LV; }
	void SetOutputFileName( string File )								{ _OutputFile = File; }
	void SetOutputFieldName( string Field )								{ _OutputField = Field; }

	void OutputToFile( int LV , const char* Title, const char* Message );
	void OutputToFile( const char* Message );

	void OutputToBuff( int LV , const char* Title , const char* format , va_list Marker );
	void OutputToBuff( int LV , const char* Title, const char* Message );
	void OutputToBuff( const char* Message );
	void OutputBuffToFile( );

};
//-------------------------------------------------------------------------------------------------

extern PrintClass*   g_pPrint;
extern PrintClass*   g_pNetStatus;

void	Print( int LV , const char* Title , const char* format , ... );
void	PrintNetstatus( int LV , const char* Title , const char* format , ... );
void	PrintToFile( int LV , const char* Title , const char* format , ... );
void	CreatePrint( );
void	DestroyPrint( );

#pragma managed
#endif