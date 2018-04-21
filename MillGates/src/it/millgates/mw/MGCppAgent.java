package it.millgates.mw;
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;

import it.unibo.ai.didattica.mulino.actions.Action;
import it.unibo.ai.didattica.mulino.actions.Phase1Action;
import it.unibo.ai.didattica.mulino.actions.Phase2Action;
import it.unibo.ai.didattica.mulino.actions.PhaseFinalAction;
import it.unibo.ai.didattica.mulino.client.MulinoClient;
import it.unibo.ai.didattica.mulino.domain.State;
import it.unibo.ai.didattica.mulino.domain.State.Checker;
import it.unibo.ai.didattica.mulino.domain.State.Phase;

public class MGCppAgent extends MulinoClient {

	public MGCppAgent(Checker player) throws UnknownHostException, IOException {
		super(player);
	}
	
	// TODO AGGIUNGERE PATH FILE CPP 
	private final static String CPP_PATH = "";
	// TODO MODIFICARE PORTA TCP
	private final static int PORT = 5850;
	
	/**
	 * Converte una stringa testuale in un oggetto azione
	 * 
	 * @param actionString
	 *            La stringa testuale che esprime l'azione desiderata
	 * @param fase
	 *            La fase di gioco attuale
	 * @return L'oggetto azione da comunicare al server
	 */
	private static Action stringToAction(String actionString, Phase fase) {
		if (fase == Phase.FIRST) { // prima fase
			Phase1Action action;
			action = new Phase1Action();
			action.setPutPosition(actionString.substring(0, 2));
			if (actionString.length() == 4)
				action.setRemoveOpponentChecker(actionString.substring(2, 4));
			else
				action.setRemoveOpponentChecker(null);
			return action;
		} else if (fase == Phase.SECOND) { // seconda fase
			Phase2Action action;
			action = new Phase2Action();
			action.setFrom(actionString.substring(0, 2));
			action.setTo(actionString.substring(2, 4));
			if (actionString.length() == 6)
				action.setRemoveOpponentChecker(actionString.substring(4, 6));
			else
				action.setRemoveOpponentChecker(null);
			return action;
		} else { // ultima fase
			PhaseFinalAction action;
			action = new PhaseFinalAction();
			action.setFrom(actionString.substring(0, 2));
			action.setTo(actionString.substring(2, 4));
			if (actionString.length() == 6)
				action.setRemoveOpponentChecker(actionString.substring(4, 6));
			else
				action.setRemoveOpponentChecker(null);
			return action;
		}
	}
	
	private static String currentStateString(State currentState) {
		
		StringBuilder sb = new StringBuilder();
		for(String position : currentState.positions) {
			Checker c = currentState.getBoard().get(position); 
			switch(c) {
			case EMPTY: sb.append('O'); break;
			case WHITE: sb.append('W'); break;
			case BLACK: sb.append('B'); break;
			}
		}
		sb.append(currentState.getWhiteCheckers());
		sb.append(" ");
		sb.append(currentState.getBlackCheckers());
		sb.append(" ");
		
		Phase p = currentState.getCurrentPhase();
		switch(p) {
		case FIRST: sb.append(0); break;
		case SECOND: sb.append(1); break;
		case FINAL: sb.append(2); break;
		}
		
		return sb.toString();
	} 
	
	public static void main(String[] args) throws UnknownHostException, IOException, ClassNotFoundException {
		
		// Start cpp agent
		Process process = new ProcessBuilder(CPP_PATH).start();
		ServerSocket serverSocket = new ServerSocket(PORT);
		Socket socket = serverSocket.accept();
		BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
		DataOutputStream dos = new DataOutputStream(socket.getOutputStream());
		
		
		State.Checker player;
		if ("White".equals(args[0]))
			player = State.Checker.WHITE;
		else
			player = State.Checker.BLACK;
		
		MulinoClient client = new MGCppAgent(player);
		String actionString = "";
		Action action;
		State currentState = null;

		if (player == State.Checker.WHITE) {
			System.out.println("You are player " + client.getPlayer().toString() + "!");
			System.out.println("Current state:");
			currentState = client.read();
			System.out.println(currentState.toString());
			
			while (true) {
				// read move from cpp agent
				actionString = br.readLine();
				action = stringToAction(actionString, currentState.getCurrentPhase());
				// write move to server
				client.write(action);
				// read result of our move from server
				currentState = client.read();
				// waiting for opponent move 
				currentState = client.read();
				// write current state string to cpp agent
				dos.writeUTF(currentStateString(currentState));
			}
		} else {
			currentState = client.read();
			while (true) {
				// waiting opponent move
				currentState = client.read();
				// write current state string to cpp agent
				dos.writeUTF(currentStateString(currentState));
				// read move from cpp agent
				actionString = br.readLine();
				action = stringToAction(actionString, currentState.getCurrentPhase());
				// write move to server
				client.write(action);
				// read result of our move from server
				currentState = client.read();
			}
		}

		
	
	}
	

}
