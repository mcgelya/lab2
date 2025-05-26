#pragma once

#include <QLayout>
#include <QWidget>

#include "sequence.h"

namespace utils {

void ClearLayout(QLayout* layout);

bool IsNumber(const QString& s);

void SplitToMutableSeq(const QString& s, Sequence<int>* res);

bool IsDarkTheme();

}  // namespace utils
