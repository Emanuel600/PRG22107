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
    for (auto iter=_notes.begin(); iter!=_notes.end(); iter++){
        cout << "\t- " << ((*iter)->title()).toStdString() << endl;
    }
}
void Notebook::load(){
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
                    if(book_obj.contains(str)){
                        QJsonArray note_arr = book_obj[str].toArray();
                        for (QJsonValueRef note_ref : note_arr){
                            QJsonObject note_obj = note_ref.toObject();

                            QString title = note_obj["title"].toString();
                            QString cont  = note_obj["content"].toString();

                            this->note(title, cont);
                        }
                    }
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
// Fecha Notebook, Shelf responsável por salvar mudanças
void Notebook::close(){
    for (auto note : _notes)
        delete note;
}
