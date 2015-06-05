package ar.edu.itba.cys.ssi.execution;

import java.awt.Image;

public class Distribute implements ExecutionMode {

	private final int k;
	private final int n;
	private final String image; // TODO change this when we know what we actually need
	
	public Distribute(final int k, final int n, final String image) {
		this.k = k;
		this.n = n;
		this.image = image;
	}
	
	
	@Override
	public void execute() {
		
		
	}
	
	public void validateParameters() throws IllegalArgumentException {
		String msg = null;
		if (k < 2) {
			msg = "k must be greater or equal than 2";
		} else if (k > n) {
			msg = "k must be lower or equal than n";
		} else if (n < 2) {
			msg = "n must be at least 2";
		} 
		// TODO validate Image formatt
		if (msg != null) {
			throw new IllegalArgumentException(msg);
		}
	}
	
}
