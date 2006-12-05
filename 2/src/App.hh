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
# include "PrefsDlg.hh"
# include "ProgressDlg.hh"
# include "MononokeXml.hh"
# include "TrayMenu.hh"
# include "Updater.hh"

namespace MononokeNotify {
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

#endif /* !_MNAPP_H_ */
