#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QFrame>
#include <QIcon>
#include <QMessageBox>
#include "column.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QWidget* window = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* columnLayout = new QHBoxLayout();

    Column* arrayColumn = new ColumnArray();
    Column* listColumn = new ColumnList();

    columnLayout->addWidget(arrayColumn);
    columnLayout->addWidget(listColumn);

    QLineEdit* input = new QLineEdit();
    input->setPlaceholderText("Введите последовательность...");

    QObject::connect(arrayColumn, &ColumnArray::AskedAdd, [=]() {
        try {
            arrayColumn->AddSeq(input->text());
        } catch (const std::runtime_error& e) {
            QMessageBox::critical(window, "Ошибка", "Введенные данные некорректны!\nПожалуйста, попробуйте снова.",
                                  QMessageBox::Ok);
        }
        input->clear();
    });

    QObject::connect(listColumn, &ColumnList::AskedAdd, [=]() {
        try {
            listColumn->AddSeq(input->text());
        } catch (const std::runtime_error& e) {
            QMessageBox::critical(window, "Ошибка", "Введенные данные некорректны!\nПожалуйста, попробуйте снова.",
                                  QMessageBox::Ok);
        }
        input->clear();
    });

    mainLayout->addLayout(columnLayout);
    mainLayout->addWidget(input);

    window->setLayout(mainLayout);
    window->setWindowTitle("Визуализация АТД");
    window->resize(900, 900);
    window->show();

    return app.exec();
}
