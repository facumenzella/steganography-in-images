package ar.edu.itba.cys.ssi.execution.distribute;

import ar.edu.itba.cys.ssi.execution.BitMapParser;
import ar.edu.itba.cys.ssi.execution.BitMapParser.BMPImageInformation;
import ar.edu.itba.cys.ssi.execution.ExecutionMode;
import ar.edu.itba.cys.ssi.parser.SSICmdParser.SSICmdExecutionParameters;

public class Distribute implements ExecutionMode {

	private final int k;
	private final int n;
	private final String image;
	
	public Distribute(final DistributionParameters parameters) {
		this.k = parameters.getK();
		this.n = parameters.getNumberOfShadows();
		this.image = parameters.getSecretImage();
	}
	
	@Override
	public void execute() {
		BitMapParser bmpParser = new BitMapParser();
		BMPImageInformation bmpInfo = bmpParser.parseImage(this.image);
	}
	
	public static class DistributionParameters {
		
		private final int k;
		private final String secretImage;
		private final int numberOfShadows;
		
		public DistributionParameters(final SSICmdExecutionParameters parameters) {
			this.k = parameters.getK();
			this.secretImage = parameters.getImage();
			this.numberOfShadows = parameters.getN();
			validate();
		}
		
		public void validate() throws IllegalArgumentException {
			String msg = null;
			if (k < 2) {
				msg = "k must be greater or equal than 2";
			} else if (k > numberOfShadows) {
				msg = "k must be lower or equal than n";
			} else if (numberOfShadows < 2) {
				msg = "n must be at least 2";
			} 
			// TODO validate Image formatt
			if (msg != null) {
				throw new IllegalArgumentException(msg);
			}
		}
		

		public int getK() {
			return k;
		}

		public String getSecretImage() {
			return secretImage;
		}

		public int getNumberOfShadows() {
			return numberOfShadows;
		}
		
		
	}

}
