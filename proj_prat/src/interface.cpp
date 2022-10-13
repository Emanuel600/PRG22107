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

    //cout << output.toStdString();

    QFile fout("C:\\Users\\Aluno\\Downloads\\output.json");
    fout.open(QIODevice::WriteOnly);
    fout.write(output);
    fout.close();
}
