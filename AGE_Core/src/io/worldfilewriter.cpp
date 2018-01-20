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

#include "worldfilewriter.h"

#include <AGE/Database/Point>

#include <QtCore/QIODevice>
#include <QtCore/QByteArray>
#include <QtCore/QSharedPointer>
#ifdef QT_DEBUG
#  include <QtCore/QDebug>
#endif

static const char *s_point     = "POINT ";
static const char *s_edge      = "EDGE ";
static const char *s_region    = "REGION ";
static const char s_separator  = ' ';
static const char s_comment    = '$';


/*! \class WorldFileWriter
 * \brief The class WorldFileWriter is a reader/writer for World file.
 *
 * The World file contains the data related to the world, especially
 * the master keypoints.
 *
 * The World file is saved in plain format, to be editable manually by a user.
 *
 * \example
 * \code
 * QFileDevice device("my_world.txt");
 * WorldFileWriter parser;
 * bool ok;
 * AGE::WorldPtr world = parser.read(device, &ok);
 * if (!ok) {
 *      qDebug() << parser.getErrors();
 *      // Here, 'world' contains error, but is still playable.
 *      // We want a robust parser, we don't care about minor syntax errors.
 * }
 * \endcode
 *
 * \sa CellFileWriter
 */

/*! \brief Constructor.
 */
WorldFileWriter::WorldFileWriter()
{
}


/******************************************************************************
 ******************************************************************************/
QStringList WorldFileWriter::getErrors() const
{
    return m_errors;
}

/******************************************************************************
 ******************************************************************************/
AGE::WorldPtr WorldFileWriter::read(QIODevice &device, bool *ok)
{
    QSharedPointer<AGE::World> world = QSharedPointer<AGE::World>(new AGE::World);
    Q_ASSERT(!world.isNull());

    m_errors.clear();
    (*ok) = true;

    if (!device.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_errors << QLatin1String("Cannot read the device.");
        (*ok) = false;
        return world;
    }

    int lineNumber = 0;

    /* ************************************************* */
    /* first pass: load the points                       */
    /* ************************************************* */
    while (!device.atEnd()) {
        lineNumber++;
        QByteArray line = device.readLine();
        line = line.simplified();

        if (line.isEmpty() || line.startsWith(s_comment)) {
            continue;
        }

        if (! line.toUpper().startsWith(s_point)) {
            qDebug() << "error";
        } else {

            const QList<QByteArray> list = line.split(s_separator);
            if (list.count() != 5) {
                m_errors << QString("line %0: wrong format for point.").arg(lineNumber);
                (*ok) = false;
            } else {

                QByteArray pid = list.at(1);
                QByteArray lon = list.at(2);
                QByteArray lat = list.at(3);
                QByteArray alt = list.at(4);

                AGE::PointPtr point = AGE::PointPtr(new AGE::Point);

                bool convert_ok = true;
                bool _ok;
                point->m_identifier        = pid.toInt(&_ok, 10); convert_ok &= _ok;
                point->m_longitude = (AGE::GeoCoordinate) lon.toInt(&_ok, 10); convert_ok &= _ok;
                point->m_latitude  = (AGE::GeoCoordinate) lat.toInt(&_ok, 10); convert_ok &= _ok;
                point->m_altitude  = (AGE::GeoCoordinate) alt.toInt(&_ok, 10); convert_ok &= _ok;
                if (!convert_ok) {
                    m_errors << QString("line %0: invalid coordinate for point.").arg(lineNumber);
                    (*ok) = false;
                } else {
                    world->m_points.append( point );
                }
            }
        }
    }

    /* ************************************************* */
    /* second pass: load the edges and regions           */
    /* ************************************************* */
    device.seek(0);


    return world;
}

bool WorldFileWriter::write(QIODevice &device, const AGE::WorldPtr &world)
{
    Q_ASSERT(!world.isNull());
    m_errors.clear();

    if (!device.open(QIODevice::WriteOnly | QIODevice::Text)) {
        m_errors << QLatin1String("Cannot write the device.");
        return false;
    }

    /* ************************************************* */
    /* first pass: write the points                      */
    /* ************************************************* */
    device.write(QString("%0 Points").arg(s_comment).toLatin1());
    foreach (const AGE::PointPtr &point, world->m_points) {
        QByteArray line;
        line.append(s_point);
        line.append(s_separator);
        line.append(QByteArray::number(point->m_identifier));
        line.append(s_separator);
        line.append(QByteArray::number(point->m_longitude));
        line.append(s_separator);
        line.append(QByteArray::number(point->m_latitude));
        line.append(s_separator);
        line.append(QByteArray::number(point->m_altitude));
        line.append(s_separator);
        device.write(line);
    }

    /* ************************************************* */
    /* second pass: load the edges                       */
    /* ************************************************* */
    device.write(QString("%0 Edges").arg(s_comment).toLatin1());




    /* ************************************************* */
    /* second pass: load the regions                     */
    /* ************************************************* */
    device.write(QString("%0 Regions").arg(s_comment).toLatin1());



    device.write(QString("%0 ").arg(s_comment).toLatin1());
    return true;
}

