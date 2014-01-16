#!/bin/sh

#
# This job assumes it's being passed:
#  $SAM_PROJECT_NAME 
#  $EXPERIMENT
#  $GRID_USER

set -x

hostname
uname -a 
ls /lib*/libc-*.so

# defaults

dest=""
conf=/dev/null
exe=$EXPERIMENT
quals=nu:e4:debug
vers=v1_2_10
renam=""
limit=""
getconfig=false
use_gdb=false
exports=""
sources=""
self_destruct_timeout=""

datadir=$TMPDIR/ifdh_$$

#set -x
#
# parse options we know, collect rest in $args
#
while [ $# -gt 0 ]
do
    echo "debug: \$1 '$1' \$2 '$2'"
    case "x$1" in
    x-q|x--quals)   quals="$2"; shift; shift; continue;;
    x-c|x--config)  conf="$2";  shift; shift; continue;;
    x-D|x--dest)    dest="$2";  shift; shift; continue;;
    x-R|x--rename)  renam="$2";   shift; shift; continue;;
    x--rename2)     renam2="$2";   shift; shift; continue;;
    x--rename3)     renam3="$2";   shift; shift; continue;;
    x-X|x--exe)     cmd="$2";   shift; shift; continue;;
    x-v|x--vers)    vers="$2";  shift; shift; continue;;
    x-g|x--getconfig)getconfig=true; shift; continue;;
    x-G|x--with-gdb)use_gdb=true; shift; continue;;
    x-L|x--limit)   limit="$2"; shift; shift; continue;;
    x--addoutput)   addoutput="$2"; shift; shift; continue;;
    x--confbase)    confbase="$2"; shift; shift; continue;;
    x--export)      exports="$exports \"$2\"" shift; shift; continue;;
    x--source)      sources="$sources \"$2\"" shift; shift; continue;;
    x--self-destruct-timer) self_destruct_timeout=$2; shift; shift; continue;;
    *)              args="$args \"$1\""; shift; continue;;
    esac
    break
done

find_ups() {
    for path in /cvmfs/oasis.opensciencegrid.org/$EXPERIMENT/externals /cvmfs/oasis.opensciencegrid.org/fermilab/products/larsoft /cvmfs/novacvs.fnal.gov/externals /nusoft/app/externals
    do
       if [ -r $path/setup ] 
       then 
	    source $path/setup
	    return 0
       fi
    done
    return 1
}

check_space() {
   set : `df -P . | tail -1`
   avail_blocks=$5
   if [ $avail_blocks -lt 1024 ] 
   then
       echo "Not enough space (only ${avail_blocks}k) on this node in `pwd`."
       df -H .
       return 1
   fi
   return 0
}

kill_proc_kids_after_n() {
    watchpid=$1
    after_secs=$2
    rate=10
    sofar=0

    start=`date +%s`
    echo "Starting self-destruct timer of $after_secs at $start"

    while kill -0 $watchpid 2> /dev/null && [ $sofar -lt $after_secs ]
    do
        sleep $rate
        now=`date +%s`
        sofar=$((now - start))
        printf "."
    done
    printf "\n"
    
    if kill -0 $watchpid
    then
       pslist=`ps -ef | grep " $watchpid " | grep -v grep`
       printf "Timed out after $sofar seconds...\n"
       for signal in 15 9
       do
           echo "$pslist" | 
              while read uid pid ppid rest
              do
                 if [ $ppid = $watchpid ]
                 then
                     echo "killing -$signal $uid $pid $ppid $rest"
                     kill -$signal $pid
                 fi
              done
           echo "killing -$signal $watchpid"
           kill -$signal $watchpid
       done
    fi
}

if [ x"$self_destruct_timeout" != x ]
then
   kill_proc_kids_after_n $$ $self_destruct_timeout &
fi

#
# if we don't have ups or enough space, try again for a bit
# before giving up
#

hostname
count=0
until find_ups && check_space 
do
   count=$((count + 1))
   if [ $count -gt 6 ]
   then
       echo "Timed out waiting for space and/or cvmfs ups area"
       exit 1
   fi
   sleep 600
done

# not sure we need this
if [ "x$IFDH_BASE_URI" = "x" ]
then
    export IFDH_BASE_URI=http://samweb.fnal.gov:8480/sam/$EXPERIMENT/api
fi

#
# treat colons as blanks when eval-ing sources below
# (need a better char? what about PATH changs?) 
# because blanks get split by jobsub no matter what you do...
#
for blat in $exports
do
    echo "doing: export $blat"
    eval export $blat
done

for blat in $sources 
do
   blat=`echo $blat | sed -e 's/:/ /g'`
   eval blat=$blat
   echo "doing: source $blat"
   eval "source $blat"
done

eval "confbase=$confbase"

#
# make sure we have ifdh_art
#
if [ x$IFDH_ART_DIR = x ]
then
    . `UPS_OVERRIDE= ups setup ifdh_art $vers -q $quals:`
fi

# should not need this, but seem to for older releases -- SL5 setup on SL6 bug
PATH=/bin:/usr/bin:`echo $IFDHC_DIR/Linux*/bin`:$PATH
LD_LIBRARY_PATH=`echo $IFDHC_DIR/Linux*/lib`:`echo $IFDH_ART_DIR/Linux*/lib`:$LD_LIBRARY_PATH
setup nova_compat_libs v1_0 -q e2:debug

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$NOVA_COMPAT_LIBS_FQ_DIR

