package app.servlets;

import app.Fun.CalcSpeed;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

import static java.lang.System.out;

public class AddServlet extends HttpServlet
{
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        RequestDispatcher requestDispatcher = req.getRequestDispatcher("views/add.jsp");
        requestDispatcher.forward(req, resp);
    }
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException
    {
        CalcSpeed ob1 = new CalcSpeed(Float.parseFloat(req.getParameter("mass1")),Float.parseFloat(req.getParameter("mass2")),
                Float.parseFloat(req.getParameter("speed1")), Float.parseFloat(req.getParameter("speed2")));
        float r = ob1.Calc();
        req.setAttribute("OutInt",r);
        out.println(r);
        doGet(req, resp);
    }
}
