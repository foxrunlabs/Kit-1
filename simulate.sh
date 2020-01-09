#!/bin/bash

BIN=kitbios/bin

py65mon -m 65C02 -l sdcard.bin -r $BIN/kitbios-sim.bin -o 0214 -i 0215
