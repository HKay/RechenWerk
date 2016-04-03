BINARY        := zaehlwerk.bin
CUNIT_BINARY  := unittests
BROOT         := build
BROOT_CUNIT   := $(BROOT)/cunit
BROOT_RELEASE := $(BROOT)/release

CC=gcc


SRC_FILES := $(wildcard *.c)
HDR_FILES := $(wildcard *.h)
OBJ_FILES := $(SRC_FILES:%.c=$(BROOT_RELEASE)/%.o)

CUNIT_SRC_FILES := $(wildcard cunit/*.c)
CUNIT_OBJ_FILES := $(CUNIT_SRC_FILES:cunit/%.c=$(BROOT_CUNIT)/%.o)

RELEASE_DEFINES =  -DCOMPILE_DATE=\"$(COMPILE_DATE)\"
RELEASE_DEFINES += -DF_CPU=16000000UL

LDFLAGS_WRAP  := -Wl,-wrap,main
LDFLAGS_CUNIT := -L/usr/local/lib -Wl,-Bstatic -lcunit -Wl,-Bdynamic

BASE_CFLAGS = -O0 -pedantic -std=c99
CFLAGS      = $(BASE_CFLAGS)
LDFLAGS     = -fPIC



.PHONY: all release dirs clean cunit printall

all: dirs release
release: $(BROOT_RELEASE)/$(BINARY)
test: TEST_CFLAGS = -g
test: TEST_DEFINES = -DPRE_POINT_DIGITS=5 -DPOST_POINT_DIGITS=8 
test: dirs release $(BROOT_CUNIT)/$(CUNIT_BINARY)

clean:
	@printf "DELETE \033\13301;33m-\033\13301;37m %-20s\n\033\13300;39m" $(BROOT)
	@rm -r $(BROOT)
	@rm cunit/*~
	@rm *~

dirs:
	@mkdir -p $(BROOT_RELEASE)
	@mkdir -p $(BROOT_CUNIT)



##########
# LINK
$(BROOT_RELEASE)/$(BINARY): $(OBJ_FILES)
	@printf "LINK  \033\13301;33m-\033\13301;37m %-20s\n\033\13300;39m" $@
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LDFLAGS) -o $@


$(BROOT_CUNIT)/$(CUNIT_BINARY): $(CUNIT_OBJ_FILES)
	@printf "LINK  \033\13301;33m-\033\13301;37m %-20s\n\033\13300;39m" $@
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(CUNIT_OBJ_FILES) $(LDFLAGS) $(LDFLAGS_WRAP) $(LDFLAGS_CUNIT) $(LDFLAGS) -o $@



##########
# COMPILE
$(BROOT_RELEASE)/%.o: %.c
	@printf "BUILD \033\13301;33m-\033\13301;37m %-20s %s\033\13300;39m\n" $< $@
	@$(CC) -c $(CFLAGS) $(TEST_CFLAGS) $(TEST_DEFINES) $< -o $@

$(BROOT_CUNIT)/%.o: cunit/%.c
	@printf "BUILD   \033\13301;33m-\033\13301;37m %-20s %s\033\13300;39m\n" $< $@
	@$(CC) -c $(CFLAGS) $(TEST_CFLAGS) $(TEST_DEFINES) $< -o $@
