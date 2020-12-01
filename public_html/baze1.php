<?php
$user='student';
$pw='pass.mysql';
$dbname='lalic';
try{
    $db=new PDO('mysql:host=rp2.studenti.math.hr;dbname='.$dbname.';charset=utf8',$user,$pw);
}catch(PDOException $e){
    echo $e;
}
$st=$db->query('SELECT * FROM Studenti');
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Baze1</title>
</head>
<body>
    <table>
        <tr><th>JMBAG</th><th>Ime</th><th>Prezime</th><th>Ocjena</th></tr>

		<?php 
			// Protrči po svim dohvaćenim studentima iz tablice.
			foreach( $st->fetchAll() as $row )
				echo '<tr>' .
				     '<td>' . $row[ 'JMBAG' ] . '</td>' .
				     '<td>' . $row[ 'Ime' ] . '</td>' .
				     '<td>' . $row[ 'Prezime' ] . '</td>' .
				     '<td>' . $row[ 'Ocjena' ] . '</td>' .
				     '</tr>';
		?>
    </table>
</body>
</html>