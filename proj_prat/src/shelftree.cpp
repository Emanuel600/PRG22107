#include "shelftree.h"

Shelftree::Shelftree(){
    this->setColumnCount(1);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, this, &Shelftree::ShowContextMenu);
    this->setHeaderLabel("Livros");
}

void Shelftree::ShowContextMenu(const QPoint & point){
    QMenu contextMenu(this);

    QTreeWidgetItem* item = this->currentItem();

    int header_raw = -1;

    if(this->currentItem()->parent()){
        CreateNoteActions();

        header_raw = item->parent()->indexOfChild(item);
    }
    else{
        CreateBookActions();

        header_raw = this->indexOfTopLevelItem(item);

        connect(NewNoteAction, &QAction::triggered, this, &Shelftree::NewNote);
        connect(EditBookItem, &QAction::triggered, this, &Shelftree::EditBook);
        connect(DeleteBookItem, &QAction::triggered, this, &Shelftree::DeleteBook);
    }

    QString header = QString::number(header_raw);

    this->setHeaderLabel(header);

    contextMenu.addActions(CurrentActions);

    contextMenu.exec(mapToGlobal(point));
}

/* Book Related */
void Shelftree::EditBook(){
    QTreeWidgetItem* item = this->currentItem();
    unsigned mod_index = unsigned(this->indexOfTopLevelItem(item));

    emit Book_Renamed(mod_index);
}
void Shelftree::DeleteBook(){
    QTreeWidgetItem* item = this->currentItem();
    unsigned mod_index = unsigned(this->indexOfTopLevelItem(item));

    emit Book_Deleted(mod_index);
}
void Shelftree::NewNote(){
    QTreeWidgetItem* item = this->currentItem();
    unsigned mod_index = unsigned(this->indexOfTopLevelItem(item));

    emit Note_Created(mod_index);
}
void Shelftree::CreateBookActions(){
    CurrentActions.clear();

    EditBookItem = new QAction();
    EditBookItem->setText("Renomear");

    DeleteBookItem = new QAction();
    DeleteBookItem->setText("Deletar");

    NewNoteAction = new QAction();
    NewNoteAction->setText("Criar nova nota");

    CurrentActions << EditBookItem << DeleteBookItem << NewNoteAction;
}

/* Note Related */
void Shelftree::CreateNoteActions(){
    CurrentActions.clear();

    EditNoteItem = new QAction();
    EditNoteItem->setText("Renomear");

    DeleteNoteItem = new QAction();
    DeleteNoteItem->setText("Deletar");

    CurrentActions << EditNoteItem << DeleteNoteItem;
}


void Shelftree::add_list(QList<QString> list){
    QTreeWidgetItem* item_ptr = new QTreeWidgetItem(list);
    this->addTopLevelItem(item_ptr);
}

void Shelftree::add_book(Notebook *book){
    QTreeWidgetItem* root = new QTreeWidgetItem();
    root->setText(0, book->title());

    this->addTopLevelItem(root);

    QList<QTreeWidgetItem*> notes;
    QTreeWidgetItem* item_ptr;

    for (Note* note : book->notes()){
        item_ptr = new QTreeWidgetItem();
        item_ptr->setText(0, note->title());
        notes.append(item_ptr);
    }

    root->addChildren(notes);
}
