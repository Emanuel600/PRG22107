/* Modular Includes */
#include "shelf.h"

// Salva notebooks em json
void Shelf::save(){
    cout << "Saving shelf" << endl;
    /* Objetos */
    QJsonObject main;
    QJsonObject temp_obj;

    /* Arrays */
    QJsonArray book_arr;

    for(vector<Notebook*>::iterator it = _books.begin(); it!=_books.end(); ++it){
        Notebook* book= *it;
        book->load();

        temp_obj = book->get_json();
        book_arr.append(temp_obj);
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
            QJsonArray book_arr = jason_obj[str].toArray();
            unsigned uid = 0;

            _books.resize(book_arr.size());

            unsigned i = 0;
            for (auto book_auto : book_arr){
                Notebook* book = new Notebook();

                QJsonObject book_obj = book_auto.toObject();
                QString     title    = book_obj["title"].toString();

                book->title(title);
                book->uid(uid++);    // Como são salvos e carregados sempre da mesma forma, isto funciona como id único sem modificar o .json

                _books[i++] = book;
            }
        }
    }
}

void Shelf::del(unsigned long long i){
    while (!(i<_books.size())){
        cout << "Index out of range, enter a vallid index: ";
        cin.clear();
        cin  >> i;
        cout << endl;
    }
    vector<Notebook*>::iterator it = _books.begin() + i;
    _books.erase(it);

    while (it != _books.end())
        (*it++)->uid(i++);
}

void Shelf::showcase(){
    for (auto book : _books)
        book->show();
}

Shelf::~Shelf(){
    cout << "~Shelf chamado" << endl;
    // Salva automaticamente quando o programa fecha
    this->save();
    // Deleta notas armazenadas na memoria e notebooks
    _books.clear();
    cout << "~Shelf encerrado" << endl;
}
