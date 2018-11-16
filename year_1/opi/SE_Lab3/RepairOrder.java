
public class RepairOrder {
    private Equipment equipment;
    private String producer;
    private int damages;

    public RepairOrder(Equipment eq, String prod, int dam){
        equipment = eq;
        producer = prod;
        damages = dam;
    }

    @Override
    public String toString(){
        return equipment.toString() + " " + producer + " " + damages;
    }

    public Equipment getEquipment() {
        return equipment;
    }

    public String getProducer() {
        return producer;
    }

    public int getDamages() {
        return damages;
    }
}
