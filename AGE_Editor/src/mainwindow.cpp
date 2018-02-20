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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "about.h"
#include "version.h"
#include "globals.h"

#include <Core/SceneManager>
#include <Core/Option>
#include <OpenGL/Viewer>
#include <Widgets/MainWidget>
#include <Widgets/PointTableWidget>
#include <Widgets/PointWidget>
#include <Widgets/SceneToolBar>

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QSettings>
#include <QtCore/QUrl>
#include <QtCore/QStandardPaths>
#include <QtGui/QCloseEvent>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QUndoStack>
#include <QtWidgets/QUndoView>
#ifdef QT_DEBUG
#  include <QtCore/QDebug>
#endif


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_sceneManager(new SceneManager(this))
  , m_option(new Option(this))
  , m_undoRedoPanel(Q_NULLPTR)
  , m_dirty(false)
  , m_physicalFile(false)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0,0);
    ui->splitter->setStretchFactor(1,10);

    this->setWindowTitle(QString("%0 v%1").arg(STR_APPLICATION_NAME).arg(STR_APPLICATION_VERSION));
    this->setWindowIcon(QIcon(":/icons/logo/maps-pin-place.ico"));
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    this->setAcceptDrops(true);

    m_option->setScene(m_sceneManager->scene());


    /* [1] */
    /* Connect the GUI to the Scene Manager. */
    ui->viewer->setModel(m_sceneManager);
    ui->mainWidget->pointTableWidget()->setModel(m_sceneManager);
    ui->mainWidget->pointWidget()->setModel(m_sceneManager);


    /* [2] */
    /* Connect the Scene Manager to the MainWindow. */
    /* In fact, the Scene Manager centralizes the changes. */
    QObject::connect(m_sceneManager, SIGNAL(changed()), this, SLOT(setDirty()));


    /* [3] */
    /* Internally, the Scene Manager updates the Scene, and
     * recalculates the geometries thanks to the ScriptEngine.
     * It emits the signal changed() to inform the GUI.
     */


    /* [4] */
    /* Connect the Scene Manager to the GUI. */
    /* Update the GUI with the new geometries. */


    /* [5] */
    /* Connect the rest of the GUI widgets together (selection, focus, etc.) */
    ui->sceneToolBar->connect(m_option);


    createActions();
    createMenus();

    readSettings();

    newFile();
}


MainWindow::~MainWindow()
{
    delete ui;
}

/******************************************************************************
 ******************************************************************************/
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

/******************************************************************************
 ******************************************************************************/
void MainWindow::newFile()
{
    if (maybeSave()) {
        m_physicalFile = false;
        m_currentFile = QFileInfo();
        m_currentFile.setFile(QStringLiteral("untitled.agw"));
        m_sceneManager->clear();

        /* Settings */
        ui->sceneToolBar->reset();

        this->setClean();
    }
}

bool MainWindow::isExampleFile() const
{
    return m_currentFile.filePath().startsWith(":/");
}

bool MainWindow::isPhysicalFile() const
{
    return m_physicalFile
            && m_currentFile.isFile()
            && !m_currentFile.isSymLink()
            && !isExampleFile();
}

bool MainWindow::save()
{
    if ( isPhysicalFile() ){
        return saveFile(m_currentFile.absoluteFilePath());
    } else {
        return saveAs();
    }
}

bool MainWindow::saveAs()
{
    QString filePath = askSaveFileName(QStringLiteral("World Data File (*.agw)"),
                                       tr("World Data File"));
    if (filePath.isEmpty()) {
        return false;
    }
    return saveFile(filePath);
}

void MainWindow::open()
{
    if (maybeSave()) {
        QString filePath = askOpenFileName(tr("World Data File (*.agw);;All files (*.*)"));
        if (!filePath.isEmpty()) {
            if (loadFile(filePath)) {
                this->setClean();
            }
        }
    }
}

/******************************************************************************
 ******************************************************************************/
void MainWindow::showFileProperties()
{
    //PropertiesDialog dialog(m_sceneManager, this);
    //dialog.exec();
}

/******************************************************************************
 ******************************************************************************/
void MainWindow::showUndoRedoPanel(bool toggled)
{
    Q_ASSERT(m_sceneManager->undoStack());
    if (!m_undoRedoPanel) {
        m_undoRedoPanel = new QUndoView(m_sceneManager->undoStack());
        Qt::WindowFlags flags = Qt::Tool | Qt::WindowStaysOnTopHint;
        flags ^= Qt::WindowCloseButtonHint;
        m_undoRedoPanel->setWindowFlags(flags);
        m_undoRedoPanel->setWindowTitle(QStringLiteral("Undo/Redo Panel"));
    }
    m_undoRedoPanel->setVisible(toggled);
}

