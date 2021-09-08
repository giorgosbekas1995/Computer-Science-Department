/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import db.UserDB;
import model.User;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author Giorgaras13
 */
@WebServlet(name ="Edit", urlPatterns = {"/edit"})
public class EditUser extends HttpServlet {
User a;
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
            throws ServletException, IOException, Exception {
        response.setContentType("text/html;charset=UTF-8");
        
            String username = request.getParameter("Username");
            String email = request.getParameter("Email");
            String pass = request.getParameter("Password");
            String conpass = request.getParameter("ConfirmPassword");
            String name = request.getParameter("FirstName");
            String lastname = request.getParameter("Lastname");
            String job = request.getParameter("ocupation");
            String address = request.getParameter("Address");
            String birth = request.getParameter("Birth");
            String gender = request.getParameter("Gender");
            String country = request.getParameter("Country");
            String city = request.getParameter("City");
            String interests = request.getParameter("Interests");
            String info = request.getParameter("MoreInfo");
            
            
           a= new User(username,email,pass,name,lastname,birth,job,country,city,address,interests,info,gender);
        
        try (PrintWriter out = response.getWriter()) {
          if(a.checkFields1()!=0&&a.getUserName().length()>=8&&(a.getPassword().length()>=6 && a.getPassword().length()<=10
              && a.getPassword().equals(conpass))&&(a.getFirstName().length()>=3 && a.getFirstName().length()<=20)
            &&(a.getLastName().length()>=4 && a.getLastName().length()<=20)&&(a.getTown().length()>=2 && a.getTown().length()<=50)){
             for(int i=0; i < UserDB.getUsers().size(); i++){
            if(UserDB.getUsers().get(i).getUserName().equals(username)){
               UserDB.updateUser(a);
              out.println(UserDB.getUsers());
                break;
            }
             } 
          }else {out.println("Missing Fields");}
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
    } catch (Exception ex) {
        Logger.getLogger(EditUser.class.getName()).log(Level.SEVERE, null, ex);
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
    } catch (Exception ex) {
        Logger.getLogger(EditUser.class.getName()).log(Level.SEVERE, null, ex);
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