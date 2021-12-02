#include <list>
#include "Block.h"
#include "Board.h"

#include <iostream>
// mapejat que defineix una lletra per cada forma
#define I 33
#define CUBE 34
#define L 35
#define T 36
#define Z 37
#define Y3 3 //rotat sobre Y 270 graus
#define Y2 2 //rotat sobre Y 180 graus
#define Y1 1 //rotat sobre Y 90 graus
#define Y0 0 //rotat sobre Y 0 graus
#define MAXZ 5
#define MAXX 5
#define MAXY 9
#define MINZ 0
#define MINX 0
#define MINY 0


class Piece
{
private:
	/* data */
	char m_form;
	vector<Block> m_blocks;
	vector<Block> m_auxiliar;
	int m_rotacioY;
	GLuint m_idVao;
	mat4 m_Matriu;
	quat m_Quaternio;
	int m_x;
	int m_y;
	int m_z;

	// rotacions



	// colisions
	bool colisionsLimitsTaulellCorrecte();
	bool colisionsBlocsTaulellCorrecte(vector<vector<vector<Block>>>& blocksTaulell);

public:
	Piece() {};
	Piece(int form);
	~Piece();

	// funcions per generar les peces de la forma dessitjada
	void TForm(int x, int y, int z);
	void LForm(int x, int y, int z);
	void CUBEForm(int x, int y, int z);
	void IForm(int x, int y, int z);
	void ZForm(int x, int y, int z);
	int getIdVao() { return m_idVao; }
	mat4 getMatrix() { return m_Matriu; }
	quat getQuaternio() { return m_Quaternio; }
	void onTocarTerra(Board& taula);
	void setX(int x) { m_x = x; }
	void sety(int y) { m_x = y; }
	void setz(int z) { m_x = z; }
	void posIni();
	void rotateQuatXleft();
	void rotateQuatYleft();
	void rotateQuatZleft();
	void rotateQuatXright();
	void rotateQuatYright();
	void rotateQuatZright();

	// rotacions
	bool rotateRightOverY(vector<vector<vector<Block>>>& blocksTaulell);
	bool rotateLeftOverY(vector<vector<vector<Block>>>& blocksTaulell);
	void ViewRotateRightOverY();
	void ViewRotateLeftOverY();



	// moviments
	bool moveRight(vector<vector<vector<Block>>>& blocksTaulell);
	void ViewMoveRight();
	bool moveLeft(vector<vector<vector<Block>>>& blocksTaulell);
	void ViewMoveLeft();
	bool moveUp(vector<vector<vector<Block>>>& blocksTaulell);
	void ViewMoveUp();
	bool moveDown(vector<vector<vector<Block>>>& blocksTaulell);
	void ViewMoveDown();
	bool cauPeca(vector<vector<vector<Block>>>& blocksTaulell);
	void ViewcauPeca();
	void printPunts();
};


void Piece::printPunts() {
	for (int i = 0; i < m_blocks.size(); i++)
	{
		cout << "block: " << i << "--> (" << m_blocks[i].getPosX() << "; " << m_blocks[i].getPosY() << "; " << m_blocks[i].getPosZ() << ") \n";

	}
}

bool Piece::colisionsLimitsTaulellCorrecte() {

	for (Block b : m_blocks) {
		if (b.getPosX() < MINX || b.getPosX() > MAXX) return false;
		if (b.getPosY() < MINY || b.getPosY() > MAXY) return false;
		if (b.getPosZ() < MINZ || b.getPosZ() > MAXZ) return false;
	}
	return true;
}

bool Piece::colisionsBlocsTaulellCorrecte(vector<vector<vector<Block>>>& blocksTaulell) {

	for (Block b : m_blocks) {
		if (blocksTaulell[b.getPosX()][b.getPosY()][b.getPosZ()].m_lliure == false) return false;
	}
	return true;
}


