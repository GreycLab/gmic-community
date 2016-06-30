/** -*- mode: c++ ; c-basic-offset: 2 -*-
 * @file   FilterThread.cpp
 * @author Sebastien Fourey
 * @date   July 2010
 * @brief Definition of the methods of the class FilterThread.
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
#include "FilterThread.h"
#include "ImageConverter.h"
#include "WebcamSource.h"
#include <QApplication>
#include <QColor>
#include <QFont>
#include <QFontMetrics>
#include <QMutex>
#include <QPainter>
#include <QImage>
#include <QTime>
#include <QSemaphore>
#include <iostream>
using namespace cimg_library;

FilterThread::FilterThread(ImageSource & imageSource,
                           const QString & command,
                           QImage * outputImageA,
                           QMutex * imageMutexA,
                           QImage * outputImageB,
                           QMutex * imageMutexB,
                           PreviewMode previewMode,
                           int frameSkip,
                           int fps,
                           QSemaphore * blockingSemaphore)
  : _imageSource(imageSource),
    _arguments(new QString("")),
    _commandUpdated(true),
    _outputImageA(outputImageA),
    _imageMutexA(imageMutexA),
    _outputImageB(outputImageB),
    _imageMutexB(imageMutexB),
    _blockingSemaphore(blockingSemaphore),
    _previewMode(previewMode),
    _frameSkip(frameSkip),
    _continue(true),
    _xMouse(-1),
    _yMouse(-1),
    _buttonsMouse(0),
    _gmic_images(),
    _gmic(0)
{
  setCommand(command);
  setFPS(fps);
#ifdef _IS_MACOS_
  setStackSize(8*1024*1024);
#endif
}

FilterThread::~FilterThread()
{
  delete _gmic;
}

void
FilterThread::setMousePosition(int x, int y, int buttons)
{
  _xMouse = x;
  _yMouse = y;
  _buttonsMouse = buttons;
}

void
FilterThread::setArguments(const QString & str)
{
  _arguments.lock();
  _arguments.object() = str;
  _arguments.unlock();
}

void
FilterThread::setPreviewMode(PreviewMode pm)
{
  _previewMode = pm;
}

void
FilterThread::setFrameSkip(int n)
{
  _frameSkip = n;
}

void
FilterThread::setFPS(int fps)
{
  _fps = fps;
  _frameInterval = 0;
  if (fps > 0) {
    _frameInterval = 1000/fps;
  }
}

void
FilterThread::stop()
{
  _continue = false;
  _fps = 1;
  _frameInterval = 0;
}

void
FilterThread::run()
{
  QTime timeMeasure;
  unsigned int lastCommandDuration = 0;
  timeMeasure.start();
  int n;
  while (_continue) {
    // Delay (minus last command duration)
    if (_frameInterval && lastCommandDuration < _frameInterval)
      msleep(_frameInterval-lastCommandDuration);
    // Skip some frames and grab an image from the webcam
    n = _frameSkip + 1;
    while (n--) {
      _imageSource.capture();
    }
    // Abort if no image is provided by the source
    if (! _imageSource.image()) {
      emit endOfCapture();
      return;
    }
    if (!_gmic_images)
      _gmic_images.assign(1);
    if (!_gmic_images[0].is_sameXYZC(_imageSource.width(),_imageSource.height(),1,3))
      _gmic_images[0].assign(_imageSource.width(),_imageSource.height(),1,3);

    ImageConverter::convert(_imageSource.image(), _gmic_images[0]);

    // Call the G'MIC interpreter.
    try {
      timeMeasure.restart();

      if (_commandUpdated) {
        delete _gmic;
        QString c = QString("foo: -skip $\"*\" ") + _command;
        _gmic = new gmic("", c.toLatin1().constData());
        _commandUpdated = false;
      }

      _gmic->run("-v -");
      QString c;
      c += QString("_x=") + QString("%1").arg(_xMouse);
      c += QString(" _y=") + QString("%1").arg(_yMouse);
      c += QString(" _b=") + QString("%1").arg(_buttonsMouse);
      QString call;
      _arguments.lock();
      if (_arguments.object().isEmpty())
        call = QString(" -foo 0");
      else
        call = QString(" -foo %1").arg(_arguments.object());
      _arguments.unlock();
      c += call;

      // SHOW(call);

      _gmic->run(c.toLatin1().constData(),_gmic_images,_gmic_images_names);
      lastCommandDuration = timeMeasure.elapsed();

      switch (_previewMode) {
      case Full:
        if (_gmic_images && _gmic_images[0]) {
          QSize size(_gmic_images[0].width(), _gmic_images[0].height());
          _imageMutexA->lock();
          if (_outputImageA->size() != size) {
            *_outputImageA = QImage(size, QImage::Format_RGB888);
          }
          _imageMutexA->unlock();
          ImageConverter::convert(_gmic_images[0], _outputImageA);
          if (_outputImageB) {
            _imageMutexB->lock();
            if (_outputImageB->size() != size) {
              *_outputImageB = QImage(size, QImage::Format_RGB888);
            }
            _imageMutexB->unlock();
            ImageConverter::convert(_gmic_images[0], _outputImageB);
          }
        }
        break;
      case Original: {
        _imageMutexA->lock();
        QSize size(_imageSource.width(), _imageSource.height());
        if (_outputImageA->size() != size) {
          *_outputImageA = QImage(size, QImage::Format_RGB888);
        }
        _imageMutexA->unlock();
        if (_outputImageB) {
          if (_outputImageB->size() != size) {
            *_outputImageB = QImage(size, QImage::Format_RGB888);
          }
          _imageMutexB->unlock();
        }
        ImageConverter::convert(_imageSource.image(), _outputImageA);
        ImageConverter::convert(_imageSource.image(), _outputImageB);
      }
        break;
      case LeftHalf:
        ImageConverter::merge(_imageSource.image(),_gmic_images[0],
            _outputImageA, _imageMutexA, ImageConverter::MergeLeft);
        ImageConverter::merge(_imageSource.image(),_gmic_images[0],
            _outputImageB, _imageMutexB, ImageConverter::MergeLeft);
        break;
      case TopHalf:
        ImageConverter::merge(_imageSource.image(), _gmic_images[0],
            _outputImageA, _imageMutexA, ImageConverter::MergeTop);
        ImageConverter::merge(_imageSource.image(), _gmic_images[0],
            _outputImageB, _imageMutexB, ImageConverter::MergeTop);
        break;
      case BottomHalf:
        ImageConverter::merge(_imageSource.image(), _gmic_images[0],
            _outputImageA, _imageMutexA, ImageConverter::MergeBottom);
        ImageConverter::merge(_imageSource.image(), _gmic_images[0],
            _outputImageB, _imageMutexB, ImageConverter::MergeBottom);
        break;
      case RightHalf:
        ImageConverter::merge(_imageSource.image(), _gmic_images[0],
            _outputImageA, _imageMutexB, ImageConverter::MergeRight);
        ImageConverter::merge(_imageSource.image(), _gmic_images[0],
            _outputImageB, _imageMutexB, ImageConverter::MergeRight);
        break;
      case DuplicateHorizontal:
        ImageConverter::merge(_imageSource.image(), _gmic_images[0],
            _outputImageA, _imageMutexA, ImageConverter::DuplicateHorizontal);
        ImageConverter::merge(_imageSource.image(), _gmic_images[0],
            _outputImageB, _imageMutexB, ImageConverter::DuplicateHorizontal);
        break;
      case DuplicateVertical:
        ImageConverter::merge(_imageSource.image(), _gmic_images[0],
            _outputImageA, _imageMutexA, ImageConverter::DuplicateVertical);
        ImageConverter::merge(_imageSource.image(), _gmic_images[0],
            _outputImageB, _imageMutexB, ImageConverter::DuplicateVertical);
        break;
      default:
        _outputImageA->fill(QColor(255,255,255).rgb());
        if (_outputImageB) {
          _outputImageB->fill(QColor(255,255,255).rgb());
        }
        break;
      }

    } catch (gmic_exception & e) {
      CImg<unsigned char> src(reinterpret_cast<unsigned char*>(_imageSource.image()->imageData),
                              3, _imageSource.width(), _imageSource.height(), 1, true);
      _gmic_images = src.get_permute_axes("yzcx");
      QString errorCommand = QString("-gimp_error_preview \"%1\"").arg(e.what());

      try {
        _gmic->run(errorCommand.toLatin1().constData(),_gmic_images,_gmic_images_names);
      } catch (gmic_exception &e) {
        const unsigned char color1[] = { 0,255,0 }, color2[] = { 0,0,0 };
        _gmic_images = src.get_permute_axes("yzcx").channel(0).resize(-100,-100,1,3).draw_text(10,10,"Syntax Error",color1,color2,0.5,57);
      }
      std::cerr << e.what() << std::endl;
      QSize size(_imageSource.image()->width, _imageSource.image()->height);
      if (_outputImageA->size() != size) {
        _imageMutexA->lock();
        *_outputImageA = QImage(size, QImage::Format_RGB888);
        _imageMutexA->unlock();
      }
      if (_outputImageB && _outputImageB->size() != size) {
        _imageMutexB->lock();
        *_outputImageB = QImage(size, QImage::Format_RGB888);
        _imageMutexB->unlock();
      }
      ImageConverter::convert(_gmic_images[0], _outputImageA);
      ImageConverter::convert(_gmic_images[0], _outputImageB);
    }
    emit imageAvailable();
    if (!_fps && _blockingSemaphore) {
      _blockingSemaphore->acquire(_blockingSemaphore->available()+1);
    }
  }
}

/*
 * Private methods
 */

void
FilterThread::setCommand(const QString & command)
{
  QByteArray str = command.toLatin1();
  _command = str.constData();
  _command.replace("{*,x}", "$_x")
      .replace("{*,y}", "$_y")
      .replace("{*,b}", "$_b");
  _commandUpdated = true;
}
