package view;

import java.awt.Color;
import java.awt.GridLayout;
import java.util.Random;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JFrame;

import board.Board;


public class GraphicUI extends JFrame{
	Board o = new Board();
	JPanel p = new JPanel();
	

	/**
	 * Φτιαχνουμε το επιτραπέζιο με  τις κάρτες
	 * Create a board 
	 */
	public GraphicUI(){
		super("Stratego");
		setSize(800,800);
		setResizable(false);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		p.setLayout(new GridLayout(8,10));
		
			for(int i=0; i<80 ; i++){
			JButton b = new JButton("("+i+")");
	
			if(i==14||i==26||i==29){
				b.setIcon(o.getImageRedBeastRider());
			}
			
			if(i==0||i==2||i==8||i==16||i==25||i==20){
					b.setIcon(o.getImageRedTrap());
				}
			
			if(i==1||i==9){
				
					b.setIcon(o.getImageRedSorceres());
					
				}
			
			if(i==4){
				
					b.setIcon(o.getImageRedSlayer());
				
			}
			if(i==7||i==11||i==15||i==23){
					b.setIcon(o.getImageRedScout());	
				
				}
				if(i==22){
					b.setIcon(o.getImageRedMage());
				
				}
				if(i==3||i==13){
					b.setIcon(o.getImageRedLavaBeast());
				}
				if(i==27||i==24)
				{
					b.setIcon(o.getImageRedKnight());
				
				}
				if(i==5){
					b.setIcon(o.getImageRedflag());
			}
				
				 if(i==18||i==28){
					b.setIcon(o.getImageRedElf());
				
				}
				if(i==12){
				
					b.setIcon(o.getImageRedDragon());
						
				}
				if(i==10||i==17||i==19||i==21||i==6){
					b.setIcon(o.getImageRedDwarf());
						
				
				}
	
				if(i==54||i==56||i==69){
					b.setIcon(o.getImageBlueBeastRider());
				}
				
				if(i==50||i==62||i==68||i==76||i==65||i==70){
						b.setIcon(o.getImageBlueTrap());
					}
				
				if(i==51||i==59){
					
						b.setIcon(o.getImageBlueSorceres());
						
					}
				
				if(i==64){
					
						b.setIcon(o.getImageBlueSlayer());
					
				}
				if(i==67||i==61||i==75||i==63){
						b.setIcon(o.getImageBlueScout());	
					
					}
					if(i==52){
						b.setIcon(o.getImageBlueMage());
					
					}
					if(i==66||i==57){
						b.setIcon(o.getImageBlueYeti());
					}
					if(i==55||i==58)
					{
						b.setIcon(o.getImageBlueKnight());
					
					}
					if(i==74){
						b.setIcon(o.getImageBlueflag());
					}
					
					 if(i==60||i==53){
						b.setIcon(o.getImageBlueElf());
					
					}
					if(i==73){
					
						b.setIcon(o.getImageBlueDragon());
							
					}
					if(i==71||i==72||i==77||i==78||i==79){
						b.setIcon(o.getImageBlueDwarf());
							
					
					}
				
				
			
			
			if(i==32||i==33||i==36||i==37||i==42||i==43||i==46||i==47){
				b.setBackground(Color.YELLOW);
			}
			p.add(b);
			}
			
			
		add(p);
		setVisible(true);
	
	}
	

	
	
	 }
