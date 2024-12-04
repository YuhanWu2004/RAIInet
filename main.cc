#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

#include "link.h"
#include "position.h"
#include "cell.h"
#include "subject.h"

#include "ability.h"
#include "linkboost.h"
#include "firewall.h"
#include "download.h"
#include "polarize.h"
#include "scan.h"
#include "brutal.h"
#include "protect.h"
#include "trade.h"

#include "player.h"
#include "board.h"

#include "observer.h"
#include "textobserver.h"
#include "window.h"
#include "graphicalobserver.h"


const int num_abilities = 5;
const int default_num = 1;
void display_usage() {
    cout << "Usage: ./program <max_row> <max_col> <player1_file> <player2_file>" << endl;
    cout << "  max_row: Number of rows in the board" << endl;
    cout << "  max_col: Number of columns in the board" << endl;
    cout << "  player1_file: File with player 1's link placements" << endl;
    cout << "  player2_file: File with player 2's link placements" << endl;
}

void ask_for_ability() {
    cout << "" << endl;
    cout << "Use command: -ability1 <order>  or -ability2 <order> to specify your abilities:" << endl;
    cout << "Example: -ability1 LFDSP" << endl;
    cout << "If you want to use the default ability set, please enter: -ability1/-ability2 default  " << endl;
    cout << "Abilities:" << endl;
    cout << "L: Link Boost" << endl;
    cout << "F: Firewall" << endl;
    cout << "D: Download" << endl;
    cout << "P: Polarize" << endl;
    cout << "S: Scan" << endl;
    cout << "B: Brutal" << endl;
    cout << "C: Protect" << endl;
    cout << "T: Trade" << endl;
}

// ===========================SET_UP_ABILITIES==============================================================
// return value int:
//      0: unsuccessful input;
//      1: player 1's abilities are set successfully
//      2: player 2's abilities are set successfully
//      3: tell main to set up the default abilities
int set_up_abilities(string input1, string input2, Player &player1, Player &player2) {

    // // Validate the length of input2 and the abilities in it.
    // if (input2.length() != 5) {
    //     return 0;
    // }

    // Set up abilities for player 1
    if (input1 == "-ability1") {
        if (input2 == "default") {
            return 3;
        }
        else {
        for (char &ability : input2) {
            if (ability == 'L' || ability == 'F' || ability == 'D' || ability == 'P'  || ability == 'S' 
            || ability =='B' || ability == 'C' || ability == 'T') {
                player1.addAbilities(ability, default_num);
            }
            else return 0;
        }
        return 1;}
    } 

    // Set up abilities for player 2
    if (input1 == "-ability2") {
         if (input2 == "default") {
            return 4;
        }
        else {
        for (char &ability : input2) {
            if (ability == 'L' || ability == 'F' || ability == 'D' || ability == 'P'  || ability == 'S' 
            || ability =='B' || ability == 'C' || ability == 'T') {
                player2.addAbilities(ability, default_num);
            }
            else return 0;
        }
        return 2;}
    }
    else {return 0;}
}


