/*!
** @file   ProgressDlg.cc
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sun Dec 10 21:41:39 2006
**
** @brief  Implementation of MononokeNotify::ProgressDlg
**
**
*/

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QScrollArea>
#include <QProgressBar>
#include <QHttp>

#include "App.hh"
#include "ProgressDlg.hh"
#include "ProgressLabel.hh"
#include "HttpDownloader.hh"

using namespace MononokeNotify;

ProgressDlg::ProgressDlg()
  : QDialog()
{
  QVBoxLayout * v = new QVBoxLayout();
  QLabel * title = new QLabel("Mise a jour...");

  title->setAlignment(Qt::AlignCenter);
  QScrollArea * area = new QScrollArea();
  QWidget * w = new QWidget();

  grid = new QGridLayout();
  grid->setColumnStretch(1, 100);
  w->setLayout(grid);
  area->setWidget(w);
  area->setWidgetResizable(1);
  QHBoxLayout * h = new QHBoxLayout();
  QCheckBox * cb = new QCheckBox("Fermer automatiquement");

  cb->setCheckState((Qt::CheckState) mn_config.progressDlgClose);
  QPushButton * bt = new QPushButton("Fermer");

  connect(bt, SIGNAL(clicked()), this, SLOT(hide()));
  connect(cb, SIGNAL(stateChanged(int)), this, SLOT(checkBoxClicked(int)));

  h->addWidget(cb);
  h->addStretch(100);
  h->addWidget(bt);
  v->addWidget(title);
  v->addWidget(area);
  v->addLayout(h);
  setLayout(v);

  setMinimumSize(400, 200);
}

void
ProgressDlg::monitorDownload(HttpDownloader * dl)
{
  QLabel * file = new QLabel(dl->name);

  file->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
  grid->addWidget(file, grid->rowCount(), 1);
  ProgressLabel * label = new ProgressLabel();

  label->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
  grid->addWidget(label, grid->rowCount() - 1, 0);
  connect(dl->http, SIGNAL(dataReadProgress(int, int)),
	  label, SLOT(update(int, int)));
}

void
ProgressDlg::checkBoxClicked(int state)
{
  mn_config.progressDlgClose = state;
  mn_config.save();
}

void
ProgressDlg::canHide(void)
{
  if (mn_config.progressDlgClose == 2)
    hide();
}
