#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //init setting info dialog
    init();

    setupSignalSlotsConnections();

}

QSize MainWindow::sizeHint() const
{
    return QSize(800,800);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete settings;
}

//---------------------------------------------------
//             setupSignalSlotsConnections
//---------------------------------------------------
void MainWindow::setupSignalSlotsConnections()
{
    //new file
    newFileAction();

    //open
    openFileAction();

    //save file
    saveFileAction();

    //export pdf file
    saveAsPdfAction();

    //export to html file
    saveAsHtmlAction();

    //quit
    quitAction();

    //copy
    copyAction();

    //cut
    cutAction();

    //paste
    pasteAction();

    //undo
    undoAction();

    //redo
    redoAction();

    //about
    aboutAction();

    //select all
    selectAllAction();

    //settings
    settingsAction();

    // cursor position
    cursorPositionChanged();

    // transparent
    transparentAction();

    // toolbar
    showToolbarAction();

    //stausbar
    showStatusBarAction();

    //font
    fontAction();

    // text color
    textColorAction();

    // change tab idx
    changeTab();

    //close tab
    closeTab();
}

//---------------------------------------------------
//             update TextEdit WrapMode (settings)
//---------------------------------------------------
void MainWindow::updateTextEditWrapMode()
{
    if(noWrapLines)
    {
        // pas de saut de lignes automatique
        textEditList[CurrentTabIdx]->setLineWrapMode(QTextEdit::NoWrap);
    }
    else
    {
        //saut automatique de lignes
        textEditList[CurrentTabIdx]->setLineWrapMode(QTextEdit::WidgetWidth);
    }
}

//---------------------------------------------------
//          updatePdfExportFormatSetings
//---------------------------------------------------
void MainWindow::updatePdfExportFormatSetings(QPrinter &printer)
{
    // apply pdfExportFormat from settings
    if(pdfExportForamt == "A1")
        printer.setPageSize(QPageSize(QPageSize::A1));
    else if(pdfExportForamt == "A2")
        printer.setPageSize(QPageSize(QPageSize::A2));
    else if(pdfExportForamt == "A3")
        printer.setPageSize(QPageSize(QPageSize::A3));
    else if(pdfExportForamt == "A4")
        printer.setPageSize(QPageSize(QPageSize::A4));
}

void MainWindow::newFileAction()
{
    connect(ui->actionNew_File, &QAction::triggered, [=]()
    {
        // create a new tab
        NewTab("New File", enInputFileType::TxtInput);
    });

}

//---------------------------------------------------
//             open file
//---------------------------------------------------
void MainWindow::openFileAction()
{
    connect(ui->actionOpen, &QAction::triggered, [=]()
            {

                QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "C:/Users/Hp_7/Desktop/Ratex/" , "Doc (*.txt *.html);;Text (*.txt);; Html(*.html)");

                QString text = readContentFromTextFile(filePath);

                QFileInfo fileInfo(filePath);
                QString FileName = fileInfo.baseName();

                // get input file extension
                enInputFileType FileType = GetInputFileType(fileInfo);

                if(!text.isEmpty())
                {
                    // create a new tab
                    NewTab(FileName, FileType, text);
                }
            });}

//---------------------------------------------------
//             saveFileAction
//---------------------------------------------------
void MainWindow::saveFileAction()
{
    connect(ui->actionSave, &QAction::triggered, [=]()
            {

                // capture text from CurrentTextEdit
                QString text = textEditList[CurrentTabIdx]->toPlainText();

                // get output file name
                QString CurrentDocName = "C:/Users/Hp_7/Desktop/Ratex/" + GetCurrentTabName() + ".txt";
                QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), CurrentDocName, tr("Text (*.txt)"));

                if(!fileName.isEmpty())
                    saveTextToFile(fileName, text);
            });

}

//---------------------------------------------------
//             saveAsPdfAction
//---------------------------------------------------
void MainWindow::saveAsPdfAction()
{
    connect(ui->actionExport_as_PDF, &QAction::triggered, [=]()
            {

                // capture text from CurrentTextEdit
                QString text = textEditList[CurrentTabIdx]->toHtml(); // toPlaintext() : text pure

                // get output file name
                QString CurrentDocName = "C:/Users/Hp_7/Desktop/Ratex/" + GetCurrentTabName() + ".pdf";

                QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), CurrentDocName, tr("PDF (*.pdf)"));

                if(!fileName.isEmpty())
                    saveTextToFile(fileName, text, enExportFileType::PdfExport);
    });
}

