package test;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Day3 {

  /**
   * Test input
   */
  private static String input = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";
  private static String input2 = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";
  /**
   * Reg exp to find a "mul(a,b)" pattern
   */
  private static String mulPairs = "mul\\((\\d*?),(\\d*?)\\)";
  
  /**
   * Multiplies 2 numbers
   * @param a
   * @param b
   * @return
   */
  private static int mul(int a, int b) {
	return a * b;
  }
  
  /**
   * Solution for Day 3 - part 1 problem
   * @return	Sum of successive multiplications required by the problem.
   * @throws 	FileNotFoundException
   */
  private static int solveD3P1() throws FileNotFoundException {
	
	int grandTotal = 0;
	// Extract info line by line
	Scanner scanner = new Scanner(new File("input.txt"));

	while (scanner.hasNextLine()) {
		String line = scanner.nextLine();
		// Clean some characters
		line = line.replaceAll(" ", "");
		
		// Apply regExp
		Pattern regExp = Pattern.compile(mulPairs);
		Matcher matcher = regExp.matcher(line);
		
		// For each pair found...
		while (matcher.find()) {
		  int a = Integer.parseInt(matcher.group(1));
		  int b = Integer.parseInt(matcher.group(2));
		  System.out.println(a + " * " + b + " = " + mul(a, b));
		  grandTotal += mul(a, b);
		}
	}

	scanner.close();
	return grandTotal;
  }
  
  
  /**
   * Solution for Day 3 - part 2 problem
   * @return	Sum of successive multiplications required by the problem, excluding DON'Ts
   * @throws 	FileNotFoundException
   */
  private static int solveD3P2() throws FileNotFoundException {
	
	int grandTotal = 0;
	// Extract info line by line
	Scanner scanner = new Scanner(new File("input.txt"));

	boolean process = true; 
	while (scanner.hasNextLine()) {
		String line = scanner.nextLine();
	
		// Clean some characters
		line = line.replaceAll(" ", "");
		
		String pattern = "mul\\((\\d*?),(\\d*?)\\)|do\\(\\)|don't\\(\\)";
		
		// Apply regExp
		Pattern regExp = Pattern.compile(pattern);
		Matcher matcher = regExp.matcher(line);
		
		
		// For each pair found...
		while (matcher.find()) {
		  String found = matcher.group(0);
		  if (found.equalsIgnoreCase("don't()")) {
			System.out.println("Found DON'T");
			process = false;
			
		  } else if (found.equalsIgnoreCase("do()")) {
			System.out.println("Found DO");
			process = true;
		  } 
		  
		  if (found.startsWith("mul")) {
			int a = Integer.parseInt(matcher.group(1));
			int b = Integer.parseInt(matcher.group(2));
			if (process) {
			  System.out.println("Use mul("+a+","+b+")");
			  grandTotal += mul(a, b);
			} else {
			  System.out.println("Ignore mul("+a+","+b+")");
			}
		  }
		}
	}

	scanner.close();
	return grandTotal;
  }
  
  
  
  public static void main(String[] args) throws FileNotFoundException {
	System.out.println("Grand total D3P1 = " + Day3.solveD3P1());
	System.out.println("Grand total D3P2 = " + Day3.solveD3P2());
  }
  
  
  
}
