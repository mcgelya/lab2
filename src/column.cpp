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

    seqsContainer = new QWidget(this);
    seqsLayout = new QVBoxLayout(seqsContainer);
    seqsLayout->setSpacing(10);
    seqsLayout->setContentsMargins(5, 5, 5, 5);
    seqsContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    scrollArea->setWidget(seqsContainer);

    QWidget* buttons = new QWidget(this);
    QHBoxLayout* buttonsLayout = new QHBoxLayout(buttons);
    QPushButton* addButton = new QPushButton("Добавить " + name, this);
    QPushButton* trashButton = new QPushButton("🗑️", this);
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(trashButton);

    QObject::connect(addButton, &QPushButton::clicked, this, &Column::AskedToAdd);
    QObject::connect(trashButton, &QPushButton::clicked, this, &Column::Clear);

    mainLayout->addWidget(buttons);
    setLayout(mainLayout);
}

void Column::Clear() {
    utils::ClearLayout(seqsLayout);
}

void Column::AddArraySequence(ArraySequence<int>* seq, bool immutable) {
    ArraySequenceVisualize* line = new ArraySequenceVisualize(seqsContainer, immutable);
    line->Initialize(seq);

    QObject::connect(line, &SequenceVisualize::AskedToPrepend, [=, this] {
        int x;
        bool ok = utils::AskValue(x);
        if (!ok) {
            return;
        }
        if (!immutable) {
            seq->Prepend(x);
            line->VisualizeSeq();
        } else {
            AddArraySequence(seq->Prepend(x), 1);
        }
    });
    QObject::connect(line, &SequenceVisualize::AskedToAppend, [=, this] {
        int x;
        bool ok = utils::AskValue(x);
        if (!ok) {
            return;
        }
        if (!immutable) {
            seq->Append(x);
            line->VisualizeSeq();
        } else {
            AddArraySequence(seq->Append(x), 1);
        }
    });

    seqsLayout->addWidget(line);

    seqsContainer->adjustSize();
    QTimer::singleShot(0, this, [this]() {
        scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->maximum());
    });
}

void Column::AddListSequence(ListSequence<int>* seq, bool immutable) {
    ListSequenceVisualize* line = new ListSequenceVisualize(seqsContainer, immutable);
    line->Initialize(seq);

    QObject::connect(line, &SequenceVisualize::AskedToPrepend, [=, this] {
        int x;
        bool ok = utils::AskValue(x);
        if (!ok) {
            return;
        }
        if (!immutable) {
            seq->Prepend(x);
            line->VisualizeSeq();
        } else {
            AddListSequence(seq->Prepend(x), 1);
        }
    });
    QObject::connect(line, &SequenceVisualize::AskedToAppend, [=, this] {
        int x;
        bool ok = utils::AskValue(x);
        if (!ok) {
            return;
        }
        if (!immutable) {
            seq->Append(x);
            line->VisualizeSeq();
        } else {
            AddListSequence(seq->Append(x), 1);
        }
    });

    seqsLayout->addWidget(line);

    seqsContainer->adjustSize();
    QTimer::singleShot(0, this, [this]() {
        scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->maximum());
    });
}

void Column::AddArraySequence(const QString& s, bool immutable) {
    ArraySequence<int>* cur = new ArraySequence<int>();
    utils::SplitToMutableSeq(s, cur);

    if (!immutable) {
        AddArraySequence(cur, 0);
    } else {
        AddArraySequence(new ImmutableArraySequence<int>(cur), 1);
    }
}

void Column::AddListSequence(const QString& s, bool immutable) {
    ListSequence<int>* cur = new ListSequence<int>();
    utils::SplitToMutableSeq(s, cur);

    if (!immutable) {
        AddListSequence(cur, 0);
    } else {
        AddListSequence(new ImmutableListSequence<int>(cur), 1);
    }
}
