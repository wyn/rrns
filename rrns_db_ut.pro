#-------------------------------------------------
#
# Project created by QtCreator 2010-09-22T12:02:56
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tests/RedisDB_UT
MOC_DIR = mocs
OBJECTS_DIR = obj

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += . \
                src \
                src/rrns_db \
                src/third_party

DEPENDPATH += . \
                src \
                src/rrns_db \
                src/third_party

SOURCES += \
            src/rrns_db/ut/RedisDB_UT.cpp

LIBPATH += lib
LIBS += -lRedisDB

DEFINES += SRCDIR=\\\"$$PWD/\\\"
