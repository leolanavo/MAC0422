#################################################
# Leonardo Lana Violin Oliveira - NUSP: 9793735 #
# Beatriz Figuereido Marouelli  - NUSP: 9793652 #
#################################################

EXECFLAGS := -O2
TESTFLAGS := -g

CC    := gcc
MV    := mv
RM    := rm -f
RMDIR := rm -rf
CP    := cp -r
ECHO  := echo -e
MKDIR := mkdir -p
TAR   := tar -cvf

BINDIR := bin
SRCDIR := src
OBJDIR := build
TSTDIR := test
TXTDIR := txt
INCDIR := include
LTXDIR := report

-include Config.mk

ROOT := $(SRCDIR) $(INCDIR) $(LTXDIR) $(TXTDIR) $(FINALDIR) $(TSTDIR) $(OBJDIR)

ifneq ($(words $(BIN)), 1)
ROOT += $(foreach r,$(INCDIR) $(SRCDIR) $(OBJDIR),$(foreach b,$(BIN),$r/$b))
$(foreach x,$(BIN),\
  $(eval $x.SRC := $(strip $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/$x/*.c)))\
  $(eval $x.OBJ := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $($x.SRC)))\
  $(eval $x.INC := $(strip $(wildcard $(INCDIR)/*.h) $(wildcard $(INCDIR)/$x/*.h))))
else
$(foreach x,$(BIN),\
  $(eval $x.SRC := $(strip $(wildcard $(SRCDIR)/*.c)))\
  $(eval $x.OBJ := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $($x.SRC)))\
  $(eval $x.INC := $(strip $(wildcard $(INCDIR)/*.h))))
endif

# main target
.PHONY: all
all: CFLAGS += $(EXECFLAGS)
all: $(addprefix $(BINDIR)/,$(BIN))

.PHONY: debug
debug: clean
debug: CFLAGS += $(TESTFLAGS)
debug: $(addprefix $(TSTDIR)/,$(BIN))

.PHONY: nothing
nothing:
	@echo $(BIN)
	@echo $(LDFLAGS)
	@echo $(CFLAGS)
	@echo $(ROOT)
	@echo $(ep2.SRC)

# Compile each one of the binaries
define bin-factory
$$(BINDIR)/$1: $$($1.OBJ) | $$(BINDIR)
	$$(CC) $$^ -o $$@  $$(CFLAGS) $$(LDFLAGS)
endef
$(foreach x,$(BIN),$(eval $(call bin-factory,$x)))

define test-factory
$$(TSTDIR)/$1: $$($1.OBJ) | $$(TSTDIR)
	$$(CC) $$^ -o $$@  $$(CFLAGS) $$(LDFLAGS)
endef
$(foreach x,$(BIN),$(eval $(call test-factory,$x)))

define object-factory
$$(OBJDIR)/$1.o: $$(SRCDIR)/$1.c $$(wildcard $$(INCDIR)/$1.h) | $$(OBJDIR) $$(ROOT)
	$$(CC) -c $$< -o $$@ $$(CFLAGS) $$(LDFLAGS)
endef
$(foreach b,$(BIN),\
	$(foreach obj,$($b.OBJ),\
		$(eval $(call object-factory,$(patsubst $(OBJDIR)/%.o,%,$(obj))))))

# Directory creation rules
$(ROOT) $(BINDIR):
	@$(MKDIR) $@

# phony targets for automation
.PHONY: init
init: | $(ROOT)
	@$(ECHO) "Creating the .gitignore..."
	@$(ECHO) "$(OBJDIR)\n$(FINALDIR)\n$(TXTDIR)\n$(BINDIR)\n$(TSTDIR)\n.git" > .gitignore
	@$(ECHO) "Finished"

.PHONY: clean
clean:
	@$(RMDIR) $(OBJDIR)
	@$(RMDIR) $(TSTDIR)
	@$(RM) $(LTXDIR)/*.dvi $(LTXDIR)/*.aux $(LTXDIR)/*.log

.PHONY: organize
organize:
	@$(MV) *.o $(OBJDIR)
	@$(MV) *.c $(SRCDIR)
	@$(MV) *.h $(INCDIR)
	@$(MV) *.txt $(TXTDIR)

.PHONY: package
package: clean | $(FINALDIR)
	@$(ECHO) "Copying files..."
	@$(CP) $(SRCDIR) $(FINALDIR)
	@$(CP) $(INCDIR) $(FINALDIR)
	@$(CP) $(LTXDIR) $(FINALDIR)
	@$(CP) Makefile $(FINALDIR)

	@$(ECHO) "Compressing..."
	@$(TAR) $(TARF).tar.gz $(FINALDIR)

	@$(ECHO) "Cleaning..."
	@$(RMDIR) $(FINALDIR)
