/*
**  Copyright 2006, Alexandre Bique <bique.alexandre@gmail.com>
**
**  This ./PrefsDlg.hh is part of mononoke-notify-2.
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
** @file   PrefsDlg.hh
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sat Dec  2 22:39:43 2006
**
** @brief  Defines MononokeNotify::PrefsDlg
**
**
*/


#ifndef _MNPREFSDLG_HH_
# define _MNPREFSDLG_HH_

# include <QDialog>

class QLineEdit;
class QSpinBox;
class QListWidget;
class QComboBox;

namespace MononokeNotify {
  class PrefsDlg : public QDialog {

  Q_OBJECT

  public:
    PrefsDlg();

  private:
    void		save();
    void		load();
    QWidget *		makeUserWidget(void);
    QWidget *		makeThemeWidget(void);
    QWidget *		makeDownloadThemeWidget(void);
    QWidget *		makeAboutWidget(void);
    QLineEdit *		leUserName;
    QSpinBox *		sNbrTorrents;
    QSpinBox *		sIconSize;
    QListWidget *	lwTheme;
    QComboBox *		cbQtStyle;

  private slots:
    void		apply(void);
    void		cancel(void);
    void		ok(void);

  };
}

#endif /* !_MNPREFSDLG_HH_ */
