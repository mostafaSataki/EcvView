#pragma once

#include <qglobal.h>

#ifndef BUILD_STATIC
# if defined(ECVVIEW_LIB)
#  define VIEWLIB_EXPORT Q_DECL_EXPORT
# else
#  define VIEWLIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define VIEWLIB_EXPORT
#endif
