/** -*- mode: c++ ; c-basic-offset: 2 -*-
 * @file   ColorParameter.cpp
 * @author Sebastien Fourey
 * @date   Nov 2014
 *
 * @brief  Declaration of the class ColorParameter
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
#include "ColorParameter.h"
#include "Common.h"
#include <QWidget>
#include <QGridLayout>
#include <QToolButton>
#include <QLabel>
#include <QFont>
#include <QFontMetrics>
#include <QColorDialog>
#include <QPainter>
#include <cstdio>

ColorParameter::ColorParameter(QDomNode node, QObject *parent)
  : AbstractParameter(parent),
    _node(node),
    _alphaChannel(false),
    _label(0),
    _button(0),
    _dialog(0)
{
  _name = node.attributes().namedItem("name").nodeValue();
  QString def = node.attributes().namedItem("default").nodeValue();
  QString value = node.toElement().attribute("savedValue",def);

  QStringList list = value.split(",");
  int r = list[0].toInt();
  int g = list[1].toInt();
  int b = list[2].toInt();
  if (list.size() == 4) {
    int a = list[3].toInt();
    _default = _value = QColor(r,g,b,a);
    _alphaChannel = true;
  } else {
    _default = _value = QColor(r,g,b);
  }
}

ColorParameter::~ColorParameter()
{
  delete _button;
  delete _label;
  delete _dialog;
}

void
ColorParameter::addTo(QWidget * widget, int row)
{
  QGridLayout * grid = dynamic_cast<QGridLayout*>(widget->layout());
  if (! grid) return;
  delete _button;
  delete _label;

  _button = new QToolButton(widget);
  _button->setText("Color");

  QFontMetrics fm(widget->font());
  QRect r = fm.boundingRect("COLOR");
  _pixmap = QPixmap(r.width(),r.height()*2);
  updateButtonColor();

  grid->addWidget(_label = new QLabel(_name,widget),row,0,1,1);
  grid->addWidget(_button,row,1,1,1);
  connect(_button, SIGNAL(clicked()),
          this, SLOT(onButtonPressed()));
}

QString
ColorParameter::textValue() const
{
  const QColor & c = _value;
  if (_alphaChannel)
    return QString("%1,%2,%3,%4").arg(c.red()).arg(c.green()).arg(c.blue()).arg(c.alpha());
  else
    return QString("%1,%2,%3").arg(c.red()).arg(c.green()).arg(c.blue());
}

void
ColorParameter::setValue(const QString & value)
{
  QStringList list = value.split(",");
  int red = list[0].toInt();
  int green = list[1].toInt();
  int blue = list[2].toInt();
  if (list.size() == 4) {
    int alpha = list[3].toInt();
    _value = QColor(red,green,blue,alpha);
    _alphaChannel = true;
  } else {
    _value = QColor(red,green,blue);
    _alphaChannel = false;
  }
  if (_button) {
    updateButtonColor();
  }
}

void
ColorParameter::reset()
{
  _value = _default;
}

void ColorParameter::saveValueInDOM()
{
  _node.toElement().setAttribute("savedValue",textValue());
}

void
ColorParameter::onButtonPressed()
{
  QColor color = _value;
  if (!_dialog) {
    _dialog = new QColorDialog(color,0);
    connect(_dialog,SIGNAL(currentColorChanged(QColor)),
            this, SLOT(colorChanged(QColor)));
  } else {
    _dialog->setCurrentColor(color);
  }
  if (_alphaChannel) {
    _dialog->setOptions(QColorDialog::ShowAlphaChannel|QColorDialog::NoButtons);
  } else {
    _dialog->setOptions(QColorDialog::NoButtons);
  }
  _dialog->exec();
}

void
ColorParameter::colorChanged(const QColor & color)
{
  if (color.isValid()) {
    _value = color;
    updateButtonColor();
    emit valueChanged();
  }
}

void ColorParameter::updateButtonColor()
{
  QPainter painter(&_pixmap);
  QColor color(_value);
  if (_alphaChannel)
    painter.drawImage(0,0,QImage(":images/transparency.png"));
  painter.setBrush(color);
  painter.setPen(Qt::black);
  painter.drawRect(0,0,_pixmap.width()-1,_pixmap.height()-1);
  _button->setIcon(_pixmap);
}


