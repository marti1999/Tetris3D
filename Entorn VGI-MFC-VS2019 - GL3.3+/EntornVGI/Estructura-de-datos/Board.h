#include <list>
//#include "Block.h"

// TODO: límits de la base del taulell 
#define MIN_Z 0
#define MAX_Z 6
#define MIN_X 0
#define MAX_X 6

#define MAX_BLOCK 36

// TODO: altura máxima del taulell en pisos
#define MAX_HEIGHT 10

class Board
{
private:
    /* data */
    
public:
    Board();
    ~Board();
    vector<vector<vector<Block>>> m_blocks;
    int m_height;

    // comprobar si s'ha completat algun pis del taulell
    void checkFloors();
};

Board::Board()
{
    //TODO: inicialitzar m_blocks amb tots m_lliure = true, a mesura que hi hagi blocs al taulell es posaran les dades que faci falta i m_lliure = false.
    //      també es tornaran a posar m_lliure = true quan s'esborri algun bloc
    for (int i = 0; i < MAX_X; i++)
    {
        vector<vector<Block>> x;
        m_blocks.push_back(x);
        for (int j = 0; j < MAX_HEIGHT; j++)
        {
            vector<Block> y;
            m_blocks[i].push_back(y);
            for (int k = 0; k < MAX_Z; k++)
            {
                Block z(i,j,k);
                m_blocks[i][j].push_back(z);
            }

        }
    }
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
