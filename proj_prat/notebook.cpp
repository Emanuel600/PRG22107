#include "notebook.h"

void Notebook::note(string title){
    Note* note = new Note();

    note->title(title);

    _notes.push_back(note);
}

void Notebook::note(string title, string cont){
    Note* note = new Note();

    note->title(title);
    note->content(cont);

    _notes.push_back(note);
}

void Notebook::show(){
    for (auto iter=_notes.begin(); iter!=_notes.end(); iter++){
        cout << ((*iter)->title()) << endl;
    }
}


