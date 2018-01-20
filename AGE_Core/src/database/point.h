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

#ifndef AGE_POINT_H
#define AGE_POINT_H

#include <AGE/Globals>
#include <AGE/Database/Coordinate>

#include <QtCore/QSharedPointer>

#ifdef __cplusplus
extern "C" {
#endif


namespace AGE {

/**
 * A point location in 3D Geodesic space.
 */
class LIBAGESHARED_EXPORT Point : public Coordinate
{
public:
    explicit Point();
    explicit Point(int identifier,
                   GeoCoordinate longitude,
                   GeoCoordinate latitude,
                   GeoCoordinate altitude);


};

typedef QSharedPointer<Point> PointPtr;

} // namespace AGE

#ifdef __cplusplus
}
#endif

#endif // AGE_POINT_H
