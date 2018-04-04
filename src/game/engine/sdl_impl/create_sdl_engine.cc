#include "create_sdl_engine.h"

#include "sdl_engine.h"

namespace game {
namespace engine {
namespace sdl_impl {

std::unique_ptr<Engine> create_sdl_engine(GameLogic& game_logic) {
  return std::make_unique<SDLEngine>(game_logic);
}

}  // namespace sdl_impl
}  // namespace engine
}  // namespace game