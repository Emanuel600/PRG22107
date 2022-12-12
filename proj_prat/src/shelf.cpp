/* Modular Includes */
#include "shelf.h"

/* init */
Shelf::Shelf(QWidget* parent) : QMainWindow(parent){
    _ind = 0;

    Book_Tree = new Shelftree();
    Text_Editor = new QTextEdit();
    setCentralWidget(Text_Editor);
    Text_Editor->setReadOnly(1);
    /* Connects Book_Tree -> Shelf */
    connect(Book_Tree, &Shelftree::Book_Renamed, this, &Shelf::Rename_Book);
    connect(Book_Tree, &Shelftree::Book_Deleted, this, &Shelf::Delete_Book);
    connect(Book_Tree, &Shelftree::Note_Created, this, &Shelf::Append_Note);
    connect(Book_Tree, &Shelftree::Note_Deleted, this, &Shelf::Delete_Note);
    connect(Book_Tree, &Shelftree::Note_Edited, this, &Shelf::Rename_Note);
    connect(Book_Tree, &Shelftree::Note_Opened, this, &Shelf::Open_Note);
    /* Connects Text_Editor -> Shelf */
    connect(Text_Editor, &QTextEdit::textChanged, this, &Shelf::Update_Note);

    this->CreateActions();
    this->CreateMenus();
    this->CreateDock();

    this->load_books();
}
/* Slots */
/* Livros */
void Shelf::Rename_Book(unsigned index, QString* str_ptr){
    Notebook* book = _books[index];
    bool ok;
    (*str_ptr) = QInputDialog::getText(this, tr("Renomear livro"),
                                             tr("Título:"), QLineEdit::Normal,
                                             book->title(), &ok);
    book->title(*str_ptr);
}
void Shelf::Delete_Book(unsigned index){this->del(index);}
void Shelf::Append_Note(unsigned index, QString* str_ptr){
    Notebook* book = _books[index];
    bool ok;
    *str_ptr = QInputDialog::getText(this, tr("Criar nova nota"),
                                             tr("Nome da nota:"), QLineEdit::Normal,
                                             tr("Título"), &ok);
    Plain_Note* note_ptr = new Plain_Note();
    note_ptr->title(*str_ptr);
    book->note(note_ptr);
}
void Shelf::Append_List(unsigned index){
    Notebook* book = _books[index];
    bool ok;
    QString input = QInputDialog::getText(this, tr("Criar nova lista"),
                                             tr("Nome da lista:"), QLineEdit::Normal,
                                             tr("Título"), &ok);
    Check_List* note_ptr = new Check_List();
    note_ptr->title(input);
    book->note(note_ptr);
}
/* Notas */
void Shelf::Open_Note(unsigned bx, unsigned nx){
    Note* note_ptr = _books[bx]->notes()[nx];
    Text_Editor->setText(note_ptr->list_content()[0]);
    setCentralWidget(Text_Editor);
    Text_Editor->setReadOnly(0);
}
void Shelf::Rename_Note(unsigned bx, unsigned nx, QString* str_ptr){
    Note* note_ptr = _books[bx]->notes()[nx];

    bool ok;
    (*str_ptr) = QInputDialog::getText(this, tr("Renomear nota"),
                                             tr("Nome da nota:"), QLineEdit::Normal,
                                             note_ptr->title(), &ok);
    note_ptr->title(*str_ptr);
}
void Shelf::Update_Note(){
    QTreeWidgetItem* child = Book_Tree->currentItem();
    QTreeWidgetItem* parent = child->parent();

    if (!parent)
        return;

    unsigned bx = unsigned(Book_Tree->indexOfTopLevelItem(parent));
    unsigned nx = unsigned(parent->indexOfChild(child));

    Note* note_ptr = _books[bx]->notes()[nx];
    QString Note_Content = Text_Editor->toPlainText();

    note_ptr->content(Note_Content);
}
void Shelf::Delete_Note(unsigned bx, unsigned nx){
    Notebook* book = _books[bx];
    book->del(nx);
}
// Ações do livro
void Shelf::CreateActions(){
    newAct = new QAction(tr("&Novo livro"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Criar um livro novo"));

    connect(newAct, &QAction::triggered, this, &Shelf::create);
    ActionList << newAct;

    saveAct = new QAction(tr("&Salvar"), this);
    saveAct->setShortcut(QKeySequence::Save);
    saveAct->setStatusTip(tr("Salvar livros"));

    connect(saveAct, &QAction::triggered, this, &Shelf::save);
    ActionList << saveAct;
}

// Cria os menus
void Shelf::CreateMenus(){
    fileMenu = menuBar()->addMenu(tr("&File"));

    fileMenu->addActions(ActionList);
}

void Shelf::CreateDock(){
    QDockWidget* dock = new QDockWidget(tr("Livros"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setWidget(Book_Tree);
    dock->setAcceptDrops(0);

    addDockWidget(Qt::LeftDockWidgetArea, dock);
}

// Cria uma nota
void Shelf::create_note(){
    bool ok;
    QString input = QInputDialog::getText(this, tr("Criar nova nota"),
                                             tr("Nome da nota:"), QLineEdit::Normal,
                                             tr("Título"), &ok);
    Plain_Note* nota = new Plain_Note();
    nota->title(input);

    _books[_ind]->note(nota);
}
Notebook* Shelf::create(){
    bool ok;
    QString input = QInputDialog::getText(this, tr("Criar novo livro"),
                                             tr("Nome do livro:"), QLineEdit::Normal,
                                             tr("Título"), &ok);
    Notebook* book = this->book(input);
    return book;
}

/* Functional */
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

            _books.resize(unsigned(book_arr.size()));

            for (auto book_auto : book_arr){
                QJsonObject book_obj = book_auto.toObject();
                Notebook* book = new Notebook(book_obj);

                book->uid(uid);    // Como são salvos e carregados sempre da mesma forma, isto funciona como id único sem modificar o .json
                _books[uid++] = book;
                Book_Tree->add_book(book);
            }
        }
    }
    Book_Tree->expandAll();
}

QStringList Shelf::list(){
    QStringList list;

    for (auto item : _books)
        list << item->title();

    return list;
}

void Shelf::del(unsigned long long i){
    while (!(i<_books.size())){
        cout << "Index out of range, enter a vallid index: ";
        cin.clear();
        cin  >> i;
        cout << endl;
    }
    vector<Notebook*>::iterator it = _books.begin() + signed(i);
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
