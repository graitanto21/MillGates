package it.millgates.mw;
import java.io.IOException;
import java.net.UnknownHostException;

import it.unibo.ai.didattica.mulino.client.MulinoClient;
import it.unibo.ai.didattica.mulino.domain.State.Checker;

public class MGCppAgent extends MulinoClient {

	public MGCppAgent(Checker player) throws UnknownHostException, IOException {
		super(player);
	}
	
	

}
