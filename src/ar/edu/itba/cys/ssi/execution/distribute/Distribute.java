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
	private final String image_name;
	private static final byte MAX_BYTE_VALUE = (byte) 251;
	
	public Distribute(final DistributionParameters parameters) {
		this.k = parameters.getK();
		this.n = parameters.getNumberOfShadows();
		this.image_name = parameters.getSecretImage();
	}
	
	@Override
	public void execute() {
		BitMapParser bmpParser = new BitMapParser();
		BMPImageInformation bmpInfo = bmpParser.parseImage(this.image_name);
		byte[] image = bmpInfo.getImage();
		permutatePixels(n, image);
		byte[][] shadows = createLosslessShadows(image, n, k);
		for (int i = 0; i < shadows.length; i++) {
			for (int j = 0; j < shadows[i].length; j++) {
				System.out.println(shadows[i][j]);
			}
		}
	}
	
	private void permutatePixels(final int n, final byte[] image) {
		for (int i = n - 1; i >= 1; i--) {
			int j = generator.nextInt(i+1); // if not its exclusive and we need  0 <= j <= i
			byte pivot = image[i];
			image[i] = image[j];
			image[j] = pivot;
		}
	}
	
	private byte[][] createLosslessShadows(byte[] image, int n, int k) {
		byte[][] shadows = new byte[n][image.length/k * 2];
		byte[] section = new byte[k];
		int shadow_pixel_index = 0;
		for (int i = 0; i < image.length; i++) {
			if (i % k == 0) {
				evaluateSection(section, shadows, shadow_pixel_index);
				shadow_pixel_index++;
				section = new byte[k];
			}
			section[i % k] = image[i];
		}
		return shadows;
	}
	
	private void evaluateSection(byte[] section, byte[][] shadows, int shadow_pixel_index) {
		for (int i = 1; i <= shadows.length; i++) {
			byte ans = 0;
			for (int j = 0; j < section.length; j++) {
				ans += section[j]*bytePow(i, j);
			}
			shadows[i-1][shadow_pixel_index] = (byte)(ans % MAX_BYTE_VALUE);
		}
	}
	
	private byte bytePow(int base, int exponent) {
		byte ans = 1;
		for (int i = 0; i < exponent; i++) {
			ans *= base;
		}
		return ans;
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
