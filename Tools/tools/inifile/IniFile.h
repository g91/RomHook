#ifndef		__INIFILE_H_2003_16__
#define		__INIFILE_H_2003_16__

#pragma warning (disable:4786)
#pragma warning (disable:4949)
#include	<string>
#include	<vector>

#pragma unmanaged

using namespace std;

class	IniFileClass
{
protected:
	//檔案完整路徑
	vector<string>	_FullPath;
	string          _Section;
public:
	IniFileClass();
	//設定INI檔案 (可負數設定)
	bool	SetIniFile(const char *FileName);
	void	SetSection(const char *section);
	string 	GetSection(void);
	int		Int(const char*);
	int		IntDef(const char*,int def =0);
	string	Str(const char*);
	float	Float( const char* KeyStr );
	float	FloatDef( const char* KeyStr ,float def =0);

	bool	Int( const char* KeyStr , int&		OutInt );
	bool	SetInt(const char* Name,int value );
	bool	Str( const char* KeyStr , string&	OutString );
	bool	Float( const char* KeyStr , float&	f );
	bool	SetStr(const char* Name, const char* value);
	bool	SetFloat( const char* KeyStr ,float f );
};


#pragma managed
#endif