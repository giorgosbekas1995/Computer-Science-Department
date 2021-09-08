/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import db.UserDB;
import model.User;
import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;


/**
 *
 * @author Giorgaras13
 */
@WebServlet(name = "Register", urlPatterns = {"/register"})
public class Register extends HttpServlet {
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
            throws ServletException, IOException {
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
         
        
        try (PrintWriter out = response.getWriter();) {
            
            UserDB.addUser(a);
     
      
       
            
            
            if(a.checkFields1()!=0&&a.getUserName().length()>=8&&(a.getPassword().length()>=6 && a.getPassword().length()<=10
              && a.getPassword().equals(conpass))&&(a.getFirstName().length()>=3 && a.getFirstName().length()<=20)
            &&(a.getLastName().length()>=4 && a.getLastName().length()<=20)&&(a.getTown().length()>=2 && a.getTown().length()<=50)){
                
            out.println("Username: " + a.getUserName() + "<br>" );
            out.println("email: " + a.getEmail() + "<br>" );
            out.println("password: " + a.getPassword() + "<br>");
            out.println("confirm pass: " + a.getPassword() + "<br>");            
            out.println("Name: " + a.getFirstName() + "<br>");
            out.println("Lastname: " + a.getLastName() + "<br>");
            out.println("birth: " + a.getBirthDate() + "<br>");
            out.println("gender: " + a.getGender() + "<br>");
            out.println("country: " + a.getCountry() + "<br>");
            out.println("city: " + a.getTown() + "<br>");
            out.println("address: " + a.getAddress() + "<br>");
            out.println("interests: " + a.getInterests() + "<br>");
            out.println("Extra info: " + a.getInfo() + "<br>");
            
            if(UserDB.checkValidUserName(a.getUserName())&&UserDB.checkValidEmail(a.getEmail())){
                UserDB.addUser(a);
            
            
                
                out.println("Succesfull Enroll");
                
            }else{
                out.println("You are already enrolled!!");
            }
            
            
            }else {out.println("Missing Fields");}
            
            
        }catch(Exception e){}
    }

    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

   
    @Override
    public String getServletInfo() {
        return "Short description";
    }

}