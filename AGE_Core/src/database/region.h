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

#ifndef AGE_REGION_H
#define AGE_REGION_H

#include <AGE/Globals>
#include <AGE/Database/Point>
#include <AGE/Database/Scriptable>

#include <QtCore/QSharedPointer>
#include <QtCore/QtContainerFwd> /* Forward Declarations of the Qt's Containers */


#ifdef __cplusplus
extern "C" {
#endif

namespace AGE {

/**
 * Represents a region of space where objects are built.
 *
 * It's appropriate for large surface objects, like city, ocean or forest.
 *
 * For example, a region can represent a forest or a city block delimited by roads.
 *
 * The region is split in different Blocks, each Block generated by the script.
 */
class LIBAGESHARED_EXPORT Region : public Scriptable
{
public:
    explicit Region();


    int m_identifier;

private:
    QList<PointPtr> m_points;

};

typedef QSharedPointer<Region> RegionPtr;

} // namespace AGE

#ifdef __cplusplus
}
#endif

#endif // AGE_REGION_H