void MainWindow::saveAsHtmlAction()
{
    connect(ui->actionExport_as_Html_file, &QAction::triggered, [=]()
            {

                // capture text from CurrentTextEdit
                QString text = textEditList[CurrentTabIdx]->toHtml(); // toPlaintext() : text pure

                // get output file name
                QString CurrentDocName = "C:/Users/Hp_7/Desktop/Ratex/" + GetCurrentTabName() + ".html";
                QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),CurrentDocName, tr("Html (*.html)"));

                if(!fileName.isEmpty())
                    saveTextToFile(fileName, text, enExportFileType::HtmlExport);
    });
}

//---------------------------------------------------
//             quitAction
//---------------------------------------------------
void MainWindow::quitAction()
{
    connect(ui->actionQuit, &QAction::triggered, [=](){
        QApplication::quit();   });
}

//---------------------------------------------------
//             copyAction
//---------------------------------------------------
void MainWindow::copyAction()
{
    connect(ui->actionCopy, &QAction::triggered, [=](){
           textEditList[CurrentTabIdx]->copy();  });
}

//---------------------------------------------------
//             cutAction
//---------------------------------------------------
void MainWindow::cutAction()
{
    connect(ui->actionCut, &QAction::triggered, [=](){
        textEditList[CurrentTabIdx]->cut();  });
}

//---------------------------------------------------
//             pasteAction
//---------------------------------------------------
void MainWindow::pasteAction()
{
    connect(ui->actionPaste, &QAction::triggered, [=](){
        textEditList[CurrentTabIdx]->paste();  });

}

//---------------------------------------------------
//            undoAction
//---------------------------------------------------
void MainWindow::undoAction()
{
    connect(ui->actionUndo, &QAction::triggered, [=](){
        textEditList[CurrentTabIdx]->undo();  });

}

//---------------------------------------------------
//            redoAction
//---------------------------------------------------
void MainWindow::redoAction()
{
    connect(ui->actionRedo, &QAction::triggered, [=](){
        textEditList[CurrentTabIdx]->redo();  });
}

//---------------------------------------------------
//             aboutAction
//---------------------------------------------------
void MainWindow::aboutAction()
{
    connect(ui->actionAbout, &QAction::triggered, [=](){
        QString msg = "RateX is a rich text editor.\n\n";
        msg.append( "Developer: Abderraouf Bousri\n");
        msg.append("Contact:\nabderraouf.bousri@gmail.com");
        QMessageBox::information(this, "About", msg , QMessageBox::Ok); });
}

//---------------------------------------------------
//             Seclect All action
//---------------------------------------------------
void MainWindow::selectAllAction()
{
    connect(ui->actionSelectAll, &QAction::triggered, [=](){
        textEditList[CurrentTabIdx]->selectAll();  });
}

//---------------------------------------------------
//             Settings action
//---------------------------------------------------
void MainWindow::settingsAction()
{
    connect(ui->settingsAction, &QAction::triggered, [=]()
    {

        int res = settings->exec();

        // accepted setting
        if(res == QDialog::Accepted)
        {
            pdfExportForamt = settings->getPdfExportForamt();
            noWrapLines = settings->getNoWrapLines();
            opacity = settings->getOpacity();
            bagroundColorInTranparentMode = settings->getBagroundColorInTranparentMode();
            bagroundColor = settings->getBagroundColor();

            // update CurrentTextEdit settings
            updateTextEditWrapMode();

            //update opacity
            updateWindowOpacity();

            updateCurrentEditStyle();

        }
    });
}

