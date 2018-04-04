#include <iostream>

#include "game/engine/sdl_application.h"
#include "game/scenes/cat_scene/cat_game_logic.h"

using game::engine::SDLApplication;
using game::engine::SDLException;
using game::scenes::cat_scene::CatGameLogic;

int main(int argc, char *argv[]) {
  try {
    CatGameLogic game_logic;
    SDLApplication app(game_logic);
    app.run();
  } catch (SDLException ex) {
    std::cout << "SDLException Caught" << std::endl;
    std::cout << ex.what() << std::endl;
  }
  return 0;
}
