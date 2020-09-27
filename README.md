# SnakeBattleRoyale
A combination of the classic snake game and battle royale

# Build & Run instructions
## Required Dependencies
### SDL2
Installation instructions available from [SDL](https://wiki.libsdl.org/Installation).

### Local build
- clone this repo
- `mkdir build && cd build`
- `cmake .. && make`

# Program Structure
## main.cpp
This section is a small wrapper and sets up some common resources such as the renderer. Game configuration settings are here as well, including things such as the map size and grid size.
The main program takes care of the game loop and ensuring consistent frames-per-second.

## GameApp
The `GameApp` class organizes all the game elements, calls updates and calls renders. The `GameApp` also performs all game logic, e.g. collision checking, in order to avoid any game logic in the `Entities` (see below).

The game app first instanciates the player, food, and enemy snakes per the configuration settings and registers them as tracked `Entities`. While running, the game will check if snakes have self collided, collided with the walls, collided with each other, or if they have found food. In the former cases, they are removed from the registered `Entities`. `Entities` and tracked with `shared_ptr` - removing them from the registry effectively calls the destructor.

For the `AutoSnake` enemies, a simple router is used to determine the path to the food. The determined direction from the router is then used to command a new direction.

`SDL_Event` is used to capture user input on the `w`, `a`, `s`, and `d` keys as well as the `close_window` call back. The keyboard keys are used to set the direction of the player snake.

## Entity class
This class is a generic base class representing the "things" which are part of the game. Examples include food, powerups, the (player) snake, and enemies (snakes). Common class methods include `render` and `update` along with `setPosition`. The class methods `render` and `update` are *pure virtual* functions as the raw Entity class is not intended to be used.

### Snake class
The `Snake` class dervies from the `Entity` base class. Unique to the snake class is the addition of the tail, the consideration of continuous movement, and directional constraints (e.g. cannot reverse direction onto tail).

Methods to make the game logic outside of the `Snake` are provided. These include checking of self collisions `isSelfCollided`, checking health `isDead`, and passing a direction change command `changeDir`, and extending the snake `extend`.

#### AutoSnake class
Enemy snakes are created as an `AutoSnake` object. The only significant difference to the base `Snake` class currently implemented is the coloring. However the design is strucutred to further compose the `AutoSnake` with various behaviors, e.g. the ability to cylce through different routers, dynamically adjust speed, route to attack the player vs. collect food, etc.

### Food class
Also derived from the `Entity` base class, the object that the snakes seek is `Food`. Food has very few properties, only the boolean `eaten` to track if food has been eaten.


# Udacity Rubric
This section outlines which parts of the optional section for the Udacity grading have been addressed. Below is brief highlight of the section of code and a reference to an example section in the code.

## Loops, Functions I/O
### Variety of Control Structures
- main.cpp
  - `Line 43` incorporates a `while` loop and `std::this_thread::sleep_for` to control the overall game life and ensure proper frame rates. 
- game.cpp::update()
  - `line 31` includes range-based `for` loop and several conditional `if` checks to implement the game logic

### Accept and process user input
- game.cpp::handleInput()
  - `line 126` implements and `SDL_event` to capture user input and use it to manipulate the character snake

## Object Oriented Programming
### Uses OO programming techniques
- Entity.h implements a virtual base class
- Snake.h derives from the `Entity` base class and implements the `Snake` class
- Food.h derives from the `Entity` base class and implements the `Food` class

### Class constructor with initialization list
- Entity.cpp `line 4`
- Snake.cpp `line 5`
- Food.cpp `line 4`

### Classes encapsulate behavior
- snake.cpp Snake::extend() encapsulates the behavior related to the game mechanics of eating food, growing the snake, and changing the speed.
- snake ::checkSelfCollision() encapsualtes the behavior specific to the `Snake` entity of crossing the snake's own tail

### Derived class functions override virtual base class
- entity.h Entity::update is a `pure virtual` method which *must* be overwritten by the derived classes.

## Memory Management
### Smart pointers
- GameApp tracks `Entities` (player snake, enemy snakes, food) with `shared_ptr`