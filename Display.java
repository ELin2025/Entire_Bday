import java.io.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;
import javax.swing.JFrame;
class Display extends Panel{
    BufferedImage image;
    File photo;
    Dimension screenSize;
    String text;
    ArrayList<String> text2;
    boolean h = true;
    int count = 0;
    Thread thread;
    final int NUM_IMAGES = getFolderSize();
    public Display(String _text, ArrayList<String> _text2){
        text = _text;
        text2 = _text2;
        try{
            screenSize = Toolkit.getDefaultToolkit().getScreenSize();
            thread = new Thread(() -> {
                while (true) {
                    try{
                        Thread.sleep(5000);
                        repaint();
                    }
                    catch(Exception e){
                        System.exit(0);
                    }
                }
            });
            addMouseListener(new MouseListener() { 
            public void mouseClicked(MouseEvent e) { thread.interrupt(); }
            public void mousePressed(MouseEvent e) {} 
            public void mouseReleased(MouseEvent e) {} 
            public void mouseEntered(MouseEvent e) {} 
            public void mouseExited(MouseEvent e) {} 
            });
            Edit.resize(NUM_IMAGES);
            thread.start();
        }
        catch(Exception e){
            e.printStackTrace();
            System.out.println(e);
        
        }
    }
    public void paint(Graphics g){
        try{
            
        if(count == NUM_IMAGES){
            count = 0;
        }
        String name = "photos/" + Integer.toString(count) + ".jpg";
        photo = new File(name);
        image = ImageIO.read(photo);
        Font font = new Font("Verdana", Font.BOLD, 24);
        g.setFont(font);
        g.setColor(Color.white);
          g.drawImage( image, 0, 0, null);
          if(h){
             g.drawString(text, 100, 100);
          }
          else{
              if(text2.size() > 0){
                for( int i = 0; i< text2.size(); i++){
                    g.drawString(text2.get(i), 100, 100);
                }
              }
              else{
                  g.drawString(text,100,100);
              }
          }
          h = !h;      
          count++;
        }
        catch(Exception e){
            e.printStackTrace(); 
            System.out.println(e);
        }
    }

    private int getFolderSize() {
    int length = 0;
    File folder = new File("photos");
    File[] files = folder.listFiles();
    if (files == null || files.length == 0){
        return length;
    }
    for (File file : files) {
        length++;
    }
    return length;
    }
}
