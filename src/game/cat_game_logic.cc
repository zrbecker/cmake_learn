#include "cat_game_logic.h"

#include <iostream>

#include "sdl_application.h"

CatGameLogic::CatGameLogic() : update_counter_("UPS"), frame_counter_("FPS") {}

void CatGameLogic::setup(SDLApplication& app) {
  app.load_image("cat", "./resources/cat.png");
  app.clear_display(0, 0, 255, 255);
  app.draw_image("cat");
  app.flip_display();
}

void CatGameLogic::render(
  SDLApplication& app,
  double last_update_seconds,
  double last_frame_seconds
) {
  frame_counter_.report_frame(last_frame_seconds);
}

void CatGameLogic::update(SDLApplication& app, double last_update_seconds) {
  update_counter_.report_frame(last_update_seconds);
}
