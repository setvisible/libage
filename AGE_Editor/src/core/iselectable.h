/* - AGE Editor - Copyright (C) 2018 Sebastien Vavassori
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

#ifndef CORE_I_SELECTABLE_H
#define CORE_I_SELECTABLE_H

#include <osg/Geode>

class ISelectable
{
public:
    ISelectable() = default;
    virtual ~ISelectable() = default;
    virtual void setSelected(bool selected) = 0;
};


class SelectableGeode : public osg::Geode
{
public:
    SelectableGeode();
    SelectableGeode(const SelectableGeode& copy, osg::CopyOp copyop = osg::CopyOp::SHALLOW_COPY);
    META_Node(osg, SelectableGeode);

    ISelectable* selectable();
    void setSelectable(ISelectable *selectable);

protected:
    virtual ~SelectableGeode();

private:
    ISelectable* m_selectable;
};


#endif // CORE_I_SELECTABLE_H
