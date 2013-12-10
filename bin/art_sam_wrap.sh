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
    x-R|x--rename)     renam="$2";   shift; shift; continue;;
    x-X|x--exe)     cmd="$2";   shift; shift; continue;;
    x-v|x--vers)    vers="$2";  shift; shift; continue;;
    x-g|x--getconfig)getconfig=true; shift; continue;;
    x-G|x--with-gdb)use_gdb=true; shift; continue;;
    x-R|x--rename)  renam="$2"; shift; shift; continue;;
    x-L|x--limit)   limit="$2"; shift; shift; continue;;
    x--addoutput)   addoutput="$2"; shift; shift; continue;;
    x--confbase)    confbase="$2"; shift; shift; continue;;
    x--export)      exports="$exports \"$2\"" shift; shift; continue;;
    x--source)      sources="$sources \"$2\"" shift; shift; continue;;
    *)              args="$args \"$1\""; shift; continue;;
    esac
    break
done

find_ups() {
    for path in /cvmfs/oasis.opensciencegrid.org/$EXPERIMENT/externals /cvmfs/novacvs.fnal.gov/externals /nusoft/app/externals
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
       reurn 1
   fi
   return 0
}

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
# Joe says not to do this...
#
#cd $TMPDIR
check_space

#
# setup latest debug ifdh_copyback script
#
do_copyback() {

    dp=${TMPDIR:-/tmp}/tmpbin$$
    mkdir -p $dp
    cat > $dp/ifdh_copyback.sh << 'EOF'
#!/bin/sh

#set -x

srmcopycmd() {
  lcg-cp  --sendreceive-timeout 4000 -b -D srmv2 "$@"
}

#
# IFDH_STAGE_VIA is allowed to be a literal '$OSG_SITE_WRITE'
# (or generally $E for some environment variable E)
# so we eval it to expand that
#

run_with_timeout() {
    timeout=$1
    poll=5
    shift
    "$@" &
    cpid=$!
    while kill -0 $cpid 2>/dev/null&& [ $timeout -gt 0 ]
    do
        sleep $poll
        timeout=$((timeout - poll))
    done
    if kill -0 $cpid 2>/dev/null
    then
         echo "killing: $1 due to timeout"
         kill -9 $cpid
    fi
    wait $cpid
}

init() {

    echo "Copyback v2013-09-24-lcg starting"
    for cmd in "ifdh --help" "lcg-cp -help" "srmls -help"
    do
	if [ `$cmd 2>&1 | wc -l` -gt 2 ]
	then
	    : 
	else
	    echo "Cannot get output of $cmd; bailing out..."
	    exit 1
	fi
    done
    
 
    printf "ifdh copyback script starting for experiment %s\n" "${EXPERIMENT:-nova}"

    IFDH_STAGE_VIA="${IFDH_STAGE_VIA:-$OSG_SITE_WRITE}"
    eval IFDH_STAGE_VIA=\""${IFDH_STAGE_VIA}"\"

    host=`hostname --fqdn`
    filelist=${TMPDIR:-/tmp}/filelist$$
    wprefix="${IFDH_STAGE_VIA}/${EXPERIMENT:-nova}/ifdh_stage"

    #
    # paths with double slashes confuse srmls...
    #
    while :
    do
      case "$wprefix" in
      *//*//*)  wprefix=`echo "$wprefix" | sed -e 's;\(//.*/\)/;\1;'`;;
      *)  break;;
      esac
    done

    ifdh log "ifdh_copyback.sh: starting for ${EXPERIMENT} on $host location $wprefix"
    # avoid falling into a hall of mirrors
    unset IFDH_STAGE_VIA

    cd ${TMPDIR:-/tmp}
}


get_first() {
   #debugging
   printf "Lock dir listing output:\n" >&2
   srmls -2 "$wprefix/lock" >&2
   printf "::\n" >&2

   srmls -2 "$wprefix/lock" | sed -e '1d' -e '/^$/d' | sort | head -1
}

i_am_first() {
   lockfile=`get_first` 
   echo "comparing $lockfile to $uniqfile" 
   case "$lockfile" in
   *$uniqfile) return 0;;
   *)            return 1;;
   esac
}

