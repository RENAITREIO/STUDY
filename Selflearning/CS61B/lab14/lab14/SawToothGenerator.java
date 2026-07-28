package lab14;

import lab14lib.Generator;

public class SawToothGenerator implements Generator {
    private int period;
    private int state;

    public SawToothGenerator(int period) {
        state = 0;
        this.period = period;
    }

    @Override
    public double next() {
        double val = (double) (2 * (state % period)) / (period - 1) - 1;
        state += 1;
        return val;
    }
}