// ===========================PROCESS COMMAND==============================================================
// Function to process commands: return int:
//      0: Exit the game loop;
//      1: Command executed successfully;
//      2: Command executed unsuccesfully;
int processCommand(
    const string &command, istream &input_stream, // Generalized input stream
    Player *current_player, Player *opponent, Board &board, bool &usedAbility, bool &game_over) {

    // command "quit" ****************change back!!!
    if (command == "quit") {
        cout << "Game exited by user." << endl;
        game_over = true;
        return 0; // Exit the game loop
    }

    // command "move"
    else if (command == "move") {
        char link_name; 
        string dir;
        if (input_stream >> link_name >> dir) {
            bool success = board.move(current_player, opponent, link_name, dir);    // need to change cin to input_stream
            board.notifyObservers(opponent);
            // command is successful
            if (success) {
                return 1;
            }
            else {return 2;}
        } else {
            cout << "Invalid move command. Usage: move <link_name> <direction>" << endl;
            // command is unsuccessful
            return 2;
        }
    } 

    // command "abilities"
    else if (command == "abilities") {
        current_player->display_abilities();
        board.notifyObservers(current_player);
        return 2;
        } 

    // command "ability"
    else if (command == "ability") {
            int id;
            // Extract ability ID from the input stream
            if (input_stream >> id) {
                
                // Check if the ID corresponds to a valid ability
                auto& abilities = current_player->get_list_of_abilities();

                if (id < 1 || id > 8) {
                    cout << "Invalid ability ID: " << id << endl;
                    return 2; // Invalid command
                }

                char c = '0';
                for (const auto& ability : abilities) {
                    if (ability->getId() == id) {
                        c = ability->getChar();
                        break;
                    }
                }
                if (c == '0') {
                    cout << "There's no such ability existing in your ability list! " << c << endl;

                }
                else {
                    cout << "Ability selected: " << c << endl;
                }

        // Ability 1 linkboost-------------------------------------------------------------
                if (id == 1) {
                    cout << "The Ability is linkboost" << endl;
                    char link_name;
                    if (input_stream >> link_name) {

                        if (current_player->useAbility(c, link_name, current_player, opponent)) {
                            usedAbility = true;
                            cout << "The ability LinkBoost is successfully set!" << endl;
                            board.notifyObservers(current_player);
                            return 1; // Successful use of ability
                        } 
                        else 
                        {
                            cout << "Failed to use ability: " << c << endl;
                            board.notifyObservers(current_player);
                            return 2;
                        }
                    }
                } 
        // Ability 2 FireWall-------------------------------------------------------------
                else if (id == 2) {
                    cout << "The Ability is FireWall!" << endl;
                    int row, col;
                    if (input_stream >> row >> col) {
                        // doesn't need link_name field, so put '0'
                        if (current_player->useAbility(c, '0', current_player, opponent, row, col, &board)) {
                            usedAbility = true;
                            cout << "The ability FireWall is successfully set!" << endl;
                            board.notifyObservers(current_player);
                            return 1; // Successful use of ability
                        }
                        else 
                        {
                            cout << "Failed to use ability: " << c << endl;
                            board.notifyObservers(current_player);
                            return 2;
                        }
                    }

                }
        // Ability 3 Download-------------------------------------------------------------
                else if (id == 3) {
                    cout << "The Ability is Download!";
                    char link_name;
                    if (input_stream >> link_name) {
                        cout << "Called on link " << link_name << endl;
                        if (current_player->useAbility(c, link_name, current_player, opponent)) {
                            usedAbility = true;
                            cout << "The ability Download is successfully set on link" << link_name << "!" << endl;
                            board.notifyObservers(current_player);
                            return 1; // Successful use of ability
                        } 
                        else 
                        {
                            cout << "Failed to use ability: " << c << endl;
                            board.notifyObservers(current_player);
                            return 2;
                        }
                    }


                }
        // Ability 4 Polarize-------------------------------------------------------------------
                else if (id == 4) {
                    cout << "The Ability is Scan!";
                    char link_name;
                    if (input_stream >> link_name) {
                        cout << "Called on link " << link_name << endl;
                        if (current_player->useAbility(c, link_name, current_player, opponent)) {
                            usedAbility = true;
                            cout << "The ability Scan is successfully set on link" << link_name << "!" << endl;
                            board.notifyObservers(current_player);
                            return 1; // Successful use of ability
                        } 
                        else 
                        {
                            cout << "Failed to use ability: " << c << endl;
                            board.notifyObservers(current_player);
                            return 2;
                        }
                    }

                }

        // Ability 5 Polarize-------------------------------------------------------------------
                else if (id == 5) {
                    cout << "The Ability is Polarize!";
                    char link_name;
                    if (input_stream >> link_name) {
                        cout << "Called on link " << link_name << endl;
                        if (current_player->useAbility(c, link_name, current_player, opponent)) {
                            usedAbility = true;
                            cout << "The ability Polarize is successfully set on link" << link_name << "!" << endl;
                            board.notifyObservers(current_player);
                            return 1; // Successful use of ability
                        } 
                        else 
                        {
                            cout << "Failed to use ability: " << c << endl;
                            board.notifyObservers(current_player);
                            return 2;
                        }
                    }

                }

        // Ability 6 Brutal-------------------------------------------------------------------
                else if (id == 6) {
                    cout << "The Ability is Brutal!";
                    char link_name;
                    if (input_stream >> link_name) {
                        cout << "Called on link " << link_name << endl;
                        if (current_player->useAbility(c, link_name, current_player, opponent)) {
                            usedAbility = true;
                            cout << "The ability Brutal is successfully set on link" << link_name << "!" << endl;
                            board.notifyObservers(current_player);
                            return 1; // Successful use of ability
                        } 
                        else 
                        {
                            cout << "Failed to use ability: " << c << endl;
                            board.notifyObservers(current_player);
                            return 2;
                        }
                    }

                }
        // Ability 7 Protect-------------------------------------------------------------------
                else if (id == 7) {
                    cout << "The Ability is Protect!";
                    char link_name;
                    if (input_stream >> link_name) {
                        cout << "Called on link " << link_name << endl;
                        if (current_player->useAbility(c, link_name, current_player, opponent)) {
                            usedAbility = true;
                            cout << "The ability Protect is successfully set on link" << link_name << "!" << endl;
                            board.notifyObservers(current_player);
                            return 1; // Successful use of ability
                        } 
                        else 
                        {
                            cout << "Failed to use ability: " << c << endl;
                            board.notifyObservers(current_player);
                            return 2;
                        }
                    }

                }
        // Ability 8 Trade-------------------------------------------------------------------
                else if (id == 8) {
                    cout << "The Ability is Trade!";
                    char link_name;
                    if (input_stream >> link_name) {
                        cout << "Called on link " << link_name << endl;
                        if (current_player->useAbility(c, link_name, current_player, opponent)) {
                            usedAbility = true;
                            cout << "The ability Trade is successfully set on link" << link_name << "!" << endl;
                            board.notifyObservers(current_player);
                            return 1; // Successful use of ability
                        } 
                        else 
                        {
                            cout << "Failed to use ability: " << c << endl;
                            board.notifyObservers(current_player);
                            return 2;
                        }
                    }

                }

             }
                else  
                {
                    cout << "Cannot identity the ability!" << endl;
                    return 2;
                }
            }

    // command "board"
    else if (command == "board") {
            board.notifyObservers(current_player);
            return 2;
        }
    else {
            cout << "Unknown command: " << command << endl;
            return 2;
        }
        
    // Check win condition
    if (current_player->won()) {
        cout << "Player " << current_player->get_id() << " wins!" << endl;
        game_over = true;
        return 0; // Exit the game loop
    }
 
    return 2; // Continue the game loop

}


