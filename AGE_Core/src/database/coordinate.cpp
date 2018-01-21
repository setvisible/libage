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

#include "coordinate.h"

#include <QtCore/QtGlobal>
#include <QtCore/QString>
#ifdef QT_DEBUG
#  include <QtCore/QDebug>
#endif
#ifdef QT_TESTLIB_LIB
#  include <QtTest/QTest>
#endif

using namespace AGE;

Coordinate::Coordinate()
    : m_identifier(-1)
    , m_longitude(0)
    , m_latitude(0)
    , m_altitude(0)
{
}

Coordinate::Coordinate(int identifier,
                       GeoCoordinate longitude,
                       GeoCoordinate latitude,
                       GeoCoordinate altitude)
    : m_identifier(identifier)
    , m_longitude(longitude)
    , m_latitude(latitude)
    , m_altitude(altitude)
{
}


/******************************************************************************
 ******************************************************************************/
bool Coordinate::operator==(const Coordinate &other) const
{
    return (*this).m_identifier == other.m_identifier
            && (*this).m_longitude == other.m_longitude
            && (*this).m_latitude == other.m_latitude
            && (*this).m_altitude == other.m_altitude;

}

bool Coordinate::operator!=(const Coordinate &other) const
{
    return ((*this) == other) ? false : true;
}

/******************************************************************************
 ******************************************************************************/
#ifdef QT_TESTLIB_LIB
/// This function is used by QCOMPARE() to output verbose information in case of a test failure.
char *toString(const AGE::Coordinate &coord)
{
    // bring QTest::toString overloads into scope:
    using QTest::toString;

    // delegate char* handling to QTest::toString(QByteArray):
    return toString( QString("Coordinate '%0' (%1, %2, %3)")
                     .arg(coord.m_identifier)
                     .arg(coord.m_longitude)
                     .arg(coord.m_latitude)
                     .arg(coord.m_altitude) );
}
#endif


#ifdef QT_DEBUG
/// Custom Types to a Stream
QDebug operator<<(QDebug dbg, const AGE::Coordinate &coord)
{
    dbg.nospace() << QString("Coordinate '%0' (%1, %2, %3)")
                     .arg(coord.m_identifier)
                     .arg(coord.m_longitude)
                     .arg(coord.m_latitude)
                     .arg(coord.m_altitude);
    return dbg.maybeSpace();
}
#endif


