/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package db;

import model.Vote;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author papadako
 */
public class VoteDB {

    /**
     * Get all votes
     *
     * @return
     * @throws ClassNotFoundException
     */
    public static List<Vote> getAllVotes() throws ClassNotFoundException {
        List<Vote> votes = new ArrayList<>();

        try {
            Connection con = CS359DB.getConnection();
            Statement stmt = con.createStatement();

            StringBuilder insQuery = new StringBuilder();

            insQuery.append("SELECT * FROM votes;");

            stmt.execute(insQuery.toString());

            ResultSet res = stmt.getResultSet();

            while (res.next() == true) {
                Vote vote = new Vote();
                vote.setId(res.getInt("id"));
                vote.setUser(res.getString("userID"));
                vote.setDelegator(res.getString("delegatorID"));
                vote.setVote(res.getInt("vote") == 1, res.getInt("votedBy") == 1);
                vote.setInitiativeID(res.getInt("initiativeID"));
                vote.setCreated(res.getTimestamp("created"));
                vote.setModified(res.getTimestamp("updated"));
                votes.add(vote);
            }

            // Close connection
            stmt.close();
            con.close();

        } catch (SQLException ex) {
            // Log exception
            Logger.getLogger(VoteDB.class.getName()).log(Level.SEVERE, null, ex);
        }

        return votes;
    }

    /**
     * Get votes of user
     *
     * @param user
     * @return
     * @throws ClassNotFoundException
     */
    public static List<Vote> getVotes(String user) throws ClassNotFoundException {
        List<Vote> votes = new ArrayList<>();

        try {
            Connection con = CS359DB.getConnection();
            Statement stmt = con.createStatement();
            StringBuilder insQuery = new StringBuilder();

            insQuery.append("SELECT * FROM votes ")
                    .append(" WHERE ")
                    .append(" userID = ").append("'").append(user).append("';");

            stmt.execute(insQuery.toString());

            ResultSet res = stmt.getResultSet();

            while (res.next() == true) {
                Vote vote = new Vote();
                vote.setId(res.getInt("id"));
                vote.setUser(res.getString("userID"));
                vote.setDelegator(res.getString("delegatorID"));
                vote.setVote(res.getInt("vote") == 1, res.getInt("votedBy") == 1);
                vote.setInitiativeID(res.getInt("initiativeID"));
                vote.setCreated(res.getTimestamp("created"));
                vote.setModified(res.getTimestamp("updated"));
                votes.add(vote);
            }

            // Close connection
            stmt.close();
            con.close();

        } catch (SQLException ex) {
            // Log exception
            Logger.getLogger(VoteDB.class.getName()).log(Level.SEVERE, null, ex);
        }

        return votes;
    }

    /**
     * Get votes voted by
     *
     * @param status, 0 for delegators, 1 for users
     * @return
     * @throws ClassNotFoundException
     */
    public static List<Vote> getVotedBy(int status) throws ClassNotFoundException {
        List<Vote> votes = new ArrayList<>();

        try {
            Connection con = CS359DB.getConnection();
            Statement stmt = con.createStatement();
            StringBuilder insQuery = new StringBuilder();

            insQuery.append("SELECT * FROM votes ")
                    .append(" WHERE ")
                    .append(" votedBy = ").append("'").append(status).append("';");

            stmt.execute(insQuery.toString());

            ResultSet res = stmt.getResultSet();

            while (res.next() == true) {
                Vote vote = new Vote();
                vote.setId(res.getInt("id"));
                vote.setUser(res.getString("userID"));
                vote.setDelegator(res.getString("delegatorID"));
                vote.setVote(res.getInt("vote") == 1, res.getInt("votedBy") == 1);
                vote.setInitiativeID(res.getInt("initiativeID"));
                vote.setCreated(res.getTimestamp("created"));
                vote.setModified(res.getTimestamp("updated"));
                votes.add(vote);
            }

            // Close connection
            stmt.close();
            con.close();

        } catch (SQLException ex) {
            // Log exception
            Logger.getLogger(VoteDB.class.getName()).log(Level.SEVERE, null, ex);
        }

        return votes;
    }

