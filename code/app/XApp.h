#pragma once

#include<SDL.h>

#include<string>
#include<queue>
#include<list>
#include "code/core/primitive/Vertex.h"
#include "code/core/basic/Camera.h"
#include "code/core/Render/RenderContext.h"
#include "code/core/basic/Object.h"
#include "code/core/Render/Renderer.h"

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

    void AddObject(Object* object);
    void RemoveObject(Object* object);
    void SetRenderMode(XRENDER_MODE mode);
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

    std::vector<Object*> m_objects;    

    XRENDER_MODE m_eRenderMode;

    virtual void SDLEnvInit(std::string title, int w, int h, Uint32 initOpt, Uint32 winOpt, Uint32 renderOpt);
    void Release();
    void CatchInput();
    void UpdateLogic();
    void Render();
};

