
hostlist="novagpvm02 novagpvm03 novasoft@novadaq-far-datamon novasoft@novadaq-far-datamon"

cat <<'EOF'
Build bits:
-----------

mkdir /tmp/$USER$$
cd /tmp/$USER$$
mkdir p
. /online_monitor/externals/setup
. /nusoft/app/externals/setup
PRODUCTS=`pwd`/p:$PRODUCTS
setup git, upd
git clone ssh://p-ifdhc@cdcvs.fnal.gov/cvs/projects/ifdhc/ifdhc.git
git clone ssh://p-ifdh-art@cdcvs.fnal.gov/cvs/projects/ifdh-art/ifdh_art.git
export VERSION=v1_2_9
. ifdh_art/ups/build_node_setup.sh
(cd ifdhc && sh  buildifdhc.sh $buildargs)
(cd ifdhc && ups declare -z /tmp/$USER$$/p -r `pwd` -M ups -m ifdhc.table ifdhc $VERSION $DECLAREBITS)
(cd ifdh_art && sh  buildifdh_art.sh $buildargs)
mv ifdh_art/Lin*/lib/*Beam* ifdhc/Lin*/lib
mv ifdh_art/Lin*/inc/*Beam* ifdhc/inc
(cd ifdhc && make distrib )
#          
(cd ifdhc && upd addproduct -T ifdhc.tar.gz  -M ups -m ifdhc.table $DECLAREBITS ifdhc $VERSION)
(cd ifdhc && upd addproduct -T ifbeam.tar.gz  -M ups -m ifbeam.table $DECLAREBITS ifbeam $VERSION)
(cd ifdh_art && upd addproduct -r `pwd` -M ups -m ifdh_art.table $DECLAREBITS ifdh_art $VERSION)

cd 
rm -rf /tmp/$USER$$

EOF


multixterm -xc "ssh %n" $hostlist
