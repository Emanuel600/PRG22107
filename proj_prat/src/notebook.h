/* System Includes */
#include <QDir>
#include <QFile>
#include <QList>
#include <vector>
#include <QDebug>
#include <string>
#include <QString>
#include <QtGlobal>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextStream>
#include <QJsonDocument>
/* Modular Includes */
#include "note.h"

#ifndef NOTEBOOK_H
#define NOTEBOOK_H

class Notebook{
private:
    vector<Note*> _notes;
    QString _title;

    unsigned long long _uid;
public:
    Notebook() {_title = "";}
    Notebook(QString title) { _title=title; }
    Notebook(QJsonObject book_obj);

    ~Notebook() { cout << "Deleting " << _title.toStdString() << " Notebook" << endl; this->close(); }

    Note* open(unsigned long long i) {return _notes[i];}
    vector<Note*> notes() {return _notes;}

    void title(QString title) { _title = title; }
    QString title() {return _title;}

    QList<QString> list_notes();

    QJsonObject get_json();
    // Cria/Remove notas
    void note(QString title, QString cont);
    void note(Plain_Note* note);
    void note(Check_List* note);
    void note(vector<Note*> note) { _notes = note; }
    void del (long long i);

    void show();

    void close();
    void save(){}

    void uid(unsigned long long id) {_uid = id;}
};

#endif // NOTEBOOK_H
