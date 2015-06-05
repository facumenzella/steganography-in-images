package ar.edu.itba.cys.ssi.parser;

import org.apache.commons.cli.BasicParser;
import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.HelpFormatter;
import org.apache.commons.cli.Option;
import org.apache.commons.cli.OptionBuilder;
import org.apache.commons.cli.OptionGroup;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.ParseException;

public final class SSICmdParser {

	private final CommandLineParser parser;
	private final Options options;

	public SSICmdParser() {
		this.parser = new BasicParser();
		this.options = new Options();
	}

	public SSICmdExecutionParameters parse(final String[] cmdLine) {
		setOptions();
		// Parse command line parameters
		String image = null, k = null, dir = null, n = null;
		SSIExecutionMode mode = SSIExecutionMode.RECOVER;
		try {
			final CommandLine cmd = parser.parse(options, cmdLine);
			if (cmd.hasOption('h')) {
				printHelp(options);
			}
			image = parseSecret(cmd);
			k = parseK(cmd);
			dir = parseDir(cmd);
			n = parseN(cmd);
			if (cmd.hasOption('d')) {
				// We are going to distribute an image
				mode = SSIExecutionMode.DISTRIBUTE;
			} else if (cmd.hasOption('r')) {
				// We are going to recover an image
				mode = SSIExecutionMode.RECOVER;
			} else {
				throw new IllegalArgumentException(
						"You must either chose recover or distribute option");
			}
		} catch (ParseException e) {
			// I think you need to ask for help before running the program
			System.out.println(e.getMessage());
			printHelp(options);
		}
		return new SSICmdExecutionParameters(image, k, dir, n, mode);
	}

	@SuppressWarnings("static-access")
	private void setOptions() {
		OptionGroup mode = new OptionGroup();
		mode.setRequired(true);
	
		mode.addOption(OptionBuilder
				.withLongOpt("recover")
				.withDescription(
						"Recover a secret image from k source images")
				.create("r"));
		mode.addOption(OptionBuilder
				.withLongOpt("distribute")
				.withDescription(
						"Distribute a source image into other shadow images")
				.create("d"));
		options.addOptionGroup(mode);
		options.addOption(OptionBuilder
				.withLongOpt("secret")
				.withDescription(
						"Either source image to distribute (in case you have chosen the option (d)) "
								+ "or recovered image (in case they are chosen option (-r))")
				.hasArg().withArgName("IMAGE").isRequired().create("s"));
		options.addOption(OptionBuilder
				.withLongOpt("mshadows")
				.withDescription(
						"Minimum amount of shadows needed to recover the secret image")
				.hasArg().withArgName("NUMBER").isRequired().create("k"));
		options.addOption(OptionBuilder
				.withLongOpt("fshadows")
				.withDescription("Final amount of shadows where the image will be distributed")
				.hasArg().withArgName("NUMBER").create("n"));
		options.addOption(OptionBuilder
				.withLongOpt("directory")
				.withDescription("Either he directory where the images where the secret will be distributed "
						+ "(in case you have chosen the option (-d)), or where images containing hidden secret "
						+ "(in case they are chosen option (-r)). If not used, the program will search the images in the current directory.")
						.hasArg().withArgName("DIRECTORY").create("dir"));
		options.addOption(OptionBuilder
				.withLongOpt("help")
				.withDescription("Print help")
				.create("h"));
	}

	private String parseN(final CommandLine cmd) {
		if (cmd.hasOption('n')) {
			return cmd.getOptionValue('n');
		}
		return null;
	}

	private String parseDir(final CommandLine cmd) {
		if (cmd.hasOption('d')) {
			return cmd.getOptionValue('d');
		}
		return null;
	}

	private String parseSecret(final CommandLine cmd) {
		if (!cmd.hasOption('s')) {
			printHelp(this.options);
		}
		return cmd.getOptionValue('s');
	}

	private String parseK(final CommandLine cmd) {
		if (!cmd.hasOption('k')) {
			printHelp(this.options);
		}
		return cmd.getOptionValue('k');
	}

	private void printHelp(final Options options) {
		String header = "\n\nHey, try reading this help\n\n";
		 String footer = "\nSteganography in images\nHiding Data Within Data\n\tAll rights reserved\n";
		 
		 HelpFormatter formatter = new HelpFormatter();
		 formatter.setWidth(100);
		 formatter.printHelp("SSIApp", header, options, footer, true);
		System.exit(0);
	}

	public final class SSICmdExecutionParameters {
		final String image, k, dir, n;
		final SSIExecutionMode mode;

		private SSICmdExecutionParameters(final String image, final String k,
				final String dir, final String n, final SSIExecutionMode mode) {
			this.image = image;
			this.k = k;
			this.dir = dir;
			this.n = n;
			this.mode = mode;
		}

		public String getImage() {
			return this.image;
		}

		public String getK() {
			return this.k;
		}

		public String getDir() {
			return this.dir;
		}

		public String getN() {
			return this.n;
		}

		public SSIExecutionMode getMode() {
			return this.mode;
		}
	}

	public enum SSIExecutionMode {
		RECOVER, DISTRIBUTE;
	}
}
