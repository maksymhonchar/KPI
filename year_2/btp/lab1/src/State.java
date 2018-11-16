public interface State {
    void doAction(StateFSM fsm, Events curEv);
}
