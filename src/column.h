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
    virtual void AddSeq(const QString& s) = 0;

    void Clear();

signals:
    void AskedAdd();

protected:
    QScrollArea* scrollArea;
    QWidget* vectorsWidget;
    QVBoxLayout* vectorsLayout;
};

class ColumnArray : public Column {
    Q_OBJECT

    using Column::Column;

public slots:
    void AddSeq(const QString& s) override;
};

class ColumnList : public Column {
    Q_OBJECT

    using Column::Column;

public slots:
    void AddSeq(const QString& s) override;
};
