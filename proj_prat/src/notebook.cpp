#include <string>

#include "notebook.h"

void Notebook::note(QString title){
    Note* note = new Note();

    note->title(title);

    _notes.push_back(note);
}

void Notebook::note(QString title, QString cont){
    Note* note = new Note();

    note->title(title);
    note->content(cont);

    _notes.push_back(note);
}

void Notebook::show(){
    cout << "Notebook: " << _title.toStdString() << endl;
    for (auto iter=_notes.begin(); iter!=_notes.end(); iter++){
        cout << "\t- " << ((*iter)->title()).toStdString() << endl;
    }
}

void Notebook::close(){
    for (auto note : _notes)
        delete note;
}
