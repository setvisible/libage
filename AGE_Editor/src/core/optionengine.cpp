/* - AGE Editor - Copyright (C) 2018 Sebastien Vavassori
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

#include "optionengine.h"

#include <Core/Scene>


/*! \class OptionEngine
 *  \brief The class OptionEngine is in charge of the view options of the scene.
 * It saves the User settings.
 *
 */

/*! \brief Constructor.
 */
OptionEngine::OptionEngine(QObject *parent) : QObject(parent)
  , m_scene(Q_NULLPTR)
{
    this->clear();
}

void OptionEngine::clear()
{
    m_axesVisible = false;
    m_gridVisible = false;
    m_backgroundVisible = false;
    // --
    m_masterVisible = true;
    m_slaveVisible = true;
    // --
    m_contourVisible = false;
    m_wireframeVisible = false;
    m_textureVisible = true;
    m_wireframeAndTextureVisible = false;
}

/******************************************************************************
 ******************************************************************************/
Scene* OptionEngine::scene() const
{
    return m_scene;
}

void OptionEngine::setScene(Scene *scene)
{
    m_scene = scene;
}

/******************************************************************************
 ******************************************************************************/
bool OptionEngine::isAxesVisible() const
{
    return m_axesVisible;
}

bool OptionEngine::isGridVisible() const
{
    return m_gridVisible;
}

bool OptionEngine::isBackgroundVisible() const
{
    return m_backgroundVisible;
}

// -----------------------------------------------------------------------------
bool OptionEngine::isMasterVisible() const
{
    return m_masterVisible;
}

bool OptionEngine::isSlaveVisible() const
{
    return m_slaveVisible;
}

// -----------------------------------------------------------------------------
bool OptionEngine::isContourVisible() const
{
    return m_contourVisible;
}

bool OptionEngine::isWireframeVisible() const
{
    return m_wireframeVisible;
}

bool OptionEngine::isTextureVisible() const
{
    return m_textureVisible;
}

bool OptionEngine::isWireframeAndTextureVisible() const
{
    return m_wireframeAndTextureVisible;
}

/******************************************************************************
 ******************************************************************************/
void OptionEngine::setAxesVisible(bool visible)
{
    Q_ASSERT(m_scene);
    if (m_axesVisible == visible)
        return;
    m_axesVisible = visible;
    m_scene->setAxesVisible(m_axesVisible);
    emit axesVisibilityChanged(visible);
}

void OptionEngine::setGridVisible(bool visible)
{
    Q_ASSERT(m_scene);
    if (m_gridVisible == visible)
        return;
    m_gridVisible = visible;
    m_scene->setGridVisible(m_gridVisible);
    emit gridVisibilityChanged(visible);
}

void OptionEngine::setBackgroundVisible(bool visible)
{
    Q_ASSERT(m_scene);
    if (m_backgroundVisible == visible)
        return;
    m_backgroundVisible = visible;
    m_scene->setBackgroundVisible(m_backgroundVisible);
    emit backgroundVisibilityChanged(visible);
}

// -----------------------------------------------------------------------------
void OptionEngine::setMasterVisible(bool visible)
{
    Q_ASSERT(m_scene);
    if (m_masterVisible == visible)
        return;
    m_masterVisible = visible;
    m_scene->setMasterVisible(visible);
    emit masterVisibilityChanged(visible);
}

void OptionEngine::setSlaveVisible(bool visible)
{
    Q_ASSERT(m_scene);
    if (m_slaveVisible == visible)
        return;
    m_slaveVisible = visible;
    m_scene->setSlaveVisible(visible);
    emit slaveVisibilityChanged(visible);
}

// -----------------------------------------------------------------------------
void OptionEngine::setContourVisible(bool visible)
{
    Q_ASSERT(m_scene);
    if (m_contourVisible == visible)
        return;
    m_contourVisible = visible;
    m_scene->setContourVisible(visible);
    emit contourVisibilityChanged(visible);
}

void OptionEngine::setWireframeVisible(bool visible)
{
    Q_ASSERT(m_scene);
    if (m_wireframeVisible == visible)
        return;
    m_wireframeVisible = visible;
    m_scene->setWireframeVisible(visible);
    emit wireframeVisibilityChanged(visible);
}

void OptionEngine::setTextureVisible(bool visible)
{
    Q_ASSERT(m_scene);
    if (m_textureVisible == visible)
        return;
    m_textureVisible = visible;
    m_scene->setTextureVisible(visible);
    emit textureVisibilityChanged(visible);
}

void OptionEngine::setWireframeAndTextureVisible(bool visible)
{
    Q_ASSERT(m_scene);
    if (m_wireframeAndTextureVisible == visible)
        return;
    m_wireframeAndTextureVisible = visible;
    m_scene->setWireframeAndTextureVisible(visible);
    emit wireframeAndTextureVisibilityChanged(visible);
}
