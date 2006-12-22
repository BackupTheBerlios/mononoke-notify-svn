
/*
**  Copyright 2006, Alexandre Bique <bique.alexandre@gmail.com>
**
**  This ./Updater.hh is part of mononoke-notify-2.
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
** @file   Updater.hh
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sat Dec  2 22:55:19 2006
**
** @brief  Defines MononokeNotify::Updater
**
**
*/


#ifndef _MNUPDATER_HH_
# define _MNUPDATER_HH_

# include <QObject>
# include <QString>
# include <QDomElement>

namespace MononokeNotify {
  class Updater : QObject {

  Q_OBJECT

  public:
    Updater();
    void	update(void);
    void	downloadIcon(QString&		url,
			     QString&		filename);
    void	downloadTeamIcon(qint32		id);
    void	downloadAnimeIcon(qint32	id);
    void	downloadGenreIcon(qint32	id);

    quint32 count;

  public slots:
    void	checkTheme(void);
    void	tryUpdateMenu(void);

  private:
    void	checkThemeFiles(QDomElement&	elem,
				QString&	base);
    void	downloadDefaultTheme(void);
    void	downloadUserInfoXml(void);
    void	unexistantTheme(void);
  };
}

#endif /* !_MNUPDATER_HH_ */
