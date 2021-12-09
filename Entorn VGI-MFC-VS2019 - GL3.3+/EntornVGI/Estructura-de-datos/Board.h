#include <list>
#include <queue>
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
    int xInici;
    int zInici;
    int xFinal;
    int yInici;
    int zFinal;
    vector<int> y;
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
    void clear();
    vector<vector<vector<Block>>> m_blocks;
    int m_height;

    int getIdVao() { return m_idVao; }
    mat4 getMatrix() { return m_Matriu; }
    void setIdVao(GLuint idVao) { m_idVao = idVao; }
    void setMatrix(mat4 matriu) { m_Matriu = matriu; }

    // comprobar si s'ha completat algun pis del taulell
    bool checkFloors();
    //Esborrar fila del taulell
    vector<aEsborrar> deleteRow();

    //hernan 01/12/2021
    vector<aEsborrar> fila;
    void caureFila(vector<aEsborrar> fila);
    void reiniciaCanvis();
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
    this->setupTest3();
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
    bool repetida = false;
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
                        for (int el = 0; el < eliminacions.size(); el++) {
                            if ((row.xInici == eliminacions[el].xInici) && (row.xFinal == eliminacions[el].xFinal) &&
                                (row.yInici != eliminacions[el].yInici) && (row.zInici == eliminacions[el].zInici) &&
                                (row.zFinal == eliminacions[el].zFinal)) {
                                eliminacions[el].y.push_back(row.yInici);
                                repetida = true;
                            }
                        }
                        if (!repetida) {
                            row.y.push_back(row.yInici);
                            eliminacions.push_back(row);
                        }
                        row.y.clear();
                        repetida = false;
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
                        for (int el = 0; el < eliminacions.size(); el++) {
                            if ((row.xInici == eliminacions[el].xInici) && (row.xFinal == eliminacions[el].xFinal) &&
                                (row.yInici != eliminacions[el].yInici) && (row.zInici == eliminacions[el].zInici) &&
                                (row.zFinal == eliminacions[el].zFinal)) {
                                eliminacions[el].y.push_back(row.yInici);
                                repetida = true;
                            }
                        }
                        if (!repetida) {
                            row.y.push_back(row.yInici);
                            eliminacions.push_back(row);
                        }
                        row.y.clear();
                        repetida = false;
                    }
                }
            }
            countX = 0;
        }
        countZ = 0;
    }
    /*for (aEsborrar el : eliminacions) {
        el.y.push_back(MAX_HEIGHT);
    }*/

    for (aEsborrar el : eliminacions) {
        for (int x = el.xInici; x <= el.xFinal; x++) {
            for (int z = el.zInici; z <= el.zFinal; z++) {
                for (int pis = 0; pis < el.y.size(); pis++)
                    m_blocks[x][el.y[pis]][z].m_lliure = true;
            }
        }
    }
    return eliminacions;
}

void Board::caureFila(vector<aEsborrar> fila)
{
    
    

    //Recorrer cada elemento del vector. Que será cada fila a bajar
    for (int i = 0; i < fila.size(); i++) { //i itera el vector

  

        //Si Z no cambia significa que se moverá por el eje X y que lo que cambiará será el eje X a cada bloque avanzado
        //Con lo cual iterar sobre el eje X
        if (fila[i].zInici == fila[i].zFinal) { //z no es mou, z es z
            for (int x = fila[i].xInici; x <= fila[i].xFinal; x++) { //j sera la nostra x

                queue<int> yQueue;
                for (int f : fila[i].y) {
                    yQueue.push(f);
                }

                int levels = 1;
                int oldLevels = 1;
                int currentY, upperY;
                while (!yQueue.empty())
                {
                    currentY = yQueue.front();
                    yQueue.pop();
                    
                    upperY;
                    if (yQueue.empty())
                    {
                        upperY = MAX_HEIGHT;
                    }
                    else {
                        upperY = yQueue.front();
                    }
                    
                    //Para cada bloque de la fila, bajamos 1 la altura
                    for (int y = currentY+oldLevels; y < upperY; y++) { //q sera la nostra y

                        if (!m_blocks[x][y][fila[i].zInici].moguda) { //Només entrarem si NO ha estat moguda
                            //No hago la comprobación de si q-1 está m_lliure porque en principio Álex ya lo ha hecho y me asegura que lo estará
                            m_blocks[x][y-levels][fila[i].zInici].m_lliure = m_blocks[x][y][fila[i].zInici].m_lliure;
                            m_blocks[x][y-levels][fila[i].zInici].setIdVao(m_blocks[x][y][fila[i].zInici].getIdVao());
                            m_blocks[x][y][fila[i].zInici].m_lliure = true;

                            //Com no ha estat moguda indiquem que ara ja ho està
                            m_blocks[x][y][fila[i].zInici].swapMoguda();
                        }
                        //Si ja havia sigut moguda, no necessitem baixar-la, doncs ja ho aviem fet. Seguim iterant
                    }
                    oldLevels = levels;
                    levels++;
                }
            }
        }

        //Si X no cambia significa que se moverá por el eje X y que lo que cambiará será el eje Z a cada bloque avanzado
        //Con lo cual iterar sobre el eje Z
        if (fila[i].xInici == fila[i].xFinal) { //x no es mou, x es x
            for (int z = fila[i].zInici; z <= fila[i].zFinal; z++) { //j sera la nostra z


                queue<int> yQueue;
                for (int f : fila[i].y) {
                    yQueue.push(f);
                }

                int levels = 1;
                int oldLevels = 1;
                int currentY, upperY;
                while (!yQueue.empty())
                {
                    currentY = yQueue.front();
                    yQueue.pop();

                    upperY;
                    if (yQueue.empty())
                    {
                        upperY = MAX_HEIGHT;
                    }
                    else {
                        upperY = yQueue.front();
                    }

                    //Para cada bloque de la fila, bajamos 1 la altura
                    for (int y = currentY + oldLevels; y < upperY; y++) { //q sera la nostra y

                        if (!m_blocks[fila[i].xInici][y][z].moguda) { //Només entrarem si NO ha estat moguda
                        //No hago la comprobación de si q-1 está m_lliure porque en principio Álex ya lo ha hecho y me asegura que lo estará
                            m_blocks[fila[i].xInici][y - levels][z].m_lliure = m_blocks[fila[i].xInici][y][z].m_lliure;
                            m_blocks[fila[i].xInici][y - levels][z].setIdVao(m_blocks[fila[i].xInici][y][z].getIdVao());
                            m_blocks[fila[i].xInici][y][z].m_lliure = true;

                            //Com no ha estat moguda indiquem que ara ja ho està
                            m_blocks[fila[i].xInici][y][z].swapMoguda();
                        }
                        //Si ja havia sigut moguda, no necessitem baixar-la, doncs ja ho aviem fet. Seguim iterant
                    }
                    oldLevels = levels;
                    levels++;
                }


             
            }
        }
    }
    //Avans de sortir posem tots i cada un dels blocks del taulell a moguda = false
    reiniciaCanvis();
}

void Board::reiniciaCanvis()
{
    for (int i = 0; i < MAX_Z; i++) {
        for (int j = 0; j < MAX_X; j++) {
            for (int q = 0; q < MAX_HEIGHT; q++) {
                m_blocks[j][q][i].moguda = false;
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
