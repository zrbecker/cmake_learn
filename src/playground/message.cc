#include "message.h"

#include <iostream>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>

#include <fruit/fruit.h>

class Greeter {
public:
  virtual void greet() const = 0;
};

class HelloGreeter : public Greeter {
public:
  INJECT(HelloGreeter()) = default;

  void greet() const {
    std::cout << "Greeter> Hello World!" << std::endl;
  }
};

fruit::Component<Greeter> getGreeterComponent() {
  return fruit::createComponent().bind<Greeter, HelloGreeter>();
}

void print_message(const std::string& message) {
  fruit::Injector<Greeter> injector(getGreeterComponent);
  Greeter* greeter = injector.get<Greeter*>();
  greeter->greet();

  SDL_Log("SDL Logging");
  std::cout << PREPEND << message << std::endl;

  auto value = std::make_unique<int>(15);
  std::cout << *value << std::endl;

  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);

  SDL_Window* window = SDL_CreateWindow(
    "Application", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    500, 500, SDL_WINDOW_SHOWN);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

  SDL_Surface* surface = IMG_Load("./resources/cat.png");
  if (!surface) {
    std::cout << "Surface failed" << std::endl;
    std::cout << IMG_GetError() << std::endl;
  } else {
    std::cout << "Loaded image" << std::endl;
  }
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);

  SDL_SetWindowIcon(window, surface);
  
  bool running = true;
  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN) {
        running = false;
      }
    }
  }

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
}
