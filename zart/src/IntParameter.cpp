/** -*- mode: c++ ; c-basic-offset: 2 -*-
 * @file   IntParameter.cpp
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
#include "IntParameter.h"
#include "Common.h"
#include <QWidget>
#include <QGridLayout>
#include <QSpinBox>
#include <QSlider>
#include <QLabel>

IntParameter::IntParameter(QDomNode node, QObject *parent)
  : AbstractParameter(parent),
    _node(node),
    _label(0),
    _slider(0),
    _spinBox(0)
{
  _name = node.attributes().namedItem("name").nodeValue();
  QString min = node.attributes().namedItem("min").nodeValue();
  QString max = node.attributes().namedItem("max").nodeValue();
  QString def = node.attributes().namedItem("default").nodeValue();
  QString value = node.toElement().attribute("savedValue",def);
  _min = min.toInt();
  _max = max.toInt();
  _default = def.toInt();
  _value = value.toInt();
}

IntParameter::~IntParameter()
{
  delete _spinBox;
  delete _slider;
  delete _label;
}

void
IntParameter::addTo(QWidget * widget, int row)
{
  QGridLayout * grid = dynamic_cast<QGridLayout*>(widget->layout());
  if (! grid) return;
  delete _spinBox;
  delete _slider;
  delete _label;
  _slider = new QSlider(Qt::Horizontal,widget);
  _slider->setRange(_min,_max);
  _slider->setValue(_value);
  _spinBox = new QSpinBox(widget);
  _spinBox->setRange(_min,_max);
  _spinBox->setValue(_value);
  grid->addWidget(_label = new QLabel(_name,widget),row,0,1,1);
  grid->addWidget(_slider,row,1,1,1);
  grid->addWidget(_spinBox,row,2,1,1);
  connect(_slider, SIGNAL(valueChanged(int)),
          this, SLOT(onSliderChanged(int)));
  connect(_spinBox, SIGNAL(valueChanged(int)),
          this, SLOT(onSpinBoxChanged(int)));
}

QString
IntParameter::textValue() const
{
  return _spinBox->text();
}

void
IntParameter::setValue(const QString & value)
{
  _value = value.toInt();
  if (_spinBox) {
    _spinBox->setValue(_value);
    _slider->setValue(_value);
  }
}

void
IntParameter::reset()
{
  _slider->setValue(_default);
  _spinBox->setValue(_default);
  _value = _default;
}

void
IntParameter::saveValueInDOM()
{
  _node.toElement().setAttribute("savedValue",_slider->value());
}

void
IntParameter::onSliderChanged(int i)
{
  _value = i;
  _spinBox->setValue(i);
  emit valueChanged();
}

void
IntParameter::onSpinBoxChanged(int i)
{
  _value= i;
  _slider->setValue(i);
  emit valueChanged();
}
