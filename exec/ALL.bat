START /B server.bat 1> server_log.txt 2>&1
ping -n 1 127.0.0.1 1> nul 2>&1
START /B java -jar middleware.jar white --debug > middleware_log.txt 2>&1
ping -n 1 127.0.0.1 1> nul 2>&1
START /B agent.bat > agent_log.txt 2>&1
ping -n 1 127.0.0.1 1> nul 2>&1
human_black_client.bat 