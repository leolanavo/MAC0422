# A simple Makefile to automate work.
# By: Leonardo Lana

#########################################################
# Quick tip: when you start a project, enter its folder #
# and type in the terminal: make init.                  #
#########################################################

###################################################
# Subtitles:                                      #
#                                                 #
# BIN -> the name of the executable.              #
# CFLAGS -> the list of flags you want.           #
# FINALDIR -> the name of the directory that will #
#             be compressed in .tar.              #
# TARF -> the name of the .tar file.              #
# TEX -> the name of the .tex file.               #
#                                                 #
###################################################

BIN   	  := ep1sh ep1
TARF      := ep1-leonardo-beatriz
FINALDIR  := ep1-leonardo-beatriz
CFLAGS    := -Wall -std=c11
EXECFLAGS := -O2
TESTFLAGS := -g

CC    := gcc
MV    := mv
RM    := rm -f
CP    := cp -r
ECHO  := echo -e
MKDIR := mkdir -p
TAR   := tar -cvf

BINDIR := bin
SRCDIR := src
OBJDIR := obj
TSTDIR := test
TXTDIR := txt
INCDIR := include
LTXDIR := report

# main target
.PHONY: all
all: 
	$(foreach x, $(BIN), $(call create_vars,$x,exec))

.PHONY: ep1
ep1:
	$(call create_vars,ep1,exec)

.PHONY: ep1sh
ep1sh:
	$(call create_vars,ep1sh,exec)

.PHONY: test
debug:
	$(foreach x, $(BIN), $(call create_vars,$x,test))

#$(eval $(BINDIR)/$1)
#$(eval $(TSTDIR)/$1)

define create_vars
	$(eval SRC := $(strip $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/$1/*.c)))
	$(eval OBJ := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.c, $(SRC)))
	$(eval INC := $(strip $(wildcard $(INCDIR)/*.c) $(wildcard $(INCDIR)/$1/*.c)))
	$(eval ifeq ($2,exec))
		@$(ECHO) "EXEC"
	$(eval else)
		@$(ECHO) "TEST"
	$(eval endif)
endef

# build rules
$(BINDIR)/%: $(OBJ) | $(BINDIR)
	$(CC) $(CFLAGS) $(EXECFLAGS) -o $@ $^

$(TSTDIR)/%: $(OBJ) | $(TSTDIR)
	$(CC) $(CFLAGS) $(TESTFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/%.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# directory creation rules
$(OBJDIR) $(BINDIR) $(SRCDIR) $(INCDIR) $(TSTDIR) $(TXTDIR) $(FINALDIR) $(LTXDIR):
	@$(MKDIR) $@

# phony targets for automation
.PHONY: init
init: | $(SRCDIR) $(INCDIR) $(LTXDIR) $(TXTDIR) $(FINALDIR) $(BINDIR)
	@$(ECHO) "Creating directories..."
	$(eval DIRS := $(INCDIR) $(SRCDIR))
	$(foreach DIR, $(DIRS), $(foreach X, $(BIN), $(MKDIR) $(DIR)/$X))
	
	@$(ECHO) "Initializing repository..."
	@git init
	
	@$(ECHO) "Creating the .gitignore..."
	@$(ECHO) "$(OBJDIR)\n$(FINALDIR)\n$(TXTDIR)\n$(BINDIR)\n$(TSTDIR)\n.git" > .gitignore
	
	@$(ECHO) "Adding the initial files..."
	@git add $(SRCDIR) $(INCDIR) $(LTXDIR) .gitignore Makefile
	@git commit -m "Initial commit"
	@git push origin master
	
	@$(ECHO) "Finished"

.PHONY: clean
clean:
	@$(RM) $(OBJDIR)
	@$(RM) $(TSTDIR)
	@$(RM) $(LTXDIR)/*.dvi $(LTXDIR)/*.aux $(LTXDIR)/*.log

.PHONY: organize
organize:
	@$(MV) *.o $(OBJDIR)
	@$(MV) *.c $(SRCDIR)
	@$(MV) *.h $(INCDIR)
	@$(MV) *.txt $(TXTDIR)

.PHONY: tar
tar: clean | $(FINALDIR)
	@$(ECHO) "Copying files..."
	@$(CP) $(SRCDIR) $(FINALDIR)
	@$(CP) $(INCDIR) $(FINALDIR)
	@$(CP) $(LTXDIR) $(FINALDIR)
	@$(CP) Makefile $(FINALDIR)
	@$(ECHO) "Compressing..."
	@$(TAR) $(TARF).tar.gz $(FINALDIR)

.PHONY: upload
upload:
	@git add --all
	@git commit -m "Upload all the files"
	@git push origin master
