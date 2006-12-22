
/*
**  Copyright 2006, Alexandre Bique <bique.alexandre@gmail.com>
**
**  This ./TrayMenuActionFrame.hh is part of mononoke-notify-2.
**
**  mononoke-notify-2 is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation; either version 2 of the License, or
**  (at your option) any later version.
**
**  mononoke-notify-2 is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with mononoke-notify-2; if not, write to the Free Software
**  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
**
*/

/*!
** @file   TrayMenuActionFrame.hh
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sat Dec  2 22:54:23 2006
**
** @brief  Defines MononokeNotify::TrayMenuActionFrame
**
**
*/


#ifndef _MNTRAYMENUACTIONFRAME_HH_
# define _MNTRAYMENUACTIONFRAME_HH_

# include <QFrame>

namespace MononokeNotify {
  class TrayMenuActionFrame : public QFrame {

  public:
    TrayMenuActionFrame();
    void	enterEvent(QEvent*	event);
    void	leaveEvent(QEvent*	event);

  };
}

#endif /* !_MNTRAYMENUACTIONFRAME_HH_ */
