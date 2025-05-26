#pragma once

#include <QGraphicsView>
#include <QWidget>

#include "sequence.h"

class SequenceVisualize : public QWidget {
    Q_OBJECT

public:
    SequenceVisualize(QWidget* parent = nullptr, bool immutable = false);

    void Initialize(Sequence<int>* seq);

    virtual void VisualizeSeq() = 0;

    bool AskValue(int& x);

signals:
    void AskedToPrepend();

    void AskedToAppend();

protected:
    QGraphicsScene* scene;
    QGraphicsView* view;

    Sequence<int>* seq;
    const bool immutable;
};

class ArraySequenceVisualize : public SequenceVisualize {
    Q_OBJECT

    using SequenceVisualize::SequenceVisualize;

public:
    void VisualizeSeq() override;
};

class ListSequenceVisualize : public SequenceVisualize {
    Q_OBJECT

    using SequenceVisualize::SequenceVisualize;

public:
    void VisualizeSeq() override;
};
