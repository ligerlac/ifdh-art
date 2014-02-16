#!/bin/sh

ds=`date +%s`
export SAM_PROJECT_NAME="test_art_sam_wrap_$USER_$ds"
export EXPERIMENT="nova"

ups setup -r `dirname $0` ifdh_art -q e4:debug

ifdh startProject  $SAM_PROJECT_NAME  $EXPERIMENT  mwm_test_8 mengel  $EXPERIMENT

printenv

echo "testing pre/post"

./art_sam_wrap.sh \
	--exe echo \
	--conf /dev/null \
	--prescript "echo:hi:there" \
        --postscript "echo:bye:bye"

