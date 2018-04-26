package it.millgates.mw;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
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
	private final static String CPP_PATH = "../MillGatesAgent/Release/MillGatesAgent.exe";
	// TODO MODIFICARE PORTA TCP
	private final static int PORT = 25568;

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

	
	private static String currentStateStringLong(State currentState) {

		StringBuilder sb = new StringBuilder();
		for(String position : currentState.positions) {
			sb.append(position);
			Checker c = currentState.getBoard().get(position);
			switch(c) {
			case EMPTY: sb.append('O'); break;
			case WHITE: sb.append('W'); break;
			case BLACK: sb.append('B'); break;
			}
		}
		sb.append(currentState.getWhiteCheckers());
		//sb.append(" ");
		sb.append(currentState.getBlackCheckers());
		//sb.append(" ");

		Phase p = currentState.getCurrentPhase();
		switch(p) {
		case FIRST: sb.append(1); break;
		case SECOND: sb.append(2); break;
		case FINAL: sb.append(3); break;
		}

		return sb.toString();
	} 

	
	public static void main(String[] args) {

		// Start C++ Agent

		Runtime rt = null;
		Process pr = null;

		if (args.length == 1 || !args[1].equals("--debug")) { 
			try {
				rt = Runtime.getRuntime();
				pr = rt.exec(CPP_PATH +" "+ args[0]);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		// Connect to C++ Agent

		ServerSocket serverSocket = null;
		Socket socket = null;
		DataInputStream agentOutput = null;
		DataOutputStream agentInput = null;
		byte[] buffer = new byte[27];

		try {
			serverSocket = new ServerSocket(PORT);
		} catch (IOException e) {
			e.printStackTrace();
		}

		System.out.println("Waiting for C++ Agent connection");

		try {
			socket = serverSocket.accept();

			System.out.println("C++ Agent connected");

			agentOutput = new DataInputStream(socket.getInputStream());
			agentInput = new DataOutputStream(socket.getOutputStream());

			State.Checker player;
			if ("White".equalsIgnoreCase(args[0]))
				player = State.Checker.WHITE;
			else
				player = State.Checker.BLACK;

			System.out.println("Connecting to server");

			MulinoClient client = new MGCppAgent(player);

			System.out.println("Connected to server");
			String actionString = "";
			String stateString = "";
			Action action;
			State currentState = null;

			if (player == State.Checker.WHITE) {

				currentState = client.read();

				while (true) {
					
					// read move from cpp agent
					agentOutput.read(buffer, 0, 7);
					actionString = new String(buffer, "UTF-8");
					
					action = stringToAction(actionString.trim(), currentState.getCurrentPhase());
					// write move to server
					client.write(action);
					// read result of our move from server
					currentState = client.read();
					// waiting for opponent move 
					currentState = client.read();
					// write current state string to cpp agent
					stateString = currentStateStringLong(currentState);
					agentInput.write(stateString.getBytes("UTF-8"), 0, stateString.length());
				}
			} else {

				currentState = client.read();

				while (true) {
					// waiting opponent move
					currentState = client.read();
					// write current state string to cpp agent
					stateString = currentStateStringLong(currentState);
					agentInput.write(stateString.getBytes("UTF-8"), 0, stateString.length());
					// read move from cpp agent
					agentOutput.read(buffer, 0, 7);
					actionString = new String(buffer, "UTF-8");
					
					action = stringToAction(actionString.trim(), currentState.getCurrentPhase());
					// write move to server
					client.write(action);
					// read result of our move from server
					currentState = client.read();
				}
			}

		}
		catch (IOException | ClassNotFoundException e) {
			e.printStackTrace();
		}
		finally {
			try {

				System.out.println("Closing sockets");

				socket.close();
				serverSocket.close();
				pr.destroy();
				
			}
			catch (Exception e) {
				e.printStackTrace();
			}
		}

	}


}
