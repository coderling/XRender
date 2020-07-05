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
        void RegisterWindowClass();
        void CreateWindows();
        void TryRegisterWindowsClassEx();

        static LRESULT CALLBACK WindowProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );

    private:
        HWND hWnd;

    };
}