#include <list>
#include "Block.h"

// TODO: límits de la base del taulell 
#define MIN_Z 0
#define MAX_Z 1
#define MIN_X 0
#define MAX_X 1

#define MAX_BLOCK 36

// TODO: altura máxima del taulell en pisos
#define MAX_HEIGHT 10

class Board
{
private:
    /* data */
    list<list<Block>> m_blocks;
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
    //list<list<Block>>::iterator it = m_blocks.begin();

    //for(it; it != m_blocks.end(); it++){
    //    if(it.length() == MAX_BLOCK){
    //        // DESTROY pis
    //        im_blocks[it].delete();

    //        // Bucle per baixar les peces de sobre

    //        // Creem un iterador auxiliar que anirá desde el pis on hem esborrat fins al pis mes alt
    //        list<Block>::iterator it_aux = it;
    //        // Per cada bloc dins cada pis decrementem la seva Y
    //        for(it_aux; it_aux != m_blocks.end(); it_aux++){ // Pis
    //            list<Block>::iterator it_block = m_blocks[it_aux].begin();
    //            for(it_block; it_block != it_block.end(); it++){ // Bloc
    //                it_block->setPosition(it_block->getPosX(), it_block->getPosY() - BLOCK_SIZE, it_block->getPosZ());
    //            }
    //        }
    //        
    //    }
    //}
}

// TODO:
    // Funcio (càmera): fa falta un getHeight()
    // 
