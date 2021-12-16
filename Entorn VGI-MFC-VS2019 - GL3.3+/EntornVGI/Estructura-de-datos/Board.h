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



//afegit hernan 01/12/2021
struct aEsborrar {
    int xInici = 0;
    int yInici = 0;
    int zInici = 0;
    int xFinal = 0;
    int zFinal = 0;
};
//fi afegit hernan

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
    int m_punts;

    void clear();
    int getIdVao() { return m_idVao; }
    mat4 getMatrix() { return m_Matriu; }
    void setIdVao(GLuint idVao) { m_idVao = idVao; }
    void setMatrix(mat4 matriu) { m_Matriu = matriu; }
    
    vector<int> getPunts();

    // comprobar si s'ha completat algun pis del taulell
    bool checkFloors();
    //Esborrar fila del taulell
    vector<aEsborrar> deleteRow();

    //hernan 01/12/2021
    vector<aEsborrar> fila;
    void caureFila(vector<aEsborrar> fila);
    //fi hernan

    // Llistat de tests:
    void setupTest1();  /* Cas: eliminar múltiples files no consecutives en el eix Y */
    void setupTest2();  /* Cas: eliminar dues files encreuades a la vegada */
    void setupTest3();  /* Cas: eliminar dues files encreuades (2 en un eix i 1 en l'altre) a la vegada */
    // Fi llistat
};

Board::Board()
{
    //TODO: inicialitzar m_blocks amb tots m_lliure = true, a mesura que hi hagi blocs al taulell es posaran les dades que faci falta i m_lliure = false.
    //      també es tornaran a posar m_lliure = true quan s'esborri algun bloc
    m_Matriu = glm::mat4(1.0);
    m_punts = 0;
    
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

    // Selecció del test a continuació (descomentar i canviar al setup de test desitjat)
    //this->setupTest3();
}

Board::~Board()
{
}

void Board::clear() {
    m_Matriu = glm::mat4(1.0);

    m_blocks.clear();

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
                Block z(i, j, k);
                m_blocks[i][j].push_back(z);
            }

        }
    }
    m_height = 0;
}

