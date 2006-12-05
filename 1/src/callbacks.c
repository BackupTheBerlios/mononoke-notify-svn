
/* callbacks.c
 * Copyright (C) 2006 Alexandre Bique <bique.alexandre@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "config.h"
#include "globals.h"
#include "menu.h"
#include "prefs_dlg.h"
#include "update.h"


void
on_applybutton1_clicked(GtkButton * button, gpointer user_data)
{
	mn_prefs_save();
	mn_save_config();
}


void
on_cancelbutton1_clicked(GtkButton * button, gpointer user_data)
{
	mn_prefs_load();
	gtk_widget_hide(mn.ui.prefs);
}


void
on_okbutton1_clicked(GtkButton * button, gpointer user_data)
{
	mn_prefs_save();
	mn_save_config();
	mn_update();
	gtk_widget_hide(mn.ui.prefs);
}


void
on_prefs_destroy(GtkObject * object, gpointer user_data)
{
	mn.ui.prefs = create_prefs();
	mn_prefs_load();
}

void
on_browser_bt_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *file_chooser;
	GtkWidget *browser;
	
	file_chooser = gtk_file_chooser_dialog_new ("Open File",
				      mn.ui.prefs,
				      GTK_FILE_CHOOSER_ACTION_OPEN,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
				      NULL);
				      
	if (gtk_dialog_run (GTK_DIALOG (file_chooser)) == GTK_RESPONSE_ACCEPT)
  {
    char *filename;

    filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (file_chooser));
	browser = lookup_widget(GTK_WIDGET(button), "browser");
	gtk_entry_set_text(GTK_ENTRY(browser),filename);
    g_free (filename);
  }

	gtk_widget_destroy (file_chooser);
}

