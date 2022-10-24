#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>

namespace Ui {
class Notepad;
}

class Notepad : public QMainWindow{
    Q_OBJECT

public:
    explicit Notepad(QWidget *parent = nullptr);
    ~Notepad();

    void New();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_actionPrint_triggered();

    void on_actionExit_triggered();

    void on_pushButton_5_clicked();

    void on_toolButton_triggered(QAction *arg1);

private:
    Ui::Notepad *ui;
    QString currentFile;
};

#endif // NOTEPAD_H
