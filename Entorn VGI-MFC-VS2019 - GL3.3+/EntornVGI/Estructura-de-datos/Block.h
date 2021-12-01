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

struct aEliminar {
    int xInici;
    int Y;
    int zInici;
    int xFinal;
    int zFinal;
};

class Board
{
private:
    GLuint m_idVao;
    mat4 m_Matriu;
    
public:
    Board();
    ~Board();
    vector<vector<vector<Block>>> m_blocks;
    int m_height;

    int getIdVao() { return m_idVao; }
    mat4 getMatrix() { return m_Matriu; }
    void setIdVao(GLuint idVao) { m_idVao = idVao; }
    void setMatrix(mat4 matriu) { m_Matriu = matriu; }

    // comprobar si s'ha completat algun pis del taulell
    void checkFloors();
    //Esborrar fila del taulell
    vector<aEliminar> deleteRow();
};

Board::Board()
{
    //TODO: inicialitzar m_blocks amb tots m_lliure = true, a mesura que hi hagi blocs al taulell es posaran les dades que faci falta i m_lliure = false.
    //      també es tornaran a posar m_lliure = true quan s'esborri algun bloc
    m_Matriu = glm::mat4(1.0);

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

vector<aEliminar> Board::deleteRow() {
    aEliminar row;
    vector<aEliminar> eliminacions;
    int countX = 0;
    int countZ = 0;
    for (int height = 0; height < MAX_HEIGHT; height++) {
        row.Y = height;
        for (int x_1 = 0; x_1 < MAX_X; x_1++) {
            row.xInici = x_1;
            row.xFinal = x_1;
            for (int z_1 = 0; z_1 < MAX_Z; z_1++) {
                //Si la primera posicio conté un bloc, el registrem com a punt d'inici i possible final
                if (m_blocks[x_1][height][z_1].m_lliure == false) {
                    countZ++;
                    //Si aconseguim arribar al final de la fila, registrem l'index per eliminar-la
                    if (countZ == MAX_Z) {
                        row.zInici = 0;
                        row.zFinal = z_1;
                        eliminacions.push_back(row);
                    }
                }
            }
            countZ = 0;
        }
        countX = 0;
        for (int z_2 = 0; z_2 < MAX_Z; z_2++) {
            row.zInici = z_2;
            row.zFinal = z_2;
            for (int x_2 = 0; x_2 < MAX_X; x_2++) {
                //Si la primera posicio conté un bloc, el registrem com a punt d'inici i possible final
                if (m_blocks[x_2][height][z_2].m_lliure == false) {
                    countX++;
                    //Si aconseguim arribar al final de la fila, registrem l'index per eliminar-la
                    if (countX == MAX_X) {
                        row.xInici = 0;
                        row.xFinal = x_2;
                        eliminacions.push_back(row);
                    }
                }
            }
            countX = 0;
        }
        countZ = 0;
    }
    for (aEliminar el : eliminacions) {
        for (int x = el.xInici; x <= el.xFinal; x++) {
            for (int z = el.zInici; z <= el.zFinal; z++) {
                m_blocks[x][el.Y][z].m_lliure = true;
            }
        }
    }
    return eliminacions;
}

void Board::checkFloors(){
    vector<aEliminar> eliminacions = this->deleteRow();
}

// TODO:
    // Funcio (càmera): fa falta un getHeight()
    // 
