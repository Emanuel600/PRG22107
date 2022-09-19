/*
 * classes.cpp
 *
 *  Created on: 19 de set de 2022
 *      Author: Aluno
 */

#include <vector>
#include <string>

#include "classes.h"

using namespace std;

void Notebook::note(string title){
	Note* note = new Note();

	note->set_title(title);

	_notes.push_back(note);
}

void Notebook::show(){
	for (auto iter=_notes.begin(); iter!=_notes.end(); iter++){
		cout << ((*iter)->get_title()) << endl;
	}
}
