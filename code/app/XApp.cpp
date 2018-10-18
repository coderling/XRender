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

    m_renderContext.Init(w, h);

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
        Render();
        SDL_BlitSurface(m_renderContext.GetSurface(), NULL, m_windowSurface, NULL);
        SDL_UpdateWindowSurface(m_pWindow);
        SDL_Delay(50);
    }

    Release();
}

void XApp::Render()
{
    if(m_pVerteices == nullptr
    || m_pIndexData == nullptr)
    {
        return;
    }

    //变换
    Matrix4x3 mvp = m_camera.GetVPMatrix();
    for(int i = 0; i < m_index_count; i++)
    {
        int ind = *(m_pIndexData + i);
        Vertex vert = *(m_pVerteices + ind);
        //变换
        Vector3 vec = m_camera.DoVertexTranslate(vert.pos);
        
        std::cout << " index: " << i << " vec: " << vec.x << " " << vec.y << " " << vec.z << std::endl;
    }
}

void XApp::PushVerteices(Vertex* pVerteices, Uint32 vert_size, Uint32* pInedxData, int index_count)
{
    m_pVerteices = pVerteices;
    m_vertex_count = vert_size;
    m_pIndexData = pInedxData;
    m_index_count = index_count;
}

void XApp::UpdateLogic()
{
    m_renderContext.Lock();

    // beHavior update
    for(auto it = m_behaviors.begin(); it != m_behaviors.end(); ++it)
    {
        it->Update();
    }

    m_renderContext.UnLock();
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
    m_renderContext.Releae();
    SDL_Quit();
}


XApp::~XApp() {
    m_pWindow = nullptr;
}

void XApp::SetCameraLookAt(const Vector3& pos, const Vector3& up, const Vector3& lookPos)
{
    m_camera.Init(m_screenW, m_screenH, pos, up, lookPos);
}

Camera& XApp::GetMainCamera()
{
    return m_camera;
}

SDL_Window* XApp::GetWindowHandler()
{
    return m_pWindow;
}

SDL_Surface* XApp::GetRenderSurface()
{
    return m_renderContext.GetSurface();
}

void XApp::GetWindowWH(int* w, int* h)
{
    w = &m_screenW; h = &m_screenH;
}

//App全局句柄
XApp* pAppInstance;
