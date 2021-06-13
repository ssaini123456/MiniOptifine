#include "Loader.h"

bool g_isToggled = false;

void init() {
    GameUtil* l;
    uint32_t process_id = l->getGameProcessId(L"Minecraft.Windows.exe");
    uintptr_t gameId = l->getGameModule(process_id);
    HANDLE process_handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, process_id);
    std::cout << "Checking if game window is present..." << std::endl;

    // check if the minecraft window is even open
    HWND gameWindow = FindWindow(NULL, L"Minecraft");
    if (!gameWindow) {
        system("color 4");
        std::cout << "!!!! Game window not found. Please open minceraft and try again.";
        return;
    }
    else {
        system("color b");
        std::cout << "[~] Game window found! To toggle optifine zoom press C." << std::endl;
    }

    // k, begin writing to the ptr
    uintptr_t optifineZoombaseAddress = gameId + 0x03F58580;
    uintptr_t __optifineZoomPtr = l->findAddressFromPointer(process_handle, optifineZoombaseAddress, { 0x28, 0xFC8, 0x8, 0xC8, 0x170, 0x128, 0x18 });
    float zoomVal;

    while (true) {
        if (GetAsyncKeyState('C') & 0x8000) {
            if (g_isToggled == false) {
                zoomVal = 10; // max zoom
                WriteProcessMemory(process_handle, (unsigned int*)__optifineZoomPtr, &zoomVal, sizeof(zoomVal), nullptr);
                g_isToggled = true;
                Sleep(100);
            }
        }

        if(GetAsyncKeyState('C') & 0x8000) {
            // write defaults
            if (g_isToggled == true) {
                zoomVal = 60;
                WriteProcessMemory(process_handle, (unsigned int*)__optifineZoomPtr, &zoomVal, sizeof(zoomVal), nullptr);
                g_isToggled = false;
                Sleep(100);
            }
            
        }    
    }

}

int main() {
    init();
}