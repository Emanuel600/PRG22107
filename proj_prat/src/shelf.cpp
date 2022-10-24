/* System Includes */
#include <QFile>
#include <QDebug>
#include <QString>
#include <QtGlobal>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextStream>
#include <QJsonDocument>

/* Modular Includes */
#include "shelf.h"

// Salva notebooks em json
void Shelf::save(){
    /* Objetos */
    QJsonObject note;
    QJsonObject main;
    QJsonObject notebook;

    /* Arrays */
    QJsonArray books;
    QJsonArray title;
    QJsonArray cont;

    for(vector<Notebook>::iterator it = _books.begin(); it!=_books.end(); ++it){
        Notebook book= *it;

        vector<Note*> notes = book.notes();

        for(vector<Note*>::iterator itn = notes.begin(); itn!=notes.end(); ++itn){
            Note note= *(*itn);
            title.push_back(note.title());
            cont.push_back(note.content());
        }

        note["title"] = title;
        note["content"] = cont;

        // Limpar arrays
        title = QJsonArray{};
        cont = title;

        notebook["title"] = book.title();
        notebook["notes"] = note;

        books.push_back(notebook);
    }
    main["Notebook"] = books;

    QByteArray output = QJsonDocument(main).toJson();

    QFile fout("C:\\Users\\emanuel\\Downloads\\output.json");
    fout.open(QIODevice::WriteOnly);
    fout.write(output);
    fout.close();
}
// Cria notebooks a partir de um json
void Shelf::create(){
    QByteArray input;

    QFile fin("C:\\Users\\emanuel\\Downloads\\output.json");
    fin.open(QIODevice::ReadOnly);
    input = fin.readAll();
    fin.close();

    QJsonParseError jsonError;
    QJsonDocument jason = QJsonDocument::fromJson(input, &jsonError);
    if(jsonError.error != QJsonParseError::NoError){
        cerr << "Erro ao ler arquivo salvo" << endl;
        return;
    }

    if(jason.isObject()){
        QJsonObject jason_obj = jason.object(); // Contains all saved notebooks
        QString str = "Notebook";
        if(jason_obj.contains(str)){ // Verifica que possui notebook salvo
            QJsonArray book_jason = jason_obj[str].toArray();

            for (auto book_auto : book_jason){
                Notebook book;

                QJsonObject book_obj = book_auto.toObject();
                QJsonObject note_obj = book_obj["notes"].toObject();
                QString     title    = book_obj["title"].toString();

                str = "notes"; book.title(title);

                if(book_obj.contains(str)){
                    QJsonArray titles = note_obj["title"].toArray();
                    QJsonArray cont   = note_obj["content"].toArray();

                    int size = titles.size();

                    for(int j = 0 ; j < size ; j++)
                        book.note(titles.at(j).toString(), cont.at(j).toString());
                }
                _books.push_back(book);
            }
        }
    }
}

void Shelf::showcase(){
    for (auto book : _books)
        book.show();
}

Shelf::~Shelf(){
    // Salva automaticamente quando o programa fecha
    this->save();
    // Deleta notas armazenadas dinamicamente na memoria
    for (auto book : _books)
        book.close();
}
