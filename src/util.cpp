#include "util.h"

#include <QGuiApplication>
#include <QStyleHints>
#include <stdexcept>

void ClearLayout(QLayout* layout) {
    if (layout == nullptr) {
        return;
    }
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (QWidget* w = item->widget()) {
            w->deleteLater();
        }
        if (QLayout* childLayout = item->layout()) {
            ClearLayout(childLayout);
        }
        delete item;
    }
}

bool IsNumber(const QString& s) {
    if (s.isEmpty()) {
        return false;
    }
    if (s.size() == 1 && s[0] == '-') {
        return false;
    }
    for (int i = (s[0] == '-' ? 1 : 0); i < s.size(); ++i) {
        if (!s[i].isDigit()) {
            return false;
        }
    }
    return true;
}

void SplitToSeq(const QString& line, Sequence<int>* res) {
    QStringList input = line.split(' ', Qt::SkipEmptyParts);
    for (const QString& s : input) {
        if (!IsNumber(s)) {
            throw std::invalid_argument("Input is not an integer: " + s.toStdString());
        }
        bool ok = 1;
        int val = s.toInt(&ok);
        if (!ok) {
            throw std::out_of_range("Number is too big for int: " + s.toStdString());
        }
        res->Append(val);
    }
}

bool IsDarkTheme() {
    return QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark;
}
