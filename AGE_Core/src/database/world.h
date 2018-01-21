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

#ifndef AGE_WORLD_H
#define AGE_WORLD_H

#include <AGE/Globals>
#include <AGE/Database/Point>
#include <AGE/Database/Edge>
#include <AGE/Database/Region>

#include <QtCore/QSharedPointer>
#include <QtCore/QList>

#ifdef __cplusplus
extern "C" {
#endif

namespace AGE {

/**
 * Represents the entire world.
 *
 * It contains the master points, edges and regions.
 *
 */
class LIBAGESHARED_EXPORT World
{
public:
    explicit World();

    inline bool isEmpty() const Q_DECL_NOTHROW
    {
        return m_points.isEmpty() && m_edges.isEmpty() && m_regions.isEmpty();
    }


    inline int pointCount() const Q_DECL_NOTHROW { return m_points.count(); }
    inline PointPtr pointAt(int index) const Q_DECL_NOTHROW {
        foreach (auto item, m_points) {
            if (item->m_identifier == index) {
                return item;
            }
        }
        return PointPtr(new Point());
    }

    inline int edgeCount() const Q_DECL_NOTHROW { return m_edges.count(); }
    inline EdgePtr edgeAt(int index) const Q_DECL_NOTHROW {
        foreach (auto item, m_edges) {
            if (item->m_identifier == index) {
                return item;
            }
        }
        return EdgePtr(new Edge());
    }

    inline int regionCount() const Q_DECL_NOTHROW { return m_regions.count(); }
    inline RegionPtr regionAt(int index) const Q_DECL_NOTHROW {
        foreach (auto item, m_regions) {
            if (item->m_identifier == index) {
                return item;
            }
        }
        return RegionPtr(new Region());
    }



    //private:
    QList<PointPtr> m_points;
    QList<EdgePtr> m_edges;
    QList<RegionPtr> m_regions;

};

typedef QSharedPointer<World> WorldPtr;

} // namespace AGE

#ifdef __cplusplus
}
#endif

#endif // AGE_WORLD_H
