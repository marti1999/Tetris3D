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
	int m_x;
	int m_y;
	int m_z;

	// rotacions
	void rotateTRigthOverY();
	void rotateTLeftOverY();
	void rotateLRightOverY();
	void rotateLLeftOverY();
	void rotateCubeRightOverY();
	void rotateCubeLeftOverY();
	void rotateIRightOverY();
	void rotateILeftOverY();
	void rotateZRightOverY();
	void rotateZLeftOverY();


	// colisions
	bool colisionsLimitsTaulellCorrecte();
	bool colisionsBlocsTaulellCorrecte(vector<vector<vector<Block>>>& blocksTaulell);
	bool check_move_colision(int a, vector<vector<vector<Block>>>& blocksTaulell);

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
	void onTocarTerra(Board& taula);
	void setX(int x) { m_x = x; }
	void sety(int y) { m_x = y; }
	void setz(int z) { m_x = z; }
	void posIni();

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

bool Piece::rotateRightOverY(vector<vector<vector<Block>>>& blocksTaulell) {
	if (m_form == I)
	{
		rotateTRigthOverY();
	}
	if (m_form == CUBE) {
		rotateLRightOverY();
	}
	if (m_form == L)
	{
		rotateCubeRightOverY();
	}
	if (m_form == T) {
		rotateIRightOverY();
	}
	if (m_form == Z)
	{
		rotateZRightOverY();
	}

	if (colisionsLimitsTaulellCorrecte()) {
		if (colisionsBlocsTaulellCorrecte(blocksTaulell)) {
			return true;
		}
	}

	rotateLeftOverY(blocksTaulell);
	return false;


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

bool Piece::rotateLeftOverY(vector<vector<vector<Block>>>& blocksTaulell) {
	if (m_form == I)
	{
		rotateTLeftOverY();
	}
	if (m_form == CUBE)
	{
		rotateLLeftOverY();
	}
	if (m_form == L)
	{
		rotateCubeLeftOverY();
	}
	if (m_form == T)
	{
		rotateILeftOverY();
	}
	if (m_form == Z)
	{
		rotateZLeftOverY();
	}

	if (colisionsLimitsTaulellCorrecte()) {
		if (colisionsBlocsTaulellCorrecte(blocksTaulell)) {
			return true;
		}
	}
	rotateLeftOverY(blocksTaulell);
	return false;
}

void Piece::rotateTLeftOverY() {
	if (m_rotacioY == Y0) {
		m_rotacioY = Y3;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[2].setX(m_blocks[2].getPosX() + 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y1) {
		m_rotacioY = Y0;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[2].setX(m_blocks[2].getPosX() - 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y2) {
		m_rotacioY = Y1;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[2].setX(m_blocks[2].getPosX() - 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y3) {
		m_rotacioY = Y2;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[2].setX(m_blocks[2].getPosX() + 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() - 1);
	}
}

void Piece::rotateTRigthOverY() {

	if (m_rotacioY == Y0) {
		m_rotacioY = Y1;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[2].setX(m_blocks[2].getPosX() + 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y1) {
		m_rotacioY = Y2;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[2].setX(m_blocks[2].getPosX() + 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y2) {
		m_rotacioY = Y3;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[2].setX(m_blocks[2].getPosX() - 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y3) {
		m_rotacioY = Y0;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[2].setX(m_blocks[2].getPosX() - 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() - 1);
	}


}

void Piece::rotateLRightOverY() {
	if (m_rotacioY == Y0) {
		m_rotacioY = Y1;
		m_blocks[3].setX(m_blocks[3].getPosX() - 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y1) {
		m_rotacioY = Y2;
		m_blocks[3].setX(m_blocks[3].getPosX() - 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y2) {
		m_rotacioY = Y3;
		m_blocks[3].setX(m_blocks[3].getPosX() + 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y3) {
		m_rotacioY = Y0;
		m_blocks[3].setX(m_blocks[3].getPosX() + 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() + 1);
	}
}

void Piece::rotateLLeftOverY() {
	if (m_rotacioY == Y0) {
		m_rotacioY = Y3;
		m_blocks[3].setX(m_blocks[3].getPosX() - 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y1) {
		m_rotacioY = Y0;
		m_blocks[3].setX(m_blocks[3].getPosX() + 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y2) {
		m_rotacioY = Y1;
		m_blocks[3].setX(m_blocks[3].getPosX() + 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y3) {
		m_rotacioY = Y2;
		m_blocks[3].setX(m_blocks[3].getPosX() - 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() + 1);
	}
}

void Piece::rotateCubeRightOverY() {
	if (m_rotacioY == Y0) {
		m_rotacioY = Y1;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[2].setX(m_blocks[2].getPosX() + 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y1) {
		m_rotacioY = Y2;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[2].setX(m_blocks[2].getPosX() + 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y2) {
		m_rotacioY = Y3;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[2].setX(m_blocks[2].getPosX() - 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y3) {
		m_rotacioY = Y0;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[2].setX(m_blocks[2].getPosX() - 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() - 1);
	}
}

void Piece::rotateCubeLeftOverY() {
	if (m_rotacioY == Y0) {
		m_rotacioY = Y3;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[2].setX(m_blocks[2].getPosX() + 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y1) {
		m_rotacioY = Y0;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[2].setX(m_blocks[2].getPosX() - 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y2) {
		m_rotacioY = Y1;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[2].setX(m_blocks[2].getPosX() - 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y3) {
		m_rotacioY = Y2;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[2].setX(m_blocks[2].getPosX() + 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() - 1);
	}
}

void Piece::rotateILeftOverY() {
	if (m_rotacioY == Y0) {
		m_rotacioY = Y3;
		return;
	}

	if (m_rotacioY == Y1) {
		m_rotacioY = Y0;
		return;
	}

	if (m_rotacioY == Y2) {
		m_rotacioY = Y1;

		return;
	}

	if (m_rotacioY == Y3) {
		m_rotacioY = Y2;

	}
}

void Piece::rotateIRightOverY() {
	if (m_rotacioY == Y0) {
		m_rotacioY = Y1;
		return;
	}

	if (m_rotacioY == Y1) {
		m_rotacioY = Y2;
		return;
	}

	if (m_rotacioY == Y2) {
		m_rotacioY = Y3;

		return;
	}

	if (m_rotacioY == Y3) {
		m_rotacioY = Y0;

	}
}

void Piece::rotateZRightOverY() {
	if (m_rotacioY == Y0) {
		m_rotacioY = Y1;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[3].setX(m_blocks[3].getPosX() + 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y1) {
		m_rotacioY = Y2;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[3].setX(m_blocks[3].getPosX() + 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y2) {
		m_rotacioY = Y3;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[3].setX(m_blocks[3].getPosX() - 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y3) {
		m_rotacioY = Y0;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[3].setX(m_blocks[3].getPosX() - 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() - 1);
	}

}

void Piece::rotateZLeftOverY() {
	if (m_rotacioY == Y0) {
		m_rotacioY = Y3;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[3].setX(m_blocks[3].getPosX() + 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y1) {
		m_rotacioY = Y0;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[3].setX(m_blocks[3].getPosX() - 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y2) {
		m_rotacioY = Y1;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[3].setX(m_blocks[3].getPosX() - 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y3) {
		m_rotacioY = Y2;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[3].setX(m_blocks[3].getPosX() + 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() - 1);
	}
}

void Piece::ViewRotateRightOverY()
{
	m_Matriu = glm::rotate(m_Matriu, radians(90.f), vec3(0.0f, -1.0f, 0.0f));
}

void Piece::ViewRotateLeftOverY()
{
	m_Matriu = glm::rotate(m_Matriu, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
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

	// creem 4 blocs per cada llista de blocs
	switch (form)
	{
	case I:
		TForm(2, 9, 2);
		break;
	case CUBE:
		LForm(2, 9, 2);
		break;
	case L:
		CUBEForm(2, 9, 2);
		break;
	case T:
		IForm(2, 9, 2);
		break;
	case Z:
		ZForm(2, 9, 2);
	default:
		break;
	}
}




/*
bool Piece::moveRight(vector<vector<vector<Block>>>& blocksTaulell) {
	// per cada bloc de la peça, moure a la dreta (incrementar X)
	int moveRight = 1;

	if (colisionsLimitsTaulellCorrecte()) {
		if (check_move_colision(moveRight, blocksTaulell)) {
			for (int i = 0; i < m_blocks.size(); i++)
			{
				m_blocks[i].setX(m_blocks[i].getPosX() + 1);
			}
			return true;
		}
	}
	return false;
}
bool Piece::moveLeft(vector<vector<vector<Block>>>& blocksTaulell) {
	// per cada bloc de la peça, moure a la esquerra (decrementar X)
	int moveLeft = 2;

	if (colisionsLimitsTaulellCorrecte()) {
		if (check_move_colision(moveLeft, blocksTaulell)) {
			for (int i = 0; i < m_blocks.size(); i++)
			{
				m_blocks[i].setX(m_blocks[i].getPosX() - 1);
			}
			return true;
		}
	}
	return false;
}
bool Piece::moveUp(vector<vector<vector<Block>>>& blocksTaulell) {
	// per cada bloc de la peça, moure amunt (incrementar Z)
	int moveUp = 3;

	if (colisionsLimitsTaulellCorrecte()) {
		if (check_move_colision(moveUp, blocksTaulell)) {
			for (int i = 0; i < m_blocks.size(); i++)
			{
				m_blocks[i].setZ(m_blocks[i].getPosZ() + 1);
			}
			return true;
		}
	}
	return false;
}
bool Piece::moveDown(vector<vector<vector<Block>>>& blocksTaulell) {
	// per cada bloc de la peça, moure avall (decrementar Z)
	int moveDown = 4;

	if (colisionsLimitsTaulellCorrecte()) {
		if (check_move_colision(moveDown, blocksTaulell)) {
			for (int i = 0; i < m_blocks.size(); i++)
			{
				m_blocks[i].setZ(m_blocks[i].getPosZ() - 1);
			}
			return true;
		}
	}
	return false;
}
*/

bool Piece::cauPeca(vector<vector<vector<Block>>>& blocksTaulell) {




	if (colisionsLimitsTaulellCorrecte()) {

		

		for (int i = 0; i < m_blocks.size(); i++)
		{
			// comprovació amb blocs ja colocats
			if (blocksTaulell[m_blocks[i].getPosX()][m_blocks[i].getPosY()][m_blocks[i].getPosZ()].m_lliure == false)
			{
				return false;
			}

			// comprovació amb fi del taulell
			if (m_blocks[i].getPosY() <=MINY)
			{
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

bool Piece::check_move_colision(int moviment, vector<vector<vector<Block>>>& blocksTaulell)
{
	//Donem al auxiliar els valors exactes de la peça que volem comprovar

	switch (moviment)
	{
	case 1: {
		//moveRight
		for (int i = 0; i < m_blocks.size(); i++)
		{
			m_auxiliar[i].setX(m_blocks[i].getPosX() + 1);
			m_auxiliar[i].setY(m_blocks[i].getPosY());
			m_auxiliar[i].setZ(m_blocks[i].getPosZ());
		}
		for (Block b : m_auxiliar) {
			if (blocksTaulell[b.getPosX()][b.getPosY()][b.getPosZ()].m_lliure == false) return false;
		}
		return true;
	}
	case 2: {
		//moveLeft
		for (int i = 0; i < m_blocks.size(); i++)
		{
			m_auxiliar[i].setX(m_blocks[i].getPosX() - 1);
			m_auxiliar[i].setY(m_blocks[i].getPosY());
			m_auxiliar[i].setZ(m_blocks[i].getPosZ());
		}
		for (Block b : m_auxiliar) {
			if (blocksTaulell[b.getPosX()][b.getPosY()][b.getPosZ()].m_lliure == false) return false;
		}
		return true;
	}
	case 3: {
		//MoveUp
		for (int i = 0; i < m_blocks.size(); i++)
		{
			m_auxiliar[i].setX(m_blocks[i].getPosX());
			m_auxiliar[i].setY(m_blocks[i].getPosY());
			m_auxiliar[i].setZ(m_blocks[i].getPosZ() + 1);
		}
		for (Block b : m_auxiliar) {
			if (blocksTaulell[b.getPosX()][b.getPosY()][b.getPosZ()].m_lliure == false) return false;
		}
		return true;
	}
	case 4: {
		//MoveDown
		for (int i = 0; i < m_blocks.size(); i++)
		{
			m_auxiliar[i].setX(m_blocks[i].getPosX());
			m_auxiliar[i].setY(m_blocks[i].getPosY());
			m_auxiliar[i].setZ(m_blocks[i].getPosZ() - 1);
		}
		for (Block b : m_auxiliar) {
			if (blocksTaulell[b.getPosX()][b.getPosY()][b.getPosZ()].m_lliure == false) return false;
		}
		return true;
	}
	case 5: {
		//cauPeca
		for (int i = 0; i < m_blocks.size(); i++)
		{
			m_auxiliar[i].setX(m_blocks[i].getPosX());
			m_auxiliar[i].setY(m_blocks[i].getPosY() - 1);
			m_auxiliar[i].setZ(m_blocks[i].getPosZ());
		}
		for (Block b : m_auxiliar) {
			if (blocksTaulell[b.getPosX()][b.getPosY()][b.getPosZ()].m_lliure == false) return false;
		}
		return true;
	}
		  return false;

	}
}

Piece::~Piece()
{

}

