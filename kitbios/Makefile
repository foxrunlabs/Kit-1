#===============================================================================
# Copyright 2019 Ryan Clarke
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License. You may obtain a copy of
# the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations under
# the License.
#===============================================================================

#===============================================================================
# Program   : KitBIOS
# File Name : Makefile
# Project   : Kit-1 8-bit Computer
# Author    : Ryan Clarke
# E-mail    : kj6msg@icloud.com
#-------------------------------------------------------------------------------
# Purpose   : Makefile for the Kit-1 BIOS.
#===============================================================================


SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .a65 .o

PREFIX   = .
SRCDIR   = $(PREFIX)/src
BUILDDIR = $(PREFIX)/build
BINDIR   = $(PREFIX)/bin

VPATH = $(SRCDIR)

BIN  = kitbios.bin
OBJS = kitbios.o kitmon.o sdcard.o spi.o

PY65 = 

AS      = ca65
ASFLAGS = --cpu 65C02 -l $(BUILDDIR)/$(basename $@).lst -t none $(PY65)

LD       = ld65
LDCONFIG = memory.conf
LDFLAGS  = -C $(LDCONFIG) -m $(BUILDDIR)/$(basename $@).map --obj-path $(BUILDDIR)

.PHONY: all
all : $(BIN)

%.o : %.a65 kit1.inc
	@mkdir -p $(BUILDDIR)
	$(AS) $(ASFLAGS) -o $(BUILDDIR)/$@ $<

$(BIN) : $(OBJS)
	@mkdir -p $(BINDIR)
	$(LD) $(LDFLAGS) -o $@ $^
	@mv $(BIN) $(BINDIR)

.PHONY: sim
sim : py65 all

.PHONY: py65
py65 :
	$(eval PY65 = -D PY65)

.PHONY: clean
clean :
	rm -rf $(BUILDDIR)
	rm -rf $(BINDIR)
