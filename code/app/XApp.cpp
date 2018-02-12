#include<SDL.h>
#include<iostream>

#include "XApp.h"

XApp::XApp(std::string title, int w, int h, Uint32 initOpt, Uint32 winOpt, Uint32 renderOpt)
{
    SDLEnvInit(title, w, h, initOpt, winOpt, renderOpt);
}

//SDL环境初始化
void XApp::SDLEnvInit(std::string title, int w, int h, Uint32 initOpt, Uint32 winOpt, Uint32 renderOpt)
{
    m_initStatus = true;
    m_pWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h,
                                            winOpt);
                                            std::cout <<"SDL_CreateRenderer: finish int" <<SDL_GetError() <<std::endl;
    if(m_pWindow == nullptr)
    {
        std::cout <<"SDL_CreateWindow: " <<SDL_GetError() <<std::endl;
        m_initStatus = false;
        return;
    }

    /* just use blit mode to update window, no need t create a render
        if also create a render if will get error when SDL_GetWindowSurface()
    m_pRender = SDL_CreateRenderer(m_pWindow, -1,
                        renderOpt);
                        std::cout <<"SDL_CreateRenderer: finish int" <<SDL_GetError() <<std::endl;
    if(NULL == m_pRender)
    {
        std::cout <<"SDL_CreateRenderer: " <<SDL_GetError() <<std::endl;
        m_initStatus = false;
        return;
    }*/

    SDL_GetWindowSize(m_pWindow, &m_screenW, &m_screenH);
    m_windowSurface = SDL_GetWindowSurface(m_pWindow);
    while(m_windowSurface == nullptr)
    {
        m_windowSurface = SDL_GetWindowSurface(m_pWindow);
    }
    Uint32 rmask, gmask, bmask, amask;
    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif
    m_cacheSurface = SDL_CreateRGBSurface(0, m_screenW, m_screenH, 32, rmask, gmask, bmask, amask);

    std::cout <<"SDL_CreateRenderer: finish int" <<SDL_GetError() <<std::endl;
}

//app循环
void XApp::AppLoop()
{
    if(!m_initStatus)
    {
        return;
    }

    m_runing = true;
    
    while(m_runing)
    {
        //std::cout <<"GameRunning... " <<SDL_GetError() <<std::endl;
        CatchInput();
        UpdateLogic();
        SDL_BlitSurface(m_cacheSurface, NULL, m_windowSurface, NULL);
        SDL_UpdateWindowSurface(m_pWindow);
        SDL_Delay(50);
    }

    Release();
}

//参数不能是成员函数，必须是普通非成员函数
void XApp::AddUpdateLogic(Update_Func func)
{
    m_updateFuncList.push_back(func);
}

void XApp::RemoveUpdateLogic(Update_Func func)
{
    m_updateFuncList.remove(func);
}

void XApp::UpdateLogic()
{
     if(SDL_MUSTLOCK(m_cacheSurface))
    {
        SDL_LockSurface(m_cacheSurface);
    } 

    std::list<Update_Func>::iterator it;
    
    for(it = m_updateFuncList.begin(); it != m_updateFuncList.end(); ++it)
    {
        (*(*it))();
    }

    if(SDL_MUSTLOCK(m_cacheSurface))
    {
        SDL_UnlockSurface(m_cacheSurface);
    }
}

//获取输入
void XApp::CatchInput()
{
    m_frameEvents.empty();
    while(SDL_PollEvent(&m_sdlEvent))
    {
        if(m_sdlEvent.type == SDL_QUIT)
        {
            m_runing = false;
        }
        else if(m_sdlEvent.type == SDL_KEYDOWN)
        {
            std::cout <<"keyDown... " <<m_sdlEvent.key.keysym.scancode <<std::endl;
        }
        else if(m_sdlEvent.type == SDL_MOUSEBUTTONDOWN)
        {
            std::cout <<"mouse keydown... " <<SDL_GetError() <<std::endl;
        }
        m_frameEvents.push(m_sdlEvent);
    }
}

void XApp::Terminate()
{
    m_runing = false;
}

void XApp::Release()
{
    //SDL_DestroyRenderer(m_pRender);
    SDL_DestroyWindow(m_pWindow);
    SDL_FreeSurface(m_cacheSurface);
    SDL_Quit();
}


XApp::~XApp() {
    m_pWindow = nullptr;
    m_cacheSurface = nullptr;
}

SDL_Window* XApp::GetWindowHandler()
{
    return m_pWindow;
}

//获取用于绘制的surface，所有绘制操作都必须绘制到这个surface
//最后由XApp更新到窗口
SDL_Surface* XApp::GetRenderSurface()
{
    return m_cacheSurface;
}

void XApp::GetWindowWH(int* w, int* h)
{
    w = &m_screenW; h = &m_screenH;
}

void XApp::SetDrawColor(Uint8 r, Uint8 g, Uint8 b)
{
    m_drawColor = SDL_MapRGBA(m_cacheSurface->format, r, g, b, 255);
}

Uint32 XApp::GetDrawColor()
{
    return m_drawColor;
}

//App全局句柄
XApp* pAppInstance;
