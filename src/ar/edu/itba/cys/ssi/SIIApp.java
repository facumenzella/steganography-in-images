package ar.edu.itba.cys.ssi;

import ar.edu.itba.cys.ssi.execution.ExecutionMode;
import ar.edu.itba.cys.ssi.execution.distribute.Distribute;
import ar.edu.itba.cys.ssi.execution.distribute.Distribute.DistributionParameters;
import ar.edu.itba.cys.ssi.parser.SSICmdParser;
import ar.edu.itba.cys.ssi.parser.SSICmdParser.SSICmdExecutionParameters;


// Steganography in images App
public class SIIApp {
	
	public static void main(String args[]) {
		SSICmdParser parser = new SSICmdParser();
		
		SSICmdExecutionParameters parameters = parser.parse(args);
		ExecutionMode mode;
		switch (parameters.getMode()) {
		case RECOVER:
			// We are recovering an image
			// TODO add Recover
			break;
		case DISTRIBUTE:
			// We are distributing an image
			DistributionParameters p = new DistributionParameters(parameters);
			mode = new Distribute(p);
			mode.execute();
			break;
		default:
			System.out.println("Holy shit the impossible hapenned");
			break;
		}
	}

}
