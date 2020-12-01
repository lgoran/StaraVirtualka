<?php
if(($f=file_get_contents('datoteke.txt'))===false)
{
    echo 'Ne može otvorit';
}
else
{
    $polje=explode(",",$f);
}
if(isset($_POST['ime']))
{
    $ime=$_POST['ime'];
    echo count($polje);
    $polje[count($polje)]=$ime;
    if(count($polje)>=5)
    {
        unset($polje[0]);
    }
    var_dump($polje);
    echo implode(",",$polje);
    if(file_put_contents('datoteke.txt',implode(",",$polje))===false)
     echo 'Ne moze pisati u file';
    unset($_POST['ime']);
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Rad s fileovima</title>
</head>
<body>
    <form action="datoteke.php" method="POST">
    <input type="text" name="ime">
    <input type="submit" value="Submit">
    </form>
</body>
</html>