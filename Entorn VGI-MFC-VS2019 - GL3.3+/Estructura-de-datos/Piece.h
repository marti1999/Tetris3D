#include <list>
#include "Block.h"
// mapejat que defineix una lletra per cada forma
#define T 'T'
#define L 'L'
#define CUBE 'C'
#define I 'I'
#define Z 'Z'
#define Y3 3 //rotat sobre Y 270 graus
#define Y2 2 //rotat sobre Y 180 graus
#define Y1 1 //rotat sobre Y 90 graus
#define Y0 0 //rotat sobre Y 0 graus


class Piece
{
private:
	/* data */
	char m_form;
	vector<Block> m_blocks;
	int m_rotacioY;

	// rotacions
	void rotateTRigthOverY();
	void rotateTLeftOverY();

public:
	Piece(char form);
	~Piece();

	// funcions per generar les peces de la forma dessitjada
	void TForm();
	void LForm();
	void CUBEForm();
	void IForm();
	void ZForm();




	// rotacions
	void rotateRightOverY();
	void rotateLeftOverY();
	

	//void rotateRight();
	//void rotateLeft();
	//void rotateUp();
	//void rotateDown();


	// moviments
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void printPunts();
};


void Piece::printPunts() {
	for (int i = 0; i < m_blocks.size(); i++)
	{
		cout << "block: " << i << "--> "<< m_blocks[i].getPosX() << m_blocks[i].getPosY() << m_blocks[i].getPosZ() << "\n";

	}
}

void Piece::rotateRightOverY() {
	if (m_form == T)
	{
		rotateTRigthOverY();
		return;
	}
}

void Piece::rotateLeftOverY() {
	if (m_form == T)
	{
		rotateTLeftOverY();
		return;
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

	BlockFromPiece.setPosition(-1, 0, 0);
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

	BlockFromPiece.setPosition(-1, 0, 0);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(0, -1, 0);
	m_blocks.push_back(BlockFromPiece);

	BlockFromPiece.setPosition(1, -1, 0);
	m_blocks.push_back(BlockFromPiece);

	/*

	0   0   0
	2   1   0
	0   3   4

	*/


}

Piece::Piece(char form)
{
	m_form = form;
	m_rotacioY = Y0;
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
}
void Piece::moveLeft() {
	// TODO: per cada bloc de la peça, moure a la esquerra (decrementar X)
}
void Piece::moveUp() {
	// TODO: per cada bloc de la peça, moure amunt (incrementar Z)
}
void Piece::moveDown() {
	// TODO: per cada bloc de la peça, moure avall (decrementar Z)
}

Piece::~Piece()
{
}

