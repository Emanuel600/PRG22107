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
    cout << "Notebook: " << _title.toStdString() << "\t(id: " << _uid << ')' << endl;
    unsigned i = 0;
    for (auto iter=_notes.begin(); iter!=_notes.end(); iter++)
        cout << i++ << "\t- " << ((*iter)->title()).toStdString() << endl;
}

void Notebook::del(unsigned int i){
    vector<Note*>::iterator it = _notes.begin() + i;
    _notes.erase(it);
}

void Notebook::load(){
    cout << "Loading notes for " << _title.toStdString() << " Notebook" << endl;
    if (_notes.size() != 0) // Já está carregado
        return;
    QByteArray input;

    QFile fin(QDir::currentPath() + "\\output.json");
    if(fin.open(QIODevice::ReadOnly)){
        input = fin.readAll();
        fin.close();
    } else {
        cerr << "Erro ao abrir arquivo\n" << endl;
        return;
    }

    QJsonParseError jsonError;
    QJsonDocument jason = QJsonDocument::fromJson(input, &jsonError);
    if(jsonError.error != QJsonParseError::NoError){
        cerr << "\nErro ao traduzir json" << endl;
        return;
    }

    if(jason.isObject()){
        QJsonObject jason_obj = jason.object(); // Contains all saved notebooks
        QString str = "Notebook";
        if(jason_obj.contains(str)){ // Verifica que possui notebook salvo
            QJsonArray book_arr = jason_obj[str].toArray();
            unsigned uid = 0;
            str = "notes";
            for (auto book_auto : book_arr){
                if(uid == _uid){
                    QJsonObject book_obj = book_auto.toObject();

                    QJsonArray note_arr = book_obj[str].toArray();
                    vector<Note*> temp_store(note_arr.size());
                    short i = 0;
                    if(book_obj.contains(str)){
                        for (QJsonValueRef note_ref : note_arr){
                            QJsonObject note_obj = note_ref.toObject();
                            Note* note_ptr = new Note(note_obj);

                            temp_store[i++] = note_ptr;
                        }
                    }
                    for (auto iter = temp_store.begin() ; iter != temp_store.end() ; iter++)
                        this->note(*iter);
                    return;
                } else uid++;
            }
        } else {
            cout << "Erro ao tentar abrir o notebook" << endl;
            cerr << "Notebook não foi encontrado" << endl;
            return;
        }
    }
}

QJsonObject Notebook::get_json(){
    QJsonObject book_json;

    QJsonArray note_arr;
    QJsonObject note_obj;

    for(vector<Note*>::iterator itn = _notes.begin(); itn!=_notes.end(); ++itn){
        Note nota = **itn;
        note_obj = nota.get_json();

        note_arr.append(note_obj);
    }

    book_json["title"] = _title;
    book_json["notes"] = note_arr;

    return book_json;
}

// Fecha Notebook, Shelf responsável por salvar mudanças
void Notebook::close(){
    for (auto note : _notes)
        delete note;
}
