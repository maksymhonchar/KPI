public class Q5 implements State {

    public void doAction(StateFSM fsm, Events curEvent) {
        switch(curEvent) {
            case MORE:
            case DIGIT:
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
        return "q5";
    }
}
