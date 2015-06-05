package ar.edu.itba.cys.ssi.bytebuffer;

import java.nio.ByteBuffer;

// This class is intended to manage everything regarding ByteBuffers.

// WRITING MODE
// capacity = n
// limit = capacity
// position = x <= n

// READING MODE
// capacity = n
// limit = m <= n
//position = 0

public class ByteBufferTools {

	private static final int cr = 13;
	private static final int lf = 10;
	private static final int point = 46;

	public static void likeNewBuffer(final ByteBuffer buf) {
		// leaves the buffer in writing mode
		buf.clear();
	}

	public static void clearWhatWasAlreadyRead(final ByteBuffer buf) {
		// Assumes the buffer in reading mode
		// Leaves the buffer in writing mode
		buf.compact();
	}

	public static void prepareForReReading(final ByteBuffer buf) {
		// Assumes its in reading mode
		// Leaves the buffer in reading mode
		buf.rewind();
	}

	public static void switchToReadingMode(final ByteBuffer buf) {
		// Assumes the buffer in writing mode
		// Leaves the buffer in reading mode
		buf.flip();
	}

	public static int getHowManyBytesWritten(final ByteBuffer buf) {
		// Assumes the buffer in reading mode
		return buf.remaining();
	}

	public static int emptySpace(final ByteBuffer buf) {
		// Assumes buffer in writing mode 
		return buf.capacity() - buf.position();
	}

	public static ByteBuffer copyFromSrcToDest(final byte[] src, ByteBuffer dest) {
		dest.put(src);
		return dest;
	}

	public static ByteBuffer copyFromSrcToDestQty(byte[] src, ByteBuffer dest,
			int qty) {
		int i = 0;
		while (i < qty) {
			dest.put(src[i++]);
		}
		return dest;
	}
	
	public static ByteBuffer removeEndOfLine(ByteBuffer buf){
		// Assumes the buffer in writing mode
		ByteBufferTools.switchToReadingMode(buf);
		int limit = buf.limit();
		byte[] withoutEnter = new byte[limit-2];
		buf.get(withoutEnter,0,withoutEnter.length);
		buf.get();
		buf.get();
		return ByteBuffer.wrap(withoutEnter);
	}
	
	public static byte[] getEndOfLine(){
		byte ans[] = new byte[2];
		ans[0] = cr;
		ans[1] = lf;
		return ans;
	}

	public static ByteBuffer safeCopyFromSrcToDest(ByteBuffer src,
			ByteBuffer dest) {
		// Assumes src in reading mode
		// Assumes dest in writing mode
		if (getHowManyBytesWritten(src) < emptySpace(dest)) {
			while (src.hasRemaining())
				dest.put(src.get());
		} else {
			ByteBuffer aux = ByteBuffer.allocate(dest.capacity() * 2 + src.capacity());
			switchToReadingMode(dest);
			while (dest.hasRemaining()) {
				aux.put(dest.get());
			}
			aux.put(src);
			dest = aux;
		}
		return dest;
	}

	public static boolean fits(final ByteBuffer dest, final byte[] src) {
		return (emptySpace(dest) > src.length);
	}

	public static boolean itsNewLine(byte[] line) {
		return (line[0] == cr) && (line[1] == lf);
	}

	public static boolean itsEndOfMessage(byte[] line) {
		return (line[0] == point) && (line[1] == cr) && (line[2] == lf);
	}
	
	public static ByteBuffer newBufferFromBuffer(ByteBuffer buffer){
		// Assumes the buffer is in writing mode, so we need to flip it
		// it returns the buffer in writing mode
		switchToReadingMode(buffer);
		byte[] arr = new byte[buffer.limit()];
		buffer.get(arr);
		ByteBuffer buf = ByteBuffer.allocate(arr.length);
		buf.put(arr);
		ByteBufferTools.clearWhatWasAlreadyRead(buffer);
		return buf;
	}
	
	public static ByteBuffer newPartBufferFromBuffer(ByteBuffer buffer, int  length){
		// Asummes buffer in write mode
		// clears the copied data from buffer
		ByteBuffer buf = null;
		switchToReadingMode(buffer);
		if(length <= buffer.limit()){
			buf = ByteBuffer.allocate(length);
			int i = 0;
			while(buffer.hasRemaining() && i++ < length)
				buf.put(buffer.get());
		}
		ByteBufferTools.clearWhatWasAlreadyRead(buffer);
		return buf;
	}

	public static byte[] readLine(ByteBuffer buffer) {
		boolean crFlag = false;
		boolean lfFlag = false;
		if (buffer.limit() == 0) {
			return null;
		}
		byte[] array = new byte[buffer.limit()];
		int i = 0;
		byte b;
		do {
			b = buffer.get();
			array[i++] = b;
			if (b == cr) {
				crFlag = true;
			} else if (b == lf) {
				lfFlag = true;
			}
		} while (buffer.hasRemaining() && !crFlag && !lfFlag);
		if (!crFlag && !lfFlag) {
			return null;
		} else {
			if (crFlag) {
				if (buffer.limit() == 0 || buffer.limit() == buffer.position()) {
					return null;
				}
				b = buffer.get();
				if (b != lf) {
					return null;
				}
				array[i++] = b;
			}
			byte[] outArray = new byte[i];
			for (int b1 = 0; b1 < outArray.length; b1++)
				outArray[b1] = array[b1];
			return outArray;
		}
	}
}
