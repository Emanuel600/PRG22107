/* System Includes */
#include <QInputDialog>
#include <QDockWidget>
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

        _ind = _books.size();
        book->uid(_ind);
        _books.push_back(book);
        Book_Tree->add_book(book);
        return book;
    }

    void book(Notebook book) {
        _ind = _books.size();
        book.uid(_ind) ;
        _books.push_back(&book);
        Book_Tree->add_book(&book);
    }

    void book(Notebook* book) {
        _ind = _books.size(); book->uid(_ind);
        _books.push_back(book);
        Book_Tree->add_book(book);
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
    void close(){ this->save() ; _books[_ind]->close();}
    // Cria Notebooks a partir de um arquivo
    void load_books();
    // Salva Notebooks a partir em um arquivo
    void save();
    // Imprime notebooks contidos em uma shelf
    void showcase();
private slots:
    /* Chamados quando Book_Tree é modificada */
    /* Livros */
    void Rename_Book(unsigned index);
    void Delete_Book(unsigned index);
    void Append_Note(unsigned index);
    void Append_List(unsigned index);
    /* Notas/Listas */
    void Open_Note(unsigned bx, unsigned nx);
    void Update_Note(unsigned bx, unsigned nx);
    void Delete_Note(unsigned bx, unsigned nx);
private:
    /* Criar Componentes da GUI */
    // Dock
    void CreateDock();
    // Menu
    void CreateMenus();
    // Ações
    void CreateActions();

    QTextEdit* Text_Editor;
    Shelftree* Book_Tree;

    QMenu* fileMenu;
    QAction* newAct;
    QAction* saveAct;

    QList<QAction*> ActionList;
};

#endif // SHELF_H
