package card;

public interface Piece {

/**
* <b>Accessor:</b> returns the card's rank
* <b>Postcondition:</b> card's rank has been returned
* @return rank
*/
public int getRank();

/**
 * <b>Transformer:</b> sets the card's rank
 * <b>Postcondition:</b> the card's rank has been set
 * @param rank
 */
public void setRank(int rank);


/**
 * <b>Accessor:</b> returns the card's avaliable
 * <b>Postcondition:</b> card's avaliable has been returned 
 * @return avaliable
 */
public int getAvaliable(); 
	
/**
 * <b>Transformer:</b> sets the card's avaliable
 * <b>Postcondition:</b> the card's avaliable has been set 
 * @param avaliable
 */
public void setAvaliable(int avaliable);
	
/**
 * <b>Accessor:</b> returns the card's name
 * <b>Postcondition:</b> card's name has been returned 
 * @return name
 */
public String getName();

/**
 * <b>Transformer:</b> sets the card's name
* <b>Postcondition:</b> the card's name has been set 
* @param name
*/
public void setName(String name);
	

/**
 * Returns the string representation of a card
 * <p><b>Postcondition:</b> The string representation of a card is returned</p>
 * @return The string representation of a card 
 */
public String toString();


}



