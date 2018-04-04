#ifndef GAME_SCENES_SPACE_GAME_SPACE_GAME_LOGIC_H
#define GAME_SCENES_SPACE_GAME_SPACE_GAME_LOGIC_H

#include "game/engine/game_logic.h"
#include "game/engine/frame_counter.h"

namespace game {
namespace scenes {
namespace space_game {

class SpaceGameLogic : public engine::GameLogic {
public:
  virtual void setup(engine::Engine& engine) override;
  virtual void cleanup(engine::Engine& engine) override;
  virtual void render(
    engine::Engine& engine,
    double last_update_seconds,
    double last_frame_seconds
  ) override;
  virtual void update(
      engine::Engine& engine, double last_update_seconds) override;

private:
  double hero_position_;
  engine::FrameCounter update_counter_;
  engine::FrameCounter frame_counter_;
};

}  // namespace space_game
}  // namespace scenes
}  // namespace game

#endif  // GAME_SCENES_SPACE_GAME_SPACE_GAME_LOGIC_H