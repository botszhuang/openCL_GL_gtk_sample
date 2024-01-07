#ifndef GTK_RUN_PRIVATE_H
#define GTK_RUN_PRIVATE_H

#include <gtk/gtk.h>

void init_glarea   ( GtkBuilder * builder , gpointer user_data ) ;
gboolean update_glarea  ( void * userdata ) ;

void init_xyzAngleSacle ( GtkBuilder * builder , gpointer user_data ) ;
void init_scaleAdjustment( GtkBuilder * builder , gpointer user_data ) ;
void init_BxyzSpinButton ( GtkBuilder * builder , gpointer user_data ) ;
void free_BxyzSpinButton() ;

#endif