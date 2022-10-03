#include "interface.h"

int main(){
    Notebook book;

    book.note("Title");
    book.note("Title");
    book.note("");
    book.note("Title");
    book.note("Title");

    book.show();
}
