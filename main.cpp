
#define NOMINMAX
#include <windows.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <thread>
#include "offsets.h"
using namespace std;

#define MAXIMUM_KEY 0xFE
#define MINIMUM_KEY 0x1

bool IsWritableAddress(void* address)
{
    MEMORY_BASIC_INFORMATION mbi = {};
    if (VirtualQuery(address, &mbi, sizeof(mbi)))
    {
        DWORD protect = mbi.Protect;

        // Allow readable memory pages (writable or not), but still skip noaccess/guard
        if (!(protect & (PAGE_NOACCESS | PAGE_GUARD)))
        {
            return true;
        }
    }
    return false;
}


//Global Variables
bool terminate_Console_Thread = false;
bool terminate_addressUpdater_Thread = false;
bool Exit = false;
string userInput;

//Cheat Global Variables
float* Health_Taken = nullptr;
float* Hunger = nullptr;
float* Thirst = nullptr;
float* XCoord = nullptr;
float* YCoord = nullptr;
float* ZCoord = nullptr;
float* XWayPCoord = nullptr;
float* YWayPCoord = nullptr;
float* ZWayPCoord = nullptr;
float* LookDegree = nullptr;
float lastYCoord;
float flySpeed = 5.0; //Default Value
bool godMode = false;
bool fly = false;

//Keybiiiiiind Variablesssssssss ( 0 Means No keybind )
int restoreKeybind = 0;
int full_restoreKeybind = 0;
int godKeybind = 0;
int waypoint_tpKeybind = 0;
int flyKeybind = 0;
int exitKeybind = 0;

//Basic Functions
static void Bind(int key, string module)
{
    if (module == "restore")
        restoreKeybind = key;

    else if (module == "full_restoreKeybind")
        full_restoreKeybind = key;

    else if (module == "god")
        godKeybind = key;

    else if (module == "exit")
        exitKeybind = key;

    else if (module == "waypoint_tp")
        waypoint_tpKeybind = key;

    else if (module == "fly")
        flyKeybind = key;

    else {
        cout << "Invalid Module Name!\n";
    }

}
static void Unbind(string module)
{
    if (module == "restore")
    {
        restoreKeybind = 0;
        cout << "Unbinded" << module << endl;
    }

    else if (module == "full_restoreKeybind")
    {
        full_restoreKeybind = 0;
        cout << "Unbinded" << module << endl;
    }

    else if (module == "god")
    {
        godKeybind = 0;
        cout << "Unbinded" << module << endl;
    }

    else if (module == "exit")
    {
        exitKeybind = 0;
        cout << "Unbinded" << module << endl;
    }

    else if (module == "waypoint_tp")
    {
        waypoint_tpKeybind = 0;
        cout << "Unbinded" << module << endl;
    }

    else if (module == "fly")
    {
        flyKeybind = 0;
        cout << "Unbinded" << module << endl;
    }

    else {
        cout << "Invalid Module Name!\n";
    }
}
void addressUpdater()
{
    while (!terminate_addressUpdater_Thread)
    {
        if (Get::ThirstAddress() != nullptr)
        {
            Health_Taken = Get::DamageTakenAddress();
            Hunger = Get::HungerAddress();
            Thirst = Get::ThirstAddress();
            XCoord = Get::XCoordAddress();
            YCoord = Get::YCoordAddress();
            ZCoord = Get::ZCoordAddress();
            LookDegree = Get::PlayerLookDegreeAddress();
            XWayPCoord = Get::XWayPCoordAddress();
            YWayPCoord = Get::YWayPCoordAddress();
            ZWayPCoord = Get::ZWayPCoordAddress();
        }

        Sleep(10);
    }
}
int WaitAndReturnKeyClick()
{
    while (true)
    {
        for (int key = MINIMUM_KEY; key < MAXIMUM_KEY; key++)
        {
            if (GetAsyncKeyState(key) & 0x8000) {
                cout << "\nKey Selected!\n";
                return key;
            }
        }
        Sleep(15);
    }
}

