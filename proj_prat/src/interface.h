/* Modular Includes */
#include "notebook.h"

#ifndef INTERFACE_H
#define INTERFACE_H

class Interface{
    vector<Notebook*> _books;

    unsigned _ind; // Índice do Notebook que está sendo visualizado
public:
    Interface(string title) {Notebook book(title); _books.push_back(&book); };

    Notebook open(int i) {return *(_books[i]); };
    // Cria Notebooks a partir de um arquivo
    void create(string path);
    // Salva Notebooks a partir em um arquivo
    void save(string path);
};

#endif // INTERFACE_H
