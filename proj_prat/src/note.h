/* System Includes */
#include <vector>
#include <QString>
#include <iostream>
#include <QJsonArray>
#include <QJsonObject>
#include <QStringList>

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

    virtual ~Note();

    void title(QString title) { _title = title; }

    QString title() { return _title; }

    virtual void content(QString) = 0;

    virtual QStringList list_content() = 0;
    virtual QJsonObject get_json() = 0;
    virtual QString get_string() = 0;
    virtual QString content() = 0;
    virtual bool get_type() = 0;
    virtual void display() = 0;
    virtual void edit() = 0;
};

class Plain_Note: public Note{
private:
    QString _content;
public:
    Plain_Note() {}
    Plain_Note(QJsonObject note_obj);

    void content(QString cont) {_content = cont;}

    QString content() {return _content;}

    QStringList list_content();
    bool get_type() {return 0;}
    QJsonObject get_json();
    QString get_string();
    void display();
    void edit();
};

class Check_List: public Note{
private:
    vector<QString> _content;
    vector<bool> _checked;
public:
    Check_List() {}
    Check_List(QJsonObject note_obj);

    void add_item(QString item);
    void change(unsigned i, QString item) {_content[i] = item;}
    void clear(){_content.clear() ; _checked.clear(); }
    void del(unsigned i);

    void content(QString cont) {_content[0] = cont;}
    void checked(vector<bool> check) {_checked = check;}

    QString content() {return _content[0];}
    vector<bool> checked() {return _checked;}

    QStringList list_content();
    bool get_type() {return 1;}
    QJsonObject get_json();
    QString get_string();
    void display();
    void edit();
};

#endif // NOTE_H
