#-------------------------------------------------
#
# Project created by QtCreator 2010-09-22T11:09:21
#
#-------------------------------------------------

QT       -= gui
TEMPLATE = lib
TARGET = lib/RedisDB
MOC_DIR = mocs
OBJECTS_DIR = obj

DEFINES += REDISDB_LIBRARY

#need to make sure the generated dylib has the correct install name baked in
QMAKE_LFLAGS_SONAME = -install_name$${LITERAL_WHITESPACE}@executable_path/../lib/

INCLUDEPATH += . \
                src \
                src/rrns_db \
                src/third_party

DEPENDPATH += . \
                src \
                src/rrns_db \
                src/third_party

HEADERS += \
            src/rrns_db/RedisDB.h \
            src/rrns_db/RedisDB_global.h \
            src/third_party/credis.h

SOURCES += \
            src/rrns_db/RedisDB.cpp \
            src/third_party/credis.c
