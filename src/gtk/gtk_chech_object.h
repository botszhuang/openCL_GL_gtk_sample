#ifndef GTK_CHECK_OBJECT_H
#define GTK_CHECK_OBJECT_H

#include <gtk/gtk.h>

#define gtk_check_object(x){\
  if ( x == NULL) { \
    printf("Error: %s not found or NULL\n", #x );\
    exit (1) ;\
  }\
}

#endif