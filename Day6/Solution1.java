import java.io.*;
import java.util.*;

public class Solution1 {
    public static void main(String[] args) throws Exception {
	new Solution1().go();
    }

    private InputStream stream;
    private InputStreamReader streamReader;
    private BufferedReader br;

    private int a, b, c, d, e, f, g, h, i, j, k, l, m;
    private int n, o, p, q, r, s, t, u, v, w, x, y, z;

    void go() throws Exception {
	final int columnsMax = 8;
	String line = null;
	final String str = "abcdefghijklmnopqrstuvwxyz";
	final char[] alphabet = str.toCharArray();

	System.out.printf("answer: ");

	for (int loopRun = 0; loopRun < columnsMax; loopRun++) {
	    int hits = 0;
	    int mostCommonValueOf = 0;
	    char mostCommon = 'a';

	    a = b = c = d = e = f = g = h = i = j = k = l = m = 0;
	    n = o = p = q = r = s = t = u = v = w = x = y = z = 0;

	    openPuzzleInput("input");

	    while ((line = getNextLineFromFile()) != null)
		increaseHits(line.charAt(loopRun));

	    for (int index = 0; index < alphabet.length; index++) {
		hits = getHits(alphabet[index]);

		if ((hits = getHits(alphabet[index])) > mostCommonValueOf) {
		    mostCommon = alphabet[index];
		    mostCommonValueOf = hits;
		}
	    }

	    closePuzzleInput();
	    System.out.printf("%c", mostCommon);
	}

	System.out.println("");
    }

    void openPuzzleInput(final String path) throws Exception {
	stream = new FileInputStream(path);
	streamReader = new InputStreamReader(stream);
	br = new BufferedReader(streamReader);
    }

    void closePuzzleInput() throws Exception {
	br.close();
	streamReader.close();
	stream.close();
    }

    String getNextLineFromFile() throws Exception {
	return br.readLine();
    }

    void increaseHits(char chr) {
	switch (chr) {
	case 'a': a++; break;
	case 'b': b++; break;
	case 'c': c++; break;
	case 'd': d++; break;
	case 'e': e++; break;
	case 'f': f++; break;
	case 'g': g++; break;
	case 'h': h++; break;
	case 'i': i++; break;
	case 'j': j++; break;
	case 'k': k++; break;
	case 'l': l++; break;
	case 'm': m++; break;
	case 'n': n++; break;
	case 'o': o++; break;
	case 'p': p++; break;
	case 'q': q++; break;
	case 'r': r++; break;
	case 's': s++; break;
	case 't': t++; break;
	case 'u': u++; break;
	case 'v': v++; break;
	case 'w': w++; break;
	case 'x': x++; break;
	case 'y': y++; break;
	case 'z': z++; break;
	}
    }

    int getHits(char chr) {
	switch (chr) {
	case 'a': return a;
	case 'b': return b;
	case 'c': return c;
	case 'd': return d;
	case 'e': return e;
	case 'f': return f;
	case 'g': return g;
	case 'h': return h;
	case 'i': return i;
	case 'j': return j;
	case 'k': return k;
	case 'l': return l;
	case 'm': return m;
	case 'n': return n;
	case 'o': return o;
	case 'p': return p;
	case 'q': return q;
	case 'r': return r;
	case 's': return s;
	case 't': return t;
	case 'u': return u;
	case 'v': return v;
	case 'w': return w;
	case 'x': return x;
	case 'y': return y;
	case 'z': return z;
	}

	return -1;
    }
}
