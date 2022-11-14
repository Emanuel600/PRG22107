#include "note.h"

Note::Note(QJsonObject note_obj){
    _title = note_obj["title"].toString();
    _contents = note_obj["contents"].toString();
}

QJsonObject Note::get_json(){
    QJsonObject note_json;

    note_json["type"] = "p"; // Plain text
    note_json["title"] = _title;
    note_json["contents"] = _contents;

    return note_json;
}
