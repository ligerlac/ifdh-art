
hostlist="novagpvm02 novagpvm03"

cat <<'EOF'
Build bits:
-----------

mkdir /tmp/$USER$$
cd /tmp/$USER$$
setup git

git clone ssh://p-ifdhc@cdcvs.fnal.gov/cvs/projects/ifdhc/ifdhc.git
git clone ssh://p-ifdh-art@cdcvs.fnal.gov/cvs/projects/ifdh-art/ifdh-art.git

. ifdh-art/ups/build_node_setup.sh

(cd ifdhc &&  buildifdhc.sh $buildargs)
(cd ifdh-art &&  buildifdh_art.sh $buildargs)

(cd ifdhc && upd addproduct -r `pwd` -M ups -m ifdhc.table $DECLAREBITS ifdhc $VERSION)
(cd ifdh-art && upd addproduct -r `pwd` -M ups -m ifdhc.table $DECLAREBITS ifdhc $VERSION)

rm -rf /tmp/$USER$$

EOF


multixterm -xc "ssh %n" $hostlist

