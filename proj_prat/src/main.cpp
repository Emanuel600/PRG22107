#include <clocale>
#include <limits.h>

#include "shelf.h"

int main(){
    // init
    Shelf shelf;
    shelf.load_books();
    if (std::setlocale(LC_ALL, "portuguese") == NULL) // Não funciona
        cerr << "Erro ao localizar o programa, erros de acento são esperados" << endl;
    // menu
    string temp;
    QString tmp;
    unsigned index;
    Notebook placeholder;
    unsigned short choice;

    while (1){
        cout << " ======================================= " << endl;
        cout << "1 - Mostrar livros armazenados na estante" << endl;
        cout << "2 - Ler um dos livros armazenados na estante" << endl;
        cout << "3 - Criar um novo livro (WIP)" << endl;
        cout << "4 - Editar um livro (WIP)" << endl;
        cout << "5 - Deletar um livro (notas não serão salvas)" << endl;
        cout << "9 - Salvar todos os livros e notas" << endl;
        cout << "* - Sair do programa (salva automáticamente)" << endl;

        cout << "Entre com sua escolha: ";

        while (1){
            cin.clear();
            if (cin >> choice)
                break;
        }
        cout << endl;

        switch (choice){
        case 1:
            shelf.showcase();
            break;
        case 2:
            cout << "Entre com índice do livro que deseja abrir" << endl;
            shelf.showcase();
            cout << ": ";
            cin >> index;

            placeholder = shelf.open(index);
            placeholder.load();
            placeholder.show();
            break;
        case 3:
            cout << "Título do livro: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            getline(cin, temp);
            tmp = temp.c_str();
            placeholder = shelf.book(tmp);

            cout << "WIP - menu para criar nota" << endl;
            break;
        case 4:
            cout << "Entre com o índice que quer modificar" << endl;
            shelf.showcase();
            cin >> index;
            placeholder = shelf.open(index);
            placeholder.load();
            placeholder.show();

            cout << "WIP - menu para criar/editar nota" << endl;
            break;
        case 5:
            cout << "Entre com o índice que quer deletar" << endl;
            shelf.showcase();
            cout << ": ";
            cin  >> index;
            shelf.del(index);
            break;
        case 9:
            shelf.save();
            break;
        default:
            cout << "Salvando e terminando programa" << endl;
            return 0;
        }
    }
}
