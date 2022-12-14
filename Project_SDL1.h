// SDL_Test.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <vector>

// Defintions
constexpr double frame_rate = 60.0; // refresh rate
constexpr double frame_time = 1. / frame_rate;
constexpr unsigned frame_width = 1400; // Width of window in pixel
constexpr unsigned frame_height = 900; // Height of window in pixel
// Minimal distance of animals to the border
// of the screen
constexpr unsigned frame_boundary = 100;

// Helper function to initialize SDL
void init();

class animal {
private:
    SDL_Surface* window_surface_ptr_; // ptr to the surface on which we want the
                                    // animal to be drawn, also non-owning
    SDL_Surface* image_ptr_; // The texture of the sheep (the loaded image), use
                           // load_surface_for
    SDL_Rect rectangle_;
    float positionX_;
    float positionY_;
    int speed_;
    std::string image_;
    float directionX_;
    float directionY_;
    bool vivant_;
    bool genre_;
    std::vector<std::string> flags_;

    // todo: Attribute(s) to define its position

public:
    animal(){};
    animal(const std::string& file_path, SDL_Surface* window_surface_ptr, float positionX, float positionY);
    // todo: The constructor has to load the sdl_surface that corresponds to the
    // texture
    void Deplacement(float px, float pY);
    float getPosX();
    float getPosY();
    void setDirectionX(float directionX);
    void setDirectionY(float directionY);
    float getDirectionX();
    float getDirectionY();
    SDL_Rect getRectangle();
    void setVivant(bool vivant);
    bool getVivant();
    void setGenre(bool genre);
    bool getGenre();
    void setSpeed(int speed);
    int getSpeed();
    void addFlag(std::string flag);
    bool hasFlag(std::string flag);

    virtual ~animal(); // todo: Use the destructor to release memory and "clean up
               // behind you"

    void draw(); // todo: Draw the animal on the screen <-> window_surface_ptr.
                 // Note that this function is not virtual, it does not depend
                 // on the static type of the instance

    virtual void move(){}; // todo: Animals move around, but in a different
                             // fashion depending on which type of animal
    virtual void setFood(int food) { };
    virtual int getFood() { return 0; };
    virtual int getCdCop() { return -1; };
    virtual bool HasBaby() { return false; };
    virtual void changeBaby() {};
    virtual void BabyFalse() {};
    virtual void copBaisse(int n) {};
    virtual void augmentCd(int n) {};
    virtual void setDestination(float destinationX, float destinationY){};
    virtual float getDestinationX() { return 0; };
    virtual float getDestinationY() { return 0; };
    virtual void setPeur(int peur){};
    virtual int getPeur() { return 1; };
    virtual void setRandomMove(int randomMove){};
    virtual int getRandomMove() { return 0; };
};

// Insert here:
// class sheep, derived from animal
class sheep : public animal {
private:
    int cdCop;
    bool Baby;
    int randomMove_;

public:
  // todo                                                                             
  // Ctor
  // Dtor
  // implement functions that are purely virtual in base class
    sheep(){};
    sheep(SDL_Surface* window_surface_ptr, float positionX, float positionY);
    ~sheep();
    void move();
    int getCdCop();
    void copBaisse(int n);
    void augmentCd(int n);
    bool HasBaby() ;
    void changeBaby();
    void BabyFalse();
    void setRandomMove(int randomMove);
    int getRandomMove();

};


// Insert here:
// class wolf, derived from animal
class wolf : public animal {
private:
    int food_;
    int peur_;
public: // todo
    wolf(SDL_Surface* window_surface_ptr, float positionX, float positionY);// Ctor
    wolf() {};
    ~wolf();
    void move();
    void setFood(int food);
    int getFood();
    void setPeur(int peur);
    int getPeur();
};
class dog : public animal {
private:
    int destinationX;
    int destinationY;
public: // todo
    dog(SDL_Surface* window_surface_ptr, float positionX, float positionY);// Ctor
    dog() {};
    ~dog();
    void move();
    void setDestination(float destinationX, float destinationY);
    float getDestinationX();
    float getDestinationY();

    
};
class Humain
{
private:
    SDL_Surface* window_surface_ptr_; // ptr to the surface on which we want the
    // animal to be drawn, also non-owning
    SDL_Surface* image_ptr_; // The texture of the sheep (the loaded image), use
    // load_surface_for
    SDL_Rect rectangle_;
    int positionX_;
    int positionY_;
    int directionX_;
    int directionY_;
    SDL_Event touche;
    int speed_;

public:
    Humain() {};
    ~Humain() {};
    Humain(SDL_Surface* window_surface_ptr, int positionX, int positionY);
    void move();
    void draw();
    int getPosX();
    int getPosY();
    void setDirectionX(int directionX);
    void setDirectionY(int directionY);
    int getDirectionX();
    int getDirectionY();
    void setSpeed(int speed);
    int getSpeed();
    SDL_Rect getRectangle();
    void setevent(SDL_Event ev);



};
class Score {
private:
    SDL_Surface* window_surface_ptr_; 
    SDL_Surface* image_ptr_;
    SDL_Rect rectangle_;
    int nbMoutonALive_;
public:
    Score() {};
    ~Score() {};

    Score(SDL_Surface* window_surface_ptr,int nbMoutonAlive);
    void setNbMoutonAlive(int nbMoutonAlive);
    int getNbMoutonAlive();
    void draw();

};
// Use only sheep at first. Once the application works
// for sheep you can add the wolves

// The "ground" on which all the animals live (like the std::vector
// in the zoo example).
class ground {
private:
  // Attention, NON-OWNING ptr, again to the screen
    SDL_Surface* window_surface_ptr_;
    SDL_Rect rectangle;
    Humain player;

    /*sheep mout;
    wolf lou;*/
    std::vector<std::shared_ptr<animal>> animalList;
    Uint32 color;
    Score score_;
    int nbScore_;
public:
    ground(){};

    ground(SDL_Surface* window_surface_ptr,int nbScore); // todo: Ctor
    ~ground(); // todo: Dtor, again for clean up (if necessary)
    void add_animal(std::shared_ptr<animal> newAnimal); // todo: Add an animal
    void update(); // todo: "refresh the screen": Move animals and draw them
    // Possibly other methods, depends on your implementation
    void updatePlayer(SDL_Event ev);// todo: "refresh the screen": Move animals and draw them
    void updateDogs(SDL_Event ev);
    void setNbScore(int nbScore);
};

// The application class, which is in charge of generating the window
class application {
private:
    // The following are OWNING ptrs
    SDL_Window* window_ptr_;
    SDL_Surface* window_surface_ptr_;
    SDL_Event window_event_;
    ground ground_;
    // Other attributes here, for example an instance of ground

public:
    application(unsigned n_sheep, unsigned n_wolf); // Ctor
    ~application();                                 // dtor

    int loop(unsigned period); // main loop of the application.
                             // this ensures that the screen is updated
                             // at the correct rate.
                             // See SDL_GetTicks() and SDL_Delay() to enforce a
                             // duration the application should terminate after
                             // 'period' seconds
};