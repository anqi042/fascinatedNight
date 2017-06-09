commad=`ps axf | grep server | grep -v grep | awk '{print "kill -9 " $1}'`
$commad
