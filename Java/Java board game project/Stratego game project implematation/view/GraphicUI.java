package view;

import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.*;

import card.*;
import board.Board;


public class GraphicUI extends JFrame{
	Board o = new Board();
	JPanel p = new JPanel();
	private boolean iconSelected;
    private MyButton selectedButton;
    Piece k;
    
	/**
	 * Φτιαχνουμε το επιτραπέζιο με  <a> κάρτες
	 * Create a board 
	 */
    
	public GraphicUI() throws IOException {
		super("Stratego");
		setSize(800,800);
		setResizable(false);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		p.setLayout(new GridLayout(8,10));
		CardListener cl= new CardListener();
			for(int i=0; i<80 ; i++){
				MyButton b = new MyButton();
			if(i==14||i==26||i==29){
				k=new BeastRider();
				b.setIcon(o.getImageRedBeastRider()); 
				b.setName(k.getName());
				b.getRank(k);
				b.getTeam(k);
				
			}
			
			if(i==0||i==2||i==8||i==16||i==25||i==20){
				k=new TRAP();
			
				b.setIcon(o.getImageRedTrap());
				b.setName(k.getName());
				b.getRank(k);
				b.getTeam(k);
				
				}
			
			if(i==1||i==9){
				k=new SORCERES();
			
				b.setName(k.getName());
				b.setIcon(o.getImageRedSorceres());
				b.getRank(k);
				b.getTeam(k);
				
			}
			
			if(i==4){
					k=new SLAYER();
				
					b.setName(k.getName());
					b.setIcon(o.getImageRedSlayer());
					b.getRank(k);
					b.getTeam(k);
					
			}
			if(i==7||i==11||i==15||i==23){
				k=new SCOUT();
				
				b.setName(k.getName());
				b.setIcon(o.getImageRedScout());
				b.getRank(k);
				b.getTeam(k);
				
				}
				if(i==22){
					k=new MAGE();
				
					b.setName(k.getName());
					b.setIcon(o.getImageRedMage());
					b.getRank(k);
					b.getTeam(k);
					
				}
				if(i==3||i==13){
					k=new LavaBeast();
					
					b.setName(k.getName());
					b.setIcon(o.getImageRedLavaBeast());
					b.getRank(k);
					b.getTeam(k);
					
				}
				if(i==27||i==24)
				{
					k=new KNIGHT();
					
					b.setName(k.getName());
					b.setIcon(o.getImageRedKnight());
					b.getRank(k);
					b.getTeam(k);
					
				}
				if(i==5){
					k=new FLAG();
					
					b.setName(k.getName());
					b.setIcon(o.getImageRedflag());
					b.getRank(k);
					b.getTeam(k);
					
			}
				
				 if(i==18||i==28){
					k=new ELF();
					
					b.setName(k.getName()); 
					b.setIcon(o.getImageRedElf());
					b.getRank(k);
					b.getTeam(k);
					
				}
				if(i==12){
					k=new DRAGON();
				
					b.setName(k.getName());
					b.setIcon(o.getImageRedDragon());
					b.getRank(k);
					b.getTeam(k);
					
				}
				if(i==10||i==17||i==19||i==21||i==6){
					k=new DWARF();
					
					b.setName(k.getName());
					b.setIcon(o.getImageRedDwarf());
					b.getRank(k);
					b.getTeam(k);
					
				}
	
				if(i==54||i==56||i==69){
					k=new BlueBeastRider();
					
					b.setName(k.getName());
					b.setIcon(o.getImageBlueBeastRider());
					b.getRank(k);
					b.getTeam(k);
					
				}
				
				if(i==50||i==62||i==68||i==75||i==65||i==70){
					k=new BlueTRAP();
					
					b.setName(k.getName());
					b.setIcon(o.getImageBlueTrap());
					b.getRank(k);
					b.getTeam(k);
					
					}
				
				if(i==51||i==59){
					k=new BlueSORCERES();
					
					b.setName(k.getName());
					b.setIcon(o.getImageBlueSorceres());
					b.getRank(k);
					b.getTeam(k);
					
					}
				
				if(i==64){
					k=new BlueSLAYER();
					
					b.setName(k.getName());
					b.setIcon(o.getImageBlueSlayer());
					b.getRank(k);
					b.getTeam(k);
					
				}
				if(i==67||i==61||i==76||i==63){
					k=new BlueSCOUT();
					
					b.setName(k.getName());
					b.setIcon(o.getImageBlueScout());
					b.getRank(k);
					b.getTeam(k);
					
					}
					if(i==52){
						k=new BlueMAGE();
						
						b.setName(k.getName());
						b.setIcon(o.getImageBlueMage());
						b.getRank(k);
						b.getTeam(k);
						
					}
					if(i==66||i==57){
						k=new YETI();
						
						b.setName(k.getName());
						b.setIcon(o.getImageBlueYeti());
						b.getRank(k);
						b.getTeam(k);
						
					}
					if(i==55||i==58)
					{
						k=new BlueKNIGHT();
						
						b.setName(k.getName());
						b.setIcon(o.getImageBlueKnight());
						b.getRank(k);
						b.getTeam(k);
						
					}
					if(i==74){
						k=new BlueFLAG();
						
						b.setName(k.getName());
						b.setIcon(o.getImageBlueflag());
						b.getRank(k);
						b.getTeam(k);
						
					}
					
					 if(i==60||i==53){
						k=new BlueELF();
						
						b.setName(k.getName()); 
						b.setIcon(o.getImageBlueElf());
						b.getRank(k);
						b.getTeam(k);
						
					}
					if(i==73){
					
						k=new BlueDRAGON();
					
						b.setName(k.getName());
						b.setIcon(o.getImageBlueDragon());
						b.getRank(k);
						b.getTeam(k);
						
					}
					if(i==71||i==72||i==77||i==78||i==79){
						k=new BlueDWARF();
					
						b.setName(k.getName());
						b.setIcon(o.getImageBlueDwarf());
						b.getRank(k);
						b.getTeam(k);
						
					}
				
				
			
			
			if(i==32||i==33||i==36||i==37||i==42||i==43||i==46||i==47){
				b.setBackground(Color.YELLOW);
			}
			b.addMouseListener(cl);
			p.add(b);
			}
			
			
		add(p);
		iconSelected=false;
		setVisible(true);
	
	}
	