expired_lock() {
   set : `get_first`
   first_file="$3"
   if [ "x$first_file" != "x" ] && [ "`basename $first_file`" != "lock" ]
   then
       printf "Checking lock file: $first_file ... "
       # example timestamp:  t_2013-09-24_12_21_22_red-d21n13.red.hcc.unl.edu_30277
       first_time=`echo $first_file | sed -e 's;.*/t_\([0-9]*\).\([0-9]*\).\([0-9]*\).\([0-9]*\).\([0-9]*\).\([0-9]*\).*;\1-\2-\3 \4:\5:\6;'`
       first_secs=`date --date="$first_time" '+%s'`
       cur_secs=`date '+%s'`


       delta=$((cur_secs - first_secs))

       printf "lock is $delta seconds old: "

       # if the lock is over 4 hours old, we consider it dead

       if [ $delta -gt 14400 ]
       then
	   lock_name=`basename $first_file`
	   printf "Breaking expired lock.\n"
           ifdh log "ifdh_copyback.sh: Breaking expired lock $lock_name\n"
	   srmrm $wprefix/lock/$lock_name
       else
           printf "Still valid.\n"
       fi
   fi
}

get_lock() {

   expired_lock

   datestamp=`date +%FT%T | sed -e 's/[^a-z0-9]/_/g'`
   uniqfile="t_${datestamp}_${host}_$$"

   if [ "x$datestamp" = x  -o "x$host" = x ]
   then
      # lock algorithm is busted.. bail
      return 1
   fi

   echo lock > ${TMPDIR:-/tmp}/$uniqfile
   run_with_timeout 300 srmcopycmd file:///${TMPDIR:-/tmp}/$uniqfile $wprefix/lock/$uniqfile
   if i_am_first
   then
      sleep 5
      if i_am_first
      then
         echo "Obtained lock $uniqfile at `date`"
         ifdh log "ifdh_copyback.sh: Obtained lock $uniqfile at `date`"
         return 0  
      fi
   fi

   printf "Lock $lockfile already exists, someone else is already copying files.\n"
   srmrm $wprefix/lock/$uniqfile
   return 1
}

clean_lock() {
   printf "Removing my lock: $wprefix/lock/$uniqfile\n"
   srmrm $wprefix/lock/$uniqfile > /dev/null 2>&1
}

have_queue() {
   count=`srmls -2  $wprefix/queue | wc -l`
   [ $count -gt 2 ]
}

copy_files() {
   srmls -2 $wprefix/queue | (
     read dirname
     while read size filename
     do

         [ x$filename = x ] && continue

         rm -f ${filelist}
         filename=`basename $filename`

         printf "Fetching queue entry: $filename\n"
         run_with_timeout 300 srmcopycmd  $wprefix/queue/$filename file:///${filelist}

         #printf "queue entry contents:\n-------------\n"
         #cat ${filelist}
         #printf "\n-------------\n"

         printf "starting copy..."
         ifdh log "ifdh_copyback.sh: starting copies for $filename"

         #
         # switching to lcg-cp for now; not sure how it does on assorted third party copy options...
         #
         
         while read src dest
         do              
  	     # fixup plain fermi destinations
             case "$dest" in
             srm:*) ;;
             /*)  dest="srm://fg-bestman1.fnal.gov:10443/srm/v2/server?SFN=$dest"
;;
             esac

             cmd="srmcopycmd \"$src\" \"$dest\""
             echo "ifdh_copyback.sh: $cmd"
             ifdh log "ifdh_copyback.sh: $cmd"
             run_with_timeout 3600 eval "$cmd"
             echo "status; $?"
         done < $filelist

         printf "completed.\n"
         ifdh log "ifdh_copyback.sh: finished copies for $filename"

         printf "Cleaning up for $filename:\n"
         while read src dest
         do
             printf "removing: $src\n"
             ifdh log "ifdh_copyback.sh: cleaned up $src"

             srmrm $src
             srcdir=`dirname $src`
         done < ${filelist}

         printf "removing: $srcdir\n"
         srmrmdir $srcdir

         printf "removing: $wprefix/queue/$filename\n"
         srmrm    $wprefix/queue/$filename
         ifdh log "ifdh_copyback.sh: cleaned up $filename"

         rm $filelist

     done
  )
}

debug_ls() {
   echo "current stage area:"
   srmls -2 --recursion_depth=4 $wprefix
   echo
}

copy_daemon() {
   init

   debug_ls

   trap "clean_lock" 0 1 2 3 4 5 6 7 8 10 12

   while get_lock && have_queue
   do
       copy_files
       clean_lock
   done

   clean_lock
   
   printf "Finished on $host at `date`\n"

   ifdh log "ifdh_copyback.sh: finished on $host"

   trap "" 0 1 2 3 4 5 6 7 8 10 12
}

copy_daemon
EOF

    chmod +x $dp/*
    PATH=$dp:$PATH

    printf "copyback is: "
    which ifdh_copyback.sh
}

do_copyback

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

if [ "x$addoutput" != "x" -a "$res" = "0" ]
then
    for f in $addoutput
    do
        ifdh addOutputFile $f 
    done
fi

if [ "x$renam" != "x" -a "$res" = "0" ]
then
    ifdh renameOutput $renam
fi

if [ "x$dest" != "x" -a "$res" = "0" ]
then
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