void MainWindow::transparentAction()
{
    connect(ui->actionTransparent , &QAction::toggled , [=](){

        flag_transparent = ! flag_transparent;

        if(flag_transparent)
        {
            ui->toolBar->update();

            //this->setAttribute(Qt::WA_TranslucentBackground);//transparent window
            this->setWindowFlags( Qt::Window);
            this->setWindowOpacity(opacity); // Réglage global de l’opacité


            // Rendre le fond du texte transparent

            QString nextStyle = QString("background: %1; color: darkgray; border: none; ").arg(bagroundColorInTranparentMode.name());

            textEditList[CurrentTabIdx]->setStyleSheet(nextStyle);

            // adapte text style according to new background (on conserve le background)
            textEditList[CurrentTabIdx]->setStyleSheet(nextStyle + GetCursorColorName());
            textEditList[CurrentTabIdx]->setTextColor(GetTextColor());


            this->hide();
            this->show();  // Très important sinon la fenêtre reste cachée

        }
        else
        {
            // Revenir au style normal (ex: bouton "Désactiver Style Custom")
            this->setAttribute(Qt::WA_TranslucentBackground, false);  // Désactive la transparence
            this->setWindowFlags( Qt::Window);            // Restaure les bordures
            this->setWindowOpacity(1.0);                  // Opaque

            // Restaure un style normal pour le QTextEdit

            //QString nextStyle = "background: white; color: black; border: 1px solid gray;" ;
            QString nextStyle = QString("background: %1; color: black; border: none; ").arg(bagroundColor.name());


            textEditList[CurrentTabIdx]->setStyleSheet(nextStyle);

            // adapte text style according to new background (on conserve le background)
            textEditList[CurrentTabIdx]->setStyleSheet(nextStyle + GetCursorColorName());
            textEditList[CurrentTabIdx]->setTextColor(GetTextColor());


            this->hide();
            this->show(); // Important pour réappliquer les flags

        }
    });
}

void MainWindow::showToolbarAction()
{
    connect(ui->actionShow_Tool_bar , &QAction::toggled , [=](){

         flag_showToolBar = !flag_showToolBar;

          // show/ hide toolbar
         for(QToolBar * bar: findChildren<QToolBar*>())
             flag_showToolBar ? bar->show() : bar->hide();
    });
}


void MainWindow::showStatusBarAction()
{
    connect(ui->actionShow_statusbar , &QAction::toggled , [=](){

        flag_showStatusBar = !flag_showStatusBar;

        // show / hide status bar
        flag_showStatusBar ?  ui->statusbar->show() : ui->statusbar->hide();
    });
}

void MainWindow::fontAction()
{

    connect(ui->actionFont , &QAction::triggered , [=]()
    {
        bool ok = false;
        // select a font
        QFont  textEditFont = QFontDialog::getFont(&ok, QFont("Select your font"));

        // apply font to text format
        QTextCharFormat format;
        format.setFont(textEditFont);

        //set selected font
        if(ok)
        {
            // if any text selected
            if(textEditList[CurrentTabIdx]->textCursor().hasSelection())
            {
                // apply font to selected text

                // get cursor position
                QTextCursor cursor = textEditList[CurrentTabIdx]->textCursor();

                cursor.mergeCharFormat(format);
            }
            else
            {
                // apply font to next characters
                textEditList[CurrentTabIdx]->mergeCurrentCharFormat(format);
            }
        }
    });
}

void MainWindow::textColorAction()
{
    connect(ui->actionColor , &QAction::triggered , [=]()
            {
               // capture color
                QPalette pal = textEditList[CurrentTabIdx]->palette();
                QColor initialTextColor = pal.color(QPalette::Text);

                //select color
                QColor const selectedColor = QColorDialog::getColor(initialTextColor,this, "Select a color");

                if(selectedColor.isValid())
                {
                    //set new text color
                    textEditList[CurrentTabIdx]->setTextColor(selectedColor);
                }
            });
}

//---------------------------------------------------
//          cursorPositionChanged
//---------------------------------------------------
void MainWindow::cursorPositionChanged()
{
    connect(textEditList[CurrentTabIdx], &QTextEdit::cursorPositionChanged, [=](){
        updateCursorPosition();
    } );

}

