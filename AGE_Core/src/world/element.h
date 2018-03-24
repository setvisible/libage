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

#ifndef AGE_WORLD_ELEMENT_H
#define AGE_WORLD_ELEMENT_H

#include <AGE/Globals>
#include <AGE/Database/MasterElement>
#include <AGE/World/Node>
#include <AGE/World/Property>
#include <AGE/World/Tile>

//#include <QtCore/QSharedPointer>

#include <QtCore/QVector>
#include <osg/LOD>

#ifdef __cplusplus
extern "C" {
#endif

namespace AGE {

/**
 * An Element is the smallest piece of visible geometry.
 * It is constructed by auto-generation.
 *
 * For example, in Manhattan, an Element can represent one building in a block,
 * or a crossroad, or a road section.
 *
 * To avoid repetitive landscape, an Element is generated with small variation. 
 * A variation is explicitly described in the Script and variables come from a
 * Property, that is attached to the Element.
 * 
 * It inherits from an osg::LOD (Level Of Detail object),
 * so it contains Geodes (Geometry Nodes).
 * After auto-generation, the final Tile in the world has Elements everywhere.
 *
 */
class LIBAGESHARED_EXPORT Element : public osg::LOD
{
public:
    Element();
    Element(const Element& copy, osg::CopyOp copyop = osg::CopyOp::SHALLOW_COPY);
    META_Node(osg, Element);

protected:
    virtual ~Element();

private:

};

} // namespace AGE

#ifdef __cplusplus
}
#endif

#endif // AGE_WORLD_ELEMENT_H
