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
    mac{
        #need to make sure the generated dylib has the correct install name baked in
        QMAKE_LFLAGS_SONAME = -install_name$${LITERAL_WHITESPACE}@executable_path/../lib/
    }
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
    /usr/local/include/boost \

#headers that are reasonably stable
DEPENDPATH += . \
    /usr/local/include \

#actual header/source files to build
HEADERS += \
    src/rrns_db/IRedisConsumer.h \
    src/rrns_db/IRedisConnector.h \
    src/rrns_db/IRandomConsumer.h \
    src/rrns_db/RandomConsumer.h \
    src/rrns_db/RedisConsumer.h \
    src/rrns_db/RedisDB_global.h \
    src/rrns_db/RedisDB_Wrapper.h \
    src/rrns_db/IKeyParser.h \
    src/rrns_db/IKey.h \
    src/rrns_db/ICredis.h \
    src/rrns_db/CredisAdapter.h \
    src/rrns_db/RedisConnector.h \
    src/rrns_db/Key.h \
    src/rrns_db/IKeyGenerator.h \
    src/rrns_db/ScopedTemporaryKey.h \
    src/rrns_db/MajorTypeKeyGenerator.h \
    src/rrns_db/MinorTypeKeyGenerator.h \
    src/rrns_db/DataKeyGenerator.h \
    src/rrns_db/SeedKeyGenerator.h \
    src/rrns_db/CutoffKeyGenerator.h \
    \
    src/third_party/credis/credis.h \
    src/rrns_db/KeyParser.h

SOURCES += \
    src/rrns_db/RandomConsumer.cpp \
    src/rrns_db/RedisConsumer.cpp \
    src/rrns_db/RedisDB_Wrapper.cpp \
    src/rrns_db/CredisAdapter.cpp \
    src/rrns_db/RedisConnector.cpp \
    src/rrns_db/ScopedTemporaryKey.cpp \
    src/rrns_db/MajorTypeKeyGenerator.cpp \
    src/rrns_db/MinorTypeKeyGenerator.cpp \
    src/rrns_db/DataKeyGenerator.cpp \
    src/rrns_db/SeedKeyGenerator.cpp \
    src/rrns_db/CutoffKeyGenerator.cpp \
    \
    src/third_party/credis/credis.c \
    src/rrns_db/ut/ScopedKeyGenerator_UT.cpp \
    src/rrns_db/KeyParser.cpp \
    src/rrns_db/ut/KeyParser_UT.cpp

test{

    HEADERS += \
        src/rrns_db/ut/MockICredis.h \
        src/rrns_db/ut/MockIRedisConnector.h \
        src/rrns_db/ut/MockIRedisConsumer.h \
        src/rrns_db/ut/MockIRandomConsumer.h \
        src/rrns_db/ut/MockIKeyParser.h \
        src/rrns_db/ut/MockIKey.h \
        src/rrns_db/ut/MockIKeyGenerator.h \
        \
        src/third_party/gmock/gmock/gmock.h \
        src/third_party/gmock/gtest/gtest.h \


    SOURCES += \
        src/rrns_db/ut/RedisConsumer_UT.cpp \
        src/rrns_db/ut/RandomConsumer_UT.cpp \
        src/rrns_db/ut/Main_UT.cpp \
        \
        src/third_party/gmock/gmock-gtest-all.cc \
}

#Google logging framework
LIBS += -L/usr/local/lib
LIBS += -lglog