//---------------------------------------------------
//          updateCursorPosition
//---------------------------------------------------
void MainWindow::updateCursorPosition()
{
    if(CurrentTabIdx != -1 && CurrentTabIdx < textEditList.size())
    {
        cursor = textEditList[CurrentTabIdx]->textCursor();
        idxLine = cursor.blockNumber() + 1;
        idxColumn = cursor.positionInBlock() + 1; // starts from 0

        writeCursorPosition();
    }

}

void MainWindow::updateWindowOpacity()
{
    if(flag_transparent)
        this->setWindowOpacity(opacity);
}


void MainWindow::updateCurrentEditStyle()
{
        if(flag_transparent){

            // Rendre le fond du texte transparent

            QString nextStyle = QString("background: %1; color: darkgray; border: none; ").arg(bagroundColorInTranparentMode.name());

            textEditList[CurrentTabIdx]->setStyleSheet(nextStyle);

            // adapte text style according to new background (on conserve le background)
            textEditList[CurrentTabIdx]->setStyleSheet(nextStyle + GetCursorColorName());
            textEditList[CurrentTabIdx]->setTextColor(GetTextColor());
        }
        else {

            //QString nextStyle = "background: white; color: black; border: 1px solid gray;" ;
            QString nextStyle = QString("background: %1; color: black; border: none; ").arg(bagroundColor.name());


            textEditList[CurrentTabIdx]->setStyleSheet(nextStyle);

            // adapte text style according to new background (on conserve le background)
            textEditList[CurrentTabIdx]->setStyleSheet(nextStyle + GetCursorColorName());
            textEditList[CurrentTabIdx]->setTextColor(GetTextColor());

        }
}

//---------------------------------------------------
//          writeCursorPosition
//---------------------------------------------------
void MainWindow::writeCursorPosition()
{
    QString strCursorPos = "Line " + QString::number(idxLine) + ", Col " + QString::number(idxColumn) + ".";
    strCursorPos.append("           |  RaTex by : A.Bousri.");
    ui->statusbar->showMessage(strCursorPos);
}

//---------------------------------------------------
// change tab in tabwiget
//---------------------------------------------------
void MainWindow::changeTab()
{
    // 2- connect the signal currentChanged of cursor to slot
            connect(TabWidget, &QTabWidget::currentChanged,
                    this, &MainWindow::on_TabWidget_currentChanged);

}

//---------------------------------------------------
// close tab in tabwiget
//---------------------------------------------------
void MainWindow::closeTab()
{
    connect(TabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::on_TabWidget_TabCloseRequested);
}

void MainWindow::acceptSettingsClicked()
{
    connect(settings, &SettingsInfoDialog::acceptSettingsClicked,this, &MainWindow::on_SettingsAccepted);
}

void MainWindow::NewTab(QString FileName, enInputFileType FileType,  QString text)
{

    //1- create a new tab
    QTextEdit * NewEditor = new QTextEdit;
    NewEditor->setFont(defaultFont);

    textEditList.push_back(NewEditor);
    CurrentTabIdx=textEditList.size()-1;

    if(FileType == enInputFileType::TxtInput)
        textEditList[CurrentTabIdx]->setText(text);
    if(FileType == enInputFileType::HtmlInput)
        textEditList[CurrentTabIdx]->setHtml(text);

    // get new/open tab name
   // QString NewTabName = GetNewTabName(FileName); //<<****ToDo

    TabWidget->addTab(NewEditor , FileName);
    TabWidget->setCurrentIndex(CurrentTabIdx);
    TabWidget->setStyleSheet("background-color: white;");


    // update cursor position
    updateCursorPosition();

    // 2- connect the current tab curosr pos changed to slot
    cursorPositionChanged();


}

QString MainWindow::GetCurrentTabName()
{
    QString currentName = TabWidget->tabText(TabWidget->currentIndex());
    return currentName;
}

/*
    QString MainWindow::GetNewTabName(QString fileName)
    {

    }
*/

MainWindow::enInputFileType MainWindow::GetInputFileType(QFileInfo FileInfo)
{
    QString FileType = FileInfo.QFileInfo::completeSuffix();

    if (FileType == "txt")
        return enInputFileType::TxtInput;
    if(FileType == "html")
        return enInputFileType::HtmlInput;

    return enInputFileType::TxtInput;
}

