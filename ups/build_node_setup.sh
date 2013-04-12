
case `hostname` in
minervagpvm02*) export buildargs="debug e2"
                export DECLAREBITS="-q debug:e2 -4"
                ;;
minervagpvm03*) export buildargs="prof e2"
                export DECLAREBITS="-q e2:prof -4"
                 ;;
esac
