package it.millgates.mw;

import it.unibo.ai.didattica.mulino.domain.State;
import it.unibo.ai.didattica.mulino.domain.State.Checker;
import it.unibo.ai.didattica.mulino.domain.State.Phase;

public class OWBStateEncoder implements StateEncoder{

	@Override
	public String encode(State state) {

		StringBuilder sb = new StringBuilder();
		for(String position : state.positions) {
			Checker c = state.getBoard().get(position);
			switch(c) {
			case EMPTY: sb.append('O'); break;
			case WHITE: sb.append('W'); break;
			case BLACK: sb.append('B'); break;
			}
		}
		sb.append(state.getWhiteCheckersOnBoard());
		sb.append(" ");
		sb.append(state.getBlackCheckersOnBoard());
		sb.append(" ");

		sb.append(state.getWhiteCheckers());
		sb.append(" ");
		sb.append(state.getBlackCheckers());
		sb.append(" ");
		
		Phase p = state.getCurrentPhase();
		switch(p) {
		case FIRST: sb.append(0); break;
		case SECOND: sb.append(1); break;
		case FINAL: sb.append(2); break;
		}

		return sb.toString();
	} 

}
