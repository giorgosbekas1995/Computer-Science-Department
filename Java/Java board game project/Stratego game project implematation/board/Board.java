package board;

import java.awt.Image;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;

import view.GraphicUI;

public class Board {

	public Board(){}

	
	public ImageIcon getImageBlue() { //image for blue hiden
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("blueHidden.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	public ImageIcon getImageBlueBeastRider() { //image for blue 
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("beastRiderB.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
		}
		
		

	
	public ImageIcon getImageBlueDragon() { //image for blue 
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("dragonB.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	public ImageIcon getImageBlueDwarf() { //image for blue 
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("dwarfB.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	public ImageIcon getImageBlueElf() { //image for blue
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("elfB.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	public ImageIcon getImageBlueflag() { //image for blue 
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("flagB.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	public ImageIcon getImageBlueKnight() { //image for blue 
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("knightB.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	public ImageIcon getImageBlueMage() { //image for blue
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("mageB.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	public ImageIcon getImageBlueScout() { //image for blue 
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("scoutB.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	public ImageIcon getImageBlueSlayer() { //image for blue 
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("slayerB.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	public ImageIcon getImageBlueSorceres() { //image for blue 
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("sorceressB.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	public ImageIcon getImageBlueTrap() { //image for blue
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("trapB.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	public ImageIcon getImageBlueYeti() { //image for blue
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("yeti.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	//-----------------------------------------------------------------------------------------//
	
	public ImageIcon getImageRed() { //image for redhiden
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("redHidden.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	
	public ImageIcon getImageRedBeastRider() { //image for red 
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("beastRiderR.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	public ImageIcon getImageRedDragon() { //image for red 
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("dragonR.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	public ImageIcon getImageRedDwarf() { //image for red 
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("dwarfR.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	public ImageIcon getImageRedElf() { //image for red
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("elfR.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	public ImageIcon getImageRedflag() { //image for red
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("flagR.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	public ImageIcon getImageRedKnight() { //image for red
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("knightR.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	public ImageIcon getImageRedMage() { //image for red
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("mageR.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	public ImageIcon getImageRedScout() { //image for red 
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("scoutR.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	public ImageIcon getImageRedSlayer() { //image for red
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("slayerR.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	public ImageIcon getImageRedSorceres() { //image for red
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("sorceressR.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	public ImageIcon getImageRedTrap() { //image for red
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("trapR.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
	
	public ImageIcon getImageRedLavaBeast() { //image for red
        try {
            return new ImageIcon(ImageIO.read(getClass().getResource("lavaBeast.png")).
                    getScaledInstance(100, 80, Image.SCALE_SMOOTH)); //image
        } catch (IOException ex) {
            Logger.getLogger(GraphicUI.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
}
