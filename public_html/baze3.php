<?php
$user='student';
$pw='pass.mysql';
$dbname='lalic';
$db=new PDO('mysql:host=rp2.studenti.math.hr;dbname='.$dbname.';charset=utf8',$user,$pw);
$db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
$db->setAttribute(PDO::ATTR_EMULATE_PREPARES, false);
if(isset($_POST['user']) && $_POST['user']!="" && isset($_POST['pw']) && $_POST['pw']!="")
{
	$pw=$_POST['pw'];
	$user=$_POST['user'];
	$hash=password_hash($pw,PASSWORD_DEFAULT);
	if($_POST['submit']=="Login")
	{
		try{
			$st = $db->prepare( 'SELECT Password FROM Korisnici WHERE Username=:username' );
			$st->execute( array( 'username' => $user ) );
		}catch(PDOException $e){
			echo $e;
		}
		foreach( $st->fetchAll() as $row )
		{
			if( password_verify( $pw, $row['Password'] ) )
			{
				echo "Uspijesno logiranje";
			}
		}
	}
	else
	{
		$flag=0;
		try{
			$st = $db->prepare( 'SELECT Password FROM Korisnici WHERE Username=:username' );
			$st->execute( array( 'username' => $user ) );
		}catch(PDOException $e){
			echo $e;
		}
		if($st->rowCount()>0)
		{
			echo "Postoji Username";
		}
		else
		{
			try{
				$st = $db->prepare( 'INSERT INTO Korisnici (Username, Password) VALUES (:username, :hash)' );
				$st->execute( array( 'username' => $user, 'hash' => $hash ) );
			}catch(PDOException $e){
				echo $e;
			}
			echo "Dodani ste!";
		}
		
	}
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Baze3</title>
</head>
<body>
<form action="baze3.php" method="POST">
	Username:<input type="text" name="user">
	Password:<input type="password" name="pw">
	<br/>
	<input type="submit" name="submit" value="Login">
	<input type="submit" name="submit" value="Create">
</form>
</body>
</html>