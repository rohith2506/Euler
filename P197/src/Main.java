import java.util.ArrayList;

public class Main {

    private static final double CONSTANT_VALUE = 30.403243784;

    private static double func(double x) {
        double numerator = Math.floor(Math.pow(2, CONSTANT_VALUE - (x * x)));
        double result = numerator * 1.0 / 1E9;
        return result;
    }

    public static void main(String[] args) {
        ArrayList<Double> results = new ArrayList<>();

        double initialResult = -1.0;
        for(long n = 0; n <= 1e3; n++) {
            double nextResult = func(initialResult);
            double finalResult = nextResult + initialResult;
            initialResult = nextResult;
            results.add(nextResult);
            System.out.println(n + "=>" + finalResult);
        }
        System.out.println(results);
    }
}