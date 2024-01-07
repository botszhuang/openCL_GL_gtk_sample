#include "variable_collection_struct.h"
#include "gtkRUN_private.h"
#include "my_cl_function.h"
#include "my_gl_function.h"
#include "variable_collection_struct.h"
#include "openCLmain.h"
#include "gtk_chech_object.h"

unsigned int windowSizeX ;
unsigned int windowSizeY ; 
unsigned int windowPositionX ;
unsigned int windowPositionY ;

static void mainWindow_destroy ( GtkWindow* mainWindow, void* userdata){
  
  global_variable_Struct *v = ( global_variable_Struct * ) userdata ;
  v->openCLRUN = false ;  
  free_openCL(); 
  puts("CLOSE APP!");
  gtk_main_quit();
}

int main ( int argc, char** argv ) {
   
    init_global_variable_main () ;
    global_variable_Struct * userdata = get_global_variable_pointer () ;

    gtk_init( & argc, & argv );
    
    GtkBuilder * builder = gtk_builder_new_from_file("./src/ui/app.ui");
      gtk_check_object ( builder ) ;

    GtkWindow * mainWindow  = GTK_WINDOW(gtk_builder_get_object(builder, "mainWindow"));
      gtk_check_object ( mainWindow ) ;
      gtk_window_get_size( mainWindow , & windowSizeX , & windowSizeY ) ;
      gtk_window_get_position( mainWindow , & windowPositionX , & windowPositionY );
      g_signal_connect ( mainWindow , "destroy" , G_CALLBACK( mainWindow_destroy ), userdata );

    init_xyzAngleSacle  ( builder , userdata ) ;
    init_scaleAdjustment( builder , userdata ) ;
    init_BxyzSpinButton ( builder , userdata ) ;
    init_glarea         ( builder , userdata ) ;
    gtk_widget_show_all( GTK_WIDGET( mainWindow ) );

    init_openCL () ;
    
    userdata->openCLRUN = true ;
    
    pthread_t thread1 ;
    pthread_create ( & thread1 , NULL, openCLmain , NULL ) ; 

    g_timeout_add ( 200, update_glarea , userdata ) ;


  gtk_main();

/*  while(!isEnd){
    g_main_context_iteration(NULL,TRUE);
  }
*/
  pthread_join( thread1 , NULL); 

  return EXIT_SUCCESS ;
}

