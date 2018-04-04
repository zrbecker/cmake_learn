#ifndef GAME_ENGINE_GAME_LOGIC_H
#define GAME_ENGINE_GAME_LOGIC_H

namespace game {
namespace engine {

class SDLApplication;

class GameLogic {
public:
  virtual void setup(SDLApplication& app) = 0;
  virtual void cleanup(SDLApplication& app) = 0;
  virtual void render(
    SDLApplication& app,
    double last_update_seconds,
    double last_frame_seconds
  ) = 0;
  virtual void update(SDLApplication& app, double last_update_seconds) = 0;
};

}  // namespace engine
}  // namespace game

#endif  // GAME_ENGINE_GAME_LOGIC_H