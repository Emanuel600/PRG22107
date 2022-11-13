/* System Includes */
#include <QDir>
#include <QFile>
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

    unsigned _uid;
public:
    Notebook() {_title = "";}
    Notebook(QString title) { _title=title; }

    Note* open(unsigned i) {return _notes[i];}
    vector<Note*> notes() {return _notes;}

    void title(QString title) { _title = title; }
    QString title() {return _title;}

    QJsonObject get_json();
    // Cria/adiciona notas
    void note(QString title);
    void note(QString title, QString cont);
    void note(Note* note) { _notes.push_back(note); }
    void note(vector<Note*> note) { _notes = note; }

    void show();
    void load();

    void close();
    void save(){}

    void uid(unsigned id) {_uid = id;}
};

#endif // NOTEBOOK_H
