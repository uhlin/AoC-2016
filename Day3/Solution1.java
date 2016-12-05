import java.io.*;
import java.util.*;

public class Solution1 {
    private static InputStream stream;
    private static InputStreamReader streamReader;
    private static BufferedReader br;
    private static String line;

    private static void fatal() {
	System.err.println("fatal error  --  program must exit!");
	System.exit(-1);
    }

    private static String[] getTokens(String str, String delim, boolean trim) {
	StringTokenizer stok = new StringTokenizer(str, delim);
	String[] tokens = new String[stok.countTokens()];

	for (int i = 0; i < tokens.length; i++) {
	    tokens[i] = stok.nextToken();

	    if (trim)
		tokens[i] = tokens[i].trim();
	}

	return tokens;
    }

    private static final int maxOfThree(int x, int y, int z) {
	int foo = (x > y ? x : y);

	return (z > foo ? z : foo);
    }

    public static void main(String[] args) {
	try {
	    stream	 = new FileInputStream("input");
	    streamReader = new InputStreamReader(stream);
	    br		 = new BufferedReader(streamReader);

	    int possible_triangles = 0;

	    while ((line = br.readLine()) != null) {
		String[] tokens = getTokens(line, " ", true);

		if (tokens.length != 3)
		    throw new IOException();

		if (false) {
		    System.out.println("\"" + tokens[0] + "\"");
		    System.out.println("\"" + tokens[1] + "\"");
		    System.out.println("\"" + tokens[2] + "\"");
		}

		final int x = Integer.parseInt(tokens[0]);
		final int y = Integer.parseInt(tokens[1]);
		final int z = Integer.parseInt(tokens[2]);

		if (maxOfThree(x, y, z) == x) {
		    if (y + z > x)
			possible_triangles++;
		} else if (maxOfThree(x, y, z) == y) {
		    if (x + z > y)
			possible_triangles++;
		} else {
		    if (x + y > z)
			possible_triangles++;
		}
	    }

	    System.out.printf("Possible triangles: %d\n", possible_triangles);
	} catch (Exception e) {
	    fatal();
	}
    }
}
