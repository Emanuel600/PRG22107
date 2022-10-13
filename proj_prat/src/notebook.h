/* System Includes */
#include <vector>
#include <QString>
/* Modular Includes */
#include "note.h"

#ifndef NOTEBOOK_H
#define NOTEBOOK_H

class Notebook{
private:
    vector<Note*> _notes;
    QString _title;
public:
    Notebook() {_title = "";}
    Notebook(QString title) { _title=title; }

    Note* open(unsigned i) {return _notes[i]; }
    vector<Note*> notes() { return _notes; }

    void title(QString title) { _title = title; }
    QString title() {return _title;}
    // Cria/adiciona notas
    void note(QString title);
    void note(QString title, QString cont);
    void note(Note* note) { _notes.push_back(note); }

    void show();
};

#endif // NOTEBOOK_H
