#include <iostream>
#include <stdexcept>

#include "game/engine/engine.h"
#include "game/scenes/cat_scene/cat_game_logic.h"

using game::engine::Engine;
using game::scenes::cat_scene::CatGameLogic;

int main(int argc, char *argv[]) {
  try {
    CatGameLogic game_logic;
    auto app = Engine::create_sdl_engine(game_logic);
    app->run();
  } catch (const std::runtime_error& ex) {
    std::cout << "SDLException Caught" << std::endl;
    std::cout << ex.what() << std::endl;
  }
  return 0;
}
