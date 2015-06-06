package ar.edu.itba.cys.ssi.execution;

import java.awt.image.BufferedImage;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import javax.imageio.ImageIO;

import ar.edu.itba.cys.ssi.bytebuffer.ByteBufferTools;

public class BitMapParser {

	private final static int HEADER_LENGHT = 54;

	public BMPImageInformation parseImage(final String str) {
		// We try to load the image
		File imgPath = new File(str);
		BufferedImage bufferedImage;
		byte[] imageAsBytes = null;
		try {
			bufferedImage = ImageIO.read(imgPath);
			ByteArrayOutputStream baos = new ByteArrayOutputStream();
			ImageIO.write(bufferedImage, "bmp", baos);
			baos.flush();
			imageAsBytes = baos.toByteArray();
			baos.close();
		} catch (IOException e) {
			e.printStackTrace(); // We fucked up
		}
		// We could do it more efficient, but we do not care about that
		ByteBuffer bb = ByteBuffer.wrap(imageAsBytes); // the bb is in reading
														// mode.
		bb.order(ByteOrder.LITTLE_ENDIAN); // (big endian, Java's native) so we
											// change it to little endian

		final int fileSize = getFileSize(bb); // I do not know if we need this but, who cares right? Looks pretty cool!!
		final int imageOffset = getImageOffset(bb);
		final int imageSize = getImageSize(bb);
		final byte[] image = getImage(bb, imageOffset, imageSize);
		
		return new BMPImageInformation(imageSize, image);
	}
	
	private byte[] getImage(final ByteBuffer bb, final int imageOffset, final int imageSize) {
		byte[] image = new byte[imageSize]; 
		int j = 0;
		for (int i = imageOffset; i < imageSize; i++) {
			image[j++] = bb.get(i);
		}
		return image;
	}

	private int getFileSize(final ByteBuffer bb) {
		final int file_size_offset = 2;
		final int file_size = bb.getInt(file_size_offset);
		ByteBufferTools.prepareForReReading(bb); // We leave it exactly as it was before
		return file_size;
	}

	private int getImageOffset(final ByteBuffer bb) {
		final int image_offset_offset = 4; // pretty cool name right?
		final int image_offset = bb.getInt(image_offset_offset);
		ByteBufferTools.prepareForReReading(bb); // We leave it exactly as it was before
		return image_offset;
	}
	
	private int getImageSize(final ByteBuffer bb) {
		final int image_size_offset = 22;
		final int image_offset = bb.getInt(image_size_offset);
		ByteBufferTools.prepareForReReading(bb); // We leave it exactly as it was before
		return image_offset;
	}

	public final class BMPImageInformation {

		private static final int BITS_PER_PIXEL = 8; // I do not know if we need this but, who cares right?

		private final int imageSize;
		private final byte[] image;

		private BMPImageInformation(final int imageSize, final byte[] image) {
			this.imageSize = imageSize;
			this.image = image;
		}

		public byte[] getImage() {
			return image;
		}
		
	}

}
