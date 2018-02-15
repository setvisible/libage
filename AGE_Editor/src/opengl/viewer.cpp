/* - AGE Editor - Copyright (C) 2017 Sebastien Vavassori
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; If not, see <http://www.gnu.org/licenses/>.
 */

#include "viewer.h"

#include "openglviewer.h"

#include <Core/AbstractSceneModel>

#include <osg/ref_ptr>
#include <osg/Group>

#include <QtWidgets/QHBoxLayout>
#ifdef QT_DEBUG
#  include <QtCore/QDebug>
#endif

/*! \class Viewer
 *  \brief The class Viewer is the main 3D view in the AGE Editor.
 */

/*! \brief Constructor.
 */
Viewer::Viewer(QWidget *parent) : AbstractSceneView(parent)
  , m_openGLViewer(new OpenGLViewer(this))
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0); /* no border */
    layout->addWidget(m_openGLViewer);
    this->setLayout(layout);
}

Viewer::~Viewer()
{
    // delete ui;
}

void Viewer::update()
{
    m_openGLViewer->update();
}

/******************************************************************************
 ******************************************************************************/
void Viewer::setModel(AbstractSceneModel *model)
{
    /* Set up the root OSG Node */
    osg::ref_ptr<osg::Group> scene = model->sceneNode();
    m_openGLViewer->setSceneNode(scene);

    AbstractSceneView::setModel(model);
}
