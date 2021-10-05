QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    chess_figures/black_figures.bmp \
    chess_figures/chess_figures.jpg \
    chess_figures/figs.jpg \
    chess_figures/hourse_black.bmp \
    chess_figures/hourse_white.bmp \
    chess_figures/king_black.bmp \
    chess_figures/king_white.bmp \
    chess_figures/lad_black.bmp \
    chess_figures/lad_white.bmp \
    chess_figures/peshka_black.bmp \
    chess_figures/peshka_white.bmp \
    chess_figures/queen_black.bmp \
    chess_figures/queen_white.bmp \
    chess_figures/slon_black.bmp \
    chess_figures/slon_white.bmp \
    chess_figures/white_figures.bmp
