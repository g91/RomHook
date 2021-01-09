#include <string.h>
#include "getfontnamefromfile.h"

string GetFontNameFromFile(LPCTSTR lpszFilePath)
{
	HANDLE f;
	string sRetVal;

	f = CreateFile(lpszFilePath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	if ( f != INVALID_HANDLE_VALUE )
	{
		DWORD readBytes;
		TT_OFFSET_TABLE ttOffsetTable;
		ReadFile( f, &ttOffsetTable, sizeof(TT_OFFSET_TABLE), &readBytes, NULL );
		ttOffsetTable.uNumOfTables = SWAPWORD(ttOffsetTable.uNumOfTables);
		ttOffsetTable.uMajorVersion = SWAPWORD(ttOffsetTable.uMajorVersion);
		ttOffsetTable.uMinorVersion = SWAPWORD(ttOffsetTable.uMinorVersion);

		//check is this is a true type font and the version is 1.0
		if(ttOffsetTable.uMajorVersion != 1 || ttOffsetTable.uMinorVersion != 0)
			return sRetVal;

		TT_TABLE_DIRECTORY tblDir;
		BOOL bFound = FALSE;
		char szTemp[1024];

		for(int i=0; i< ttOffsetTable.uNumOfTables; i++)
		{
			ReadFile( f, &tblDir, sizeof(TT_TABLE_DIRECTORY), &readBytes, NULL );
			memcpy( szTemp, tblDir.szTag, sizeof(tblDir.szTag) );
			szTemp[4] = 0;

			if ( _stricmp(szTemp, "name") == 0 )
			{
				bFound = TRUE;
				tblDir.uLength = SWAPLONG(tblDir.uLength);
				tblDir.uOffset = SWAPLONG(tblDir.uOffset);
				break;
			}
		}

		if( bFound )
		{
			SetFilePointer( f, tblDir.uOffset, 0, FILE_BEGIN );
			TT_NAME_TABLE_HEADER ttNTHeader;

			ReadFile( f, &ttNTHeader, sizeof(TT_NAME_TABLE_HEADER), &readBytes, NULL );
			ttNTHeader.uNRCount = SWAPWORD(ttNTHeader.uNRCount);
			ttNTHeader.uStorageOffset = SWAPWORD(ttNTHeader.uStorageOffset);
			TT_NAME_RECORD ttRecord;
			bFound = FALSE;

			for(int i=0; i<ttNTHeader.uNRCount; i++)
			{
				ReadFile( f, &ttRecord, sizeof(TT_NAME_RECORD), &readBytes, NULL );
				ttRecord.uNameID = SWAPWORD(ttRecord.uNameID);
				if(ttRecord.uNameID == 4)
				{
					ttRecord.uStringLength = SWAPWORD(ttRecord.uStringLength);
					ttRecord.uStringOffset = SWAPWORD(ttRecord.uStringOffset);
					DWORD nPos = SetFilePointer( f, 0, 0, FILE_CURRENT );
					SetFilePointer( f, tblDir.uOffset + ttRecord.uStringOffset + ttNTHeader.uStorageOffset, 0, FILE_BEGIN );
					ReadFile( f, szTemp, ttRecord.uStringLength, &readBytes, NULL );

					szTemp[ttRecord.uStringLength] = 0;
					
					if ( szTemp[0] == 0 )
					{
						char buf[256];
						int count = 0;
						memset(buf, 0, sizeof(buf));
						for (int i = 0; i < readBytes; i++)
						{
							if (szTemp[i] != 0)
								buf[count++] = szTemp[i];
						}

						memcpy(szTemp, buf, count);
					}

					
					if ( strlen(szTemp) > 0 )
					{
						sRetVal = szTemp;
						break;
					}
					SetFilePointer( f, nPos, 0, FILE_BEGIN );
				}
			}			
		}
		CloseHandle( f );
	}
	return sRetVal;
}

