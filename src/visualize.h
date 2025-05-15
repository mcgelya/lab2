#pragma once

#include <QWidget>
#include <QGraphicsView>
#include "array_sequence.h"
#include "list_sequence.h"

class SequenceVisualize : public QWidget {
    Q_OBJECT

public:
    SequenceVisualize(QWidget* parent = nullptr);

    virtual void VisualizeSeq() = 0;

public slots:
    virtual void Prepend() = 0;

    virtual void Append() = 0;

protected:
    QGraphicsScene* scene;
    QGraphicsView* view;
};

class ArraySequenceVisualize : public SequenceVisualize {
    Q_OBJECT

    using SequenceVisualize::SequenceVisualize;

public:
    void Initialize(ArraySequence<int>* v);

    void VisualizeSeq() override;

public slots:
    void Prepend() override;

    void Append() override;

private:
    ArraySequence<int>* seq;
};

class ListSequenceVisualize : public SequenceVisualize {
    Q_OBJECT

    using SequenceVisualize::SequenceVisualize;

public:
    void Initialize(ListSequence<int>* v);

    void VisualizeSeq() override;

public slots:
    void Prepend() override;

    void Append() override;

private:
    ListSequence<int>* seq;
};
