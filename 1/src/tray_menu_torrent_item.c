
/* torrent_item.c
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
#include <glib/gprintf.h>

#include "globals.h"
#include "download.h"

void
mn_mononoke_torrent_clicked(GtkMenuItem * menuitem, struct mononoke_torrent * mt)
{
	gchar *tmp;

	tmp = g_strdup_printf("%s http://mononoke-bt.org/gettorrent.php/%s?id=%d&r=1",
						  mn.cfg.browser, mt->filename, mt->id);
	g_spawn_command_line_async(tmp, 0);
	g_free(tmp);
}


static int
mn_check_par(const gchar * s)
{
	int i;

	if (*s != '(')
		return -1;

	for (i = 1; s[i] != 0; i++) {
		if (s[i] == ')')
			return i;
		else if (s[i] == '(')
			return -1;
	}

	return -1;
}

GtkWidget *
mn_torrent_item_elt_from_var(const gchar * v, struct mononoke_torrent * mt)
{
	int i;
	GtkWidget *w = 0;
	GdkPixbuf *pixbuf = 0;
	gchar *tmp;
	gchar *image_filename = 0;
	gchar *dup = g_strdup(v);

	for (i = 0; dup[i] != ')'; i++);
	dup[i] = 0;

	if (g_ascii_strcasecmp(dup, "anime_icon") == 0) {
		mn_download_category_logo(mt->category);
		image_filename = g_strdup_printf("%s/category_%d.jpg",
										 mn.env.icons_dir, mt->category);
		pixbuf = gdk_pixbuf_new_from_file_at_size(image_filename,
												  mn.cfg.icon_size,
												  mn.cfg.icon_size, 0);
		w = gtk_image_new_from_pixbuf(pixbuf);
		g_object_unref(pixbuf);
	} else if (g_ascii_strcasecmp(dup, "team_icon") == 0) {
		mn_download_team_logo(mt->team_id);
		image_filename = g_strdup_printf("%s/team_%d.jpg",
										 mn.env.icons_dir, mt->team_id);
		pixbuf = gdk_pixbuf_new_from_file_at_size(image_filename,
												  mn.cfg.icon_size,
												  mn.cfg.icon_size, 0);
		w = gtk_image_new_from_pixbuf(pixbuf);
		g_object_unref(pixbuf);
	} else if (g_ascii_strcasecmp(dup, "packet_icon") == 0) {
		image_filename = g_strdup_printf("%s/cadeau%d-large.png",
										 mn.env.icons_dir, mt->free_download);
		pixbuf = gdk_pixbuf_new_from_file_at_size(image_filename,
												  mn.cfg.icon_size,
												  mn.cfg.icon_size, 0);
		w = gtk_image_new_from_pixbuf(pixbuf);
		g_object_unref(pixbuf);
	} else if (g_ascii_strcasecmp(dup, "leechers") == 0) {
		tmp = g_strdup_printf("%d", mt->leechers);
		w = gtk_label_new(tmp);
		g_free(tmp);
	} else if (g_ascii_strcasecmp(dup, "seeders") == 0) {
		tmp = g_strdup_printf("%d", mt->seeders);
		w = gtk_label_new(tmp);
		g_free(tmp);
	} else if (g_ascii_strcasecmp(dup, "cat_name") == 0) {
		w = gtk_label_new(mt->cat_name);
	} else if (g_ascii_strcasecmp(dup, "name") == 0) {
		w = gtk_label_new(mt->name);
	} else if (g_ascii_strcasecmp(dup, "id") == 0) {
		tmp = g_strdup_printf("%d", mt->id);
		w = gtk_label_new(tmp);
		g_free(tmp);
	} else if (g_ascii_strcasecmp(dup, "team_id") == 0) {
		tmp = g_strdup_printf("%d", mt->team_id);
		w = gtk_label_new(tmp);
		g_free(tmp);
	} else if (g_ascii_strcasecmp(dup, "filename") == 0) {
		w = gtk_label_new(mt->filename);
	} else if (g_ascii_strcasecmp(dup, "added") == 0) {
		w = gtk_label_new(mt->added);
	} else if (g_ascii_strcasecmp(dup, "team_name") == 0) {
		w = gtk_label_new(mt->team_name);
	} else if (g_ascii_strcasecmp(dup, "category") == 0) {
		tmp = g_strdup_printf("%d", mt->category);
		w = gtk_label_new(tmp);
		g_free(tmp);
	} else {
		tmp = g_strdup_printf("$(%s)",dup);
		w = gtk_label_new(tmp);
		g_free(tmp);
	}

	g_free(dup);

	return w;
}


GtkWidget *
mn_torrent_item_elt_next(gchar ** s, struct mononoke_torrent * mt)
{
	gint i;
	GtkWidget *w = 0;

	if (*s[0] == 0)
		return 0;

	if (*s[0] == '$') {
		i = mn_check_par(&(*s)[1]);
		if (i != -1) {
			// On a effectivement une variable
			w = mn_torrent_item_elt_from_var(&(*s)[2], mt);
			*s = &(*s)[i + 2];
			return w;
		}
	}
	// On a du texte
	gchar *t = g_strdup(*s);

	// On s'arrete a la premiere variable rencontree
	for (i = 0; TRUE; i++) {
		if (t[i] == 0) {
			*s = &(*s)[i];
			break;
		}
		if (t[i] == '$')
			if (mn_check_par(&t[1 + i]) != -1) {
				t[i] = 0;
				*s = &(*s)[i];
				break;
			}
	}
	w = gtk_label_new(t);
	g_free(t);

	return w;
}

GtkWidget *
mn_torrent_item(struct mononoke_torrent * mt)
{
	GtkWidget *item;
	GtkWidget *hbox;
	GtkWidget *tmp;
	gchar *model, *p;

	p = model = g_strdup(mn.cfg.torrent_syntax);

	// Menu de base
	item = gtk_menu_item_new();
	hbox = gtk_hbox_new(FALSE, 1);
	gtk_container_add(GTK_CONTAINER(item), hbox);

	while ((tmp = mn_torrent_item_elt_next(&p, mt)) != 0) {
		gtk_widget_show(tmp);
		gtk_box_pack_start(GTK_BOX(hbox), tmp, FALSE, FALSE, 0);
	}

	gtk_container_set_border_width(GTK_CONTAINER(hbox), 0);
	gtk_container_set_border_width(GTK_CONTAINER(item), 0);
	
	// OnClick
	g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(mn_mononoke_torrent_clicked), mt);
	
	return item;
}
