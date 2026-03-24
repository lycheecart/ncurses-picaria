#include <ncurses.h>
#include <vector>
#include <map>
#include <string>
#include <random>

/*TODO
disallow highlighting/movement to dest selections to non adjacent nodes
*/

#define BLANKCHAR '.'

enum GameState { 
    begin, 
    placeX0, 
    placeY0,
    placeX1,
    placeY1,
    placeX2,
    placeY2,
    tripletCheck,
    chooseXMover,
    chooseXDest,
    chooseYMover,
    chooseYDest,
    victory
};

enum Direction {
    north,
    northeast,
    east,
    southeast,
    south,
    southwest,
    west,
    northwest
};

class Node {
public:
 Node();
 Node(int id, int row, int col);
 int id;
 int row;
 int col;
 char displayChar;

 Node* nw_node;
 Node*  n_node;
 Node* ne_node;
 Node*  w_node;
 Node*  e_node;
 Node* sw_node;
 Node*  s_node;
 Node* se_node;

 bool centralCheck();
 bool distalCheck(Direction d);
 bool tripletCheck();
 bool samePosition(Node* n);
 bool isAdjacent(Node* n);
};

Node::Node() {
    this->id = -1;
    this->row = 0;
    this->col = 0;
    this->displayChar = BLANKCHAR;
    this->nw_node = (Node*)NULL;
    this-> n_node = (Node*)NULL;
    this->ne_node = (Node*)NULL;
    this-> w_node = (Node*)NULL;
    this-> e_node = (Node*)NULL;
    this->sw_node = (Node*)NULL;
    this-> s_node = (Node*)NULL;
    this->se_node = (Node*)NULL;
}

Node::Node(int id, int row, int col) {
    this->id = id;
    this->row = row;
    this->col = col;
    this->displayChar = BLANKCHAR;
    this->nw_node = (Node*)NULL;
    this-> n_node = (Node*)NULL;
    this->ne_node = (Node*)NULL;
    this-> w_node = (Node*)NULL;
    this-> e_node = (Node*)NULL;
    this->sw_node = (Node*)NULL;
    this-> s_node = (Node*)NULL;
    this->se_node = (Node*)NULL;
}

bool Node::distalCheck(Direction d) {
    switch(d) {
        case north:
            if (this->n_node == (Node*)NULL) {
                return false;
            }
            if (this->n_node->n_node == (Node*)NULL) {
                return false;
            }
            return this->displayChar == this->n_node->displayChar && this->displayChar == this->n_node->n_node->displayChar;
        break;
        case northeast:
            if (this->ne_node == (Node*)NULL) {
                return false;
            }
            if (this->ne_node->ne_node == (Node*)NULL) {
                return false;
            }
            return this->displayChar == this->ne_node->displayChar && this->displayChar == this->ne_node->ne_node->displayChar;
        break;
        case east:
            if (this->e_node == (Node*)NULL) {
                return false;
            }
            if (this->e_node->e_node == (Node*)NULL) {
                return false;
            }
            return this->displayChar == this->e_node->displayChar && this->displayChar == this->e_node->e_node->displayChar;
        break;
        case southeast:
            if (this->se_node == (Node*)NULL) {
                return false;
            }
            if (this->se_node->se_node == (Node*)NULL) {
                return false;
            }
            return this->displayChar == this->se_node->displayChar && this->displayChar == this->se_node->se_node->displayChar;
        break;
        case south:
            if (this->s_node == (Node*)NULL) {
                return false;
            }
            if (this->s_node->s_node == (Node*)NULL) {
                return false;
            }
            return this->displayChar == this->s_node->displayChar && this->displayChar == this->s_node->s_node->displayChar;
        break;
        case southwest:
            if (this->sw_node == (Node*)NULL) {
                return false;
            }
            if (this->sw_node->sw_node == (Node*)NULL) {
                return false;
            }
            return this->displayChar == this->sw_node->displayChar && this->displayChar == this->sw_node->sw_node->displayChar;
        break;
        case west:
            if (this->w_node == (Node*)NULL) {
                return false;
            }
            if (this->w_node->w_node == (Node*)NULL) {
                return false;
            }
            return this->displayChar == this->w_node->displayChar && this->displayChar == this->w_node->w_node->displayChar;
        break;
        case northwest:
            if (this->nw_node == (Node*)NULL) {
                return false;
            }
            if (this->nw_node->nw_node == (Node*)NULL) {
                return false;
            }
            return this->displayChar == this->nw_node->displayChar && this->displayChar == this->nw_node->nw_node->displayChar;
        break;
        default:
            return false;
        break;
    }
}

