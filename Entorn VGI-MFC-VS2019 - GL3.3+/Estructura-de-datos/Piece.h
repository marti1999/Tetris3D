#include <list>
#include "Block.h"
// mapejat que defineix una lletra per cada forma
#define T 'T'
#define L 'L'
#define CUBE 'C'
#define I 'I'

class Piece
{
private:
    /* data */
    char m_form;
    list<Block> m_blocks;
public:
    Piece(char form);
    ~Piece();

    // funcions per generar les peces de la forma dessitjada
    Piece TForm();
    Piece LForm();
    Piece CUBEForm();
    Piece IForm();

    // rotacions
    void rotateRight();
    void rotateLeft();
    void rotateUp();
    void rotateDown();
    

    // moviments
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
};

// TODO: peça en forma de T
Piece Piece::TForm(){
}
// TODO: peça en forma de L
Piece Piece::LForm(){
}
// TODO: peça en forma de CUB
Piece Piece::CUBEForm(){
}
// TODO: peça en forma de I
Piece Piece::IForm(){
}

Piece::Piece(char form)
{
    m_form = form;
    // creem 4 blocs per cada llista de blocs
    switch (form)
    {
    case T:
        TForm();
        break;
    case L:
        LForm();
        break;
    case CUBE:
        CUBEForm();
        break;
    case I:
        IForm();
        break;
    default:
        break;
    }
}

void Piece::rotateRight(){
    // TODO: establir la columna centra de la peça com a eix de traslació
    // TODO: traslladar els blocs cap a la dreta en funció de l'eix Y

    list<Block> blocs_a_rotar; //identificar els blocs a rotar
    list<Block>::iterator it = blocs_a_rotar.begin();

    for(it; it != blocs_a_rotar.end(); it++){

        if(it->getPosX() == 0){
            if(it->getPosZ() == 1)
                it->setPosition(-1, it->getPosY(), 0);
            else
                it->setPosition(1, it->getPosY(), 0);
        }else{
            if(it->getPosX() == 1)
                it->setPosition(0, it->getPosY(), 1);
            else
                it->setPosition(0, it->getPosY(), -1);
        }
    }
    
}
void Piece::rotateLeft(){
    // TODO: establir la columna centra de la peça com a eix de traslació
    // TODO: traslladar els blocs cap a l'esquerra en funció de l'eix Y

    list<Block> blocs_a_rotar; //identificar els blocs a rotar
    list<Block>::iterator it = blocs_a_rotar.begin();

    for(it; it != blocs_a_rotar.end(); it++){
        
        if(it->getPosX() == 0){
            if(it->getPosZ() == 1)
                it->setPosition(1, it->getPosY(), 0);
            else
                it->setPosition(-1, it->getPosY(), 0);
        }else{
            if(it->getPosX() == 1)
                it->setPosition(0, it->getPosY(), -1);
            else
                it->setPosition(0, it->getPosY(), 1);
        }
    }
}
void Piece::rotateUp(){
    // TODO: establir la columna centra de la peça com a eix de traslació
    // TODO: traslladar els blocs cap a la dreta en funció de l'eix Y

    list<Block> blocs_a_rotar; //identificar els blocs a rotar
    list<Block>::iterator it = blocs_a_rotar.begin();

    for(it; it != blocs_a_rotar.end(); it++){
        
        if(it->getPosY() == 0){
            if(it->getPosZ() == 1)
                it->setPosition(it->getPosX(), -1, 0);
            else
                it->setPosition(it->getPosX(), 1, 0);
        }else{
            if(it->getPosX() == 1)
                it->setPosition(it->getPosX(), 0, 1);
            else
                it->setPosition(it->getPosX(), 0, -1);
        }
    }
}
void Piece::rotateDown(){
    // TODO: establir la columna centra de la peça com a eix de traslació
    // TODO: traslladar els blocs cap amunt en funció de l'eix X

    list<Block> blocs_a_rotar; //identificar els blocs a rotar
    list<Block>::iterator it = blocs_a_rotar.begin();

    for(it; it != blocs_a_rotar.end(); it++){
        
        if(it->getPosY() == 0){
            if(it->getPosZ() == 1)
                it->setPosition(it->getPosX(), 1, 0);
            else
                it->setPosition(it->getPosX(), -1, 0);
        }else{
            if(it->getPosX() == 1)
                it->setPosition(it->getPosX(), 0, -1);
            else
                it->setPosition(it->getPosX(), 0, 1);
        }
    }
}

void Piece::moveRight(){
    // TODO: per cada bloc de la peça, moure a la dreta (incrementar X)
}
void Piece::moveLeft(){
    // TODO: per cada bloc de la peça, moure a la esquerra (decrementar X)
}
void Piece::moveUp(){
    // TODO: per cada bloc de la peça, moure amunt (incrementar Z)
}
void Piece::moveDown(){
    // TODO: per cada bloc de la peça, moure avall (decrementar Z)
}

Piece::~Piece()
{
}

