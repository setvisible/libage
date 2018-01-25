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

#include "scenemanager.h"

#include <Core/Scene>

#include <AGE/Globals>
#include <AGE/Database/World>
#include <AGE/IO/WorldFileWriter>

#include <QtCore/QBuffer>
#include <QtCore/QSharedPointer>


/*! \class SceneManager
 *  \brief The class SceneManager is in charge of the procedural scene.
 *
 * The main role of SceneManager is to perform the user actions:
 * \li in the AGE::World that contains the libAGE scene
 * \li in the Scene that contains the OSG scene
 *
 * The SceneManager updates the procedural scene
 * whenever the user changes a thing, through the AGE::Generator.
 *
 * The SceneManager manages the current user selection
 * and highlights the selected 3D objects.
 *
 * The SceneManager animates the scene.
 */

/*! \brief Constructor.
 */
SceneManager::SceneManager(QObject *parent) : AbstractSceneModel(parent)
  , m_scene(new Scene(this))
  , m_world(AGE::WorldPtr(new AGE::World))
{
    this->clear();
}

/******************************************************************************
 ******************************************************************************/
/*!
 * \fn void SceneManager::changed()
 * \brief This signal is emitted whenever the SceneManager world data is changed.
 * (i.e. AGE::World's and children's data, like a script or a 3D Object)
 */

/******************************************************************************
 ******************************************************************************/
/*! \brief Clear and emit the change, in order to update the views,
 * that derive from AbstractSceneView.
 */
void SceneManager::clear()
{
    m_world.clear();
    m_scene->clear();
}

/******************************************************************************
 ******************************************************************************/
/* SERIALISATION */
void SceneManager::read(QByteArray &bytes, bool *ok)
{
    clear();
    QBuffer buffer(&bytes);
    WorldFileWriter parser;
    m_world = parser.read(buffer, ok);
}

void SceneManager::write(QByteArray &bytes) const
{
    QBuffer buffer(&bytes);
    WorldFileWriter parser;
    bool ok = parser.write(buffer, m_world);
    Q_ASSERT(ok);
}


/******************************************************************************
 ******************************************************************************/
osg::ref_ptr<osg::Group> SceneManager::sceneNode() const
{
    return m_scene->sceneNode();
}


/******************************************************************************
 ******************************************************************************/
int SceneManager::pointCount() const
{
    Q_ASSERT(m_world.data());
    return m_world->pointCount();
}

AGE::PointPtr SceneManager::pointAt(const int index) const
{
    if (index >= 0 && index < m_world->m_points.count()) {
        return m_world->m_points.at(index);
    }
    return AGE::PointPtr();
}

/******************************************************************************
 ******************************************************************************/
QSet<int> SceneManager::selectedPointIndexes() const
{
    return m_selectedPointIndexes;
}

AGE::ElementPtr SceneManager::elementAt(const int index) const
{
    return AGE::ElementPtr(Q_NULLPTR);
}


/******************************************************************************
 ******************************************************************************/
bool SceneManager::insertPoint(const int index, const AGE::PointPtr &point)
{

    // Command here

    Q_UNUSED(index);
    Q_UNUSED(point);
    return false;
}

bool SceneManager::setPoint(const int index, const AGE::PointPtr &point)
{
    Q_UNUSED(index);
    Q_UNUSED(point);
    return false;
}

bool SceneManager::removePoint(const int index)
{
    Q_UNUSED(index);
    return false;
}

bool SceneManager::setPointSelection(const QSet<int> indexes)
{

}

bool SceneManager::setElementSelection(const QSet<int> indexes)
{

}


/******************************************************************************
 ******************************************************************************/
void SceneManager::regenerate()
{
    /// \todo Use worker thread here.
    /// \todo see  Mandelbrot Example  or  Blocking Fortune Client Example
    /*  if (m_solver && m_splice) {
        m_results = m_solver->calculate( m_splice );
    } else {
        m_results.clear();
    }
    emit resultsChanged();*/
}

