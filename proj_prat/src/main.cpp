#include <clocale>
#include <limits.h>
#include <QApplication>

#include "shelf.h"

int main(int argc, char *argv[]){
    // init
    if (std::setlocale(LC_ALL, "portuguese") == NULL) // Não funciona
        cerr << "Erro ao localizar o programa, erros de acento são esperados" << endl;

    QApplication a(argc, argv);
    Shelf shelf;
    shelf.show();/*

    // menu
    string temp;
    QString tmp;
    unsigned index;

    Note* note_ptr = NULL;
    Plain_Note* plain_ptr = new Plain_Note();
    Check_List* clist_ptr = new Check_List();
    Notebook* placeholder_book;
    unsigned short choice;

    while (1){
        cout << " ================================================= " << endl;
        cout << "1 - Mostrar livros armazenados na estante" << endl;
        cout << "2 - Ler um dos livros armazenados na estante" << endl;
        cout << "3 - Criar um novo livro" << endl;
        cout << "4 - Editar um livro" << endl;
        cout << "5 - Deletar um livro (notas não serão salvas)" << endl;
        cout << "9 - Salvar todos os livros e notas" << endl;
        cout << "* - Sair do programa (salva automáticamente)" << endl;
        cout << " ================================================= " << endl;

        clist_ptr->clear();

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
            cin.clear();
            cin >> index;

            placeholder_book = shelf.open(index);
            placeholder_book->load();
            placeholder_book->show();

            if (placeholder_book->notes().empty()){
                cout << "Livro está vazio" << endl;
                break;
            }

            cout << "Entre com a nota que quer abrir: ";
            cin.clear();
            cin  >> index;
            note_ptr = placeholder_book->notes()[index];
            note_ptr->display();

            getchar();
            break;
        case 3:
            cout << "Título do livro: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            getline(cin, temp);
            tmp = temp.c_str();

            placeholder_book = shelf.book(tmp);

            cout << "Entre '1' para criar uma nota: ";
            cin.clear();
            cin  >> choice;
            if (!choice)
                 break;
            cout << "Entre com o título da nota: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            getline(cin, temp);
            tmp = temp.c_str();

            plain_ptr->title(tmp);
            // Não funciona como deve, mas vai ser concertado com a GUI
            cout << "Entre com o conteúdo da nota: ";
            cin.clear();
            getline(cin, temp);
            tmp = temp.c_str();
            plain_ptr->content(tmp);

            placeholder_book->note(plain_ptr);
            break;
        case 4:
            cout << "Entre com o índice que quer modificar" << endl;
            shelf.showcase();
            cin.clear();
            cin >> index;
            placeholder_book = shelf.open(index);
            placeholder_book->load();
            placeholder_book->show();

            cout << "1 - Criar uma nota simples" << endl;
            cout << "2 - Criar uma lista de tarefas" << endl;
            cout << "3 - Deletar uma nota/lista qualquer" << endl;
            cout << "4 - Editar uma nota/lista qualquer" << endl;
            cout << "* - Cancelar" << endl;

            cin.clear();
            cin  >> choice;
            cin.clear();

            switch(choice){
            case 1:
                cin  >> choice;

                cout << "Entre com o título da nota: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                getline(cin, temp);
                tmp = temp.c_str();

                plain_ptr->title(tmp);

                cout << "Entre com o conteúdo da nota: ";
                cin.clear();
                getline(cin, temp);
                tmp = temp.c_str();
                plain_ptr->content(tmp);
                placeholder_book->note(plain_ptr);
                break;
            case 2:
                cout << "Entre com o título da nota: ";
                cin.ignore(INT_MAX, '\n');
                getline(cin, temp);
                tmp = temp.c_str();

                clist_ptr->title(tmp);

                cout << "Entre com um item:" << endl;

                cin.clear();
                getline(cin, temp);
                tmp = temp.c_str();

                clist_ptr->add_item(tmp);
                placeholder_book->note(clist_ptr);
                break;
            case 3:
                cout << "Entre com a nota que quer deletar: ";
                cin  >> index;
                placeholder_book->del(index);
                break;
            case 4:
                cout << "Entre com a nota que quer editar: " << endl;
                cin  >> choice;
                note_ptr = placeholder_book->open(choice);
                note_ptr->edit();
                break;
            default:
                break;
            }
            break;
        case 5:
            cout << "Entre com o índice que quer deletar" << endl;
            shelf.showcase();
            cout << ": ";
            cin.clear();
            cin  >> index;
            shelf.del(index);
            break;
        case 9:
            shelf.save();
            break;
        default:
            cout << "Salvando e terminando programa" << endl;
            delete clist_ptr;
            delete plain_ptr;
            return 0;
        }
    }*/
    return a.exec();
}
