/*
 * game.cpp
 *
 *  Created on: 5 de set de 2022
 *      Author: Aluno
 */

#include <ctime>

#include "game.h"

bool DiceGame::play(){
	D1= dice();
	D2= dice();

	D1.roll();
	D2.roll();

	if (D1.get_face()+D2.get_face()==7){
		cout << "Congratulations! You've won" << endl;
		return 1;
	}

	cout << "Unfortunately, you've lost" << endl;
	return 0;
}

DiceGame::DiceGame(){
	srand (time(NULL));
}