// ===========================EXECUTE SEQUENCE==============================================================
// Function to read and execute a sequence of commands from a file
// Return int:
//      0: exit the game;
//      1: the current player is player1 ;
//      2: the current player is player2

int executeSequence(const string &filename, Player *current_player, Player *opponent, Board &board, bool &game_over) {
    ifstream sequenceFile(filename);
    if (!sequenceFile.is_open()) {
        cout << "Error: Unable to open sequence file: " << filename << endl;
        return 2;
    }
    string command;
    while (getline(sequenceFile, command) && !game_over) {

        cout << endl;
        cout << "Player " << current_player->get_id() << endl;
        cout << "Executing command: " << command << endl;
        cout << endl;
        stringstream ss(command);
        string actualCommand;
        ss >> actualCommand;

        // Process each command in the file
        // set useAbility to be false for each turn
        bool usedAbility = false;
        int result = processCommand(actualCommand, ss, current_player, opponent, board, usedAbility, game_over);
        board.notifyObservers(current_player);
        // Switch turns after each successful command
        if (result == 1) {
            Player *holder = current_player;
            current_player = opponent;
            opponent = holder;
            continue;
        }
        // command is invalid or execution of the command is unsuccessful
        if (result == 2) {
            continue;
        }
        // exit the game
        if (result == 0) {
            return 0;
        }
    }
    sequenceFile.close();
    if (board.GameOver()) {
        return 0;
    }
    else {
        if (current_player->get_id() == 2) {
            return 2;

        }
        else {
            return 1;}
    }
    
}


