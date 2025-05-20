#pragma once

#include <QWidget>
#include <QGraphicsView>
#include "sequence.h"

class SequenceVisualize : public QWidget {
    Q_OBJECT

public:
    SequenceVisualize(QWidget* parent = nullptr);

    void Initialize(Sequence<int>* seq);

    virtual void VisualizeSeq() = 0;

public slots:
    void Prepend();

    void Append();

protected:
    QGraphicsScene* scene;
    QGraphicsView* view;

    Sequence<int>* seq;
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
