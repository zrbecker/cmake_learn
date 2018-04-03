#ifndef GAME_GAME_LOGIC_H
#define GAME_GAME_LOGIC_H

class SDLApplication;

class GameLogic {
public:
  virtual void setup(SDLApplication& app) = 0;
  virtual void cleanup(SDLApplication& app) = 0;
  virtual void render(SDLApplication& app, double seconds) = 0;
  virtual void update(SDLApplication& app, double seconds) = 0;
};

#endif  // GAME_GAME_LOGIC_H