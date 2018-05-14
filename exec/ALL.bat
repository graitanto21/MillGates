START /B server.bat > server_log.txt
Sleep 500
START /B java -jar middleware.jar white --debug > middleware_log.txt
Sleep 500
START /B agent.bat > agent_log.txt
Sleep 500
human_black_client.bat