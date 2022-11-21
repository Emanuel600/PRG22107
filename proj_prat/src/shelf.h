/* Modular Includes */
#include "notebook.h"

#ifndef SHELF_H
#define SHELF_H

class Shelf{
    vector<Notebook*> _books;

    unsigned long long _ind; // Índice do Notebook que está sendo visualizado
public:
    Shelf() {}
    Shelf(QString title) {Notebook* book = new Notebook(title); book->uid(0) ; _books.push_back(book); }
    Shelf(Notebook book) { _books.push_back(&book); }
    Shelf(Notebook* book) { _books.push_back(book); }

    ~Shelf();

    Notebook* open(unsigned long long i) { _ind = i ; return _books[i]; }
    Notebook* book(QString title) { Notebook* book = new Notebook(title); book->uid(_books.size()) ; _books.push_back(book); return book; }
    void book(Notebook book) { _ind = _books.size(); book.uid(_ind) ; _books.push_back(&book);}
    void book(Notebook* book) { _ind = _books.size(); book->uid(_ind); _books.push_back(book); }

    void del(unsigned long long i);
    // Recarrega estante de forma ineficiente
    void reload() {
        this->save();
        _books.erase(_books.begin(), _books.end());
        this->load_books();
    }

    /* IO */
    // Fecha Notebook
    void close(){ this->save() ; (this->open(_ind))->close(); }
    // Cria Notebooks a partir de um arquivo
    void load_books();
    // Salva Notebooks a partir em um arquivo
    void save();
    // Imprime notebooks contidos em uma shelf
    void showcase();
};

#endif // SHELF_H
