package mainpackage;

public class Student {

	private String name;
	private String surname;
	private int group;
	private int zachetka;

	public Student() {
		this.setName("NoName");
		this.setSurname("NoSurname");
		this.setGroup(0);
		this.setZachetka(0);
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getSurname() {
		return surname;
	}

	public void setSurname(String surname) {
		this.surname = surname;
	}

	public int getGroup() {
		return group;
	}

	public void setGroup(int group) {
		this.group = group;
	}

	public int getZachetka() {
		return zachetka;
	}

	public void setZachetka(int zachetka) {
		this.zachetka = zachetka;
	}

	public void StudentCopy(Student src) {
		this.setName(src.getName());
		this.setSurname(src.getSurname());
		this.setGroup(src.getGroup());
		this.setZachetka(src.getZachetka());
	}

}
