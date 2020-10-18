<html>
<head>
	<title>DS PROJECT</title>
<style type="text/css">
table, td, th {  
  border: 1px solid #ddd;
  text-align: left;
}

table {
  border-collapse: collapse;
  width: 100%;
}

th, td {
  padding: 15px;
  font-size:25px;
}
body {
  background-color: lightblue;
}

h1 {
  color: white;
  text-align: center;
  font-size:60px;
}

b {
  color: white;
  text-align: justify;
  font-size:50px;

div {
  border: 1px solid black;
  background-color: lightblue;
  padding-top: 50px;
  padding-right: 30px;
  padding-bottom: 50px;
  padding-left: 80px;
}
</style>
</head>
<body>
	
	<h1>Phone Book</h1>
	<div>
    <table>
    <b>Contact List: </b>
    <tr>
    <th>Sr.No</th>
    <th>Name</th>
    <th>Email Address</th>
    <th>Address</th>
    <th>Mobile Number </th>
    
    </tr>
    <?php

    $myfile = fopen("Contactlist1.txt","r") or die("Unable to open file!");
    while(!feof($myfile))
    {
        $bat1 = fgets($myfile);
        $bat2 = explode(" ", $bat1);
        print "<tr>";
        print "<td>$bat2[0]</td>";
        print "<td>$bat2[1]</td>";
        print "<td>$bat2[2]</td>";
        print "<td>$bat2[3]</td>";
        print "<td>$bat2[4]</td>";
        print "</tr>";
        error_reporting(0);
    }
      fclose($myfile);
    ?>
    </table>
	</div>


	
</body>
</html>