bool Node::centralCheck() {
    //n s
    if (this->n_node != (Node*)NULL && this->s_node != (Node*)NULL) {
        if (this->displayChar == this->n_node->displayChar && this->displayChar ==  this->s_node->displayChar) {
            return true;
        }
    }

    //ne sw
    if (this->ne_node != (Node*)NULL && this->sw_node != (Node*)NULL) {
        if (this->displayChar == this->ne_node->displayChar && this->displayChar == this->sw_node->displayChar) {
            return true;
        }
    }

    //e w
    if (this->e_node != (Node*)NULL && this->w_node != (Node*)NULL) {
        if (this->displayChar == this->e_node->displayChar && this->displayChar == this->w_node->displayChar) {
            return true;
        }
    }

    //se nw
    if (this->se_node != (Node*)NULL && this->nw_node != (Node*)NULL) {
        if (this->displayChar == this->se_node->displayChar && this->displayChar == this->nw_node->displayChar) {
            return true;
        }
    }

    return false;
}

bool Node::tripletCheck() {
    return this->centralCheck()         ||
           this->distalCheck(north)     ||
           this->distalCheck(northeast) ||
           this->distalCheck(east)      ||
           this->distalCheck(southeast) ||
           this->distalCheck(south)     ||
           this->distalCheck(southwest) ||
           this->distalCheck(west)      ||
           this->distalCheck(northwest);
}

bool Node::samePosition(Node* n) {
    return this->row == n->row && this->col == n->col;
}

bool Node::isAdjacent(Node* n) {
    std::vector<Node*> adjs;

    if (this->nw_node != (Node*)NULL) {
        adjs.push_back(this->nw_node);
    }
    if (this-> n_node != (Node*)NULL) {
        adjs.push_back(this->n_node);
    }
    if (this->ne_node != (Node*)NULL) {
        adjs.push_back(this->ne_node);
    }
    if (this-> w_node != (Node*)NULL) {
        adjs.push_back(this->w_node);
    }
    if (this-> e_node != (Node*)NULL) {
        adjs.push_back(this->e_node);
    }
    if (this->sw_node != (Node*)NULL) {
        adjs.push_back(this->sw_node);
    }
    if (this-> s_node != (Node*)NULL) {
        adjs.push_back(this->s_node);
    }
    if (this->se_node != (Node*)NULL) {
        adjs.push_back(this->se_node);
    }


    std::vector<Node*>::iterator it; 
    for (it = adjs.begin(); it < adjs.end(); it++) {
        if ((*it)->samePosition(n)) {
            return true;
        }
    }
    return false;
}

class Game {
public:
 Game();
 ~Game();
 WINDOW* boardWindow;
 WINDOW* informWindow;
 GameState gameState;
 std::vector<GameState> states;
 std::vector<Node*> nodes;
 Node* selectedNode;
 Node* sourceNode;
 Node* centerNode;
 bool done;

 void selectNorth();
 void selectSouth();
 void selectEast();
 void selectWest();
 void selectNortheast();
 void selectNorthwest();
 void selectSoutheast();
 void selectSouthwest();

 void informState();
 void drawBoard();
 void restartGameplay();
 void proceedState();
 void occupyNode(Node* n, char ch);
 void selectMover(char ch);
 void selectDest(char ch);
 void handleEnter();
 void victoryCheck(Node* n);
};

