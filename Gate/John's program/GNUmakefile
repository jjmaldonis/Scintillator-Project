# $Id: GNUmakefile,v 1.1 1999/01/07 16:05:40 gunter Exp $
# --------------------------------------------------------------
# GNUmakefile Non-uniform sampling calorimeter  John Neuhaus 1/12/10.
# --------------------------------------------------------------

name := NUCalo
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

CPPFLAGS += -I$(ROOTSYS)/include
EXTRALIBS := -L$(ROOTSYS)/lib libCore.lib libTree.lib libCint.lib libReflex.lib libCintex.lib libRIO.lib libHist.lib

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/binmake.gmk
