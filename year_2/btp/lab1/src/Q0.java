public class Q0 implements State {

    public void doAction(StateFSM fsm, Events curEvent) {
        switch(curEvent) {
            case LESS:
                fsm.setState(new Q1());
                break;
            case MORE:
            case PLUS:
            case MINUS:
            case DIGIT:
            case LETTER:
            case OTHER:
            default:
                fsm.setState(new ERR());
                break;
        }
    }

    public String toString() {
        return "q0";
    }
}
