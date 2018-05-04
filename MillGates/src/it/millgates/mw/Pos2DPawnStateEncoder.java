package it.millgates.mw;

import it.unibo.ai.didattica.mulino.domain.State;
import it.unibo.ai.didattica.mulino.domain.State.Checker;
import it.unibo.ai.didattica.mulino.domain.State.Phase;

public class Pos2DPawnStateEncoder implements StateEncoder{

	@Override
	public String encode(State state) {

		StringBuilder sb = new StringBuilder();
		for(String position : state.positions) {
			sb.append(position);
			Checker c = state.getBoard().get(position);
			switch(c) {
			case EMPTY: sb.append('O'); break;
			case WHITE: sb.append('W'); break;
			case BLACK: sb.append('B'); break;
			}
		}
		if(state.getWhiteCheckersOnBoard() < 10 ) sb.append(" ");
		sb.append(state.getWhiteCheckersOnBoard());
		if(state.getBlackCheckersOnBoard() < 10 ) sb.append(" ");
		sb.append(state.getBlackCheckersOnBoard());

		Phase p = state.getCurrentPhase();
		switch(p) {
		case FIRST: sb.append(1); break;
		case SECOND: sb.append(2); break;
		case FINAL: sb.append(3); break;
		}

		return sb.toString();
	} 
	
}
