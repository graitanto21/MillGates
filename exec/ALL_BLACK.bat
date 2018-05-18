START /B server.bat 1> server_log.txt 2>&1
ping -n 1 127.0.0.1 1> nul 
START /B human_white_client.bat 
ping -n 2 127.0.0.1 1> nul 
START /B java -jar middleware.jar black --debug > middleware_log.txt 2>&1
ping -n 1 127.0.0.1 1> nul
START /B agent.bat black > agent_log.txt 2>&1