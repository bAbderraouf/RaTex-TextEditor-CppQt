#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QWidget>
#include <QTextEdit>
#include "settingsinfodialog.h"

class document : public QWidget
{
private :
    // settings   // externaly calculated
    QString PdfExportFormat_;
    bool    NoWrapLines_;
    double  Opacity_;
    QColor  BgColorInTranparentMode_;
    QColor  BgColor_;

    // cursor position    // internaly calculated
    QTextCursor Cursor_;
    int         IdxLine_;
    int         IdxColumn_;

    //falgs         // externaly calculated
    bool flag_IsSaved_;
    bool flag_IsTransparent_;

    //Text Edit
    QTextEdit   *TextEdit_;
    //QString     TabName_;
    QString     DefaultStyle_;
    QString     TransparentDefaultStyle_;
    int         TabIndex_;
    QColor      TextColor_;
    QFont       Font_;


public:
    document(QString DefaultStyle, QFont DefautlFont, int TabIndex);
    ~document();

    // getters
    bool IsSaved();
    bool IsTransparent();
    //QString GetTabName();
    int GetTabIndex();
    int GetCursorXPos();
    int GetCursorYPos();
    QColor GetBgColor();
    QColor GetBgColorInTransparentMode();
    QColor GetTextColor();
    QFont GetFont();
    double GetOpacity();
    bool IsWrapLines();
    QString GetPdfExportFormat();
    QTextEdit * GetTextEdit();
    SettingsInfoDialog::Settings GetSettings();


    void SetSaved(bool IsSaved);
    void SetTransparent(bool IsTransparent);
    //void SetTabName(QString TabName);
    void SetBgColor(QColor BgColor);
    void SetBgColorInTransparentMode(QColor BgTrModeColor);
    void SetOpacity(double Opacity);
    void SetWraplines(bool IsWrapLines);
    void SetPdfExportFormat(QString PdfFormat);
    void SetTextEdit(QTextEdit *TextEdit);
    void SetStyleSheet(QString NewStyle);
    void SetTextColor(QColor NewTxtColor);
    void SetFont(QFont NewFont);
    void DeleteTextEdit();
    void UpdateTextEditStyle();
    void SetSettings(SettingsInfoDialog::Settings DocSettings);
};

#endif // DOCUMENT_H


