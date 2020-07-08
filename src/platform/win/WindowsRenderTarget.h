#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>

#include "../../RenderTarget.h"

namespace XRender
{
    class WindowsRenderTarget : public RenderTarget
    {
    public:
        WindowsRenderTarget(const std::string& name);
        ~WindowsRenderTarget() override;
        void OnPresent(const Color* frame_buffer) override;
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