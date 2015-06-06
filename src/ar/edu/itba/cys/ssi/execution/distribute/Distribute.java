package ar.edu.itba.cys.ssi.execution.distribute;

import java.io.File;
import java.util.Random;

import ar.edu.itba.cys.ssi.execution.BitMapParser;
import ar.edu.itba.cys.ssi.execution.BitMapParser.BMPImageInformation;
import ar.edu.itba.cys.ssi.execution.ExecutionMode;
import ar.edu.itba.cys.ssi.parser.SSICmdParser.SSICmdExecutionParameters;

public class Distribute implements ExecutionMode {

	private final static long SEED = 10;
	private final static Random generator = new Random(SEED); // I am sure this is wrong.
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
		permutatePixels(n, bmpInfo.getImage());
		
	}
	
	private void permutatePixels(final int n, final byte[] image) {
		for (int i = n - 1; i >= 1; i--) {
			int j = generator.nextInt(i+1); // if not its exclusive and we need  0 <= j <= i
			byte pivot = image[i];
			image[i] = image[j];
			image[j] = pivot;
		}
	}
	
	public static class DistributionParameters {
		
		private final int k;
		private final String secretImage;
		private final int numberOfShadows;
		
		public DistributionParameters(final SSICmdExecutionParameters parameters) {
			this.k = parameters.getK();
			this.secretImage = parameters.getImage();
			int n = parameters.getN();
			if (n == -1) {
				// TODO set path to folder
				this.numberOfShadows = new File("/path/to/folder").listFiles().length;
			} else {
				this.numberOfShadows = n;
			}
			validate();
		}
		
		public void validate() throws IllegalArgumentException {
			String msg = null;
			if (k < 2) {
				msg = "k must be greater or equal than 2";
			} else if (k > numberOfShadows) {
				msg = "k must be lower or equal than n";
			} else if (numberOfShadows < 2) {
				// TODO if n is not provided we need to set it 
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
