TEMPLATE = app
CONFIG += console c++11
CONFIG += c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += thread
QT += sql

INCLUDEPATH += -I"/home/platosha/Desktop/BMSTU/8sem/Diplom/postgresql-14.2/src/include"
LIBS += -L"/home/platosha/Desktop/BMSTU/8sem/Diplom/postgresql-14.2/src" -lpq

INCLUDEPATH += -I/usr/local/pgsql/include -lpqxx -lpq

SOURCES += \
        main.cpp
