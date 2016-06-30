/** -*- mode: c++ ; c-basic-offset: 2 -*-
 * @file   OutputWindow.cpp
 * @author Sebastien Fourey
 * @date   Nov 2015
 * @brief  Declaration of the class OutputWindow
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
#include "OutputWindow.h"
#include "ImageView.h"
#include <QKeyEvent>
#include <QCloseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include "MainWindow.h"

OutputWindow::OutputWindow(MainWindow * mainwindow)
  : QWidget(0),
    _ui(new Ui::OutputWindow),
    _mainWindow(mainwindow)
{
  _ui->setupUi(this);

  _fullScreenAction = new QAction(this);
  _fullScreenAction->setCheckable(true);
  _ui->_tbFullScreen->setDefaultAction(_fullScreenAction);
#if QT_VERSION >= 0x040600
  _fullScreenAction->setIcon(QIcon::fromTheme("view-fullscreen"));
#else
  _fullScreenAction->setText("Fullscreen");
  _ui->_tbFullScreen->setToolButtonStyle(Qt::ToolButtonTextOnly);
#endif
  _ui->_pbClose->setCheckable(false);
  connect(_fullScreenAction, SIGNAL(toggled(bool)),
          this, SLOT(onShowFullscreen(bool)));
  connect(_ui->_pbClose, SIGNAL(clicked(bool)),
          this, SLOT(onCloseClicked()));
  connect(_ui->_imageView, SIGNAL(escapePressed()),
          this, SIGNAL(escapePressed()));
  connect(_ui->_imageView, SIGNAL(spaceBarPressed()),
          this, SIGNAL(spaceBarPressed()));
  connect(_ui->_imageView, SIGNAL(mousePress(QMouseEvent *)),
          _mainWindow, SLOT(imageViewMouseEvent(QMouseEvent *)));
  connect(_ui->_imageView, SIGNAL(mouseMove(QMouseEvent *)),
          _mainWindow, SLOT(imageViewMouseEvent(QMouseEvent *)));
  connect(_ui->_imageView, SIGNAL(mouseDoubleClick(QMouseEvent*)),
          this, SLOT(toggleFullScreen()));
  _ui->_imageView->setMouseTracking(true);
  setMouseTracking(true);
  layout()->setContentsMargins(1,0,1,0);
}

OutputWindow::~OutputWindow()
{
  delete _ui;
}

void
OutputWindow::keyPressEvent(QKeyEvent * e)
{    
  if (isFullScreen() && (e->key() == Qt::Key_Escape || e->key() == Qt::Key_F5)) {
    onShowFullscreen(false);
    emit escapePressed();
    e->accept();
  }
  if (e->key() == Qt::Key_Space) {
    emit spaceBarPressed();
    e->accept();
  }
}

void
OutputWindow::closeEvent(QCloseEvent * e)
{
  emit aboutToClose();
  e->accept();
}

void
OutputWindow::onCloseClicked()
{
  close();
}

void
OutputWindow::onShowFullscreen(bool on)
{
  if (on) {
    QPalette p = palette();
    p.setColor(QPalette::Window,Qt::black);
    setPalette(p);
    _ui->_buttonsFrame->hide();
    showFullScreen();
    setFocus();
    _fullScreenAction->setChecked(true);
  } else {
    setPalette(QPalette());
    _ui->_buttonsFrame->show();
    _ui->_pbClose->show();
    _fullScreenAction->setChecked(false);
    showNormal();
  }
}

void
OutputWindow::toggleFullScreen()
{
  _fullScreenAction->setChecked(!isFullScreen());
}

ImageView *
OutputWindow::imageView()
{
  return _ui->_imageView;
}

void
OutputWindow::showEvent(QShowEvent *)
{
  _ui->_imageView->setFocus();
}

