<?php
session_start();

if(!isset($_SESSION['polje']))
    $polje=["KKKKKKKKKK"];
else
    $polje=$_SESSION['polje'];
if(isset($_POST['napravi']))
{
    if(isset($_POST['radio']))
    {
        if($_POST['radio']==="dodaj")
        {
            $red=(int)$_POST['dodaj'];
            $broj=(int)$_POST['dodajtxt'];
            for ($i=0; $i < $broj; $i++) { 
                $polje[$red]=$polje[$red] . "K";
            }
        }
        else if($_POST['radio']==="makni")
        {
            $red=(int)$_POST['makni'];
            $broj=(int)$_POST['maknitxt'];
            $polje[$red]=substr( $polje[$red],0,strlen($polje[$red])-$broj);
        }
        else if($_POST['radio']==="novi")
        {
            array_push($polje,"KKKKKKKKKK");
        }
    }
}
echo '<table style="border:1px solid black">';
for($i=0;$i<count($polje);$i++)
{
    echo '<tr>';
    for ($j=0; $j < strlen($polje[$i]); $j++) { 
        echo '<td style="border:1px solid black">K</td>';
    }
    echo '</tr>';   
}
echo '</table>';
$_SESSION['polje']=$polje;
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>test</title>
</head>
<body>
    <form action="test1.php" method="post">
    <input type="radio" name="radio" value="dodaj" checked>
    Dodaj<input type="text" id="dodajtxt" name="dodajtxt">
    Red<select name="dodaj" id="dodaj">
    <?php
    for($i=1;$i<=count($polje);$i++)
    {
        echo '<option value='.($i-1).'>'.$i.'</option>';
    }
    ?>
    </select>
    <br>
    <input type="radio" name="radio" id="makni" value="makni">
    Makni<input type="text" id="maknitxt" name="maknitxt">
    Red<select name="makni" id="makni">
    <?php
    for($i=1;$i<=count($polje);$i++)
    {
        echo '<option value='.($i-1).'>'.$i.'</option>';
    }
    ?>
    </select>
    <br>
    <input type="radio" name="radio" id="novi" value="novi">Dodaj novi
    <br>
    <button type="submit" name="napravi" value="napravi">Napravi</button>
    <button type="submit" name="kraj" value="kraj">Kraj</button>
    </form>
</body>
</html>

