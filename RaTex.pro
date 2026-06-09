QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    document.cpp \
    main.cpp \
    mainwindow.cpp \
    settingsinfodialog.cpp

HEADERS += \
    document.h \
    mainwindow.h \
    settingsinfodialog.h

FORMS += \
    mainwindow.ui \
    settingsinfodialog.ui

TRANSLATIONS += \
    RaTex_ar_DZ.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc

DISTFILES += \
    images/RaText.png \
    images/color.png \
    images/copy.png \
    images/display.png \
    images/font-size.png \
    images/loupe.png \
    images/opacity.png \
    images/open-folder.png \
    images/paste.png \
    images/redo.png \
    images/rotate-arrow.png \
    images/save.png \
    images/save_as_pdf.png \
    images/save_as_pdf1.png \
    images/savf.png \
    images/scissors.png \
    images/selectAll.png \
    images/settings.png \
    images/shutdown.png \
    images/support.png \
    images/turn-left.png \
    images/undo.png
