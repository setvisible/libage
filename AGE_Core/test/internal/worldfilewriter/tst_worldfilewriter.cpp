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

#include <QtTest/QtTest>
#include <QtCore/QDebug>

#include <AGE/IO/WorldFileWriter>

class tst_WorldFileWriter : public QObject
{
    Q_OBJECT
private slots:
    void parse_empty();
    void parse_points();

};

using namespace AGE;


/******************************************************************************
 ******************************************************************************/
void tst_WorldFileWriter::parse_empty()
{
    // Given
    bool ok;
    WorldFileWriter parser;
    QBuffer emptyBuffer;

    // When
    AGE::WorldPtr world = parser.read(emptyBuffer, &ok);

    // Then
    QCOMPARE(ok, true);
    QCOMPARE(parser.getErrors().count(), 0);
    QCOMPARE(world->isEmpty(), true);
}


/******************************************************************************
 ******************************************************************************/
void tst_WorldFileWriter::parse_points()
{
    // Given
    bool ok;
    WorldFileWriter parser;
    QByteArray byteArray("POINT 1 1000 1000 555\n");
    QBuffer buffer(&byteArray);

    // When
    AGE::WorldPtr world = parser.read(buffer, &ok);

    // Then
    QCOMPARE(ok, true);
    QCOMPARE(parser.getErrors().count(), 0);
    QCOMPARE(world->isEmpty(), false);
    QCOMPARE(world->pointCount(), 1);
    QCOMPARE((*world->pointAt(0).data()), AGE::Point(1, 1000, 1000, 555));
}


QTEST_APPLESS_MAIN(tst_WorldFileWriter)

#include "tst_worldfilewriter.moc"

