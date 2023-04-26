## Arcade Project Documentation

# Introduction
The Arcade project is an extensible program designed to run various arcade games using different graphic libraries. The core system manages the game loop and game logic, as well as communication between the game module and the graphic module.

This documentation provides an overview of how the Arcade project works and guides you through implementing new graphics and game libraries compatible with the system.

# System Architecture
The system architecture is divided into three main components:

Core: The central component that handles the game loop, user inputs, and communication between the game and graphic modules.

Graphic Modules: Libraries that implement the IGraphicModule interface and are responsible for rendering the game using a specific graphic library (e.g., ncurses, SFML, SDL2).

Game Modules: Libraries that implement the IGameModule interface and define the game logic and rules for a specific game (e.g., Snake, Nibbler).

# Implementing New Graphics Libraries
To implement a new graphics library compatible with the Arcade system, follow these steps:

Create a new class that implements the IGraphicModule interface. The interface requires the implementation of the following methods:

void run(): Manage the main loop of the graphic module.
void playSound(): Play sound effects when required.
void display(const std::vectorstd::string &map, const std::string &score): Render the game map and score on the graphics window.
void updateTexture(const std::string &direction): Update the textures based on the direction of the game objects.
void drawMenu(const std::vectorstd::string &gameNames, int selectedIndex): Render the game selection menu.
std::string handle_events(): Handle user inputs and return the corresponding event string.
const std::string& getName() const: Get the name of the graphics module.
void displayGameName(std::string name): Display the game name on the graphics window.

Update the Core::attributeLibraryPaths method in the Core class to recognize the new graphics library.

Add the new graphics library path to the _libraryPaths vector in the Core class.

# Implementing New Game Libraries
To implement a new game library compatible with the Arcade system, follow these steps:

Create a new class that implements the IGameModule interface. The interface requires the implementation of the following methods:

const std::vector<std::string> &getMap() const: Get the current game map.
std::string getScoreAsString() const: Get the current score as a string.
int getLife() const: Get the remaining lives.
int move(const std::string &direction): Update the game state based on the given direction.
std::vector<std::string> getValidDirections(): Get the valid directions for the game objects.
Ensure the new game module class is compiled into a shared library with the appropriate naming convention (e.g., "lib/arcade_newgame.so").

Add the new game library path and name to the _gamePaths vector in the Core class.