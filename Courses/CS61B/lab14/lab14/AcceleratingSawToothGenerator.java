package lab14;

import lab14lib.Generator;

public class AcceleratingSawToothGenerator implements Generator {
    private int state;
    private int period;
    private double acc;

    public AcceleratingSawToothGenerator(int period, double acc) {
        this.period = period;
        this.acc = acc;
        state = 0;
    }

    @Override
    public double next() {
        double val = (double) (2 * (state % period)) / (period - 1) - 1;
        state += 1;
        if (state % period == 0) {
            period = (int) Math.floor(period * acc);
            state = 0;
        }
        return val;
    }
}
