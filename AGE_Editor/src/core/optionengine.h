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

#ifndef CORE_OPTION_ENGINE_H
#define CORE_OPTION_ENGINE_H

#include <QtCore/QObject>

class Scene;

class OptionEngine : public QObject
{
    Q_OBJECT
public:
    explicit OptionEngine(QObject *parent = Q_NULLPTR);

    Scene* scene() const;
    void setScene(Scene *scene);

    /// \todo persistence of user settings ?
    /// \todo Add ReadSettings
    /// \todo Add WriteSettings

    bool isAxesVisible() const;
    bool isGridVisible() const;
    bool isBackgroundVisible() const;
    // --
    bool isMasterVisible() const;
    bool isSlaveVisible() const;
    // --
    bool isContourVisible() const;
    bool isWireframeVisible() const;
    bool isTextureVisible() const;
    bool isWireframeAndTextureVisible() const;

Q_SIGNALS:
    void axesVisibilityChanged(bool visible);
    void gridVisibilityChanged(bool visible);
    void backgroundVisibilityChanged(bool visible);
    // --
    void masterVisibilityChanged(bool visible);
    void slaveVisibilityChanged(bool visible);
    // --
    void contourVisibilityChanged(bool visible);
    void wireframeVisibilityChanged(bool visible);
    void textureVisibilityChanged(bool visible);
    void wireframeAndTextureVisibilityChanged(bool visible);

public Q_SLOTS:
    virtual void clear();

    virtual void setAxesVisible(bool visible);
    virtual void setGridVisible(bool visible);
    virtual void setBackgroundVisible(bool visible);
    // --
    virtual void setMasterVisible(bool visible);
    virtual void setSlaveVisible(bool visible);
    // --
    virtual void setContourVisible(bool visible);
    virtual void setWireframeVisible(bool visible);
    virtual void setTextureVisible(bool visible);
    virtual void setWireframeAndTextureVisible(bool visible);

    /// \todo change color of points
    /// \todo change size of points
    /// \todo set points visible
    ///  ...


private:
    Scene* m_scene;
    bool m_axesVisible;
    bool m_gridVisible;
    bool m_backgroundVisible;
    // --
    bool m_masterVisible;
    bool m_slaveVisible;
    // --
    bool m_contourVisible;
    bool m_wireframeVisible;
    bool m_textureVisible;
    bool m_wireframeAndTextureVisible;

};

#endif // CORE_OPTION_ENGINE_H
