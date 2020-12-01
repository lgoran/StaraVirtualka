<?php
$user='student';
$pw='pass.mysql';
$dbname='lalic';
$db=new PDO('mysql:host=rp2.studenti.math.hr;dbname='.$dbname.';charset=utf8',$user,$pw);
$db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
$db->setAttribute(PDO::ATTR_EMULATE_PREPARES, false);
if(isset($_POST['broj']))
{
	try{
		$st=$db->prepare('SELECT * FROM Studenti where Ocjena='.$_POST['broj'] );
		$st->execute();
	}catch(PDOException $e){
		echo $e;
	}
}

?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
	
    <title>Baze2</title>
</head>
<body>
<form action="baze2.php" method="POST">
	<input type="number" name="broj" id="broj">
	<input type="submit" value="Submit">
</form>
    <table>
        <tr><th>JMBAG</th><th>Ime</th><th>Prezime</th><th>Ocjena</th></tr>

		<?php 
			// Protrči po svim dohvaćenim studentima iz tablice.
		if(isset($_POST['broj']))
		{	
			foreach( $st->fetchAll() as $row )
				echo '<tr>' .
				     '<td>' . $row[ 'JMBAG' ] . '</td>' .
				     '<td>' . $row[ 'Ime' ] . '</td>' .
				     '<td>' . $row[ 'Prezime' ] . '</td>' .
				     '<td>' . $row[ 'Ocjena' ] . '</td>' .
				     '</tr>';
		}
		unset($_POST['broj']);
		?>
    </table>
</body>
</html>