Game::Game() {
    this->gameState = begin;
    this->done = false;
    states.push_back(begin);
    states.push_back(placeX0);
    states.push_back(placeY0);
    states.push_back(placeX1);
    states.push_back(placeY1);
    states.push_back(placeX2);
    states.push_back(placeY2);
    states.push_back(tripletCheck);
    states.push_back(chooseXMover);
    states.push_back(chooseXDest);
    states.push_back(chooseYMover);
    states.push_back(chooseYDest);
    states.push_back(victory);


/*
    0---0---0
    |\ / \ /|
    | 0   0 |
    |/ \ / \|
    0---0---0
    |\ / \ /|
    | 0   0 |
    |/ \ / \|
    0---0---0

      0 1 2
       3 4
      5 6 7
       8 9
      A B C
*/

    Node* n0 = (new Node( 0,  3,  5));
    Node* n1 = (new Node( 1,  3,  9));
    Node* n2 = (new Node( 2,  3, 13));
    Node* n3 = (new Node( 3,  5,  7));
    Node* n4 = (new Node( 4,  5, 11));
    Node* n5 = (new Node( 5,  7,  5));
    Node* n6 = (new Node( 6,  7,  9));
    Node* n7 = (new Node( 7,  7, 13));
    Node* n8 = (new Node( 8,  9,  7));
    Node* n9 = (new Node( 9,  9, 11));
    Node* nA = (new Node(10, 11,  5));
    Node* nB = (new Node(11, 11,  9));
    Node* nC = (new Node(12, 11, 13));

    this->nodes.push_back(n0);
    this->nodes.push_back(n1);
    this->nodes.push_back(n2);
    this->nodes.push_back(n3);
    this->nodes.push_back(n4);
    this->nodes.push_back(n5);
    this->nodes.push_back(n6);
    this->nodes.push_back(n7);
    this->nodes.push_back(n8);
    this->nodes.push_back(n9);
    this->nodes.push_back(nA);
    this->nodes.push_back(nB);
    this->nodes.push_back(nC);

    n0-> e_node = n1;
    n0-> s_node = n5;
    n0->se_node = n3;

    n1-> w_node = n0;
    n1-> e_node = n2;
    n1->sw_node = n3;
    n1-> s_node = n6;
    n1->se_node = n4;

    n2-> w_node = n1;
    n2->sw_node = n4;
    n2-> s_node = n7;

    n3->nw_node = n0;
    n3->ne_node = n1;
    n3-> e_node = n4;
    n3->sw_node = n5;
    n3-> s_node = n8;
    n3->se_node = n6;

    n4->nw_node = n1;
    n4->ne_node = n2;
    n4-> w_node = n3;
    n4->sw_node = n6;
    n4-> s_node = n9;
    n4->se_node = n7;

    n5-> n_node = n0;
    n5->ne_node = n3;
    n5-> e_node = n6;
    n5-> s_node = nA; 
    n5->se_node = n8;

    n6->nw_node = n3;
    n6-> n_node = n1;
    n6->ne_node = n4;
    n6-> w_node = n5;
    n6-> e_node = n7;
    n6->sw_node = n8;
    n6-> s_node = nB;
    n6->se_node = n9;

    n7->nw_node = n4;
    n7-> n_node = n2;
    n7-> w_node = n6;
    n7->sw_node = n9;
    n7-> s_node = nC;

    n8->nw_node = n5;
    n8-> n_node = n3;
    n8->ne_node = n6;
    n8-> e_node = n9;
    n8->sw_node = nA;
    n8->se_node = nB;

    n9->nw_node = n6;
    n9-> n_node = n4;
    n9->ne_node = n7;
    n9-> w_node = n8;
    n9->sw_node = nB;
    n9->se_node = nC;

    nA-> n_node = n5;
    nA->ne_node = n8;
    nA-> e_node = nB;

    nB->nw_node = n8;
    nB-> n_node = n6;
    nB->ne_node = n9;
    nB-> w_node = nA;
    nB-> e_node = nC;

    nC->nw_node = n9;
    nC-> n_node = n7;
    nC-> w_node = nB;

    this->selectedNode = n0;
    this->centerNode = n6;
}

Game::~Game() {
    this->selectedNode = (Node*)NULL;
    std::vector<Node*>::iterator rit;
    for(rit = this->nodes.end(); rit >= this->nodes.begin(); rit--) {
        delete(*rit);
    }
    this->nodes.clear();
}

