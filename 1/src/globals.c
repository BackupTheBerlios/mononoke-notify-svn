
/* my_globals.c
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


#define _MY_GLOBALS_C_

#include <string.h>
#include <glib.h>
#include "globals.h"


void
mn_data_init(void)
{
	memset(&mn, 0, sizeof (struct global_data));
	mn.env.icons_dir =
		g_strdup_printf("%s/mononoke-notify/icons", g_get_user_config_dir());
	mn.env.xml_dir =
		g_strdup_printf("%s/mononoke-notify/xml", g_get_user_config_dir());
}
