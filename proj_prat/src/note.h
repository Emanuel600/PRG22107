/* System Includes */
#include <vector>
#include <QString>
#include <iostream>
#include <QJsonObject>

using namespace std;

#ifndef NOTE_H
#define NOTE_H

class Note{
private:
    QString _title;
    QString _contents; // Pode ser feita em markdown no QT
public:
    Note() {}
    Note(QString title) {_title = title;}
    Note(QString title, QString cont) {_title = title; _contents = cont;}
    Note(QJsonObject note_obj);

    ~Note() { cout << "Note {" << _title.toStdString() << "} has been destroyed" << endl; }

    void title(QString title) { _title = title; }
    void content(QString contents) { _contents = contents; }

    QString title() { return _title; }
    QString content() { return _contents;}

    QJsonObject get_json();
};

#endif // NOTE_H
