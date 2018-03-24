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

#ifndef AGE_DATABASE_WORLD_H
#define AGE_DATABASE_WORLD_H

#include <AGE/Globals>
#include <AGE/Database/Point>
#include <AGE/Database/Edge>
#include <AGE/Database/Region>

#include <QtCore/QSharedPointer>
#include <QtCore/QVector>

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
class LIBAGESHARED_EXPORT MasterWorld
{
public:
    explicit MasterWorld();
    ~MasterWorld();


    void clear();
    bool isEmpty() const;


    /*inline*/ int pointCount() const;  /*Q_DECL_NOTHROW*/
    const PointPtr &pointAt(const int index) const;
    // AGE::PointPtr pointAt(const int index) const;

    void insertPoint(const int index, const AGE::PointPtr &point);
    void addFastener(const AGE::PointPtr &point);
    void addFastener(const QVector<AGE::PointPtr> &points);
    void setPointAt(const int index, const AGE::PointPtr &point);
    void removePointAt(const int index);
    void removeAllPoints();



    int edgeCount() const;
    EdgePtr edgeAt(int index) const ;

    int regionCount() const;
    RegionPtr regionAt(int index) const;


    //private:
    QVector<PointPtr> m_points;
    QVector<EdgePtr> m_edges;
    QVector<RegionPtr> m_regions;

};

typedef QSharedPointer<MasterWorld> WorldPtr;

} // namespace AGE

#ifdef __cplusplus
}
#endif

#endif // AGE_DATABASE_WORLD_H
