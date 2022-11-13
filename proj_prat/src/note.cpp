#include "note.h"


QJsonObject Note::get_json(){
    QJsonObject note_json;

    note_json["title"] = _title;
    note_json["title"] = _contents;

    return note_json;
}
