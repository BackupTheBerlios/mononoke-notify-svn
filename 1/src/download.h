
/* download.h
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


#ifndef _DOWNLOAD_H_
# define _DOWNLOAD_H_

gint mn_download(const gchar * url, const gchar * filename);
void mn_download_base(void);
void mn_download_xml(void);
void mn_download_category_logo(gint category);
void mn_download_team_logo(gint team_id);
void mn_download_genre_logo(gint genre_id);
#endif