vector<aEsborrar> Board::deleteRow() {
    aEsborrar row;
    vector<aEsborrar> eliminacions;
    int countX = 0;
    int countZ = 0;
    for (int height = 0; height < MAX_HEIGHT; height++) {
        row.yInici = height;
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
    m_punts += eliminacions.size()*(100 * eliminacions.size());
    for (aEsborrar el : eliminacions) {
        for (int x = el.xInici; x <= el.xFinal; x++) {
            for (int z = el.zInici; z <= el.zFinal; z++) {
                m_blocks[x][el.yInici][z].m_lliure = true;
            }
        }
    }
    return eliminacions;
}

void Board::caureFila(vector<aEsborrar> fila) {
    bool changed = false;
    for (int y = MAX_HEIGHT; y >= 0; y--) {
        for (aEsborrar f : fila) {
            if (f.yInici == y) {
                for (int x = f.xInici; x <= f.xFinal; x++) {
                    for (int z = f.zInici; z <= f.zFinal; z++) {
                        if (!m_blocks[x][y][z].moguda) {
                            for (int h = y; h < MAX_HEIGHT; h++) {
                                if (((h + 1) < MAX_HEIGHT) && (m_blocks[x][h][z].moguda == false)) {
                                    m_blocks[x][h][z].m_lliure = m_blocks[x][h + 1][z].m_lliure;
                                    m_blocks[x][h][z].moguda = true;
                                    changed = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (changed == true) {
            for (int x = 0; x < MAX_X; x++) {
                for (int z = 0; z < MAX_Z; z++) {
                    for (int h = y; h < MAX_HEIGHT; h++)
                        m_blocks[x][h][z].moguda = false;
                }
            }
        }
    }
}


bool Board::checkFloors(){
    vector<aEsborrar> eliminacions = this->deleteRow();
    if (eliminacions.size() != 0)
    {
        // ha trobat files a eliminar
        caureFila(eliminacions);
        return true;
    }

    // no ha trobat files a eliminar
    return false;
}

vector<int> Board::getPunts() {
    vector<int> p_inv;
    vector<int> p;
    int punts = m_punts;
    while (punts >= 10) {
        p_inv.push_back(punts % 10);
        punts = punts / 10;
    }
    //if(punts != 0)
    p_inv.push_back(punts);

    for (int i = p_inv.size()-1; i >= 0; i--) {
        p.push_back(p_inv.back());
        p_inv.pop_back();
    }
    return p;
}

void Board::setupTest1()    /* Cas: eliminar múltiples files no consecutives en el eix Y */
{
    m_blocks[0][0][2].m_lliure = false;
    m_blocks[1][0][2].m_lliure = false;
    m_blocks[3][0][2].m_lliure = false;
    m_blocks[4][0][2].m_lliure = false;
    m_blocks[5][0][2].m_lliure = false;
    m_blocks[0][1][2].m_lliure = false;
    m_blocks[4][1][2].m_lliure = false;
    m_blocks[5][1][2].m_lliure = false;
    m_blocks[0][2][2].m_lliure = false;
    m_blocks[4][2][2].m_lliure = false;
    m_blocks[5][2][2].m_lliure = false;
    m_blocks[0][3][2].m_lliure = false;
    m_blocks[1][3][2].m_lliure = false;
    m_blocks[3][3][2].m_lliure = false;
    m_blocks[4][3][2].m_lliure = false;
    m_blocks[5][3][2].m_lliure = false;
    m_blocks[4][4][2].m_lliure = false;
    m_blocks[5][4][2].m_lliure = false;
}

void Board::setupTest2()    /* Cas: eliminar dues files encreuades a la vegada */
{
    m_blocks[0][0][2].m_lliure = false;
    m_blocks[1][0][2].m_lliure = false;
    m_blocks[3][0][2].m_lliure = false;
    m_blocks[4][0][2].m_lliure = false;
    m_blocks[5][0][2].m_lliure = false;
    m_blocks[2][0][0].m_lliure = false;
    m_blocks[2][0][1].m_lliure = false;
    m_blocks[2][0][3].m_lliure = false;
    m_blocks[2][0][4].m_lliure = false;
    m_blocks[2][0][5].m_lliure = false;
    m_blocks[0][1][2].m_lliure = false;
    m_blocks[4][1][2].m_lliure = false;
    m_blocks[5][1][2].m_lliure = false;
    m_blocks[4][2][2].m_lliure = false;
    m_blocks[5][2][2].m_lliure = false;
    m_blocks[3][2][2].m_lliure = false;
    m_blocks[2][1][4].m_lliure = false;
    m_blocks[2][1][5].m_lliure = false;
}

void Board::setupTest3()    /* Cas: eliminar dues files encreuades (2 en un eix i 1 en l'altre) a la vegada */
{
    m_blocks[0][0][2].m_lliure = false;
    m_blocks[1][0][2].m_lliure = false;
    m_blocks[3][0][2].m_lliure = false;
    m_blocks[4][0][2].m_lliure = false;
    m_blocks[5][0][2].m_lliure = false;
    m_blocks[2][0][0].m_lliure = false;
    m_blocks[2][0][1].m_lliure = false;
    m_blocks[2][0][3].m_lliure = false;
    m_blocks[2][0][4].m_lliure = false;
    m_blocks[2][0][5].m_lliure = false;
    m_blocks[0][1][2].m_lliure = false;
    m_blocks[1][1][2].m_lliure = false;
    m_blocks[3][1][2].m_lliure = false;
    m_blocks[4][1][2].m_lliure = false;
    m_blocks[5][1][2].m_lliure = false;
    m_blocks[4][2][2].m_lliure = false;
    m_blocks[5][2][2].m_lliure = false;
    m_blocks[3][2][2].m_lliure = false;
    m_blocks[2][1][4].m_lliure = false;
    m_blocks[2][1][5].m_lliure = false;
    m_blocks[0][2][2].m_lliure = false;
    m_blocks[0][3][2].m_lliure = false;
    m_blocks[1][3][2].m_lliure = false;
}

// TODO:
    // Funcio (càmera): fa falta un getHeight()
    // 
