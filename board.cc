#include "board.h"
using namespace std;

// Constructor
Board::Board(int mr, int mc, int np) 
    : max_row{mr}, max_col{mc}, num_player{np} {}

// Destructor
Board::~Board() {}

// Add a player to the board
void Board::addPlayer(Player* player) {
    players.push_back(player);
}

// Get a player by index
Player* Board::getPlayer(int index) const {
    if (index >= 0 && index < static_cast<int>(players.size())) {
        return players[index];
    }
    return nullptr; // Handle out-of-bounds access
}


map<Position, Cell> &Board::getGrid() {
    return grid;
}  

// Initialize the grid with players' links and server ports
void Board::initialize_grid(Player& player1, Player& player2) {
    // Clear the grid if it has any previous data
    grid.clear();

    // Define server ports row and col
    int serverport1_c = (max_col / 2) - 1;
    int serverport2_c = max_col / 2;
    int serverport1_r = 0;
    int serverport2_r = max_row -1;

    // Initialize all cells
    for (int row = 0; row < max_row; ++row) {
        for (int col = 0; col < max_col; ++col) {
            Position pos = {row, col};
            bool isPort = (row == serverport1_r || row == serverport2_r) &&
                          (col == serverport1_c || col == serverport2_c);



            if (isPort && row == serverport1_r) {
                grid[pos] = Cell{nullptr, isPort, 1};
            }
            else if (isPort && row == serverport2_r) {
                grid[pos] = Cell{nullptr, isPort, 2};
            }
            else {
                grid[pos] = Cell{nullptr, isPort, 0};
                }
        }
    }

    // Place Player 1's links
    const auto& links1 = player1.get_links();
    for (size_t i = 0; i < links1.size(); ++i) {
        int col = static_cast<int>(i);
        if (col == serverport1_c || col == serverport2_c) {
            Position pos = {serverport1_r + 1, col};
            grid[pos].link = links1[i].get();
        }
        else {
            Position pos = {serverport1_r, col};
            grid[pos].link = links1[i].get();
        }
    }

    // Place Player 2's links
    const auto& links2 = player2.get_links();
    for (size_t i = 0; i < links2.size(); ++i) {
        int col = static_cast<int>(i);
        if (col == serverport1_c || col == serverport2_c) {
            Position pos = {serverport2_r - 1, col};
            grid[pos].link = links2[i].get();
        }
        else {
        Position pos = {serverport2_r, col};
        grid[pos].link = links2[i].get();}
    }
}

// Find the position of a link on the board
Position Board::find_link_position(Link* link) const {
    for (const auto& [pos, cell] : grid) {
        if (cell.link == link) {
            return pos;
        }
    }
    return {-1, -1}; // Indicate not found
}

// Handle link movement and related actions
bool Board::link_make_move(Player* player, Player* opponent, Link* link, const string& dir, Position pos) {
    Position newPos = pos;
    int step = 1;
    if (link->is_linkboost()) {step *= 2;}

    if (dir == "up") {
        newPos.row -= step;
    } else if (dir == "down") {
        newPos.row += step;
    } else if (dir == "left") {
        newPos.col -= step;
    } else if (dir == "right") {
        newPos.col += step;
    } else {
        cout << "Invalid direction: " << dir << endl;
        return false;
    }

    // Handle interactions with the new position
    Cell& currentCell = grid[pos];
    Cell& nextCell = grid[newPos];
    // Check if the new position is within bounds
    if (newPos.row < 0 || newPos.row >= max_row || newPos.col < 0 || newPos.col >= max_col) {
        if ((newPos.row < 0 && player->get_id() == 2) ||
        (newPos.row >= max_row && player->get_id() == 1)) {
            player->download(*link);
            currentCell.link = nullptr;
            cout << "link " << link->get_name() << " moved across the board!" 
            << " " << link->get_name()  << " is successfully downloaded!" << endl;
            return true;
        }
        else {
            cout << "Invalid move! Can't move out of bounds!" << endl;
            return false;
        }
    }

    if (nextCell.is_server_port) {
        // if the server port is opponent's
        if (player->get_id() != nextCell.get_SP_owner())
        {
            opponent->download(*link);
            currentCell.link = nullptr;
            cout << "link belongs to player " << player->get_id() <<endl;
            cout << "server port belongs to player " << nextCell.get_SP_owner() << endl;
            cout << "link " << link->get_name() << " hits the server port!" 
            << " " << link->get_name()  << " is successfully downloaded!" << endl;
            return true;
        }
        else {
            cout << "Invalid move! Can't move onto your own server port!" << endl;
            return false;
        }
    } 

    if (nextCell.is_fire_wall) {
        // The FireWall belongs to the opponent
        if (nextCell.get_FW_owner() == opponent->get_id()) {
            Link *link = currentCell.link;
            link->set_revealed(true);
            if (link->get_type() == 'V') {
                // download by its owner
                opponent->download(* link);
                link->set_downloaded(true);
                currentCell.link = nullptr;
                cout << "link " << link->get_name() << " is viruses and" << " hits the FireWall!" 
                << " " << link->get_name()  << " is successfully downloaded by player "  << opponent->get_id() << "!" << endl;
                return true;
            }

        }
    }
    
    if (nextCell.link) {
        if (! nextCell.link->is_downloaded())
        {   currentCell.link->set_revealed(true);
            nextCell.link->set_revealed(true);
            cout << "Needs battle with link " << nextCell.link->get_name() << endl;
            return battle(pos, newPos, player, opponent);
            }

    } else {
        nextCell.link = link;
        currentCell.link = nullptr;
        cout << "successfully moved the link!" << endl;
        cout << "( " <<  newPos.row << ", " <<  newPos.col << ") "
        << grid[newPos].link->get_name() << endl;
        return true;
    }
    cout << "Here is the very end of function Board::link_make_move() funcion! And the function returns false!" << endl;
    return false;
}

