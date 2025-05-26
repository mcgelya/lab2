#include "visualize.h"

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QPushButton>

#include "utils.h"

SequenceVisualize::SequenceVisualize(QWidget* parent, bool immutable) : QWidget(parent), immutable(immutable) {
    QHBoxLayout* layout = new QHBoxLayout(this);

    scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(Qt::NoBrush);

    view = new QGraphicsView(scene, this);
    view->setAttribute(Qt::WA_TranslucentBackground);
    view->viewport()->setAttribute(Qt::WA_TranslucentBackground);
    view->viewport()->setAutoFillBackground(false);
    view->setBackgroundBrush(Qt::NoBrush);
    view->setRenderHint(QPainter::Antialiasing);
    view->setFrameShape(QFrame::NoFrame);

    QPushButton* prepend = new QPushButton("+", this);
    QPushButton* append = new QPushButton("+", this);
    if (immutable) {
        prepend->setText("🔒");
        prepend->setToolTip("Последовательность иммутабельная");
        append->setText("🔒");
        append->setToolTip("Последовательность иммутабельная");
    }

    QObject::connect(prepend, &QPushButton::clicked, this, &SequenceVisualize::AskedToPrepend);
    QObject::connect(append, &QPushButton::clicked, this, &SequenceVisualize::AskedToAppend);

    layout->addWidget(prepend);
    layout->addWidget(view);
    layout->addWidget(append);

    setLayout(layout);
}

void SequenceVisualize::Initialize(Sequence<int>* v) {
    seq = v;
    VisualizeSeq();
}

bool SequenceVisualize::AskValue(int& x) {
    bool ok = 1;
    x = QInputDialog::getInt(this, "Ввод", "Число", 1, INT_MIN, INT_MAX, 1, &ok);
    return ok;
}

void ArraySequenceVisualize::VisualizeSeq() {
    scene->clear();

    const int boxSize = 30;

    QFont font;
    font.setPointSize(10);
    QPen pen(utils::IsDarkTheme() ? Qt::white : Qt::black);
    QBrush brush(Qt::NoBrush);

    if (!immutable) {
        QPen penGray(utils::IsDarkTheme() ? Qt::darkGray : Qt::lightGray);
        for (int i = seq->GetLength(); i < seq->GetCapacity(); ++i) {
            int x = i * boxSize;
            scene->addRect(x, 0, boxSize, boxSize, penGray, brush);
        }
    }

    for (IConstEnumerator<int>* it = seq->GetConstEnumerator(); !it->IsEnd(); it->MoveNext()) {
        int x = it->Index() * boxSize;
        int value = it->ConstDereference();

        QGraphicsRectItem* rect = scene->addRect(x, 0, boxSize, boxSize, pen, brush);

        QGraphicsTextItem* text = scene->addText(QString::number(value), font);
        QRectF textRect = text->boundingRect();
        text->setPos(x + (boxSize - textRect.width()) / 2, (boxSize - textRect.height()) / 2);
    }
}

void ListSequenceVisualize::VisualizeSeq() {
    scene->clear();

    const int nodeSize = 30;
    const int spacing = 30;

    QFont font;
    font.setPointSize(10);
    QPen pen(utils::IsDarkTheme() ? Qt::white : Qt::black);
    QBrush brush(Qt::NoBrush);
    QBrush brushArrow(utils::IsDarkTheme() ? Qt::white : Qt::black);

    for (IConstEnumerator<int>* it = seq->GetConstEnumerator(); !it->IsEnd(); it->MoveNext()) {
        int i = it->Index();
        int x = i * (nodeSize + spacing);
        int value = it->ConstDereference();

        QGraphicsEllipseItem* circle = scene->addEllipse(x, 0, nodeSize, nodeSize, pen, brush);

        QGraphicsTextItem* text = scene->addText(QString::number(value), font);
        QRectF textRect = text->boundingRect();
        text->setPos(x + (nodeSize - textRect.width()) / 2, (nodeSize - textRect.height()) / 2);

        if (i + 1 < seq->GetLength()) {
            int x1 = x + nodeSize;
            int x2 = x + nodeSize + spacing;
            int y = nodeSize / 2;

            scene->addLine(x1, y, x2, y, pen);

            QPolygonF arrow;
            arrow << QPointF(x2, y) << QPointF(x2 - 6, y - 4) << QPointF(x2 - 6, y + 4);
            scene->addPolygon(arrow, pen, brushArrow);
        }
    }
}
