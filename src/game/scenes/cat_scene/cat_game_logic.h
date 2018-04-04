#ifndef GAME_CAT_GAME_LOGIC
#define GAME_CAT_GAME_LOGIC

#include <vector>

#include "game/engine/frame_counter.h"
#include "game/engine/game_logic.h"

namespace game {
namespace scenes {
namespace cat_scene {

class CatGameLogic : public engine::GameLogic {
public:
  CatGameLogic();

  virtual void setup(engine::Engine& app) override;
  virtual void cleanup(engine::Engine& app) override {};
  virtual void render(
    engine::Engine& app,
    double last_update_seconds,
    double last_frame_seconds
  ) override;
  virtual void update(
      engine::Engine& app, double last_update_seconds) override;

private:
  engine::FrameCounter update_counter_;
  engine::FrameCounter frame_counter_;

  bool move_out_;
  double radius_;
  double angle_;
};

}  // namespace cat_scene
}  // namespace scenes
}  // game

#endif  // GAME_CAT_GAME_LOGIC