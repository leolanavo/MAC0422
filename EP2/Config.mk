# Configuration file for the makefile

###################################################
# BIN -> binaries                                 #
# CFLAGS -> compilation flags                     #
# LDFLAGS -> linker flags                         #
# FINALDIR -> the name of the directory that will #
#             be compressed in .tar.gz            #
# TARF -> the name of the .tar.gz file            #
#                                                 #
###################################################

BIN       := ep2 
TARF      := ep2-leonardo-beatriz
FINALDIR  := ep2-leonardo-beatriz

CFLAGS    := -Wall -Werror -Wextra -std=gnu11
LDFLAGS   := -I $(INCDIR) 
