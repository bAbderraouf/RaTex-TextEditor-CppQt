#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "settingsinfodialog.h"
#include "document.h"

#include <QMainWindow>
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QDebug>
#include <Qfile>
#include <QTextStream>
#include <QTextDocument>
#include <QPainter>
#include <QPdfWriter>
#include <QPrinter>
#include <QTextCursor>
#include <QList>

#include <QTabWidget>
#include <QTextEdit>
#include <QFileInfo>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QSize sizeHint() const;
    ~MainWindow();



    enum class enExportFileType{ TxtExport = 0, PdfExport = 1, HtmlExport = 2, RtfExport = 3};

    enum class enInputFileType{  TxtInput = 0 , HtmlInput = 1};

    void saveTextToFile(QString const &filePath, QString const &  text , enExportFileType ExportType = enExportFileType::TxtExport);

    QString readContentFromTextFile(QString const &filePath);

    void init();


    // automatic color for visible text/cursor (different bgs)

    QString GetCursorColorName();

    QColor GetTextColor();

    void setupSignalSlotsConnections(void);

    void updatePdfExportFormatSetings(QPrinter &printer);

    void newFileAction(void);

    void openFileAction(void);

    void saveFileAction(void);

    void saveAsPdfAction(void);

    void saveAsHtmlAction(void);

    void quitAction(void);

    void copyAction(void);

    void cutAction(void);

    void pasteAction(void);

    void undoAction(void);

    void redoAction(void);

    void aboutAction(void);

    void selectAllAction(void);

    void settingsAction(void);

    void transparentAction(void);

    void showToolbarAction(void);

    void showStatusBarAction(void);

    void fontAction(void);

    void textColorAction(void);

    void cursorPositionChanged(void); // not an aciton

    void updateCursorPosition(void);

    void updateWindowOpacity(void);

    void writeCursorPosition(void);

    void changeTab(void);

    void closeTab(void);

    void acceptSettingsClicked();  // signal custom quand le bouton Accept est cliqué

    void NewTab(QString FileName, enInputFileType FileType, QString text = "");

    QString GetCurrentTabName();

    //QString GetNewTabName(QString fileName);

    enInputFileType GetInputFileType(QFileInfo FileInfo);

private slots:


    void on_removeQuitFromToolbar_toggled(bool isSelected);

    void on_removeSettingsFromToolbar_toggled(bool isSelected);

    void on_removeAboutFromToolbar_toggled(bool isSelected);

    void on_removeActionZoomInFromTollbar_toggled(bool isSelected);

    void on_removeText_colorFromToolbar_toggled(bool isSelected);

    void on_removeActionFontFromToolbar_toggled(bool isSelected);

    void on_removeActionRedoFromToolbar_toggled(bool isSelected);

    void on_removeActionUndoFromToolbar_toggled(bool isSelected);

    void on_removeActionSelect_AllFromtoolbar_toggled(bool isSelected);

    void on_removeactionPasteFromToolbar_toggled(bool isSelected);

    void on_removeActionCutFromToolbar_toggled(bool isSelected);

    void on_removeActionCopyFromToolbar_toggled(bool isSelected);

    void on_removeExport_as_PDF_file_fromToolbar_toggled(bool isSelected);

    void on_removeOpenFileFromToolbar_toggled(bool isSelected);

    void on_removeSaveFileFromToolbar_toggled(bool isSelected);

    void on_removeTransparentModeFromToolbar_toggled(bool isSelected);

    void on_removeActionZoomOutFromTollbar_toggled(bool isSelected);

    void on_actionzoomIn_triggered();

    void on_actionzoom_out_triggered();

    void on_TabWidget_currentChanged(int index);

    void on_TabWidget_TabCloseRequested(int index);

    void on_SettingsAccepted();

    void updateCurrentEditStyle();

    void UpdteCurrentDocumentSettings();

    void SetCurrentDocumentSettings(SettingsInfoDialog::Settings CurrentSetings_);



private:

    Ui::MainWindow *ui;

    QList<QTextEdit*> textEditList;

    QList<document*> DocList;

    QTabWidget *TabWidget;

    int CurrentTabIdx;

    SettingsInfoDialog * settings;

    SettingsInfoDialog::Settings CurrentSettings;


    // cursor position

    QTextCursor  cursor;

    int idxLine;

    int idxColumn;

    QString defaultStyleSheet, transparentStyleSheet;

    QFont defaultFont;

    bool    flag_transparent,
            flag_showToolBar,
            flag_showMenuBar,
            flag_showStatusBar;



};
#endif // MAINWINDOW_H
