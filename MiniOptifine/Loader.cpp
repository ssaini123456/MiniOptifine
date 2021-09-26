#include "Loader.h"

bool g_isToggled = false;
std::string bootLogo = R"(
           __ __ __      __ __ __ 
          /_ /_ /_ |    /_ /_ /_ |
  ___  __ _| || || |_ __ | || || |
 / __|/ _` | || || | '_ \| || || |
 \__ \ (_| | || || | | | | || || |
 |___/\__,_|_||_||_|_| |_|_||_||_|
                                  
@github: https://github.com/sa111n111 
@twitter: https://twitter.com/sa111n111            
)";

void init() {
    GameUtil* l;
    float zoomVal = 0;
    float defaultFov = 0;
    uint32_t process_id = l->getGameProcessId();
    uintptr_t gameId = l->getGameModule(process_id);
    HANDLE process_handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, process_id);
    uintptr_t optifineZoombaseAddress = gameId + 0x040858C8;
    uintptr_t __optifineZoomPtr = l->findAddressFromPointer(process_handle, optifineZoombaseAddress, { 0x28, 0xCC0, 0x08, 0x50, 0x50, 0x128, 0x18 });


    std::cout << bootLogo << "\n";
    std::cout << "Checking if game window is present...\n\n";
    // check if the minecraft window is even open
    HWND gameWindow = FindWindow(NULL, L"Minecraft");
    if (!gameWindow) {
        system("color 4");
        std::cout << "!!!! Game window not found. Please open minceraft and try again.\n\n";
        return;
    }
    else {
        system("color b");
        std::cout << "[~] Game window found! To toggle optifine zoom press C.\n";
    }
    ReadProcessMemory(process_handle, (unsigned int*)__optifineZoomPtr, &defaultFov, sizeof(defaultFov), nullptr); /* copy what we read from the process to the defaultFov buffer */

    while (true) {
        Sleep(100);
        if (GetAsyncKeyState('C') & 0x8000) {
            g_isToggled = !g_isToggled;
            
            if (g_isToggled == true) {
                zoomVal = 11;
                WriteProcessMemory(process_handle, (unsigned int*)__optifineZoomPtr, &zoomVal, sizeof(zoomVal), nullptr);
                
            } else {
                //std::cout << std::dec << defaultFov << "\n";
                WriteProcessMemory(process_handle, (unsigned int*)__optifineZoomPtr, &defaultFov, sizeof(defaultFov), nullptr);
            }
        }
    }

}

int main() {
    init();
}