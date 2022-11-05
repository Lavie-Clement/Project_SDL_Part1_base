// SDL_Test.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "Project_SDL1.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <random>
#include <string>

void init() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0)
    throw std::runtime_error("init():" + std::string(SDL_GetError()));

  // Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
    throw std::runtime_error("init(): SDL_image could not initialize! "
                             "SDL_image Error: " +
                             std::string(IMG_GetError()));
}

sheep::sheep(SDL_Surface* window_surface_ptr, int px, int py):animal("sheep.png", window_surface_ptr,px,py)
{
  
}
wolf::wolf(SDL_Surface* window_surface_ptr, int px, int py) : animal("wolf.png", window_surface_ptr, px, py)
{

}
void animal::Deplacement(int pX,int pY)
{
    this->x += pX;
    this->y += pY;
}

animal::animal(const std::string& file_path, SDL_Surface* window_surface_ptr,int px,int py)
{
    this->x = px;
    this->y = py;
    this->image_ptr_ = IMG_Load(file_path.c_str());
    if (!this->image_ptr_)
        throw std::runtime_error("Could not load image");
    this->window_surface_ptr_ = window_surface_ptr;
    if(!this->window_surface_ptr_)
        throw std::runtime_error(std::string(SDL_GetError()));
    
    this->rectangle = { x, y ,30,30 };

}
animal::~animal()
{
    //SDL_FreeSurface(this->image_ptr_);
    
   
}
void animal::draw()
{
    this->rectangle = { x, y ,30,30 };
    SDL_BlitScaled(this->image_ptr_, NULL, this->window_surface_ptr_, &this->rectangle);
}
ground::ground(SDL_Surface* window_surface_ptr)
{
    this->window_surface_ptr_ = window_surface_ptr;
    this->color= SDL_MapRGB(this->window_surface_ptr_->format, 0, 255, 0);
    SDL_FillRect(window_surface_ptr_, NULL, color);
    this->rectangle = { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,frame_width, frame_height };
    this->mout = sheep(this->window_surface_ptr_, 0, 100);
    this->lou = wolf(this->window_surface_ptr_, 1000, 100);
}
ground::~ground()
{
    
    
}

void ground::update()
{
    SDL_FillRect(window_surface_ptr_, NULL,this->color);
    this->mout.Deplacement(1,1);
    this->lou.Deplacement(-1, 1);
    this->lou.draw();
    
    this->mout.draw();
}
ground::ground()
{
    ;
}
application::application(unsigned n_sheep, unsigned n_wolf)
{
    window_ptr_ = SDL_CreateWindow("fenetre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,frame_width, frame_height ,SDL_WINDOW_SHOWN);
    if (!window_ptr_)
        throw std::runtime_error(std::string(SDL_GetError()));
    window_surface_ptr_= SDL_GetWindowSurface(window_ptr_);
    if (!window_surface_ptr_)
    {
        throw std::runtime_error(std::string(SDL_GetError()));
    }
    sol = ground(window_surface_ptr_);
    
   
}

application::~application()
{
   // delete &sol;
    SDL_FreeSurface(window_surface_ptr_);
    SDL_DestroyWindow(window_ptr_);
    
    delete &window_event_;
    

}
int application::loop(unsigned period)
{
    sol.update();

    SDL_UpdateWindowSurface(window_ptr_);

    auto start = SDL_GetTicks();
 
    SDL_Event e;
    bool quit = false;
    while (!quit && (SDL_GetTicks() - start < period)) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
                break;
            }
        }
        sol.update();

        SDL_UpdateWindowSurface(window_ptr_);
    }
    return 0;
}
namespace {
// Defining a namespace without a name -> Anonymous workspace
// Its purpose is to indicate to the compiler that everything
// inside of it is UNIQUELY used within this source file.

SDL_Surface* load_surface_for(const std::string& path,
                              SDL_Surface* window_surface_ptr) {

  // Helper function to load a png for a specific surface
  // See SDL_ConvertSurface
}
} // namespace
