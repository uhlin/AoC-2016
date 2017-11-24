import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class Day1 {
    public static void main(String[] args) {
        new Day1().go();
    }

    void go() {
        Charset cs = Charset.forName("UTF-8");
        Path puzzleInput = Paths.get("input");
        String lineOne = null;

        try {
            List<String> lines = Files.readAllLines(puzzleInput, cs);

            for (String line : lines) {
                lineOne = new String(line);
                break;
            }
        } catch (Exception ex) {
            System.err.println("Error: " + ex);
            System.exit(1);
        }

        String[] instructions = lineOne.split(", ");
        MakeMove mm = new MakeMove();
        int i = 0;

        for (String instruction : instructions) {
            instruction.trim();
            int blocks = Integer.parseInt(instruction.substring(1));
            if (instruction.charAt(0) == 'L')
                mm.moveLeft(blocks);
            else if (instruction.charAt(0) == 'R')
                mm.moveRight(blocks);
            else {
                System.err.println("fatal: bogus instruction!");
                System.exit(1);
            }
        }

        System.out.println("Part 1: " + mm.blocksAway());
        System.out.println("Part 2: " + mm.getFirstLocationVisitedTwice());
    }
}

class MakeMove {
    private Direction direction;
    private int blocksNorth;
    private int blocksEast;
    private int blocksSouth;
    private int blocksWest;
    private List<Position> positions;
    private int firstLocationVisitedTwice;
    public MakeMove() {
        this.direction = Direction.NORTH;
        this.blocksNorth = 0;
        this.blocksEast = 0;
        this.blocksSouth = 0;
        this.blocksWest = 0;
        this.positions = new ArrayList<Position>();
        this.firstLocationVisitedTwice = -1;
    }

    public void moveLeft(int blocks) {
        switch (direction) {
            case NORTH:
                direction = Direction.WEST;
                walkWest(blocks);
                break;
            case SOUTH:
                direction = Direction.EAST;
                walkEast(blocks);
                break;

            case EAST:
                direction = Direction.NORTH;
                walkNorth(blocks);
                break;
            case WEST:
                direction = Direction.SOUTH;
                walkSouth(blocks);
                break;

            default:
                System.err.println("moveLeft: fatal error");
                System.exit(1);
        }
    }

    public void moveRight(int blocks) {
        switch (direction) {
            case NORTH:
                direction = Direction.EAST;
                walkEast(blocks);
                break;
            case SOUTH:
                direction = Direction.WEST;
                walkWest(blocks);
                break;

            case EAST:
                direction = Direction.SOUTH;
                walkSouth(blocks);
                break;
            case WEST:
                direction = Direction.NORTH;
                walkNorth(blocks);
                break;

            default:
                System.err.println("moveRight: fatal error");
                System.exit(1);
        }
    }

    private void walkNorth(int blocks) {
        while (blocks != 0 && blocksSouth != 0) {
            blocksSouth--;
            blocks--;
            addVisited(blocksNorth, blocksSouth, blocksEast, blocksWest);
        }
        while (blocks != 0) {
            blocksNorth++;
            blocks--;
            addVisited(blocksNorth, blocksSouth, blocksEast, blocksWest);
        }
    }

    private void walkSouth(int blocks) {
        while (blocks != 0 && blocksNorth != 0) {
            blocksNorth--;
            blocks--;
            addVisited(blocksNorth, blocksSouth, blocksEast, blocksWest);
        }
        while (blocks != 0) {
            blocksSouth++;
            blocks--;
            addVisited(blocksNorth, blocksSouth, blocksEast, blocksWest);
        }
    }

    private void walkEast(int blocks) {
        while (blocks != 0 && blocksWest != 0) {
            blocksWest--;
            blocks--;
            addVisited(blocksNorth, blocksSouth, blocksEast, blocksWest);
        }
        while (blocks != 0) {
            blocksEast++;
            blocks--;
            addVisited(blocksNorth, blocksSouth, blocksEast, blocksWest);
        }
    }

    private void walkWest(int blocks) {
        while (blocks != 0 && blocksEast != 0) {
            blocksEast--;
            blocks--;
            addVisited(blocksNorth, blocksSouth, blocksEast, blocksWest);
        }
        while (blocks != 0) {
            blocksWest++;
            blocks--;
            addVisited(blocksNorth, blocksSouth, blocksEast, blocksWest);
        }
    }

//    public void printPosition() {
//        System.out.print(" N:" + blocksNorth);
//        System.out.print(" S:" + blocksSouth);
//        System.out.print(" E:" + blocksEast);
//        System.out.print(" W:" + blocksWest);
//        System.out.print('\n');
//    }

    public int getFirstLocationVisitedTwice() {
        return firstLocationVisitedTwice;
    }

    public void addVisited(int north, int south, int east, int west) {
        for (Position position : positions) {
            if (position.getNorth() == north && position.getSouth() == south &&
                    position.getEast() == east && position.getWest() == west) {
                if (firstLocationVisitedTwice == -1)
                    firstLocationVisitedTwice = blocksAway();
            }
        }

        positions.add(new Position(north, south, east, west));
    }

    public int blocksAway() {
        int diff1 = 0;
        int diff2 = 0;

        diff1 = ((blocksNorth > blocksSouth)
                ? blocksNorth - blocksSouth
                : blocksSouth - blocksNorth);
        diff2 = ((blocksWest > blocksEast)
                ? blocksWest - blocksEast
                : blocksEast - blocksWest);

        return (diff1 + diff2);
    }

    enum Direction {
        NORTH,
        EAST,
        SOUTH,
        WEST
    }
}

class Position {
    private int north;
    private int south;
    private int east;
    private int west;

    public Position(int north, int south, int east, int west) {
        this.north = north;
        this.south = south;
        this.east = east;
        this.west = west;
    }

    public int getNorth() {
        return north;
    }

    public int getSouth() {
        return south;
    }

    public int getEast() {
        return east;
    }

    public int getWest() {
        return west;
    }
}
