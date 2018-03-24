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

#include "masterworld.h"



using namespace AGE;

MasterWorld::MasterWorld()
{

}

MasterWorld::~MasterWorld()
{
}

/******************************************************************************
 ******************************************************************************/

void MasterWorld::clear()
{
     // a enlever

    m_points.clear();
    m_edges.clear();
    m_regions.clear();
}


bool MasterWorld::isEmpty() const
{
    return m_points.isEmpty() && m_edges.isEmpty() && m_regions.isEmpty();
}

/******************************************************************************
 ******************************************************************************/
int MasterWorld::pointCount() const
{
    return m_points.count();
}

const PointPtr &MasterWorld::pointAt(const int index) const
{
    return m_points.at(index);
}

/*PointPtr World::pointAt(const int index) const
{
    foreach (auto item, m_points) {
        if (item->m_identifier == index) {
            return item;
        }
    }
    return PointPtr(new Point());
}*/


void MasterWorld::insertPoint(const int index, const AGE::PointPtr &point)
{
    m_points.insert(index, point);
}

void MasterWorld::addFastener(const AGE::PointPtr &point)
{
    m_points.append(point);
}

void MasterWorld::addFastener(const QVector<AGE::PointPtr> &points)
{
#if QT_VERSION >= 0x050500
    m_points.append(points);
#else
    foreach (auto p, points) {
        m_points.append(p);
    }
#endif
}

void MasterWorld::setPointAt(const int index, const AGE::PointPtr &point)
{
    m_points[index] = point;
}

void MasterWorld::removePointAt(const int index)
{
    m_points.removeAt(index);
}

void MasterWorld::removeAllPoints()
{
    m_points.clear();
}

/******************************************************************************
 ******************************************************************************/

int MasterWorld::edgeCount() const
{
    return m_edges.count();
}

EdgePtr MasterWorld::edgeAt(int index) const
{
    foreach (auto item, m_edges) {
        if (item->m_identifier == index) {
            return item;
        }
    }
    return EdgePtr(new Edge());
}

int MasterWorld::regionCount() const
{
    return m_regions.count();
}

RegionPtr MasterWorld::regionAt(int index) const
{
    foreach (auto item, m_regions) {
        if (item->m_identifier == index) {
            return item;
        }
    }
    return RegionPtr(new Region());
}