//Cheat Functions
void RestoreThirstAndHunger()
{
    if (Get::ThirstAddress() != nullptr)
    {
        *Hunger = 100.0f;
        *Thirst = 100.0f;
        cout << "Restored Hunger and Thirst\n";
    } else { cout << "Not In A Game!\n"; }
}
void RestoreAll()
{
    if (Get::ThirstAddress() != nullptr)
    {
        *Hunger = 100.0f;
        *Thirst = 100.0f;
        *Health_Taken = 0.0f;
        cout << "Restored Hunger, Health, and Thirst\n";
    } else { cout << "Not In A Game!\n"; }
}
void ToggleGodMode()
{
    if (Get::ThirstAddress() != nullptr)
    {
        godMode = !godMode;
        if (godMode == true)
            cout << "God Mode Enabled\n";
        else
            cout << "God Mode Disabled\n";
    } else { cout << "Not In A Game, God Mod Not Toggled\n"; }
}
void ToggleFly()
{
    if (Get::PlayerLookDegreeAddress() != nullptr)
    {
        fly = !fly;
        lastYCoord = *YCoord;
    }
    else { cout << "Not In A Game\n"; }
}
void TeleportForward(float distance)
{
    float yaw = *LookDegree;
    float radians = yaw * (3.14159265f / 180.0f);
    *XCoord += cosf(radians) * distance;
    *ZCoord += sinf(radians) * distance;
}
void TeleportBackward(float distance)
{
    float yaw = *LookDegree;
    float radians = yaw * (3.14159265f / 180.0f);
    *XCoord -= cosf(radians) * distance;
    *ZCoord -= sinf(radians) * distance;
}
void TeleportRight(float distance)
{
    float yaw = *LookDegree + 90.0f;
    float radians = yaw * (3.14159265f / 180.0f);
    *XCoord += cosf(radians) * distance;
    *ZCoord += sinf(radians) * distance;
}
void TeleportLeft(float distance)
{
    float yaw = *LookDegree - 90.0f;
    float radians = yaw * (3.14159265f / 180.0f);
    *XCoord += cosf(radians) * distance;
    *ZCoord += sinf(radians) * distance;
}
void TeleportUp(float distance)
{
    *YCoord += distance * 2;
}
void TeleportDown(float distance)
{
    *YCoord -= distance;
}
void TpToWayPoint()
{
    if (Get::ThirstAddress() != nullptr)
    {
        *XCoord = *XWayPCoord;
        *YCoord = *YWayPCoord + 200.0f; //Prevents Cl-cl-clipping ( every cheaters bane )
        *ZCoord = *ZWayPCoord;
        cout << "Teleported To WayPoint\n";
    } else { cout << "Not In A Game!\n"; }
}

//Utility Functions
void BindModule()
{
    if (Get::ThirstAddress() != nullptr)
    {
        string module;
        cout << "\nEnter Module Name: ";
        cin >> module;
        cout << "\n";
        cout << "\nPress Key You Want To Bind With...\n";
        Sleep(2000);
        int Key = WaitAndReturnKeyClick();
        Bind(Key, module);
    } else { cout << "Not In A Game!\n"; }
}
void UnbindModule()
{
    if (Get::ThirstAddress() != nullptr)
    {
        string module;
        cout << "\nEnter Module Name: ";
        cin >> module;
        cout << "\n";
        Unbind(module);
    } else { cout << "Not In A Game!\n"; }
}




void ConsoleThread()
{

    //Keybinds are just handled in Hcack thread
    while (!terminate_Console_Thread) {
        cin >> userInput;

        if (userInput == "/help")
        {
            cout << "\n";
            cout << "/restore - Restores Hunger And Thirst To Full\n";
            cout << "/full_restore - Restores Hunger, Thirst, and Health To Full\n";
            cout << "/waypoint_tp - Teleports you to your last Way Point\n";
            cout << "/god - Toggles God Mode So You Can't Die\n";
            cout << "/fly - toggles fly\n";
            cout << "/bind - Binds a Key to a Module\n";
            cout << "/unbind - Unbinds a Module\n";
            cout << "/exit - Closes The Console And Stops Cheats\n";
            cout << "\n";
        }
        
        else if (userInput == "/restore")
        {
            RestoreThirstAndHunger();
        }

        else if (userInput == "/full_restore")
        {
            RestoreAll();
        }

        else if (userInput == "/god")
        {
            ToggleGodMode();
        }

        else if (userInput == "/waypoint_tp")
        {
            TpToWayPoint();
        }
        
        else if (userInput == "/bind")
        {
            BindModule();
        }

        else if (userInput == "/unbind")
        {
            UnbindModule();
        }

        else if (userInput == "/fly")
        {
            ToggleFly();
        }

        else if (userInput == "/fly_speed")
        {
            
            cout << "\nEnter Number For Fly Speed (Default is 5): ";
            cin >> flySpeed;
            if (std::cin.fail()) {
                std::cout << "Invalid input!\n";
                std::cin.clear(); // Clear error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard bad input
            }
            cout << "\n";
            

        }

        else if (userInput == "/exit")
        {
            Exit = true;
        }

        else {
            cout << "Invalid Command\n";
        }

        Sleep(20);
    }
}


