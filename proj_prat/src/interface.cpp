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
#include "interface.h"
// Salva notebooks em json
void Interface::save(){
    /* Objetos */
    QJsonObject note;
    QJsonObject main;
    QJsonObject notebook;

    /* Arrays */
    QJsonArray books;
    QJsonArray title;
    QJsonArray cont;

    for(vector<Notebook*>::iterator it = _books.begin(); it!=_books.end(); ++it){
        Notebook book= *(*it);

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

    QFile fout("C:\\Users\\Aluno\\Downloads\\output.json");
    fout.open(QIODevice::WriteOnly);
    fout.write(output);
    fout.close();
}
// Cria notebooks a partir de um json
Interface Interface::create(){
    QByteArray input;

    QFile fin("C:\\Users\\Aluno\\Downloads\\output.json");
    fin.open(QIODevice::ReadOnly);
    input = fin.readAll();
    fin.close();

    QJsonParseError jsonError;
    QJsonDocument jason = QJsonDocument::fromJson(input, &jsonError);
    if(jsonError.error != QJsonParseError::NoError){
        cerr << "Erro ao ler arquivo salvo" << endl;
        return nullptr;
    }

    if(jason.isObject()){
        QJsonObject jason_obj = jason.object();
    }
    return nullptr;
}
