#ifndef TSC_MACRO_H
#define TSC_MACRO_H

#include <SSC/Macro.h>

#ifdef TSC_EXTERN_STATIC_LIB
 #define TSC_API /* Nil */
 #define TSC_API_IS_NIL
#else
 /* Unless explicitly specified as being statically linked, assume
  * TSC is being imported as a dynamically linked, shared library.
  */
 #define TSC_API SSC_IMPORT
 #define TSC_API_IS_IMPORT
 #ifdef SSC_IMPORT_IS_NIL
  #define TSC_API_IS_NIL
 #endif
#endif

#endif /* ~ TSC_MACRO_H */
