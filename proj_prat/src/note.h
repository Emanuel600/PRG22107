/* System Includes */
#include <vector>
#include <QString>
#include <iostream>
#include <QJsonArray>
#include <QJsonObject>

using namespace std;

#ifndef NOTE_H
#define NOTE_H

class Note{
protected:
    QString _title;
public:
    Note() {}
    Note(QString title) {_title = title;}
    Note(QJsonObject note_obj);

    virtual ~Note() { cout << "Note {" << _title.toStdString() << "} has been destroyed" << endl; }

    void title(QString title) { _title = title; }

    QString title() { return _title; }

    virtual QJsonObject get_json() = 0;
    virtual string display() = 0;
};

class Plain_Note: public Note{
private:
    QString _content;
public:
    void content(QString cont) {_content = cont;}

    QString content() {return _content;}

    QJsonObject get_json();
    string display() {return "";}
};

class Check_List: public Note{
private:
    vector<QString> _content;
public:
    QJsonObject get_json();
    string display() {return "";}
};

#endif // NOTE_H
