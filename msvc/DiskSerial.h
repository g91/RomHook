#ifndef DISKSERIAL_INCLUDE
#define DISKSERIAL_INCLUDE

#pragma warning(disable: 4996)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winioctl.h>
#include <stdio.h>
#include <string.h>

#pragma optimize( "", off )

#define FUNC_DeviceIoControl	0
#define FUNC_CreateFileA		1
#define FUNC_CloseHandle		2

extern DWORD   func_hashes[];
extern BOOL    gHaveSerial;
extern DWORD   DriveSerial;


typedef BOOL (WINAPI *tDeviceIoControl)(
  __in         HANDLE hDevice,
  __in         DWORD dwIoControlCode,
  __in_opt     LPVOID lpInBuffer,
  __in         DWORD nInBufferSize,
  __out_opt    LPVOID lpOutBuffer,
  __in         DWORD nOutBufferSize,
  __out_opt    LPDWORD lpBytesReturned,
  __inout_opt  LPOVERLAPPED lpOverlapped
);

typedef HANDLE (WINAPI* tCreateFileA)(
  __in      LPCTSTR lpFileName,
  __in      DWORD dwDesiredAccess,
  __in      DWORD dwShareMode,
  __in_opt  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  __in      DWORD dwCreationDisposition,
  __in      DWORD dwFlagsAndAttributes,
  __in_opt  HANDLE hTemplateFile
);

typedef BOOL (WINAPI* tCloseHandle)(
  __in  HANDLE hObject
);

typedef struct DEVICE_NUMBER {
  DEVICE_TYPE	DeviceType;
  ULONG			DeviceNumber;
  ULONG			PartitionNumber;
} DEVICE_NUMBER, *PDEVICE_NUMBER;

extern tDeviceIoControl pDeviceIoControl;
extern tCreateFileA		pCreateFileA;
extern tCloseHandle     pCloseHandle;

DWORD  GetDriveSerialNumber(char *sSerial=0);

#endif