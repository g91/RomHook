
#include "iniFile2.h"

#include <windows.h>
#include <shlwapi.h>

#pragma warning (disable:4949)
#pragma unmanaged

//**************************************************************************************
//ÀRºA¸ê®Æ
//**************************************************************************************
IniFile2::IniFile2()
{
	_ini.SetUnicode(true);
	_Section=_T("BOOT");
}

bool IniFile2::SetInt(LPCTSTR key,int value )

{
	TCHAR temp[256];
	_stprintf(temp,_T("%d"),value);

	if(	SetStr( key , temp ) == false )
		return false;
	return true; 
}

int		IniFile2::Int(LPCTSTR key )

{
	CTString a=Str(key);
	if (a.length()==0)
		return 0;

	return _tstoi(a.c_str());
}

int		IniFile2::IntDef(LPCTSTR key,int def )

{
	CTString a=Str(key);
	if (a.length()==0)
		return def;

	return _tstoi(a.c_str());
}


void	IniFile2::SetSection(LPCTSTR section)
{
	_Section=section;

}
CTString 	IniFile2::GetSection(void)
{

	return _Section;
}
float	IniFile2::Float( LPCTSTR key )
{
	CTString a=Str(key);
    if (a.length()==0)
		return 0;

	return (float)_tstof(a.c_str());
}

CTString IniFile2::StrDef(LPCTSTR key,LPCTSTR defValue)
{
	CTString a=Str(key);
	if (a.length()==0)
		return defValue;

	return a;
}
float	IniFile2::FloatDef( LPCTSTR key  ,float def  )
{
	CTString a=Str(key);
    if (a.length()==0)
		return def;

	return (float)_tstof(a.c_str());
}
bool	IniFile2::SetFloat( LPCTSTR key ,float f )
{
	TCHAR temp[256];
	_stprintf(temp,_T("%f"),f);

	if(	SetStr( key , temp ) == false )
		return false;

return true;
}

bool IniFile2::SetStr(LPCTSTR key, LPCTSTR value)
{
    SI_Error ReturnCode = SI_OK;
    ReturnCode = _ini.SetValue(_Section.c_str(), key, value);

    if (ReturnCode != SI_OK)
	{
        TCHAR Buf[256];
        Buf[255] = '\0';
        _sntprintf(Buf, 255, _T("IniFile(%s) : SetStr(%s, %s) - return error !\n"), _Section.c_str(), key, value);
		OutputDebugString(Buf);
		return false;
	}

	return true;
}

CTString IniFile2::Str(LPCTSTR key)
{
	LPCTSTR pValue = NULL;
    pValue = _ini.GetValue(_Section.c_str(), key);

    if (pValue == NULL)
	{
		TCHAR Buf[256];
        Buf[255] = '\0';
        _sntprintf(Buf, 255, _T("IniFile(%s) : GetStr(%s) : got null string !\n"), _Section.c_str(), key);
		OutputDebugString(Buf);
		return _T("");
	}

    return pValue;
}

bool	IniFile2::SetIniFile(LPCTSTR filename)
{
	TCHAR Path[1024];
	
	lstrcpy(Path,filename);
	// if file contain filepath
	if( PathFileExists( filename ) == false )
	{		
		TCHAR tCurrentDirectory[1024];
		GetCurrentDirectory(sizeof(tCurrentDirectory),tCurrentDirectory);
		wsprintf(Path,_T("%s\\%s") ,tCurrentDirectory,filename);	
	}
	return _ini.LoadFile(Path)==SI_OK;


	//return true;
}


void IniFile2::SetUnicode(bool s)
{
_ini.SetUnicode(s);

}
bool IniFile2::SetIniData(LPVOID data,DWORD size)
{

	return _ini.Load((char *)data,size)==SI_OK;


	//return true;
}

void IniFile2::Save(LPCTSTR FileName)
{

	_ini.SaveFile(FileName);



}
void IniFile2::SaveString (std::string &buff)
{

	_ini.Save(buff);



}
#pragma managed