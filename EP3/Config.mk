#################################################
# Leonardo Lana Violin Oliveira - NUSP: 9793735 #
# Beatriz Figuereido Marouelli  - NUSP: 9793652 #
#################################################

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

BIN       := ep3
TARF      := ep3-leonardo-beatriz
FINALDIR  := ep3-leonardo-beatriz

CFLAGS    := -std=c++11
LDFLAGS   := -I $(INCDIR)
