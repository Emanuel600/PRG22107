/*
 * comp_test.h
 *
 *  Created on: 29 de ago de 2022
 *      Author: Aluno
 */

#ifndef DADO_PADRAO_H_
#define DADO_PADRAO_H_

#include <iostream>

using namespace std;

class dice{
	short unsigned int face;

public:
	dice();

	void roll();
	void set_face(short unsigned int value);

	short unsigned int get_face();
};

#endif /*DADO_PADRAO_H_ */
