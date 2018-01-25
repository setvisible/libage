/* - AGE Editor - Copyright (C) 2017 Sebastien Vavassori
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

#ifndef CORE_SCENE_COMMAND_H
#define CORE_SCENE_COMMAND_H

#include <QtCore/QString>
#include <QtWidgets/QUndoCommand>

#include <Core/SceneManager>

namespace SpliceCommand {

class AppendPoint : public QUndoCommand
{
public:
    AppendPoint(QString *doc, const QString &text)
        : m_document(doc), m_text(text) { setText("append text"); }
    virtual void undo() { m_document->chop(m_text.length()); }
    virtual void redo() { m_document->append(m_text); }
private:
    QString *m_document;
    QString m_text;
};
/******************************************************************************
 ******************************************************************************/


} // namespace SpliceCommand

#endif // CORE_SCENE_COMMAND_H