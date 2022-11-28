#include "notebook.h"


void Notebook::note(QString title, QString cont){
    Plain_Note* note = new Plain_Note();

    note->title(title);
    note->content(cont);

    _notes.push_back(note);
}

void Notebook::note(Plain_Note* note_ptr){
    Plain_Note* note = new Plain_Note();
    // Preenche valores
    note->title(note_ptr->title());
    note->content(note_ptr->content());

    _notes.push_back(note);
}

void Notebook::note(Check_List* note_ptr){
    Check_List* note = new Check_List();
    // Preenche valores
    note->title(note_ptr->title());
    note->content(note_ptr->content());
    note->checked(note_ptr->checked());

    _notes.push_back(note);
}

void Notebook::show(){
    cout << "Notebook: " << _title.toStdString() << "\t(id: " << _uid << ')' << endl;
    unsigned i = 0;
    for (auto iter=_notes.begin(); iter!=_notes.end(); iter++)
        cout << "Nota " << i++ << ": " << ((*iter)->title()).toStdString() << endl;
}

void Notebook::del(long long i){
    vector<Note*>::iterator it = _notes.begin() + i;
    _notes.erase(it);
}

Notebook::Notebook(QJsonObject book_obj){
    QJsonArray note_arr = book_obj["notes"].toArray();
    _title = book_obj["title"].toString();

    if (!note_arr.empty()){
        _notes.resize(unsigned(note_arr.size()));
        unsigned i = 0;
        for (QJsonValueRef note_ref : note_arr){
            QJsonObject note_obj = note_ref.toObject();
            Note* note_ptr;
            char type = note_obj["type"].toString().toStdString()[0];
            switch (type){
            case 'p':
                note_ptr = new Plain_Note(note_obj);
            break;
            case 'c':
                note_ptr = new Check_List(note_obj);
            break;
            default:
                cout << "Fatal error when creating note" << endl;
            return;
            }
            _notes[i++] = note_ptr;
            }
        } else cout << "Empty note array" << endl;
    return;
}

QJsonObject Notebook::get_json(){
    QJsonObject book_json;

    QJsonArray note_arr;
    QJsonObject note_obj;

    for(vector<Note*>::iterator itn = _notes.begin(); itn!=_notes.end(); ++itn){
        Note* nota = *itn;
        note_obj = nota->get_json();

        note_arr.append(note_obj);
    }

    book_json["title"] = _title;
    book_json["notes"] = note_arr;

    return book_json;
}

// Fecha Notebook, Shelf responsável por salvar mudanças
void Notebook::close(){
    if (!_notes.empty())
        for (auto note : _notes)
            delete note;
}