//---------------------------------------------------
//          saveTextToFile
//---------------------------------------------------
void MainWindow::saveTextToFile(QString const &filePath, QString const & text , enExportFileType ExportType  )
{
    // define file full path
    QFile outputFile = filePath;

    if(ExportType == enExportFileType::PdfExport) // save pdf file
    {
        // a formated object wich contains text
        QTextDocument doc;
         // doc.setPlainText(text);  // text pure
        doc.setHtml(text);

        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);

        // apply pdfExportFormat from settings
        updatePdfExportFormatSetings(printer);

        printer.setOutputFileName(filePath);
        printer.setFontEmbeddingEnabled(true);

        doc.print(&printer);

    }
    else if(ExportType == enExportFileType::TxtExport)  // save text file
    {
        //open the file and write it
        if(outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream outStream(&outputFile);
            outStream << text;
            outputFile.close();
        }
        else
        {
            qDebug() << "impossible d'ouvrir le fichier";
        }
    }
    else if(ExportType == enExportFileType::HtmlExport)
    {
        //open the file and write it
        if(outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            // html file
            QTextStream outStream(&outputFile);
            outStream << text;
            //outStream << textEditList[CurrentTabIdx]->toHtml();
            outputFile.close();
        }
        else
        {
            qDebug() << "impossible d'ouvrir le fichier";
        }
    }
}

//---------------------------------------------------
//          readContentFromTextFile
//---------------------------------------------------
QString MainWindow::readContentFromTextFile(QString const &filePath)
{
    // define file full path
    QFile inputFile = filePath;
    QString text = "";

    //open the file and write it
    if(inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream inStream(&inputFile);
        text = inStream.readAll();
        inputFile.close();
    }
    else
    {
        //QMessageBox::critical(this, "Import error!", "Could not open the file!", QMessageBox::Ok);
    }
    return text;
}

void MainWindow::init()
{

    // default style
    defaultStyleSheet       = this->styleSheet();
    transparentStyleSheet   = "";

    // layout central
    QVBoxLayout *Layout = new QVBoxLayout(ui->centralwidget);
    Layout->setContentsMargins(0,0,0,0); // no margins
    Layout->setSpacing(0); // no space between widgets

    // add a widget as background for central widget
    QWidget * ParentCentralWidget = new QWidget;
    ParentCentralWidget->setLayout(Layout);
    Layout->addWidget(ParentCentralWidget);


    defaultFont = QFont("Consolas", 12);
    defaultFont.setStyleHint(QFont::Monospace);
    defaultFont.setFixedPitch(true);

    // new tab and new text editor
    CurrentTabIdx = 0;
    QTextEdit * editor = new QTextEdit;
    editor->setFont(defaultFont);
    editor->setAcceptRichText(true); // pour recupere des copies avec couleur
    textEditList.push_back(editor);

    // new document
    document *NewDoc = new document( defaultStyleSheet , defaultFont, CurrentTabIdx);
    DocList.push_back(NewDoc);

    // tab widgets
    TabWidget = new QTabWidget(ParentCentralWidget);
    TabWidget->setTabsClosable(true);
    TabWidget->setTabShape(QTabWidget::TabShape::Triangular);
    Layout->addWidget(TabWidget);

    this->setCentralWidget(ParentCentralWidget);

    TabWidget->addTab(NewDoc->GetTextEdit(), "New File");
    TabWidget->setCurrentWidget(NewDoc->GetTextEdit());//(editor);


    // fenetre avec bg transparent
    this->setAttribute(Qt::WA_TranslucentBackground);

    // default background
    ui->toolBar->setStyleSheet("background: white;");
    ui->statusbar->setStyleSheet("background: white;");
    ParentCentralWidget->setStyleSheet("background: white;");
    TabWidget->setStyleSheet("background:white;");


    TabWidget->setStyleSheet(R"(
                                QTabWidget { background-color: white;
                                                    margin:0px; border:0px ;}        /* fond général */
                                QTabWidget::pane { background-color: white;
                                                   margin:0px; border:0px solid transparent;}  /* zone des pages */
                                QTabBar { background-color: white; }           /* barre des onglets */
                                QTabBar::tab { background-color: white; }  /* chaque onglet */
                             )");


    // cursor stylesheet
    //this->setStyleSheet(R"(  QTextEdit { caret-color: black;   /* curseur noir sur fond blanc */
                      //  } )");




    ui->toolBar->setMovable(true);

    // new settings QDialog form
    settings = new SettingsInfoDialog(this);

    // get default settings
    pdfExportForamt =   SettingsInfoDialog::DefaultValues.PdfExportFormat;  //settings->getPdfExportForamt();
    noWrapLines     =   SettingsInfoDialog::DefaultValues.NoWrapLines;      //settings->getNoWrapLines();
    opacity         =   SettingsInfoDialog::DefaultValues.Opacity;          //settings->getOpacity();
    bagroundColor   =   SettingsInfoDialog::DefaultValues.BgColor;          //settings->getBagroundColor();
    bagroundColorInTranparentMode =  SettingsInfoDialog::DefaultValues.BgColorInTranparentMode;     //settings->getBagroundColorInTranparentMode();

    updateTextEditWrapMode();


    // size hint
    this->sizeHint();

    // cursor position
    updateCursorPosition();


    flag_transparent = false;
    flag_showToolBar= true;
    flag_showStatusBar = true;
    flag_showMenuBar = true;



}


