#include "cat_game_logic.h"

#include <iostream>

#include "sdl_application.h"

CatGameLogic::CatGameLogic()
  : last_output_(0),
    total_seconds_(0),
    frame_counts_() {}

void CatGameLogic::setup(SDLApplication& app) {
  app.load_image("cat", "./resources/cat.png");
  app.clear_display(0, 0, 255, 255);
  app.draw_image("cat");
  app.flip_display();
}

void CatGameLogic::update(SDLApplication& app, double seconds) {
  if (frame_counts_.size() == 0 ||
      int(total_seconds_ + seconds) - int(total_seconds_) >= 1) {
    frame_counts_.push_back(0);
  }
  total_seconds_ += seconds;
  frame_counts_.back() += 1;

  if (total_seconds_ > last_output_ + 5.0 && frame_counts_.size() > 1) {
    while (frame_counts_.size() > 21) {
      frame_counts_.erase(frame_counts_. begin());
    }
    int total_frames = 0;
    for (int i = 0; i < frame_counts_.size() - 1; ++i) {
      total_frames += frame_counts_[i];
    }
    double average_frames = double(total_frames) / (frame_counts_.size() - 1);
    std::cout << "ups: " << average_frames << std::endl;
    last_output_ = total_seconds_;
  }
}

void CatGameLogic::render(SDLApplication& app, double seconds) {

}
