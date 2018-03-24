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

#ifndef IO_WORLD_FILE_WRITER_H
#define IO_WORLD_FILE_WRITER_H

#include <AGE/Globals>
#include <AGE/Database/MasterWorld>

#include <QtCore/QStringList>
#include <QtCore/QSharedPointer>

AGE_PIMPL_INCLUDE(WorldFileWriter)
class QIODevice;

#ifdef __cplusplus
extern "C" {
#endif

class LIBAGESHARED_EXPORT WorldFileWriter
{
public:
    explicit WorldFileWriter();

    AGE::WorldPtr read(QIODevice &device, bool *ok = Q_NULLPTR);
    bool write(QIODevice &device, const AGE::WorldPtr &world);

    QStringList getErrors() const;

private:
    AGE_PIMPL_DECLARE(WorldFileWriter)

};

#ifdef __cplusplus
}
#endif


#endif // IO_WORLD_FILE_WRITER_H
