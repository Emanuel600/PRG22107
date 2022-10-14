#include "interface.h"

int main(){
    Notebook book("aaaaa");

    book.note("Title");
    book.note("Title");
    book.note("", "Lorena Epsum");
    book.note("Title", "Lorem Ipsum");
    book.note("Title");

    book.show();

    Notebook trog("dyte");

    trog.note("b", "v");
    trog.note("i");
    trog.note("j");

    Interface inter(&book);
    inter.add(&trog);
    inter.add(new Notebook);

    inter.save();
    inter.create();
}
