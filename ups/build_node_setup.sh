
case `hostname`$BUILD_EXTRA in
novagpvm02*) export buildargs="debug e4"
                export DECLAREBITS="-q debug:e4 -4"
                ;;
novagpvm03*) export buildargs="prof e4"
                export DECLAREBITS="-q e4:prof -4"
                 ;;
novagdaq-far-datamon*) export buildargs="debug e4"
                export DECLAREBITS="-q debug:e4 -4"
		. /online_monitor/externals/setup
                ;;
novagdaq-far-datamon*prof*) export buildargs="prof e4"
                export DECLAREBITS="-q e4:prof -4"
		. /online_monitor/externals/setup
                ;;
esac
