#include <list>
#include "Block.h"

// TODO: límits de la base del taulell 
#define MIN_Z 0
#define MAX_Z 1
#define MIN_X 0
#define MAX_X 1

// TODO: altura máxima del taulell en pisos
#define MAX_HEIGHT 10

class Board
{
private:
    /* data */
    list<Block> m_blocks;
    int m_height;
public:
    Board();
    ~Board();

    // comprobar si s'ha completat algun pis del taulell
    void checkFloors();
};

Board::Board()
{
    m_height = 0;
}

Board::~Board()
{
}

void Board::checkFloors(){
    int completedFloors = 0;
    bool notComplete = false;
    for(int h = 0; h < m_height; h++){

    }
}