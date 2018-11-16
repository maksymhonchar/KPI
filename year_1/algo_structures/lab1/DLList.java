package labPackage;

public class DLList {
	private final String ERROR_CODE = "ERROR_CODE";
	private DLNode header;
	private DLNode trailer;
	private int size;

	public DLList() {
		this.header = new DLNode();
		this.trailer = new DLNode();
		this.header.setNext(this.trailer);
		this.header.setPrev(null);
		this.trailer.setPrev(this.header);
		this.trailer.setNext(null);
		this.size = 0;
	}

	public int size() {
		return (this.size);
	}

	public boolean empty() {
		return (this.size == 0);
	}

	public String first() {
		if (empty()) {
			System.out.println("DLList is empty.");
			return (ERROR_CODE);
		}
		return (this.header.getNext().getElement());
	}

	public String last() {
		if (empty()) {
			System.out.println("DLList is empty.");
			return (ERROR_CODE);
		}
		return (this.trailer.getPrev().getElement());
	}

	public void insertFirst(String element) {
		DLNode second = this.header.getNext();
		DLNode first = new DLNode(element, this.header, second);
		second.setPrev(first);
		this.header.setNext(first);
		this.size++;
	}

	public void insertLast(String element) {
		DLNode preLast = this.trailer.getPrev();
		DLNode last = new DLNode(element, preLast, this.trailer);
		preLast.setNext(last);
		this.trailer.setPrev(last);
		this.size++;
	}

	public boolean addByIndex(int index, String element) {
		if (index < 0 || index > size) {
			//System.out.println("Invalid index: " + index);
			return (false);
		} else if (index == 0)
			insertFirst(element);
		else if (index == size)
			insertLast(element);
		else {
			DLNode curr = this.header;
			for (int i = 0; i < index; i++) {
				curr = curr.getNext();
			}
			DLNode nodeToAdd = new DLNode(element, curr, curr.getNext());
			curr.setNext(nodeToAdd);
			curr.getNext().setPrev(nodeToAdd);
		}
		this.size++;
		return (true);
	}

	public String removeLast() {
		if (empty()) {
			System.out.println("DLList is empty. Nothing to delete.");
			return (ERROR_CODE);
		}
		DLNode last = this.trailer.getPrev();
		String temp = last.getElement();
		DLNode preLast = last.getPrev();
		this.trailer.setPrev(preLast);
		preLast.setNext(this.trailer);
		this.size--;
		return (temp);
	}

	public String removeFirst() {
		if (empty()) {
			System.out.println("DLList is empty. Nothing to delete.");
			return (ERROR_CODE);
		}
		DLNode first = this.header.getNext();
		String temp = first.getElement();
		DLNode second = first.getNext();
		this.header.setNext(second);
		second.setPrev(this.header);
		this.size--;
		return (temp);
	}

	public String deleteIndex(int index) {
		if (index < 0 || index >= size) {
			//System.out.println("Invalid index: " + index);
			return (ERROR_CODE);
		} else if (index == 0) {
			return (removeFirst());
		} else if (index == size - 1) {
			return (removeLast());
		}
		DLNode curr = this.header;
		for (int i = 0; i < index; i++) {
			curr = curr.getNext();
		}
		String itemToRet = curr.getNext().getElement();
		removeDLNode(curr.getNext());
		this.size--;
		return (itemToRet);
	}

	public String removeDLNode(DLNode curr) {
		String itemToRet = curr.getElement();
		curr.getPrev().setNext(curr.getNext());
		curr.getNext().setPrev(curr.getPrev());
		curr.setPrev(null);
		curr.setNext(null);
		this.size--;
		return (itemToRet);
	}

	public DLNode getDLNode(int index) {
		if (index < 0 || index >= size) {
			//System.out.println("Invalid index: " + index);
			DLNode tmp = new DLNode("null", null, null);
			return (tmp);
		}
		DLNode curr = header;
		for (int i = 0; i < index; i++) {
			curr = curr.getNext();
		}
		return (curr.getNext());
	}

	public void setDLNode(int index, String element) {
		if (index < 0 || index >= size) {
			//System.out.println("Invalid index: " + index);
			return;
		}
		DLNode curr = header;
		for (int i = 0; i < index; i++) {
			curr = curr.getNext();
		}
		curr.getNext().setElement(element);
	}

	/**
	 * Testing method.<br>
	 * Print all elements of the dllist from the HEADER to the TRAILER
	 */
	public void printDLList() {
		if (empty()) {
			System.out.println("DLList is empty. Nothing to print.");
			return;
		}
		DLNode curr = header;
		// while (tempDLNode.getNext() != null) {
		// System.out.printf("%s ", tempDLNode.getElement());
		// tempDLNode = tempDLNode.getNext();
		// }
		for (int i = 0; i < size(); i++) {
			System.out.printf("%s ", curr.getNext().getElement());
			curr = curr.getNext();
		}
		System.out.println("");
	}
}
