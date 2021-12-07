package l;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;

public class The_Treachery_of_Whales {

	public static void main(String[] args) {
		
		
		String data="";
		
		try {
			File myObj = new File("Day7.txt");
			Scanner myReader;
			myReader = new Scanner(myObj);
			while (myReader.hasNextLine()) {
				data = myReader.nextLine();
			  
			} 
			
			
			int[] arr = Arrays.stream(data.substring(0, data.length()-1).split(",")).map(String::trim).mapToInt(Integer::parseInt).toArray();
			
			int fuel=0;
			int position=0;
			int minFuel=1000000;
			int p=0;
			
			for(int i=0;i<arr.length;i++) {
				
				for(int k=0;k <arr.length;k++) {
					
					
			        fuel+=Math.abs(arr[i]-arr[k]);
			        
			        
					
				}
				if(minFuel!=0 && fuel< minFuel) {
					
					position=arr[i];
				}
				else if(minFuel==0){
					minFuel=fuel;
					position=arr[i];
				}
			   
				
				
				fuel=0;
				
			}
			
			System.out.println(position);
			System.out.println(Arrays.stream(arr).anyMatch(i -> i == 14));
			
			
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	      
	      
	      
	}
	        
}
