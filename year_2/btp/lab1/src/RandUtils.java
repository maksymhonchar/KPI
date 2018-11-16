import java.security.SecureRandom;
import java.util.Date;

public class RandUtils {
    private SecureRandom _rnd = null;

    public RandUtils() {
        _rnd = new SecureRandom();
        _rnd.setSeed(new Date().getTime());
    }

    public char getRndNumber() {
        String numbers = "0123456789";
        return numbers.charAt(_rnd.nextInt(numbers.length()));
    }

    public char getRndLetter() {
        StringBuilder sb = new StringBuilder();
        for (char i = 'A'; i <= 'Z'; i++) {
            sb.append(i);
        }
        String _letters = sb.toString();
        return _letters.charAt(_rnd.nextInt(_letters.length()));
    }

    public boolean getRndChance(int chance) {
        chance = Math.abs(chance) % 100;
        return _rnd.nextInt(100 ) < chance;
    }

    public int getRndAmount(int max)
    {
        return _rnd.nextInt(max);
    }
}
