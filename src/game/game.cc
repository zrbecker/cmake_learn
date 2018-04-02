#include "SDL.h"
#include "SDL_image.h"

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

class SDLException : public std::runtime_error {
  using std::runtime_error::runtime_error;
};

struct Image {
  SDL_Surface* surface;
  SDL_Texture* texture;
};

class SDLApplication {
public:
  SDLApplication()
      : window_(nullptr),
        renderer_(nullptr),
        running_(false),
        images_() {
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

  ~SDLApplication() {
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

  void run() {
    setup();
    running_ = true;
    while (running_) {
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          running_ = false;
        }
      }
      render();
      SDL_Delay(2);
    }
    cleanup();
  }

protected:
  virtual void setup() {
    images_["cat"] = load_png("./resources/cat.png");
    SDL_SetRenderDrawColor(renderer_, 0, 0, 255, 255);
    SDL_RenderClear(renderer_);
    SDL_RenderCopy(renderer_, images_["cat"].texture, NULL, NULL);
    SDL_RenderPresent(renderer_);
  }

  virtual void render() {
  }

  virtual void cleanup() {

  }

  Image load_png(const std::string& filename) {
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
    return Image {
      surface,
      texture
    };
  }

private:
  SDL_Window* window_;
  SDL_Renderer* renderer_;
  bool running_;
  std::map<std::string, Image> images_;
};

int main(int argc, char *argv[]) {
  try {
    SDLApplication app;
    app.run();
  } catch (SDLException ex) {
    std::cout << "SDLException Caught" << std::endl;
    std::cout << ex.what() << std::endl;
  }
  return 0;
}
