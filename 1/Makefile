SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)
CFLAGS = -pipe -fomit-frame-pointer -Wall \
	`pkg-config --cflags glib-2.0 gthread-2.0 gtk+-2.0 libxml-2.0 libcurl`
LDFLAGS = `pkg-config --libs glib-2.0 gthread-2.0 gtk+-2.0 libxml-2.0 libcurl`
RELEASE = mononoke-notify

all: mononoke-notify

mononoke-notify: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(RELEASE)
clean:
	find . -name '*~' -o -name '*.o' -o -name '*.bak' | xargs rm -f \
	data/category_* data/team_* data/config.xml

run: all
	./mononoke-notify

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

depend:
	$(RM) .depend
	makedepend -f- -- $(CFLAGS) -- $(SRCS) > .depend

include .depend
