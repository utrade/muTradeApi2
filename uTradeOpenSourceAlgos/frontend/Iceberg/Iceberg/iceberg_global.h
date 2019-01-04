#ifndef ICEBERG_GLOBAL_H
#define ICEBERG_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ICEBERG_LIBRARY)
#  define ICEBERGSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ICEBERGSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ICEBERG_GLOBAL_H
