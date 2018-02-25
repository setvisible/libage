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

#include "selectionvisitor.h"

#include <Core/ISelectable>

SelectionVisitor::SelectionVisitor() : osg::NodeVisitor()
{
    setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN);
}

void SelectionVisitor::setSelected(const QSet<SelectableGeode*> geodes)
{
    m_selected = geodes;
}

void SelectionVisitor::apply(osg::Geode& geode)
{
    SelectableGeode* sg = dynamic_cast<SelectableGeode*>(&geode);
    if (sg) {
        ISelectable* selectable = sg->selectable();
        if (selectable) {
            bool selected = m_selected.contains(sg);
            selectable->setSelected(selected);
        }
    }
    traverse( geode );
}
