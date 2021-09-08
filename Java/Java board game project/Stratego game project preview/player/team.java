package player;

public class team {
private String name;


/**Constructor.
 * 
 * <b>Postcondition</b>Creates a new Team with 'name' name.
 *
 * @param name
 */
public team(String name) {
            
            this.name = name;
           
    }



/**
 * <b>accessor(selector)</b>:Returns the name of the team <br />
 * 
 * <p><b>Postcondition:</b> returns the name of the team </p>
 *
 * @return the the name of the team
 */
public String getName() {
            return name;
    }



/**
 * <b>transformer(mutative)</b>: sets the name of the team to newName <br />
 * <p><b>Postcondition:</b> the name of this team is changed to newName</p>
 *
 * @param newName the new name of the team
 * 
 */ 
public void setName(String newName) {
            this.name = newName;
    }

}
