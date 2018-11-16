package labPackage;

public class DLNode {
	private String element;
	private DLNode next;
	private DLNode prev;

	public DLNode() {
		this("0", null, null);
	}

	public DLNode(String element, DLNode prev, DLNode next) {
		this.element = element;
		this.prev = prev;
		this.next = next;
	}

	public void setElement(String element) {
		this.element = element;
	}

	public void setNext(DLNode n) {
		this.next = n;
	}

	public void setPrev(DLNode p) {
		this.prev = p;
	}

	public String getElement() {
		return (this.element);
	}

	public DLNode getNext() {
		return (this.next);
	}

	public DLNode getPrev() {
		return (this.prev);
	}

	public double getAverage() {
		double averItem = 0;
		for (int i = 0; i < this.element.length(); i++) {
			averItem += (double)Character.digit(element.toCharArray()[i], 10);
		}
		averItem /= element.length();
		return (averItem);
	}
}
