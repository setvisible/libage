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

#include "iselectable.h"

SelectableGeode::SelectableGeode() : osg::Geode()
  , m_selectable(0)
{
}

SelectableGeode::SelectableGeode(const SelectableGeode& copy, osg::CopyOp copyop)
    : osg::Geode(copy, copyop)
    , m_selectable(copy.m_selectable)
{
}

SelectableGeode::~SelectableGeode()
{
}

ISelectable* SelectableGeode::selectable()
{
    return m_selectable;
}

void SelectableGeode::setSelectable(ISelectable *selectable)
{
    m_selectable = selectable;
}
