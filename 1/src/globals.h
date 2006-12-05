
/* my_globals.h
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


#ifndef _MY_GLOBALS_H_
# define _MY_GLOBALS_H_

# include <glib.h>
# include <gtk/gtk.h>
# include "config.h"

struct config_data {
	gchar *user_login;
	gchar *browser;

	gint nbr_latest_torrent;
	gchar *torrent_syntax;

	gint icon_size;
};

struct ui_data {
	GtkWidget *tray_menu;
	GtkWidget *prefs;
};

struct mononoke_torrent {
	gint id;
	gint leechers;
	gint seeders;
	gchar *name;
	gint team_id;
	gint main_genre;
	gchar *filename;
	gfloat seed_ratio;
	gint free_download;
	gint category;
	gint times_completed;
	glong size;
	gchar *added;
	gint numfiles;
	gfloat rating;
	gchar *cat_name;
	gint is_hentai;
	gchar *team_name;
};

struct torrent_list {
	struct mononoke_torrent torrent[10];
	gint count;
};

struct parsed_data {
	gdouble uploaded;
	gdouble downloaded;
	gdouble free_downloaded;
	gint new_pm;
	struct torrent_list need_seed;
	struct torrent_list sorties;
	struct torrent_list latest;
};

struct environment_data {
	gchar *icons_dir;
	gchar *xml_dir;
};

struct global_data {
	struct config_data cfg;
	struct ui_data ui;
	struct parsed_data xml;
	struct environment_data env;
	GMutex *lock;
};

# ifndef _MY_GLOBALS_C_
extern struct global_data mn;
# else
struct global_data mn;
# endif

void mn_data_init(void);

#endif
