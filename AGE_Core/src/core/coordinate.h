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

#ifndef AGE_CORE_COORDINATE_H
#define AGE_CORE_COORDINATE_H

#include <AGE/Globals>

#include <QtGlobal>
#include <QtCore/QSharedPointer>
#include <QtCore/QMetaType>

QT_BEGIN_NAMESPACE
class QDebug;
QT_END_NAMESPACE

#ifdef __cplusplus
extern "C" {
#endif

namespace AGE {

/**
 * A Geodesic coordinate in Geodesic.
 * The precision is about 10cm in the worst case (equator line).
 */
typedef quint32 GeoCoordinate;


/**
 * A Coordinate location in 3D Geodesic space.
 */
class LIBAGESHARED_EXPORT Coordinate
{
public:
    explicit Coordinate();
    explicit Coordinate(int identifier,
                        GeoCoordinate longitude,
                        GeoCoordinate latitude,
                        GeoCoordinate altitude);


    bool operator==(const Coordinate &other) const;
    bool operator!=(const Coordinate &other) const;


    //protected:
    int m_identifier;
    GeoCoordinate m_longitude;
    GeoCoordinate m_latitude;
    GeoCoordinate m_altitude;


};

// static methods to convert, project, intersect...

typedef QSharedPointer<Coordinate> CoordinatePtr;


} // namespace AGE

#ifdef __cplusplus
}
#endif


Q_DECLARE_TYPEINFO(AGE::Coordinate, Q_PRIMITIVE_TYPE);


#ifdef QT_TESTLIB_LIB
LIBAGESHARED_EXPORT char *toString(const AGE::Coordinate &coord);
#endif

Q_DECLARE_METATYPE(AGE::Coordinate)

#ifdef QT_DEBUG
QT_BEGIN_NAMESPACE
LIBAGESHARED_EXPORT QDebug operator<<(QDebug dbg, const AGE::Coordinate &coord);
QT_END_NAMESPACE
#endif



#endif // AGE_CORE_COORDINATE_H
