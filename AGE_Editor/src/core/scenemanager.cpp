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

#include "scenemanager.h"

#include "scenecommand.h"

#include <AGE/Database/Point>

#include <QtWidgets/QUndoStack>


/*! \class Manager
 *  \brief The class Manager is an adapter class for SceneManager.
 *
 * It manages the Undo/Redo Mechanism for the SceneManager.
 */

SceneManager::SceneManager(QObject *parent) : SceneModelManager(parent)
  , m_undoStack(new QUndoStack(this))
{
    this->clear();
}

QUndoStack* SceneManager::undoStack() const
{
    return m_undoStack;
}

/******************************************************************************
 ******************************************************************************/
void SceneManager::clear()
{
    SceneModelManager::clear();
    m_undoStack->clear();
}

/******************************************************************************
 ******************************************************************************/
void SceneManager::insertPoint(const int index, const AGE::PointPtr &point)
{
    m_undoStack->push(new SceneCommand::InsertPoint(this, index, point));
}

void SceneManager::setPoint(const int index, const AGE::PointPtr &point)
{
    m_undoStack->push(new SceneCommand::SetPoint(this, index, point));
}

void SceneManager::removePoint(const int index)
{
    m_undoStack->push(new SceneCommand::RemovePoint(this, index));
}

// -----------------------------------------------------------------------------

/******************************************************************************
 ******************************************************************************/
/* Callback Methods */
void SceneManager::_q_insertPoint(const int index, const AGE::PointPtr &point)
{
    SceneModelManager::insertPoint(index, point);
}

void SceneManager::_q_setPoint(const int index, const AGE::PointPtr &point)
{
    SceneModelManager::setPoint(index, point);
}

void SceneManager::_q_removePoint(const int index)
{
    SceneModelManager::removePoint(index);
}

// -----------------------------------------------------------------------------



