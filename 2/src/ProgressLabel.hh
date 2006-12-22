
/*
**  Copyright 2006, Alexandre Bique <bique.alexandre@gmail.com>
**
**  This ./ProgressLabel.hh is part of mononoke-notify-2.
**
**  Foobar is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation; either version 2 of the License, or
**  (at your option) any later version.
**
**  Foobar is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with Foobar; if not, write to the Free Software
**  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
**
*/

/*!
** @file   ProgressLabel.hh
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sat Dec  2 22:40:55 2006
**
** @brief  Defines MononokeNotify::ProgressLabel
**
**
*/


#ifndef _PROGRESSLABEL_HH_
# define _PROGRESSLABEL_HH_

# include <QLabel>

namespace MononokeNotify {
  class ProgressLabel : public QLabel {

  Q_OBJECT

  public:
    ProgressLabel();

  public slots:
    void	update(int	current,
		       int	total);

  };
}

#endif /* !_PROGRESSLABEL_HH_ */
