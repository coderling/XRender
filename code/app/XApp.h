#pragma once

#include<SDL.h>

#include<string>
#include<queue>
#include<list>
#include "code/core/primitive/Vertex.h"
#include "code/core/basic/Camera.h"
#include "code/core/Render/RenderContext.h"
#include "code/core/basic/Behavior.h"

class XApp;
extern XApp* pAppInstance;

class XApp
{
public:
    static XApp* CreateAppSingleton(std::string title, int w, int h, Uint32 initOpt, Uint32 winOpt, Uint32 renderOpt)
    {
        if(pAppInstance == nullptr)
        {
            pAppInstance = new XApp(title, w, h, initOpt, winOpt, renderOpt);
        }
        return pAppInstance;
    }
    
    ~XApp();

    void SetCameraLookAt(const Vector3& pos, const Vector3& up, const Vector3& lookPos);

    Camera& GetMainCamera();
    SDL_Window* GetWindowHandler();
    SDL_Surface* GetRenderSurface();
    void GetWindowWH(int* w, int* h);

    void AppLoop();
    void Terminate();

    void AddBehavior(Behavior& behavior);
    void RemoveBehavior(Behavior& behavior);
    //rener func
    void PushVerteices(Vertex* pVerteices, Uint32 vert_size, Uint32* pInedxData, int index_count);
protected:
    SDL_Window* m_pWindow;
    RenderContext m_renderContext;
    SDL_Surface* m_windowSurface;


    XApp(std::string title, int w, int h, Uint32 initOpt, Uint32 winOpt, Uint32 renderOpt);
private:
    bool m_initStatus;
    bool m_runing;
    int m_screenW;
    int m_screenH;
    Uint32 m_initOptions;
    Uint32 m_windowOptions;
    Uint32 m_renderOptions;

    Camera m_camera;
    SDL_Event m_sdlEvent;
    std::queue<SDL_Event> m_frameEvents;
    
    Uint32 m_drawColor;

    std::vector<Behavior> m_behaviors;    

    //渲染数据，采用定点索引方式进行数据输入
    Vertex* m_pVerteices;
    Uint32 m_vertex_count;
    Uint32* m_pIndexData;
    Uint32 m_index_count;

    virtual void SDLEnvInit(std::string title, int w, int h, Uint32 initOpt, Uint32 winOpt, Uint32 renderOpt);
    void Release();
    void CatchInput();
    void UpdateLogic();
    void Render();
};

