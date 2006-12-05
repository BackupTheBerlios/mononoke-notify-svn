
/* menu.c
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


#include <glib.h>
#include "globals.h"
#include "menu.h"
#include "xml_user_info.h"
#include "interface.h"
#include "tray_menu_torrent_item.h"
#include "download.h"
#include "support.h"
#include "update.h"
#include "prefs_dlg.h"

void
mn_quitter(void)
{
	gtk_main_quit();
}


void
mn_mononoke_clicked(void)
{
	gchar buffer[128];
	GError *error;

	g_snprintf(buffer, 128, "%s http://mononoke-bt.org", mn.cfg.browser);
	g_spawn_command_line_async(buffer, &error);
}

void
mn_mononoke_pm_clicked(void)
{
	gchar buffer[128];
	GError *error;

	g_snprintf(buffer, 128, "%s http://mononoke-bt.org/inbox.php",
			   mn.cfg.browser);
	g_spawn_command_line_async(buffer, &error);
}

void
mn_menu_torrent_list_init(const gchar * label,
						  const struct torrent_list *tl, GtkWidget * image)
{
	GtkWidget *menu;
	GtkWidget *item;
	gint i;

	item = gtk_image_menu_item_new_with_label(label);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), GTK_WIDGET(image));
	gtk_container_add(GTK_CONTAINER(mn.ui.tray_menu), item);

	if (tl->count == 0) {
		gtk_widget_set_sensitive(item, FALSE);
		return;
	}

	menu = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), menu);

	for (i = 0; i < tl->count; i++) {
		item = mn_torrent_item((struct mononoke_torrent *) &tl->torrent[i]);
		gtk_container_add(GTK_CONTAINER(menu), item);
	}
	gtk_container_set_border_width(GTK_CONTAINER(menu), 0);
}

void
mn_tray_menu_init(void)
{
	GtkWidget *item;
	GtkWidget *image;
	GdkPixbuf *pixbuf;
	gchar buffer[128];
	gchar *image_filename;

	mn.ui.tray_menu = gtk_menu_new();

	//Mononoke
	g_snprintf(buffer, 128, "Mononoke [%s]", mn.cfg.user_login);
	image_filename = g_strdup_printf("%s/%s", mn.env.icons_dir, "mononoke.jpg");
	pixbuf = gdk_pixbuf_new_from_file_at_size(image_filename, 20, 20, 0);
	image = gtk_image_new_from_pixbuf(pixbuf);
	g_object_unref(pixbuf);
	item = gtk_image_menu_item_new_with_label(buffer);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), GTK_WIDGET(image));
	gtk_container_add(GTK_CONTAINER(mn.ui.tray_menu), item);
	g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(mn_mononoke_clicked), NULL);

	//Mettre a jour item
	item = gtk_image_menu_item_new_with_label("Mettre à jour");
	image_filename = g_strdup_printf("%s/%s", mn.env.icons_dir, "refresh.gif");
	pixbuf = gdk_pixbuf_new_from_file_at_size(image_filename, 20, 20, 0);
	image = gtk_image_new_from_pixbuf(pixbuf);
	g_object_unref(pixbuf);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), GTK_WIDGET(image));
	gtk_container_add(GTK_CONTAINER(mn.ui.tray_menu), item);
	g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(mn_update), NULL);

	//break
	item = gtk_menu_item_new();
	gtk_widget_set_sensitive(item, FALSE);
	gtk_container_add(GTK_CONTAINER(mn.ui.tray_menu), item);

	//Upload
	g_snprintf(buffer, 128, "Envoyé: %.4g Go", mn.xml.uploaded);
	item = gtk_image_menu_item_new_with_label(buffer);
	image_filename = g_strdup_printf("%s/%s", mn.env.icons_dir, "upload.gif");
	pixbuf = gdk_pixbuf_new_from_file_at_size(image_filename, 20, 20, 0);
	image = gtk_image_new_from_pixbuf(pixbuf);
	g_object_unref(pixbuf);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), GTK_WIDGET(image));
	gtk_container_add(GTK_CONTAINER(mn.ui.tray_menu), item);

	//Download
	g_snprintf(buffer, 128, "Téléchargé: %.4g + %.4g = %.4g Go",
			   mn.xml.downloaded, mn.xml.free_downloaded,
			   mn.xml.free_downloaded + mn.xml.downloaded);
	image_filename = g_strdup_printf("%s/%s", mn.env.icons_dir, "download.gif");
	pixbuf = gdk_pixbuf_new_from_file_at_size(image_filename, 20, 20, 0);
	image = gtk_image_new_from_pixbuf(pixbuf);
	g_object_unref(pixbuf);
	item = gtk_image_menu_item_new_with_label(buffer);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), GTK_WIDGET(image));
	gtk_container_add(GTK_CONTAINER(mn.ui.tray_menu), item);

	//Ratio
	if (mn.xml.uploaded == 0)
		g_snprintf(buffer, 128, "Espèce de rat ;)");
	else
		g_snprintf(buffer, 128, "Ratio: %.2g, %.2g",
				   mn.xml.uploaded / mn.xml.downloaded,
				   mn.xml.uploaded / (mn.xml.free_downloaded +
										   mn.xml.downloaded));
	item = gtk_image_menu_item_new_with_label(buffer);
	if (mn.xml.uploaded / mn.xml.downloaded < 0.9)
		image_filename =
			g_strdup_printf("%s/%s", mn.env.icons_dir, "crazy.gif");
	else if (mn.xml.uploaded / mn.xml.downloaded < 1.5)
		image_filename =
			g_strdup_printf("%s/%s", mn.env.icons_dir, "smile1.gif");
	else if (mn.xml.uploaded / mn.xml.downloaded < 3)
		image_filename = g_strdup_printf("%s/%s", mn.env.icons_dir, "grin.gif");
	else
		image_filename = g_strdup_printf("%s/%s", mn.env.icons_dir, "w00t.gif");
	pixbuf = gdk_pixbuf_new_from_file_at_size(image_filename, 20, 20, 0);
	image = gtk_image_new_from_pixbuf(pixbuf);
	g_object_unref(pixbuf);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), GTK_WIDGET(image));
	gtk_container_add(GTK_CONTAINER(mn.ui.tray_menu), item);

	//PM
	g_snprintf(buffer, 128, "Nouveaux messages: %d", mn.xml.new_pm);
	item = gtk_image_menu_item_new_with_label(buffer);
	image_filename = g_strdup_printf("%s/%s", mn.env.icons_dir, "contact.gif");
	pixbuf = gdk_pixbuf_new_from_file_at_size(image_filename, 20, 20, 0);
	image = gtk_image_new_from_pixbuf(pixbuf);
	g_object_unref(pixbuf);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), GTK_WIDGET(image));
	gtk_container_add(GTK_CONTAINER(mn.ui.tray_menu), item);
	g_signal_connect(G_OBJECT(item), "activate",
					 G_CALLBACK(mn_mononoke_pm_clicked), NULL);

	//break
	item = gtk_menu_item_new();
	gtk_widget_set_sensitive(item, FALSE);
	gtk_container_add(GTK_CONTAINER(mn.ui.tray_menu), item);

	//Need seed
	image_filename = g_strdup_printf("%s/%s", mn.env.icons_dir, "donate.gif");
	pixbuf = gdk_pixbuf_new_from_file_at_size(image_filename, 20, 20, 0);
	image = gtk_image_new_from_pixbuf(pixbuf);
	g_object_unref(pixbuf);
	mn_menu_torrent_list_init("Besoin de sources", &mn.xml.need_seed, image);

	//Sorties
	image_filename = g_strdup_printf("%s/%s", mn.env.icons_dir, "bomb.png");
	pixbuf = gdk_pixbuf_new_from_file_at_size(image_filename, 20, 20, 0);
	image = gtk_image_new_from_pixbuf(pixbuf);
	g_object_unref(pixbuf);
	mn_menu_torrent_list_init("Dernières sorties", &mn.xml.sorties, image);

	//Latest
	image_filename = g_strdup_printf("%s/%s", mn.env.icons_dir, "search.gif");
	pixbuf = gdk_pixbuf_new_from_file_at_size(image_filename, 20, 20, 0);
	image = gtk_image_new_from_pixbuf(pixbuf);
	g_object_unref(pixbuf);
	mn_menu_torrent_list_init("Derniers torrents", &mn.xml.latest, image);

	//break
	item = gtk_menu_item_new();
	gtk_widget_set_sensitive(item, FALSE);
	gtk_container_add(GTK_CONTAINER(mn.ui.tray_menu), item);

	//Preferences
	item = gtk_image_menu_item_new_with_label("Préférences");
	image_filename = g_strdup_printf("%s/%s", mn.env.icons_dir, "my.gif");
	pixbuf = gdk_pixbuf_new_from_file_at_size(image_filename, 20, 20, 0);
	image = gtk_image_new_from_pixbuf(pixbuf);
	g_object_unref(pixbuf);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), GTK_WIDGET(image));
	gtk_container_add(GTK_CONTAINER(mn.ui.tray_menu), item);
	g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(mn_prefs_show), NULL);

	//break
	item = gtk_menu_item_new();
	gtk_widget_set_sensitive(item, FALSE);
	gtk_container_add(GTK_CONTAINER(mn.ui.tray_menu), item);

	//Quiiter item
	item = gtk_image_menu_item_new_with_label("Quitter");
	image_filename = g_strdup_printf("%s/%s", mn.env.icons_dir, "logout.gif");
	pixbuf = gdk_pixbuf_new_from_file_at_size(image_filename, 20, 20, 0);
	image = gtk_image_new_from_pixbuf(pixbuf);
	g_object_unref(pixbuf);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), image);
	gtk_container_add(GTK_CONTAINER(mn.ui.tray_menu), item);
	g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(mn_quitter), NULL);

	//finalization
	gtk_widget_show_all(mn.ui.tray_menu);
}

gboolean
mn_tray_menu(GtkWidget * widget, GdkEventButton * event, gpointer data)
{
	g_mutex_lock(mn.lock);
	if (mn.ui.tray_menu == 0)
		mn_tray_menu_init();
	gtk_menu_popup(GTK_MENU(mn.ui.tray_menu), NULL, NULL, NULL, NULL,
				   event->button, event->time);
	g_mutex_unlock(mn.lock);

	return TRUE;
}
