#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>

class Column : public QWidget {
    Q_OBJECT

public:
    Column(QWidget* parent = nullptr);

public slots:
    void AddArraySequence(const QString& s);

    void AddListSequence(const QString& s);

    void Clear();

signals:
    void AskedToAdd();

protected:
    QScrollArea* scrollArea;
    QWidget* vectorsWidget;
    QVBoxLayout* vectorsLayout;
};
