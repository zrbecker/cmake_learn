#ifndef GAME_ENGINE_SDL_IMPL_CREATE_SDL_ENGINE
#define GAME_ENGINE_SDL_IMPL_CREATE_SDL_ENGINE

#include <memory>

#include "game/engine/engine.h"
#include "game/engine/game_logic.h"

namespace game {
namespace engine {
namespace sdl_impl {

std::unique_ptr<Engine> create_sdl_engine(GameLogic& game_logic);

}  // namespace sdl_impl
}  // namespace engine
}  // namespace game

#endif  // GAME_ENGINE_SDL_IMPL_CREATE_SDL_ENGINE