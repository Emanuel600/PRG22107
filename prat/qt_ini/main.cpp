#include "notepad.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication Editor(argc, argv);
    Notepad widget;
    widget.show();

    return Editor.exec();
}
