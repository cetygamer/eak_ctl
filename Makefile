CROSS_COMPILE := arm-linux-gnueabihf-
CC            := $(CROSS_COMPILE)gcc
READELF       := $(CROSS_COMPILE)readelf

SRC         := eak_ctl.c MQTT-C/src/mqtt.c MQTT-C/src/mqtt_pal.c
OUT         := eak_ctl.so
TARGET_LIBS ?= firmware/extracted/rootfs/lib

CFLAGS_COMMON  := -fPIC -O2 -fno-stack-protector -Wextra -Wall -std=gnu99 -IMQTT-C/include -Wno-unused-parameter -Wno-unused-variable -Wno-duplicate-decl-specifier -D_TIME_BITS=32 -U_FILE_OFFSET_BITS
LDFLAGS_COMMON := -L$(TARGET_LIBS) -Wl,-rpath-link,$(TARGET_LIBS) -Wl,--no-as-needed
LDLIBS_COMMON  := -l:libdl.so.2 -l:libc.so.6 -lgcc

CFLAGS_EAK_CTL  := -nostdlib -fvisibility=hidden $(CFLAGS_COMMON)
LDFLAGS_EAK_CTL := -shared $(LDFLAGS_COMMON)
LDLIBS_EAK_CTL  := -l:libpthread.so.0  $(LDLIBS_COMMON)

CFLAGS_TEST  := $(CFLAGS_COMMON)
LDFLAGS_TEST := -rdynamic $(LDFLAGS_COMMON)
LDLIBS_TEST  := $(LDLIBS_COMMON)

PANEL ?= 192.168.3.14

.PHONY: all check deploy test check-test deploy-test clean

all: $(OUT) check

$(OUT): $(SRC) | $(TARGET_LIBS)/libc.so.6
	$(CC) $(CFLAGS_EAK_CTL) -o $@ $^ $(LDFLAGS_EAK_CTL) $(LDLIBS_EAK_CTL)
	@echo "built $@ ($$(wc -c < $@) bytes)"

$(TARGET_LIBS)/libc.so.6:
	@echo "ERROR: device libs not found at $(TARGET_LIBS)"
	exit 1

check: $(OUT)
	@echo "--- glibc symbol versions referenced (must be <= 2.30) ---"
	@$(READELF) --dyn-syms $(OUT) | grep -oE 'GLIBC_[0-9.]+' | sort -u | sed 's/^/  /'
	@bad=$$($(READELF) --dyn-syms $(OUT) | grep -oE 'GLIBC_2\.(3[1-9]|[4-9][0-9])' | sort -u); \
	 if [ -n "$$bad" ]; then echo "FAIL: newer than 2.30: $$bad"; exit 1; \
	 else echo "OK: nothing newer than GLIBC_2.30"; fi
	@iso=$$($(READELF) --dyn-syms $(OUT) | grep -oE '__isoc2[0-9]_[a-z]+' | sort -u); \
	 if [ -n "$$iso" ]; then echo "FAIL: unversioned modern symbol(s) absent on glibc 2.30: $$iso"; exit 1; \
	 else echo "OK: no __isoc2x_* symbols"; fi
	@echo "--- NEEDED ---"; $(READELF) -d $(OUT) | grep NEEDED | sed 's/^/  /'

SSH ?= ssh -o StrictHostKeyChecking=no -o HostKeyAlgorithms=+ssh-rsa -o PubkeyAcceptedAlgorithms=+ssh-rsa

deploy: $(OUT)
	$(SSH) root@$(PANEL) 'cat > /customer/$<' < $<

test: test.c
	$(CC) $(CFLAGS_TEST) -o $@ $^ $(LDFLAGS_TEST) $(LDLIBS_TEST)

check-test: test
	@echo "--- glibc symbol versions referenced (must be <= 2.30) ---"
	@$(READELF) --dyn-syms test | grep -oE 'GLIBC_[0-9.]+' | sort -u | sed 's/^/  /'
	@bad=$$($(READELF) --dyn-syms test | grep -oE 'GLIBC_2\.(3[1-9]|[4-9][0-9])' | sort -u); \
	 if [ -n "$$bad" ]; then echo "FAIL: newer than 2.30: $$bad"; exit 1; \
	 else echo "OK: nothing newer than GLIBC_2.30"; fi
	@iso=$$($(READELF) --dyn-syms test | grep -oE '__isoc2[0-9]_[a-z]+' | sort -u); \
	 if [ -n "$$iso" ]; then echo "FAIL: unversioned modern symbol(s) absent on glibc 2.30: $$iso"; exit 1; \
	 else echo "OK: no __isoc2x_* symbols"; fi
	@echo "--- NEEDED ---"; $(READELF) -d test | grep NEEDED | sed 's/^/  /'

deploy-test: test
	$(SSH) root@$(PANEL) 'cat > /tmp/$<' < $<

clean:
	rm -f $(OUT)
	rm -f test
