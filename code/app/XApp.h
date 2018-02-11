#pragma once

#include<SDL.h>

#include<string>
#include<queue>
#include<list>

typedef void (*Update_Func)();


class XApp
{
public:
    XApp(std::string title, int w, int h, Uint32 initOpt, Uint32 winOpt, Uint32 renderOpt);
    ~XApp();

    SDL_Window* GetWindowHandler();
    //SDL_Renderer* GetRendererHandler();
    SDL_Surface* GetRenderSurface();
    void GetWindowWH(int* w, int* h);
    void SetDrawColor(Uint8 r, Uint8 g, Uint8 b);
    Uint32 GetDrawColor();
    void AddUpdateLogic(Update_Func func);
    void RemoveUpdateLogic(Update_Func func);

    void AppLoop();
    void Terminate();
protected:
    SDL_Window* m_pWindow;
    //SDL_Renderer* m_pRender;
    SDL_Surface* m_cacheSurface;
    SDL_Surface* m_windowSurface;

private:
    bool m_initStatus;
    bool m_runing;
    int m_screenW;
    int m_screenH;
    Uint32 m_initOptions;
    Uint32 m_windowOptions;
    Uint32 m_renderOptions;

    SDL_Event m_sdlEvent;
    std::queue<SDL_Event> m_frameEvents;

    Uint32 m_drawColor;

    std::list<Update_Func> m_updateFuncList;

    virtual void SDLEnvInit(std::string title, int w, int h, Uint32 initOpt, Uint32 winOpt, Uint32 renderOpt);
    void Release();
    void CatchInput();
    void UpdateLogic();
};

extern XApp* pAppInstance;