#include "WindowWrapper.h"

WindowWrapper::WindowWrapper()
{
  m_window   = NULL;
  m_renderer = NULL;
  
  m_errors_exist = false;
}

WindowWrapper::WindowWrapper(std::string title, int p_x, int p_y, int p_w, int p_h, int p_flags) : WindowWrapper()
{
    m_window = SDL_CreateWindow(title.c_str(),
                                p_x, p_y,
                                p_w, p_h,
                                p_flags
                               );

    if(m_window == NULL)
    {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        m_errors_exist = true;
    }
    else
    {
        m_renderer = SDL_CreateRenderer(m_window, -1,
                                        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
                                       );

        if(m_renderer == NULL)
        {
            std::cerr << "Error creating renderer " << SDL_GetError() << std::endl;
            m_errors_exist = true;
        }
    }
}

WindowWrapper::~WindowWrapper()
{
    SDL_DestroyWindow(m_window);

    SDL_DestroyRenderer(m_renderer);
}

SDL_Window* WindowWrapper::getWindow()
{
    return m_window;
}

SDL_Renderer* WindowWrapper::getRenderer()
{
    return m_renderer;
}

bool WindowWrapper::errorsExist()
{
    return m_errors_exist;
}