DWORD WINAPI HackThread(LPVOID lpParam)
{

    //Creates console and allows output or whatever
    AllocConsole();
    FILE* fOut;
    freopen_s(&fOut, "CONOUT$", "w", stdout);
    FILE* fIn;
    freopen_s(&fIn, "CONIN$", "r", stdin);
    std::cout << "[+] Console attached!\n";


    //Thread Handler
    thread ConsoleThread_Thread(ConsoleThread);
    thread addressUpdater_Thread(addressUpdater);
    ConsoleThread_Thread.detach();
    addressUpdater_Thread.detach();

    cout << "Type '/help' to show list of commands -  Cheat Made by Elijah, JaltyisSalty on Discord\n";
    cout << "\n";

    while (!Exit)
    {
        //Cheat Thread
        if (GetAsyncKeyState(godKeybind) & 1)
        {
            ToggleGodMode();
        }


        if (GetAsyncKeyState(restoreKeybind) & 1)
        {
            RestoreThirstAndHunger();
        }

        if (GetAsyncKeyState(full_restoreKeybind) & 1)
        {
            RestoreAll();
        }

        if (GetAsyncKeyState(exitKeybind) & 1)
        {
            Exit = true;
        }

        if (GetAsyncKeyState(waypoint_tpKeybind) & 1)
        {
            TpToWayPoint();
        }

        if (GetAsyncKeyState(flyKeybind) & 1)
        {
            ToggleFly();
        }

        if (godMode == true)
        {
            if (Get::ThirstAddress() != nullptr)
            {
                *Hunger = 100.0f;
                *Thirst = 100.0f;
                *Health_Taken = -9999.0f;
            } else { cout << "Not In A Game\n"; }
        }

        if (fly == true)
        {

            if (Get::PlayerLookDegreeAddress() != nullptr)
            {
                *Health_Taken = -99999.0f;
                if (GetAsyncKeyState(0x57) & 0x8000) // W
                    TeleportForward(flySpeed);

                if (GetAsyncKeyState(0x53) & 0x8000) // S
                    TeleportBackward(flySpeed);

                if (GetAsyncKeyState(0x41) & 0x8000) // A
                    TeleportLeft(flySpeed);

                if (GetAsyncKeyState(0x44) & 0x8000) // D
                    TeleportRight(flySpeed);

                if (GetAsyncKeyState(0x11) & 0x8000) // Ctrl
                {
                    TeleportDown(flySpeed);
                    lastYCoord = *YCoord;
                }

                else if (GetAsyncKeyState(0x20) & 0x8000) // Space
                {
                    TeleportUp(flySpeed);
                    lastYCoord = *YCoord;

                }
                else {
                    *YCoord = lastYCoord; // Freeze Y when not pressing Ctrl or Space
                }
            }
        }

        Sleep(1);
    }

    //Closes and Cleans Things Up
    terminate_Console_Thread = true;
    terminate_addressUpdater_Thread = true;
    HWND hwnd = GetConsoleWindow();
    FreeConsole();
    if (hwnd != nullptr) {
        PostMessage(hwnd, WM_CLOSE, 0, 0); 
    }

    HMODULE hModule = (HMODULE)lpParam;
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hmodule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hmodule);
        CreateThread(nullptr, 0, HackThread, nullptr, 0, nullptr);
    }
    return TRUE;
}