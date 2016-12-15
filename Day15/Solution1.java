import java.io.*;
import java.util.*;
import java.util.regex.*;

public class Solution1 {
    public static void main(String[] args) throws Exception {
	new Solution1().go();
    }

    private InputStream stream;
    private InputStreamReader streamReader;
    private BufferedReader br;

    private class Disc {
	int discNum;
	int numPos;
	int atTime;
	int atPosition;
    }

    private List<Disc> discs = new ArrayList<Disc>();

    private final boolean puzzlePartTwo = false;

    void go() throws Exception {
	String	line	= null;
	Pattern pattern = Pattern.compile("\\d+");
	int	time	= 0;
	Disc	element = null;

	openPuzzleInput("inputM");

	while ((line = getNextLineFromFile()) != null) {
	    Matcher matcher = pattern.matcher(line);
	    int run = 0;
	    int val1, val2, val3, val4;

	    val1 = val2 = val3 = val4 = -1;

	    while (matcher.find()) {
		switch (run++) {
		case 0:
		    val1 = Integer.parseInt(matcher.group());
		    break;
		case 1:
		    val2 = Integer.parseInt(matcher.group());
		    break;
		case 2:
		    val3 = Integer.parseInt(matcher.group());
		    break;
		case 3:
		    val4 = Integer.parseInt(matcher.group());
		    break;
		default:
		    throw new Exception();
		}
	    }

	    if (val1 < 0 || val2 < 0 || val3 < 0 || val4 < 0)
		throw new Exception();
	    element = new Disc();
	    element.discNum    = val1;
	    element.numPos     = val2;
	    element.atTime     = val3;
	    element.atPosition = val4;
	    discs.add(element);
	}

	if (puzzlePartTwo) {
	    element = new Disc();
	    element.discNum    = discs.size() + 1;
	    element.numPos     = 11;
	    element.atTime     = 0;
	    element.atPosition = 0;
	    discs.add(element);
	}

	while (true) {
	    boolean bad = false;

	    for (int i = 0; i < discs.size(); i++) {
		Disc elmt = discs.get(i);

		if ((elmt.discNum + elmt.atPosition + time) % elmt.numPos != 0)
		    bad = true;
	    }

	    if (!bad)
		break;
	    time++;
	}

	if (false)
	    outputList();

	System.out.println(time);

	closePuzzleInput();
    }

    void openPuzzleInput(final String path) throws Exception {
	stream	     = new FileInputStream(path);
	streamReader = new InputStreamReader(stream);
	br	     = new BufferedReader(streamReader);
    }

    void closePuzzleInput() throws Exception {
	br.close();
	streamReader.close();
	stream.close();
    }

    String getNextLineFromFile() throws Exception {
	return br.readLine();
    }

    void outputList() {
	for (int i = 0; i < discs.size(); i++) {
	    Disc element = discs.get(i);

	    System.out.println("---------- " + "disc: " + element.discNum +
			       " ----------");
	    System.out.printf("pos:\t%d(%d)\ntime:\t%d\n",
		element.numPos, element.atPosition, element.atTime);
	}
    }
}
