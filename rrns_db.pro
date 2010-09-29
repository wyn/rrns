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
    src/third_party \
    src/third_party/credis \
    src/third_party/gmock \

#headers that are reasonably stable
DEPENDPATH += . \
    src \
    src/third_party \
    /usr/local/include

#actual header/source files to build
HEADERS += \
    src/rrns_db/ICredisConsumer.h \
    src/rrns_db/ICredisConnector.h \
    src/rrns_db/IRedisManager.h \
    src/rrns_db/RedisManager.h \
    src/rrns_db/RedisConsumer.h \
    src/rrns_db/RedisDB_global.h \
    src/rrns_db/RedisDB_Wrapper.h \
    \
    src/third_party/credis/credis.h \

SOURCES += \
    src/rrns_db/RedisManager.cpp \
    src/rrns_db/RedisConsumer.cpp \
    src/rrns_db/RedisDB_Wrapper.cpp \
    \
    src/third_party/credis/credis.c \

test{

    HEADERS += \
        src/rrns_db/ut/MockICredisConnector.h \
        src/rrns_db/ut/MockICredisConsumer.h \
        \
        src/third_party/gmock/gmock/gmock.h \
        src/third_party/gmock/gtest/gtest.h \


    SOURCES += \
        src/rrns_db/ut/RedisConsumer_UT.cpp \
        src/rrns_db/ut/RedisManager_UT.cpp \
        src/rrns_db/ut/Main_UT.cpp \
        \
        src/third_party/gmock/gmock-gtest-all.cc \
}

#Google logging framework
LIBS += -L/usr/local/lib
LIBS += -lglog