// Move a link on the board
bool Board::move(Player *player, Player *opponent, char link_name, const string& dir) {
    Link* link = player->find_link(link_name);
    if (!link) {
        cout << "Link not found." << endl;
        return false;
    }
    // Find the current position of the link
    Position currentPos = find_link_position(link);
    if (currentPos.row == -1 && currentPos.col == -1) {
        cout << "Link is no longer on the board." << endl;
        return false;
    }

    // Check for valid direction
    if (dir != "up" && dir != "down" && dir != "left" && dir != "right") {
        throw invalid_argument("Invalid direction.");
        return false;
    }

    // Delegate to Link_make_move
    bool success = link_make_move(player, opponent, link, dir, currentPos);
    if (success) {
        return true;}
    else {
        return false;
    }
}


int Board::getRowSize() const {return max_row;}
int Board::getColSize() const {return max_col;}
Cell & Board::getCell(Position p) { return grid[p];}
const Cell & Board::retriveCell(Position p) const {return grid.at(p);}

// Conduct a battle between two links
bool Board::battle(Position c1, Position c2, Player* p1, Player* p2) {
    Link* link1 = grid[c1].link;
    Link* link2 = grid[c2].link;
    cout << "links are clones" << endl;

    if (!link1 || !link2) return false; // No links to battle
    
    // if link1 is brutal and link2 is not
    if (link1->is_brutal() && !link2->is_brutal()) {
        cout << link1->get_name() << " is brutal!" << endl;
        p1->download(*link2);
        grid[c2].link = nullptr;
        link2->set_revealed(true);
        link2->set_downloaded(true);
        return true;
    }

    // if link2 is brutal and link1 is not
    if (!link1->is_brutal() && link2->is_brutal()) {
        cout << link2->get_name() << " is brutal!" << endl;
        p2->download(*link1);
        grid[c1].link = nullptr;
        link1->set_revealed(true);
        link1->set_downloaded(true);
        return true;
    }

    // if link1 and link2 are both brutal then follow the basic rule
    if (link1->get_strength() > link2->get_strength()) {

        p1->download(*link2);
        grid[c2].link = nullptr;
        grid[c2].link = grid[c1].link;
        grid[c1].link = nullptr;
        link2->set_revealed(true);
        link2->set_downloaded(true);
        return true;
    } else if (link2->get_strength() > link1->get_strength()) {
        p2->download(*link1);
        grid[c1].link = nullptr;
        link1->set_revealed(true);
        link1->set_downloaded(true);
        return true;
    } else {
        // If strengths are equal, initiating player wins
        p1->download(*link2);
        grid[c2].link = nullptr;
        link2->set_revealed(true);
        link2->set_downloaded(true);
        return true;
    }
}


char Board::getState( int row, int col ) const {
    Position p{row, col};
    if (retriveCell(p).link != nullptr) {
        return retriveCell(p).link->get_name();
    }

    if (retriveCell(p).is_server_port) {
        return 'S';
    }
    if (retriveCell(p).is_fire_wall) {
        if (retriveCell(p).FW_owner == 1) {
            return 'm';
        }
        else {return 'w';}
    }
    else {return '.';}

}

// Check if the game is over
bool Board::GameOver() const {
    for (const auto& player : players) {
        if (player->won()) {
            cout << "Player " << player->get_id() << " won the game!" << endl; 
            cout << "Game is over!" << endl;
            return true;
        }
        if (player->lost()) {
            cout << "Player " << player->get_id() << " lost the game!" << endl; 
            cout << "Game is over!" << endl;
            return true;
        }
    }
    return false;
}

void Board::display_board(Player* current_player, Player* opponent) const {
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
                cout << cell.link->get_name();
            } else if (cell.is_server_port) {
                cout << "S";
            } else {
                cout << ".";
            }
        }
        cout << "\n";
    }
    cout << string(max_col, '=') << "\n";

    // Display opponent's info
    opponent->display_player_info();
}