inline void Piece::posIni()
{
	glm::mat4 mat(1.0);
	//m_Matriu = glm::mat4(1.0);
	mat = glm::translate(mat, glm::vec3(5, 19, 5));
	m_Matriu = mat;
	m_Quaternio = quat(1, 0, 0, 0);

	m_rotacioY = Y0;

	m_blocks.clear();
	switch (m_form)
	{
	case I:
		IForm(2, 9, 2);
		break;
	case CUBE:
		CUBEForm(2, 9, 2);
		break;
	case L:
		LForm(2, 9, 2);
		break;
	case T:
		TForm(2, 9, 2);
		break;
	case Z:
		ZForm(2, 9, 2);
	default:
		break;
	}
}



bool Piece::moveRight(vector<vector<vector<Block>>>& blocksTaulell) {
	for (int i = 0; i < m_blocks.size(); i++)
	{
		m_blocks[i].setX(m_blocks[i].getPosX() + 1);
	}

	if (colisionsLimitsTaulellCorrecte()) {
		if (colisionsBlocsTaulellCorrecte(blocksTaulell)) {
			return true;
		}
	}

	moveLeft(blocksTaulell);
	return false;


}

bool Piece::moveLeft(vector<vector<vector<Block>>>& blocksTaulell) {
	for (int i = 0; i < m_blocks.size(); i++)
	{
		m_blocks[i].setX(m_blocks[i].getPosX() - 1);
	}

	if (colisionsLimitsTaulellCorrecte()) {
		if (colisionsBlocsTaulellCorrecte(blocksTaulell)) {
			return true;
		}
	}

	moveRight(blocksTaulell);
	return false;

}

bool Piece::moveDown(vector<vector<vector<Block>>>& blocksTaulell) {
	for (int i = 0; i < m_blocks.size(); i++)
	{
		m_blocks[i].setZ(m_blocks[i].getPosZ() + 1);
	}

	if (colisionsLimitsTaulellCorrecte()) {
		if (colisionsBlocsTaulellCorrecte(blocksTaulell)) {
			return true;
		}
	}

	moveUp(blocksTaulell);
	return false;

}

bool Piece::moveUp(vector<vector<vector<Block>>>& blocksTaulell) {
	for (int i = 0; i < m_blocks.size(); i++)
	{
		m_blocks[i].setZ(m_blocks[i].getPosZ() - 1);
	}

	if (colisionsLimitsTaulellCorrecte()) {
		if (colisionsBlocsTaulellCorrecte(blocksTaulell)) {
			return true;
		}
	}

	moveDown(blocksTaulell);
	return false;

}

bool Piece::rotateRightOverY(vector<vector<vector<Block>>>& blocksTaulell) {
	rotateQuatYright();

	if (colisionsLimitsTaulellCorrecte()) {
		if (colisionsBlocsTaulellCorrecte(blocksTaulell)) {
			return true;
		}
	}

	rotateQuatYleft();
	return false;
}

bool Piece::rotateLeftOverY(vector<vector<vector<Block>>>& blocksTaulell) {
	rotateQuatYleft();

	if (colisionsLimitsTaulellCorrecte()) {
		if (colisionsBlocsTaulellCorrecte(blocksTaulell)) {
			return true;
		}
	}
	rotateQuatYright();
	
	return false;
}


inline void Piece::rotateQuatXleft()
{
	vec3 pivot(m_blocks.front().getPosX(), m_blocks.front().getPosY(), m_blocks.front().getPosZ());
	for (Block& b : m_blocks)
	{
		vec3 pos(b.getPosX(), b.getPosY(), b.getPosZ());
		vec3 new_pos = (pos - pivot) * quat(0.707106, -0.707106, 0, 0) + pivot;
		b.setX(round(new_pos.x));
		b.setY(round(new_pos.y));
		b.setZ(round(new_pos.z));
	}
}

inline void Piece::rotateQuatYleft()
{
	vec3 pivot(m_blocks.front().getPosX(), m_blocks.front().getPosY(), m_blocks.front().getPosZ());
	for (Block& b : m_blocks)
	{
		vec3 pos(b.getPosX(), b.getPosY(), b.getPosZ());
		vec3 new_pos = (pos - pivot) * quat(0.707106, 0, -0.707106, 0) + pivot;
		b.setX(round(new_pos.x));
		b.setY(round(new_pos.y));
		b.setZ(round(new_pos.z));
	}
}

