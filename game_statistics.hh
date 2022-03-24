#ifndef GAME_STATISTICS_HH
#define GAME_STATISTICS_HH
/*
* Program author
* Name: Veeti Lukin
* Student number: 50797635
* UserID: gtvelu
* E-Mail: veeti.lukin@tuni.fi
*
* Notes about the class and it's implementation:
*   Can be used for storing information of players playing games and their scores.
*   This is only a header file.(check main.cpp for more information about the program
*   and game_statistics.cpp for class implementation.)
*
*   Public interface offers methods to add a game, add a player to a game,
*   remove player from all games, print all games, all players,
*   print stats of specific game and to print all games of specific player.
*
*   Inofrmation of games and their players and scores is saved in nested map.
*/

#include <string>
#include <map>

class Game_statistics {
public:
    // Default constructor
    Game_statistics();

    // adds game of given *game_name* without players in the <stats> data structure
    // return true if adding was succesful, false if game already exists
    bool add_game(const std::string& game_name);

    // adds a player with given name *player* to a given *game* with *score*
    // to the <stats> data structure
    // can also be used to set players score after adding
    // return true if adding was succesful, false if game dosn't exists
    bool add_player(const std::string& game, const std::string& player,
                             int score);

    // prints all the games (keys of the first map) in <stats> in ascii order
    void print_all_games() const;

    // prints all the players (keys in inner map) of the game in ascending score order
    // return false if *game* cannot be found, true if print was succesfull
    bool print_game_stats(const std::string& game) const;

    // prints the players(keys in inner maps) from every game(keys in outer map)
    // checks that no dublicate name will be printed
    void print_all_players() const;

    // prints all the games(outer maps keys) the player plays (aka. wich have
    // *player* as key in inner map)
    // return false if *player* cannot be found, true if print was succesfull
    bool print_players_games(const std::string& player) const;

    // remove player (*player* score pair) from all games (aka. every inner map
    // the *player* key is found)
    // return false if *player* cannot be found, true if print was succesfull
    bool remove_player(const std::string& player);
private:
    /* Data structure that holds the information of the games, players and scores
     * First maps key is name of the game.
     * Inner maps key is name of the player and payload is players score.
     * Example visualization:
     *  {"Sudoku" : {"Matti" : 1, "Maarit" : 50},
     *   "Hitori" : {"Maarit" : 30, "Mikko" : 10}}
     */
    std::map<std::string, std::map<std::string, int>> stats;
};

#endif // GAME_STATISTICS_HH
