#include "space_game_logic.h"

namespace game {
namespace scenes {
namespace space_game {

void SpaceGameLogic::setup(engine::Engine& engine) {
  engine.load_image("hero", "./resources/space_ship.png");
  engine.register_input("Left", game::engine::Key::Left);
  engine.register_input("Right", game::engine::Key::Right);
  hero_position_ = 400 - 25;
}

void SpaceGameLogic::cleanup(engine::Engine& engine) {}
void SpaceGameLogic::render(
  engine::Engine& engine,
  double last_update_seconds,
  double last_frame_seconds
) {
  engine.clear_display(20, 20, 20, 255);
  engine.draw_image("hero", hero_position_, 540);
  engine.flip_display();
}

void SpaceGameLogic::update(
    engine::Engine& engine, double last_update_seconds) {
  const double HERO_SPEED = 350.0;
  if (engine.input_is_down("Left")) {
    hero_position_ -= HERO_SPEED * last_update_seconds;
    if (hero_position_ < 0) {
      hero_position_ = 0;
    }
  }

  if (engine.input_is_down("Right")) {
    hero_position_ += HERO_SPEED * last_update_seconds;
    if (hero_position_ > 800 - 50) {
      hero_position_ = 800 - 50;
    }
  }
}

}  // namespace space_game
}  // namespace scenes
}  // namespace game
