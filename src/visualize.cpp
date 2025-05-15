#include "visualize.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGuiApplication>
#include <QStyleHints>

SequenceVisualize::SequenceVisualize(QWidget* parent) : QWidget(parent) {
    QHBoxLayout* layout = new QHBoxLayout(this);
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setFrameShape(QFrame::NoFrame);
    view->setFixedHeight(32);

    QPushButton* prepend = new QPushButton("+", this);
    prepend->setObjectName("prepend");
    QPushButton* append = new QPushButton("+", this);
    append->setObjectName("append");

    QObject::connect(prepend, &QPushButton::clicked, this, &SequenceVisualize::Prepend);
    QObject::connect(append, &QPushButton::clicked, this, &SequenceVisualize::Append);

    layout->addWidget(prepend);
    layout->addWidget(view);
    layout->addWidget(append);

    setLayout(layout);
}

void ArraySequenceVisualize::Initialize(ArraySequence<int>* v) {
    seq = v;
    VisualizeSeq();
}

bool IsDarkTheme() {
    return QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark;
}

void ArraySequenceVisualize::VisualizeSeq() {
    scene->clear();

    constexpr int boxSize = 30;
    constexpr int startY = 1;

    QFont font;
    font.setPointSize(10);
    QPen pen(IsDarkTheme() ? Qt::white : Qt::black);
    QBrush brush(Qt::NoBrush);

    int i = 0;
    for (int v : *seq) {
        int x = i * boxSize;

        QGraphicsRectItem* rect = scene->addRect(x, 0, boxSize, boxSize, pen, brush);

        QGraphicsTextItem* text = scene->addText(QString::number(v), font);
        QRectF textRect = text->boundingRect();
        text->setPos(x + (boxSize - textRect.width()) / 2, startY + (boxSize - textRect.height()) / 2);
        ++i;
    }

    int totalWidth = i * boxSize;
    scene->setSceneRect(0, 0, totalWidth, boxSize + 2);
}

void ArraySequenceVisualize::Prepend() {
    bool ok = 1;
    int x = QInputDialog::getInt(this, "Ввод", "Число", 1, INT_MIN, INT_MAX, 1, &ok);
    if (ok) {
        seq->Prepend(x);
        VisualizeSeq();
    }
}

void ArraySequenceVisualize::Append() {
    bool ok = 1;
    int x = QInputDialog::getInt(this, "Ввод", "Число", 1, INT_MIN, INT_MAX, 1, &ok);
    if (ok) {
        seq->Append(x);
        VisualizeSeq();
    }
}

void ListSequenceVisualize::Initialize(ListSequence<int>* v) {
    seq = v;
    VisualizeSeq();
}

void ListSequenceVisualize::VisualizeSeq() {
    scene->clear();

    const int nodeSize = 30;
    const int spacing = 30;
    const int startY = 1;

    QFont font;
    font.setPointSize(10);
    QPen pen(IsDarkTheme() ? Qt::white : Qt::black);
    QBrush brush(Qt::NoBrush);
    QBrush brushArrow(IsDarkTheme() ? Qt::white : Qt::black);

    int i = 0;
    for (int v : *seq) {
        int x = i * (nodeSize + spacing);
        QGraphicsEllipseItem* circle = scene->addEllipse(x, startY, nodeSize, nodeSize, pen, brush);

        QGraphicsTextItem* text = scene->addText(QString::number(v), font);
        QRectF textRect = text->boundingRect();
        text->setPos(x + (nodeSize - textRect.width()) / 2, startY + (nodeSize - textRect.height()) / 2);

        if (i + 1 < seq->GetLength()) {
            int x1 = x + nodeSize;
            int x2 = x + nodeSize + spacing;
            int y = startY + nodeSize / 2;

            scene->addLine(x1, y, x2, y, pen);

            QPolygonF arrow;
            arrow << QPointF(x2, y) << QPointF(x2 - 6, y - 4) << QPointF(x2 - 6, y + 4);
            scene->addPolygon(arrow, pen, brushArrow);
        }
        ++i;
    }

    int totalWidth = i * (nodeSize + spacing);
    scene->setSceneRect(0, 0, totalWidth + 20, nodeSize + 2);
}

void ListSequenceVisualize::Prepend() {
    bool ok = 1;
    int x = QInputDialog::getInt(this, "Ввод", "Число", 1, INT_MIN, INT_MAX, 1, &ok);
    if (ok) {
        seq->Prepend(x);
        VisualizeSeq();
    }
}

void ListSequenceVisualize::Append() {
    bool ok = 1;
    int x = QInputDialog::getInt(this, "Ввод", "Число", 1, INT_MIN, INT_MAX, 1, &ok);
    if (ok) {
        seq->Append(x);
        VisualizeSeq();
    }
}
