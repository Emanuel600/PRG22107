#include "shelf.h"

int main(){
    // init
    Shelf shelf;
    shelf.load_books();
    // menu
    bool stay = 1;
    unsigned char choice;

    while (stay){
        cout << "Entre com a ação desejada" << endl;
        cout << "1 - Mostrar livros armazenados na estante" << endl;
        cout << "2 - Abrir um dos livros armazenados na estante" << endl;
        cout << "9 - Salvar todos os livros e notas" << endl;
        cout << "* - Sair do programa (salva automáticamente)" << endl;

        cin >> choice;

        switch (choice){
        case 1:
            shelf.showcase();
            break;
        case 2:
            cout << "não" << endl;
            break;
        default:
            return 0;
        }
    }
}
