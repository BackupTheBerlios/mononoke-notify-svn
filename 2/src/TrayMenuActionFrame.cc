#include <QtDebug>

#include "TrayMenuActionFrame.hh"

using namespace MononokeNotify;

TrayMenuActionFrame::TrayMenuActionFrame()
: QFrame()
{
}

void
   TrayMenuActionFrame::enterEvent(QEvent * event)
{
   setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
}

void
   TrayMenuActionFrame::leaveEvent(QEvent * event)
{
   setFrameStyle(0);
}
