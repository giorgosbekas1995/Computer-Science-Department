package turn;

import java.util.ArrayList;

import player.Player;



public class Turn {
	  private int IDplayer,players;
	  
	  
	  public Turn(){
		  setIDplayer(0);
		  setPlayers(2);
	  }
	  
	  
	  /**
	     * <b>Transformer:</b> Sets the player's turn.
	     * <b>Postcondition:</b> Player's turn has been set.
	     * @param players
	     */
	    public void setID(ArrayList <Player> players){
	    
	    }

	    /**
	     * <b>Accessor:</b> returns the player's ID whose turn is to play
	     * <b>Postcondition:</b> the player's ID whose turn is to play
	     * @return the player's ID whose turn is to play
	     */
	public int getIDplayer() {
		return IDplayer;
	}

	/**
     * <b>Accessor:</b> set the player's ID whose turn is to play
     * <b>Postcondition:</b> the player's ID has been set
     * @param 
     */
	public void setIDplayer(int player) {
		this.IDplayer = player;
	}

	
	 /**
     * <b>Accessor:</b> returns the number of player's
     * <b>Postcondition:</b> the number of players is returned
     * @return the number of players
     */
	public int getPlayers() {
		return players;
	}

	
	
	/**
     * <b>Accessor:</b> set the number of players
     * <b>Postcondition:</b> the player's ID has been set
     * @param 
     */
	public void setPlayers(int players) {
		this.players = players;
	}
}
