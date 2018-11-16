public class Q3 implements State {
    public void doAction(StateFSM fsm, Events curEvent) {

        switch(curEvent) {
            case MORE:
                fsm.setState(new Q5());
                break;
            case DIGIT:
                fsm.setState(new Q3());
                break;
            case LETTER:
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
        return "q3";
    }
}
