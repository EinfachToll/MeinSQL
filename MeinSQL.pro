# -------------------------------------------------
# Project created by QtCreator 2010-06-02T21:58:43
# -------------------------------------------------
QT += sql
TARGET = MeinSQL
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    settingswindow.cpp \
    table.cpp \
    mysqlhighlighter.cpp \
    sqltabletable.cpp \
    querytable.cpp \
    querytextedit.cpp \
    infotable.cpp
HEADERS += mainwindow.hh \
    settingswindow.hh \
    table.hh \
    mysqlhighlighter.h \
    sqltabletable.hh \
    querytable.hh \
    querytextedit.hh \
    infotable.hh
FORMS += mainwindow.ui \
    settingswindow.ui

OTHER_FILES += Readme.txt

TRANSLATIONS = meinsql_de.ts

CODECFORTR = UTF-8
