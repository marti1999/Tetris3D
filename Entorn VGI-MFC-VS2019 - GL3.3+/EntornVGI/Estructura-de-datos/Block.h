#include <vector>
#include <list>

#define BLOCK_SIZE 1 //TEMPORAL, falta decidir
#define POSICIO 3

using namespace std;

class Block
{
private:
    /* data */
    vector<int> m_posicio; // posició del bloc al taulell, es tracta d'un vector(x, y, z)
    bool m_collisionable; // indicador que utilitzarem per comprovar les col·lisions entre els blocs
    bool m_fixed; // indicador de si el bloc ha sigut col·locat o no
    
public:
    Block();
    void setX(int x);
    void setZ(int z);
    void setY(int y);
    ~Block();
    bool detectCollision(list<Block> setBlocks);

    // getters de la posició
    int getPosX(){return m_posicio[0];}
    int getPosY(){return m_posicio[1];}
    int getPosZ(){return m_posicio[2];}
    void setPosition(int x, int y, int z);
    void setFixed(bool fixed);

    bool m_lliure; // no es pot tenir en un vector<vector<vector<Block>>> posicions en null, així que quan no hi hagi un bloc realment hi haurà un block tenint lliure = true

};

Block::Block()
{
    for(int i = 0; i < 3; i++)
        m_posicio.push_back(0);
    m_collisionable = true;
    m_fixed = false;
}

void Block::setX(int x) {
    m_posicio[0] = x;
}
void Block::setY(int y) {
    m_posicio[1] = y;
}
void Block::setZ(int z) {
    m_posicio[2] = z;
}

void Block::setPosition(int x, int y, int z){
    m_posicio[0] = x;
    m_posicio[1] = y;
    m_posicio[2] = z;
}

void Block::setFixed(bool fixed) {
    m_fixed = fixed;
}

bool Block::detectCollision(list<Block> setBlocks){
    // TODO: iterar per cada bloc, return true si coincideix la posicio del bloc_actual amb qualsevol de la llista
    return true;
}

Block::~Block()
{
}
