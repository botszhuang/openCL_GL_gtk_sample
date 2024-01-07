
#include "gtk_chech_object.h"
#include "variable_collection_struct.h"
#include "openCLmain.h"

static GMutex mutex ;

#define update_B( Bx , button ){\
  g_mutex_lock ( & mutex ) ;\
  Bx = ( float ) gtk_spin_button_get_value (button);\
  printf ( "update_B B = %.2lf, %.2lf, %.2lf\n" , v->B_amp.x , v->B_amp.y , v->B_amp.z ) ;\
  g_mutex_unlock ( & mutex ) ;\
}
static void updat_Bx_value( GtkSpinButton *button , gpointer user_data ) {
    global_variable_Struct * v = ( global_variable_Struct * ) user_data ;
    update_B( v->B_amp.x , button ) ;
}
static void updat_By_value( GtkSpinButton *button , gpointer user_data ) {
    global_variable_Struct * v = ( global_variable_Struct * ) user_data ;
    update_B( v->B_amp.y , button ) ;
}
static void updat_Bz_value( GtkSpinButton *button , gpointer user_data ) {
    global_variable_Struct * v = ( global_variable_Struct * ) user_data ;
    update_B( v->B_amp.z , button ) ;
}
void free_BxyzSpinButton()
{
  g_mutex_clear  ( & mutex ) ;
}
void init_BxyzSpinButton ( GtkBuilder * builder , gpointer user_data )
{
    GtkAdjustment *BxAdjustment  = GTK_ADJUSTMENT ( gtk_builder_get_object ( builder , "BxAdjustment" ) ) ; gtk_check_object ( BxAdjustment ) ;
    GtkAdjustment *ByAdjustment  = GTK_ADJUSTMENT ( gtk_builder_get_object ( builder , "ByAdjustment" ) ) ; gtk_check_object ( ByAdjustment ) ;
    GtkAdjustment *BzAdjustment  = GTK_ADJUSTMENT ( gtk_builder_get_object ( builder , "BzAdjustment" ) ) ; gtk_check_object ( BzAdjustment ) ;

    global_variable_Struct * v = ( global_variable_Struct * ) user_data ;
    gtk_adjustment_set_value( BxAdjustment, v->B_amp.x );
    gtk_adjustment_set_value( ByAdjustment, v->B_amp.y );
    gtk_adjustment_set_value( BzAdjustment, v->B_amp.z );

    GtkSpinButton * BxSpinButton =  GTK_SPIN_BUTTON ( gtk_builder_get_object ( builder , "BxSpinButton" ) ) ; gtk_check_object ( BxSpinButton ) ;
    GtkSpinButton * BySpinButton =  GTK_SPIN_BUTTON ( gtk_builder_get_object ( builder , "BySpinButton" ) ) ; gtk_check_object ( BySpinButton ) ;
    GtkSpinButton * BzSpinButton =  GTK_SPIN_BUTTON ( gtk_builder_get_object ( builder , "BzSpinButton" ) ) ; gtk_check_object ( BzSpinButton ) ;

    g_signal_connect(BxSpinButton, "value-changed", G_CALLBACK(updat_Bx_value), user_data );     
    g_signal_connect(BySpinButton, "value-changed", G_CALLBACK(updat_By_value), user_data );
    g_signal_connect(BzSpinButton, "value-changed", G_CALLBACK(updat_Bz_value), user_data );

}

#undef update_B
