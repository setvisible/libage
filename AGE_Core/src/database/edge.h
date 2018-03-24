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

#ifndef AGE_DATABASE_EDGE_H
#define AGE_DATABASE_EDGE_H

#include <AGE/Globals>
#include <AGE/Database/Point>
#include <AGE/Database/MasterElement>
#include <AGE/Database/ScriptFile>

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
 * Represents an edge in the landscape.
 *
 * It is defined by two points.
 *
 * It represents a single segment of an electrical line, a road, a highway,
 * a river or a bridge.
 *
 * The final type is given by the \a Script to which the \a Edge is associed.
 *
 * \sa AGE::ScriptEngine::Script
 */
class LIBAGESHARED_EXPORT Edge : public MasterElement
{
public:
    explicit Edge();
    explicit Edge(int identifier, int pid1, int pid2);

    bool operator==(const Edge &other) const;
    bool operator!=(const Edge &other) const;

    int m_identifier;
    int m_pid1;     ///< Starting master point id.
    int m_pid2;     ///< Ending master point id.

protected:
    PointPtr m_point1;
    PointPtr m_point2;

    //private:
    //QList<EdgePtr> m_adjacentEdges;

};

typedef QSharedPointer<Edge> EdgePtr;

} // namespace AGE

#ifdef __cplusplus
}
#endif


Q_DECLARE_TYPEINFO(AGE::Edge, Q_PRIMITIVE_TYPE);


#ifdef QT_TESTLIB_LIB
LIBAGESHARED_EXPORT char *toString(const AGE::Edge &edge);
#endif

Q_DECLARE_METATYPE(AGE::Edge)

#ifdef QT_DEBUG
QT_BEGIN_NAMESPACE
LIBAGESHARED_EXPORT QDebug operator<<(QDebug dbg, const AGE::Edge &edge);
QT_END_NAMESPACE
#endif


#endif // AGE_DATABASE_EDGE_H
