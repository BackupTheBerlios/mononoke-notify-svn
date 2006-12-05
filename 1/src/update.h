#ifndef _UPDATE_H_
# define _UPDATE_H_

# include <glib.h>

void mn_update(void);
gpointer mn_update_thread_entry(gpointer data);

#endif