	private class CardListener implements MouseListener {
		int rank,x,y,bluehaswin=0,redhaswin=0;
		String team;
		int turn=0,scoutcanmove=0;
	
		
		public void mouseClicked(MouseEvent e) {
			MyButton but = ((MyButton) e.getSource());
			
			

			
				if(bluehaswin==23&&redhaswin==23){
					JOptionPane.showMessageDialog(but.getComponentAt(x, y),"Game is Tie");
					System.exit(0);
				}else if(redhaswin==23){
					JOptionPane.showMessageDialog(but.getComponentAt(x, y),"Red Team Won");
				}else if(bluehaswin==23){
					JOptionPane.showMessageDialog(but.getComponentAt(x, y),"Blue Team Won");
				}
			
			if(iconSelected  && !but.equals(selectedButton) && but.getBackground()!=Color.YELLOW
				&&(selectedButton.getName()=="RedScout"||selectedButton.getName()=="BlueScout")){
				if(but.getX()==x){
					scoutcanmove=0;
					if(but.getY()>y){
				 	for(int i=selectedButton.getY()+93;i<=but.getY();i+=93){
				 
						if(((((AbstractButton) p.getComponentAt(x, i)).getIcon()!=null)||p.getComponentAt(x, i).getBackground()==Color.YELLOW)
								&&(i!=but.getY()&&(but.team!=team||but.team==team))){
						System.out.println("there is icon before scout play again");
							scoutcanmove=1;
							iconSelected=false;
							
							turn--;
							break;
				 		}else
				 			if(((((AbstractButton) p.getComponentAt(x, i)).getIcon()==null)||p.getComponentAt(x, i).getBackground()!=Color.YELLOW)){
				 				if(i==but.getY()&&but.team!=team&&but.team!=null)
				 				scoutcanmove=0;
				 	
				 			}
						
				 			
					
					}
					}else
				 	if(but.getY()<y){
				 	for(int i=selectedButton.getY()-93;i>=but.getY();i-=93){
						 
						if(((((AbstractButton) p.getComponentAt(x, i)).getIcon()!=null)||p.getComponentAt(x, i).getBackground()==Color.YELLOW)
								&&(i!=but.getY()&&(but.team!=team||but.team==team))){
						System.out.println("there is icon before scout play again");
							scoutcanmove=1;
							iconSelected=false;
							
							turn--;
							break;
				 		}else
				 			if(((((AbstractButton) p.getComponentAt(x, i)).getIcon()==null)||p.getComponentAt(x, i).getBackground()!=Color.YELLOW)){
				 			if(i==but.getY()&&but.team!=team&&but.team!=null)
				 				scoutcanmove=0;
				 				
				 			}
					
				 			
					}
				 	}
					
				
				if((but.getName()=="RedFlag"||but.getName()=="BlueFlag")&&scoutcanmove== 0&&but.team!=team){
					
					but.setIcon(selectedButton.getIcon());
					System.out.println(selectedButton.getName()+" captured the "+" "+but.getName());
	                but.setName(selectedButton.getName());
	                but.team=team;
	                but.rank=rank;
	               
	                selectedButton.setIcon(null);
	                selectedButton.setName(null);
	                 selectedButton=but;
	                iconSelected=false;
	                JOptionPane.showMessageDialog(but.getComponentAt(x, y), but.team+" WON");
	                System.exit(0);
				}else
				
				if((but.getName()=="RedTrap"||but.getName()=="BlueTrap")&&scoutcanmove==0 && but.team!=team){
					if(but.team=="RedTeam"){
						redhaswin++;
					}else if(but.team=="BlueTeam"){
						bluehaswin++;
					}
					selectedButton.setIcon(null);
					System.out.println(selectedButton.getName()+" is Defeated by trap");
	                selectedButton.setName(null);
	                selectedButton=but;
	                iconSelected=false;
	                
				}else
					if((but.freesquare(but)||(but.rank<rank&&but.team!=team))&&scoutcanmove== 0){
						
					but.setIcon(selectedButton.getIcon());
					if(selectedButton.getName()!=null&&but.getName()!=null){
						if(selectedButton.team=="RedTeam"){
							redhaswin++;
						}else if(but.team=="BlueTeam"){
							bluehaswin++;
						}
					System.out.println(selectedButton.getName()+" Defeated"+" "+but.getName());
					}
	                but.setName(selectedButton.getName());
	                but.team=team;
	                but.rank=rank;
	                //but.setBorder(BorderFactory.createLineBorder(Color.YELLOW,5));
	               
	                selectedButton.setIcon(null);
	                selectedButton.setName(null);
	                 selectedButton=but;
	                iconSelected=false;
				}else
				if((but.freesquare(but)||(but.rank>rank&&but.team!=team))&&scoutcanmove== 0){
					
					selectedButton.setIcon(null);
					if(selectedButton.getName()!=null&&but.getName()!=null){
						if(selectedButton.team=="RedTeam"){
							bluehaswin++;
						}else if(selectedButton.team=="BlueTeam"){
							redhaswin++;
						}
					System.out.println(selectedButton.getName()+" is Defeated by "+but.getName());
					}
	                selectedButton.setName(null);
	                selectedButton=but; 
	                iconSelected=false;
				}else
				if((but.freesquare(but)||(but.rank==rank&&but.team!=team))&&scoutcanmove== 0){
					redhaswin++;
					bluehaswin++;
					but.setIcon(null);
	                selectedButton.setIcon(null);
	                if(selectedButton.getName()!=null&&but.getName()!=null){
	                System.out.println(selectedButton.getName()+" and "+but.getName()+" are both defeated");
	                }
	                but.setName(null);
	                selectedButton.setName(null);
	                 selectedButton=but;
	                iconSelected=false;
				}
				
				}else if(but.getY()==y){
					scoutcanmove=0;
						if(but.getX()>x){
					 	for(int i=selectedButton.getX()+79;i<=but.getX();i+=79){
					 		
							if(((((AbstractButton) p.getComponentAt(i, y)).getIcon()!=null)||(p.getComponentAt(i, y).getBackground()==Color.YELLOW))
								&&(i!=but.getX()&&(but.team!=team||but.team==team))){
							System.out.println("there is icon more right");
								scoutcanmove=1;
								iconSelected=false;
								turn--;
								break;
					 		}else
					 			if(((((AbstractButton) p.getComponentAt(i, y)).getIcon()==null)||p.getComponentAt(i, y).getBackground()!=Color.YELLOW)){
					 				if(i==but.getX()&&but.team!=team&&but.team!=null)
					 				scoutcanmove=0;
					 			
					 			}
					 			
					 			}
					 			
					 			
						}
					 			
						
						else
							if(but.getX()<x){
							 	for(int i=selectedButton.getX()-79;i>=but.getX();i-=79){
							 		if(((((AbstractButton) p.getComponentAt(i, y)).getIcon()!=null)||(p.getComponentAt(i, y).getBackground()==Color.YELLOW))
											&&(i!=but.getX()&&(but.team!=team||but.team==team))){
									System.out.println("there is icon more left");
										scoutcanmove=1;
										iconSelected=false;
										turn--;
										break;
							 		}else
							 			if(((((AbstractButton) p.getComponentAt(i, y)).getIcon()==null)||p.getComponentAt(i, y).getBackground()!=Color.YELLOW)){
							 				if(i==but.getX()&&(but.team!=team||but.team!=null))
							 				scoutcanmove=0;
							 				
							 			}
							 			
							 			}
							 			
							 			
								
				}
					 		
					
					if((but.getName()=="RedFlag"||but.getName()=="BlueFlag")&&scoutcanmove== 0&&but.team!=team){
						but.setIcon(selectedButton.getIcon());
						System.out.println(selectedButton.getName()+" captured the "+" "+but.getName());
		                but.setName(selectedButton.getName());
		                but.team=team;
		                but.rank=rank;
		               
		                selectedButton.setIcon(null);
		                selectedButton.setName(null);
		                 selectedButton=but;
		                iconSelected=false;
		                JOptionPane.showMessageDialog(but.getComponentAt(x, y), but.team+" WON");
		                System.exit(0);
					}else
					
					if((but.getName()=="RedTrap"||but.getName()=="BlueTrap")&&scoutcanmove== 0&&but.team!=team){
						if(but.team=="RedTeam"){
							redhaswin++;
						}else if(but.team=="BlueTeam"){
							bluehaswin++;
						}
						selectedButton.setIcon(null);
						System.out.println(selectedButton.getName()+" is Defeated by trap");
		                selectedButton.setName(null);
		                selectedButton=but;
		                iconSelected=false;
		                
					}else
						if((but.freesquare(but)||(but.rank<rank&&but.team!=team))&&scoutcanmove== 0){
							
						but.setIcon(selectedButton.getIcon());
						if(selectedButton.getName()!=null&&but.getName()!=null){
							if(selectedButton.team=="RedTeam"){
								redhaswin++;
							}else if(selectedButton.team=="BlueTeam"){
								bluehaswin++;
							}
						System.out.println(selectedButton.getName()+" Defeated"+" "+but.getName());
						}
		                but.setName(selectedButton.getName());
		                but.team=team;
		                but.rank=rank;
		               
		               
		                selectedButton.setIcon(null);
		                selectedButton.setName(null);
		                 selectedButton=but;
		                iconSelected=false;
					}else
					if((but.freesquare(but)||(but.rank>rank&&but.team!=team))&&scoutcanmove== 0){
						
						selectedButton.setIcon(null);
						if(selectedButton.getName()!=null&&but.getName()!=null){
							if(selectedButton.team=="RedTeam"){
								bluehaswin++;
							}else if(selectedButton.team=="BlueTeam"){
								redhaswin++;
							}
						System.out.println(selectedButton.getName()+" is Defeated by "+but.getName());
						}
		                selectedButton.setName(null);
		                selectedButton=but; 
		                iconSelected=false;
					}else
					if((but.freesquare(but)||(but.rank==rank&&but.team!=team))&&scoutcanmove== 0){
						redhaswin++;
						bluehaswin++;
						but.setIcon(null);
		                selectedButton.setIcon(null);
		                if(selectedButton.getName()!=null&&but.getName()!=null){
		                System.out.println(selectedButton.getName()+" and "+but.getName()+" are both defeated");
		                }
		                but.setName(null);
		                selectedButton.setName(null);
		                 selectedButton=but;
		                iconSelected=false;
					}
					}
				
					
			}else
			
				if(((but.getX()==x+79)&&(but.getY()==y)||(but.getX()==x-79)&&(but.getY()==y)||(but.getX()==x)&&(but.getY()==y+93)||(but.getX()==x)&&(but.getY()==y-93))
					&&iconSelected  && !but.equals(selectedButton) && but.getBackground()!=Color.YELLOW
					&&(but.getName()=="RedFlag"||but.getName()=="BlueFlag")&&but.team!=team){
					but.setIcon(selectedButton.getIcon());
					if(selectedButton.getName()!=null&&but.getName()!=null){
					System.out.println(selectedButton.getName()+" captured the "+" "+but.getName());
					}
	                but.setName(selectedButton.getName());
	                but.team=team;
	                but.rank=rank;
	                
	               
	                selectedButton.setIcon(null);
	                selectedButton.setName(null);
	                 selectedButton=but;
	                iconSelected=false;
	                JOptionPane.showMessageDialog(but.getComponentAt(x, y), but.team+" WON");
	                System.exit(0);
				}else
				
			if(((but.getX()==x+79)&&(but.getY()==y)||(but.getX()==x-79)&&(but.getY()==y)||(but.getX()==x)&&(but.getY()==y+93)||(but.getX()==x)&&(but.getY()==y-93))&&
				iconSelected  && !but.equals(selectedButton) && but.getBackground()!=Color.YELLOW 
				&&((but.getName()=="RedTrap"&&but.team!=team&&selectedButton.getName()!="BlueDwarf")
				||(but.getName()=="BlueTrap"&&but.team!=team&&selectedButton.getName()!="RedDwarf"))){
				if(but.team=="RedTeam"){
					redhaswin++;
				}else if(but.team=="BlueTeam"){
					bluehaswin++;
				}
				selectedButton.setIcon(null);
				System.out.println(selectedButton.getName()+" is Defeated by trap");
                selectedButton.setName(null);
                 selectedButton=but;
                iconSelected=false;
                
			}else if(((but.getX()==x+79)&&(but.getY()==y)||(but.getX()==x-79)&&(but.getY()==y)||(but.getX()==x)&&(but.getY()==y+93)||(but.getX()==x)&&(but.getY()==y-93))&&
					iconSelected  && !but.equals(selectedButton) && but.getBackground()!=Color.YELLOW ){
               if((but.rank<rank&&but.team!=team) || but.freesquare(but) 
                   	||(selectedButton.getName()=="RedSlayer" && but.getName()=="BlueDragon")
                	||(selectedButton.getName()=="BlueSlayer" && but.getName()=="RedDragon")){// move(swap) buttons
            	   
            	   but.setIcon(selectedButton.getIcon());
            	if(selectedButton.getName()!=null&&but.getName()!=null){
            		if(selectedButton.team=="RedTeam"){
						redhaswin++;
					}else if(selectedButton.team=="BlueTeam"){
						bluehaswin++;
					}
            	System.out.println(selectedButton.getName()+" Defeated"+" "+but.getName());
            	}
                but.setName(selectedButton.getName());
                but.team=team;
                but.rank=rank;
                selectedButton.setIcon(null);
                selectedButton.setName(null);
                 selectedButton=but;
                iconSelected=false;
               }else
               if((but.rank>rank&&but.team!=team)){
            	   selectedButton.setIcon(null);
            	   if(selectedButton.getName()!=null&&but.getName()!=null){
            		   if(selectedButton.team=="RedTeam"){
   						bluehaswin++;
   					}else if(selectedButton.team=="BlueTeam"){
   						redhaswin++;
   					}
            	   System.out.println(selectedButton.getName()+" is Defeated by "+but.getName());
            	   }
	                selectedButton.setName(null);
	                selectedButton=but;
	                iconSelected=false;
               }else
               if((but.rank==rank&&but.team!=team)){
            	   redhaswin++;
            	   bluehaswin++;
					but.setIcon(null);
	                selectedButton.setIcon(null);
	                if(selectedButton.getName()!=null&&but.getName()!=null){
	                System.out.println(selectedButton.getName()+" and "+but.getName()+" are both defeated");
	                }
	                but.setName(null);
	                selectedButton.setName(null);
	                 selectedButton=but;
	                iconSelected=false;
				}else{
					System.out.println("Invalid move play again");
					turn--;
					iconSelected=false;
				}
            }else if(!iconSelected && but.getName()!=null && (but.getName()!="RedTrap"
            		||but.getName()!="BlueTrap"||but.getName()!="RedFlag"
            		||but.getName()!="BlueFlag")){//select the icon
            
            if(turn%2==0&&but.team=="RedTeam"&&but.getName()!="RedTrap"&&but.getName()!="RedFlag"){
            	System.out.println("Red Team Plays");
            	iconSelected=true; 
                x=but.getX();
                y=but.getY();
                selectedButton=but;
                rank=but.rank;
                team=but.team;
                System.out.println(selectedButton.getName()+" "+rank +" "+ team );
                System.out.println(x+" "+y);
                turn++;
            	
               }else
          
            	   if(turn%2==1&&but.team=="BlueTeam"&&but.getName()!="BlueTrap"&&but.getName()!="BlueFlag"){
            		   System.out.println("Blue Team Plays");
                   	iconSelected=true; 
                       x=but.getX();
                       y=but.getY();
                       selectedButton=but;
                       rank=but.rank;
                       team=but.team;
                       System.out.println(selectedButton.getName()+" "+rank +" "+ team );
                       System.out.println(x+" "+y);
                       turn++;
            	   }
               
            } else{ 
                if(iconSelected){
                    System.out.println("Invalid Box");
                }else{
                    System.out.println("Not selected");
                }
            }
           
        }

		

		@Override
		public void mousePressed(MouseEvent e) {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void mouseReleased(MouseEvent e) {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void mouseEntered(MouseEvent e) {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void mouseExited(MouseEvent e) {
			// TODO Auto-generated method stub
			
		}

			
		}

		private class MyButton extends JButton{
			private int rank;
			private String team;
			
			public void getRank(Piece e){
				rank = e.getRank();
			}

			
			public boolean freesquare(MyButton k){
			
				if(k.getIcon() == null){
					return true;
				}else
					return false;
			}
			
			public String getTeam(Object e){
				if(e instanceof RedFighters){
					team="RedTeam";
				}else if(e instanceof BlueFighters){
					team="BlueTeam";
				}
				return team;
			}
			
		}
}
			

		
	
	 
