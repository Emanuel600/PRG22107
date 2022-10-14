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
        /* Pseudo-code */
        /*
         * for every notebook{
         *    int n = *(notebook.open(j)).title.len() => title is an array containing titles of all notes
         *      for(int i=0; i < n; i++){ => n is size+1
         *        Note nota(title[i], content[i]) => content.len = title.len
         *      }
         *  }
         */
        QString snotebook = "Notebook";
        if(jason_obj.contains(snotebook)){ // Verifica que possui notebook salvo
            QJsonObject book_jason = jason_obj.value(snotebook).toObject(); // Notebook.json => reads empty
            QStringList keys = book_jason.keys();

            QByteArray json = QJsonDocument(book_jason).toJson();
            cout << json.toStdString() << endl;

            for (int i = 0; i < keys.size(); ++i){ // Imprime valores armazenados em 'keys' (nenhum)
                cout << "Entered loop";
                cout << keys.at(i).toLocal8Bit().constData();
            }

            for(auto key:keys){ // Not getting keys properly
                auto note = book_jason.take(key); // note contains two arrays
                cout << key.toStdString() << " : " << note.toString().toStdString();
            }
        }
    }
    return nullptr;
}
