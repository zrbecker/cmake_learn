#include <iostream>
#include <stdexcept>

#include "game/engine/engine.h"
#include "game/engine/sdl_impl/create_sdl_engine.h"
#include "game/scenes/cat_scene/cat_game_logic.h"
#include "game/scenes/space_game/space_game_logic.h"

using game::engine::Engine;
using game::engine::EngineException;
using game::scenes::cat_scene::CatGameLogic;
using game::scenes::space_game::SpaceGameLogic;

int main(int argc, char *argv[]) {
  try {
    SpaceGameLogic game_logic;
    auto app = game::engine::sdl_impl::create_sdl_engine(game_logic);
    app->run();
  } catch (const EngineException& ex) {
    std::cout << "EngineException Caught" << std::endl;
    std::cout << ex.what() << std::endl;
  }
  return 0;
}