QString MainWindow::GetCursorColorName()
{
    QColor bg = textEditList[CurrentTabIdx]->palette().color(QPalette::Base);

       // Détecter si le fond est sombre ou clair
       QColor caretColor = (bg.lightness() < 128) ? Qt::white : Qt::black; // contraste

       return QString("caret-color: %1;").arg(caretColor.name());
}

QColor MainWindow::GetTextColor()
{
    QColor bg ;//textEditList[CurrentTabIdx]->palette().color(QPalette::Base);

   if(flag_transparent)
       bg = bagroundColorInTranparentMode;
   else
       bg = bagroundColor;

   // Détecter si le fond est sombre ou clair
   QColor textColor  = (bg.lightness() < 128) ?  QColor(Qt::darkGray) : QColor(Qt::darkGray); // même logique pour le texte

   qDebug() << "text color : " << textColor << "transparent mode ? : " << flag_transparent;

   return textColor; //QString("color: %1;").arg(textColor.name());
}


void MainWindow::on_removeQuitFromToolbar_toggled(bool isSelected)
{
    if(isSelected)
        ui->toolBar->removeAction(ui->actionQuit);
    else
        ui->toolBar->addAction(ui->actionQuit);
}


void MainWindow::on_removeSettingsFromToolbar_toggled(bool isSelected)
{
    if(isSelected)
        ui->toolBar->removeAction(ui->settingsAction);
    else
        ui->toolBar->addAction(ui->settingsAction);
}


void MainWindow::on_removeAboutFromToolbar_toggled(bool isSelected)
{
    if(isSelected)
        ui->toolBar->removeAction(ui->actionAbout);
    else
        ui->toolBar->addAction(ui->actionAbout);
}


void MainWindow::on_removeActionZoomInFromTollbar_toggled(bool isSelected)
{
    if(isSelected)
        ui->toolBar->removeAction(ui->actionzoomIn);
    else
        ui->toolBar->addAction(ui->actionzoomIn);

}

void MainWindow::on_removeText_colorFromToolbar_toggled(bool isSelected)
{
    if(isSelected)
        ui->toolBar->removeAction(ui->actionColor);
    else
        ui->toolBar->addAction(ui->actionColor);
}


void MainWindow::on_removeActionFontFromToolbar_toggled(bool isSelected)
{
    if(isSelected)
        ui->toolBar->removeAction(ui->actionFont);
    else
        ui->toolBar->addAction(ui->actionFont);
}


void MainWindow::on_removeActionRedoFromToolbar_toggled(bool isSelected)
{
    if(isSelected)
        ui->toolBar->removeAction(ui->actionRedo);
    else
        ui->toolBar->addAction(ui->actionRedo);
}


void MainWindow::on_removeActionUndoFromToolbar_toggled(bool isSelected)
{
    if(isSelected)
        ui->toolBar->removeAction(ui->actionUndo);
    else
        ui->toolBar->addAction(ui->actionUndo);
}


