/*
 * dado_padrao.cpp
 *
 *  Created on: 29 de ago de 2022
 *      Author: Aluno
 */

#include <time.h>

#include "dado_padrao.h"

void dice::set_face(short int value){
	if ((value < 0) | (value>6)){
		cerr << "Error when setting face value" << endl;
	}

	face = value;
}

void dice::roll(){
	set_face( (rand() % 6 ) +1 );
	cout << "Created a dice with {" << get_face() << "}" << endl;
}

short int dice::get_face(){
	return face;
}
