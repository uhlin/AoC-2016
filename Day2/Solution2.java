import java.io.*;
import java.util.*;

public class Solution2 {
    private static InputStream stream;
    private static InputStreamReader streamReader;
    private static BufferedReader br;
    private static String line;
    private static final int A = 100;
    private static final int B = 101;
    private static final int C = 102;
    private static final int D = 103;
    private static int position = 5;

    private static void fatal() {
	System.err.println("fatal error  --  program must exit!");
	System.exit(1);
    }

    private static void moveUp(int pos) {
	if (pos == 5 || pos == 2 || pos == 1 || pos == 4 || pos == 9)
	    return;
	else if (pos == A) position = 6;
	else if (pos == 6) position = 2;
	else if (pos == D) position = B;
	else if (pos == B) position = 7;
	else if (pos == 7) position = 3;
	else if (pos == 3) position = 1;
	else if (pos == C) position = 8;
	else if (pos == 8) position = 4;
	else fatal();
    }

    private static void moveDown(int pos) {
	if (pos == 5 || pos == A || pos == D || pos == C || pos == 9)
	    return;
	else if (pos == 2) position = 6;
	else if (pos == 6) position = A;
	else if (pos == 1) position = 3;
	else if (pos == 3) position = 7;
	else if (pos == 7) position = B;
	else if (pos == B) position = D;
	else if (pos == 4) position = 8;
	else if (pos == 8) position = C;
	else fatal();
    }

    private static void moveLeft(int pos) {
	if (pos == 1 || pos == 2 || pos == 5 || pos == A || pos == D)
	    return;
	else if (pos == 4) position = 3;
	else if (pos == 3) position = 2;
	else if (pos == 9) position = 8;
	else if (pos == 8) position = 7;
	else if (pos == 7) position = 6;
	else if (pos == 6) position = 5;
	else if (pos == C) position = B;
	else if (pos == B) position = A;
	else fatal();
    }

    private static void moveRight(int pos) {
	if (pos == 1 || pos == 4 || pos == 9 || pos == C || pos == D)
	    return;
	else if (pos == A) position = B;
	else if (pos == B) position = C;
	else if (pos == 5) position = 6;
	else if (pos == 6) position = 7;
	else if (pos == 7) position = 8;
	else if (pos == 8) position = 9;
	else if (pos == 2) position = 3;
	else if (pos == 3) position = 4;
	else fatal();
    }

    private static void moveToNewPos(int pos, char move) {
	switch (move) {
	case 'U':
	    moveUp(pos);
	    return;
	case 'D':
	    moveDown(pos);
	    return;
	case 'L':
	    moveLeft(pos);
	    return;
	case 'R':
	    moveRight(pos);
	    return;
	}
    }

    public static void main(String[] ar) {
	try {
	    stream	 = new FileInputStream("input");
	    streamReader = new InputStreamReader(stream);
	    br		 = new BufferedReader(streamReader);

	    while ((line = br.readLine()) != null) {
		for (int i = 0; i < line.length(); i++) {
		    if (true) {
			if (line.charAt(i) != 'U' && line.charAt(i) != 'D' &&
			    line.charAt(i) != 'L' && line.charAt(i) != 'R')
			    throw new IOException();
		    }

		    moveToNewPos(position, line.charAt(i));
		}

		if (position == A)
		    System.out.printf("A");
		else if (position == B)
		    System.out.printf("B");
		else if (position == C)
		    System.out.printf("C");
		else if (position == D)
		    System.out.printf("D");
		else
		    System.out.printf("%d", position);
	    }

	    System.out.printf("\n");
	} catch (Exception e) {
	    fatal();
	}
    }
}
