#ifndef WINDOWWRAPPER_H
#define WINDOWWRAPPER_H

#include <SDL2/SDL.h>

#include <string>
#include <iostream>

class WindowWrapper{
public:
  /**Constructor */
  WindowWrapper();
  WindowWrapper(std::string title, int p_x, int p_y, int p_w, int p_h, int p_flags);
  ~WindowWrapper();

  /**Get */
  SDL_Window* getWindow();
  SDL_Renderer* getRenderer();
  bool errorsExist();

private:
  /**Variables */
  SDL_Window*   m_window;
  SDL_Renderer* m_renderer;
  
  bool m_errors_exist;
};

#endif /* WINDOWWRAPPER_H */
