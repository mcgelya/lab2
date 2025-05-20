#pragma once

#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

class Column : public QWidget {
    Q_OBJECT

public:
    Column(const QString& name, QWidget* parent = nullptr);

    void AddArraySequence(const QString& s);

    void AddListSequence(const QString& s);

public slots:
    void Clear();

signals:
    void AskedToAdd();

protected:
    QScrollArea* scrollArea;
    QWidget* vectorsWidget;
    QVBoxLayout* vectorsLayout;
};
