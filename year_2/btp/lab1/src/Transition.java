public class Transition {
    protected States _startEvent;
    protected States _endEvent;
    protected Events _trigger;

    public Transition(States startEv, States endEv, Events curEv) {
        _startEvent = startEv;
        _endEvent = endEv;
        _trigger = curEv;
    }

}
