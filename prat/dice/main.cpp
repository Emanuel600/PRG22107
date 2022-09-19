/*
 * main.cpp
 *
 *  Created on: 29 de ago de 2022
 *      Author: Aluno
 */

#include <time.h>

#include "dado_padrao.h"
#include "game.h"

int main(){
	DiceGame game;

	for (int i = 0; i < 10; i++){
		game.play();
	}

}
