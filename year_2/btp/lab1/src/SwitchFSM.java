public class SwitchFSM extends FSM {

    protected States nextState(Events curEvent) {
        switch (_currentState) {
            case q0:
                switch(curEvent) {
                    case LESS:
                        return States.q1;
                    case MORE:
                    case PLUS:
                    case MINUS:
                    case DIGIT:
                    case LETTER:
                    case OTHER:
                    default:
                        return States.ERR;
                }

            case q1:
                switch(curEvent) {
                    case PLUS:
                        return States.q2;
                    case MINUS:
                        return States.q2;
                    case MORE:
                    case LESS:
                    case DIGIT:
                    case LETTER:
                    case OTHER:
                    default:
                        return States.ERR;
                }

            case q2:
                switch(curEvent) {
                    case DIGIT:
                        return States.q3;
                    case LETTER:
                        return States.q4;
                    case LESS:
                    case MORE:
                    case MINUS:
                    case PLUS:
                    case OTHER:
                    default:
                        return States.ERR;
                }

            case q3:
                switch(curEvent) {
                    case MORE:
                        return States.q5;
                    case DIGIT:
                        return States.q3;
                    case LETTER:
                    case LESS:
                    case PLUS:
                    case MINUS:
                    case OTHER:
                    default:
                        return States.ERR;
                }

            case q4:
                switch(curEvent) {
                    case MORE:
                        return States.q5;
                    case LETTER:
                        return States.q4;
                    case DIGIT:
                    case LESS:
                    case PLUS:
                    case MINUS:
                    case OTHER:
                    default:
                        return States.ERR;
                }

            case q5:
                switch(curEvent) {
                    case MORE:
                    case DIGIT:
                    case LETTER:
                    case LESS:
                    case PLUS:
                    case MINUS:
                    case OTHER:
                    default:
                        return States.END;
                }

            case ERR:
            default:
                return States.ERR;
        }
    }

}
