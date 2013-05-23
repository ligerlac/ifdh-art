
hostlist="novagpvm02 novagpvm03"

cat <<'EOF'
Build bits:
-----------

mkdir /tmp/$USER$$
cd /tmp/$USER$$

PRODUCTS=/nusoft/app/externals:$PRODUCTS
setup git, upd

git clone ssh://p-ifdhc@cdcvs.fnal.gov/cvs/projects/ifdhc/ifdhc.git
git clone ssh://p-ifdh-art@cdcvs.fnal.gov/cvs/projects/ifdh-art/ifdh_art.git

. ifdh_art/ups/build_node_setup.sh

(cd ifdhc && sh  buildifdhc.sh $buildargs)
cd ifdhc ; setup -. ifdhc $DECLAREBITS ; cd ..
(cd ifdh_art && sh  buildifdh_art.sh $buildargs)

export VERSION=v1_2_0
(cd ifdhc && upd addproduct -r `pwd` -M ups -m ifdhc.table $DECLAREBITS ifdhc $VERSION)
(cd ifdh_art && upd addproduct -r `pwd` -M ups -m ifdh_art.table $DECLAREBITS ifdh_art $VERSION)

cd 
rm -rf /tmp/$USER$$

EOF


multixterm -xc "ssh %n" $hostlist

