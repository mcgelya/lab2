#pragma once

#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

#include "array_sequence.h"
#include "list_sequence.h"

class Column : public QWidget {
    Q_OBJECT

public:
    Column(const QString& name, QWidget* parent = nullptr);

    void AddArraySequence(const QString& s, bool immutable);

    void AddListSequence(const QString& s, bool immutable);

public slots:
    void Clear();

signals:
    void AskedToAdd();

private:
    void AddArraySequence(ArraySequence<int>* seq, bool immutable);

    void AddListSequence(ListSequence<int>* seq, bool immutable);

    QScrollArea* scrollArea;
    QWidget* vectorsWidget;
    QVBoxLayout* vectorsLayout;
};
