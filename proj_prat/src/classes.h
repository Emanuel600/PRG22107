/*
 * classes.h
 *
 *  Created on: 19 de set de 2022
 *      Author: Aluno
 */

#ifndef CLASSES_H_
#define CLASSES_H_

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Note{
	string _title;
	string _contents; // Pode ser feita em markdown no QT
public:
	Note() {};
	Note(string title) {_title = title; }

	void title(string title) { _title = title; }
	void content(string contents) { _contents = contents; }

	void set_title(string title) {_title = title; }
	string get_title() {return _title; }
};

class Notebook{
	vector<Note*> _notes;
	string _title;
public:
	Notebook() {};
	Notebook(string title) { _title=title; }

	Note* open(int i) {return _notes[i]; }

	void title(string title) { _title = title; }
	// Cria/adiciona notas
	void note(string title);
	void note(Note* note) { _notes.push_back(note); }

	void show();
};

class Interface{
	vector<Notebook*> books;

	unsigned ind; // Índice do Notebook que está sendo visualizado

	Notebook* open(int);
	// Cria Notebooks a partir de um arquivo
	void create(string path);
};


#endif /* CLASSES_H_ */
