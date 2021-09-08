package trapoula;

import java.util.ArrayList;
import card.ImmovablePiece;
import card.MoveablePiece;
import card.BeastRider;
import card.DRAGON;
import card.DWARF;
import card.ELF;
import card.FLAG;
import card.KNIGHT;
import card.LavaBeast;
import card.MAGE;
import card.Piece;
import card.SCOUT;
import card.SLAYER;
import card.SORCERES;
import card.TRAP;
import card.YETI;


public class trapoula {
private ArrayList<Piece> cards;
	

/**Constructor.
 * 
 * <b>Postcondition</b>Creates a new trapoula with a new card ArrayList.
 *
 */
public trapoula()
{
    cards = new ArrayList<Piece>();
}
/**
 * <b>Transformer:</b> Initializes the 30 cards.
 * <b>Postcondition:</b> The cards have been initialised.
 */
public void init_Cards(){

}

/**
 * <b>Observer:</b> Adds a card to the list.
 * <b>Postcondition:</b> A card has been added to the list.
 * @param i
 */
public void addCard(Piece i){
    this.cards.add(i);
}

public String get(int i){
    return cards.get(i).toString();
}


/**
 * <b>Transformer:</b> Removes a card from the list.
 * <b>Postcondition:</b> A card has been removed from the list.
 * @param i
 */
public void removeCard(Piece i){
    this.cards.remove(i);
}


/**
 * <b>Transformer:</b> Returns the size of a list.
 * <Postcondition:</b> The size of the list has been returned.
 * @return size of the list
 */
public int size(){
    return cards.size();
}


/**
 * <b>Accessor:</b> returns the card in position 'index'
 * <b>Postcondition:</b> the card in position 'index' has been returned
 * @return the card in position 'index'
 */
public Piece getCard(int index){
    return cards.get(index);
}
/**
* <b>Transformer:</b> Clears an ArrayList 
 * <b>Postcondition:</b> An ArrayList is cleared.
 */
public void clearAll(){
    this.cards.clear();
}    
/**
 * <b>Accessor:</b> returns all the cards
 * <b>Postcondition:</b> all the cards has been returned
 * @return all the cards
 */
public ArrayList<Piece> getCards(){
    return this.cards;
}

}

