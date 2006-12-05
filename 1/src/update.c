#include "globals.h"
#include "xml_user_info.h"
#include "tray_menu.h"
#include "download.h"
#include "interface.h"
#include "support.h"
#include "update.h"

void
mn_update(void)
{
	g_thread_create(mn_update_thread_entry, 0, 0, 0);
}

gpointer
mn_update_thread_entry(gpointer data)
{
	/* Locking gtk and global data */
	gdk_threads_enter();
	g_mutex_lock(mn.lock);
	/* Download xml */
	mn_download_xml();
	/* Parse xml */
	mn_xml_user_info_parse();
	/* Make the menu */
	if (mn.ui.tray_menu != 0)
		gtk_widget_destroy(mn.ui.tray_menu);
	mn_tray_menu_init();
	/* Unlocking */
	g_mutex_unlock(mn.lock);
	gdk_threads_leave();

	return NULL;
}
