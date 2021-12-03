package l;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Day3 {

	public static void main(String[] args) {
		
		int NullCounter[]= {0,0,0,0,0,0,0,0,0,0,0,0};
		
		int OneCounter[]= {0,0,0,0,0,0,0,0,0,0,0,0};
		
		
		
		try {
		      File myObj = new File("proba.txt");
		      Scanner myReader = new Scanner(myObj);
		      while (myReader.hasNextLine()) {
		        char []data = myReader.nextLine().toCharArray();
		        for(int i=0; i<12;i++) {
		        	if(data[i]=='1') {
		        		OneCounter[i]++;
		        	}
		        	else {
		        		NullCounter[i]++;
		        	}
		        	
		        }
		        
		        
		        //System.out.println(data[0]);
		      }
		      myReader.close();
		      
		      //Calc Gamma
		      int gamma=0;
		      for(int i=0;i< OneCounter.length;i++) {
		    	 if(OneCounter[i]>NullCounter[i]) {
		    		 gamma+=Math.pow(2, OneCounter.length-i);
		    		 //System.out.println(Math.pow(2, OneCounter.length-i));
		    	 }
		    	 else {
		    		 gamma+=0;
		    	 }
		    	 
		      }
		      
		      int epsilon=0;
		      
		      for(int i=0;i< OneCounter.length;i++) {
			    	 if(OneCounter[i]<NullCounter[i]) {
			    		 epsilon+=Math.pow(2, OneCounter.length-i);
			    		 //System.out.println(Math.pow(2, OneCounter.length-i));
			    	 }
			    	 else {
			    		 epsilon+=0;
			    	 }
			    	 
			      }
		      
		      
		      
		      System.out.println("Gamma: ");
		      System.out.println(gamma);
		      
		      
		      System.out.println("Eplsion: ");
		      System.out.println(epsilon);
		      
		    
		     
		      System.out.println("Power Consumption:"+ epsilon*gamma);
		      
		    } catch (FileNotFoundException e) {
		      System.out.println("An error occurred.");
		      e.printStackTrace();
		    }
		

	}

}
