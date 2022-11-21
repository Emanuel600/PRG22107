#include "note.h"

QJsonObject Plain_Note::get_json(){
    QJsonObject note_json;

    note_json["type"] = "p"; // Plain text
    note_json["title"] = _title;
    note_json["contents"] = _content;

    return note_json;
}

QJsonObject Check_List::get_json(){
    QJsonObject note_json;
    QJsonArray  contents;

    unsigned short i = 0;
    for (auto item : _content){
        contents[i++] = item;
    }

    note_json["type"] = "c"; // Plain text
    note_json["title"] = _title;
    note_json["contents"] = contents;

    return note_json;
}
