#include "column.h"

#include <QInputDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollBar>
#include <QTimer>

#include "array_sequence.h"
#include "list_sequence.h"
#include "utils.h"
#include "visualize.h"

Column::Column(const QString& name, QWidget* parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    mainLayout->addWidget(scrollArea);

    vectorsWidget = new QWidget(this);
    vectorsLayout = new QVBoxLayout(vectorsWidget);
    vectorsLayout->setSpacing(10);
    vectorsLayout->setContentsMargins(5, 5, 5, 5);
    vectorsWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    scrollArea->setWidget(vectorsWidget);

    QWidget* buttons = new QWidget(this);
    QHBoxLayout* buttonsLayout = new QHBoxLayout(buttons);
    QPushButton* addButton = new QPushButton("Добавить " + name, this);
    QPushButton* trashButton = new QPushButton(this);
    trashButton->setIcon(QIcon::fromTheme("user-trash"));
    trashButton->setIconSize(QSize(20, 20));
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(trashButton);

    QObject::connect(addButton, &QPushButton::clicked, this, &Column::AskedToAdd);
    QObject::connect(trashButton, &QPushButton::clicked, this, &Column::Clear);

    mainLayout->addWidget(buttons);
    setLayout(mainLayout);
}

void Column::Clear() {
    utils::ClearLayout(vectorsLayout);
}

void Column::AddArraySequence(const QString& s) {
    ArraySequence<int>* cur = new ArraySequence<int>();
    utils::SplitToSeq(s, cur);

    ArraySequenceVisualize* line = new ArraySequenceVisualize(vectorsWidget);
    line->Initialize(cur);

    vectorsLayout->addWidget(line);

    vectorsWidget->adjustSize();
    QTimer::singleShot(
        0, this, [this]() { scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->maximum()); });
}

void Column::AddListSequence(const QString& s) {
    ListSequence<int>* cur = new ListSequence<int>();
    utils::SplitToSeq(s, cur);

    ListSequenceVisualize* line = new ListSequenceVisualize(vectorsWidget);
    line->Initialize(cur);

    vectorsLayout->addWidget(line);

    vectorsWidget->adjustSize();
    QTimer::singleShot(
        0, this, [this]() { scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->maximum()); });
}
