
/*
**  Copyright 2006, Alexandre Bique <bique.alexandre@gmail.com>
**
**  This ./MononokeXml.hh is part of mononoke-notify-2.
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
** @file   MononokeXml.hh
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sat Dec  2 22:32:49 2006
**
** @brief  The definition of MononokeNotify::MononokeXml
**
**
*/


#ifndef _MNMONONOKEXML_HH_
# define _MNMONONOKEXML_HH_

# include <QObject>
# include <QDomNode>

# include "TorrentXml.hh"

namespace MononokeNotify {

# define _MN_TORRENTLIST_MAX_ 15

  struct TorrentList {
    TorrentXml		t[_MN_TORRENTLIST_MAX_];
    int			count;
  };

  /*! @brief Parses xml from mononoke-bt */
  class MononokeXml : public QObject {

  Q_OBJECT

  public slots:
    void		parse(void);

  public:
    quint32		id;
    quint64		upload;
    quint64		download;
    quint64		download_free;
    QString		show_hentai;
    qint32		class_;
    quint32		unread;
    TorrentList		need_seed;
    TorrentList		sorties;
    TorrentList		latest;
    float		ratio;
    float		trueRatio;

  private:
    void		handleNode(QDomNode&	node);
  };
}
#endif /* !_MNMONONOKEXML_HH_ */
