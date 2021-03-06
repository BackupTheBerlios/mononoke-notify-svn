
/*
**  Copyright 2006, Alexandre Bique <bique.alexandre@gmail.com>
**
**  This ./App.cc is part of mononoke-notify-2.
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
** @file   App.cc
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sat Dec  2 15:51:38 2006
**
** @brief  The implementation of MononokeNotify::App
**
**
*/


#include <QtDebug>

#include "App.hh"
#include "Config.hh"
#include "TrayMenu.hh"
#include "Updater.hh"
#include "PrefsDlg.hh"
#include "ProgressDlg.hh"

using namespace MononokeNotify;

App::App(int argc, char **argv)
  :QApplication(argc, argv)
{
  config.init();
  config.load();
  trayMenu = new TrayMenu();
  trayIcon.setContextMenu(trayMenu);
  prefsDlg = new PrefsDlg();
  progressDlg = new ProgressDlg();
  updater.update();
}

int
main(int argc, char **argv)
{
  App app(argc, argv);

  return (app.exec());
}
