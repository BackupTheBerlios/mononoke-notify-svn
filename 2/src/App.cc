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
  progressDlg = new ProgressDlg();
  prefsDlg = new PrefsDlg();
  updater.update();
}

int
main(int argc, char **argv)
{
  App app(argc, argv);

  return (app.exec());
}
