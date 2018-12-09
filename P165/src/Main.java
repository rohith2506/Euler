/*
Problem 165 Euler
Find number of true distinct intersection points between line segments

@Author: Rohith Uppala
 */

import java.util.ArrayList;
import java.util.HashMap;

public class Main {

    private static final long MaxNumbers = 20000;
    private static final long Modulo = 50515093;

    private static class Point {
        double x, y;

        Point(double x, double y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public String toString() {
            return String.format("{%f, %f}", x, y);
        }
    }

    private static class Line {
        Point s, e;

        Line(Point s, Point e) {
            this.s = s;
            this.e = e;
        }
    }

    private static Point findIntersection(Line l1, Line l2) {
        double a1 = l1.e.y - l1.s.y;
        double b1 = l1.s.x - l1.e.x;
        double c1 = a1 * l1.s.x + b1 * l1.s.y;

        double a2 = l2.e.y - l2.s.y;
        double b2 = l2.s.x - l2.e.x;
        double c2 = a2 * l2.s.x + b2 * l2.s.y;

        double delta = a1 * b2 - a2 * b1;

        return new Point((b2 * c1 - b1 * c2) / delta, (a1 * c2 - a2 * c1) / delta);
    }


    private int FindOrientation(Point p, Point q, Point r) {
        double value = (q.y - p.y)  * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        if(value == 0) return 0;
        return (value > 0) ? 1 : 2;
    }

    private boolean IsIntersection(Point p1, Point q1, Point p2, Point q2) {
        int o1 = FindOrientation(p1, q1, p2);
        int o2 = FindOrientation(p1, q1, q2);
        int o3 = FindOrientation(p2, q2, p1);
        int o4 = FindOrientation(p2, q2, q1);

        if (o1 != 0 && o2 != 0 && o3 != 0 && o4 != 0 && o1 != o2 && o3 != o4) return true;
        else return false;
    }

    private ArrayList<Integer> GenerateLineSegmentNumbers() {
        ArrayList<Integer> Numbers = new ArrayList<>();
        long InitialNumber = 290797;
        for(int i = 0; i < MaxNumbers; i++) {
            Long NewNumber = ((InitialNumber % Modulo) * (InitialNumber % Modulo))  % Modulo;
            Numbers.add((int)(NewNumber % 500));
            InitialNumber = NewNumber;
        }
        return Numbers;
    }

    public static void main(String[] args) {
        Main main = new Main();
        ArrayList<Integer> LineSegmentNumbers = main.GenerateLineSegmentNumbers();
        int count = 0, totalLoops = 0;

        HashMap<String, Boolean> DistinctPoints = new HashMap<>();

        for(int i=0; i<=LineSegmentNumbers.size() - 4; i=i+4) {

            Point p1 = new Point(LineSegmentNumbers.get(i), LineSegmentNumbers.get(i+1));
            Point p2 = new Point(LineSegmentNumbers.get(i+2), LineSegmentNumbers.get(i+3));

            for(int j=i+4; j<=LineSegmentNumbers.size() - 4; j=j+4) {

                Point p3 = new Point(LineSegmentNumbers.get(j), LineSegmentNumbers.get(j+1));
                Point p4 = new Point(LineSegmentNumbers.get(j+2), LineSegmentNumbers.get(j+3));


                if(main.IsIntersection(p1, p2, p3, p4)) {
                    Line l1 = new Line(p1, p2);
                    Line l2 = new Line(p3, p4);

                    Point intersectionPoint = findIntersection(l1, l2);

                    if(!DistinctPoints.containsKey(intersectionPoint.toString())) {
                        DistinctPoints.put(intersectionPoint.toString(), true);
                        count = count + 1;
                    }
                }

                totalLoops += 1;
                if(totalLoops % 1000 == 0) {
                    System.out.println("totalLoops: " + totalLoops);
                }
            }
        }

        System.out.println("Number of true intersection points: " + count);
    }
}
