package labPackage;

public class Queue {
	private static final int CAPACITY = 1000;
	private int front;
	private int rear;
	private int N;
	double[] queueArr;

	public Queue() {
		queueArr = new double[CAPACITY];
		front = 0;
		rear = 0;
		N = 0;
	}

	public Queue(int inputSize) {
		queueArr = new double[inputSize];
		front = 0;
		rear = 0;
		N = 0;
	}

	public int size() {
		return (N);
	}

	public boolean empty() {
		return (N == 0);
	}

	public void enqueue(double element) {
		if (size() == queueArr.length) {
			// System.out.println("Queue is full.");
			// return;
			appendElement();
		}
		queueArr[rear] = element;
		rear = (rear + 1) % queueArr.length;
		N++;
	}

	public double dequeue() {
		if (empty()) {
			System.out.println("Queue is empty.");
			return (0);
		}
		double temp = queueArr[front];
		front = (front + 1) % queueArr.length;
		N--;
		return temp;
	}

	public void appendElement() {
		double[] queueArr_temp = new double[getCapacity() + 1];
		System.arraycopy(queueArr, front, queueArr_temp, 0, getCapacity() - front);
		System.arraycopy(queueArr, 0, queueArr_temp, getCapacity() - front, rear);
		front = 0;
		rear = getCapacity();
		queueArr = queueArr_temp;
	}

	/**
	 * Testing function <br>
	 * Print elements of the queue.
	 */

	public void printQueue() {
		if (empty()) {
			System.out.println("Queue is empty.");
			return;
		}
		for (int i = 0; i < N; i++) {
			System.out.printf("%.2f ", queueArr[(front + i) % queueArr.length]);
		}
		System.out.println("");
	}

	/**
	 * Testing function.
	 * 
	 * @return Capacity of the queue.
	 */
	public int getCapacity() {
		return (queueArr.length);
	}

}
