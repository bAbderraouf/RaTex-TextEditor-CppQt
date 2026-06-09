#ifndef SETTINGSINFODIALOG_H
#define SETTINGSINFODIALOG_H

#include <QDialog>
#include <QColorDialog>
#include <QDebug>

namespace Ui {
    class SettingsInfoDialog;
}

class SettingsInfoDialog : public QDialog
{
    Q_OBJECT

public:

    struct Settings {

        QString PdfExportFormat;
        bool    NoWrapLines;
        double  Opacity;
        QColor  BgColorInTranparentMode;
        QColor  BgColor;
    };

    static Settings DefaultValues;

    explicit SettingsInfoDialog(QWidget *parent = nullptr);

    ~SettingsInfoDialog();

    QString getPdfExportForamt() ;

    bool getNoWrapLines() ;

    float getOpacity();

    QColor getBagroundColorInTranparentMode();

    QColor getBagroundColor();

    void SetSettings(Settings CurrentDocSettings);

private slots:

    void on_cancelPushButton_2_clicked();

    void on_okPushButton_clicked();

    void on_pushButton_clicked();

    void on_selectBgColor_clicked();

private:
    Ui::SettingsInfoDialog *ui;

    QString pdfExportForamt;

    bool   noWrapLines;

    QColor bagroundColorInTranparentMode;

    QColor bagroundColor;

signals:
    void acceptSettingsClicked();
};

#endif // SETTINGSINFODIALOG_H
