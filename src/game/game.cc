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
    this->load_png("cat", "./resources/cat.png");
    this->clear_display(0, 0, 255, 255);
    this->draw_image("cat");
    this->flip_display();
  }

  virtual void render() {
  }

  virtual void cleanup() {

  }

  void draw_image(const std::string& image_name) {
    SDL_RenderCopy(renderer_, images_.at(image_name).texture, NULL, NULL);
  }

  void clear_display(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SDL_SetRenderDrawColor(renderer_, r, g, b, a);
    SDL_RenderClear(renderer_);
  }

  void flip_display() {
    SDL_RenderPresent(renderer_);
  }

  Image load_png(const std::string& image_name, const std::string& filename) {
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
