/*  Game statistics
 *
 * Desc:
 *  Acts as a game statistics with n commands
 *  some commands will need parameters that are marked with <parameter>
 *  extra paramaeters will not cause an error they will only be left useless:
 * ALL_GAMES - Prints all known game names
 * GAME <game name> - Prints all players playing the given game
 * ALL_PLAYERS - Prints all known player names
 * PLAYER <player name> - Prints all games the given player plays
 * ADD_GAME <game name> - Adds a new game
 * ADD_PLAYER <game name> <player name> <score> - Adds a new player with the
 * given score for the given game, or updates the player's score if the player
 * already playes the game
 * REMOVE_PLAYER <player name> - Removes the player from all games
 *
 *  The data file's lines should be in format game_name;player_name;score
 * Otherwise the program execution terminates instantly (but still gracefully).
 *
 * Program author
 * Name: Veeti Lukin
 * Student number: 50797635
 * UserID: gtvelu
 * E-Mail: veeti.lukin@tuni.fi
 *
 * Notes about the program and it's implementation:
 *  Stats of the games is implemented in class that contains datastructure of
 *  information of the games, players and scores.
 *  Main will handle csv file reading and all interaction with user.
 *  All changes to game stats and stat printing will be done from Game_statistics
 *  instances public interface
 */
#include "game_statistics.hh"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::cin;
using std::getline;


const string PROMPT = "games> ";
const string INVALID_INPUT_ERROR = "Error: Invalid input.";
const string GAME_NOT_FOUND_ERROR = "Error: Game could not be found.";
const string PLAYER_NOT_FOUND_ERROR = "Error: Player could not be found.";
const string GAME_ALREADY_EXISTS_ERROR = "Error: Already exists.";

// Casual split func, if delim char is between "'s, ignores it.
// Empty strings between delimeters will be skipped
vector<string> split( const string& str, char delim = ';' )
{
    vector<string> result = {""};
    bool inside_quatation = false;
    for ( auto current_char : str )
    {
        if ( current_char == '"' )
        {
            inside_quatation = not inside_quatation;
        }
        else if ( current_char == delim and not inside_quatation )
        {
            if (result.back() != ""){
                result.push_back("");
            }
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if ( result.back() == "" )
    {
        result.pop_back();
    }
    return result;
}

// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns -1.
int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i){
        if(not isdigit(str.at(i))){
            is_numeric = false;
            break;
        }
    }
    if(is_numeric){
        return stoi(str);
    }
    else{
        return -1;
    }
}

// Opens and reads a csv file by given *file_name*
// csv file has to be formated as "game;player;score"
// error messege will be printed if there is invalid line, file cant be opened,
// or score is not numeric. return true if succeeded, false otherwise.
bool read_game_stats_from_file(const string& file_name,
                               Game_statistics& stats_object) {

    std::ifstream file_object(file_name);
    // check if there is an error opening the file
    if (!file_object) {
        cout << "Error: File could not be read." << endl;
        return false;
    }

    // read file line by line until end
    string line = "";
    while (getline(file_object, line)) {
        vector<string> parts = split(line);

        // check if line has is formatted as "game;player;score"
        // wll also be false if some of these values is empty between seperators
        if (parts.size() != 3) {
            cout << "Error: Invalid format in file." << endl;
            return false;
        }
        string game = parts.at(0);
        string player = parts.at(1);
        int score = stoi_with_check(parts.at(2));

        // <stoi_with_check> reutned -1 if the value was not numeric 
        // empty player or game names are not allowed
        if (score == -1) {
            cout << "Error: Invalid format in file." << endl;
            return false;
        }

        stats_object.add_game(game); // does nothing if the game already exists
        stats_object.add_player(game, player, score);
    }
    return true;
}

// converts given string to upppercase and returnds it
string  convert_upper(string str) {
    for (char& c : str) {
        c = toupper(c);
    }
    return str;
}

int main() {
    // object that handles all the information of the players games and scores
    Game_statistics stats_object = Game_statistics();

    // read game stats from source file
    cout << "Give a name for input file: ";
    string file_name = "";
    getline(cin, file_name);
    if (!read_game_stats_from_file(file_name, stats_object)) {
        return EXIT_FAILURE;
    }

    // user interface loop
    // commands will test that they have enough parameters
    // extra paramaeters will not give an error they will only be left useless
    while (true) {

        cout << PROMPT;
        string input = "";
        getline(cin, input );

        // parse command out of vector so that only parameters are left in vector
        vector<string> arguments = split(input, ' ');
        string command = convert_upper(arguments.at(0));
        arguments.erase(arguments.begin());

        if (command == "ALL_GAMES")
        {
            stats_object.print_all_games();
        }

        else if (command == "GAME")
        {
            // requires one parameter: name of the game
            if (arguments.size() < 1) {
                cout << INVALID_INPUT_ERROR << endl;
                continue;
            }

            if (!stats_object.print_game_stats(arguments.at(0))) {
                cout << GAME_NOT_FOUND_ERROR << endl;
            }
        }

        else if (command == "ALL_PLAYERS")
        {
            stats_object.print_all_players();
        }

        else if (command == "PLAYER")
        {
            // requires one parameter: name of the player
            if (arguments.size() < 1) {
                cout << INVALID_INPUT_ERROR << endl;
                continue;
            }

            if (!stats_object.print_players_games(arguments.at(0))) {
                cout << PLAYER_NOT_FOUND_ERROR << endl;
            }
        }

        else if (command == "ADD_GAME")
        {
            // requires one parameter: name of the game
            if (arguments.size() < 1) {
                cout << INVALID_INPUT_ERROR << endl;
                continue;
            }

            if (!stats_object.add_game(arguments.at(0))) {
                cout << GAME_ALREADY_EXISTS_ERROR << endl;
            }
            else {
                cout << "Game was added." << endl;
            }
        }

        else if (command == "ADD_PLAYER")
        {
            //requires 3 parameters: game player score
            if (arguments.size() < 3) {
                cout << INVALID_INPUT_ERROR << endl;
                continue;
            }

            // check if score is numeric <stoi_with_check> returns -1 if not
            int score = stoi_with_check(arguments.at(2));
            if (score == -1) {
                cout << INVALID_INPUT_ERROR << endl;
            }

            if (!stats_object.add_player(arguments.at(0), arguments.at(1),
                                    score)) {
                cout << GAME_NOT_FOUND_ERROR << endl;
            }
            else {
                cout << "Player was added." << endl;
            }
        }

        else if (command == "REMOVE")
        {
            // requires one parameter: name of the player
            if (arguments.size() < 1) {
                cout << INVALID_INPUT_ERROR << endl;
                continue;
            }

            if (stats_object.remove_player(arguments.at(0))) {
                cout << "Player was removed from all games." << endl;
            }
            else {
                cout << PLAYER_NOT_FOUND_ERROR << endl;
            }
        }

        else if (command == "QUIT")
        {
             return EXIT_SUCCESS;
        }

        else {
            cout << INVALID_INPUT_ERROR << endl;
        }
    }
}
