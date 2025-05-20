#pragma once

#include <QLayout>
#include <QWidget>

#include "sequence.h"

void ClearLayout(QLayout* layout);

bool IsNumber(const QString& s);

void SplitToSeq(const QString& s, Sequence<int>* res);

bool IsDarkTheme();

template <class T>
QDebug operator<<(QDebug dbg, const T& obj) {
    std::ostringstream oss;
    oss << obj;
    dbg << QString::fromStdString(oss.str());
    return dbg;
}