void MainWindow::on_removeActionSelect_AllFromtoolbar_toggled(bool isSelected)
{
    if(isSelected)
        ui->toolBar->removeAction(ui->actionSelectAll);
    else
        ui->toolBar->addAction(ui->actionSelectAll);
}


void MainWindow::on_removeactionPasteFromToolbar_toggled(bool isSelected)
{
    if(isSelected)
        ui->toolBar->removeAction(ui->actionPaste);
    else
        ui->toolBar->addAction(ui->actionPaste);
}


void MainWindow::on_removeActionCutFromToolbar_toggled(bool isSelected)
{
    if(isSelected)
        ui->toolBar->removeAction(ui->actionCut);
    else
        ui->toolBar->addAction(ui->actionCut);
}


void MainWindow::on_removeActionCopyFromToolbar_toggled(bool isSelected)
{
    if(isSelected)
        ui->toolBar->removeAction(ui->actionCopy);
    else
        ui->toolBar->addAction(ui->actionCopy);
}


void MainWindow::on_removeExport_as_PDF_file_fromToolbar_toggled(bool isSelected)
{
    if(isSelected)
        ui->toolBar->removeAction(ui->actionExport_as_PDF);
    else
        ui->toolBar->addAction(ui->actionExport_as_PDF);
}


void MainWindow::on_removeOpenFileFromToolbar_toggled(bool isSelected)
{
    if(isSelected)
        ui->toolBar->removeAction(ui->actionOpen);
    else
        ui->toolBar->addAction(ui->actionOpen);
}


void MainWindow::on_removeSaveFileFromToolbar_toggled(bool isSelected)
{
    if(isSelected)
        ui->toolBar->removeAction(ui->actionSave);
    else
        ui->toolBar->addAction(ui->actionSave);
}


void MainWindow::on_removeTransparentModeFromToolbar_toggled(bool  isSelected)
{
    if(isSelected)
        ui->toolBar->removeAction(ui->actionTransparent);
    else
        ui->toolBar->addAction(ui->actionTransparent);
}



void MainWindow::on_removeActionZoomOutFromTollbar_toggled(bool  isSelected)
{
    if(isSelected)
        ui->toolBar->removeAction(ui->actionzoom_out);
    else
        ui->toolBar->addAction(ui->actionzoom_out);
}


void MainWindow::on_actionzoomIn_triggered()
{
    textEditList[CurrentTabIdx]->zoomIn();
}


void MainWindow::on_actionzoom_out_triggered()
{
    textEditList[CurrentTabIdx]->zoomOut();
}


void MainWindow::on_TabWidget_currentChanged(int index)
{
    // 1 - update current index
    CurrentTabIdx = index;

    // 2- update cursor position
    updateCursorPosition();

}

void MainWindow::on_TabWidget_TabCloseRequested(int index)
{
    QMessageBox msgBox;
     msgBox.setText("The document has been modified.");
     msgBox.setInformativeText("Do you want to close this file without saving changes?");
     msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
     msgBox.setDefaultButton(QMessageBox::No);


    if (index >= 0 && index < textEditList.size()) // security check
    {


        // get textEdit widget pointer index
        QTextEdit *EditorToDelete = textEditList[index];

        //ask to save file
        int ret = msgBox.exec();

        if(ret == QMessageBox::Yes )
        {
            // close without saving

            //1- remove tab
            TabWidget->removeTab(index);

            //2- remove corresponding textEdit
            textEditList.removeAt(index);

            //3- free memory (text edit)
            delete EditorToDelete;
        }

    }

}


void MainWindow::on_SettingsAccepted()  // redandance  avec settings-> exec()
{

    pdfExportForamt = settings->getPdfExportForamt() ;

    noWrapLines =  settings->getNoWrapLines() ;

    opacity = settings->getOpacity();

    bagroundColorInTranparentMode = settings->getBagroundColorInTranparentMode();

    bagroundColor = settings->getBagroundColor();

    // update settings
    //------------------
    // update CurrentTextEdit settings
    updateTextEditWrapMode();

    //update opacity
    updateWindowOpacity();

    updateCurrentEditStyle();
}
