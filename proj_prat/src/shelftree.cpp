#include "shelftree.h"

Shelftree::Shelftree(){
    this->setColumnCount(1);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, this, &Shelftree::ShowContextMenu);
    this->setHeaderLabel("Livros");
}

void Shelftree::ShowContextMenu(const QPoint & point){
    QMenu contextMenu(this);

    CreateActions();

    connect(EditItem, &QAction::triggered, this, &Shelftree::Edit);
    contextMenu.addAction(EditItem);

    contextMenu.exec(mapToGlobal(point));
}

void Shelftree::CreateActions(){
    EditItem = new QAction();
    EditItem->setText("Edit");
}

void Shelftree::Edit(){
    if(this->currentItem()->parent())
        setHeaderLabel("Note selected");
    else
        setHeaderLabel("Book selected");
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
