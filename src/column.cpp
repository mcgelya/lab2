#include "column.h"

#include <QLineEdit>
#include <QPushButton>
#include <QScrollBar>
#include <QTimer>
#include <stdexcept>
#include "array_sequence.h"
#include "list_sequence.h"
#include <QInputDialog>
#include "visualize.h"

Column::Column(QWidget* parent) : QWidget(parent) {
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
    QPushButton* addButton = new QPushButton("Добавить", this);
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

void ClearLayout(QLayout* layout) {
    if (layout == nullptr) {
        return;
    }
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (QWidget* w = item->widget()) {
            w->deleteLater();
        }
        if (QLayout* childLayout = item->layout()) {
            ClearLayout(childLayout);
        }
        delete item;
    }
}

void Column::Clear() {
    ClearLayout(vectorsLayout);
}

void SplitToSeq(const QString& s, Sequence<int>* res) {
    QStringList input = s.split(' ', Qt::SkipEmptyParts);
    for (const QString& c : input) {
        bool ok = 1;
        int val = c.toInt(&ok);
        if (!ok) {
            throw std::runtime_error("Overflow or incorrect string!");
        }
        res->Append(val);
    }
}

template <class T>
QDebug operator<<(QDebug dbg, const T& obj) {
    std::ostringstream oss;
    oss << obj;
    dbg << QString::fromStdString(oss.str());
    return dbg;
}

void Column::AddArraySequence(const QString& s) {
    ArraySequence<int>* cur = new ArraySequence<int>();
    SplitToSeq(s, cur);
    qDebug() << "ColumnArray::addSeq: " << *cur;

    ArraySequenceVisualize* line = new ArraySequenceVisualize(vectorsWidget);
    line->Initialize(cur);

    vectorsLayout->addWidget(line);

    vectorsWidget->adjustSize();
    QTimer::singleShot(
        0, this, [this]() { scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->maximum()); });
}

void Column::AddListSequence(const QString& s) {
    ListSequence<int>* cur = new ListSequence<int>();
    SplitToSeq(s, cur);
    qDebug() << "ColumnList::addSeq: " << *cur;

    ListSequenceVisualize* line = new ListSequenceVisualize(vectorsWidget);
    line->Initialize(cur);

    vectorsLayout->addWidget(line);

    vectorsWidget->adjustSize();
    QTimer::singleShot(
        0, this, [this]() { scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->maximum()); });
}
