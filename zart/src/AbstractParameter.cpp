/** -*- mode: c++ ; c-basic-offset: 2 -*-
 * @file   AbstractParameter.cpp
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
#include "AbstractParameter.h"
#include "IntParameter.h"
#include "FloatParameter.h"
#include "BoolParameter.h"
#include "ChoiceParameter.h"
#include "ColorParameter.h"
#include "SeparatorParameter.h"
#include "NoteParameter.h"
#include "FileParameter.h"
#include "FolderParameter.h"
#include "TextParameter.h"
#include "LinkParameter.h"
#include "ConstParameter.h"

AbstractParameter::AbstractParameter(QObject *parent)
  : QObject(parent)
{
}

AbstractParameter::~AbstractParameter()
{
}

bool
AbstractParameter::isVisible() const
{
  return true;
}

QString
AbstractParameter::unquotedTextValue() const
{
  return textValue();
}

AbstractParameter *
AbstractParameter::createFromNode(QDomNode node, QObject * parent)
{
  QString name = node.nodeName();
  if (name == "int") {
    return new IntParameter(node,parent);
  }
  if (name == "float") {
    return new FloatParameter(node,parent);
  }
  if (name == "bool") {
    return new BoolParameter(node,parent);
  }
  if (name == "choice") {
    return new ChoiceParameter(node,parent);
  }
  if (name == "color") {
    return new ColorParameter(node,parent);
  }
  if (name == "separator") {
    return new SeparatorParameter(node,parent);
  }
  if (name == "note") {
    return new NoteParameter(node,parent);
  }
  if (name == "file") {
    return new FileParameter(node,parent);
  }
  if (name == "folder") {
    return new FolderParameter(node,parent);
  }
  if (name == "text") {
    return new TextParameter(node,parent);
  }
  if (name == "link") {
    return new LinkParameter(node,parent);
  }
  if (name == "const") {
    return new ConstParameter(node,parent);
  }
  return 0;
}

