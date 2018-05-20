START /B server.bat 1> server_log.txt 2>&1
ping -n 1 127.0.0.1 1> nul 
START /B human_white_client.bat 
ping -n 2 127.0.0.1 1> nul 
START /B java -jar middleware.jar black %1 > middleware_log.txt 2>&1
ping -n 1 127.0.0.1 1> nul
START /B agent.bat black %1 > agent_log.txt 2>&1