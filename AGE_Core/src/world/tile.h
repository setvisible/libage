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

#ifndef AGE_WORLD_TILE_H
#define AGE_WORLD_TILE_H

#include <AGE/Globals>

#include <osg/PagedLOD>

#ifdef __cplusplus
extern "C" {
#endif

namespace AGE {

/**
 * A Tile is used for the pagination mechanism in OSG.
 *
 */
class LIBAGESHARED_EXPORT Tile : public osg::PagedLOD
{
public:
    Tile();
    Tile(const Tile& copy, osg::CopyOp copyop = osg::CopyOp::SHALLOW_COPY);
    META_Node(osg, Tile);

protected:
    virtual ~Tile();

};

} // namespace AGE

#ifdef __cplusplus
}
#endif

#endif // AGE_WORLD_TILE_H
