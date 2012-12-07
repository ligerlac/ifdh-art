#!/bin/sh

#
# This script assumes it is run under a jobsub-generated wrapper
# which sets environment variables:
#  $SAM_PROJECT_NAME 
#  $EXPERIMENT
# and also has setup whatever is needed to find the art executable
# (i.e. "nova" or "gm2") for that experiment
#

# defaults
dest=""
conf=/dev/null
exe=$EXPERIMENT
quals=nu:e2:debug
vers=v0_2
renam=none

datadir=$TMPDIR/ifdh_$$

#
# parse options we know, collect rest in $args
#
while [ $# -gt 0 ]
do
    case "x$1" in
    x-q|x--quals)   quals="$2"; shift; shift; continue;;
    x-c|x--config)  conf="$2";  shift; shift; continue;;
    x-D|x--dest)    dest="$2";  shift; shift; continue;;
    x-X|x--exe)     cmd="$2";   shift; shift; continue;;
    x-v|x--vers)    vers="$2";  shift; shift; continue;;
    x-R|x--rename)  renam="$2"; shift; shift; continue;;
    *)              args="$args \"$1\""; shift; continue;;
    esac
    break
done

if [ "x$IFDH_ART_DIR" = "x" ] 
then
    . `ups setup -j ifdh_art $vers -q $quals:`
fi

if [ "x$IFDH_BASE_URI" = "x" ]
then
    export IFDH_BASE_URI=http://samweb.fnal.gov:8480/sam/$EXPERIMENT/api
fi

hostname=`hostname --fqdn`
projurl=`ifdh findProject $SAM_PROJECT_NAME $EXPERIMENT`
sleep 5
consumer_id=`ifdh establishProcess $projurl demo 1 $hostname $GRID_USER "" "" ""`

update_via_fcl=true

if $update_via_fcl
then

    cp $conf ${TMPDIR:=/var/tmp}/conf.$$
    conf=$TMPDIR/conf.$$
    cat >> $conf <<EOF
services.user.IFDH: {}
services.user.IFDH.debug: "1"
services.user.CatalogInterface.service_provider: "IFCatalogInterface"
services.user.CatalogInterface.webURI: "$projurl"
services.user.FileTransfer.service_provider: "IFFileTransfer"
source.fileNames: [ "$consumer_id" ]
EOF

else
    args="$args \"--sam-web-uri=$projurl\" \"--sam-process-id=$consumer-id\""
fi

echo project url: $projurl
echo consumer id: $consumer_id

cd $TMPDIR

command="\"${cmd}\" -c \"$conf\" $args"
echo "Running: $command"
eval "$command"
res=$?

#
# ART can't currently name output files based on input files
#    so we have  a pass here to rename output files either
#    "uniq" -- unique prefix
#    "s/this/that/" -- make output input file with changes
#  We rename the files and change the output_list, so the
#  ifdh copyBackOutput will copy back the updated names.
#
case $renam in
none) ;;
uniq) while read f < $datadir/output_list
      do
         fnew="u_$hostname_$$_$f"
         echo $fnew >> $datadir/output_list.new
         mv $datadir/$f $datadir/$fnew
      done
      mv $datadir/output_list.new $datadir/output_list
      ;;
s/* ) 
      fix="sed -e $renam"
      pr -t -2 $datadir/output_list $datadir/input_list 
      while read f  infile
      do
         fnew=`echo $infile | $fix`
         echo $fnew >> $datadir/output_list.new
         mv $datadir/$f $datadir/$fnew
      done
      mv $datadir/output_list.new $datadir/output_list
      ;;
esac


if [ "x$dest" != "x" && "$res" = "0" ]
then
    ifdh copyBackOutput "$dest"
fi

ifdh cleanup

if $update_via_fcl
then
    rm ${conf}
fi

exit $res