inline void Piece::rotateQuatZleft()
{
	vec3 pivot(m_blocks.front().getPosX(), m_blocks.front().getPosY(), m_blocks.front().getPosZ());
	for (Block& b : m_blocks)
	{
		vec3 pos(b.getPosX(), b.getPosY(), b.getPosZ());
		vec3 new_pos = (pos - pivot) * quat(0.707106, 0, 0, -0.707106) + pivot;
		b.setX(round(new_pos.x));
		b.setY(round(new_pos.y));
		b.setZ(round(new_pos.z));
	}
}

inline void Piece::rotateQuatXright()
{
	vec3 pivot(m_blocks.front().getPosX(), m_blocks.front().getPosY(), m_blocks.front().getPosZ());
	for (Block& b : m_blocks)
	{
		vec3 pos(b.getPosX(), b.getPosY(), b.getPosZ());
		vec3 new_pos = (pos - pivot) * quat(0.707106, 0.707106, 0, 0) + pivot;
		b.setX(round(new_pos.x));
		b.setY(round(new_pos.y));
		b.setZ(round(new_pos.z));
	}
}

inline void Piece::rotateQuatYright()
{
	vec3 pivot(m_blocks.front().getPosX(), m_blocks.front().getPosY(), m_blocks.front().getPosZ());
	for (Block& b : m_blocks)
	{
		vec3 pos(b.getPosX(), b.getPosY(), b.getPosZ());
		vec3 new_pos = (pos - pivot) * quat(0.707106, 0, 0.707106, 0) + pivot;
		b.setX(round(new_pos.x));
		b.setY(round(new_pos.y));
		b.setZ(round(new_pos.z));
	}
}

inline void Piece::rotateQuatZright()
{
	vec3 pivot(m_blocks.front().getPosX(), m_blocks.front().getPosY(), m_blocks.front().getPosZ());
	for (Block& b : m_blocks)
	{
		vec3 pos(b.getPosX(), b.getPosY(), b.getPosZ());
		vec3 new_pos = (pos - pivot) * quat(0.707106, 0, 0, 0.707106) + pivot;
		b.setX(round(new_pos.x));
		b.setY(round(new_pos.y));
		b.setZ(round(new_pos.z));
	}
}


void Piece::ViewRotateRightOverY()
{
	m_Quaternio = m_Quaternio * quat(0.7071, 0, -0.7071, 0);
}

void Piece::ViewRotateLeftOverY()
{
	m_Quaternio = m_Quaternio * quat(0.7071, 0, 0.7071, 0);
}

void Piece::ViewMoveUp()
{
	m_Matriu = glm::translate(m_Matriu, glm::vec3(0.0f, 0.0f, -2));
}

void Piece::ViewMoveDown()
{
	m_Matriu = glm::translate(m_Matriu, glm::vec3(0.0f, 0.0f, 2));
}
void Piece::ViewMoveRight()
{
	m_Matriu = glm::translate(m_Matriu, glm::vec3(2, 0, 0.0f));
}

void Piece::ViewMoveLeft()
{
	m_Matriu = glm::translate(m_Matriu, glm::vec3(-2, 0.0f, 0.0f));
}



