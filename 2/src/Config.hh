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
    /** @brief The size of an icon in the menu, torrent item */
    int		iconSize;
    /** @brief The max number of torrents to display */
    int		nbrTorrent;
    /** @brief If we close the progress dialog when finished */
    int		progressDlgClose;
  };
}
#endif /* !_MNCONFIG_HH_ */
