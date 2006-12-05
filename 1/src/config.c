
/* config.c
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
#include <glib.h>
#include <glib/gprintf.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xmlwriter.h>


#define _CONFIG_C_
#include "config.h"
#include "tray_menu.h"
#include "globals.h"
#include "prefs_dlg.h"

void
mn_load_config_default(void)
{
	g_mutex_lock(mn.lock);
	mn.cfg.user_login = 0;
	mn.cfg.browser = "firefox";
	mn.cfg.nbr_latest_torrent = 5;
	mn.cfg.icon_size = 20;
	mn.cfg.torrent_syntax = "$(team_icon)$(anime_icon)$(packet_icon) "
		"L:$(leechers),S:$(seeders) << $(name) >>";
	g_mutex_unlock(mn.lock);
}

void
mn_load_config(void)
{
	xmlDocPtr doc;
	xmlNodePtr cur;
	gchar *filename;
	gchar *tmp;

	mn_load_config_default();
	filename = g_strdup_printf("%s/config.xml", mn.env.xml_dir);

	doc = xmlParseFile(filename);
	if (doc == NULL) {
		// On affiche la fenetre de prefs
		mn_prefs_show();
		return;
	}

	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		xmlFreeDoc(doc);
		// On affiche la fenetre de prefs
		mn_prefs_show();
		return;
	}

	if (xmlStrcmp(cur->name, (const xmlChar *) "mononoke-notify_config")) {
		xmlFreeDoc(doc);
		// On affiche la fenetre de prefs
		mn_prefs_show();
		return;
	}

	g_mutex_lock(mn.lock);
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "user_login"))) {
			mn.cfg.user_login =
				xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *) "browser"))) {
			mn.cfg.browser = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *) "nbr_latest_torrent"))) {
			tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			mn.cfg.nbr_latest_torrent = atoi(tmp);
			g_free(tmp);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *) "torrent_syntax"))) {
			mn.cfg.torrent_syntax =
				xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *) "icon_size"))) {
			tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			mn.cfg.icon_size = atoi(tmp);
			g_free(tmp);
		}
		cur = cur->next;
	}
	g_mutex_unlock(mn.lock);

	xmlFreeDoc(doc);
}

void
mn_save_config(void)
{
	int rc;
	xmlTextWriterPtr writer;
	gchar *filename;

	filename = g_strdup_printf("%s/config.xml", mn.env.xml_dir);

	/* Create a new XmlWriter for uri, with no compression. */
	writer = xmlNewTextWriterFilename(filename, 0);
	if (writer == NULL) {
		printf("testXmlwriterFilename: Error creating the xml writer\n");
		return;
	}

	/* Start the document with the xml default for the version,
	 * encoding ISO 8859-1 and the default for the standalone
	 * declaration. */
	rc = xmlTextWriterStartDocument(writer, NULL, "ISO-8859-1", NULL);
	if (rc < 0) {
		printf("testXmlwriterFilename: Error at xmlTextWriterStartDocument\n");
		return;
	}

	/* Start an element named "EXAMPLE". Since thist is the first
	 * element, this will be the root element of the document. */
	rc = xmlTextWriterStartElement(writer, BAD_CAST "mononoke-notify_config");
	if (rc < 0) {
		printf("testXmlwriterFilename: Error at xmlTextWriterStartElement\n");
		return;
	}

	g_mutex_lock(mn.lock);
	/* Write an element named "X_ORDER_ID" as child of HEADER. */
	xmlTextWriterWriteFormatElement(writer, BAD_CAST "user_login",
									mn.cfg.user_login);
	xmlTextWriterWriteFormatElement(writer, BAD_CAST "browser", mn.cfg.browser);
	xmlTextWriterWriteFormatElement(writer, BAD_CAST "nbr_latest_torrent",
									"%d", mn.cfg.nbr_latest_torrent);
	xmlTextWriterWriteFormatElement(writer, BAD_CAST "torrent_syntax",
									mn.cfg.torrent_syntax);
	xmlTextWriterWriteFormatElement(writer, BAD_CAST "icon_size",
									"%d", mn.cfg.icon_size);
	g_mutex_unlock(mn.lock);

	/* Close the element named HEADER. */
	rc = xmlTextWriterEndElement(writer);
	if (rc < 0) {
		printf("testXmlwriterFilename: Error at xmlTextWriterEndElement\n");
		return;
	}

	/* Here we could close the elements ORDER and EXAMPLE using the
	 * function xmlTextWriterEndElement, but since we do not want to
	 * write any other elements, we simply call xmlTextWriterEndDocument,
	 * which will do all the work. */
	rc = xmlTextWriterEndDocument(writer);
	if (rc < 0) {
		printf("testXmlwriterFilename: Error at xmlTextWriterEndDocument\n");
		return;
	}

	xmlFreeTextWriter(writer);
	g_free(filename);
}
