/*
This is a classic example of Dragon Curve.
We used the following algorithm to calculate the coordinate position after n steps
https://en.wikipedia.org/w/index.php?title=Dragon_curve&oldid=259897065#Coordinate_calculation

@Author: Rohith Uppala
*/

public class Main {
    static  class Point {
        private int x, y;
        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    private static Point GenerateHeighwayDragon(long n) {
        Point p = new Point(0, 1);
        long steps = 1, length = 1;
        while(length < n) {
            p = new Point(p.x + p.y, p.y - p.x);
            length = length * 2;
        }
        if(length == n) return p;
        long m = length - n;
        Point p2 = GenerateHeighwayDragon(m);
        p2 = new Point(-p2.y, p2.x);
        return new Point(p.x + p2.x, p.y + p2.y);
    }

    public static void main(String[] args) {
        long n = (long)1e12;
        Point result = GenerateHeighwayDragon(n);
        System.out.println("Result: " + result.x + " , " + result.y);
    }
}
