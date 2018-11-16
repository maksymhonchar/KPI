public class ERR implements State {
    public void doAction(StateFSM fsm, Events curEvent) {
        fsm.setState(new ERR());
    }

    public String toString() {
        return "ERR";
    }
}
