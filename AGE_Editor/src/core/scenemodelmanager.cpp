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

#include "scenemodelmanager.h"

#include <Core/Scene>

#include <Utils/Logger>

#include <AGE/Globals>
#include <AGE/Database/MasterWorld>
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
SceneModelManager::SceneModelManager(QObject *parent) : AbstractSceneModel(parent)
  , m_scene(new Scene(this))
  , m_masterWorld(AGE::WorldPtr(new AGE::MasterWorld))
{
    osg::setNotifyLevel( osg::INFO );
    osg::setNotifyHandler(new Logger);

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
void SceneModelManager::clear()
{
    m_world->clear();
    m_scene->clear();
}

/******************************************************************************
 ******************************************************************************/
/* SERIALISATION */
void SceneModelManager::read(QByteArray &bytes, bool *ok)
{
    clear();
    QBuffer buffer(&bytes);
    WorldFileWriter parser;
    m_masterWorld = parser.read(buffer, ok);
    populateScene();
}

void SceneModelManager::write(QByteArray &bytes) const
{
    QBuffer buffer(&bytes);
    WorldFileWriter parser;
    bool ok = parser.write(buffer, m_masterWorld);
    Q_ASSERT(ok);
}


/******************************************************************************
 ******************************************************************************/

Scene* SceneModelManager::scene() const
{
    return m_scene;
}



osg::ref_ptr<osg::Group> SceneModelManager::sceneNode() const
{
    return m_scene->sceneNode();
}


/******************************************************************************
 ******************************************************************************/
/// Populate the Scene from the World.
void SceneModelManager::populateScene()
{
    Q_ASSERT(m_masterWorld.data());

    int index = m_masterWorld->m_points.count();
    while (index>0) {
        index--;
        AGE::PointPtr point = m_masterWorld->m_points.at(index);
        m_scene->insertPoint(0, point);
        emit pointInserted(0, point);
    }

    // ...


    emit changed();
    regenerate();
}

/******************************************************************************
 ******************************************************************************/
int SceneModelManager::pointCount() const
{
    Q_ASSERT(m_masterWorld.data());
    return m_masterWorld->pointCount();
}

AGE::PointPtr SceneModelManager::pointAt(const int index) const
{
    if (index >= 0 && index < m_masterWorld->m_points.count()) {
        return m_masterWorld->m_points.at(index);
    }
    return AGE::PointPtr();
}

/******************************************************************************
 ******************************************************************************/
QSet<int> SceneModelManager::selectedPointIndexes() const
{
    return m_selectedPointIndexes;
}

AGE::ElementPtr SceneModelManager::elementAt(const int index) const
{
    return AGE::ElementPtr(Q_NULLPTR);
}


/******************************************************************************
 ******************************************************************************/
void SceneModelManager::insertPoint(const int index, const AGE::PointPtr &point)
{
    m_scene->insertPoint(index, point);
    m_masterWorld->insertPoint(index, point);
    emit pointInserted(index, point);
    emit changed();
    regenerate();
}

void SceneModelManager::setPoint(const int index, const AGE::PointPtr &point)
{
    if (index < 0 || index >= m_masterWorld->pointCount())
        return;

    const AGE::PointPtr old = m_masterWorld->pointAt(index);
    if (old == point)
        return;

    m_scene->setPointAt(index, point);
    m_masterWorld->setPointAt(index, point);

    emit pointChanged(index, point);
    emit changed();
    regenerate();
}

void SceneModelManager::removePoint(const int index)
{
    if (m_selectedPointIndexes.remove( index )) {
        emit selectionPointChanged();
    }
    if (index >= 0 && index < m_masterWorld->pointCount()) {

        m_scene->removePointAt(index);
        m_masterWorld->removePointAt(index);

        emit pointRemoved(index);
        emit changed();
        regenerate();
    }
}

void SceneModelManager::setPointSelection(const QSet<int> indexes)
{
    if (m_selectedPointIndexes == indexes)
        return;
    m_selectedPointIndexes = indexes;
    emit selectionPointChanged();
}

void SceneModelManager::setElementSelection(const QSet<int> indexes)
{

}


/******************************************************************************
 ******************************************************************************/
void SceneModelManager::regenerate()
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

