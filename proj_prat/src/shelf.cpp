/* Modular Includes */
#include "shelf.h"

// Salva notebooks em json
void Shelf::save(){
    cout << "Saving shelf" << endl;

    /* Temporários */
    Note temp_nota;

    /* Objetos */
    QJsonObject main;
    QJsonObject temp_obj;

    /* Arrays */
    QJsonArray book_arr;

    for(vector<Notebook>::iterator it = _books.begin(); it!=_books.end(); ++it){
        Notebook book= *it;
        book.load();
        book_arr.append(book.get_json());
    }
    main["Notebook"] = book_arr;

    QByteArray output = QJsonDocument(main).toJson();

    QFile fout(QDir::currentPath() + "\\output.json");
    if (fout.open(QIODevice::WriteOnly)){
        fout.write(output);
        fout.close();
    } else {
        cerr << "\nErro ao salvar o arquivo" << endl;
    }
    return;
}
// Cria notebooks a partir de um json
void Shelf::load_books(){
    QByteArray input;

    QFile fin(QDir::currentPath() + "\\output.json");
    if(fin.open(QIODevice::ReadOnly)){
        input = fin.readAll();
        fin.close();
    } else {
        cerr << "Erro ao abrir arquivo\n" << endl;
        return;
    }

    QJsonParseError jsonError;
    QJsonDocument jason = QJsonDocument::fromJson(input, &jsonError);
    if(jsonError.error != QJsonParseError::NoError){
        cerr << "\nErro ao traduzir json" << endl;
        return;
    }

    if(jason.isObject()){
        QJsonObject jason_obj = jason.object(); // Contains all saved notebooks
        QString str = "Notebook";
        if(jason_obj.contains(str)){ // Verifica que possui notebook salvo
            QJsonArray book_jason = jason_obj[str].toArray();
            unsigned uid = 0;

            for (auto book_auto : book_jason){
                Notebook book;

                QJsonObject book_obj = book_auto.toObject();
                QString     title    = book_obj["title"].toString();

                book.title(title);
                book.uid(uid++);    // Como são salvos e carregados sempre da mesma forma, isto funciona como id único sem modificar o .json

                _books.push_back(book);
            }
        }
    }
}

void Shelf::del(unsigned long long i){
    vector<Notebook>::iterator it = _books.begin() + i;
    _books.erase(it);
}

void Shelf::showcase(){
    for (auto book : _books)
        book.show();
}

Shelf::~Shelf(){
    // Salva automaticamente quando o programa fecha
    this->save();
    // Deleta notas armazenadas na memoria
    for (auto book : _books)
        book.close();
}
