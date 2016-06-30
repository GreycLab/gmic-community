/** -*- mode: c++ ; c-basic-offset: 2 -*-
 * @file   FullScreenWidget.cpp
 * @author Sebastien Fourey
 * @date   July 2010
 * @brief  Declaration of the class FullScreenWidget
 *
 * This file is part of the ZArt software's source code.
 *
 * Copyright Sebastien Fourey / GREYC Ensicaen (2010-...)
 *
 *                    https://foureys.users.greyc.fr/
 *
 * This software is a computer program whose purpose is to demonstrate
 * the possibilities of the GMIC image processing language by offering the
 * choice of several manipulations on a video stream aquired from a webcam. In
 * other words, ZArt is a GUI for G'MIC real-time manipulations on the output
 * of a webcam.
 *
 * This software is governed by the CeCILL  license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info". See also the directory "Licence" which comes
 * with this source code for the full text of the CeCILL license.
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and,  more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 */
#include <iostream>
#include "FullScreenWidget.h"
#include "ImageView.h"
#include <QKeyEvent>
#include <QCloseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "MainWindow.h"

FullScreenWidget::FullScreenWidget(MainWindow * mainwindow)
  : QWidget(0),
    _mainWindow(mainwindow)
{
  setupUi(this);

#if QT_VERSION >= 0x040600
  _tbFoldRightPanel->setIcon(QIcon::fromTheme("window-close"));
#else
  _tbFoldRightPanel->setText("Hide >>");
#endif
  connect(_tbFoldRightPanel,SIGNAL(clicked()),
          _rightFrame, SLOT(hide()));
  connect(_tbFoldRightPanel,SIGNAL(clicked()),
          _imageView, SLOT(setFocus()));
  connect(_imageView, SIGNAL(escapePressed()),
          this, SIGNAL(escapePressed()));
  connect(_imageView, SIGNAL(spaceBarPressed()),
          this, SIGNAL(spaceBarPressed()));
  connect(_imageView, SIGNAL(mousePress(QMouseEvent *)),
          _mainWindow, SLOT(imageViewMouseEvent(QMouseEvent *)));
  connect(_imageView, SIGNAL(mouseMove(QMouseEvent *)),
          _mainWindow, SLOT(imageViewMouseEvent(QMouseEvent *)));
  _imageView->setMouseTracking(true);
  _imageView->setBackgroundColor(Qt::black);
  setMouseTracking(true);
  _rightFrame->setVisible(false);
  _splitter->setChildrenCollapsible(false);
  layout()->setContentsMargins(0,0,0,0);
  _imageView->installEventFilter(this);
}

FullScreenWidget::~FullScreenWidget()
{

}

void
FullScreenWidget::keyPressEvent(QKeyEvent * e)
{
  if (e->key() == Qt::Key_Escape || e->key() == Qt::Key_F5) {
    emit escapePressed();
    e->accept();
  }
  if (e->key() == Qt::Key_Space && !_rightFrame->isVisible()) {
    emit spaceBarPressed();
    e->accept();
  }
}

bool
FullScreenWidget::eventFilter(QObject * , QEvent * event)
{
  if (_rightFrame->isVisible() ||(event->type() != QEvent::MouseMove)) return false;
  if (dynamic_cast<QMouseEvent*>(event)->x() == width() - 1) {
    _rightFrame->setVisible(true);
    return true;
  } else {
    return false;
  }
}

ImageView *
FullScreenWidget::imageView()
{
  return _imageView;
}

QTreeWidget *
FullScreenWidget::treeWidget()
{
  return _treePresetsFullScreen;
}

CommandParamsWidget *
FullScreenWidget::commandParamsWidget()
{
  return _commandParamsWidget;
}

void
FullScreenWidget::setFavesModel(QAbstractItemModel * model)
{
  _cbFaves->setModel(model);
}

QComboBox *
FullScreenWidget::cbFaves()
{
  return _cbFaves;
}

void
FullScreenWidget::showEvent(QShowEvent *)
{
  _imageView->setFocus();
}
