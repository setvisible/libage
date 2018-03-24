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

#ifndef AGE_DATABASE_MASTER_ELEMENT_H
#define AGE_DATABASE_MASTER_ELEMENT_H

#include <AGE/Globals>
#include <AGE/Database/Point>
#include <AGE/Database/ScriptFile>

#include <QtCore/QSharedPointer>
#include <QtCore/QtContainerFwd> /* Forward Declarations of the Qt's Containers */


#ifdef __cplusplus
extern "C" {
#endif

namespace AGE {

/**
 * An interface for Edge and Region.
 *
 */
class LIBAGESHARED_EXPORT MasterElement
{
public:
    explicit MasterElement() {}
    virtual ~MasterElement() Q_DECL_NOEXCEPT {}

    // Q_INVOKABLE virtual int pointCount() const = 0;
    // Q_INVOKABLE virtual int secondaryPointCount() const = 0;
    // Q_INVOKABLE virtual int blockCount() const = 0;
    // Q_INVOKABLE virtual QSet<Block> execute() const = 0;


};

} // namespace AGE

#ifdef __cplusplus
}
#endif

#endif // AGE_DATABASE_MASTER_ELEMENT_H
