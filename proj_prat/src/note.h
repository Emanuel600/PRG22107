/* System Includes */
#include <string>
#include <iostream>

using namespace std;

#ifndef NOTE_H
#define NOTE_H

class Note{
private:
    string _title;
    string _contents; // Pode ser feita em markdown no QT
public:
    Note() {};
    Note(string title) {_title = title; }
    Note(string title, string cont) {_title = title; _contents = cont; }

    void title(string title) { _title = title; }
    void content(string contents) { _contents = contents; }

    string title() { return _title; }
    string content() { return _contents; }
    // Salva em formato json
    void json(string path);
};

#endif // NOTE_H
