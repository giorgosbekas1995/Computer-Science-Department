package player;

import card.Piece;
import trapoula.trapoula;
import player.team;

public class Player {
	 private String name;
     private team team;
     private trapoula cards;
     private int ID;
     private boolean hasPlayed;
     
     
     
     /**
 	 * <b>constructor</b>: Constructs a new Player with the given
 	 * parameter name  team  and ID.<br />
 	 * <b>postcondition</b>: Creates and initializes a player with the given
 	 * name,team and ID.Also initializes some variables
 	 * @param name is the name of the player.
 	 * @param team is the team of the player
          * @param ID is the ID of the player
 	 */
         public Player(String name, team team,int ID) {
                 
                 this.name = name;
                 this.team = team;
                 this.cards=new trapoula();
                 this.setHasPlayed(false);
                 
                 this.ID=ID;
         }

     
         /**
     	 * <b>accessor(selector)</b>: Returns the ID of a player. <br />
      	 * <b>postcondition</b>: Returns the ID of the player. 
     	 * @return the ID of the player (int)
     	 */
             public int getID() {
                     return ID;
             }
             /**
     	 * <b>transformer(mutative)</b>: It sets the ID of a plater <br />
     	 * <b>postcondition</b>:the ID of the player is changed to id  
     	 * @param id the new ID of the player
     	 */
             public void setID(int id) {
                     this.ID = id;
             }

             /**
     	 * <b>accessor(selector)</b>:Returns the name of the player <br />
     	 * 
     	 * <p><b>Postcondition:</b> returns the name of the player </p>
     	 *
     	 * @return the name of the player
     	 */
             public String getName() {
                     return name;
             }
             	
     	/**
     	 * <b>transformer(mutative)</b>: sets the name of the player to newName <br />
     	 * <p><b>Postcondition:</b> the name of this player is changed to newName</p>
     	 *
     	 * @param newName the new name of the player
              * 
       	 */ 
             public void setName(String newName) {
                     this.name = newName;
             }
             /**
     	 * <b>accessor(selector)</b>:Returns the team of the player <br />
     	 * 
     	 * <p><b>Postcondition:</b> returns the team of the player </p>
     	 *
     	 * @return the the team of the player
     	 */
             public team getTeam() {
                 return team;
         }
             
             /**
         	 * <b>transformer(mutative)</b>: sets the team of the player to newTeam <br />
         	 * <p><b>Postcondition:</b> the team of this player is changed to newTeam</p>
         	 *
                  * 
                  * 
                  * @param team 
                  */ 
                 public void setTeam(team team) {
                         this.team = team;
                 }
                   
                 
                 
                 /**
             	 * <b>transformer(mutative)</b>: brings back a Card to players cards  <br />
             	 * <p><b>Postcondition:</b>  a card added to players cards</p>
             	 *
             	 * @param c the card that will be added to players Collection
                      * 
               	 */ 
                     public void addCards(Piece c){
                         this.cards.addCard(c);
                     }
                     
                     /**
                  	 * <b>transformer(mutative)</b>: delete a Card to players cards  <br />
                  	 * <p><b>Postcondition:</b>  a card deleted to players cards</p>
                  	 *
                  	 * @param c the card that will be deleted 
                           * 
                    	 */ 
                          public void removeCards(Piece c){
                              this.cards.removeCard(c);
                          }


					public boolean HasPlayed() {
						return hasPlayed;
					}


					public void setHasPlayed(boolean hasPlayed) {
						this.hasPlayed = hasPlayed;
					}
}
