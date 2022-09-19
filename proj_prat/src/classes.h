/*
 * classes.h
 *
 *  Created on: 19 de set de 2022
 *      Author: Aluno
 */

#ifndef CLASSES_H_
#define CLASSES_H_

#include <vector>
#include <String>

using namespace std;

class Note{
	string _title;
	string _contents; // Pode ser feita em markdown no QT
public:
	Note();
	Note(string title) {_title = title; }

	void title(string title) { _title = title; }
	void contents(string contents) { _contents = contents; }
};

class Notebook{
	vector<Note*> _notes;
	string _title;
public:
	Notebook();
	Notebook(string title) { _title=title; }

	Note* open(int);

	void title(string title) { _title = title; }
};

class Interface{
	vector<Notebook*> books;

	Notebook* OnDisp;

	Notebook* open(int);
};


#endif /* CLASSES_H_ */
