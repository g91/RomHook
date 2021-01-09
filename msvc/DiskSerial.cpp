#include "StdAfx.h"
#include "diskserial.h"
#include "Utils.h"

#pragma unmanaged

BOOL  gHaveSerial=false;
DWORD DriveSerial=0;			// hash value
char  sDriveSerial[256]="";		// serial string

tDeviceIoControl pDeviceIoControl;
tCreateFileA	 pCreateFileA;
tCloseHandle     pCloseHandle;

int getPhysicalDeviceID(char drive)
{
PROT_BEGIN
	HANDLE hDevice;
	DWORD  bytesreturned;
	BOOL   bResult;
	int    result;
	DEVICE_NUMBER deviceInfo;
	char devicename[7];

	devicename[0] = devicename[1]=devicename[3]='\\';		 //  \\\\.\\<drive>:
	devicename[4] = drive;
	devicename[2] = '.';
	devicename[5] = ':';
	devicename[6] = 0;
	result=-1;
	hDevice = pCreateFileA((LPCTSTR)devicename, 0, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hDevice != INVALID_HANDLE_VALUE)
	{
		bResult = DeviceIoControl(hDevice, IOCTL_STORAGE_GET_DEVICE_NUMBER, NULL, 0, &deviceInfo, sizeof(deviceInfo), &bytesreturned, NULL);
		if (bResult) result=(int)deviceInfo.DeviceNumber;
		CloseHandle(hDevice);
	}
PROT_END
	return result;
}

DWORD ReadPhysicalDriveInNTWithZeroRights(char *sSerial, int len)
{
PROT_BEGIN
   DWORD  serial;
   int	  drive;
   char	  driveformat[20]=".'/hQiztjdbmEsjwf&e";   /* "\\\\.\\PhysicalDisk%s"  */
   char   driveName [256];
   HANDLE hPhysicalDriveIOCTL = 0;

   if (sSerial) sSerial[0]=0;

   // recover original formatstring
   for (drive=0; driveformat[drive]!=0; drive++) driveformat[drive]-=1;
   driveformat[0]=driveformat[1]=driveformat[3]='\\';

   serial=0;
   drive=getPhysicalDeviceID('C');		// get physical disk of C:    So no checks for removeble has to be taken.
   //  Try to get a handle to PhysicalDrive IOCTL, report failure
   //  and exit if can't.

   if (drive!=-1) {
	   sprintf (driveName, driveformat, drive);
	   //  Windows NT, Windows 2000, Windows XP - admin rights not required
	   hPhysicalDriveIOCTL = pCreateFileA ((LPCTSTR)driveName, 0,
							   FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
							   OPEN_EXISTING, 0, NULL);

	   if (hPhysicalDriveIOCTL != INVALID_HANDLE_VALUE)
	   {
		 STORAGE_PROPERTY_QUERY query;
		 DWORD		cbBytesReturned = 0;
		 char		*ptr,buffer[1000];

		 memset ((void *)&query, 0, sizeof(query));
		 query.PropertyId = StorageDeviceProperty;
		 query.QueryType = PropertyStandardQuery;
		 memset (buffer, 0, sizeof (buffer));

		 if ( pDeviceIoControl(hPhysicalDriveIOCTL, IOCTL_STORAGE_QUERY_PROPERTY,
				   & query,
				   sizeof (query),
				   & buffer,
				   sizeof (buffer),
				   & cbBytesReturned, NULL) )
		 {         
			 STORAGE_DEVICE_DESCRIPTOR * descrip = (STORAGE_DEVICE_DESCRIPTOR *) & buffer;
			 // append hexserial
			 ptr=&buffer[descrip->SerialNumberOffset];
			 if (*ptr!=0 && *ptr!=' ') {
				 if (sSerial) strcat_s(sSerial,len,ptr);
				 //DEBUGprintf(("Disk %d  serial: %s\n", drive,&buffer[descrip->SerialNumberOffset]));
				 // just use the hash on the hex serialnumber to get a unique (and short) id
				 serial += Utils::Str2Hash(&buffer[descrip->SerialNumberOffset]);  // can be multiple
			 }
		 }
		 pCloseHandle (hPhysicalDriveIOCTL);
	   }
   }
   memset(driveformat,0,sizeof(driveformat));	// clear visible format name
   //DEBUGprintf(("Disk %08x  serial: %s\n", serial,sSerial));
PROT_END
   return serial;
}

DWORD GetDriveSerialNumber(char *sSerial)
{
PROT_BEGIN
	if (!gHaveSerial)
	{
		if (pDeviceIoControl==0 || pCreateFileA==0 || pCloseHandle==0) {
			DriveSerial=0;
		} else {
			DriveSerial = ReadPhysicalDriveInNTWithZeroRights(sDriveSerial,250);
			gHaveSerial = true;
		}
	} 
	if (sSerial)	strcpy(sSerial,sDriveSerial);
PROT_END
	return DriveSerial;
}
