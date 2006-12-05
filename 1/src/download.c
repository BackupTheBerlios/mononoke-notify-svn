
/* download.c
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


#include <stdio.h>
#include <curl/curl.h>
#include <glib.h>
#include <glib/gstdio.h>

#include "globals.h"

gint
mn_download(const gchar * url, const gchar * filename)
{
	CURL *curl;
	CURLcode res;
	FILE *file;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		file = fopen(filename, "w+");
		if (file == 0) {
			fprintf(stderr, "Impossible d'ouvrir %s en ecriture\n", filename);
			return FALSE;
		}
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
		res = curl_easy_perform(curl);
		fclose(file);
		/* always cleanup */
		curl_easy_cleanup(curl);
	}

	return TRUE;
}

void
mn_download_base_file(const gchar * icon)
{
	gchar *filename;
	gchar *url;

	filename = g_strdup_printf("%s/%s", mn.env.icons_dir, icon);

	if (g_file_test(filename, G_FILE_TEST_EXISTS)) {
		g_free(filename);
		return;
	}

	url =
		g_strdup_printf("http://mononoke-bt.org/projets/mononoke-notify/icons/%s",
						icon);
	mn_download(url, filename);

	g_free(filename);
	g_free(url);
}

void
mn_download_base(void)
{
	mn_download_base_file("bomb.png");
	mn_download_base_file("cadeau0-large.png");
	mn_download_base_file("cadeau1-large.png");
	mn_download_base_file("cadeau2-large.png");
	mn_download_base_file("cadeau3-large.png");
	mn_download_base_file("contact.gif");
	mn_download_base_file("crazy.gif");
	mn_download_base_file("donate.gif");
	mn_download_base_file("download.gif");
	mn_download_base_file("grin.gif");
	mn_download_base_file("logout.gif");
	mn_download_base_file("mononoke.jpg");
	mn_download_base_file("my.gif");
	mn_download_base_file("refresh.gif");
	mn_download_base_file("search.gif");
	mn_download_base_file("smile1.gif");
	mn_download_base_file("upload.gif");
	mn_download_base_file("w00t.gif");
}

void
mn_download_xml(void)
{
	gchar *url;
	gchar *filename;

	url =
		g_strdup_printf("http://mononoke-bt.org/myinfos.php?login=%s&latest=%d&xml",
						mn.cfg.user_login, mn.cfg.nbr_latest_torrent);
	filename = g_strdup_printf("%s/user_info.xml", mn.env.xml_dir);
	mn_download(url, filename);

	g_free(url);
	g_free(filename);
}

void
mn_download_category_logo(gint category)
{
	gchar *url;
	gchar *filename;

	filename =
		g_strdup_printf("%s/category_%d.jpg", mn.env.icons_dir, category);

	if (g_file_test(filename, G_FILE_TEST_EXISTS)) {
		g_free(filename);
		return;
	}

	url = g_strdup_printf("http://mononoke-bt.org/pic/categories/%d.jpg", category);
	mn_download(url, filename);

	g_free(url);
	g_free(filename);
}

void
mn_download_team_logo(gint team_id)
{
	gchar *url;
	gchar *filename;

	filename = g_strdup_printf("%s/team_%d.jpg", mn.env.icons_dir, team_id);

	if (g_file_test(filename, G_FILE_TEST_EXISTS)) {
		g_free(filename);
		return;
	}

	url = g_strdup_printf("http://mononoke-bt.org/pic/teams/icons/%d.jpg", team_id);
	mn_download(url, filename);

	g_free(url);
	g_free(filename);
}

void
mn_download_genre_logo(gint genre_id)
{
	gchar *url;
	gchar *filename;

	filename = g_strdup_printf("%s/genre_%d.jpg", mn.env.icons_dir, genre_id);

	if (g_file_test(filename, G_FILE_TEST_EXISTS)) {
		g_free(filename);
		return;
	}

	url = g_strdup_printf("http://mononoke-bt.org/pic/genres/%d.jpg", genre_id);
	mn_download(url, filename);

	g_free(url);
	g_free(filename);
}