/******************************************************************************
 ******************************************************************************/
void MainWindow::showPreferences()
{
    //  SettingsDialog dialog(this);
    //  dialog.exec();
    //  m_mystery->readSettings();
}

/******************************************************************************
 ******************************************************************************/
void MainWindow::about()
{
    QMessageBox msgBox(QMessageBox::NoIcon, tr("About AGE Editor"), aboutHtml());
    msgBox.exec();
}

/******************************************************************************
 ******************************************************************************/
bool MainWindow::maybeSave()
{
    if (m_dirty) {
        int ret = QMessageBox::warning(
                    this, tr("Unsaved changes"),
                    tr("The scene has not been saved.\n\n"
                       "Do you want to save your changes ?"),
                    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        if (ret == QMessageBox::Save) {
            return save();
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

QString MainWindow::niceFileName() const
{
    if ( isPhysicalFile() ){
        return QDir::toNativeSeparators(m_currentFile.canonicalFilePath());
    }else{
        return m_currentFile.fileName();
    }
}

void MainWindow::setDirty()
{
    if (!m_dirty) {
        m_dirty = true;
        this->setWindowTitle( niceFileName() + QStringLiteral("* - AGE Editor"));
    }
}

void MainWindow::setClean()
{
    m_dirty = false;
    this->setWindowTitle( niceFileName() + QStringLiteral(" - AGE Editor "));
}


/******************************************************************************
 ******************************************************************************/
QString MainWindow::askSaveFileName(const QString &fileFilter, const QString &title)
{
    QString suggestedPath;
    if ( isPhysicalFile() ) {
        suggestedPath = m_currentFile.canonicalFilePath();
    }else{
        const QString dir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        suggestedPath = dir + QDir::separator() + m_currentFile.fileName();
        suggestedPath = QDir::toNativeSeparators(suggestedPath);
    }
    return QFileDialog::getSaveFileName(this, title, suggestedPath, fileFilter);
}

QString MainWindow::askOpenFileName(const QString &fileFilter, const QString &title)
{
    QString currentDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    if ( isPhysicalFile() ){
        currentDir = m_currentFile.absolutePath();
    }
    return QFileDialog::getOpenFileName(this, title, currentDir, fileFilter);
}


/******************************************************************************
 ******************************************************************************/
void MainWindow::readSettings()
{
    QSettings settings;
    if ( !isMaximized() ) {
        this->move(settings.value("Position", QPoint(100, 100)).toPoint());
        this->resize(settings.value("Size", QSize(350, 350)).toSize());
    }
    this->setWindowState( (Qt::WindowStates)settings.value("WindowState", 0).toInt() );

}

void MainWindow::writeSettings()
{
    QSettings settings;

    if( !(isMaximized() | isFullScreen()) ) {
        settings.setValue("Position", this->pos());
        settings.setValue("Size", this->size());
    }
    settings.setValue("WindowState", (int)this->windowState()); // minimized, maximized, active, fullscreen...


    // --------------------------------------------------------------
    // Write also the current version of application in the settings,
    // because it might be used by 3rd-party update manager softwares like
    // FileHippo or Google Updater (aka gup).
    // --------------------------------------------------------------
    settings.setValue("Version", STR_APPLICATION_VERSION );
}

/******************************************************************************
 ******************************************************************************/
void MainWindow::createActions()
{
    //! [0] File
    ui->action_New->setShortcuts(QKeySequence::New);
    ui->action_New->setStatusTip(tr("Create a new world"));
    connect(ui->action_New, SIGNAL(triggered()), this, SLOT(newFile()));

    ui->action_Open->setShortcuts(QKeySequence::Open);
    ui->action_Open->setStatusTip(tr("Open a world from a file"));
    connect(ui->action_Open, SIGNAL(triggered()), this, SLOT(open()));

    ui->action_Save->setShortcuts(QKeySequence::Save);
    ui->action_Save->setStatusTip(tr("Save the world to current file"));
    connect(ui->action_Save, SIGNAL(triggered()), this, SLOT(save()));

    ui->action_SaveAs->setShortcuts(QKeySequence::SaveAs);
    ui->action_SaveAs->setStatusTip(tr("Save the world to a different file"));
    connect(ui->action_SaveAs, SIGNAL(triggered()), this, SLOT(saveAs()));

    ui->action_Properties->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F2));
    ui->action_Properties->setStatusTip(tr("Show the properties of the current file"));
    connect(ui->action_Properties, SIGNAL(triggered()), this, SLOT(showFileProperties()));

    ui->action_Exit->setShortcuts(QKeySequence::Quit);
    ui->action_Exit->setStatusTip(tr("Quit AGE Editor"));
    connect(ui->action_Exit, SIGNAL(triggered()), this, SLOT(close()));
    //! [0]

    //! [1] Edit
    {
        QUndoStack *stack = m_sceneManager->undoStack();
        Q_ASSERT(stack);

        ui->action_Undo->setShortcuts(QKeySequence::Undo);
        ui->action_Undo->setStatusTip(tr("Undo"));
        connect(ui->action_Undo, SIGNAL(triggered()), stack, SLOT(undo()));
        connect(stack, SIGNAL(canUndoChanged(bool)), ui->action_Undo, SLOT(setEnabled(bool)));
        ui->action_Undo->setEnabled(false);

        ui->action_Redo->setShortcuts(QKeySequence::Redo);
        ui->action_Redo->setStatusTip(tr("Redo"));
        connect(ui->action_Redo, SIGNAL(triggered()), stack, SLOT(redo()));
        connect(stack, SIGNAL(canRedoChanged(bool)), ui->action_Redo, SLOT(setEnabled(bool)));
        ui->action_Redo->setEnabled(false);
    }

    //! [1]

    //! [2] Find
    //! [2]

    //! [3] View
    ui->action_ZoomFit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_0));
    ui->action_ZoomFit->setStatusTip(tr("Zoom Fit"));
    //connect(ui->action_ZoomFit, SIGNAL(triggered()), ui->viewer, SLOT(zoomFit()));

    ui->action_ZoomIn->setShortcuts(QKeySequence::ZoomIn);
    ui->action_ZoomIn->setStatusTip(tr("Zoom In"));
    //connect(ui->action_ZoomIn, SIGNAL(triggered()), ui->viewer, SLOT(zoomIn()));

    ui->action_ZoomOut->setShortcuts(QKeySequence::ZoomOut);
    ui->action_ZoomOut->setStatusTip(tr("Zoom Out"));
    //connect(ui->action_ZoomOut, SIGNAL(triggered()), ui->viewer, SLOT(zoomOut()));


    ui->action_Axes->setStatusTip(tr("Show Axes"));
    ui->action_Axes->setCheckable(true);
    ui->action_Axes->setChecked(false);
    connect(ui->action_Axes, SIGNAL(toggled(bool)), m_option, SLOT(setAxesVisible(bool)));
    connect(m_option, SIGNAL(axesVisibilityChanged(bool)), ui->action_Axes, SLOT(setChecked(bool)));

    ui->action_Grid->setStatusTip(tr("Show Grid"));
    ui->action_Grid->setCheckable(true);
    ui->action_Grid->setChecked(false);
    connect(ui->action_Grid, SIGNAL(toggled(bool)), m_option, SLOT(setGridVisible(bool)));
    connect(m_option, SIGNAL(gridVisibilityChanged(bool)), ui->action_Grid, SLOT(setChecked(bool)));

    ui->action_Background->setStatusTip(tr("Show Background"));
    ui->action_Background->setCheckable(true);
    ui->action_Background->setChecked(false);
    connect(ui->action_Background, SIGNAL(toggled(bool)), m_option, SLOT(setBackgroundVisible(bool)));
    connect(m_option, SIGNAL(backgroundVisibilityChanged(bool)), ui->action_Background, SLOT(setChecked(bool)));

    ui->action_Contour->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_1));
    ui->action_Contour->setStatusTip(tr("Show Contour"));
    ui->action_Contour->setCheckable(true);
    ui->action_Contour->setChecked(false);
    connect(ui->action_Contour, SIGNAL(toggled(bool)), m_option, SLOT(setContourVisible(bool)));
    connect(m_option, SIGNAL(contourVisibilityChanged(bool)), ui->action_Contour, SLOT(setChecked(bool)));

    ui->action_Wireframe->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_2));
    ui->action_Wireframe->setStatusTip(tr("Show Wireframe"));
    ui->action_Wireframe->setCheckable(true);
    ui->action_Wireframe->setChecked(false);
    connect(ui->action_Wireframe, SIGNAL(toggled(bool)), m_option, SLOT(setWireframeVisible(bool)));
    connect(m_option, SIGNAL(wireframeVisibilityChanged(bool)), ui->action_Wireframe, SLOT(setChecked(bool)));

    ui->action_Texture->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_3));
    ui->action_Texture->setStatusTip(tr("Show Texture"));
    ui->action_Texture->setCheckable(true);
    ui->action_Texture->setChecked(true);
    connect(ui->action_Texture, SIGNAL(toggled(bool)), m_option, SLOT(setTextureVisible(bool)));
    connect(m_option, SIGNAL(textureVisibilityChanged(bool)), ui->action_Texture, SLOT(setChecked(bool)));

    ui->action_WireframeAndTexture->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_4));
    ui->action_WireframeAndTexture->setStatusTip(tr("Show Wireframe and Texture"));
    ui->action_WireframeAndTexture->setCheckable(true);
    ui->action_WireframeAndTexture->setChecked(false);
    connect(ui->action_WireframeAndTexture, SIGNAL(toggled(bool)), m_option, SLOT(setWireframeAndTextureVisible(bool)));
    connect(m_option, SIGNAL(wireframeAndTextureVisibilityChanged(bool)), ui->action_WireframeAndTexture, SLOT(setChecked(bool)));


    //! [3]

    //! [4] Database
    ui->action_CreatePoint->setStatusTip(tr("Create Point"));
    ui->action_CreatePoint->setCheckable(true);
    ui->action_CreatePoint->setChecked(false);
    //..

    //! [4]

    //! [5] Options
    ui->action_ShowUndoRedoPanel->setStatusTip(tr("Show Undo/Redo Panel"));
    ui->action_ShowUndoRedoPanel->setCheckable(true);
    ui->action_ShowUndoRedoPanel->setChecked(false);
    connect(ui->action_ShowUndoRedoPanel, SIGNAL(toggled(bool)), this, SLOT(showUndoRedoPanel(bool)));

