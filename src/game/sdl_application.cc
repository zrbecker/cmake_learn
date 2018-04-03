#include "sdl_application.h"

#include "SDL_image.h"

SDLApplication::SDLApplication(GameLogic& game_logic)
    : window_(nullptr),
      renderer_(nullptr),
      running_(false),
      images_(),
      game_logic_(game_logic) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw SDLException(std::string("SDL_Init Error: ") + SDL_GetError());
  }

  if (IMG_Init(IMG_INIT_PNG) == 0) {
    throw SDLException(std::string("IMG_Init Error: ") + IMG_GetError());
  }

  window_ = SDL_CreateWindow(
    "SDLApplication", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    600, 600, 0);
  if (!window_) {
    throw SDLException(
      std::string("SDL_CreateWindow Error: ") + SDL_GetError()
    );
  }

  renderer_ = SDL_CreateRenderer(window_, -1, 0);
  if (!renderer_) {
    throw SDLException(
      std::string("SDL_CreateRenderer Error: ") + SDL_GetError()
    );
  }
}

SDLApplication::~SDLApplication() {
  for (const auto& image_kvp : images_) {
    const auto& image = image_kvp.second;
    SDL_FreeSurface(image.surface);
    SDL_DestroyTexture(image.texture);
  }
  images_.clear();

  SDL_DestroyRenderer(renderer_);
  renderer_ = nullptr;

  SDL_DestroyWindow(window_);
  window_ = nullptr;

  IMG_Quit();
  SDL_Quit();
}

void SDLApplication::run() {
  game_logic_.setup(*this);
  running_ = true;
  Uint32 last = SDL_GetTicks();
  while (running_) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running_ = false;
      }
    }

    Uint32 now = SDL_GetTicks();
    double seconds = (now - last) / 1000.0;
    
    if (seconds >= 1.0 / 30.0) {
      game_logic_.update(*this, seconds);
      last = now;
    }

    game_logic_.render(*this, seconds);

    // SDL_Delay(2);
  }
  game_logic_.cleanup(*this);
}

void SDLApplication::draw_image(const std::string& image_name) {
  SDL_RenderCopy(renderer_, images_.at(image_name).texture, NULL, NULL);
}

void SDLApplication::clear_display(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  SDL_SetRenderDrawColor(renderer_, r, g, b, a);
  SDL_RenderClear(renderer_);
}

void SDLApplication::flip_display() {
  SDL_RenderPresent(renderer_);
}

void SDLApplication::load_image(
    const std::string& image_name, const std::string& filename) {
  SDL_Surface* surface = IMG_Load(filename.c_str());
  if (!surface) {
    throw SDLException(std::string("IMG_Load Error: ") + SDL_GetError());
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
  if (!texture) {
    throw SDLException(
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
