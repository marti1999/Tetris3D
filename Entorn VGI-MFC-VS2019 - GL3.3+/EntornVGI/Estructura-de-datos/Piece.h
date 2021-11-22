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
	int m_rotacioY;
	GLuint m_idVao;
	mat4 m_Matriu;

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
	void rotateRightOverY(vector<vector<vector<Block>>>& blocksTaulell);
	void rotateLeftOverY(vector<vector<vector<Block>>>& blocksTaulell);
	

	//void rotateRight();
	//void rotateLeft();
	//void rotateUp();
	//void rotateDown();


	// moviments
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void cauPeca();
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


void Piece::rotateRightOverY(vector<vector<vector<Block>>>& blocksTaulell) {
	if (m_form == T)
	{
		rotateTRigthOverY();
		return;
	}
	if (m_form == L) {
		rotateLRightOverY();
		return;
	}
	if (m_form == CUBE)
	{
		rotateCubeRightOverY();
		return;
	}
	if (m_form == I) {
		rotateIRightOverY();
		return;
	}
	if (m_form == Z)
	{
		rotateZRightOverY();
	}

	if (colisionsLimitsTaulellCorrecte() && colisionsBlocsTaulellCorrecte(blocksTaulell)) {
		ViewRotateRightOverY();
	}
	else {
		rotateLeftOverY(blocksTaulell);
	}


}

void Piece::rotateLeftOverY(vector<vector<vector<Block>>>& blocksTaulell) {
	if (m_form == T)
	{
		rotateTLeftOverY();
		return;
	}
	if (m_form == L)
	{
		rotateLLeftOverY();
		return;
	}
	if (m_form == CUBE)
	{
		rotateCubeLeftOverY();
		return;
	}
	if (m_form == I)
	{
		rotateILeftOverY();
		return;
	}
	if (m_form == Z)
	{
		rotateZLeftOverY();
	}

	if (colisionsLimitsTaulellCorrecte() && colisionsBlocsTaulellCorrecte(blocksTaulell)) {
		ViewRotateLeftOverY();
	}
	else {
		rotateRightOverY(blocksTaulell);
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




void Piece::TForm() {
	//El primer bloc sera sempre el pivot el pivot.
	Block BlockFromPiece;
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
	Block BlockFromPiece;
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
	Block BlockFromPiece;
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
	Block BlockFromPiece;
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
	Block BlockFromPiece;
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
void Piece::moveRight() {
	// TODO: per cada bloc de la peça, moure a la dreta (incrementar X)
	for (int i = 0; i < m_blocks.size(); i++)
	{
		m_blocks[i].setX(m_blocks[i].getPosX() + 1);
	}
}
void Piece::moveLeft() {
	// TODO: per cada bloc de la peça, moure a la esquerra (decrementar X)
	for (int i = 0; i < m_blocks.size(); i++)
	{
		m_blocks[i].setX(m_blocks[i].getPosX() - 1);
	}
}
void Piece::moveUp() {
	// TODO: per cada bloc de la peça, moure amunt (incrementar Z)
	for (int i = 0; i < m_blocks.size(); i++)
	{
		m_blocks[i].setZ(m_blocks[i].getPosZ() + 1);
	}
}
void Piece::moveDown() {
	// TODO: per cada bloc de la peça, moure avall (decrementar Z)
	for (int i = 0; i < m_blocks.size(); i++)
	{
		m_blocks[i].setZ(m_blocks[i].getPosZ() - 1);
	}
}

void Piece::cauPeca() {
	for (int i = 0; i < m_blocks.size(); i++)
	{
		m_blocks[i].setY(m_blocks[i].getPosY() - 1);
	}
}

Piece::~Piece()
{
}

