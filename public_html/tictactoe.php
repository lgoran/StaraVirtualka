<?php
function provjeri_pobjedu($kucice,$slovo)
{
    if($kucice[0]==$slovo && $kucice[1]==$slovo && $kucice[2]==$slovo)
        return TRUE;
    else if($kucice[3]==$slovo && $kucice[4]==$slovo && $kucice[5]==$slovo)
        return TRUE;
    else if($kucice[6]==$slovo && $kucice[7]==$slovo && $kucice[8]==$slovo)
        return TRUE;

    else if($kucice[0]==$slovo && $kucice[3]==$slovo && $kucice[6]==$slovo)
        return TRUE;
    else if($kucice[1]==$slovo && $kucice[4]==$slovo && $kucice[7]==$slovo)
        return TRUE;
    else if($kucice[2]==$slovo && $kucice[5]==$slovo && $kucice[8]==$slovo)
        return TRUE;

    else if($kucice[0]==$slovo && $kucice[4]==$slovo && $kucice[8]==$slovo)
        return TRUE;
    else if($kucice[2]==$slovo && $kucice[4]==$slovo && $kucice[6]==$slovo)
        return TRUE;
    else return FALSE;
}
$kucice="?????????";
$potez=0;
if(isset($_POST["restart"]))
{
    setcookie("kucice",$kucice,1);
    setcookie("potez",$potez,1);
}
else
{
    if(isset($_COOKIE["kucice"]))
        $kucice=$_COOKIE["kucice"];
    if(isset($_COOKIE["potez"]))
        $potez=(int)$_COOKIE["potez"] % 2;
    for ($i=1; $i <= 9; $i++) { 
        $pom = "b" . $i;
        if(isset($_POST[$pom]) && $kucice[$i-1]=="?")
        {
            $ind=$i - 1;
            if($potez==0)
                $slovo='O';
            else
                $slovo='X';
            $kucice[$ind]=$slovo;
            $potez++;
        }
        unset($_POST[$pom]);
    }
}
setcookie("kucice",$kucice,time()+60);
setcookie("potez",$potez,time()+60);
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Krizic Kruzic</title>
</head>
<body>

    <form action="tictactoe.php" method="POST">
    <button type="submit" name="b1"><?php echo $kucice[0] ?></button>
    <button type="submit" name="b2"><?php echo $kucice[1] ?></button>
    <button type="submit" name="b3"><?php echo $kucice[2] ?></button>
    <br><br>
    <button type="submit" name="b4"><?php echo $kucice[3] ?></button>
    <button type="submit" name="b5"><?php echo $kucice[4] ?></button>
    <button type="submit" name="b6"><?php echo $kucice[5] ?></button>
    <br><br>
    <button type="submit" name="b7"><?php echo $kucice[6] ?></button>
    <button type="submit" name="b8"><?php echo $kucice[7] ?></button>
    <button type="submit" name="b9"><?php echo $kucice[8] ?></button>
    <br><br>
    <button type="submit" name="restart">Restartaj Igru</button>
    </form>
    <br>
    <h1><?php if(isset($slovo) && provjeri_pobjedu($kucice,$slovo)) echo "Pobjeda igrac " . $slovo; ?> </h1>
    
    
</body>
</html>