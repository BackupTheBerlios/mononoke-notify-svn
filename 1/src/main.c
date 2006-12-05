
/* main.c
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


#include <gtk-2.0/gtk/gtk.h>
#include <glib.h>
#include <glib/gstdio.h>
#include <stdio.h>
#include <unistd.h>

#include "eggtrayicon.h"
#include "download.h"
#include "xml_user_info.h"
#include "config.h"
#include "globals.h"
#include "tray_menu.h"
#include "update.h"
#include "notify_area.h"
#include "dir.h"


int
main(int argc, char **argv)
{
	if (!g_thread_supported())	// Pour le multithreading
		g_thread_init(NULL);
	gdk_threads_init();
	gtk_init(&argc, &argv);		// Initialistaion gtk
	mn_data_init();				// Initialisation des globales
	mn.lock = g_mutex_new();
	mn_check_all_dir();
	mn_download_base();
	mn_load_config();			// On charge data/config.xml
	mn_update();				// On telecharge et mets a jour le menu
	mn_notify_init();			// Initialisation de la notify area (thx xchat)
	gdk_threads_enter();		// Pour que gdk puisse 'locker'
	gtk_main();					// Main loop
	g_mutex_free(mn.lock);
	gdk_threads_leave();		// Besoin de l'expliquer ? :]

	return 0;
}