    /**
     * Establish a database connection and add the member in the database.
     *
     * @param vote
     * @throws ClassNotFoundException
     */
    public static void addVote(Vote vote) throws ClassNotFoundException {
        // Check that we have all we need
        try {
            vote.checkFields();

        } catch (Exception ex) {
            // Log exception
            Logger.getLogger(VoteDB.class.getName()).log(Level.SEVERE, null, ex);
        }
        try {
            Connection con = CS359DB.getConnection();
            StringBuilder insQuery = new StringBuilder();

            insQuery.append("INSERT INTO ")
                    .append(" votes (userID, delegatorID, initiativeID, vote, votedBy) ")
                    .append(" VALUES (")
                    .append("'").append(vote.getUser()).append("',");
            // If there is a delegator
            if (vote.getDelegator() != null && !vote.getDelegator().trim().equals("")) {
                insQuery.append("'").append(vote.getDelegator()).append("',");
            } else {
                insQuery.append("'").append(vote.getUser()).append("',");
            }

            insQuery.append("'").append(vote.getInitiativeID()).append("',")
                    .append("'").append(vote.getVote()).append("',")
                    .append("'").append(vote.getVotedBy()).append("');");

            String generatedColumns[] = {"ID"};
            PreparedStatement stmtIns = con.prepareStatement(insQuery.toString(), generatedColumns);
            stmtIns.executeUpdate();

            // Get information magically completed from database
            ResultSet rs = stmtIns.getGeneratedKeys();
            if (rs.next()) {
                // Update values based on database
                int id = rs.getInt(1);
                vote.setId(id);
                Vote inserted = getVote(id);
                vote.setCreated(inserted.getCreated());
                vote.setModified(inserted.getModified());
            }

            System.out.println("#DB: The vote was successfully added in the database.");

            // Close connection
            stmtIns.close();

        } catch (SQLException ex) {
            // Log exception
            Logger.getLogger(VoteDB.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * Establish a database connection and get vote with specific id
     *
     * @param id
     * @return
     * @throws ClassNotFoundException
     */
    public static Vote getVote(int id) throws ClassNotFoundException {
        Vote vote = null;
        try {
            Connection con = CS359DB.getConnection();
            StringBuilder insQuery = new StringBuilder();

            insQuery.append("SELECT * FROM votes ")
                    .append(" WHERE ")
                    .append(" ID = ").append("'").append(id).append("';");

            String generatedColumns[] = {"ID"};
            PreparedStatement stmtIns = con.prepareStatement(insQuery.toString(), generatedColumns);
            stmtIns.executeUpdate();

            ResultSet res = stmtIns.getResultSet();

            if (res.next() == true) {
                vote = new Vote();
                vote.setId(res.getInt("id"));
                vote.setUser(res.getString("userID"));
                vote.setDelegator(res.getString("delegatorID"));
                vote.setVote(res.getInt("vote") == 1, res.getInt("votedBy") == 1);
                vote.setInitiativeID(res.getInt("initiativeID"));
                vote.setCreated(res.getTimestamp("created"));
                vote.setModified(res.getTimestamp("updated"));
            }

            System.out.println("#DB: The vote was successfully retrieved from the database.");

            // Close connection
            stmtIns.close();

        } catch (SQLException ex) {
            // Log exception
            Logger.getLogger(VoteDB.class.getName()).log(Level.SEVERE, null, ex);
        }
        return vote;
    }

    /**
     * Establish a database connection and get vote for initiative with id for
     * user with username
     *
     * @param name userName
     * @param initiativeID initiative id
     * @return
     * @throws ClassNotFoundException
     */
    public static Vote getVote(String userName, int initiativeID) throws ClassNotFoundException {
        Vote vote = null;
        try {
            Connection con = CS359DB.getConnection();
            StringBuilder insQuery = new StringBuilder();

            insQuery.append("SELECT * FROM votes ")
                    .append(" WHERE ")
                    .append(" INITIATIVEID = ").append("'").append(initiativeID).append("'")
                    .append(" AND USERID = ").append("'").append(userName).append("';");

            String generatedColumns[] = {"ID"};
            PreparedStatement stmtIns = con.prepareStatement(insQuery.toString(), generatedColumns);
            stmtIns.executeUpdate();

            ResultSet res = stmtIns.getResultSet();

            if (res.next() == true) {
                vote = new Vote();
                vote.setId(res.getInt("id"));
                vote.setUser(res.getString("userID"));
                vote.setDelegator(res.getString("delegatorID"));
                vote.setVote(res.getInt("vote") == 1, res.getInt("votedBy") == 1);
                vote.setInitiativeID(res.getInt("initiativeID"));
                vote.setCreated(res.getTimestamp("created"));
                vote.setModified(res.getTimestamp("updated"));
            }

            System.out.println("#DB: The vote was successfully retrieved from the database.");

            // Close connection
            stmtIns.close();

        } catch (SQLException ex) {
            // Log exception
            Logger.getLogger(VoteDB.class.getName()).log(Level.SEVERE, null, ex);
        }
        return vote;
    }

    /**
     * Updates information for specific initiative
     *
     * @param initiative
     * @throws ClassNotFoundException
     */
    public static void updateVote(Vote vote) throws ClassNotFoundException {
        // Check that we have all we need
        try {
            vote.checkFields();

        } catch (Exception ex) {
            // Log exception
            Logger.getLogger(VoteDB.class.getName()).log(Level.SEVERE, null, ex);
        }
        try {
            Connection con = CS359DB.getConnection();
            StringBuilder insQuery = new StringBuilder();

            insQuery.append("UPDATE votes ")
                    .append(" SET ")
                    .append(" VOTE = ").append("'").append(vote.getVote()).append("',")
                    .append(" VOTEDBY = ").append("'").append(vote.getVotedBy()).append("',");
            // If there is a delegator
            if (vote.getDelegator() != null && !vote.getDelegator().trim().equals("")) {
                insQuery.append(" DELEGATORID = ").append("'").append(vote.getDelegator()).append("'");
            } else {
                insQuery.append(" DELEGATORID = ").append("'").append(vote.getUser()).append("'");
            }

            insQuery.append(" WHERE ID = ").append("'").append(vote.getId()).append("';");

            PreparedStatement stmtUpdate = con.prepareStatement(insQuery.toString());

            stmtUpdate.executeUpdate();

            // Update info
            Vote updated = getVote(vote.getId());
            vote.setCreated(updated.getCreated());
            vote.setModified(updated.getModified());

            System.out.println("#DB: The vote was successfully updated in the database.");

            // Close connection
            stmtUpdate.close();

        } catch (SQLException ex) {
            // Log exception
            Logger.getLogger(VoteDB.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * Delete vote with id
     *
     * @param id
     * @throws ClassNotFoundException
     */
    public static void deleteVote(int id) throws ClassNotFoundException {

        try {
            try (Connection con = CS359DB.getConnection();
                    Statement stmt = con.createStatement()) {

                StringBuilder insQuery = new StringBuilder();

                insQuery.append("DELETE FROM votes ")
                        .append(" WHERE ")
                        .append(" id = ").append("'").append(id).append("';");

                stmt.executeUpdate(insQuery.toString());
                System.out.println("#DB: The vote was successfully deleted from the database.");

                // Close connection
                stmt.close();
                con.close();
            }

        } catch (SQLException ex) {
            // Log exception
            Logger.getLogger(VoteDB.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
