#!/bin/sh

# Hello World C example for the Neo6502 (build script)
#
# requires 'cc65' compiler suite


# cc65 search paths
#readonly _CC65_HOME="${CC65_HOME:/opt/homebrew/share/cc65}"
readonly _CC65_HOME="/opt/homebrew/share/cc65"


# environment checks
for prog in ar65 ca65 cl65
do  which $prog > /dev/null || ! echo "could not find '$prog' program" || exit 1
done
for inc in "$_CC65_HOME"/{include/{stdio.h,stdint.h},asminc/zeropage.inc}
do  dir=$(dirname "$inc")
    test -d "$dir" || ! echo "CC65 include directory '$dir' does not exist" || exit 1
    test -f "$inc" || ! echo "CC65 include file '$inc' does not exist"      || exit 1
done


# cleanup
rm -f *.o main.neo main.map neo6502.lib{,.temp}

#genera rooms
#python3 genera_array.py

# compile
export CC65_HOME="$_CC65_HOME"
ca65 crt0.s
ar65 a neo6502.lib crt0.o
cl65 --static-locals -t none -C neo6502.cfg -O --cpu 65c02 -m main.map \
     -o main.neo main.c api.c utility.c sprite.c neo6502.lib
 
# launch emulator
test -f main.neo && ./neo main.neo@800 cold
