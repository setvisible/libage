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

#include <AGE/Database/World>

#include <QtCore/QStringList>

class QIODevice;

class WorldFileWriter
{
public:
    explicit WorldFileWriter();

    AGE::WorldPtr read(QIODevice &device, bool *ok = Q_NULLPTR);
    bool write(QIODevice &device, const AGE::WorldPtr &world);

    QStringList getErrors() const;

private:
    QStringList m_errors;
};

#endif // IO_WORLD_FILE_WRITER_H
