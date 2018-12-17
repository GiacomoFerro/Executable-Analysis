#!/bin/bash

gcc nascondi-time-mod.c -shared -o nascondi-time-mod.32

LD_PRELOAD=./nascondi-time-mod.32 ./ggfm >> outputGGFM.txt
