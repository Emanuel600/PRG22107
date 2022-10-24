/* Modular Includes */
#include "notebook.h"

#ifndef SHELF_H
#define SHELF_H

class Shelf{
    vector<Notebook> _books;

    unsigned _ind; // Índice do Notebook que está sendo visualizado
public:
    Shelf() {}

    Shelf(QString title) {Notebook book(title); _books.push_back(book); }
    Shelf(Notebook book) { _books.push_back(book); }

    ~Shelf();

    Notebook open(unsigned long long i) {return (_books[i]); }

    // Cria Notebooks a partir de um arquivo
    void create();
    // Salva Notebooks a partir em um arquivo
    void save();
    // Imprime notebooks contidos em uma shelf
    void showcase();
};

#endif // SHELF_H
