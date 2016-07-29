#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Node.h"
#include "Label.h"
#include "Sprite.h"
#include "Cursor.h"
#include "WindowWrapper.h"
#include "InputHandler.h"

#include "Globals.h"

#define WINDOW_X 10
#define WINDOW_Y 10
#define WINDOW_W 640
#define WINDOW_H 480

class Director{
private:
  /**Singleton */
  Director();
  static Director* instance;

public:
  /**Singleton */
  ~Director();
  static Director* getInstance();

public:
  /**Director */
  void quit();
  bool isRunning();
  void cleanUp();

  /**SDL */
  bool initSDL();
  SDL_Window* createWindow();

  /**Setup */
  bool init();
  void setupDefaultFont();
  void setupCursor();

  /**Input */
  void handleEvents();
  void resetInput();
  bool getKey(int p_key);
  void resetKey(int p_key);

  /**Nodes */
  void addNode(Sprite* p_sprite);
  void deleteNode(Sprite* p_sprite);
  void addNode(Label* p_label);
  void deleteNode(Label* p_label);

  /**Textures */
  void assignTexture(Sprite* p_sprite);
  SDL_Texture* createTexture(Sprite* p_sprite);
  void assignTexture(Label* p_label);
  SDL_Texture* createTexture(Label* p_label);

  /**Render */
  void render();
  void draw();
  void draw(Node* p_node);
#ifndef PRODUCTION_MODE
  void draw(Body* p_body);
#endif

  /**Animation */
  void animation();
  void passiveAnimation();
  void activeAnimation();

  /**Timer */
  long getTimer();
  
  /**Utilities */
  int getRandomNumber();

private:
    // Status
    bool m_running;
    //bool m_critical_error;

    // Containers
    std::vector<Sprite*> m_sprites;
    std::vector<Label*>  m_labels;
    std::map<std::string, SDL_Texture*> m_loaded_textures;

    // SDL
    WindowWrapper* m_windows;
    SDL_Surface*   m_surface;
    TTF_Font* m_default_font;

    // Input
    InputHandler* m_input_handler;
};

#endif /* DIRECTOR_H */
