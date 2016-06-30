/** -*- mode: c++ ; c-basic-offset: 2 -*-
 * @file   FileParameter.cpp
 * @author Sebastien Fourey
 * @date   Nov 2014
 *
 * @brief  Declaration of the class AbstractParameter
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
#include "FileParameter.h"
#include "Common.h"
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QFileDialog>
#include <QPushButton>
#include <QFileInfo>
#include <QFontMetrics>

FileParameter::FileParameter(QDomNode node, QObject *parent)
  : AbstractParameter(parent),
    _node(node),
    _label(0),
    _button(0)
{
  _name = node.attributes().namedItem("name").nodeValue();
  _default = node.toElement().attribute("default",QString());
  _value = node.toElement().attribute("savedValue",_default);
}

FileParameter::~FileParameter()
{
  delete _label;
  delete _button;
}

void
FileParameter::addTo(QWidget * widget, int row)
{
  QGridLayout * grid = dynamic_cast<QGridLayout*>(widget->layout());
  if (! grid) return;
  delete _label;
  delete _button;

  QString buttonText;
  if (_value.isEmpty()) {
    buttonText = "...";
  } else {
    int w = widget->contentsRect().width()/3;
    QFontMetrics fm(widget->font());
    buttonText = fm.elidedText(QFileInfo(_value).fileName(),Qt::ElideRight,w);
  }
  _button = new QPushButton(buttonText,widget);
  grid->addWidget(_label = new QLabel(_name,widget),row,0,1,1);
  grid->addWidget(_button,row,1,1,2);
  connect(_button, SIGNAL(clicked()),
          this, SLOT(onButtonPressed()));
}

QString
FileParameter::textValue() const
{
  if (_value.isEmpty())
    return QString("\"\\\"\\\"\"");
  else
    return QString("\"%1\"").arg(_value);
}

QString
FileParameter::unquotedTextValue() const
{
  return _value;
}

void
FileParameter::setValue(const QString & value)
{
  _value = value;
  if (_button) {
    if (_value.isEmpty()) {
      _button->setText("...");
    } else {
      int width = _button->contentsRect().width()-10;
      QFontMetrics fm(_button->font());
      _button->setText(fm.elidedText(QFileInfo(_value).fileName(),Qt::ElideRight,width));
    }
  }
}

void
FileParameter::reset()
{
  _value = _default;
}

void
FileParameter::saveValueInDOM()
{
  _node.toElement().setAttribute("savedValue",_value);
}

void
FileParameter::onButtonPressed()
{
  QString folder;
  if (!_value.isEmpty()) {
    folder = QFileInfo(_value).path();
  }
  QString filename = QFileDialog::getSaveFileName(0,"Select a file",folder,QString(),0,
                                                  QFileDialog::DontConfirmOverwrite);
  if (filename.isNull()) {
    _value = "";
    _button->setText("...");
  } else {
    _value = filename;
    int w = _button->contentsRect().width()-10;
    QFontMetrics fm(_button->font());
    _button->setText(fm.elidedText(QFileInfo(_value).fileName(),Qt::ElideRight,w));
  }
  emit valueChanged();
}
