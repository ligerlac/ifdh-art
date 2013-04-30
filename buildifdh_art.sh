#!/bin/sh
case "$1$2" in
*debug*) sfdflag="-d" ;;
*prof*)  sfdflag="-p" ;;
*)       sfdflag="-d" ;;
esac

ups build -. ifdh_art -q $1:$2 -O $sfdflag
