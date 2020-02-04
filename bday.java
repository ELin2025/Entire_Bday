import java.util.*;
import java.io.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;
import javax.swing.JFrame;
class bday{
    public static void main(String[] args){
        try{
         File text = new File("read.txt");
         Scanner reader = new Scanner(text);
         String date = reader.nextLine();
         ArrayList<String> texts = new ArrayList<String>();
         while(reader.hasNext()){
           texts.add(reader.nextLine() + "\n");
         }
        Display panel = new Display(date, texts);
        JFrame frame = new JFrame("Display image");
        frame.getContentPane().add((Panel)panel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setUndecorated(true);
        frame.setVisible(true);
        GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice().setFullScreenWindow(frame);
        Thread.sleep(2000);

        }
        catch(Exception e){
            System.out.println(e);
            e.printStackTrace(); 
        }
    }
}