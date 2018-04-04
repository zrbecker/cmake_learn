#ifndef GAME_ENGINE_GAME_LOGIC_H
#define GAME_ENGINE_GAME_LOGIC_H

#include "engine.h"

namespace game {
namespace engine {

class GameLogic {
public:
  virtual void setup(Engine& engine) = 0;
  virtual void cleanup(Engine& engine) = 0;
  virtual void render(
    Engine& engine,
    double last_update_seconds,
    double last_frame_seconds
  ) = 0;
  virtual void update(Engine& engine, double last_update_seconds) = 0;
};

}  // namespace engine
}  // namespace game

#endif  // GAME_ENGINE_GAME_LOGIC_H