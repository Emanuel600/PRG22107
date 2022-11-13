/* Modular Includes */
#include "notebook.h"

#ifndef SHELF_H
#define SHELF_H

class Shelf{
    vector<Notebook> _books;

    unsigned long long _ind; // Índice do Notebook que está sendo visualizado
public:
    Shelf() {}
    Shelf(QString title) {Notebook book(title); _books.push_back(book); }
    Shelf(Notebook book) { _books.push_back(book); }

    ~Shelf();

    Notebook open(unsigned long long i) { _ind = i ; Notebook book = _books[i]; book.load() ; return book; }
    Notebook book(QString title) { Notebook book(title); _books.push_back(book); return book; }
    Notebook book(Notebook book) {_books.push_back(book); return book; }

    void edit_book(Notebook book){_books[_ind] = book;}
    void del(unsigned long long i);

    /* IO */
    // Fecha Notebook
    void close(){ this->save() ; (this->open(_ind)).close(); }
    // Cria Notebooks a partir de um arquivo
    void load_books();
    // Salva Notebooks a partir em um arquivo
    void save();
    // Imprime notebooks contidos em uma shelf
    void showcase();
};

#endif // SHELF_H
