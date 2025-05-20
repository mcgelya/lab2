#include <QApplication>
#include <QFrame>
#include <QIcon>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QWidget>

#include "column.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QWidget* window = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* columnLayout = new QHBoxLayout();

    Column* arrayColumn = new Column("массив");
    Column* listColumn = new Column("список");

    columnLayout->addWidget(arrayColumn);
    columnLayout->addWidget(listColumn);

    QLineEdit* input = new QLineEdit();
    input->setPlaceholderText("Введите последовательность...");

    QObject::connect(arrayColumn, &Column::AskedToAdd, [=]() {
        try {
            arrayColumn->AddArraySequence(input->text());
        } catch (const std::runtime_error& e) {
            QMessageBox::critical(window, "Ошибка",
                                  "Вы ввели не числа или число слишком большое.\nПожалуйста, попробуйте снова.",
                                  QMessageBox::Ok);
        }
        input->clear();
    });

    QObject::connect(listColumn, &Column::AskedToAdd, [=]() {
        try {
            listColumn->AddListSequence(input->text());
        } catch (const std::runtime_error& e) {
            QMessageBox::critical(window, "Ошибка",
                                  "Вы ввели не числа или число слишком большое.\nПожалуйста, попробуйте снова.",
                                  QMessageBox::Ok);
        }
        input->clear();
    });

    mainLayout->addLayout(columnLayout);
    mainLayout->addWidget(input);

    window->setLayout(mainLayout);
    window->setWindowTitle("Визуализация АТД");
    window->setWindowState(Qt::WindowMaximized);
    window->show();

    return app.exec();
}
