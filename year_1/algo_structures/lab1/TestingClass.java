package labPackage;

import java.util.Random;

public class TestingClass {
	static void asterisks() {
		System.out.println("************");
	}

	static void prSent(String sent) {
		System.out.printf("%s\n", sent);
	}

	static void prQueueInfo(Queue queueObject) {
		asterisks();
		prSent("Current queue :");
		queueObject.printQueue();
		System.out.printf("Capacity: %d\n", queueObject.getCapacity());
		System.out.printf("Size: %d\n", queueObject.size());
		asterisks();
	}

	static void prDLListInfo(DLList dequeObject) {
		asterisks();
		prSent("Current DLList :");
		dequeObject.printDLList();
		System.out.printf("Size: %d\n", dequeObject.size());
		//System.out.printf("First item: %s\n", dequeObject.first());
		//System.out.printf("Last item: %s\n", dequeObject.last());
		asterisks();
	}

	static void QueueDemo(final int size) {
		Queue myQueue = new Queue(size);
		prQueueInfo(myQueue);
		for (int i = 0; i < myQueue.getCapacity(); i++) {
			myQueue.enqueue((double) i + (double) i / 10);
			System.out.printf("Added \"%.2f\"\n", (double) i + (double) i / 10);
		}
		prSent("Trying to add element to the full queue...");
		myQueue.enqueue(16);
		prQueueInfo(myQueue);
		prSent("Deleting element from the front... ");
		myQueue.dequeue();
		prQueueInfo(myQueue);
		prSent("Deleting two elements...");
		myQueue.dequeue();
		myQueue.dequeue();
		prQueueInfo(myQueue);
		prSent("Add some more!");
		myQueue.enqueue(123);
		myQueue.enqueue(1234);
		prQueueInfo(myQueue);
		prSent("Delete it to the end!");
		while (myQueue.size() != 0)
			myQueue.dequeue();
		prQueueInfo(myQueue);
		prSent("Try to delete the element from the empty queue...");
		myQueue.dequeue();
	}

	static void DLListDemo(final int firstTest) {
		DLList myDLList = new DLList();
		prSent("start.");
		prDLListInfo(myDLList);
		prSent("Adding items to the list...");
		for (Integer i = 0; i < firstTest; i++) {
			myDLList.insertLast(i.toString());
			System.out.printf("Added \"%s\"\n", i.toString());
		}
		prDLListInfo(myDLList);
		prSent("Deleting 2 items from the start...");
		prSent("Deleting 3 items from the end...");
		myDLList.removeFirst();
		myDLList.removeFirst();
		myDLList.removeLast();
		myDLList.removeLast();
		myDLList.removeLast();
		prDLListInfo(myDLList);
		prSent("Deleting item with index 3...");
		myDLList.deleteIndex(3);
		prDLListInfo(myDLList);
		prSent("What is the element with index 10?");
		System.out.printf("This is %s\n", myDLList.getDLNode(10).getElement());
		prSent("What is the element with index 1?");
		System.out.printf("This is %s\n", myDLList.getDLNode(1).getElement());
		asterisks();
		prSent("Changing some elements...");
		prSent("Change element with index 2 to \"-9\"");
		myDLList.setDLNode(2, "-9");
		prSent("Change element with index 6 to \"-5\"");
		myDLList.setDLNode(6, "-5");
		prDLListInfo(myDLList);
		prSent("end.");
	}

	static void ThirdTaskDemo(final int testSize) {
		DLList myDLList = new DLList();
		Queue myQueue = new Queue(myDLList.size());
		Random r = new Random();
		prSent("start.");
		prSent("Adding elements to the DLList...");
		myDLList.insertLast(Integer.toString(1999));
		for (int i = 1; i < testSize; i++) {
			Integer itemToAdd = r.nextInt(100000);
			myDLList.insertLast(Integer.toString(itemToAdd));
			System.out.printf("Added \"%s\"\n", itemToAdd.toString());
		}
		prDLListInfo(myDLList);
		prSent("Deleting odd items in DLList...");
		int dllistRealSize = myDLList.size();
		for (int i = 0; i < dllistRealSize; i++) {
			DLNode curr = myDLList.getDLNode(i);
			if (curr.getElement().length() % 2 == 1) {
				myDLList.deleteIndex(i);
				i--;
			}
		}
		prDLListInfo(myDLList);
		prSent("Calculating average number from the elements in DLList...");
		for (int i = 0; i < myDLList.size(); i++) {
			myQueue.enqueue(myDLList.getDLNode(i).getAverage());
		}
		prQueueInfo(myQueue);
		prSent("end.");
	}

	public static void main(String[] args) {
		final int testSize = 10;
		// QueueDemo(testSize);
		// DLListDemo(testSize);
		ThirdTaskDemo(testSize);
	}

}