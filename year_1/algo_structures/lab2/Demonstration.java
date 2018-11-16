package mainpackage;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class Demonstration {

	static final int MAX_STUDENTS = 30;
	static final String csvPath = "./data.csv";

	static String[][] parseCSV(String path) {
		String[][] dataToRet = new String[MAX_STUDENTS][4];
		String csvFilePath = path;
		BufferedReader br = null;
		String line = "";
		String csvSplitBy = ",";
		int index = 0;

		try {
			br = new BufferedReader(new FileReader(csvFilePath));
			while ((line = br.readLine()) != null) {
				String[] data = line.split(csvSplitBy);
				dataToRet[index++] = data;
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (br != null) {
				try {
					br.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
		return (dataToRet);
	}

	static Student[] FillStudents() {
		Student[] studentArray = new Student[MAX_STUDENTS];
		for (int i = 0; i < MAX_STUDENTS; i++) {
			studentArray[i] = new Student();
		}
		String[][] parsedData = parseCSV(csvPath);
		for (int i = 0; i < MAX_STUDENTS; i++) {
			studentArray[i].setName(parsedData[i][0]);
			studentArray[i].setSurname(parsedData[i][1]);
			studentArray[i].setGroup(Integer.parseInt(parsedData[i][2]));
			studentArray[i].setZachetka(Integer.parseInt(parsedData[i][3]));
		}
		return (studentArray);
	}

	static void PrintStudents(Student[] studentArray) {
		System.out.println("");
		System.out.printf("-----------------------------\n%-7s %-10s %-4s %-4s\n-----------------------------\n",
				"Name", "Surname", "Group", "Zach");
		for (int i = 0; i < MAX_STUDENTS; i++) {
			System.out.printf("%-7s %-12s %-4d %-4d\n", studentArray[i].getName(), studentArray[i].getSurname(),
					studentArray[i].getGroup(), studentArray[i].getZachetka());
		}
		System.out.println("-----------------------------\n");
	}

	static int StudentsCompareFacultyGroup(Student s1, Student s2) {
		int result = Integer.valueOf(s1.getGroup()).compareTo(s2.getGroup());
		if (result == 0) {
			return Integer.valueOf(s1.getZachetka()).compareTo(s2.getZachetka());
		} else {
			return result;
		}
	}

	static void SwapStudents(Student a, Student b) {
		Student temp = new Student();
		temp.StudentCopy(a);
		a.StudentCopy(b);
		b.StudentCopy(temp);
	}

	static void InsertionSort(Student[] arr) {
		for (int i = 1; i < arr.length; i++) {
			Student elem = arr[i];
			int j = i - 1;
			while (j >= 0 && StudentsCompareFacultyGroup(arr[j], elem) > 0) {
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j + 1] = elem;
		}
	}

	static void ShellSort(Student[] arr) {
		int h = 1;
		while (h <= arr.length / 3) {
			h = h * 3 + 1;
		}
		//h=13
		while (h > 0) {
			for (int i = h; i < arr.length; i++) {
				Student temp = arr[i];
				int j = i;
				while (j > h - 1 && arr[j - h].getZachetka() >= temp.getZachetka()) {
					arr[j] = arr[j - h];
					j -= h;
				}
				arr[j] = temp;
			}
			h /= 3;
		}
	}

	static Student[][] ConvertTwoDimensionalArray(Student[] studentArray) {
		// Count how many different groups exists in studentArray.
		// We need this var for returning array initialization.
		int groupCountMax = studentArray[0].getGroup();
		for (int i = 1; i < MAX_STUDENTS; i++) {
			if (studentArray[i].getGroup() > groupCountMax) {
				groupCountMax = studentArray[i].getGroup();
			}
		}
		// Initialize returning array - that`s why we needed groupCountMax
		// integer.
		Student[][] out = new Student[groupCountMax][];
		// Fill returning array with certain students.
		for (int i = 0; i < groupCountMax; i++) {
			// How much students are in certain group.
			int studentInGroup = 0;
			for (int j = 0; j < MAX_STUDENTS; j++) {
				if (studentArray[j].getGroup() == (i + 1)) {
					studentInGroup++;
				}
			}
			out[i] = new Student[studentInGroup];
			// Paste Students into returning array.
			int indexStudentInGroup = 0;
			for (int j = 0; j < MAX_STUDENTS; j++) {
				if (studentArray[j].getGroup() == (i + 1)) {
					out[i][indexStudentInGroup++] = studentArray[j];
				}
			}
		}
		// Return sorted two-dimensional array.
		return (out);
	}

	static void PrintStudentsTwoDimensional(Student[][] toPrint) {
		System.out.println("");
		System.out.println("-----------------------------\n");
		for (int i = 0; i < toPrint.length; i++) {
			System.out.printf("GROUP %d\n", (i + 1));
			System.out.printf("%-7s %-10s %-4s\n", "Name", "Surname", "Zach");
			for (int j = 0; j < toPrint[i].length; j++) {
				System.out.printf("%-7s %-10s %-4d\n", toPrint[i][j].getName(), toPrint[i][j].getSurname(),
						toPrint[i][j].getZachetka());
			}
			System.out.println("");
		}
		System.out.println("-----------------------------\n");
	}

	static void Task1(Student[] studentArray) {
		System.out.println("Task1 - insertion sort.");
		System.out.println("Students array before sorting:");
		PrintStudents(studentArray);
		InsertionSort(studentArray);
		System.out.println("Students array, sorted by group and zachetka:");
		PrintStudents(studentArray);
	}

	static void Task2(Student[] studentArray) {
		System.out.println("Task 2 - Shell sort.");
		System.out.println("Students array before sorting:");
		Student[][] twoDimStudentArray = ConvertTwoDimensionalArray(studentArray);
		PrintStudentsTwoDimensional(twoDimStudentArray);
		// Sort each group by increasing by zachetka with Shellsort algorithm.
		for (int i = 0; i < twoDimStudentArray.length; i++) {
			ShellSort(twoDimStudentArray[i]);
		}
		System.out.println("Students array, sorted by group and zachetka");
		PrintStudentsTwoDimensional(twoDimStudentArray);

	}

	public static void main(String[] args) throws IOException {
		Student[] studentArray = FillStudents();
		// Task1(studentArray);
		Task2(studentArray);
	}
}
