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

#ifndef AGE_BLOCK_H
#define AGE_BLOCK_H

#include <AGE/Globals>
#include <AGE/ScriptEngine/Script>
#include <AGE/ScriptEngine/Node>

#include <QtCore/QSharedPointer>

#ifdef __cplusplus
extern "C" {
#endif

namespace AGE {

/**
 * Represents a subdivision of the Region.
 *
 * For example, if the Region represents a city block delimited by roads,
 * the Region is composed by several Blocks. Each Block represents a building.
 *
 */
class LIBAGESHARED_EXPORT Block
{
public:
    explicit Block();
   

private:
    QList<NodePtr> m_points;

};

typedef QSharedPointer<Block> BlockPtr;

} // namespace AGE

#ifdef __cplusplus
}
#endif

#endif // AGE_BLOCK_H
