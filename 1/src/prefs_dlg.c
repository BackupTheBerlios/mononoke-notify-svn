
/* prefs_dlg.c
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


#include <gtk/gtk.h>
#include <glib.h>

#include "globals.h"
#include "support.h"
#include "interface.h"
#include "prefs_dlg.h"


void
mn_prefs_show(void)
{
	if (mn.ui.prefs == 0) {
		mn.ui.prefs = create_prefs();
		mn_prefs_load();
	}
	gtk_widget_show(mn.ui.prefs);
}


void
mn_prefs_save(void)
{
	GtkWidget *widget;

	// user_login
	widget = lookup_widget(mn.ui.prefs, "user_login");
	mn.cfg.user_login = (gchar *) gtk_entry_get_text(GTK_ENTRY(widget));

	// browser
	widget = lookup_widget(mn.ui.prefs, "browser");
	mn.cfg.browser = (gchar *) gtk_entry_get_text(GTK_ENTRY(widget));

	// nbr_latest_torrent
	widget = lookup_widget(mn.ui.prefs, "nbr_latest_torrent");
	mn.cfg.nbr_latest_torrent =
		gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));

	// torrent_syntax
	widget = lookup_widget(mn.ui.prefs, "torrent_syntax");
	mn.cfg.torrent_syntax = (gchar *)
		gtk_entry_get_text(GTK_ENTRY(widget));

	// icon size
	widget = lookup_widget(mn.ui.prefs, "icon_size");
	mn.cfg.icon_size =
		gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));
}


void
mn_prefs_load(void)
{
	GtkWidget *widget;

	// user_login
	widget = lookup_widget(mn.ui.prefs, "user_login");
	gtk_entry_set_text(GTK_ENTRY(widget), mn.cfg.user_login);

	// browser
	widget = lookup_widget(mn.ui.prefs, "browser");
	gtk_entry_set_text(GTK_ENTRY(widget), mn.cfg.browser);

	// nbr_latest_torrent
	widget = lookup_widget(mn.ui.prefs, "nbr_latest_torrent");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget),
							  mn.cfg.nbr_latest_torrent);

	// torrent_syntax
	widget = lookup_widget(mn.ui.prefs, "torrent_syntax");
	gtk_entry_set_text(GTK_ENTRY(widget), mn.cfg.torrent_syntax);

	// icon size
	widget = lookup_widget(mn.ui.prefs, "icon_size");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), mn.cfg.icon_size);
}
