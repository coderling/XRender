#include <cassert>
#include <strsafe.h>

#include "WindowsRenderTarget.h"

void ErrorExit(LPTSTR lpszFunction) 
{ 
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw); 
}

void ShowError()
{
    if(!GetProcessId(NULL))
        ErrorExit(TEXT("GetProcessId"));
}

XRender::WindowsRenderTarget::WindowsRenderTarget(const std::string& name): RenderTarget(name), hWnd(NULL), memory_dc(NULL), memory_dc_buffer(NULL)
{
    auto c_str = name.c_str();
	int len = MultiByteToWideChar(CP_ACP, 0, c_str, std::strlen(c_str), NULL, 0);
	lname = new wchar_t[len + 1];
	MultiByteToWideChar(CP_ACP, 0, c_str, strlen(c_str), lname, len);
	lname[len] = '\0';
}

XRender::WindowsRenderTarget::~WindowsRenderTarget()
{
    ShowWindow(hWnd, SW_HIDE);
    DestroyWindowData();
}

void XRender::WindowsRenderTarget::OnPresent(const RenderContext* context)
{
    auto frame_buffer = context->GetBuffer();
    uint32_t tcount = width * height;
    Color32 color;
    for(uint32_t index = 0; index < tcount; ++index)
    {
        ColorToColor32(frame_buffer[index], color);
        uint32_t buffer_index = index * 4;
        memory_dc_buffer[buffer_index + 0] = static_cast<unsigned char>(color.b);
        memory_dc_buffer[buffer_index + 1] = static_cast<unsigned char>(color.g);
        memory_dc_buffer[buffer_index + 2] = static_cast<unsigned char>(color.r);
    }

    BitBltMemoryDC();
}

void XRender::WindowsRenderTarget::OnUpdate()
{
    MSG message;
    while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}

void XRender::WindowsRenderTarget::BitBltMemoryDC()
{
    HDC window_dc = GetDC(hWnd);
    BitBlt(window_dc, 0, 0, width, height, memory_dc, 0, 0, SRCCOPY);
    ReleaseDC(hWnd, window_dc);
}

void XRender::WindowsRenderTarget::OnInit()
{
    TryRegisterWindowsClassEx();
    CreateWindows();
    CreateMemoryDevieceContext();
    ShowWindow(hWnd, SW_SHOW);
}

void XRender::WindowsRenderTarget::CreateWindows()
{
    this->hWnd = CreateWindow(name.c_str(),
                              name.c_str(),
                              WS_OVERLAPPEDWINDOW,
                              500,
                              500,
                              width,
                              height,
                              NULL,
                              NULL,
                              GetModuleHandle(NULL),
                              NULL);

    assert(this->hWnd != NULL);
}

void XRender::WindowsRenderTarget::CreateMemoryDevieceContext()
{
    HDC window_dc = GetDC(hWnd);
    memory_dc = CreateCompatibleDC(window_dc);
    ReleaseDC(hWnd, window_dc);

    HBITMAP new_bitmap = NULL;
    HBITMAP old_bitmap = NULL;

    BITMAPINFOHEADER bitmap_header;
    memset(&bitmap_header, 0, sizeof(BITMAPINFOHEADER));
    bitmap_header.biSize = sizeof(BITMAPINFOHEADER);
    bitmap_header.biWidth = width;
    bitmap_header.biHeight = -height;
    bitmap_header.biPlanes = 1;
    bitmap_header.biBitCount = 32;
    bitmap_header.biCompression = BI_RGB;

    new_bitmap = CreateDIBSection(memory_dc,
                                (BITMAPINFO *)&bitmap_header,
                                DIB_RGB_COLORS,
                                (void **)&memory_dc_buffer, NULL, 0);
    
    assert(new_bitmap != NULL);
    if (memory_dc_buffer == NULL)
    {
        ShowError();
    }

    old_bitmap = (HBITMAP)SelectObject(memory_dc, new_bitmap);
    if(old_bitmap != NULL)
    {
        DeleteObject(old_bitmap);
    }
}

void XRender::WindowsRenderTarget::TryRegisterWindowsClassEx()
{
    static bool is_register = false;
    if (is_register)
    {
        return;
    }
    WNDCLASS wc;

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = &WindowsRenderTarget::WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = _T(name.c_str());
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.lpszMenuName = NULL;
    const auto& atom = RegisterClass(&wc);
    if (atom == 0)
    {
        ShowError();
    }
    is_register = true;
}

void XRender::WindowsRenderTarget::DestroyWindowData()
{
    DeleteDC(memory_dc);
    DestroyWindow(hWnd);
}

LRESULT CALLBACK XRender::WindowsRenderTarget::WindowProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    return DefWindowProc(hwnd, message, wParam, lParam);
}