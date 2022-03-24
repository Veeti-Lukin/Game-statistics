# Game-statistics
Text based program to keep track of multiple games players of those games and their scores.

## About the program
Acts as a game statistics with these commands

some commands will need parameters that are marked with <parameter>
extra paramaeters will not cause an error they will only be left useless:
  
- ALL_GAMES - Prints all known game names
- GAME <game name> - Prints all players playing the given game
- ALL_PLAYERS - Prints all known player names
- PLAYER <player name> - Prints all games the given player plays
- ADD_GAME <game name> - Adds a new game
- ADD_PLAYER <game name> <player name> <score> - Adds a new player with the given score for the given game, or updates the player's score if the player
  already playes the game
- REMOVE_PLAYER <player name> - Removes the player from all games
  
when program starts user will be asked to give name of the csv file of saved statistics
The data file's lines should be in format game_name;player_name;score
Otherwise the program execution terminates instantly (but still gracefully).
  
  
## Notes about the program and it's implementation:
- Stats of the games is implemented in class that contains datastructure of information of the games, players and scores.
- Main will handle csv file reading and all interaction with user.
- All changes to game stats and stat printing will be done from Game_statistics instances public interface
