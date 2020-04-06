CFLAGS+=-std=c11
CFLAGS+=-Wall -Wextra -Wpedantic -D_SVID_SOURCE -D_GNU_SOURCE
CFLAGS+=-Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline

all: hashclient

hashclient:

.PHONY: clean debug

clean:
	-rm *.o
	-rm hashclient

debug: CFLAGS+=-g
debug: all

profile: CFLAGS+=-pg
profile: LDFLAGS+=-pg
profile: all
