#include <list>
#include "Block.h"
#include <iostream>
// mapejat que defineix una lletra per cada forma
#define T 33
#define L 34
#define CUBE 35
#define I 36
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
	void ViewRotateRightOverY();
	
	void ViewRotateLeftOverY();

	// colisions
	bool colisionsLimitsTaulellCorrecte();
	bool colisionsBlocsTaulellCorrecte(vector<vector<vector<Block>>>& blocksTaulell);
	bool check_move_colision(bool a, vector<vector<vector<Block>>>& blocksTaulell);

public:
	Piece() {};
	Piece(int form);
	~Piece();

	// funcions per generar les peces de la forma dessitjada
	void TForm();
	void LForm();
	void CUBEForm();
	void IForm();
	void ZForm();
	int getIdVao() { return m_idVao; }
	mat4 getMatrix() { return m_Matriu; }


	// rotacions
	bool rotateRightOverY(vector<vector<vector<Block>>>& blocksTaulell);
	bool rotateLeftOverY(vector<vector<vector<Block>>>& blocksTaulell);
	

	//void rotateRight();
	//void rotateLeft();
	//void rotateUp();
	//void rotateDown();


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
	void printPunts();
};


void Piece::printPunts() {
	for (int i = 0; i < m_blocks.size(); i++)
	{
		cout << "block: " << i << "--> ("<< m_blocks[i].getPosX() << "; " << m_blocks[i].getPosY() << "; " << m_blocks[i].getPosZ() << ") \n";

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


bool Piece::rotateRightOverY(vector<vector<vector<Block>>>& blocksTaulell) {
	if (m_form == T)
	{
		rotateTRigthOverY();
	}
	if (m_form == L) {
		rotateLRightOverY();
	}
	if (m_form == CUBE)
	{
		rotateCubeRightOverY();
	}
	if (m_form == I) {
		rotateIRightOverY();
	}
	if (m_form == Z)
	{
		rotateZRightOverY();
	}

	if (colisionsLimitsTaulellCorrecte() && colisionsBlocsTaulellCorrecte(blocksTaulell)) {
		return true;
	}
	else {
		rotateLeftOverY(blocksTaulell);	
		return false;
	}


}

bool Piece::rotateLeftOverY(vector<vector<vector<Block>>>& blocksTaulell) {
	if (m_form == T)
	{
		rotateTLeftOverY();
	}
	if (m_form == L)
	{
		rotateLLeftOverY();
	}
	if (m_form == CUBE)
	{
		rotateCubeLeftOverY();
	}
	if (m_form == I)
	{
		rotateILeftOverY();
	}
	if (m_form == Z)
	{
		rotateZLeftOverY();
	}

	if (colisionsLimitsTaulellCorrecte() && colisionsBlocsTaulellCorrecte(blocksTaulell)) {
		return true;
	}
	else {
		rotateRightOverY(blocksTaulell);
		return false;
	}
}

void Piece::rotateTLeftOverY() {
	if (m_rotacioY == Y0) {
		m_rotacioY = Y3;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[2].setX(m_blocks[2].getPosX() + 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y1) {
		m_rotacioY = Y0;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[2].setX(m_blocks[2].getPosX() - 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y2) {
		m_rotacioY = Y1;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[2].setX(m_blocks[2].getPosX() - 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y3) {
		m_rotacioY = Y2;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[2].setX(m_blocks[2].getPosX() + 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() + 1);
	}
}

void Piece::rotateTRigthOverY() {

	if (m_rotacioY == Y0) {
		m_rotacioY = Y1;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[2].setX(m_blocks[2].getPosX() + 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y1) {
		m_rotacioY = Y2;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[2].setX(m_blocks[2].getPosX() + 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y2) {
		m_rotacioY = Y3;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[2].setX(m_blocks[2].getPosX() - 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y3) {
		m_rotacioY = Y0;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[2].setX(m_blocks[2].getPosX() - 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() + 1);
	}


}

void Piece::rotateLRightOverY() {
	if (m_rotacioY == Y0) {
		m_rotacioY = Y1;
		m_blocks[3].setX(m_blocks[3].getPosX() - 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y1) {
		m_rotacioY = Y2;
		m_blocks[3].setX(m_blocks[3].getPosX() - 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y2) {
		m_rotacioY = Y3;
		m_blocks[3].setX(m_blocks[3].getPosX() + 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y3) {
		m_rotacioY = Y0;
		m_blocks[3].setX(m_blocks[3].getPosX() + 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() - 1);
	}
}

void Piece::rotateLLeftOverY() {
	if (m_rotacioY == Y0) {
		m_rotacioY = Y3;
		m_blocks[3].setX(m_blocks[3].getPosX() - 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y1) {
		m_rotacioY = Y0;
		m_blocks[3].setX(m_blocks[3].getPosX() + 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y2) {
		m_rotacioY = Y1;
		m_blocks[3].setX(m_blocks[3].getPosX() + 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y3) {
		m_rotacioY = Y2;
		m_blocks[3].setX(m_blocks[3].getPosX() - 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() - 1);
	}
}

void Piece::rotateCubeRightOverY() {
	if (m_rotacioY == Y0) {
		m_rotacioY = Y1;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[2].setX(m_blocks[2].getPosX() + 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y1) {
		m_rotacioY = Y2;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[2].setX(m_blocks[2].getPosX() + 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y2) {
		m_rotacioY = Y3;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[2].setX(m_blocks[2].getPosX() - 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y3) {
		m_rotacioY = Y0;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[2].setX(m_blocks[2].getPosX() - 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() + 1);
	}
}

void Piece::rotateCubeLeftOverY() {
	if (m_rotacioY == Y0) {
		m_rotacioY = Y3;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[2].setX(m_blocks[2].getPosX() + 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y1) {
		m_rotacioY = Y0;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[2].setX(m_blocks[2].getPosX() - 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y2) {
		m_rotacioY = Y1;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[2].setX(m_blocks[2].getPosX() - 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y3) {
		m_rotacioY = Y2;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[2].setX(m_blocks[2].getPosX() + 1);
		m_blocks[2].setZ(m_blocks[2].getPosZ() + 1);
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
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[3].setX(m_blocks[3].getPosX() + 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y1) {
		m_rotacioY = Y2;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[3].setX(m_blocks[3].getPosX() + 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y2) {
		m_rotacioY = Y3;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[3].setX(m_blocks[3].getPosX() - 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y3) {
		m_rotacioY = Y0;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[3].setX(m_blocks[3].getPosX() - 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() + 1);
	}

}

void Piece::rotateZLeftOverY() {
	if (m_rotacioY == Y0) {
		m_rotacioY = Y3;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[3].setX(m_blocks[3].getPosX() + 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y1) {
		m_rotacioY = Y0;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() + 1);

		m_blocks[3].setX(m_blocks[3].getPosX() - 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() - 1);
		return;
	}

	if (m_rotacioY == Y2) {
		m_rotacioY = Y1;
		m_blocks[1].setX(m_blocks[1].getPosX() + 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[3].setX(m_blocks[3].getPosX() - 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() + 1);
		return;
	}

	if (m_rotacioY == Y3) {
		m_rotacioY = Y2;
		m_blocks[1].setX(m_blocks[1].getPosX() - 1);
		m_blocks[1].setZ(m_blocks[1].getPosZ() - 1);

		m_blocks[3].setX(m_blocks[3].getPosX() + 1);
		m_blocks[3].setZ(m_blocks[3].getPosZ() + 1);
	}
}

inline void Piece::ViewRotateRightOverY()
{
	m_Matriu = glm::rotate(m_Matriu, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
}

inline void Piece::ViewRotateLeftOverY()
{
	m_Matriu = glm::rotate(m_Matriu, radians(90.f), vec3(0.0f, 1.0f, 0.0f));
}

void Piece::ViewMoveUp()
{
	m_Matriu = glm::translate(m_Matriu, glm::vec3(0.0f, 0.0f, -1));
}

void Piece::ViewMoveDown()
{
	m_Matriu = glm::translate(m_Matriu, glm::vec3(0.0f, 0.0f, 1));
}
void Piece::ViewMoveRight()
{
	m_Matriu = glm::translate(m_Matriu, glm::vec3(1, 0, 0.0f));
}

void Piece::ViewMoveLeft()
{
	m_Matriu = glm::translate(m_Matriu, glm::vec3(-1, 0.0f, 0.0f));
}



void Piece::TForm() {
	//El primer bloc sera sempre el pivot el pivot.
	Block BlockFromPiece(0, 0, 0);
	// BlockFromPiece.setPosition(0, 0, 0);         //Per defecte ja ve a 0,0,0
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(1, 0, 0);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(-1, 0, 0);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(0, -1, 0);
	m_blocks.push_back(BlockFromPiece);

	/*

	0   0   0
	3   1   2
	0   4   0

	*/

}
// TODO: peça en forma de L
void Piece::LForm() {
	//El primer bloc sera sempre el pivot.
	Block BlockFromPiece(0,0,0);
	BlockFromPiece.setPosition(0, 0, 0);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(0, -1, 0);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(0, -2, 0);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(1, -2, 0);
	m_blocks.push_back(BlockFromPiece);

	/*

	0   1   0
	0   2   0
	0   3   4

	*/





}
// TODO: peça en forma de CUB
void Piece::CUBEForm() {
	//El primer bloc sera sempre el pivot.
	Block BlockFromPiece(0, 0, 0);
	//BlockFromPiece.setPosition(0, 0, 0);  //Per defecte ja ve a 0,0,0
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(-1, 0, 0);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(-1, -1, 0);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(0, -1, 0);
	m_blocks.push_back(BlockFromPiece);

	/*

	2   1
	3   4

	*/





}
// TODO: peça en forma de I
void Piece::IForm() {
	//El primer bloc sera sempre el pivot.
	Block BlockFromPiece(0, 0, 0);
	BlockFromPiece.setPosition(0, 0, 0);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(0, -1, 0);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(0, -2, 0);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(0, -3, 0);
	m_blocks.push_back(BlockFromPiece);



	/*

	0   0   1   0
	0   0   2   0
	0   0   3   0
	0   0   4   0

	*/
}

void Piece::ZForm() {
	Block BlockFromPiece(0, 0, 0);
	//BlockFromPiece.setPosition(0, 0, 0);  //Per defecte ja ve a 0,0,0
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(1, -1, 0);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(0, -1, 0);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(-1, 0, 0);
	m_blocks.push_back(BlockFromPiece);

	/*

	0   0   0
	3   1   0
	0   3   2

	*/


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
	case Z:
		ZForm();
	default:
		break;
	}
}

/*
void Piece::rotateRight() {
	// TODO: establir la columna centra de la peça com a eix de traslació
	// TODO: traslladar els blocs cap a la dreta en funció de l'eix Y

	list<Block> blocs_a_rotar; //identificar els blocs a rotar
	list<Block>::iterator it = blocs_a_rotar.begin();

	for (it; it != blocs_a_rotar.end(); it++) {

		if (it->getPosX() == 0) {
			if (it->getPosZ() == 1)
				it->setPosition(-1, it->getPosY(), 0);
			else
				it->setPosition(1, it->getPosY(), 0);
		}
		else {
			if (it->getPosX() == 1)
				it->setPosition(0, it->getPosY(), 1);
			else
				it->setPosition(0, it->getPosY(), -1);
		}
	}

}
void Piece::rotateLeft() {
	// TODO: establir la columna centra de la peça com a eix de traslació
	// TODO: traslladar els blocs cap a l'esquerra en funció de l'eix Y

	list<Block> blocs_a_rotar; //identificar els blocs a rotar
	list<Block>::iterator it = blocs_a_rotar.begin();

	for (it; it != blocs_a_rotar.end(); it++) {

		if (it->getPosX() == 0) {
			if (it->getPosZ() == 1)
				it->setPosition(1, it->getPosY(), 0);
			else
				it->setPosition(-1, it->getPosY(), 0);
		}
		else {
			if (it->getPosX() == 1)
				it->setPosition(0, it->getPosY(), -1);
			else
				it->setPosition(0, it->getPosY(), 1);
		}
	}
}
void Piece::rotateUp() {
	// TODO: establir la columna centra de la peça com a eix de traslació
	// TODO: traslladar els blocs cap a la dreta en funció de l'eix Y

	list<Block> blocs_a_rotar; //identificar els blocs a rotar
	list<Block>::iterator it = blocs_a_rotar.begin();

	for (it; it != blocs_a_rotar.end(); it++) {

		if (it->getPosY() == 0) {
			if (it->getPosZ() == 1)
				it->setPosition(it->getPosX(), -1, 0);
			else
				it->setPosition(it->getPosX(), 1, 0);
		}
		else {
			if (it->getPosX() == 1)
				it->setPosition(it->getPosX(), 0, 1);
			else
				it->setPosition(it->getPosX(), 0, -1);
		}
	}
}
void Piece::rotateDown() {
	// TODO: establir la columna centra de la peça com a eix de traslació
	// TODO: traslladar els blocs cap amunt en funció de l'eix X

	list<Block> blocs_a_rotar; //identificar els blocs a rotar
	list<Block>::iterator it = blocs_a_rotar.begin();

	for (it; it != blocs_a_rotar.end(); it++) {

		if (it->getPosY() == 0) {
			if (it->getPosZ() == 1)
				it->setPosition(it->getPosX(), 1, 0);
			else
				it->setPosition(it->getPosX(), -1, 0);
		}
		else {
			if (it->getPosX() == 1)
				it->setPosition(it->getPosX(), 0, -1);
			else
				it->setPosition(it->getPosX(), 0, 1);
		}
	}
}
*/
bool Piece::moveRight(vector<vector<vector<Block>>>& blocksTaulell) {
	// per cada bloc de la peça, moure a la dreta (incrementar X)
	bool moveRight = 1;

	if (check_move_colision(moveRight, blocksTaulell)) {
		for (int i = 0; i < m_blocks.size(); i++)
		{
			m_blocks[i].setX(m_blocks[i].getPosX() + 1);
		}
		return true;
	}
	else
		return false;
}
bool Piece::moveLeft(vector<vector<vector<Block>>>& blocksTaulell) {
	// per cada bloc de la peça, moure a la esquerra (decrementar X)
	bool moveLeft = 2;

	if (check_move_colision(moveLeft, blocksTaulell)) {
		for (int i = 0; i < m_blocks.size(); i++)
		{
			m_blocks[i].setX(m_blocks[i].getPosX() - 1);
		}
		return true;
	}
	else
		return false;
}
bool Piece::moveUp(vector<vector<vector<Block>>>& blocksTaulell) {
	// per cada bloc de la peça, moure amunt (incrementar Z)
	bool moveUp = 3;

	if (check_move_colision(moveUp, blocksTaulell)) {
		for (int i = 0; i < m_blocks.size(); i++)
		{
			m_blocks[i].setZ(m_blocks[i].getPosZ() + 1);
		}
		return true;
	}
	else
		return false;
}
bool Piece::moveDown(vector<vector<vector<Block>>>& blocksTaulell) {
	// per cada bloc de la peça, moure avall (decrementar Z)
	bool moveDown = 4;
	
	if (check_move_colision(moveDown, blocksTaulell)) {
		for (int i = 0; i < m_blocks.size(); i++)
		{
			m_blocks[i].setZ(m_blocks[i].getPosZ() - 1);
		}
		return true;
	}
	else
		return false;
}

bool Piece::cauPeca(vector<vector<vector<Block>>>& blocksTaulell) {
	// per cada bloc de la peça, cau (decrementar Y)
	bool cauPeca = 5;

	if (check_move_colision(cauPeca, blocksTaulell)) {
		for (int i = 0; i < m_blocks.size(); i++)
		{
			m_blocks[i].setY(m_blocks[i].getPosY() - 1);
		}
		return true;
	}
	else
		return false;
}

bool Piece::check_move_colision(bool moviment, vector<vector<vector<Block>>>& blocksTaulell)
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

