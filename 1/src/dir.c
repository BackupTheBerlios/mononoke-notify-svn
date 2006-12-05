
/* dir.c
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
#include <glib/gstdio.h>

#include "dir.h"
#include "globals.h"

void
mn_check_all_dir(void)
{
	if (g_file_test(mn.env.icons_dir, G_FILE_TEST_IS_DIR) == FALSE) {
		g_mkdir_with_parents(mn.env.icons_dir, 0x1ed);
	}

	if (g_file_test(mn.env.xml_dir, G_FILE_TEST_IS_DIR) == FALSE) {
		g_mkdir_with_parents(mn.env.xml_dir, 0x1ed);
	}
}
