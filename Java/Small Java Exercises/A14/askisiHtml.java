package asksi41;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;



public class askisiHtml {
	public static void main(String[] args){
		long startTime = System.nanoTime();
		BufferedReader y = null;
		String j = null,i="";
		try {
			y = new BufferedReader(new FileReader("D://name.txt"));
		} catch (FileNotFoundException e1) {                         //diavazoume to arxeio pou theloume
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		File x = new File("D:\\name.html");  //dimiourgeia html file
		
			try {
				while((j=y.readLine())!= null){
					i+=j;                         // apothikeuoume ta dedomena tou txt se ena string oso to diavazoume
				}
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			
			String s="<!DOCTYPE html>"
					+	"<html>"
					+	"<head>"
	  +	     "<meta http-equiv=content-type content=text/html;charset=utf-8 >"
					+	"<title>"
					+   "<!--name.html-->"
					+   "</title>"                   //apothikeuoume se string ta dedomena gia to html arxeio
					+   "/head"                                               
					+   "</body>"
					+   "<br />" +"&lt" + "&nbsp" + i + "&nbsp" + "&gt" 
					+   "</body>"
					+   "</html>";
			
			
				try {
					BufferedWriter in = new BufferedWriter(new FileWriter(x));//entolh pou mas dini dikaiwma na grapsoume sto html arxeio mas
					in.write(s);
					in.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
		

			long endTime = System.nanoTime();
			long timeInNanosecs = endTime - startTime;
			System.out.println(timeInNanosecs);
	}
}
