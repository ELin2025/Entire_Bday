import java.io.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;
import javax.swing.JFrame;

public class Edit{
    public static void resize(int NUM_IMAGES) throws IOException {
        BufferedImage image;
        Dimension screenSize = screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        File photo;
        for(int i = 0; i< NUM_IMAGES;i++){
            String name = "photos/" + Integer.toString(i) + ".jpg"; 
            photo = new File(name);
            image = ImageIO.read(photo);
            BufferedImage resize = new BufferedImage((int)screenSize.getWidth(),(int)screenSize.getHeight(), image.getType());
            Graphics2D g = resize.createGraphics();
            g.drawImage(image, 0, 0,(int)screenSize.getWidth(), (int)screenSize.getHeight(), null);
            g.dispose();
            ImageIO.write(resize, "jpg", photo);
        }
    }
}