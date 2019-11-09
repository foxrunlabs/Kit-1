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
# Program   : bin2c
# File Name : Makefile
# Project   : Kit-1 8-bit Computer
# Author    : Ryan Clarke
# E-mail    : kj6msg@icloud.com
#-------------------------------------------------------------------------------
# Purpose : Makefile for the entire Kit-1 project. It will build the toolchain,
#           KitBIOS, and KitROM.
#===============================================================================


MAKE = make

.PHONY: all
all : tools bios bin2c rom

.PHONY: tools
tools :
	@echo "[Building toolchain]"
	@$(MAKE) -C tools

.PHONY: bios
bios :
	@echo "[Building KitBIOS]"
	@$(MAKE) -C kitbios

.PHONY: bin2c
bin2c :
	@echo "[Converting .BIN to .C]"
	tools/bin/bin2c kitbios/bin/kitbios.bin kitrom.X/src/kitbios.c

.PHONY: rom
rom :
	@echo "[Building KitROM]"
	@$(MAKE) -C kitrom.X

.PHONY: sim
sim :
	@echo "[Building KitBIOS (py65mon version)]"
	@$(MAKE) -C kitbios $@

.PHONY: clean
clean :
	@$(MAKE) -C tools $@
	@$(MAKE) -C kitbios $@
	@$(MAKE) -C kitrom.X $@
