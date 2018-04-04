#include "space_game_logic.h"

#include <sstream>

namespace game {
namespace scenes {
namespace space_game {

void SpaceGameLogic::setup(engine::Engine& engine) {
  engine.load_image("hero", "./resources/space_ship.png");
  engine.register_input("Left", game::engine::Key::Left);
  engine.register_input("Right", game::engine::Key::Right);
  engine.load_font("default", "./resources/IBMPlexSans-Regular.ttf", 14);
  hero_position_ = 400 - 25;
}

void SpaceGameLogic::cleanup(engine::Engine& engine) {}
void SpaceGameLogic::render(
  engine::Engine& engine,
  double last_update_seconds,
  double last_frame_seconds
) {
  frame_counter_.report_frame(last_frame_seconds);

  std::stringstream ups;
  ups << "UPS: " << update_counter_.get_average_frames();
  std::stringstream fps;
  fps << "FPS: " << frame_counter_.get_average_frames();

  engine.clear_display(20, 20, 20, 255);
  engine.draw_image("hero", hero_position_, 540);
  engine.render_text("default", ups.str(), 5, 0, 255, 255, 255);
  engine.render_text("default", fps.str(), 5, 17, 255, 255, 255);
  engine.flip_display();
}

void SpaceGameLogic::update(
    engine::Engine& engine, double last_update_seconds) {
  update_counter_.report_frame(last_update_seconds);

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