void Game::informState() {
    std::string msg = "";
    switch(this->gameState) {
        case begin:
            msg = "begin";
        break;
        case placeX0:
            msg = "place first x";
        break;
        case placeY0:
            msg = "place first y";
        break;
        case placeX1:
            msg = "place second x";
        break;
        case placeY1:
            msg = "place second y";
        break;
        case placeX2:
            msg = "place third x";
        break;
        case placeY2:
            msg = "place third y";
        break;
        case tripletCheck:
            msg = "checking for victory";
        break;
        case chooseXMover:
            msg = "x choose mover";
        break;
        case chooseXDest:
            msg = "x choose destination";
        break;
        case chooseYMover:
            msg = "y choose mover";
        break;
        case chooseYDest:
            msg = "y choose destination";
        break;
        case victory:
            msg = "victory achieved";
        break;
        default:
            msg = "Dunno";
        break;
    }

    mvwprintw(informWindow, 0, 0, "%s", msg.c_str());
    wrefresh(informWindow);
}
void Game::drawBoard() {
    std::vector<Node*>::iterator it;

    for (it = nodes.begin(); it < nodes.end(); it++) {
        mvwaddch(this->boardWindow, (*it)->row, (*it)->col, (*it)->displayChar);
    }
    wmove(this->boardWindow, this->selectedNode->row, this->selectedNode->col);
    wrefresh(this->boardWindow);
}

void Game::restartGameplay() {
    this->drawBoard();
    this->gameState = placeX0;
    this->informState();

    std::vector<Node*>::iterator it;
    for (it = nodes.begin(); it < nodes.end(); it++) {
        (*it)->displayChar = BLANKCHAR;
    }
}

void Game::proceedState() {
    std::vector<GameState>::iterator it;
    int i = 0;
    int next = 0;
    for (it = states.begin(); it < states.end(); it++) {
        if ((*it) == this->gameState) {
            next = (i+1) % states.size();
            this->gameState = states.at(next);
            return;
        }
        i++;
    }
}

void Game::occupyNode(Node* n, char ch) {
    std::map<GameState, GameState> stateMap {
        {placeX0, placeY0}, 
        {placeY0, placeX1}, 
        {placeX1, placeY1}, 
        {placeY1, placeX2}, 
        {placeX2, placeY2}, 
        {placeY2, chooseXMover}, 
        {chooseXMover, chooseXDest}, 
        {chooseXDest, chooseYMover}, 
        {chooseYMover, chooseYDest}, 
        {chooseYDest, chooseXMover} 
    };

    if (n->displayChar == BLANKCHAR) { //n->isUnoccupied()
        n->displayChar = ch;

        if (auto search = stateMap.find(this->gameState); search != stateMap.end()) {
            this->gameState = search->second;
        } 

        victoryCheck(n);
    }
}

void Game::selectMover(char ch) {
    bool legalPiece = this->selectedNode->displayChar == ch;
    if (!legalPiece) {
        return;
    }
    this->sourceNode = this->selectedNode;

    if (this->gameState == chooseXMover) {
        this->gameState = chooseXDest;
    } else if (this->gameState == chooseYMover) {
        this->gameState = chooseYDest;
    }
}

void Game::selectDest(char ch) {
    bool reselectCancel = (this->selectedNode == this->sourceNode);
    if (reselectCancel) {
        if (this->gameState == chooseXDest) {
            this->gameState = chooseXMover;
        }
        if (this->gameState == chooseYDest) {
            this->gameState = chooseYMover;
        }

        return;
    }

    bool adj = this->selectedNode->isAdjacent(this->sourceNode);
    bool destOccupied = (this->selectedNode->displayChar != BLANKCHAR);
    if (destOccupied || !adj) {
        return;
    }

    this->selectedNode->displayChar = this->sourceNode->displayChar;
    this->sourceNode->displayChar = BLANKCHAR;
    this->victoryCheck(selectedNode);

    if (this->gameState == chooseXDest) {
        this->gameState = chooseYMover;
    }
    if (this->gameState == chooseYDest) {
        this->gameState = chooseXMover;
    }
}

