#include "WindowsRenderTarget.h"

XRender::WindowsRenderTarget::WindowsRenderTarget(const std::string& name): RenderTarget(name){}

XRender::WindowsRenderTarget::~WindowsRenderTarget(){}

void XRender::WindowsRenderTarget::OnPresent(const Color *frame_buffer)
{

}

void XRender::WindowsRenderTarget::OnInit()
{

}

void XRender::WindowsRenderTarget::RegisterWindowClass()
{

}

void XRender::WindowsRenderTarget::CreateWindows()
{

}

void XRender::WindowsRenderTarget::TryRegisterWindowsClassEx()
{
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(sizeof(WNDCLASSEX));
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = &WindowsRenderTarget::WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    
}