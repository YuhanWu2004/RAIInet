#include "textobserver.h"
using namespace std;

TextObserver::TextObserver(Board *myBoard, Player *current_player, Player *opponent, map<Position, Cell> &grid,
int max_row, int max_col):
myBoard{myBoard}, current_player{current_player}, opponent{opponent}, grid{grid}, max_row{max_row}, max_col{max_col} {
    myBoard->attach(this);

}

TextObserver::~TextObserver() {
    myBoard->detach(this);
}

Player *TextObserver::getPlayer() const {return current_player;}

void TextObserver::notify() {
    cout << "Current Board State (Player " << current_player->get_id() << "'s turn):\n";

     // Display current player's info
    current_player->display_player_full_info();

    // Display the grid
    cout << string(max_col, '=') << "\n";
    for (int row = 0; row < max_row; ++row) {
        for (int col = 0; col < max_col; ++col) {
            Position pos = {row, col};
            const Cell& cell = grid.at(pos);
            if (cell.link) {
                if (!cell.link->is_downloaded())
                {cout << cell.link->get_name();}
                else {cout << ".";}
            } 
            else if (cell.is_server_port) {
                cout << "S";
            } else if (cell.is_fire_wall) {
                if (cell.get_FW_owner() == 1) {
                    cout << "m";
                }
                if (cell.get_FW_owner() == 2) {
                    cout << "w";
                }
            }
            else {
                cout << ".";
            }
        }
        cout << "\n";
    }
    cout << string(max_col, '=') << "\n";

    // Display opponent's info
    opponent->display_player_info();
}





