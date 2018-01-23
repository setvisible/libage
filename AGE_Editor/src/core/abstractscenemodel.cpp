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

#include "abstractscenemodel.h"

#include <QtCore/QSet>

/*! \class AbstractSceneModel
 *  \brief The class AbstractSceneModel is a model (MVC paradigm).
 *
 * It synchronize the data and selections for the views, that must derived
 * from the class AbstractSceneView.
 *
 * For instance, when the user clicks on a 3D object in the 3D scene,
 * the other widgets of the application (let's say, the table containing the
 * list of the 3D objects, the property's editor that shows the properties
 * of the selected 3D object, and the main toolbar related to the
 * 3D object's state) are automatically updated accordingly to the selection.
 *
 * This is an elegant way to reduce the responsibility of the MainWindow,
 * because now the MainWindow doesn't directly connect its widgets each other.
 *
 * Moreover, this architecture simplifies the QUndoCommand implementation.
 *
 * \sa AbstractSceneView.
 */

/* Public Setters */
bool AbstractSceneModel::setPointSelection(const QSet<int> indexes)
{
    Q_UNUSED(indexes);
    return false;
}

bool AbstractSceneModel::setElementSelection(const QSet<int> indexes)
{
    Q_UNUSED(indexes);
    return false;
}
