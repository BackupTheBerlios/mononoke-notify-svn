
/* callbacks.h
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


void on_applybutton1_clicked(GtkButton * button, gpointer user_data);

void on_cancelbutton1_clicked(GtkButton * button, gpointer user_data);

void on_okbutton1_clicked(GtkButton * button, gpointer user_data);

void on_prefs_destroy(GtkObject * object, gpointer user_data);

void
on_browser_bt_clicked                  (GtkButton       *button,
                                        gpointer         user_data);