int main(int argc, char *argv[]) {
    if (argc != 5) {
        display_usage();
        return 1;
    }

    // Parse command-line arguments--------------------------------------------
    int max_row, max_col;
    string player1_file, player2_file;

    try {
        max_row = stoi(argv[1]);
        max_col = stoi(argv[2]);
        player1_file = argv[3];
        player2_file = argv[4];
    } catch (const exception &e) {
        cerr << "Error parsing arguments: " << e.what() << endl;
        display_usage();
        return 1;
    }

    // Create players--------------------------------------------------------
    Player player1{player1_file, num_abilities, 1};
    Player player2{player2_file, num_abilities, 2};

  // Ask the players whether they want to have ablities in their program 
    int abilitiesEnabled = false;
    // Before the game starts, ask both players if they want abilities enabled
    cout << "Do you want to enable abilities for this game? (y/n): ";
    string choice;
    if (cin >> choice) {
        if (choice == "y" || choice == "Y") {
            abilitiesEnabled = true;
            cout << "Abilities enabled." << endl;
        } else {
            abilitiesEnabled = false;
            cout << "Abilities disabled." << endl;
        }
    }

    if (abilitiesEnabled) {
    // Set up ablities--------------------------------------------------------
    bool ability1_set_up = false;
    bool ability2_set_up = false;
    string default_ability1 = "LFDSP";  
    string default_ability2 = "LFDSP";

    while (!ability1_set_up || !ability2_set_up) {
        // Ask for abilities
        ask_for_ability();
        string input1, input2;
        while (true) {
            cin >> input1 >> input2;
            int result = set_up_abilities(input1, input2, player1, player2);
            if (result == 1) {
                ability1_set_up = true;
                cout << "Successfully set Abilities for player 1!" << endl;
                break;
            }
            if (result == 2) {
                ability2_set_up = true;
                cout << "Successfully ase Abilities for Player 2!" << endl;
                break;
            }
            if (result == 3) {
                int result1 = set_up_abilities("-ability1", default_ability1, player1, player2);
                if (result1 == 1) {
                    cout << "Successfully set up default abilities for player 1!" << endl;
                    ability1_set_up = true;
                    break;
                }
                else {cout << "Failed to set up default abilities for player 1!" << endl;}
                }
            if (result == 4) {
                int result2 = set_up_abilities("-ability2", default_ability2, player1, player2);
                if (result2 == 2) {
                    cout << "Successfully set up default abilities for player 2!" << endl;
                    ability2_set_up = true;
                    break;
                }
                else {cout << "Failed to set up default abilities for player 2!" << endl;}
    
            }
            if (result == 0) {
                cout << "invalid arguments, plase enter again!" << endl;
                ask_for_ability();
            }
        }
    }
    }
    // Create the board--------------------------------------------------------
    Board board(max_row, max_col, 2);

    // Add players to the board-----------------------------------------------
    board.addPlayer(&player1);
    board.addPlayer(&player2);
    board.initialize_grid(player1, player2);


    // Initialize observers--------------------------------------------------
    // Use smart pointers for observers and Xwindow
    std::vector<std::shared_ptr<TextObserver>> textObservers;
    std::vector<std::shared_ptr<GraphicalObserver>> graphicalObservers;

    auto textObserver1 = std::make_shared<TextObserver>(&board, &player1, &player2, board.getGrid(), max_row, max_col);
    auto textObserver2 = std::make_shared<TextObserver>(&board, &player2, &player1, board.getGrid(), max_row, max_col);

    auto window = std::make_shared<Xwindow>(50 * max_col, 50 * max_row);
    auto graphicalObserver1 = std::make_shared<GraphicalObserver>(&board, &player1, &player2, board.getGrid(), window.get(), max_row, max_col);
    auto graphicalObserver2 = std::make_shared<GraphicalObserver>(&board, &player2, &player1, board.getGrid(), window.get(), max_row, max_col);

    // Add them to the container
    textObservers.push_back(textObserver1);
    textObservers.push_back(textObserver2);
    graphicalObservers.push_back(graphicalObserver1);
    graphicalObservers.push_back(graphicalObserver2);

    // Main game loop **********************************************************
    bool game_over = false;
    bool usedAbility = false;
    Player *current_player = &player1;
    Player *opponent = &player2;

    while (!board.GameOver()) {
        cout << "Player " << current_player->get_id() << "'s turn:" << endl;
        string command;

        if (!(cin >> command)) { // Handle EOF (Ctrl-d)
            cout << "Game exited by EOF (Ctrl-d)." << endl;
            break;
        }

        // execute the command sequence in a file
        if (command == "sequence") {
            string filename;
            if (cin >> filename) {
                int result = executeSequence(filename, current_player, opponent, board, game_over);
                if (result == 0) {
                    break;
                }
                else if (result == 1) {
                    current_player = &player1;
                    opponent = &player2;
                    continue;
                }
                else if (result == 2) {
                    cout << "result 2" << endl;
                    current_player = &player2;
                    opponent = &player1;
                    continue;
                }
                else {cout << "Undefined behaviors" << endl;}
            } else {
                cout << "Invalid sequence command. Usage: sequence <file>" << endl;
                continue;
            }
        }
        // Process command from input!
         else {
            // Ends the game
            int result = processCommand(command, cin, current_player, opponent, board, usedAbility, game_over);
            if (result == 0) {
                break;
            }
            // Successful Command Completed Switch turns
            if (result== 1) {
                if (current_player == &player1) {
                    current_player = &player2;
                    opponent = &player1;
                }
                else {
                    current_player = &player1;
                    opponent = &player2;
                }
                continue;

            }
            // Unsuccessful Command 
            if (result == 2) {
                continue;
            }
        }
    }

}
