package ar.edu.itba.cys.ssi.execution;

public interface ExecutionMode {
	
	public void execute();
	public void validateParameters() throws IllegalArgumentException;

	
	public interface ExecutionParameters {
		// Just to make it more generic, but we will cast it where we need it	
	}
}
