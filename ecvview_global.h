#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(ECVVIEW_LIB)
#  define ECVVIEW_EXPORT Q_DECL_EXPORT
# else
#  define ECVVIEW_EXPORT Q_DECL_IMPORT
# endif
#else
# define ECVVIEW_EXPORT
#endif
