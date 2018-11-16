package com.maxdev.hometask;

/**
 * Performs the quicksort algorithm to sort an array a[0..n-1] that is passed in constructor. <br />
 * Sorting algorithm sorts an array in ascending order.
 * 
 * @author MaxGonchar
 *
 */
public class QuickSorter {

	/**
	 * Array, already filled with integers, which is supposed to sort.
	 */
	private int[] arrToSort;

	/**
	 * Initialize private field [arrToSort] in QuickSorter class.
	 * @param arrToSort An array to be sorted.
	 */
	public QuickSorter(int[] arrToSort) {
		this.arrToSort = arrToSort;
	}

	/**
	 * Sort an array of integers from smallest to largest, using a quicksort algorithm. <br />
	 * <b>NOTE:</b>
	 * Algorithm can cause errors in worst case, when recursion depth is too big (>5000).
	 * In this case use method Arrays.sort(int[] a) in java.util.Arrays.
	 * 
	 * @param left The start index for the portion of the array that will be sorted.
	 * @param right The ending index for the portion of the array that will be sorted.
	 */
	public void quicksort(int left, int right) {
		if (left < right) {
			int q = this.partition(left, right);
			this.quicksort(left, q - 1);
			this.quicksort(q + 1, right);
		}
	}

	/**
	 * Partition a[p..r] into two subarrays a[p..q-1] and a[q+1..r], where p <= q <= r. <br />
	 * Select the original value of a[r] as the pivot element and partition a[p..r] around the pivot.
	 * 
	 * @param p Start index for the portion of the array.
	 * @param r Ending index for the portion of the array.
	 * @return Value of q that marks the partition - pivot element.
	 */
	private int partition(int p, int r) {
		int pivot = this.arrToSort[r];
		int i = p - 1;
		for (int j = p; j < r; j++) {
			if (this.arrToSort[j] <= pivot) {
				i++;
				swap(i, j);
			}
		}
		swap(i + 1, r);
		return i + 1;
	}

	/**
	 * Swap two elements by index i and j in array.
	 * 
	 * @param i First value to be swapped.
	 * @param j Second value to be swapped.
	 */
	private void swap(int i, int j) {
		int t = this.arrToSort[i];
		this.arrToSort[i] = this.arrToSort[j];
		this.arrToSort[j] = t;
	}

}
