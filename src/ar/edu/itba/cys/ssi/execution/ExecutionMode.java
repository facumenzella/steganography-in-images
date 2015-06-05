package ar.edu.itba.cys.ssi.execution;

public interface ExecutionMode {
	
	public void execute();
	public void validateParameters() throws IllegalArgumentException;
	
}
