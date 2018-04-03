#include "cat_game_logic.h"

#include "sdl_application.h"

void CatGameLogic::setup(SDLApplication& app) {
  app.load_png("cat", "./resources/cat.png");
  app.clear_display(0, 0, 255, 255);
  app.draw_image("cat");
  app.flip_display();
}