#ifdef Q_OS_WIN
    ui->action_Preferences->setShortcut(QKeySequence(/*Qt::CTRL +*/ Qt::Key_F10));
#else
    ui->action_Preferences->setShortcuts(QKeySequence::Preferences);
#endif
    ui->action_Preferences->setStatusTip(tr("Open settings"));
    connect(ui->action_Preferences, SIGNAL(triggered()), this, SLOT(showPreferences()));

    //! [5]

    //! [6] Examples
    //! [6]

    //! [7] Help
    ui->action_About->setShortcuts(QKeySequence::HelpContents);
    ui->action_About->setStatusTip(tr("About %0").arg(STR_APPLICATION_NAME));
    connect(ui->action_About, SIGNAL(triggered()), this, SLOT(about()));

    ui->action_AboutQt->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F1));
    ui->action_AboutQt->setStatusTip(tr("About Qt"));
    connect(ui->action_AboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    //! [7]
}

void MainWindow::createMenus()
{

}


/******************************************************************************
 ******************************************************************************/
bool MainWindow::saveFile(const QString &path)
{
    QDir::setCurrent(path);
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        QMessageBox::warning(this, tr("Cannot save file"),
                             tr("Cannot write to file %1:\n%2.")
                             .arg(path)
                             .arg(file.errorString()));
        return false;
    }

    QByteArray ba;
    m_sceneManager->write(ba);
    file.write( ba );

    m_physicalFile = true;
    m_currentFile.setFile(path);
    this->statusBar()->showMessage(tr("File saved"), 2000);
    this->setClean();
    return true;
}

/******************************************************************************
 ******************************************************************************/
bool MainWindow::loadFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Couldn't open file.");
        QMessageBox::warning(this, tr("Error"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(path)
                             .arg(file.errorString()));
        return false;
    }
    bool ok;
    QByteArray data = file.readAll();
    m_sceneManager->read(data, &ok);
    if (!ok) {
        qCritical("Couldn't parse AGW file.");
        QMessageBox::warning(this, tr("Error"),
                             tr("Error found in the AGW file:\n"
                                "%1\n")
                             .arg(path));
    }

    m_physicalFile = true;
    m_currentFile = path;
    this->statusBar()->showMessage(tr("File loaded"), 5000);
    this->setClean();
    return true;
}

/******************************************************************************
 ******************************************************************************/
void MainWindow::on_action_SimpleWorld_triggered()
{
    if (maybeSave()) {
        loadFile(":/examples/SimpleWorld.agw");
    }
}

