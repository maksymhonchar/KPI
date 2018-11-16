public class Q4 implements State {
    public void doAction(StateFSM fsm, Events curEvent) {
        switch(curEvent) {
            case MORE:
                fsm.setState(new Q5());
                break;
            case LETTER:
                fsm.setState(new Q4());
                break;
            case DIGIT:
            case LESS:
            case PLUS:
            case MINUS:
            case OTHER:
            default:
                fsm.setState(new ERR());
                break;
        }
    }

    public String toString() {
        return "q4";
    }
}
