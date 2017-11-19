#################################################
# Leonardo Lana Violin Oliveira - NUSP: 9793735 #
# Beatriz Figuereido Marouelli  - NUSP: 9793652 #
#################################################

EXECFLAGS := -O2
TESTFLAGS := -g

CC    := g++
CEXT  := cpp
HEXT  := h
OEXT  := o

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

ROOT := $(SRCDIR) $(INCDIR) $(LTXDIR) $(TXTDIR) $(TSTDIR) $(OBJDIR)

ifneq ($(words $(BIN)), 1)
ROOT += $(foreach r,$(INCDIR) $(SRCDIR) $(OBJDIR),$(foreach b,$(BIN),$r/$b))
$(foreach x,$(BIN),\
  $(eval $x.SRC := $(strip $(wildcard $(SRCDIR)/*.$(CEXT)) $(wildcard $(SRCDIR)/$x/*.$(CEXT))))\
  $(eval $x.OBJ := $(patsubst $(SRCDIR)/%.$(CEXT), $(OBJDIR)/%.$(OEXT), $($x.SRC)))\
  $(eval $x.INC := $(strip $(wildcard $(INCDIR)/*.$(HEXT)) $(wildcard $(INCDIR)/$x/*.$(HEXT)))))
else
$(foreach x,$(BIN),\
  $(eval $x.SRC := $(strip $(wildcard $(SRCDIR)/*.$(CEXT))))\
  $(eval $x.OBJ := $(patsubst $(SRCDIR)/%.$(CEXT), $(OBJDIR)/%.$(OEXT), $($x.SRC)))\
  $(eval $x.INC := $(strip $(wildcard $(INCDIR)/*.(HEXT)))))
endif

# main target
.PHONY: all
all: CFLAGS += $(EXECFLAGS)
all: $(addprefix $(BINDIR)/,$(BIN))

.PHONY: debug
debug: CFLAGS += $(TESTFLAGS)
debug: $(addprefix $(TSTDIR)/,$(BIN))

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
$$(OBJDIR)/$1.$(OEXT): $$(SRCDIR)/$1.$(CEXT) $$(wildcard $$(INCDIR)/$1.$(HEXT)) | $$(OBJDIR) $$(ROOT)
	$$(CC) -c $$< -o $$@ $$(CFLAGS) $$(LDFLAGS)
endef
$(foreach b,$(BIN),\
	$(foreach obj,$($b.OBJ),\
		$(eval $(call object-factory,$(patsubst $(OBJDIR)/%.$(OEXT),%,$(obj))))))

# Directory creation rules
$(ROOT) $(BINDIR) $(FINALDIR):
	@$(MKDIR) $@

# phony targets for automation
.PHONY: init
init: | $(ROOT)
	@$(ECHO) "Created core directories"

.PHONY: gitignore
gitignore:
	@$(ECHO) "Creating the .gitignore..."
	@$(ECHO) "$(OBJDIR)\n$(FINALDIR)\n$(TXTDIR)\n$(BINDIR)\n$(TSTDIR)\n.git" > .gitignore

.PHONY: clean
clean:
	@$(RMDIR) $(BINDIR)
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
	@$(CP) Config.mk $(FINALDIR)
	@$(CP) leiame.txt $(FINALDIR)

	@$(ECHO) "Compressing..."
	@$(TAR) $(TARF).tar.gz $(FINALDIR)

	@$(ECHO) "Cleaning..."
	@$(RMDIR) $(FINALDIR)
