#!/bin/bash
java -jar middleware.jar $1 & > middleware_log.txt
sleep 1
./MillGatesAgent.exe $1 & > agent_log.txt
