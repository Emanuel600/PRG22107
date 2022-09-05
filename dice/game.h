/*
 * game.h
 *
 *  Created on: 5 de set de 2022
 *      Author: Aluno
 */

#ifndef GAME_H_
#define GAME_H_

#include "dado_padrao.h"

class DiceGame{
private:
	dice D1;
	dice D2;
public:
	DiceGame();

	bool roll();
	bool play();
};



#endif /* GAME_H_ */
