public class FSM {

    protected States _currentState;

    public FSM() {
        _currentState = States.q0;
    }

    private void start() {
        _currentState = States.q0;
    }

    public Events recognizeEvent(char curSymbol) {
        switch(curSymbol) {
            case '>':
                return Events.MORE;
            case '<':
                return Events.LESS;
            case '+':
                return Events.PLUS;
            case '-':
                return Events.MINUS;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
                return Events.DIGIT;
            case 'p':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
                return Events.LETTER;
        }
        return Events.OTHER;
    }

    // Default implementation.
    public boolean scanString(String toScan) {
        start();
        for (int i = 0; i < toScan.length(); i++) {
            Events curEvent = recognizeEvent(toScan.charAt(i));
            _currentState = nextState(curEvent);
            if (_currentState == States.ERR) {
                return false;
            }
        }
        return _currentState == States.q5;
    }

    // Default implementation.
    protected States nextState(Events curEvent) {
        return States.ERR;
    }

}
