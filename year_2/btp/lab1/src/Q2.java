public class Q2 implements State {

    public void doAction(StateFSM fsm, Events curEvent) {

        switch(curEvent) {
            case DIGIT:
                fsm.setState(new Q3());
                break;
            case LETTER:
                fsm.setState(new Q4());
                break;
            case LESS:
            case MORE:
            case MINUS:
            case PLUS:
            case OTHER:
            default:
                fsm.setState(new ERR());
                break;
        }
    }

    public String toString() {
        return "q2";
    }
}
