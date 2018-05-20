#!/bin/bash
java -jar middleware.jar $1 $2 & > middleware_log.txt
sleep 1
./MillGatesAgent.exe $1 $2 & > agent_log.txt
