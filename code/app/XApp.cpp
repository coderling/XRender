#include<SDL.h>
#include<iostream>

#include "XApp.h"
#include "code/core/Render/Shader.h"
#include "code/core/Render/Renderer.h"
#include "code/core/Render/Rasterization.h"
#include "code/core/primitive/PrimitiveUtil.h"

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

void XApp::AddObject(Object*  object)
{
    if(!object->IsEnable())
    {
        m_objects.push_back(object);
        object->Start();
        object->Enable();
        object->StartBehaviors();
    }
}

void XApp::RemoveObject(Object*  object)
{
    for(auto it = m_objects.begin(); it != m_objects.end(); ++it)
    {
        if((*object) == *(*it))
        {
            (*it)->Disable();
            m_objects.erase(it);
            break;
        }
    }
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
    m_renderContext.Clear();
    m_renderContext.Lock();
    //变换
    Matrix4x3 vp = m_camera.GetVPMatrix();
    Matrix4x3 vmat = m_camera.GetCameraMatrix();
    for(auto ob : m_objects)
    {   
        auto mesh = ob->GetMesh();
        auto verteies = mesh->GetVerteies();
        int *pIndeies = nullptr;
        auto count = mesh->GetIndeies(pIndeies);
        int triangleCount = count / 3;
        auto material = mesh->GetMat();
        auto shader = material.GetShader();
        
        shader->PreVert(ob->ModelMatrix(), vp);

        VertInput vin;
        std::vector<VertOut> fragments;
        std::vector<Trapezoidal_t> traps;
        
        for(int i = 0; i < triangleCount; ++i)
        {
            auto tri = verteies + i;
            VertOut points[3];
            //简单检查三角形是否在cvv内，只要一个点在cvv内都不做裁剪
            int inc = 0;
            for(int j = 0; j < 3; j++)
            {
                auto ver = *(tri + j);
                vin.pos = ver.pos;
                vin.color = ver.color;
                points[j] = shader->Vert(vin);
                float w = (ver.pos * vmat).z;
                //这里有点不好理解，其实是因为计算出来的变换矩阵公式w = z, z 为摄像机空间下的z值
                if(Check_CVV(points[j].pos, w))
                {
                    ++inc;
                }
                IdentityToDevice(m_renderContext, points[j].pos, w);
            }

            if(inc > 0)
            {
                traps.empty();
                DivisionTriangle(points[0], points[1], points[2], traps);
                fragments.empty();
                for(int t = 0; t < traps.size(); ++t)
                {
                    ScanLineTrapezoidal(m_renderContext, traps[t], fragments);
                    for(int f = 0; f < fragments.size(); ++f)
                    {
                        Color c = shader->Frag(fragments[f]);
                        m_renderContext.DrawPixel(fragments[f].pos.x, fragments[f].pos.y, fragments[f].color);
                    }
                }
            }
            else
            {
                //std::cout << "tri out: " << points[0].pos.ToString() << points[1].pos.ToString() << points[2].pos.ToString() << std::endl;
            }
        }
    }
    m_renderContext.UnLock();
}

void XApp::UpdateLogic()
{
    m_renderContext.Lock();

    // beHavior update
    for(auto it = m_objects.begin(); it != m_objects.end(); ++it)
    {
        (*it)->UpdateBehaviors();
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
            std::cout <<"keyDown... " <<m_sdlEvent.key.keysym.sym <<std::endl;
            if(m_sdlEvent.key.keysym.sym == SDLK_ESCAPE)
            {
                this->Terminate();
            }
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
