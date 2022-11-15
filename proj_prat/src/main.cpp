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
    Note* note_ptr = NULL;
    Note placeholder_note;
    Notebook placeholder_book;
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
            placeholder_book.load();
            placeholder_book.show();

            if (placeholder_book.notes().empty()){
                cout << "Livro está vazio" << endl;
                break;
            }

            cout << "Entre com a nota que quer abrir: ";
            cin.clear();
            cin  >> index;
            placeholder_note = *(placeholder_book.notes()[index]);
            cout << "Title: " << placeholder_note.title().toStdString() << endl;
            cout << placeholder_note.content().toStdString() << endl;
            cout << "Aperte qualquer tecla para fechar" << endl;

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

            note_ptr = new Note();
            note_ptr->title(tmp);
            // Não funciona como deve, mas vai ser concertado com a GUI
            cout << "Entre com o conteúdo da nota: ";
            cin.clear();
            getline(cin, temp);
            tmp = temp.c_str();
            note_ptr->content(tmp);

            placeholder_book.note(note_ptr);
            shelf.edit_book(placeholder_book);
            shelf.reload();
            break;
        case 4:
            cout << "Entre com o índice que quer modificar" << endl;
            shelf.showcase();
            cin.clear();
            cin >> index;
            placeholder_book = shelf.open(index);
            placeholder_book.load();
            placeholder_book.show();

            cout << "1 - Criar uma nota" << endl;
            cout << "2 - Deletar um nota" << endl;
            cout << "* - Cancelar" << endl;

            cin.clear();
            cin  >> choice;

            switch(choice){
            case 1:
                cout << "Entre com o título da nota: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                getline(cin, temp);
                tmp = temp.c_str();

                note_ptr = new Note();
                note_ptr->title(tmp);
                // Não funciona como deve, mas vai ser concertado com a GUI
                cout << "Entre com o conteúdo da nota: ";
                cin.clear();
                getline(cin, temp);
                tmp = temp.c_str();
                note_ptr->content(tmp);
                placeholder_book.note(note_ptr);
                break;
            case 2:
                cout << "Entre com a nota que quer deletar: ";
                cin.clear();
                cin  >> index;
                placeholder_book.del(index);
                break;
            default:
                break;
            }

            shelf.edit_book(placeholder_book);
            shelf.reload(); // Resets note_ptr
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
            return 0;
        }
    }
}
