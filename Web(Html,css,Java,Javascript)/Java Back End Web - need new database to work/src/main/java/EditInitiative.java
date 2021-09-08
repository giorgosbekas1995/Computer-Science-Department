/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import db.InitiativeDB;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import model.Initiative;

/**
 *
 * @author giorgos
 */
@WebServlet(name ="EditInitiative", urlPatterns = {"/editinitiative"})
public class EditInitiative extends HttpServlet {
Initiative a;
    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException, ClassNotFoundException {
        response.setContentType("text/html;charset=UTF-8");
        
       
            int id = Integer.parseInt(request.getParameter("Id"));
            String category = request.getParameter("Category");
            String title = request.getParameter("Title");
            String description = request.getParameter("Description");
            int status = Integer.parseInt(request.getParameter("Status"));
            String expire = request.getParameter("Expire");
            SimpleDateFormat sdfDate = new SimpleDateFormat("dd-MM-yyyy");
            
            
            int previousStatus = InitiativeDB.getInitiative(id).getStatus();
            a = InitiativeDB.getInitiative(id);
 
           
        try (PrintWriter out = response.getWriter()) {
            if(previousStatus==0){
                
          if(category!=null){
             a.setCategory(category);
          }
          if(title!=null){
              a.setTitle(title);
          }
          if(description!=null){
              a.setDescription(description);
          }
          if(status!=0){
              //out.println("sdasd123af");
              
              a.setStatus(status);
               
          }
          if(expire!=null){
          try {
      Date  date = sdfDate.parse(expire);
      a.setExpires(date);
    } catch (ParseException ex) {
        Logger.getLogger(CreateInitiave.class.getName()).log(Level.SEVERE, null, ex);
    }
          }
          
          
         
          a.setModified(new Date());
         InitiativeDB.updateInitiative(a);
          response.sendRedirect("user.html");
        
         
        }
    }
    }
    

    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
    try {
        processRequest(request, response);
    } catch (ClassNotFoundException ex) {
        Logger.getLogger(EditInitiative.class.getName()).log(Level.SEVERE, null, ex);
    }
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
    try {
        processRequest(request, response);
    } catch (ClassNotFoundException ex) {
        Logger.getLogger(EditInitiative.class.getName()).log(Level.SEVERE, null, ex);
    }
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>

}
