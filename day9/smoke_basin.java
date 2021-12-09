package l;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class Smoke_Basin {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		List<int[]> data_int = new ArrayList<int[]>();

		List<String> data = new ArrayList<String>();

		List<Integer> results = new ArrayList<Integer>();

		// int[] arr;

		File myObj = new File("Day8.txt");
		Scanner myReader;
		int counter = 0;
		try {
			myReader = new Scanner(myObj);
			while (myReader.hasNextLine()) {

				String test = myReader.nextLine();

				System.out.println("STR");
				System.out.println(test);

				int[] arr = Arrays.stream(test.substring(0, test.length() - 1).split("")).map(String::trim)
						.mapToInt(Integer::parseInt).toArray();

				System.out.println("Int");

				data_int.add(arr);

				counter++;
			}

			int c = 0;
			for (int k = 0; k < counter; k++) {
				for (int i = 0; i < data_int.get(k).length; i++) {

					int upp = k != 0 ? data_int.get(k - 1)[i] : -1;
					int down = k != counter - 1 ? data_int.get(k + 1)[i] : -1;
					int left = i != 0 ? data_int.get(k)[i - 1] : -1;
					int right = i != data_int.get(k).length - 1 ? data_int.get(k)[i + 1] : -1;

					System.out.println("Param: " + upp);
					System.out.println("Param: " + down);
					System.out.println("Param: " + left);
					System.out.println("Param: " + right);

					if (upp > data_int.get(k)[i] && down > data_int.get(k)[i] && left > data_int.get(k)[i]
							&& right > data_int.get(k)[i]) {
						results.add(data_int.get(k)[i]);

					}

				}
				System.out.println("------------");

			}

			System.out.println("RESULTS");

			Integer sum = results.stream().reduce(0, (a, b) -> a + b);

			System.out.println(sum);

		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}
