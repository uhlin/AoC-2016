import java.io.*;
import java.security.*;
import java.util.*;

public class Solution1 {
    public static void main(String[] args) throws Exception {
	new Solution1().go();
    }

    private final String puzzleInput = "ugkcyxxp";

    void go() throws Exception {
	final int loopMax = 100000000;
	byte[] a, b, result;
	MessageDigest md = MessageDigest.getInstance("MD5");
	int matches = 0;

	for (int i = 0; i < loopMax; i++) {
	    final String numbers = Integer.toString(i);
	    String hash = null;

	    a = puzzleInput.getBytes();
	    b = numbers.getBytes();

	    result = new byte[a.length + b.length];
	    System.arraycopy(a, 0, result, 0, a.length);
	    System.arraycopy(b, 0, result, a.length, b.length);

	    md.update(result);
	    hash = getHash(md.digest());
	    if (hash.startsWith("00000")) {
		System.out.printf("%c", hash.charAt(5));
		matches++;
		if (matches == 8)
		    break;
	    }
	}

	System.out.println("");
	System.out.printf("matches: %d\n", matches);
    }

    void fatal() {
	System.err.println("fatal error  --  program must exit!");
	System.exit(1);
    }

    String getHash(final byte[] array) {
	StringBuffer sb = new StringBuffer();

	for (int i = 0; i < array.length; i++)
	    sb.append(Integer.toString((array[i] & 0xff) + 0x100,
				       16).substring(1));

	return sb.toString();
    }
}