void Game::handleEnter() {
    switch(this->gameState) {
        case placeX0:
            if(this->selectedNode != this->centerNode) {
                occupyNode(this->selectedNode, 'X');
            }
        break;
        case placeY0:
            if(this->selectedNode != this->centerNode) {
                occupyNode(this->selectedNode, 'Y');
            }
        break;
        case placeX1:
            if(this->selectedNode != this->centerNode) {
                occupyNode(this->selectedNode, 'X');
            }
        break;
        case placeY1:
            if(this->selectedNode != this->centerNode) {
                occupyNode(this->selectedNode, 'Y');
            }
        break;
        case placeX2:
            if(this->selectedNode != this->centerNode) {
                occupyNode(this->selectedNode, 'X');
            }
        break;
        case placeY2:
            if(this->selectedNode != this->centerNode) {
                occupyNode(this->selectedNode, 'Y');
            }
        break;
        case chooseXMover:
            this->selectMover('X');
        break;
        case chooseXDest:
            this->selectDest('X');
        break;
        case chooseYMover:
            this->selectMover('Y');
        break;
        case chooseYDest:
            this->selectDest('Y');
        break;
        case victory:
        break;

        default:
        break;
    }
}

void Game::victoryCheck(Node* n) {
    if (n->tripletCheck()) {
        this->gameState = victory;
    }
}

void Game::selectNorth() {
    if (this->selectedNode->n_node == (Node*)NULL) {
        return;
    }
    this->selectedNode = this->selectedNode->n_node;
}

void Game::selectSouth() {
    if (this->selectedNode->s_node == (Node*)NULL) {
        return;
    }
    this->selectedNode = this->selectedNode->s_node;
}

void Game::selectEast() {
    if (this->selectedNode->e_node == (Node*)NULL) {
        return;
    }
    this->selectedNode = this->selectedNode->e_node;
}

void Game::selectWest() {
    if (this->selectedNode->w_node == (Node*)NULL) {
        return;
    }
    this->selectedNode = this->selectedNode->w_node;
}

void Game::selectNorthwest() {
    if (this->selectedNode->nw_node == (Node*)NULL) {
        return;
    }
    this->selectedNode = this->selectedNode->nw_node;
}
void Game::selectNortheast() {
    if (this->selectedNode->ne_node == (Node*)NULL) {
        return;
    }
    this->selectedNode = this->selectedNode->ne_node;
}
void Game::selectSouthwest() {
    if (this->selectedNode->sw_node == (Node*)NULL) {
        return;
    }
    this->selectedNode = this->selectedNode->sw_node;
}
void Game::selectSoutheast() {
    if (this->selectedNode->se_node == (Node*)NULL) {
        return;
    }
    this->selectedNode = this->selectedNode->se_node;
}


int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(1);
    keypad(stdscr, TRUE);
    touchwin(stdscr);

    Game* game = new Game();

    game->boardWindow  = subwin(stdscr, 14, 22, 1, 0);
    game->informWindow = subwin(stdscr, 14, 22, 1, 23);

    game->restartGameplay();

    refresh();
    wrefresh(game->informWindow);
    wrefresh(game->boardWindow);

    while (!(game->done)) {
        wmove(game->boardWindow, game->selectedNode->row, game->selectedNode->col);

        int ch = getch();

        switch(ch) {
            case KEY_F(6):
                game->done = true;
            break;

            case 'q':
                game->done = true;
            break;

            case 'h':
                game->selectWest();
            break;
            case 'j':
                game->selectSouth();
            break;
            case 'k':
                game->selectNorth();
            break;
            case 'l':
                game->selectEast();
            break;
            case 'y':
                game->selectNorthwest();
            break;
            case 'u':
                game->selectNortheast();
            break;
            case 'n':
                game->selectSoutheast();
            break;
            case 'b':
                game->selectSouthwest();
            break;
            case 'p':
                game->proceedState();
            break;
            case 'r':
                game->restartGameplay();
            break;
            case '\n':
                game->handleEnter();
            break;

            case ' ':
            break;

            case 'f':
            break;

            default:
            break;
        } //switch input char

        wclear(game->informWindow);
        game->informState();

        if (game->gameState == victory) {
            mvwprintw(game->informWindow, 1, 0, "%s", "q: quit");
            mvwprintw(game->informWindow, 2, 0, "%s", "r: restart");
            wrefresh(game->informWindow);
        }

        game->drawBoard();
    } //input-process-output loop

    delwin(game->boardWindow);
    delwin(game->informWindow);
    delete(game);

    endwin();
    return 0;
}
