<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Calc</title>
</head>
<body>
<form method="post">
    <label>mass1:
        <input type="number" name="mass1"><br />
    </label>

    <label>mass2:
        <input type="number" name="mass2"><br />
    </label>
    <label>speed1:
        <input type="number" name="speed1"><br />
    </label>

    <label>speed2:
        <input type="number" name="speed2"><br />
    </label>
    <button type="submit">Calc</button>
    <p>
    <label>Out:
    <%
        out.println("   " + request.getAttribute("OutInt"));
    %>
    </label>
    </p>
</form>
</body>
</html>
