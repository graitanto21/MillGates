START /B server.bat > server_log.txt
START /B java -jar middleware.jar white --debug > middleware_log.txt
START /B agent.bat > agent_log.txt
human_black_client.bat