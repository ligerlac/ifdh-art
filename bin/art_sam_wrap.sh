#!/bin/sh

#
# This script assumes it is run under a jobsub-generated wrapper
# which sets environment variables:
#  $SAM_PROJECT_NAME 
#  $EXPERIMENT
#  $GRID_USER
# and also has setup whatever is needed to find the art executable
# (i.e. "nova" or "gm2") for that experiment
#

# defaults
dest=""
conf=/dev/null
exe=$EXPERIMENT
quals=nu:e2:debug
vers=v1_0_rc1
renam=""
limit=""
getconfig=false

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
    x-R|x--rename)     renam="$2";   shift; shift; continue;;
    x-X|x--exe)     cmd="$2";   shift; shift; continue;;
    x-v|x--vers)    vers="$2";  shift; shift; continue;;
    x-g|x--getconfig)getconfig=true; shift; continue;;
    x-R|x--rename)  renam="$2"; shift; shift; continue;;
    x-L|x--limit)   limit="$2"; shift; shift; continue;;
    *)              args="$args \"$1\""; shift; continue;;
    esac
    break
done

check_space() {
   set : `df -P . | tail -1`
   avail=$5
   if [ $avail -lt 100 ] 
   then
       echo "Not enough space on this node in `pwd`."
       df -H .
       exit 1
   fi
}

if [ "x$IFDH_ART_DIR" = "x" ] 
then
    . `ups setup ifdh_art $vers -q $quals:`
fi

if [ "x$CPN_DIR" = "x" ] 
then
    . `ups setup cpn -z /grid/fermiapp/products/common/db`
fi

if [ "x$IFDH_BASE_URI" = "x" ]
then
    export IFDH_BASE_URI=http://samweb.fnal.gov:8480/sam/$EXPERIMENT/api
fi

hostname=`hostname --fqdn`
projurl=`ifdh findProject $SAM_PROJECT_NAME $EXPERIMENT`
sleep 5
consumer_id=`ifdh establishProcess "$projurl" "$cmd" "$ART_VERSION" "$hostname" "$GRID_USER" "art" "" "$limit"`

echo project url: $projurl
echo consumer id: $consumer_id

cd $TMPDIR
check_space()

if $getconfig
then

    uri=`ifdh getNextFile $projurl $consumer_id`
    res=0
    while [ -n "$uri" -a "$res" = 0 ]
    do
	fname=`ifdh fetchInput "$uri"`
        conf="$fname"
	ifdh updateFileStatus $cpurl  $consumer_id $fname transferred
	command="\"${cmd}\" -c \"$conf\" $args"
        echo "Running: $command"
	if eval "$command"
        then 
	   ifdh updateFileStatus $cpurl  $consumer_id $fname consumed
        else
	   res=$?
	   ifdh updateFileStatus $cpurl  $consumer_id $fname skipped
        fi
        uri=`ifdh getNextFile $projurl $consumer_id`
    done

else

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



    command="\"${cmd}\" -c \"$conf\" $args"
    echo "Running: $command"
    eval "$command"
    res=$?

fi

if [ "x$renam" != "x" -a "$res" = "0" ]
then
    ifdh renameOutput $renam
fi

if [ "x$dest" != "x" -a "$res" = "0" ]
then
    ifdh copyBackOutput "$dest"
fi

if $update_via_fcl
then
    rm ${conf}
fi

if [ "$res" = 0 ]
then
    ifdh setStatus $cpurl $consumer_id  completed
else
    ifdh setStatus $cpurl $consumer_id  bad
fi

ifdh endProject $cpurl 

ifdh cleanup

exit $res
