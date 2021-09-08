package card;

public class MoveablePiece implements Piece {
	
	private String name;
	private int rank;
	private int avaliable;


	/**
	 *  <b>Postcondition:</b>create new card with 'name' name 'rank' rank 'avaliable' avaliable
	 *  
	 * @param name
	 * @param rank
	 * @param avaliable
	 */
	MoveablePiece(String name,int rank,int avaliable){
		this.name=name;
		this.rank=rank;
		this.avaliable=avaliable;
	}


	@Override
	/**
	 * <b>Accessor:</b> returns the card's rank
	 * <b>Postcondition:</b> card's rank has been returned
	 * @return rank
	 */
	public int getRank() {
		return rank;
	}
	@Override
	/**
	 * <b>Transformer:</b> sets the card's rank
	 * <b>Postcondition:</b> the card's rank has been set
	 * @param rank
	 */
	public void setRank(int rank) {
		this.rank = rank;
		
	}
	@Override
	/**
	 * <b>Accessor:</b> returns the card's avaliable
	 * <b>Postcondition:</b> card's avaliable has been returned 
	 * @return avaliable
	 */
	public int getAvaliable() {
		return avaliable;
	}
	@Override
	/**
	 * <b>Transformer:</b> sets the card's avaliable
	 * <b>Postcondition:</b> the card's avaliable has been set 
	 * @param avaliable
	 */
	public void setAvaliable(int avaliable) {
		this.avaliable=avaliable;
		
	}
	@Override
	/**
	 * <b>Accessor:</b> returns the card's name
	 * <b>Postcondition:</b> card's name has been returned 
	 * @return name
	 */
	public String getName() {
		
		return name;
	}
	@Override
	/**
	  * <b>Transformer:</b> sets the card's name
	 * <b>Postcondition:</b> the card's name has been set 
	 * @param name
	 */
	public void setName(String name) {
		this.name = name;
		
	}
	
	
	 /**
     * Returns the string representation of a card
     * <p><b>Postcondition:</b> The string representation of a card is returned</p>
     * @return The string representation of a card 
     */
	public String toString(){
		return getName() + " " + getRank() + " " + getAvaliable();
	}
	
}
