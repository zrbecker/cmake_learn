#include "cat_game_logic.h"

#include <cmath>
#include <sstream>

#include "game/engine/engine.h"

namespace game {
namespace scenes {
namespace cat_scene {

const int CAT_SIZE = 100;

CatGameLogic::CatGameLogic()
  : update_counter_(),
    frame_counter_(),
    move_out_(true),
    radius_(0),
    angle_(0) {}

void CatGameLogic::setup(engine::Engine& app) {
  app.load_image("cat", "./resources/cat.png");
  app.resize_image("cat", CAT_SIZE, CAT_SIZE);

  app.load_font("default", "./resources/IBMPlexSans-Regular.ttf", 14);
}

void CatGameLogic::render(
  engine::Engine& app,
  double last_update_seconds,
  double last_frame_seconds
) {
  frame_counter_.report_frame(last_frame_seconds);

  double center_x = 400 - CAT_SIZE / 2;
  double center_y = 300 - CAT_SIZE / 2;

  double sinval = sin(angle_ / 180.0 * M_PI);
  double cosval = cos(angle_ / 180.0 * M_PI);

  double x = center_x + radius_ * cosval;
  double y = center_y + radius_ * sinval;

  std::stringstream ups;
  ups << "UPS: " << update_counter_.get_average_frames();
  std::stringstream fps;
  fps << "FPS: " << frame_counter_.get_average_frames();
  
  app.clear_display(0, 0, 255, 255);
  app.render_text("default", ups.str(), 5, 0, 255, 255, 255);
  app.render_text("default", fps.str(), 5, 17, 255, 255, 255);
  app.draw_image("cat", center_x, center_y);
  app.draw_image("cat", x, y);
  app.flip_display();
}

void CatGameLogic::update(
    engine::Engine& app, double last_update_seconds) {
  update_counter_.report_frame(last_update_seconds);

  const double CAT_SPEED = 150.0;  // Pixels per second.
  const double TURN_SPEED = 20.0;  // Degrees per second.

  angle_ += TURN_SPEED * last_update_seconds;
  while (angle_ >= 360) {
    angle_ -= 360;
  }

  if (move_out_) {
    radius_ += CAT_SPEED * last_update_seconds;
    if (radius_ >= 300) {
      move_out_ = false;
      radius_ = 300;
    }
  } else {
    radius_ -= CAT_SPEED * last_update_seconds;
    if (radius_ <= 0) {
      move_out_ = true;
      radius_ = 0;
    }
  }
}

}  // namespace cat_scene
}  // namespace scenes
}  // game
