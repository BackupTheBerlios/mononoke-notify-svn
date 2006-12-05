#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QDir>
#include <QDesktopServices>

#include "App.hh"
#include "TrayMenuAction.hh"
#include "TrayMenuActionFrame.hh"

using namespace MononokeNotify;

TrayMenuAction::TrayMenuAction(QDomElement & elem, TorrentXml & t)
: QWidgetAction(0)
{
   widget = new TrayMenuActionFrame();
   QDomElement child = elem.firstChildElement();
   QHBoxLayout *h = new QHBoxLayout();

   url = QUrl("http://mononoke-bt.org/gettorrent.php/"
              + t.filename + "?id=" + QString::number(t.id) + "&r=1");

   h->setSpacing(2);
   h->setMargin(2);

   while (!child.isNull()) {
      if (child.nodeName() == "Text") {
         h->addWidget(new QLabel(child.attribute("val")));
      } else if (child.nodeName() == "TeamIcon") {
         QString filename = QDir::homePath()
            + "/.config/mononoke-notify-2/data/team_" + QString::number(t.team)
            + ".jpg";
         QLabel *l = new QLabel();

         l->setPixmap(QPixmap(filename).scaled(mn_config.iconSize,
                                               mn_config.iconSize));
         h->addWidget(l);
      } else if (child.nodeName() == "AnimeIcon") {
         QString filename = QDir::homePath()
            + "/.config/mononoke-notify-2/data/anime_" + QString::number(t.category)
            + ".jpg";
         QLabel *l = new QLabel();

         l->setPixmap(QPixmap(filename).scaled(mn_config.iconSize,
                                               mn_config.iconSize));
         h->addWidget(l);
      } else if (child.nodeName() == "MainGenreIcon") {
         if (t.main_genre != 0) {
            QString filename = QDir::homePath()
               + "/.config/mononoke-notify-2/data/genre_"
               + QString::number(t.main_genre)
               + ".jpg";
            QLabel *l = new QLabel();

            l->setPixmap(QPixmap(filename).scaled(mn_config.iconSize,
                                                  mn_config.iconSize));
            h->addWidget(l);
         }
      } else if (child.nodeName() == "PackageIcon") {
         QString filename = QDir::homePath()
            + "/.config/mononoke-notify-2/themes/default/"
            + child.attribute("src" + QString::number(t.free_download));
         QLabel *l = new QLabel();

         l->setPixmap(QPixmap(filename).scaled(mn_config.iconSize,
                                               mn_config.iconSize));
         h->addWidget(l);
      } else if (child.nodeName() == "Id") {
         h->addWidget(new QLabel(QString::number(t.id)));
      } else if (child.nodeName() == "NbrLeech") {
         h->addWidget(new QLabel(QString::number(t.leechers)));
      } else if (child.nodeName() == "NbrSeed") {
         h->addWidget(new QLabel(QString::number(t.seeders)));
      } else if (child.nodeName() == "Name") {
         h->addWidget(new QLabel(t.name));
      } else if (child.nodeName() == "Team") {
         h->addWidget(new QLabel(QString::number(t.team)));
      } else if (child.nodeName() == "FileName") {
         h->addWidget(new QLabel(t.filename));
      } else if (child.nodeName() == "SeedRatio") {
         h->addWidget(new QLabel(QString::number(t.seedratio)));
      } else if (child.nodeName() == "FreeDownload") {
         h->addWidget(new QLabel(QString::number(t.free_download)));
      } else if (child.nodeName() == "Category") {
         h->addWidget(new QLabel(QString::number(t.category)));
      } else if (child.nodeName() == "TimesCompleted") {
         h->addWidget(new QLabel(QString::number(t.times_completed)));
      } else if (child.nodeName() == "Size") {
         h->addWidget(new QLabel(QString::number((double) t.size / 1024 / 1024)
                                 + " Mo"));
      } else if (child.nodeName() == "Added") {
         h->addWidget(new QLabel(t.added));
      } else if (child.nodeName() == "NumFiles") {
         h->addWidget(new QLabel(QString::number(t.numfiles)));
      } else if (child.nodeName() == "Rating") {
         h->addWidget(new QLabel(QString::number(t.rating)));
      } else if (child.nodeName() == "CatName") {
         h->addWidget(new QLabel(t.cat_name));
      } else if (child.nodeName() == "IsHentai") {
         if (t.is_hentai)
            h->addWidget(new QLabel("hentai"));
      } else if (child.nodeName() == "MainGenre") {
         h->addWidget(new QLabel(QString::number(t.main_genre)));
      } else if (child.nodeName() == "TeamName") {
         h->addWidget(new QLabel(t.team_name));
      }
      child = child.nextSiblingElement();
   }
   h->addStretch(100);
   widget->setLayout(h);
   connect(this, SIGNAL(triggered()), this, SLOT(clicked()));
}

QWidget *
TrayMenuAction::createWidget(QWidget * parent)
{
   widget->setParent(parent);
   return widget;
}

void
   TrayMenuAction::clicked(void)
{
   QDesktopServices::openUrl(url);
}