void Piece::TForm(int x, int y, int z) {
	//El primer bloc sera sempre el pivot el pivot.
	Block BlockFromPiece(0, 0, 0);
	BlockFromPiece.setPosition(x, y, z);         //Per defecte ja ve a 0,0,0
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(x + 1, y, z);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(x - 1, y, z);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(x, y - 1, z);
	m_blocks.push_back(BlockFromPiece);

	/*

	0   0   0
	3   1   2
	0   4   0

	*/

}
void Piece::LForm(int x, int y, int z) {
	//El primer bloc sera sempre el pivot.
	Block BlockFromPiece(0, 0, 0);
	BlockFromPiece.setPosition(x, y, z);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(x, y - 1, z);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(x, y - 2, z);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(x + 1, y - 2, z);
	m_blocks.push_back(BlockFromPiece);

	/*

	0   1   0
	0   2   0
	0   3   4

	*/





}
void Piece::CUBEForm(int x, int y, int z) {
	//El primer bloc sera sempre el pivot.
	Block BlockFromPiece(0, 0, 0);
	BlockFromPiece.setPosition(x, y, z);  //Per defecte ja ve a 0,0,0
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(x - 1, y, z);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(x - 1, y - 1, z);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(x, y - 1, z);
	m_blocks.push_back(BlockFromPiece);

	/*

	2   1
	3   4

	*/





}
void Piece::IForm(int x, int y, int z) {
	//El primer bloc sera sempre el pivot.
	Block BlockFromPiece(0, 0, 0);
	BlockFromPiece.setPosition(x, y, z);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(x, y - 1, z);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(x, y - 2, z);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(x, y - 3, z);
	m_blocks.push_back(BlockFromPiece);



	/*

	0   0   1   0
	0   0   2   0
	0   0   3   0
	0   0   4   0

	*/
}

void Piece::ZForm(int x, int y, int z) {
	Block BlockFromPiece(0, 0, 0);
	BlockFromPiece.setPosition(x, y, z);  //Per defecte ja ve a 0,0,0
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(x + 1, y - 1, z);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(x, y - 1, z);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(x - 1, y, z);
	m_blocks.push_back(BlockFromPiece);

	/*

	0   0   0
	2   1   0
	0   3   4

	*/


}

void Piece::onTocarTerra(Board& taula)
{
	int x = 0, y = 0, z = 0;
	for (Block b : m_blocks)
	{
		b.getPosicions(x, y, z);
		taula.m_blocks[x][y][z].fixBlock();
		taula.m_blocks[x][y][z].setIdVao(m_idVao + 7);
	}
}


Piece::Piece(int form)
{
	m_form = form;
	m_rotacioY = Y0;
	m_idVao = form;
	m_Matriu = glm::mat4(1.0);
	m_Quaternio = quat(1, 0, 0, 0);

	// creem 4 blocs per cada llista de blocs
	switch (form)
	{
	case T:
		TForm(2, 9, 2);
		break;
	case L:
		LForm(2, 9, 2);
		break;
	case CUBE:
		CUBEForm(2, 9, 2);
		break;
	case I:
		IForm(2, 9, 2);
		break;
	case Z:
		ZForm(2, 9, 2);
	default:
		break;
	}
}





bool Piece::cauPeca(vector<vector<vector<Block>>>& blocksTaulell) {




	if (colisionsLimitsTaulellCorrecte()) {



		for (int i = 0; i < m_blocks.size(); i++)
		{
			// comprovació amb fi del taulell
			if (m_blocks[i].getPosY() <= MINY)
			{
				for (Block b : m_blocks) {
					blocksTaulell[b.getPosX()][b.getPosY()][b.getPosZ()].m_lliure = false;
					blocksTaulell[b.getPosX()][b.getPosY()][b.getPosZ()].setIdVao(m_idVao + 5);
				}
				return false;
			}
			// comprovació amb blocs ja colocats
			if (blocksTaulell[m_blocks[i].getPosX()][m_blocks[i].getPosY() - 1][m_blocks[i].getPosZ()].m_lliure == false)
			{
				for (Block b : m_blocks) {
					blocksTaulell[b.getPosX()][b.getPosY()][b.getPosZ()].m_lliure = false;
					blocksTaulell[b.getPosX()][b.getPosY()][b.getPosZ()].setIdVao(m_idVao + 5);
				}
				return false;
			}
		}

		// si arribem fins aquí significa que és un moviment vàlid, guardem les noves posicions
		for (int i = 0; i < m_blocks.size(); i++)
		{
			m_blocks[i].setY(m_blocks[i].getPosY() - 1);

		}
		return true;

	}
	return false;
}

void Piece::ViewcauPeca()
{
	m_Matriu = glm::translate(m_Matriu, glm::vec3(0.0f, -2, 0.0f));
}


Piece::~Piece()
{

}

