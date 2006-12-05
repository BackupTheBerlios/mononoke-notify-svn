
/* parsing.c
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


#define _PARSING_C_

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "globals.h"
#include "xml_user_info.h"


static double
mn_byte_to_Gbyte(const char *str)
{
	if (str == 0)
		return 0;
	return atof(str) / 1024 / 1024 / 1024;
}

void
mn_parse_torrent_list_item(xmlDocPtr doc, xmlNodePtr cur, struct mononoke_torrent *mt)
{
	cur = cur->children;
	gchar *tmp;

	while (cur) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "id"))) {
			tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (tmp) {
				mt->id = atoi(tmp);
			} else {
				mt->id = 0;
			}
			g_free(tmp);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "leechers"))) {
			tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (tmp) {
				mt->leechers = atoi(tmp);
			} else {
				mt->leechers = 0;
			}
			g_free(tmp);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "seeders"))) {
			tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (tmp) {
				mt->seeders = atoi(tmp);
			} else {
				mt->seeders = 0;
			}
			g_free(tmp);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "name"))) {
			mt->name = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "team"))) {
			tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (tmp) {
				mt->team_id = atoi(tmp);
			} else {
				mt->team_id = 0;
			}
			g_free(tmp);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "filename"))) {
			mt->filename = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "seed_ratio"))) {
			tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (tmp) {
				mt->seed_ratio = atof(tmp);
			} else {
				mt->seed_ratio = 0;
			}
			g_free(tmp);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "free_download"))) {
			tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (tmp) {
				mt->free_download = atoi(tmp);
			} else {
				mt->free_download = 0;
			}
			g_free(tmp);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "category"))) {
			tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (tmp) {
				mt->category = atoi(tmp);
			} else {
				mt->category = 0;
			}
			free(tmp);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "times_completed"))) {
			tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (tmp) {
				mt->times_completed = atoi(tmp);
			} else {
				mt->times_completed = 0;
			}
			g_free(tmp);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "size"))) {
			tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (tmp) {
				mt->size = atol(tmp);
			} else {
				mt->size = 0;
			}
			g_free(tmp);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "added"))) {
			mt->added = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "numfiles"))) {
			tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (tmp) {
				mt->numfiles = atoi(tmp);
			} else {
				mt->numfiles = 0;
			}
			g_free(tmp);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "ratings"))) {
			tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (tmp) {
				mt->rating = atof(tmp);
			} else {
				mt->rating = 0;
			}
			g_free(tmp);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "cat_name"))) {
			mt->cat_name = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "is_hentai"))) {
			tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (tmp) {
				mt->is_hentai = atoi(tmp);
			} else {
				mt->is_hentai = 0;
			}
			g_free(tmp);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "team_name"))) {
			mt->team_name = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "main_genre"))) {
			tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (tmp) {
				mt->main_genre = atoi(tmp);
				g_free(tmp);
			} else {
				mt->main_genre = 0;
			}
		}
		cur = cur->next;
	}
}

void
mn_free_torrent_list(struct torrent_list *tl)
{
	int i;

	for (i = 0; i < tl->count; i++) {
		if (tl->torrent[i].name != 0)
			free(tl->torrent[i].name);
		if (tl->torrent[i].filename != 0)
			free(tl->torrent[i].filename);
		if (tl->torrent[i].added != 0)
			free(tl->torrent[i].added);
		if (tl->torrent[i].cat_name != 0)
			free(tl->torrent[i].cat_name);
		if (tl->torrent[i].team_name != 0)
			free(tl->torrent[i].team_name);
	}
	tl->count = 0;
}

void
mn_parse_torrent_list(xmlDocPtr doc, xmlNodePtr cur, struct torrent_list *tl)
{
	int i;

	cur = cur->children;
	for (i = 0; i < 10 && cur != 0;) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "item"))) {
			mn_parse_torrent_list_item(doc, cur, &(tl->torrent[i]));
			i++;
		}
		cur = cur->next;
	}
	tl->count = i;
}

void
mn_xml_user_info_parse(void)
{
	xmlDocPtr doc;
	xmlNodePtr cur;
	gchar *tmp;

	mn_free_torrent_list(&mn.xml.need_seed);
	mn_free_torrent_list(&mn.xml.sorties);
	mn_free_torrent_list(&mn.xml.latest);

	tmp = g_strdup_printf("%s/user_info.xml", mn.env.xml_dir);

	doc = xmlParseFile(tmp);
	if (doc == NULL) {
		fprintf(stderr, "Document not parsed successfully. \n");
		return;
	}

	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		fprintf(stderr, "empty document\n");
		xmlFreeDoc(doc);
		return;
	}

	if (xmlStrcmp(cur->name, (const xmlChar *) "data")) {
		fprintf(stderr, "document of the wrong type, root node != data");
		xmlFreeDoc(doc);
		return;
	}

	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "upload"))) {
			tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			mn.xml.uploaded = mn_byte_to_Gbyte(tmp);
			free(tmp);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "download"))) {
			tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			mn.xml.downloaded = mn_byte_to_Gbyte(tmp);
			free(tmp);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "download_free"))) {
			tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			mn.xml.free_downloaded = mn_byte_to_Gbyte(tmp);
			free(tmp);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "unread"))) {
			tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			mn.xml.new_pm = atoi(tmp);
			free(tmp);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "need_seed"))) {
			mn_parse_torrent_list(doc, cur, &mn.xml.need_seed);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "sorties"))) {
			mn_parse_torrent_list(doc, cur, &mn.xml.sorties);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "latest"))) {
			mn_parse_torrent_list(doc, cur, &mn.xml.latest);
		}
		cur = cur->next;
	}
	xmlFreeDoc(doc);
}
