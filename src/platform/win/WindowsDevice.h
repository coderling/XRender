#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>

#include "../../RenderDevice.h"

namespace XRender
{
    class WindowsDevice : public RenderDevice
    {
    public:
        WindowsDevice(const std::string& name);
        ~WindowsDevice() override;
        void OnPresent(const RenderContext* context) override;
    private:
        void OnInit() override;
        void OnUpdate() override;
        void CreateWindows();
        void CreateMemoryDevieceContext();
        void TryRegisterWindowsClassEx();
        void DestroyWindowData();
        void BitBltMemoryDC();
        static LRESULT CALLBACK WindowProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );

    private:
        wchar_t* lname;
        HWND hWnd;
        HDC memory_dc;
        unsigned char* memory_dc_buffer;
    };
}