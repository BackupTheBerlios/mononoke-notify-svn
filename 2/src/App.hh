
/*
**  Copyright 2006, Alexandre Bique <bique.alexandre@gmail.com>
**
**  This ./App.hh is part of mononoke-notify-2.
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
** @file   App.hh
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sat Dec  2 16:50:32 2006
**
** @brief  Defines MononokeNotify::App class
**
**
*/

#ifndef _MNAPP_HH_
# define _MNAPP_HH_

# include <QApplication>
# include <QSystemTrayIcon>

# include "Config.hh"
# include "MononokeXml.hh"
# include "Updater.hh"

/** @brief contains all mononoke-notify classes */
namespace MononokeNotify {

  class TrayMenu;
  class PrefsDlg;
  class ProgressDlg;

  /** @brief The application */
  class App : public QApplication {

  Q_OBJECT

  public:
    App(int argc, char **argv);

    QSystemTrayIcon	trayIcon;
    PrefsDlg *		prefsDlg;
    ProgressDlg *	progressDlg;
    TrayMenu *		trayMenu;
    Config		config;
    MononokeXml		mnXml;
    Updater		updater;
  };
}

# define mn_xml ((App *)qApp)->mnXml
# define mn_config ((App *)qApp)->config
# define mn_prefs ((App *)qApp)->prefsDlg
# define mn_progress ((App *)qApp)->progressDlg
# define mn_updater ((App *)qApp)->updater
# define mn_menu ((App *)qApp)->trayMenu
# define mn_tray_icon ((App *)qApp)->trayIcon

#endif /* !_MNAPP_H_ */
