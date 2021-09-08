package controller;

import java.util.ArrayList;



import player.Player;
import player.team;
import trapoula.trapoula;
import turn.Turn;



public class Controller {

	 private team RED,BLUE;
	    private Player P1,P2;
	    private ArrayList <Player> players=new ArrayList<Player>();
	    private Turn turn=new Turn();
	    private trapoula allcards = new trapoula();
	
	    
	    
	    /**
		* <b>postcondition</b>: constructs a new Controller,with new 2 players,new 
	        * instances of Turn Class ,  trapoula Class 
	        and is responsible for creating a new game and 
		* initializing it.
		*/
	public Controller(){
		RED=new team("RED");
        BLUE=new team("BLUE");
        P1=new Player("p1",RED,1);
        P2=new Player("p2",BLUE,2);
        players.add(P1);
        players.add(P2);
	}
	
	/**
	    * <b>transformer(mutative)</b>: initializes players cards in the beginning
	    * <p><b>Postcondition:</b> initializes players cards in the beginning </p>
	    */ 
	    public void init_player_cards()
	    {
	       
	    }
	    
	    
	    
	    public void PlayCards(ArrayList<Integer> MyCards)
	    {

	    }
	    
	    /**
	     * <b>accessor(selector)</b>:Returns which player has the turn <br />
	     * 
	     * <p><b>Postcondition:</b> Returns which player has the turn </p>
	     *
	     * @return which player has the turn (for example 0 if p1 has the turn )
	     */
	    public int seeTurn()
	    {
	        return turn.getIDplayer();
	    }
	    
	    /**
	     * <b>Observer</b>:Return true somoene take the flag, false otherwise
	     * <p><b>Postcondition:</b> return true if a game  has finished, false otherwise
	     * </p>
	     * @return true if a game has finished, false otherwise
	     */
	     public boolean game_has_finished()
	     {
	        
	         return false;
	     }
	     
	     /**
	      * <b>transformer(mutative)</b>: give the turn to player 
	      * <p><b>Postcondition:</b> give the turn to player </p>
	      */ 
	     public void set_Turn()
	     {
	        
	     }
}
