#include "ProgressLabel.hh"

using namespace MononokeNotify;

ProgressLabel::ProgressLabel()
    :QLabel()
{
    setText("0%");
}

void
ProgressLabel::update(int current, int total)
{
    if (total == 0)
	setText("100%");
    setText(QString::number((double) (current * 100) / total, 'f', 0) + "%");
}
