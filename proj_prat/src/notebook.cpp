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
            QJsonArray book_jason = jason_obj[str].toArray();
            unsigned uid = 0;
            str = "notes";
            for (auto book_auto : book_jason){
                if(uid == _uid){
                    QJsonObject book_obj = book_auto.toObject();
                    if(book_obj.contains(str)){
                        QJsonObject note_obj = book_obj[str].toObject();
                        QJsonArray  titles   = note_obj["title"].toArray();
                        QJsonArray  cont     = note_obj["content"].toArray();

                        int size = titles.size();

                        for(int i = 0 ; i < size ; i++)
                            this->note(titles.at(i).toString(), cont.at(i).toString());
                    }
                    return;
                } else uid++;
            }
        } else {
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
