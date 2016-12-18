import java.io.*;
import java.util.*;

public class Solution1 {
    public static void main(String[] args) throws Exception {
	new Solution1().go();
    }

    /* Initial state */
    private final String puzzleInput = "10111100110001111";

    /* Set to '35651584' for part 2 of the puzzle */
    private final int diskSize = 272;

    private class Compos {
	String str;
	int strLen;
    }

    void go() throws Exception {
	Compos	compos	  = null;
	String	chksum	  = null;
	String	str	  = null;
	int	chksumLen = 0;
	int	strLen	  = 0;

	compos = makeStringLonger(puzzleInput);
	str = new String(compos.str);
	strLen = compos.strLen;

	while (strLen < diskSize) {
	    compos = makeStringLonger(str);
	    str = new String(compos.str);
	    strLen = compos.strLen;
	}

	compos = getChecksum(getRidOfTrailing(str),
			     getRidOfTrailing(str).length());

	while ((compos.strLen % 2) == 0) {
	    str = new String(compos.str);
	    strLen = compos.strLen;
	    compos = getChecksum(str, strLen);
	}

	System.out.printf("answer: %s\n", compos.str);
    }

    Compos makeStringLonger(String input) {
	String reversed = new StringBuilder(input).reverse().toString();
	Compos out = new Compos();

	reversed = reversed.replace('0', 'X');
	reversed = reversed.replace('1', '0');
	reversed = reversed.replace('X', '1');

	out.str = (input + "0" + reversed);
	out.strLen = (input + "0" + reversed).length();

	return (out);
    }

    String getRidOfTrailing(String input) {
	char[] ar = new char[diskSize];

	for (int i = 0; i < diskSize; i++)
	    ar[i] = input.charAt(i);

	return new String(ar);
    }

    Compos getChecksum(String input, int inputLen) {
	int i, j;
	char[] ar = new char[inputLen];
	Compos out = new Compos();

	for (i = j = 0; i < inputLen; i += 2, j++) {
	    if (input.charAt(i) == input.charAt(i + 1))
		ar[j] = '1';
	    else
		ar[j] = '0';
	}

	out.str = new String(ar);
	out.strLen = j;

	return (out);
    }
}
