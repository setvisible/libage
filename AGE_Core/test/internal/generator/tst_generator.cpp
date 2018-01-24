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

#include <AGE/Generator>

class tst_Generator : public QObject
{
    Q_OBJECT
private slots:
    void test_yo();

};

/******************************************************************************
 ******************************************************************************/
void tst_Generator::test_yo()
{
    AGE::Generator target;
    const int expected = 33;
    const int actual = target.yo();

    QCOMPARE(actual, expected);
}

QTEST_APPLESS_MAIN(tst_Generator)

#include "tst_generator.moc"
