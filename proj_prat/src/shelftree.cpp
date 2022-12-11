#include "shelftree.h"

Shelftree::Shelftree(){
    this->setColumnCount(1);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, this, &Shelftree::ShowContextMenu);
    connect(this, &QTreeWidget::itemDoubleClicked, this, &Shelftree::OpenNote);
}

void Shelftree::ShowContextMenu(const QPoint & point){
    QMenu contextMenu(this);

    if(this->currentItem()->parent()){
        CreateNoteActions();

        connect(EditNoteItem, &QAction::triggered, this, &Shelftree::EditNote);
        connect(DeleteNoteItem, &QAction::triggered, this, &Shelftree::DeleteNote);
    }
    else{
        CreateBookActions();

        connect(NewNoteAction, &QAction::triggered, this, &Shelftree::NewNote);
        connect(NewListAction, &QAction::triggered, this, &Shelftree::NewList);
        connect(EditBookItem, &QAction::triggered, this, &Shelftree::EditBook);
        connect(DeleteBookItem, &QAction::triggered, this, &Shelftree::DeleteBook);
    }

    contextMenu.addActions(CurrentActions);

    contextMenu.exec(mapToGlobal(point));
}

/* Book Related */
/* Signals */
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
void Shelftree::NewList(){
    QTreeWidgetItem* item = this->currentItem();
    unsigned mod_index = unsigned(this->indexOfTopLevelItem(item));

    emit List_Created(mod_index);
}
void Shelftree::OpenNote(){
    QTreeWidgetItem* child  = this->currentItem();
    QTreeWidgetItem* parent = child->parent();
    if (!parent)
        return;

    unsigned bx = this->indexOfTopLevelItem(parent);
    unsigned nx = parent->indexOfChild(child);

    emit Note_Opened(bx, nx);
}
void Shelftree::EditNote(){
    QTreeWidgetItem* child  = this->currentItem();
    QTreeWidgetItem* parent = child->parent();
    if (!parent)
        return;

    unsigned bx = this->indexOfTopLevelItem(parent);
    unsigned nx = parent->indexOfChild(child);

    emit Note_Edited(bx, nx);
}
void Shelftree::DeleteNote(){
    QTreeWidgetItem* child = this->currentItem();
    QTreeWidgetItem* parent = child->parent();
    if (!parent)
        return;

    unsigned bx = this->indexOfTopLevelItem(parent);
    unsigned nx = parent->indexOfChild(child);

    emit Note_Deleted(bx, nx);
}
/* Actions */
void Shelftree::CreateBookActions(){
    CurrentActions.clear();

    EditBookItem = new QAction();
    EditBookItem->setText("Renomear");

    DeleteBookItem = new QAction();
    DeleteBookItem->setText("Deletar");

    NewNoteAction = new QAction();
    NewNoteAction->setText("Criar nova nota");

    NewListAction = new QAction();
    NewListAction->setText("Criar nova lista");

    CurrentActions << EditBookItem << DeleteBookItem << NewNoteAction << NewListAction;
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
