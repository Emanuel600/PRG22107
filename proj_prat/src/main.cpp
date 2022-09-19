/*
 * main.cpp
 *
 *  Created on: 19 de set de 2022
 *      Author: Aluno
 */
/* Includes do Sistema */
#include <vector>
#include <string>

using namespace std;
/* Includes do Módulo */
#include "classes.h"

int main(){
	Notebook book;

	book.note("Title");
	book.note("Title");
	book.note("");
	book.note("Title");
	book.note("Title");

	book.show();
}


