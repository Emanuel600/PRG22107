/* System Includes */
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QPrinter>
#include <QFile>
/* Module Includes */
#include "notepad.h"
#include "ui_notepad.h"

Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notepad){
    ui->setupUi(this);
}

Notepad::~Notepad(){
    delete ui;
}

/* Menu Bar */
// Cria novo arquivo
void Notepad::on_actionNew_triggered(){
    currentFile.clear();
    ui->textEdit->setText(QString());
}
// Abre novo arquivo
void Notepad::on_actionOpen_triggered(){
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}
// Salva arquivo
void Notepad::on_actionSave_triggered(){
    QString fileName;
    QString extension = ".txt";
    // Recebe novo arquivo se um nao estiver aberto
    if (currentFile.isEmpty()){ // equivalente a "save as"
        fileName = QFileDialog::getSaveFileName(this, "save");
        currentFile = fileName;
    } else { fileName = currentFile; }

    if (!fileName.contains(extension)){ fileName.append(extension); }

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::on_actionSaveAs_triggered(){
    QString filename = QFileDialog::getSaveFileName(this, "save as");

    QFile file(filename);

    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "cannot save file: " + file.errorString());
        return;
    }

    currentFile = filename;

    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::on_actionPrint_triggered(){
    QMessageBox::warning(this, "Warning", "Operation not supported");
}

void Notepad::on_actionExit_triggered(){
    // Salva arquivo
    on_actionSave_triggered();

    exit(0); // ^X (atalho) nao funciona
}
