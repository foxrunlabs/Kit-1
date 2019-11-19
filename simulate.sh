#!/bin/bash

BIN=kitbios/bin

py65mon -m 65C02 -l $BIN/sdcard.bin -r $BIN/kitbios.bin -o 0214 -i 0215
