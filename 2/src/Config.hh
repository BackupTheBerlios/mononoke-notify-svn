
/*
**  Copyright 2006, Alexandre Bique <bique.alexandre@gmail.com>
**
**  This ./Config.hh is part of mononoke-notify-2.
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
** @file   Config.hh
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sat Dec  2 18:55:49 2006
**
** @brief  Defines MononokeNotify::Config class
**
**
*/


#ifndef _MNCONFIG_HH_
# define _MNCONFIG_HH_

# include <QString>

namespace MononokeNotify {
  /** @brief Load configuration file */
  class Config : public QObject {

  public:
    void	init(void);
    void	checkPath(void);
    void	load(void);
    void	loadDefault(void);
    void	save(void);

    /** @brief The user's name on mononoke-bt */
    QString	userName;
    /** @brief The theme's name */
    QString	theme;
    /** The Qt's style*/
    QString	qtStyle;
    /** @brief The size of an icon in the menu, torrent item */
    int		iconSize;
    /** @brief The max number of torrents to display */
    int		nbrTorrent;
    /** @brief If we close the progress dialog when finished */
    int		progressDlgClose;
  };
}
#endif /* !_MNCONFIG_HH_ */
