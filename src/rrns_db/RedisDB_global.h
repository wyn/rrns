#ifndef REDISDB_GLOBAL_H
#define REDISDB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(REDISDB_LIBRARY)
#  define REDISDBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define REDISDBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // REDISDB_GLOBAL_H
