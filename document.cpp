#include "document.h"
#include "settingsinfodialog.h"


document::document(QString DefaultStyle, QFont DefautlFont,  int TabIndex){


    //Text Edit
    Font_                   =  DefautlFont;
    TextColor_              =  QColor(Qt::black); // default txt color
    TextEdit_               =  new QTextEdit;
    TextEdit_->setFont(Font_);
    TextEdit_->setAcceptRichText(true); // pour recupere des copies avec couleur


    // TabName_             =  TabName;
    DefaultStyle_           =  DefaultStyle;
    TransparentDefaultStyle_=  DefaultStyle;
    TabIndex_               =  TabIndex;

    // settings   // externaly calculated
    PdfExportFormat_        =  SettingsInfoDialog::DefaultValues.PdfExportFormat;
    NoWrapLines_            =  SettingsInfoDialog::DefaultValues.NoWrapLines;
    Opacity_                =  SettingsInfoDialog::DefaultValues.Opacity;
    BgColor_                =  SettingsInfoDialog::DefaultValues.BgColor;
    BgColorInTranparentMode_=  SettingsInfoDialog::DefaultValues.BgColorInTranparentMode;

    // cursor position    // internaly calculated
    Cursor_                 =  TextEdit_->textCursor();
    IdxLine_                =  0; // Cursor_.blockNumber() + 1;
    IdxColumn_              =  0; // Cursor_.positionInBlock()+1;

    //falgs         // externaly calculated
    flag_IsSaved_           =  true;
    flag_IsTransparent_     =  false;
}

document::~document()
{
    delete TextEdit_;
    TextEdit_ = nullptr;
}

// getters
bool document::IsSaved()
{
    return flag_IsSaved_;
}

bool document::IsTransparent()
{
    return flag_IsTransparent_;
}


int document::GetTabIndex(){

    return TabIndex_;
}

int document::GetCursorXPos(){

    Cursor_ =  TextEdit_->textCursor();

    return Cursor_.positionInBlock()+1;
}

int document::GetCursorYPos(){

    Cursor_  =  TextEdit_->textCursor();

    return Cursor_.blockNumber() + 1;
}

QColor document::GetBgColor(){

    return BgColor_;
}

QColor document::GetBgColorInTransparentMode(){

    return BgColorInTranparentMode_;
}

QColor document::GetTextColor()
{
    return TextColor_;
}

QFont document::GetFont()
{
    return Font_;
}

double document::GetOpacity(){

    return Opacity_;
}

bool document::IsWrapLines(){

    return !NoWrapLines_;
}

QString document::GetPdfExportFormat(){

    return PdfExportFormat_;
}

QTextEdit * document::GetTextEdit(){

    return  TextEdit_;
}

SettingsInfoDialog::Settings document::GetSettings()
{

    return SettingsInfoDialog::Settings {
                                            GetPdfExportFormat(),
                                            !IsWrapLines(),
                                            GetOpacity(),
                                            GetBgColorInTransparentMode(),
                                            GetBgColor()
                                                            };
}


// setters
void document::SetSaved(bool IsSaved){

    flag_IsSaved_ = IsSaved;
}

void document::SetTransparent(bool IsTransparent){

    flag_IsTransparent_ = IsTransparent; //<***ToCheck if ne weed to update here (no need cause w eexport textedit pointer)
}

void document::SetBgColor(QColor BgColor){

    BgColor_ = BgColor;
    //UpdateTextEditStyle(); // to apply new colors
}

void document::SetBgColorInTransparentMode(QColor BgTrModeColor){

    BgColorInTranparentMode_ = BgTrModeColor;
    //UpdateTextEditStyle(); // to apply new colors
}

void document::SetOpacity(double Opacity){

    Opacity_ = Opacity;
}

void document::SetWraplines(bool IsWrapLines){

    NoWrapLines_ = !IsWrapLines;

    if(NoWrapLines_)
        TextEdit_->setLineWrapMode(QTextEdit::NoWrap);
    else
        TextEdit_->setLineWrapMode(QTextEdit::WidgetWidth);
}

void document::SetPdfExportFormat(QString PdfFormat){

    PdfExportFormat_ = PdfFormat;
}

void document::SetTextEdit(QTextEdit *TextEdit){

    this->TextEdit_ = TextEdit;
}

void document::SetStyleSheet(QString NewStyle)
{
    this->TextEdit_->setStyleSheet(NewStyle);
}

void document::SetTextColor(QColor NewColor)
{
    TextColor_ = NewColor;
    this->TextEdit_->setTextColor(NewColor);
}

void document::SetFont(QFont NewFont)
{
    Font_ = NewFont;

    // apply font to text format
    QTextCharFormat format;
    format.setFont(NewFont);

    // apply font to next characters
    this->TextEdit_->mergeCurrentCharFormat(format);
}

void document::DeleteTextEdit()
{
    delete TextEdit_;
    TextEdit_ = nullptr;
}

void document::UpdateTextEditStyle()
{

    QString BgColor = QString("background: %1;").arg(BgColor_.name());
    QString BgColorTransparentMode  = QString("background: %1;").arg(BgColorInTranparentMode_.name());
    QString TextColor = QString("color : %1;").arg(TextColor_.name());

    QString nextStyle =  flag_IsTransparent_ ? BgColorTransparentMode : BgColor + TextColor;

    TextEdit_->setStyleSheet(nextStyle);

    /*
    if(flag_transparent){

        // Rendre le fond du texte transparent

        QString nextStyle = QString("background: %1; color: darkgray; border: none; ").arg(bagroundColorInTranparentMode.name());

        DocList[CurrentTabIdx]->SetStyleSheet(nextStyle);

        // adapte text style according to new background (on conserve le background)
        DocList[CurrentTabIdx]->SetStyleSheet(nextStyle + GetCursorColorName());
        DocList[CurrentTabIdx]->SetTextColor(GetTextColor());
    }
    else {

        //QString nextStyle = "background: white; color: black; border: 1px solid gray;" ;
        QString nextStyle = QString("background: %1; color: black; border: none; ").arg(bagroundColor.name());


        DocList[CurrentTabIdx]->SetStyleSheet(nextStyle);

        // adapte text style according to new background (on conserve le background)
        DocList[CurrentTabIdx]->SetStyleSheet(nextStyle + GetCursorColorName());
        DocList[CurrentTabIdx]->SetTextColor(GetTextColor());

    }
    */
}

void document::SetSettings(SettingsInfoDialog::Settings DocSettings)
{
    NoWrapLines_        = DocSettings.NoWrapLines;
    BgColor_            = DocSettings.BgColor;
    Opacity_            = DocSettings.Opacity;
    PdfExportFormat_    = DocSettings.PdfExportFormat;
    BgColorInTranparentMode_ = DocSettings.BgColorInTranparentMode;
}


