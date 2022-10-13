/* Modular Includes */
#include "notebook.h"

#ifndef INTERFACE_H
#define INTERFACE_H

class Interface{
    vector<Notebook*> _books;

    unsigned _ind; // Índice do Notebook que está sendo visualizado
public:
    Interface(QString title) {Notebook book(title); _books.push_back(&book); }
    Interface(Notebook* book) { _books.push_back(book); }

    Notebook open() {return **(_books.begin()); }

    // Cria Notebooks a partir de um arquivo
    Interface create();
    // Salva Notebooks a partir em um arquivo
    void save();
    // Adiciona notebook a uma interface existente
    void add(Notebook* book) { _books.push_back(book); }
};

#endif // INTERFACE_H
