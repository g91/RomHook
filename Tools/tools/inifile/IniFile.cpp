#include "iniFile.h"

#include <windows.h>
#include <shlwapi.h>

#pragma warning (disable:4949)
#pragma unmanaged

//**************************************************************************************
//靜態資料
//**************************************************************************************
IniFileClass::IniFileClass()
{
_Section="BOOT";

}

bool		IniFileClass::SetInt(const char* Name,int value )

{
	char temp[256];
	sprintf(temp,"%d",value);

	if(	SetStr( Name , temp ) == false )
		return false;
	return true;
}

int		IniFileClass::Int(const char* Name )

{
	string a=Str(Name);
	if (a.length()==0)
		return 0;

	return atoi(a.c_str());
}

int		IniFileClass::IntDef(const char* Name,int def )

{
	string a=Str(Name);
	if (a.length()==0)
		return def;

	return atoi(a.c_str());
}


void	IniFileClass::SetSection(const char *section)
{
	_Section=section;

}
string 	IniFileClass::GetSection(void)
{

	return _Section;
}
float	IniFileClass::Float( const char* KeyStr  )
{
	string a=Str(KeyStr);
    if (a.length()==0)
		return 0;

	return float( atof(a.c_str()) );
}
float	IniFileClass::FloatDef( const char* KeyStr  ,float def  )
{
	string a=Str(KeyStr);
    if (a.length()==0)
		return def;

	return float( atof(a.c_str()) );
}
bool	IniFileClass::SetFloat( const char* KeyStr ,float f )
{
	char temp[256];
	sprintf(temp,"%f",f);

	if(	SetStr( KeyStr , temp ) == false )
		return false;

return true;
}
bool	IniFileClass::Float( const char* KeyStr , float&	f )
{

	string tempStr;
	if( Str( KeyStr , tempStr ) == false )
		return false;

	f = float( atof( tempStr.c_str() ) );
	return true;
}
bool IniFileClass::SetStr(const char* Name, const char* value)
{
	char Buf[256];
	vector<string>::iterator Iter;
	int		Ret;

	for( Iter = _FullPath.begin() ; Iter != _FullPath.end() ; Iter++)
	{
		Ret = WritePrivateProfileString(_Section.c_str(), Name,  value, Iter->c_str()); 

		//如果有找到資料則結束
		if( Ret > 0 )
			break;		
	}
	if( Iter == _FullPath.end() )
	{
		sprintf( Buf , "IniFile : Name = %s not find!\n" , Name );
		OutputDebugString( Buf );
		return false;
	}

	return true;
}
string	IniFileClass::Str(const char* Name)
{
	char Buf[256];
	vector<string>::iterator Iter;
	int		Ret;

	for( Iter = _FullPath.begin() ; Iter != _FullPath.end() ; Iter++)
	{
		Ret = GetPrivateProfileString(_Section.c_str(), Name, NULL, Buf, sizeof(Buf),Iter->c_str()); 

		//如果有找到資料則結束
		if( Ret > 0 )
			break;		
	}
	if( Iter == _FullPath.end() )
	{
		sprintf( Buf , "IniFile : Name = %s not find!\n" , Name );
		OutputDebugString( Buf );
		return "";
	}

	return Buf;
}

bool	IniFileClass::SetIniFile(const char *filename)
{
	char	Path[255];
	string	FileFullPath;

	GetCurrentDirectory(sizeof(Path),Path);
	FileFullPath = Path ;
	FileFullPath = FileFullPath + "\\" + filename;

	// if file contain filepath
	if( PathFileExists( FileFullPath.c_str() ) == false )
	{
/*		//檢查檔案是否存在
		if( PathFileExists( FileFullPath.c_str()) == false )
		{
			return false;
		}
		*/
		if( PathFileExists( filename ) == false )
		{
			return false;
		}
		_FullPath.push_back( filename );
	}
	else
	{
		
		_FullPath.push_back( FileFullPath );
	}

	return true;
}

bool	IniFileClass::Int( const char* KeyStr , int& OutInt )
{
	string tempStr;
	if( Str( KeyStr , tempStr ) == false )
		return false;

	OutInt = atoi( tempStr.c_str() );
	return true;
}
bool	IniFileClass::Str( const char* KeyStr , string&	OutString )
{
	char Buf[256];
	vector<string>::iterator Iter;
	int		Ret;

	for( Iter = _FullPath.begin() ; Iter != _FullPath.end() ; Iter++)
	{
		Ret = GetPrivateProfileString(_Section.c_str(), KeyStr, NULL, Buf, sizeof(Buf),Iter->c_str()); 

		//如果有找到資料則結束
		if( Ret > 0 )
			break;		
	}
	if( Iter == _FullPath.end() )
	{
		return false;
	}

	OutString = Buf;

	return true;
}
#pragma managed