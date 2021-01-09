#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include <atlstr.h>
//////////////////////////////////////////////////////////////////////
/*
 $History: FileVersion.h $
 * 
 * *****************  Version 3  *****************
 * User: Navis        Date: 6/18/99    Time: 3:35p
 * Updated in $/PJ
 * Standardized History and include format.
 * Implemented Insert Template Wizard.
 * 
 * *****************  Version 2  *****************
 * User: Navis        Date: 4/19/99    Time: 3:29p
 * Updated in $/PJ
 * class to obtain module version info.  Intend to use in About Dialog
 * box.
*/
//////////////////////////////////////////////////////////////////////
// by Manuel Laflamme from CodeGuru site.

class CFileVersion
{ 
// Construction
public: 
    CFileVersion();

// Operations	
public: 
    BOOL    Open(LPCTSTR lpszModuleName);
    void    Close();

    CString QueryValue(LPCTSTR lpszValueName, DWORD dwLangCharset = 0);
    CString GetFileDescription()  {return QueryValue(_T("FileDescription")); };
    CString GetFileVersion()      {return QueryValue(_T("FileVersion"));     };
    CString GetInternalName()     {return QueryValue(_T("InternalName"));    };
    CString GetCompanyName()      {return QueryValue(_T("CompanyName"));     }; 
    CString GetLegalCopyright()   {return QueryValue(_T("LegalCopyright"));  };
    CString GetOriginalFilename() {return QueryValue(_T("OriginalFilename"));};
    CString GetProductName()      {return QueryValue(_T("ProductName"));     };
    CString GetProductVersion()   {return QueryValue(_T("ProductVersion"));  };

    BOOL    GetFixedInfo(VS_FIXEDFILEINFO& vsffi);
    CString GetFixedFileVersion();
    CString GetFixedProductVersion();

// Attributes
protected:
    LPBYTE  m_lpVersionData; 
    DWORD   m_dwLangCharset; 

// Implementation
public:
    ~CFileVersion(); 
}; 




