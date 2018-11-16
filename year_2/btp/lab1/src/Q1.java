public class Q1 implements State{
    public void doAction(StateFSM fsm, Events curEvent) {
        switch(curEvent) {
            case PLUS:
                fsm.setState(new Q2());
                break;
            case MINUS:
                fsm.setState(new Q2());
                break;
            case MORE:
            case LESS:
            case DIGIT:
            case LETTER:
            case OTHER:
            default:
                fsm.setState(new ERR());
                break;
        }
    }

    public String toString() {
        return "q1";
    }
}
