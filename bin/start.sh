#!/bin/bash 
if [ $# = 2 ]
then
	java -jar middleware.jar "$1" "$2" & > middleware_log.txt
	sleep 1
	./MillGatesAgent_AlphaBeta.exe "$1" "$2" & > agent_log.txt
else
	java -jar middleware.jar "$1" & > middleware_log.txt
        sleep 1
        ./MillGatesAgent_AlphaBeta.exe "$1" & > agent_log.txt
fi
