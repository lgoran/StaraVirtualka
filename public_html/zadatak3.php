<?php
session_start();
function isNumber($str)
{
    return preg_match('/^[0-9]{1,20}$/',$str);
}
$suma=0;
if(isset($_SESSION['suma']))
{
    $suma=(int)$_SESSION['suma'];
}
if(isset($_POST['broj']) && isNumber($_POST['broj']))
{
    $suma+=(int)$_POST['broj'];   
}
$_SESSION['suma']=$suma;
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Zadatak3</title>
</head>
<body>
    <form action="zadatak3.php" method="POST">
    <input type="text" name="broj">
    <input type="submit" value="Pošalji broj">    
    </form>
    <p>Suma=<?php echo $_SESSION['suma'] ?></p>
</body>
</html>