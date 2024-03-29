#include "sdl_engine.h"

#include <iostream>
#include <memory>

#include "SDL_image.h"
#include "SDL_ttf.h"

#include "game/engine/game_logic.h"

namespace game {
namespace engine {

SDLEngine::SDLEngine(GameLogic& game_logic)
    : window_(nullptr),
      renderer_(nullptr),
      running_(false),
      images_(),
      game_logic_(game_logic) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw EngineException(std::string("SDL_Init Error: ") + SDL_GetError());
  }

  if (IMG_Init(IMG_INIT_PNG) == 0) {
    throw EngineException(std::string("IMG_Init Error: ") + IMG_GetError());
  }

  if (TTF_Init() != 0) {
    throw EngineException(std::string("TTF_Init Error: ") + TTF_GetError());
  }

  window_ = SDL_CreateWindow(
    "SDLApplication", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    800, 600, 0);
  if (!window_) {
    throw EngineException(
      std::string("SDL_CreateWindow Error: ") + SDL_GetError()
    );
  }

  renderer_ = SDL_CreateRenderer(window_, -1, 0);
  if (!renderer_) {
    throw EngineException(
      std::string("SDL_CreateRenderer Error: ") + SDL_GetError()
    );
  }
}

SDLEngine::~SDLEngine() {
  for (const auto& image_kvp : images_) {
    const auto& image = image_kvp.second;
    SDL_FreeSurface(image.surface);
    SDL_DestroyTexture(image.texture);
  }
  images_.clear();

  for (const auto& font_kvp : fonts_) {
    const auto& font = font_kvp.second;
    TTF_CloseFont(font);
  }
  fonts_.clear();

  SDL_DestroyRenderer(renderer_);
  renderer_ = nullptr;

  SDL_DestroyWindow(window_);
  window_ = nullptr;

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

Key sdl_key_to_engine_key(int keycode) {
  switch (keycode) {
    case SDLK_LEFT:
      return Key::Left;
    case SDLK_RIGHT:
      return Key::Right;
    default:
      return Key::Unknown;
  }
}

void SDLEngine::run() {
  game_logic_.setup(*this);
  running_ = true;
  Uint32 last_update = SDL_GetTicks();
  Uint32 last_frame = last_update;
  while (running_) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running_ = false;
      }

      if (event.type == SDL_KEYDOWN) {
        Key key = sdl_key_to_engine_key(event.key.keysym.sym);
        if (key_to_key_info_.count(key) > 0) {
          auto key_info = key_to_key_info_.at(key);
          key_info->is_key_down = true;
        }
      }

      if (event.type == SDL_KEYUP) {
        Key key = sdl_key_to_engine_key(event.key.keysym.sym);
        if (key_to_key_info_.count(key) > 0) {
          auto key_info = key_to_key_info_.at(key);
          key_info->is_key_down = false;
        }
      }
    }

    Uint32 now = SDL_GetTicks();
    double last_update_seconds = (now - last_update) / 1000.0;
    double last_frame_seconds = (now - last_frame) / 1000.0;

    double last_update_after_delay_seconds = (now + 1 - last_update) / 1000.0;
    
    if (last_update_after_delay_seconds >= 1.0 / 120.0) {
      game_logic_.update(*this, last_update_seconds);
      last_update = now;
    }

    game_logic_.render(*this, last_update_seconds, last_frame_seconds);
    last_frame = now;

    SDL_Delay(1);
  }
  game_logic_.cleanup(*this);
}

