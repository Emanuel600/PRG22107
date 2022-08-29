/*
 * main.cpp
 *
 *  Created on: 29 de ago de 2022
 *      Author: Aluno
 */
#include "comp_test.h"

int main(){
	dice new_dye;

	//cout << "Received face " << new_dye.get_face() << endl;

	for (int i = 0; i < 10; i++){
		new_dye.roll();
		cout << "Rolled a " << new_dye.get_face() << endl << endl;
	}

}
