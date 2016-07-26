#ifndef GAME_H
#define GAME_H

#include <vector>
#include <ctime>
#include <string>

#include "Director.h"

#include "Scene.h"

#define FPS             1000/60
#define GAME_SPEED      1000/60
#define INPUT_SPEED     1000/3
#define ANIMATION_SPEED 1000/3

#define SCENES 3
enum Scenes{
  MENU_SCENE = 0,
  OVERWORLD_SCENE,
  COMBAT_SCNENE
};

#define TIMERS 4
enum Timers{
  UPDATE_TIMER = 0,
  RENDER_TIMER,
  INPUT_TIMER,
  ANIMATION_TIMER
};

class Game {
private:
  /** Singleton*/
  Game();
  static Game* instance;

public:
  /** Destructor */
  ~Game();
  static Game* getInstance();

public:
  /** Main */
  int  run(Scene* starting_scene);
  void quit();
  void cleanUp();

  /** Game Status */
  bool isRunning();
  //bool isPaused();

  /** Scene */
  void setScene(Scene* p_starting_scene);
  Scene* getScene();

  /** Loop */
  long getTimer();
  void update();
  void handleEvents();
  void handleUserInput();
  void resetInput();
  void animation();
  void render();

  /** Utilities */
  //void displayFramerate();
  void settleTimers();

private:
  /** Game Status */
  bool   m_critical_error;
  Scene* m_scene;

  /** Containers */
  std::vector<Sprite*> pause_menu;

  /** Timers */
  long m_timer_now;
  long m_timer_next[TIMERS];

  // Utilities
  /*long framerate_timer;
  int framerate;
  Sprite* framerate_display;*/
};

#endif /* GAME_H */
