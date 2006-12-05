
/* notify_area.c
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

#include "eggtrayicon.h"
#include "tray_menu.h"
#include "globals.h"

gboolean
mn_tray_clicked(GtkWidget * event_box, GdkEventButton * event, gpointer data)
{
	//mouse right click
	if (event->button == 3) {
		return mn_tray_menu(event_box, event, data);
	}

	return FALSE;
}

void
mn_notify_init(void)
{
	GtkWidget *eventbox;
	GtkWidget *tray_icon_image;
	GtkWidget *tray_icon;
	GtkTooltips *tray_icon_tooltip;
	gchar *tmp;

	tray_icon = GTK_WIDGET(egg_tray_icon_new("Test"));
	gtk_widget_set_usize(tray_icon, 22, 22);
	gtk_widget_realize(tray_icon);

	tmp = g_strdup_printf("%s/mononoke.jpg", mn.env.icons_dir);
	tray_icon_image =
		gtk_image_new_from_pixbuf(gdk_pixbuf_new_from_file_at_size
								  (tmp, 20, 20, NULL));
	g_free(tmp);

	eventbox = gtk_event_box_new();


	gtk_container_add(GTK_CONTAINER(eventbox), tray_icon_image);
	gtk_container_add(GTK_CONTAINER(tray_icon), eventbox);

	g_signal_connect(G_OBJECT(eventbox), "button_press_event",
					 G_CALLBACK(mn_tray_clicked), NULL);
	g_signal_connect(GTK_OBJECT(tray_icon), "destroy",
					 GTK_SIGNAL_FUNC(gtk_widget_destroyed), &tray_icon);
	g_signal_connect(G_OBJECT(tray_icon), "destroy",
					 GTK_SIGNAL_FUNC(gtk_widget_destroyed), NULL);

	//finalize
	gtk_widget_show(GTK_WIDGET(tray_icon));
	gtk_widget_show(eventbox);
	gtk_widget_show(GTK_WIDGET(tray_icon_image));

	//tooltip
	tray_icon_tooltip = gtk_tooltips_new();
	gtk_tooltips_set_tip(tray_icon_tooltip, GTK_WIDGET(tray_icon),
						 "Mononoke Notify", NULL);
	gtk_tooltips_set_delay(tray_icon_tooltip, 1000);

}
