import synthesizer.GuitarString;

public class GuitarHero {
    private static final String KEYBOARD = "q2we4r5ty7u8i9op-[=zxdcfvgbnjmk,.;/' ";
    private static final int N = 37;
    private static final double STDFREQ = 440.0;

    public static GuitarString[] guitarStringInit() {
        GuitarString[] note = new GuitarString[N];
        for (int i = 0; i < KEYBOARD.length(); i++) {
            note[i] = new GuitarString(STDFREQ * Math.pow(2, (double) (i - 24) / 12));
        }
        return note;
    }

    public static void main(String[] args) {
        GuitarString[] notes = guitarStringInit();

        while (true) {

            /* check if the user has typed a key; if so, process it */
            GuitarString note;
            if (StdDraw.hasNextKeyTyped()) {
                char key = StdDraw.nextKeyTyped();
                int index = KEYBOARD.indexOf(key);
                if (index == -1) {
                    continue;
                }
                note = notes[index];
                note.pluck();
            }

            /* compute the superposition of samples */
            double sample = 0;
            for (int i = 0; i < notes.length; i++) {
                sample += notes[i].sample();
            }

            /* play the sample on standard audio */
            StdAudio.play(sample);

            /* advance the simulation of each guitar string by one step */
            for (int i = 0; i < notes.length; i++) {
                notes[i].tic();
            }
        }
    }
}
