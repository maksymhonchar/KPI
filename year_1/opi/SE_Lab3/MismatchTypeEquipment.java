
public class MismatchTypeEquipment extends Exception {
    public MismatchTypeEquipment() {
        this("Wrong type of equipment. Must take values from the list: MOUSE, KEYBOARD, MOTHERBOARD, MONITOR, WEBCAM.");
    }

    public MismatchTypeEquipment(String message) {
        super(message);
    }
}
