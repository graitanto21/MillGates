Per l'avvio dell'agent utilizzare lo script bin/start.sh

Utilizzo: 
./start.sh <white|black> [PORT]

Millgates è composto da un agent c++ che comunica al server di gioco utilizzando come intermediario middleware.jar
L'argomento PORT è opzionale e stabilisce la porta su cui middleware e agent c++ devono comunicare. 
Di default viene utilizzata la porta 25568, ma nel caso in cui altre applicazioni utilizzino già tale porta è possibile
utilizzarne una diversa.