/*
 * comp_test.cpp
 *
 *  Created on: 29 de ago de 2022
 *      Author: Aluno
 */

#include <time.h>

#include "dado_padrao.h"

void dice::set_face(short unsigned int value){
	face = value;
}

void dice::roll(){
	set_face( (rand() % 6 ) +1 );
}

short unsigned int dice::get_face(){
	return face;
}

dice::dice(){
	srand (time(NULL));

	cout << "Created a dice with {" << get_face() << "}" << endl;
}
