#include "cat_game_logic.h"

#include <iostream>

#include "sdl_application.h"

CatGameLogic::CatGameLogic()
  : update_counter_("UPS"),
    frame_counter_("FPS"),
    cat_x_(100),
    cat_y_(50),
    move_right_(true) {}

void CatGameLogic::setup(SDLApplication& app) {
  app.load_image("cat", "./resources/cat.png");
  app.resize_image("cat", 50, 50);
}

void CatGameLogic::render(
  SDLApplication& app,
  double last_update_seconds,
  double last_frame_seconds
) {
  frame_counter_.report_frame(last_frame_seconds);
  
  app.clear_display(0, 0, 255, 255);
  app.draw_image("cat", cat_x_, cat_y_);
  app.flip_display();
}

void CatGameLogic::update(SDLApplication& app, double last_update_seconds) {
  update_counter_.report_frame(last_update_seconds);

  if (move_right_) {
    cat_x_ += 10;
    if (cat_x_ >= 500) {
      move_right_ = false;
    }
  } else {
    cat_x_ -= 10;
    if (cat_x_ <= 100) {
      move_right_ = true;
    }
  }
}
