#include <Windows.h>
#include <iostream>
#include <string>
#include <filesystem>
using namespace std;

int main() 

{

    // Get the handle of the console window
    HWND hwnd = GetConsoleWindow();

    // Set the window title
    SetWindowText(hwnd, "RUT BSOD Fix Version 1.0");


    BOOL isAdmin = FALSE;
    DWORD errorCode = ERROR_SUCCESS;
    PSID adminSid = NULL;
    SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;

    // Check if the current process is running with administrator privileges
    if (AllocateAndInitializeSid(&ntAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &adminSid)) {
        CheckTokenMembership(NULL, adminSid, &isAdmin);
        FreeSid(adminSid);
    }

    if (!isAdmin) {
        // The program is not running with administrator privileges
        cout << "This program requires administrator privileges. Please run it as an administrator." << endl;
        system("pause");
        return 0;
    }

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    cout << "[!] MAKE SURE ALL 4 ANTIVIRUS OPTIONS ARE DISABLED BEFORE RUNNING THIS PROGRAM!\n";
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    system("pause");
    system("cls");

    // Disable memory integrity in core isolation details found in windows defender (using registry editor)
    system("REG ADD \"HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\DeviceGuard\" /v \"EnableVirtualizationBasedSecurity\" /t REG_DWORD /d 0 /f > nul");
    cout << "\033[32m[+]\033[0m Core Isolation was disabled.\n";
    Sleep(1000);

    // Find these windows services and change the startup type to disabled
    SC_HANDLE schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (!schSCManager) {
        cout << "\033[31m[-]\033[0m Error: Could not open Service Control Manager. Run as administrator.";
        return 1;
    }
    SC_HANDLE schService = OpenService(schSCManager, "MEIx64", SERVICE_CHANGE_CONFIG);
    if (schService) {
        ChangeServiceConfig(schService, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        CloseServiceHandle(schService);
    }
    schService = OpenService(schSCManager, "IntelPMT", SERVICE_CHANGE_CONFIG);
    if (schService) {
        ChangeServiceConfig(schService, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        CloseServiceHandle(schService);
    }
    schService = OpenService(schSCManager, "Intel(R) PROSet", SERVICE_CHANGE_CONFIG);
    if (schService) {
        ChangeServiceConfig(schService, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        CloseServiceHandle(schService);
    }
    schService = OpenService(schSCManager, "jhi_service", SERVICE_CHANGE_CONFIG);
    if (schService) {
        ChangeServiceConfig(schService, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        CloseServiceHandle(schService);
    }
    schService = OpenService(schSCManager, "LMS", SERVICE_CHANGE_CONFIG);
    if (schService) {
        ChangeServiceConfig(schService, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        CloseServiceHandle(schService);
    }
    schService = OpenService(schSCManager, "Telemetry", SERVICE_CHANGE_CONFIG);
    if (schService) {
        ChangeServiceConfig(schService, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        CloseServiceHandle(schService);
    }
    CloseServiceHandle(schSCManager);
    cout << "\033[32m[+]\033[0m Services have been disabled.\n";
    Sleep(1000);

    system("REG ADD \"HKEY_LOCAL_MACHINE\\SOFTWARE\\Policies\\Microsoft\\Windows Defender\" /v \"DisableAntiSpyware\" /t REG_DWORD /d 1 /f > nul");
    system("REG ADD \"HKEY_LOCAL_MACHINE\\SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection\" /v \"DisableBehaviorMonitoring\" /t REG_DWORD /d 1 /f > nul");
    system("REG ADD \"HKEY_LOCAL_MACHINE\\SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection\" /v \"DisableOnAccessProtection\" /t REG_DWORD /d 1 /f > nul");
    system("REG ADD \"HKEY_LOCAL_MACHINE\\SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection\" /v \"DisableScanOnRealtimeEnable\" /t REG_DWORD /d 1 /f > nul");
    cout << "\033[32m[+]\033[0m Antivirus was disabled. \n";
    Sleep(1000);

        cout << "\033[32m[+]\033[0m All changes complete, please restart your PC to apply the changes.\n";

        system("pause");

        return 0;
    }