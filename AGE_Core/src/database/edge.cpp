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

#include "edge.h"

#include <QtCore/QtGlobal>
#include <QtCore/QString>
#ifdef QT_DEBUG
#  include <QtCore/QDebug>
#endif
#ifdef QT_TESTLIB_LIB
#  include <QtTest/QTest>
#endif

using namespace AGE;

Edge::Edge()
    : m_identifier(-1)
    , m_pid1(-1)
    , m_pid2(-1)
    , m_point1(PointPtr(0))
    , m_point2(PointPtr(0))
{
}

Edge::Edge(int identifier, int pid1, int pid2)
    : m_identifier(identifier)
    , m_pid1(pid1)
    , m_pid2(pid2)
    , m_point1(PointPtr(0))
    , m_point2(PointPtr(0))
{
}

/******************************************************************************
 ******************************************************************************/
bool Edge::operator==(const Edge &other) const
{
    return (*this).m_identifier == other.m_identifier
            && (*this).m_pid1 == other.m_pid1
            && (*this).m_pid2 == other.m_pid2;
}

bool Edge::operator!=(const Edge &other) const
{
    return ((*this) == other) ? false : true;
}

/******************************************************************************
 ******************************************************************************/
#ifdef QT_TESTLIB_LIB
/// This function is used by QCOMPARE() to output verbose information in case of a test failure.
char *toString(const AGE::Edge &edge)
{
    // bring QTest::toString overloads into scope:
    using QTest::toString;

    // delegate char* handling to QTest::toString(QByteArray):
    return toString( QString("Edge '%0' (%1, %2)")
                     .arg(edge.m_identifier)
                     .arg(edge.m_pid1)
                     .arg(edge.m_pid2) );
}
#endif


#ifdef QT_DEBUG
/// Custom Types to a Stream
QDebug operator<<(QDebug dbg, const AGE::Edge &edge)
{
    dbg.nospace() << QString("Edge '%0' (%1, %2)")
                     .arg(edge.m_identifier)
                     .arg(edge.m_pid1)
                     .arg(edge.m_pid2);
    return dbg.maybeSpace();
}
#endif


