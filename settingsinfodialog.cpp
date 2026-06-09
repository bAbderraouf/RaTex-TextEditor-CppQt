#include "settingsinfodialog.h"
#include "ui_settingsinfodialog.h"

SettingsInfoDialog::SettingsInfoDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsInfoDialog)
{
    ui->setupUi(this);

    // init
    ui->pdfFormatComboBox->addItem("A1");
    ui->pdfFormatComboBox->addItem("A2");
    ui->pdfFormatComboBox->addItem("A3");
    ui->pdfFormatComboBox->addItem("A4");
    ui->pdfFormatComboBox->setEditable(false);


    // default values
    ui->pdfFormatComboBox->setCurrentText(DefaultValues.PdfExportFormat);
    ui->noWrapCheckbox->setChecked(DefaultValues.NoWrapLines);
    bagroundColorInTranparentMode = DefaultValues.BgColorInTranparentMode;
    bagroundColor = DefaultValues.BgColor;
    ui->opacityDoubleSpinBox->setValue(DefaultValues.Opacity);

    // init variables
    pdfExportForamt = ui->pdfFormatComboBox->currentText();
    noWrapLines     = ui->noWrapCheckbox->isChecked();

    //emettre le signal accept settings
    // Quand le bouton est cliqué, on émet notre signal acceptClicked
      connect(ui->okPushButton, &QPushButton::clicked, this, [=](){
            emit acceptSettingsClicked(); // <-- c’est ici qu’on émet le signal
        });
}

SettingsInfoDialog::~SettingsInfoDialog()
{
    delete ui;
}


QString SettingsInfoDialog::getPdfExportForamt()
{
    pdfExportForamt = ui->pdfFormatComboBox->currentText();
    return pdfExportForamt;
}

bool SettingsInfoDialog::getNoWrapLines()
{
    noWrapLines = ui->noWrapCheckbox->isChecked();
    return noWrapLines;
}

float SettingsInfoDialog::getOpacity()
{
    return ui->opacityDoubleSpinBox->value();
}

QColor SettingsInfoDialog::getBagroundColorInTranparentMode()
{
    return bagroundColorInTranparentMode;
}

QColor SettingsInfoDialog::getBagroundColor()
{
    return bagroundColor;
}

void SettingsInfoDialog::SetSettings(Settings CurrentDocSettings)
{
    this->pdfExportForamt = CurrentDocSettings.PdfExportFormat;
    this->noWrapLines = CurrentDocSettings.NoWrapLines;
    this->bagroundColor = CurrentDocSettings.BgColor;
    this->bagroundColorInTranparentMode = CurrentDocSettings.BgColorInTranparentMode;

    this->ui->opacityDoubleSpinBox->setValue(CurrentDocSettings.Opacity);
    this->ui->pdfFormatComboBox->setCurrentText(pdfExportForamt);
    this->ui->noWrapCheckbox->setChecked(noWrapLines);
}


void SettingsInfoDialog::on_cancelPushButton_2_clicked()
{
    this->reject();
}


void SettingsInfoDialog::on_okPushButton_clicked()
{
    noWrapLines = ui->noWrapCheckbox->isChecked();
    pdfExportForamt = ui->pdfFormatComboBox->currentText();

    this->accept();
}


void SettingsInfoDialog::on_pushButton_clicked()
{
    //select color
    QColor const selectedColor = QColorDialog::getColor(bagroundColorInTranparentMode,this, "Select a color");

    qDebug() << "selected color " << selectedColor;

    if(selectedColor.isValid())
    {
        //set new color
        bagroundColorInTranparentMode = selectedColor;
    }

}

void SettingsInfoDialog::on_selectBgColor_clicked()
{
    //select color
    QColor const selectedColor = QColorDialog::getColor(bagroundColor,this, "Select a color");

    qDebug() << "selected color " << selectedColor;

    if(selectedColor.isValid())
    {
        //set new color
        bagroundColor = selectedColor;
    }

}

// default values
SettingsInfoDialog::Settings   SettingsInfoDialog::DefaultValues = {
    "A4",       // pdfExportFormat
    false,      // no wrap lines
    0.5f,       // opacity
    Qt::black,  // bg color transparent mode
    Qt::white,  // bg color
};

