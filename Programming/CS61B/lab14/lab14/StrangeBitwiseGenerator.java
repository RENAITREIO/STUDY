package lab14;

import lab14lib.Generator;

public class StrangeBitwiseGenerator implements Generator {
    private int period;
    private int state;

    public StrangeBitwiseGenerator(int period) {
        state = 0;
        this.period = period;
    }

    @Override
    public double next() {
        int weirdState = state & (state >>> 3) & (state >> 8) % period;
        double val = (double) (2 * (weirdState % period)) / (period - 1) - 1;
        state += 1;
        return val;
    }
}
