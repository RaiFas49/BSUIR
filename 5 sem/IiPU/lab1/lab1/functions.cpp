#include "functions.h"

void OutDevices()
{
	HDEVINFO DeviceInfoSet;
	HDEVINFO NewDeviceInfoSet;
	DWORD Err;
	// Create a device information set that will be the container for 
	// the device interfaces.
	//GUID MyGuid = GUID_DEVCLASS_PORTS;
	DeviceInfoSet = SetupDiCreateDeviceInfoList(NULL, NULL);
	if (DeviceInfoSet == INVALID_HANDLE_VALUE) {
		Err = GetLastError();
		printf("SetupDiCreateDeviceInfoList failed: %lx.\n", Err);
		return;
	}
	// Retrieve the device information set for the interface class.
	NewDeviceInfoSet = ::SetupDiGetClassDevsEx(NULL, NULL, NULL,/*DIGCF_PRESENT |*/ DIGCF_ALLCLASSES, DeviceInfoSet, NULL, NULL);
	if (NewDeviceInfoSet == INVALID_HANDLE_VALUE)
	{
		Err = GetLastError();
		printf("SetupDiGetClassDevsEx failed: %lx.\n", Err);
		return;
	}
	SP_DEVINFO_DATA DeviceInfoData;
	SP_DEVICE_INTERFACE_DATA DeviceInterfaceData;
	SP_DEVINFO_LIST_DETAIL_DATA  DeviceInfoSetDetailData;
	TCHAR buf[1024] = L"";
	DEVPROPTYPE dpt = 0;
	DWORD count = 0;
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	DeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
	DeviceInfoSetDetailData.cbSize = sizeof(SP_DEVINFO_LIST_DETAIL_DATA);
	BOOL b0 = SetupDiGetDeviceInfoListDetail(
		NewDeviceInfoSet,
		&DeviceInfoSetDetailData
	);
	int i = 0;
	TCHAR ClassDescription[512];
	TCHAR DeviceInstanceId[512];
	DWORD RequiredSize;
	while (SetupDiEnumDeviceInfo(NewDeviceInfoSet, i++, &DeviceInfoData))
	{
		//Dev class 
		BOOL b = SetupDiGetClassDescription(&DeviceInfoData.ClassGuid, ClassDescription, 512, &RequiredSize);
		//Path
		b = SetupDiGetDeviceInstanceId(NewDeviceInfoSet, &DeviceInfoData, DeviceInstanceId, 512, NULL);
		std::wstring wStr = DeviceInstanceId;
		std::string s_temp = std::string(wStr.begin(), wStr.end());
		if (s_temp.substr(0, 3) == "PCI")
		{
			b = SetupDiGetDeviceProperty(NewDeviceInfoSet, &DeviceInfoData, &DEVPKEY_Device_DeviceDesc, &dpt, (PBYTE)buf, 1000, NULL, 0);
			if (b == FALSE)
				return;
			else wprintf(L"%s\n", buf);
			std::cout << s_temp << std::endl;
			int j = 0;
			while (s_temp.substr(j, 3) != "VEN")
				++j;
			j += 4 ;
			std::cout << "Vendor ID: ";
			while (s_temp[j] != '&')
			{
				std::cout << s_temp[j];
				++j;
			}
			j += 5;
			std::cout << "\tDevice ID: ";
			while (s_temp[j] != '&')
			{
				std::cout << s_temp[j];
				++j;
			}
			std::cout << "\n" << std::endl;
		}
	}
	SetupDiDestroyDeviceInfoList(DeviceInfoSet);
}