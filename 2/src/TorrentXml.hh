
/*
**  Copyright 2006, Alexandre Bique <bique.alexandre@gmail.com>
**
**  This ./TorrentXml.hh is part of mononoke-notify-2.
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
** @file   TorrentXml.hh
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sat Dec  2 22:43:38 2006
**
** @brief  Defines MononokeNotify::TorrentXml
**
**
*/


#ifndef _MNTORRENTXML_HH_
# define _MNTORRENTXML_HH_

# include <QObject>
# include <QDomNode>

namespace MononokeNotify {
  class TorrentXml : public QObject {

  public:
    void	parse(QDomNode &	node);

    quint32	id;
    quint32	leechers;
    quint32	seeders;
    QString	name;
    quint32	team;
    QString	filename;
    float	seedratio;
    quint32	free_download;
    quint32	category;
    quint32	times_completed;
    quint64	size;
    QString	added;
    quint32	numfiles;
    float	rating;
    QString	cat_name;
    bool	is_hentai;
    quint32	main_genre;
    QString	team_name;

  private:
    void	handleNode(QDomNode	node);

  };
}

#endif /* !_MNTORRENTXML_HH_ */
