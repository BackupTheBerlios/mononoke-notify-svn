
/*
**  Copyright 2006, Alexandre Bique <bique.alexandre@gmail.com>
**
**  This ./TrayMenu.hh is part of mononoke-notify-2.
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
** @file   TrayMenu.hh
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sat Dec  2 22:44:20 2006
**
** @brief  Defines MononokeNotify::TrayMenu
**
**
*/


#ifndef _MNTRAYMENU_HH_
# define _MNTRAYMENU_HH_

# include <QMenu>
# include <QDomElement>

# include "MononokeXml.hh"

namespace MononokeNotify {
  /** @brief The menu displayed when the user right click */
  class TrayMenu : public QMenu {

  Q_OBJECT

  public:
    TrayMenu(void);

    void	generate(void);

  private:
    void	appendSepparator(void);
    void	parse(QString  &		filename);
    void	handleTrayIcon(QDomElement &	elem);
    void	handleTrayMenu(QDomElement &	elem);
    void	handleItem(QDomElement &	elem);
    QMenu*	handleTorrentList(QDomElement	elem,
				  TorrentList &	tl);

  private slots:
    void	mononoke(void);
    void	newMessage(void);
    void	update(void);
  };
}

#endif /* !_MNTRAYMENU_HH_ */
