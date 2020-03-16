import java.util.HashMap;

public class p149 {
    // Max Points on a Line - Hard

    // Given n points on a 2D plane, find the maximum number of points that lie on
    // the same straight line.
    class Solution {
        public int maxPoints(Point[] points) {
            if (points == null)
                return 0;
            if (points.length <= 2)
                return points.length;

            int biggestCollection = 1;
            HashMap<Line, Integer> map = new HashMap<Line, Integer>();
            for (int i = 0; i < points.length - biggestCollection; i++) {
                Point p1 = points[i];
                int matchedPoints = 0;
                int biggestThisPoint = 1;
                for (int j = i + 1; j < points.length; j++) {
                    Point p2 = points[j];
                    // System.out.println("comparing points: " + i + ", " + j);
                    // if we've found a point matching the first point, keep note of it for later
                    if (p1.x == p2.x && p1.y == p2.y) {
                        matchedPoints++;
                        continue;
                    }

                    Line line = new Line(p1, p2);
                    // System.out.println("Line - { rise: " + line.rise + ", run: " + line.run + "
                    // }");
                    int nPoints;
                    if (map.containsKey(line)) {
                        // System.out.println("!!OLD!!");
                        // we've seen this line before
                        nPoints = map.get(line) + 1;
                    } else {
                        // System.out.println("~~NEW~~");
                        // we haven't seen this line before
                        nPoints = 2;
                        map.put(line, nPoints);
                    }
                    map.put(line, nPoints);
                    biggestThisPoint = Math.max(biggestThisPoint, nPoints);
                }
                biggestThisPoint += matchedPoints;
                biggestCollection = Math.max(biggestCollection, biggestThisPoint);
                map.clear();
            }
            return biggestCollection;
        }
    }

    class Line {
        public int rise;
        public int run;
        public boolean isVertical;
        public boolean isHorizontal;

        public Line(Point p1, Point p2) {
            if (p1.y == p2.y)
                isHorizontal = true;
            else if (p1.x == p2.x)
                isHorizontal = true;
            else {
                rise = p1.y - p2.y;
                run = p1.x - p2.x;
                int gcd = calculateGCD(Math.abs(rise), Math.abs(run));
                // System.out.println("rise: " + rise + ", run: " + run + ", gcd: " + gcd);
                rise /= gcd;
                run /= gcd;
                // for consistency, if both are negative, make both positive.
                // if only one is negative, make sure it's rise
                if ((rise < 0 && run < 0) || run < 0) {
                    rise *= -1;
                    run *= -1;
                }
            }
        }

        // GCD via stein's algorithm
        private int calculateGCD(int a, int b) {
            if (a == b || b == 0)
                return a;
            if (a == 0)
                return b;

            // while even, divide by 2
            int shift = 0;
            while (((a | b) & 1) == 0) {
                shift++;
                a >>= 1;
                b >>= 1;
            }

            // force a to be odd
            while ((a & 1) == 0)
                a >>= 1;

            do {
                // force b to be odd
                while ((b & 1) == 0)
                    b >>= 1;

                if (a > b) {
                    int swap = a;
                    a = b;
                    b = swap;
                }

                b -= a;
            } while (b != 0);

            return a << shift;
        }

        @Override
        public boolean equals(Object obj) {
            if (!(obj instanceof Line))
                return false;
            Line other = (Line) obj;
            return isHorizontal == other.isHorizontal && isVertical == other.isVertical && rise == other.rise
                    && run == other.run;
        }

        @Override
        public int hashCode() {
            int hash = 17;
            hash = hash * 31 + rise;
            hash = hash * 31 + run;
            return hash;
        }
    }

    class Point {
        int x;
        int y;

        Point() {
            x = 0;
            y = 0;
        }

        Point(int a, int b) {
            x = a;
            y = b;
        }
    }
}