void SDLEngine::resize_image(const std::string& image_name, int w, int h) {
  Image image = images_.at(image_name);

  SDL_Texture* screen_texture = SDL_GetRenderTarget(renderer_);

  Uint32 format;
  int access, screen_w, screen_h;
  SDL_QueryTexture(screen_texture, &format, &access, &screen_w, &screen_h);

  SDL_Texture* resize_texture = SDL_CreateTexture(
    renderer_, format, SDL_TEXTUREACCESS_TARGET, w, h);
  if (!resize_texture) {
    std::cerr << "SDL_CreateTexture: " << SDL_GetError() << std::endl;
  }
  SDL_SetRenderTarget(renderer_, resize_texture);

  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderClear(renderer_);
  int error = SDL_RenderCopy(renderer_, image.texture, NULL, NULL);
  SDL_RenderPresent(renderer_);
  if (error != 0) {
    std::cerr << "SDL_RenderCopy: " << SDL_GetError() << std::endl;
  }
  SDL_SetTextureAlphaMod(resize_texture, 0);

  SDL_DestroyTexture(image.texture);
  image.texture = resize_texture;

  images_[image_name] = image;

  SDL_SetRenderTarget(renderer_, screen_texture);
}

void SDLEngine::draw_image(const std::string& image_name, int x, int y) {
  Image image = images_.at(image_name);

  Uint32 format;
  int access, w, h;
  SDL_QueryTexture(image.texture, &format, &access, &w, &h);

  SDL_Rect dest_rect {x, y, w, h};
  SDL_RenderCopy(renderer_, images_.at(image_name).texture, NULL, &dest_rect);
}

void SDLEngine::clear_display(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  SDL_SetRenderDrawColor(renderer_, r, g, b, a);
  SDL_RenderClear(renderer_);
}

void SDLEngine::flip_display() {
  SDL_RenderPresent(renderer_);
}

void SDLEngine::load_image(
    const std::string& image_name, const std::string& filename) {
  SDL_Surface* surface = IMG_Load(filename.c_str());
  if (!surface) {
    throw EngineException(std::string("IMG_Load Error: ") + SDL_GetError());
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
  if (!texture) {
    throw EngineException(
      std::string("SDL_CreateTextureFromSurface Error: ") + SDL_GetError()
    );
  }

  Image image;
  image.surface = surface;
  image.texture = texture;
  
  if (images_.count(image_name) > 0) {
    SDL_FreeSurface(images_[image_name].surface);
    SDL_DestroyTexture(images_[image_name].texture);
  }

  images_[image_name] = image;
}

void SDLEngine::load_font(
    const std::string& font_name, const std::string& filename, int size) {
  TTF_Font* font = TTF_OpenFont(filename.c_str(), size);
  if (!font) {
    throw EngineException(std::string("TTF_OpenFont: ") + TTF_GetError());
  }
  fonts_[font_name] = font;
}

void SDLEngine::render_text(
    const std::string& font_name,
    const std::string& text,
    int x, int y,
    uint8_t r, uint8_t g, uint8_t b
) {
  TTF_Font* font = fonts_.at(font_name);
  SDL_Color color = {r, g, b, 255};
  SDL_Surface* font_surface = TTF_RenderText_Solid(font, text.c_str(), color);
  SDL_Texture* font_texture = SDL_CreateTextureFromSurface(
      renderer_, font_surface);

  SDL_Rect dest_rect = {x, y, font_surface->w, font_surface->h};
  SDL_RenderCopy(renderer_, font_texture, NULL, &dest_rect);

  SDL_DestroyTexture(font_texture);
  SDL_FreeSurface(font_surface);
}

void SDLEngine::register_input(const std::string& input_name, Key key) {
  auto key_info = std::make_unique<KeyInfo>();
  key_info->input_name = input_name;
  key_info->key = key;
  key_info->is_key_down = false;

  auto key_info_ptr = key_info.get();

  input_to_key_info_[input_name] = std::move(key_info);
  key_to_key_info_[key] = key_info_ptr;
}

bool SDLEngine::input_is_down(const std::string& input_name) {
  if (input_to_key_info_.count(input_name) > 0) {
    return input_to_key_info_.at(input_name)->is_key_down;
  }
  return false;
}

}  // namespace engine
}  // namespace game
