import java.util.*;
import java.io.*;
public class Main 
{
public static void main(String[] args)
{
//stdin
Scanner cin1 = new Scanner(System.in);
Scanner cin2 = new Scanner(new BufferedInputStream(System.in));
//使用cin2进行输入的时候可能会比cin1快一些。

//fileout
File file = new File("output.txt");  
if(!file.exists()) file.createNewFile();  
FileWriter fw = new FileWriter("output.txt", true);  
PrintWriter pw = new PrintWriter(fw);  
pw.print("China");  
pw.flush();  
pw.println("Foreign");  
pw.flush(); 
}
}

