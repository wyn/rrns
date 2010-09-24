#-------------------------------------------------
#
# Project created by QtCreator 2010-09-22T11:09:21
#
#-------------------------------------------------

message($$_PRO_FILE_)

QT -= gui
QT += core

test{
    CONFIG   += console
    CONFIG   -= app_bundle
    TEMPLATE = app
    TARGET = tests/rrns_db_ut
}
!test{
    CONFIG   -= console
    TEMPLATE = lib
    TARGET = lib/rrns_db
    #need to make sure the generated dylib has the correct install name baked in
    QMAKE_LFLAGS_SONAME = -install_name$${LITERAL_WHITESPACE}@executable_path/../lib/
}

MOC_DIR = mocs
OBJECTS_DIR = obj

DEFINES += RRNS_DB_LIBRARY

#headers that will always need a rebuild
INCLUDEPATH += . \
    src \
    src/rrns_db \
    src/third_party/credis \
    src/third_party/gmock/gtest/include \
    src/third_party/gmock/gtest \
    src/third_party/gmock/include \
    src/third_party/gmock

#headers that are reasonably stable
DEPENDPATH += . \
    src \
    src/third_party \
    src/third_party/credis

#actual header/source files to build
#TODO should build credis to a static lib?
#TODO should build gmock to a static lib?
HEADERS += \
    src/rrns_db/RedisConsumer.h \
    src/rrns_db/RedisDB_global.h \
    src/rrns_db/RedisDB_Wrapper.h \
    src/third_party/credis/credis.h

SOURCES += \
    src/rrns_db/RedisConsumer.cpp \
    src/rrns_db/RedisDB_Wrapper.cpp \
    src/third_party/credis/credis.c

test{
    SOURCES += \
        src/rrns_db/ut/RedisConsumer_UT.cpp \
        src/rrns_db/ut/Main_UT.cpp \
        src/third_party/gmock/gtest/src/gtest-all.cc \
        src/third_party/gmock/src/gmock-all.cc
}

#Google test framework
#LIBS += -L$$_PRO_FILE_PWD_/src/third_party/gtest/lib
#LIBS += -lgmock
