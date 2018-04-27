package it.millgates.mw;

import it.unibo.ai.didattica.mulino.actions.Action;
import it.unibo.ai.didattica.mulino.domain.State.Phase;

public interface ActionFactory {

	public Action stringToAction(String actionString, Phase phase);
	
	public int maxStringLength();
	
}
