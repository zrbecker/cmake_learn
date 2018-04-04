#include "cat_game_logic.h"

#include <cmath>
#include <iostream>
#include <sstream>

#include "sdl_application.h"

#include "SDL_ttf.h"

CatGameLogic::CatGameLogic()
  : update_counter_("UPS"),
    frame_counter_("FPS"),
    cat_x_(100),
    cat_y_(50),
    move_right_(true),
    sin_(),
    angle_(0) {}

void CatGameLogic::setup(SDLApplication& app) {
  app.load_image("cat", "./resources/cat.png");
  app.resize_image("cat", 50, 50);

  for (int theta = 0; theta < 360; ++theta) {
    sin_.push_back(sin(theta / 180.0 * M_PI));
    cos_.push_back(cos(theta / 180.0 * M_PI));
  }

  font_ = TTF_OpenFont("./resources/IBMPlexSans-Regular.ttf", 14);
  if (!font_) {
    throw SDLException(std::string("TTF_OpenFont: ") + TTF_GetError());
  }
}

void CatGameLogic::render(
  SDLApplication& app,
  double last_update_seconds,
  double last_frame_seconds
) {
  frame_counter_.report_frame(last_frame_seconds);

  double radius = cat_x_;
  double center_x = 400 - 25;
  double center_y = 300 - 25;

  // double sinval = sin_[int(angle_)];
  // double cosval = cos_[int(angle_)];

  double sinval = sin(angle_ / 180.0 * M_PI);
  double cosval = cos(angle_ / 180.0 * M_PI);

  double x = center_x + radius * cosval;
  double y = center_y + radius * sinval;

  std::stringstream ups;
  ups << "UPS: " << update_counter_.get_average_frames();
  std::stringstream fps;
  fps << "FPS: " << frame_counter_.get_average_frames();
  
  app.clear_display(0, 0, 255, 255);
  app.render_text(font_, ups.str(), 5, 0, 255, 255, 255);
  app.render_text(font_, fps.str(), 5, 17, 255, 255, 255);
  app.draw_image("cat", center_x, center_y);
  app.draw_image("cat", x, y);
  app.flip_display();
}

void CatGameLogic::update(SDLApplication& app, double last_update_seconds) {
  update_counter_.report_frame(last_update_seconds);

  const double CAT_SPEED = 150.0;  // Pixels per second.
  const double TURN_SPEED = 20.0;  // Degrees per second.

  angle_ += TURN_SPEED * last_update_seconds;
  while (angle_ >= 360) {
    angle_ -= 360;
  }

  if (move_right_) {
    cat_x_ += CAT_SPEED * last_update_seconds;
    if (cat_x_ >= 300) {
      move_right_ = false;
    }
  } else {
    cat_x_ -= CAT_SPEED * last_update_seconds;
    if (cat_x_ <= 0) {
      move_right_ = true;
    }
  }
}
