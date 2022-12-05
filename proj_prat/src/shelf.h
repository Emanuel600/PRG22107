/* System Includes */
#include <QInputDialog>
#include <QMainWindow>
#include <QTextEdit>

/* Modular Includes */
#include "notebook.h"
#include "shelftree.h"
#include "shelflist.h"

#ifndef SHELF_H
#define SHELF_H

class Shelf : public QMainWindow{
    Q_OBJECT

    vector<Notebook*> _books;

    unsigned long long _ind; // Índice do Notebook que está sendo visualizado
public:
    Shelf(QWidget *parent = nullptr);

    ~Shelf();

    Notebook* open(unsigned long long i) { _ind = i ; return _books[i]; }

    Notebook* create();
    void create_note();

    Notebook* book(QString title) {
        Notebook* book = new Notebook(title);
        book->note("Teste", "I won't even be able to see this");

        _ind = _books.size();
        book->uid(_ind);
        _books.push_back(book);

        Book_List->addItem(book->title());
        Book_Tree->add_book(book);
        return book;
    }

    void book(Notebook book) {
        _ind = _books.size();
        book.uid(_ind) ;
        _books.push_back(&book);
        Book_List->addItem(book.title());
    }

    void book(Notebook* book) {
        _ind = _books.size(); book->uid(_ind);
        _books.push_back(book);
        Book_List->addItem(book->title());
    }

    void del(unsigned long long i);
    // Recarrega estante de forma ineficiente
    void reload() {
        this->save();
        _books.clear();
        this->load_books();
    }
    // Lista livros
    QStringList list();
    // Carrega notas para interface gráfica
    void load_notes();

    /* IO */
    // Fecha Notebook
    void close(){ this->save() ; _books[_ind]->close(); if (Note_List) delete Note_List; }
    // Cria Notebooks a partir de um arquivo
    void load_books();
    // Salva Notebooks a partir em um arquivo
    void save();
    // Imprime notebooks contidos em uma shelf
    void showcase();

private slots:
    void item_dclicked(QListWidgetItem*item);
private:
    void CreateMenus();
    // Acções dos livros
    void CreateBActions();
    // Ações das notas
    void CreateNActions();

    QTextEdit* Text_Editor;
    ShelfList* Book_List;
    ShelfList* Note_List;
    Shelftree* Book_Tree;

    QMenu* fileMenu;
    QAction* newAct;
    QAction* saveAct;

    QList<QAction*> ActionList;
};

#endif // SHELF_H
