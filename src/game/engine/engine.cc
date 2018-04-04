#include "engine.h"

#include "sdl_engine.h"

namespace game {
namespace engine {

std::unique_ptr<Engine> Engine::create_sdl_engine(GameLogic& game_logic) {
  return std::make_unique<SDLEngine>(game_logic);
}

}  // namespace engine
}  // namespace game