hostname=`hostname --fqdn`
projurl=`ifdh findProject $SAM_PROJECT_NAME`
consumer_id=''
count=0
while [ "$consumer_id" = "" ]
do
    sleep 5
    consumer_id=`IFDH_DEBUG= ifdh establishProcess "$projurl" "$cmd" "$ART_VERSION" "$hostname" "$GRID_USER" "art" "" "$limit"`
    count=$((count + 1))
    if [ $count -gt 10 ]
    then
        echo "Unable to establish consumer id!"
        echo "Unable to establish consumer id!" >&2 
        exit 
    fi
done

echo project url: $projurl
echo consumer id: $consumer_id

#
# override flags based on NAT IP addresses.
# this should be in ifdh_cp, but until it is...
case `hostname -i` in
10.*|192.168.*|172.1[6-9].*|172.2*|179.3[01].*) 
           export IFDH_GRIDFTP_EXTRA="-p 0 -dp"
           echo "turning on gridftp -dp flags due to NAT..."
           ;;
esac
case `hostname` in
*.wisc.edu) 
           export IFDH_GRIDFTP_EXTRA="-p 0 -dp"
           echo "turning on gridftp -dp flags due to Wisconsin firewall..."
           ;;
esac

#
#
# Joe says not to do this...
#
#cd $TMPDIR
check_space

echo "Active ups products:"
ups active

if $getconfig
then

    echo "Getconfig case:"

    uri=`IFDH_DEBUG= ifdh getNextFile $projurl $consumer_id | tail -1`
    res=0
    while [ -n "$uri" -a "$res" = 0 ]
    do
	fname=`IFDH_DEBUG= ifdh fetchInput "$uri" | tail -1 `
        if [ x$confbase != x ]
        then
             cat $confbase $fname > $fname.new
             mv $fname.new $fname
        fi
        
        echo "config is now:"
        echo "=============="
        cat $fname
        echo "=============="
        conf=$fname
        datestamp=`date +%F-%H-%M-%S`
	echo conf is $conf
	ifdh updateFileStatus $projurl  $consumer_id $fname transferred

        #out=`basename $fname | sed -e "s/.fcl$/$datestamp.root/"`
        #command="\"${cmd}\" -c \"$conf\" $args -o $out --process-name test"
        command="\"${cmd}\" -c \"$conf\" $args --process-name test"

	echo "Running: $command"

	if eval "$command"
        then 
	   ifdh updateFileStatus $projurl  $consumer_id $fname consumed
        else
	   res=$?
	   ifdh updateFileStatus $projurl  $consumer_id $fname skipped
        fi
        uri=`ifdh getNextFile $projurl $consumer_id`
    done

else
    echo "Not Getconfig case:"

    update_via_fcl=false

    : $update_via_fcl

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
	args="$args \"--sam-web-uri=$projurl\" \"--sam-process-id=$consumer_id\""
    fi

    #
    #debugging 
    #
    # ups active
    # printenv

    command="\"${cmd}\" -c \"$conf\" $args"

    if $use_gdb
    then
         printf 'run\nwhere\nquit\n'  > gdbcmds
	 command="gdb -x gdbcmds --args $command"
    fi

    echo "Running: $command"
    eval "$command"
    res=$?

    if $update_via_fcl
    then
        rm ${conf}
    fi

fi

get_last_input() {
    curl -o - "$projurl/summary?format=json" 2>/dev/null  | (
        nextone=false
        while read tag val
        do
           if [ "$tag" = '"process_id":' -a "$val" = "$consumer_id," ]
           then
               nextone=true
           fi
           if $nextone && [ "$tag" = '"last_file":' ] 
           then
               echo $val | sed -e 's/",*//g'
               break
           fi
        done
        )
}

if [ "x$addoutput" != "x" -a "$res" = "0" ]
then
    if [ -z "$IFDH_INPUT_FILE" ]
    then
        export IFDH_INPUT_FILE=`get_last_input`
    fi
    for f in $addoutput
    do
        ifdh addOutputFile $f 
    done
fi

if [ "x$renam" != "x" -a "$res" = "0" ]
then
    ifdh renameOutput $renam
fi

if [ "x$renam2" != "x" -a "$res" = "0" ]
then
    ifdh renameOutput $renam2
fi

if [ "x$renam3" != "x" -a "$res" = "0" ]
then
    ifdh renameOutput $renam3
fi

case `hostname` in
*.smu.edu) export IFDH_STAGE_VIA='srm://smuosgse.hpc.smu.edu:8443/srm/v2/server?SFN=/data/srm'
           echo "turning on staging and for SMU..."
           ;;
esac

if [ "x$dest" != "x" -a "$res" = "0" ]
then
    # workaround for srmls hangs
    export SRM_JAVA_OPTIONS=-Xmx2048m

    voms-proxy-info -all

    ifdh copyBackOutput "$dest"
fi


if [ "$res" = 0 ]
then
    ifdh setStatus $projurl $consumer_id  completed
else
    ifdh setStatus $projurl $consumer_id  bad
fi

ifdh endProcess $projurl $consumer_id

ifdh cleanup -

# cleanup temporary script dir
rm -rf $dp

# clean up usual detritus
rm -f *.fcl *.raw *.root t_* stage_*

exit $res
