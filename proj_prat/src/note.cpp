#include "note.h"

/* Note */
Note::~Note(){
    cout << "Note {" << _title.toStdString() << "} has been destroyed" << endl;
}
/* Plain_Note */
Plain_Note::Plain_Note(QJsonObject note_obj){
    _title = note_obj["title"].toString();
    _content = note_obj["contents"].toString();
}

QJsonObject Plain_Note::get_json(){
    QJsonObject note_json;

    note_json["type"] = "p"; // Plain text
    note_json["title"] = _title;
    note_json["contents"] = _content;

    return note_json;
}

QString Plain_Note::get_string(){
    QString string = " #" + _title + "\n\n";
    string += _content;

    return string;
}

void Plain_Note::display(){
    cout << "Title: " << _title.toStdString() << endl;
    cout << "---\n" << _content.toStdString() << endl;
}

void Plain_Note::edit(){
    cout << "1 - Editar título" << endl;
    cout << "2 - Editar Conteúdo" << endl;
    cout << "* - Cancelar" << endl;

    unsigned short choice;
    cin.clear();
    cin >> choice;

    cin.clear();
    cin.ignore(INT_MAX, '\n');
    string input;
    QString Qinput;

    switch (choice){
    case 1:
        cout << "Entre com o novo título" << endl;
        getline(cin, input);
        Qinput = input.c_str();
        this->title(Qinput);
        break;
    case 2:
        cout << "Entre com o novo conteudo" << endl;
        getline(cin, input);
        Qinput = input.c_str();
        this->content(Qinput);
        break;
    default:
        break;
    }
}
/* Check_List*/
Check_List::Check_List(QJsonObject note_obj){
    QJsonArray contents = note_obj["contents"].toArray();
    QJsonArray checked = note_obj["checked"].toArray();

    _title = note_obj["title"].toString();

    for(int i=0; i < checked.size(); i++){
        _content.push_back(contents[i].toString());
        _checked.push_back(checked[i].toBool());
    }
}

QJsonObject Check_List::get_json(){
    QJsonObject note_json;
    QJsonArray  contents;
    QJsonArray  checked;

    unsigned short i = 0;
    while (i < _content.size()){
        contents.append(_content[i]);
        checked.append(char(_checked[i]));
        i++;
    }

    note_json["type"] = "c"; // Plain text
    note_json["title"] = _title;
    note_json["contents"] = contents;
    note_json["checked"] = checked;

    return note_json;
}

QString Check_List::get_string(){
    QString string = _title + "\n\n";

    unsigned i = 0;

    while (i < _checked.size()){
        string += " - [";
        if (_checked[i])
            string += "x";
        else
            string += " ";
        string += "] " + _content[i++] + "\n";
    }

    return string;
}

void Check_List::display(){
    cout << "Title: " << _title.toStdString() << endl;

    unsigned i = 0;

    while (i < _checked.size()){
        cout << i << " - [";
        if (_checked[i])
            cout << "x";
        else
            cout << " ";
        cout << "] " << _content[i++].toStdString() << endl;
    }
}

void Check_List::add_item(QString item){
    _content.push_back(item);
    _checked.push_back(0);
}

void Check_List::edit(){
    cout << "1 - Editar título" << endl;
    cout << "2 - Editar item" << endl;
    cout << "3 - Adicionar item" << endl;
    cout << "4 - Remover item" << endl;
    cout << "* - Cancelar" << endl;

    unsigned short choice;
    cin.clear();
    cin >> choice;
    cin.clear();
    string input;
    QString Qinput;

    switch (choice){
    case 1:
        cout << "Entre com o novo título" << endl;
        cin.ignore(INT_MAX, '\n');
        getline(cin, input);
        Qinput = input.c_str();
        this->title(Qinput);
        break;
    case 2:
        cout << "Entre com o número do item que quer editar" << endl;
        cin  >> choice;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        getline(cin, input);
        Qinput = input.c_str();
        this->change(choice, Qinput);
        break;
    case 3:
        cout << "Entre com o item que quer adicionar" << endl;
        cin.ignore(INT_MAX, '\n');
        getline(cin, input);
        Qinput = input.c_str();
        this->add_item(Qinput);
        break;
    case 4:
        cout << "Entre com o índice que quer deletar" << endl;
        cin  >> choice;
        this->del(choice);
        break;
    default:
        break;
    }
}

void Check_List::del(unsigned i){
    vector<QString>::iterator it = _content.begin() + i;
    _content.erase(it);

    vector<bool>::iterator bit = _checked.begin() + i;
    _checked.erase(bit);
}
