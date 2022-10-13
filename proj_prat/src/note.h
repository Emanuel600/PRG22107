/* System Includes */
#include <QString>
#include <iostream>

using namespace std;

#ifndef NOTE_H
#define NOTE_H

class Note{
private:
    QString _title;
    QString _contents; // Pode ser feita em markdown no QT
public:
    Note() {}
    Note(QString title) {_title = title; }
    Note(QString title, QString cont) {_title = title; _contents = cont; }

    void title(QString title) { _title = title; }
    void content(QString contents) { _contents = contents; }

    QString title() { return _title; }
    QString content() { return _contents; }
};

#endif // NOTE_H
