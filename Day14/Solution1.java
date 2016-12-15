import java.io.*;
import java.security.*;
import java.util.*;

public class Solution1 {
    public static void main(String[] args) throws Exception {
	new Solution1().go();
    }

    private MessageDigest	md	    = null;
    private final int		loopMax	    = 100000000;
    private final String	puzzleInput = "qzyelonm";
    private char		triple	    = 'X';

    void go() throws Exception {
	int	index	= 0;
	int	matches = 0;

	md = MessageDigest.getInstance("MD5");

	while (index < loopMax) {
	    String hash = getHash(index);

	    if (!threeInRow(hash)) {
		index++;
		continue;
	    }

	    for (int Foo = (index + 1); Foo < (index + 1000); Foo++) {
		hash = getHash(Foo);
		if (gotFiveHits(hash, triple)) {
		    matches++;
		    break;
		}
	    }

	    if (matches == 64)
		break;
	    index++;
	}

	System.out.printf("index:   %d\n", index);
	System.out.printf("matches: %d\n", matches);
    }

    String getHashHelper(final byte[] array) {
	StringBuffer sb = new StringBuffer();

	for (int i = 0; i < array.length; i++)
	    sb.append(Integer.toString((array[i] & 0xff) + 0x100,
				       16).substring(1));

	return sb.toString();
    }

    String getHash(final int index) {
	byte[] a, b, result;
	final String numbers = Integer.toString(index);

	a = puzzleInput.getBytes();
	b = numbers.getBytes();

	result = new byte[a.length + b.length];
	System.arraycopy(a, 0, result, 0, a.length);
	System.arraycopy(b, 0, result, a.length, b.length);

	md.update(result);
	return getHashHelper(md.digest());
    }

    boolean threeInRow(final String hash) {
	final int hashLen = hash.length();

	for (int i = 0; i < hashLen; i++) {
	    if ((i + 2) >= hashLen)
		return false;
	    if (hash.charAt(i) == hash.charAt(i + 1) &&
		hash.charAt(i + 1) == hash.charAt(i + 2)) {
		triple = hash.charAt(i);
		return true;
	    }
	}

	return false;
    }

    boolean gotFiveHits(String hash, char c) {
	final int hashLen = hash.length();

	for (int i = 0; i < hashLen; i++) {
	    if ((i + 4) >= hashLen)
		return false;
	    if (hash.charAt(i) == c &&
		hash.charAt(i) == hash.charAt(i + 1) &&
		hash.charAt(i + 1) == hash.charAt(i + 2) &&
		hash.charAt(i + 2) == hash.charAt(i + 3) &&
		hash.charAt(i + 3) == hash.charAt(i + 4))
		return true;
	}

	return false;
    }
}
