/* System Includes */
#include <vector>
/* Modular Includes */
#include "note.h"

#ifndef NOTEBOOK_H
#define NOTEBOOK_H

class Notebook{
private:
    vector<Note*> _notes;
    string _title;
public:
    Notebook() {};
    Notebook(string title) { _title=title; }

    Note* open(int i) {return _notes[i]; }

    void title(string title) { _title = title; }
    // Cria/adiciona notas
    void note(string title);
    void note(string title, string cont);
    void note(Note* note) { _notes.push_back(note); }

    void show();
};

#endif // NOTEBOOK_H
