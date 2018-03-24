/* - AGE Core Library - Copyright (C) 2018 Sebastien Vavassori
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

#ifndef AGE_WORLD_NODE_H
#define AGE_WORLD_NODE_H

#include <AGE/Globals>
#include <AGE/Core/Coordinate>
#include <AGE/Database/Point>
#include <AGE/World/Element>

#include <QtCore/QSharedPointer>

#ifdef __cplusplus
extern "C" {
#endif

namespace AGE {

/**
 * A Node is auto-generated from constraints given by the Point,
 * Edge and/or Region that owns it.
 *
 * For example, an house and the adjacent road is contructed by
 * two Elements, ans share 2 Nodes.
 */
class LIBAGESHARED_EXPORT Node : public Coordinate
{
public:
    explicit Node();

    AGE::PointPtr masterPoint() const;

private:
    AGE::PointPtr m_masterPoint;

};
typedef QSharedPointer<Node> NodePtr;


} // namespace AGE

#ifdef __cplusplus
}
#endif

#endif // AGE_WORLD_NODE_H
