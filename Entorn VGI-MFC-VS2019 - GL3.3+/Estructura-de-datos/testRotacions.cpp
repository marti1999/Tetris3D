// testRotacions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Piece.h"


int main()
{

    Piece t('Z');
    t.printPunts();
    for (int i = 0; i < 4; i++)
    {   
        cout << "\n";
        //t.rotateRightOverY();
        //t.moveRight();      //X++
        //t.moveUp();         //Z++
        t.cauPeca();          //Y--
        t.printPunts();
    }
}

