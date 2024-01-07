
#include "gtk_chech_object.h"
#include "const_extern_parameter.h"
#include "my_gl_function.h"
#include "geometry_matrix.h"
#include "openCLmain.h"

GtkWidget *gl_area ;

static float tMatrix [ 16 ] ;
static float tMatrixForMarker [ 16 ] ;
static unsigned int tMatrixBytes = 0 ;
static rotation_angle_struct R ;

static float scaleGLArea = 10 ;

static void realize (GtkWidget *widget)
{
  GdkGLContext *context;
  gtk_gl_area_make_current (GTK_GL_AREA (widget));
  if (gtk_gl_area_get_error (GTK_GL_AREA (widget)) != NULL)
    return;
  context = gtk_gl_area_get_context (GTK_GL_AREA (widget));

  tMatrixBytes = 16 * sizeof ( tMatrix [0] ) ;

  init_triangleProgram () ;
  init_coordinateMarker () ;
  init_colorBar () ;
  init_objects () ;
}
static void unrealize (GtkWidget *widget)
{
  gtk_gl_area_make_current (GTK_GL_AREA (widget));

  if (gtk_gl_area_get_error (GTK_GL_AREA (widget)) != NULL)
    return;

  free_objects () ;
  free_coordinateMarker () ;
  free_colorBar () ;
  free_triangleProgram () ;   
}
static gboolean render (GtkGLArea    *area,
                     GdkGLContext *context ,
                     void * userdata )
{
  if (gtk_gl_area_get_error (area) != NULL)
    return FALSE;
  
  puts("rendering ......");
 
  glClearColor (1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport( 0, 0,  windowSizeX ,  windowSizeY );

  get_rotaion_matrix ( tMatrix , R ) ;
  memcpy( tMatrixForMarker , tMatrix , tMatrixBytes ) ;

  get_scale_matrix ( tMatrix , 1/scaleGLArea , 1/scaleGLArea , 1/scaleGLArea ) ;

  draw_openCL_data ( tMatrix ) ;
  draw_coordinateMarker ( tMatrixForMarker ) ;
  draw_colorBar () ;
  glFlush ();

  return TRUE;
}
gboolean update_glarea ( void * userdata )
{
  gtk_widget_queue_draw ( gl_area ) ;
  return true ;
}
void init_glarea ( GtkBuilder * builder , gpointer user_data ) 
{
  puts("init glraea ...");
    gl_area = GTK_WIDGET ( gtk_builder_get_object ( builder , "openGLArea" ) ) ; 
    gtk_check_object ( gl_area ) ;
      g_signal_connect (gl_area, "realize"  , G_CALLBACK (realize)  , NULL);
      g_signal_connect (gl_area, "unrealize", G_CALLBACK (unrealize), NULL);
      g_signal_connect (gl_area, "render"   , G_CALLBACK (render)   , NULL); 

}

static void updat_xAngle_value( GtkRange *range, gpointer user_data ) {
   R.phi = ( float ) gtk_range_get_value(range);
   gtk_widget_queue_draw ( gl_area ) ;
}
static void updat_yAngle_value( GtkRange *range, gpointer user_data ) {
    R.theta = ( float ) gtk_range_get_value(range);
    gtk_widget_queue_draw ( gl_area ) ;
}
static void updat_zAngle_value( GtkRange *range, gpointer user_data ) {
    R.psi = ( float ) gtk_range_get_value(range);
    gtk_widget_queue_draw ( gl_area ) ;
}
void init_xyzAngleSacle( GtkBuilder * builder , gpointer user_data )
{
    GtkAdjustment *xAngleAdjustment  = GTK_ADJUSTMENT ( gtk_builder_get_object ( builder , "xAngleAdjustment" ) ) ; gtk_check_object ( xAngleAdjustment ) ;
    GtkAdjustment *yAngleAdjustment  = GTK_ADJUSTMENT ( gtk_builder_get_object ( builder , "yAngleAdjustment" ) ) ; gtk_check_object ( yAngleAdjustment ) ;
    GtkAdjustment *zAngleAdjustment  = GTK_ADJUSTMENT ( gtk_builder_get_object ( builder , "zAngleAdjustment" ) ) ; gtk_check_object ( zAngleAdjustment ) ;

    R.phi   = 0 ;   gtk_adjustment_set_value(xAngleAdjustment, R.phi   );
    R.theta = 0 ;   gtk_adjustment_set_value(yAngleAdjustment, R.theta );
    R.psi   = 0 ;   gtk_adjustment_set_value(zAngleAdjustment, R.psi   );

    GtkWidget * xAngle = GTK_WIDGET ( gtk_builder_get_object ( builder , "xAngle" ) ) ; gtk_check_object ( xAngle ) ;
    GtkWidget * yAngle = GTK_WIDGET ( gtk_builder_get_object ( builder , "yAngle" ) ) ; gtk_check_object ( yAngle ) ;
    GtkWidget * zAngle = GTK_WIDGET ( gtk_builder_get_object ( builder , "zAngle" ) ) ; gtk_check_object ( zAngle ) ;

    g_signal_connect(xAngle, "button-release-event", G_CALLBACK(updat_xAngle_value), user_data );     
    g_signal_connect(yAngle, "button-release-event", G_CALLBACK(updat_yAngle_value), user_data );
    g_signal_connect(zAngle, "button-release-event", G_CALLBACK(updat_zAngle_value), user_data );
}
void updat_scale_value ( GtkRange *range, gpointer user_data )
{
    scaleGLArea = ( float ) gtk_range_get_value(range);
    gtk_widget_queue_draw ( gl_area ) ;
}
void init_scaleAdjustment( GtkBuilder * builder , gpointer user_data )
{
    GtkAdjustment *scaleAdjustment  = GTK_ADJUSTMENT ( gtk_builder_get_object ( builder , "scaleAdjustment" ) ) ; 
    gtk_check_object ( scaleAdjustment ) ;
    scaleGLArea = 10 ;   
    gtk_adjustment_set_value( scaleAdjustment , scaleGLArea );
    
    GtkWidget * scale = GTK_WIDGET ( gtk_builder_get_object ( builder , "scale" ) ) ; gtk_check_object ( scale ) ;
    g_signal_connect( scale , "button-release-event", G_CALLBACK(updat_scale_value), user_data );   
   
}
