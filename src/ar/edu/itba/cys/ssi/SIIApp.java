package ar.edu.itba.cys.ssi;

import ar.edu.itba.cys.ssi.parser.SSICmdParser;
import ar.edu.itba.cys.ssi.parser.SSICmdParser.SSICmdExecutionParameters;


// Steganography in images App
public class SIIApp {
	
	public static void main(String args[]) {
		SSICmdParser parser = new SSICmdParser();
		
		SSICmdExecutionParameters parameters = parser.parse(args);
		
		switch (parameters.getMode()) {
		case RECOVER:
			// We are recovering an image
			break;
		case DISTRIBUTE:
			// We are distributing an image
			break;
		default:
			System.out.println("Holy shit the impossible hapenned");
			break;
		}
	}

}
