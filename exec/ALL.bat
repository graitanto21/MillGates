START /B server.bat > server_log.txt
ping -n 1 127.0.0.1 > nul
START /B java -jar middleware.jar white --debug > middleware_log.txt
ping -n 1 127.0.0.1 > nul
START /B agent.bat > agent_log.txt
ping -n 1 127.0.0.1 > nul
human_black_client.bat