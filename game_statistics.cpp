/*
* Program author
* Name: Veeti Lukin
* Student number: 50797635
* UserID: gtvelu
* E-Mail: veeti.lukin@tuni.fi
*
* Notes about the class and it's implementation:
*   This is only class implemention.
*   Check header file for more infomation.
*/

#include "game_statistics.hh"
#include <iostream>
#include <string>
#include <vector>
#include <set>

using std::endl;
using std::cout;
using std::vector;
using std::string;
using std::map;

Game_statistics::Game_statistics()
{

}

bool Game_statistics::add_game(const string& game_name) {
    // check if game already exists
    if (stats.find(game_name) != stats.end()) {
        return false;
    }

    stats.insert({game_name, {}});
    return true;
}

bool Game_statistics::add_player(const string& game, const string& player,
                                          int score) {
    // check if game exists
    if (stats.find(game) == stats.end()) {
        return false;
    }
    // add player inside the games inner map
    if (stats.at(game).find(player) == stats.at(game).end()) {
        stats.at(game).insert({player, 0});
    }
    stats.at(game).at(player) = score;
    return true;
}

void Game_statistics::print_all_games() const {
    cout << "All games in alphabetical order:" << endl;

    for (const auto& game : stats) {
        cout << game.first << endl;
    }
}

bool Game_statistics::print_game_stats(const string& game) const{
    // check if game exists
    if (stats.find(game) == stats.end()) {
        return false;
    }

    cout << "Game " << game
         << " has these scores and players, listed in ascending order:"
         << endl;

    // Insert every (player-score) pairs from <stats> inner map corresponding to *game*
    // to multimap mirror_map as (score-player)
    std::multimap<int, string> mirror_map;
    for (auto& i : stats.at(game)) {
        mirror_map.insert({ i.second, i.first });
    }

    // loop trhoug multimap and print players in ascending score order
    // player with same scores will be printed to same line seperated by ", "
    bool to_same_row = false;
    for (auto iter =  mirror_map.begin(); iter != mirror_map.end(); iter++) {
        if (to_same_row) {
            cout <<", " <<iter->second;
            to_same_row = false;
        }
        else {
            cout << iter->first << " : " << iter->second;
        }
        // if next player has the same score
        if (iter->first == std::next(iter)->first) {
            to_same_row = true;
        }
        else {
            cout << endl;
        }
    }
    return true;
}

void Game_statistics::print_all_players() const{
    // set cant have dublicate players from diffrent games
    std::set<string> players = {};

    // add every playe to set
    for (const auto& game : stats) {
        for (const auto& player : stats.at(game.first)) {
            players.insert(player.first);
        }
    }

    // prints players from the set
    cout << "All players in alphabetical order:" << endl;
    for (const string& player : players) {
        cout << player << endl;
    }
}

bool Game_statistics::print_players_games(const string& player) const {
    bool player_found = false;
    for (const auto& game : stats) {
        // search for player in inner map
        map<string, int>::const_iterator player_iter = stats.at(game.first).find(player);
        // player is found if iterator is not same as end iterator
        if (player_iter != stats.at(game.first).end()) {
            if (!player_found) {
                cout << "Player " << player << " playes the following games:" << endl;
                player_found = true;
            }

            cout << game.first << endl;

        }
    }
    return player_found;
}

bool Game_statistics::remove_player(const string& player) {
    bool player_found = false;
    for (const auto& game : stats) {
        // search for player in inner map
        map<string, int>::iterator player_iter = stats.at(game.first).find(player);
        // player is found if iterator is not same as end iterator
        if (player_iter != stats.at(game.first).end()) {
            stats.at(game.first).erase(player);
            player_found = true;
        }
    }
    return player_found;
}
