/*
Game States used for loading and menus screens
*/

typedef enum GameState{
    MENU_LOAD, //Load Menu Screen
    MENU_RUN, //Menu Screen
    GAME_LOAD, //Used for 1 frame while the game is loading
    GAME_RUN, //Used for the main game loop
    GAME_RESET // Reset Game
} GameStates;