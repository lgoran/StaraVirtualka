<?php
session_start();
function isValidNumber($str)
{
    return preg_match('/^[1-6]{1}$/',$str);
}
function dobarKucica($polje,$x)//poziciju unosimo i gledamo ima li jos jedan takav
{
    $br=0;
    $red=intdiv($x,6);
    $stupac=$x%6;
    if($stupac<3 && $red%2==0)
    {
        for ($i=0; $i < 3; $i++) { 
            if($polje[$red*6+$i]==$polje[$x])
            $br++;
            if($polje[($red+1)*6+$i]==$polje[$x])
            $br++;
        }
    }
    else if($stupac>=3 && $red%2==0)
    {
        for ($i=3; $i < 6; $i++) { 
            if($polje[$red*6+$i]==$polje[$x])
            $br++;
            if($polje[($red+1)*6+$i]==$polje[$x])
            $br++;
        }
    }
    else if($stupac<3 && $red%2==1)
    {
        for ($i=0; $i < 3; $i++) { 
            if($polje[$red*6+$i]==$polje[$x])
            $br++;
            if($polje[($red-1)*6+$i]==$polje[$x])
            $br++;
        }
    }
    else if($stupac>=3 && $red%2==1)
    {
        for ($i=3; $i < 6; $i++) { 
            if($polje[$red*6+$i]==$polje[$x])
            $br++;
            if($polje[($red-1)*6+$i]==$polje[$x])
            $br++;
        }
    }

    if($br>1)
        return FALSE;
    return TRUE;
}
function dobarRed($polje,$x)//xy 0-35
{
    $br=0;
    $stupac=$x%6;
    for ($i=0; $i < 6; $i++) { 
        if($polje[6*$i+$stupac]==$polje[$x])
        {
            $br++;
        }
    }
    if($br>1)
        return FALSE;
    return TRUE;
}
function dobarStupac($polje,$x)
{
    $br=0;
    $red=intdiv($x,6);
    for ($i=0; $i < 6; $i++) { 
        if($polje[$i+6*$red]==$polje[$x])
        {
            $br++;
        }
    }
    if($br>1)
        return FALSE;
    return TRUE;
}
function dobar($polje,$x)
{
    if(dobarKucica($polje,$x) && dobarRed($polje,$x) && dobarStupac($polje,$x))
        return TRUE;
    return FALSE;
}
if(isset($_POST['ime']))
{
    $_SESSION['username']=$_POST['ime'];
}
if(isset($_SESSION['username']))
{
    $username=$_SESSION['username'];
}
if(isset($_POST['roku']) && $_POST['roku']=='Rokudoku1')
{
    $original_tablica="004000000230300060060002021000000500";
    $tablica="004000000230300060060002021000000500";
    $_SESSION['org_tablica']=$original_tablica;
    $_SESSION['tablica']=$original_tablica;
}
else if (isset($_POST['roku']) && $_POST['roku']=='Rokudoku2')
{
    $original_tablica="003200204010300100001006030401002300";
    $tablica="003200204010300100001006030401002300";
    $_SESSION['org_tablica']=$original_tablica;
    $_SESSION['tablica']=$original_tablica;
}
if(isset($_SESSION['org_tablica']))
    $tablica=$_SESSION['org_tablica'];
if(isset($_SESSION['org_tablica']))
    $original_tablica=$_SESSION['org_tablica'];
$pokusaj=1;
if(isset($_POST["submit"]) && $_POST["submit"]=="Izvrši akciju!")
{
    
    if($_POST['opcija']=="1")
    {
        if(isset($_SESSION['tablica']))
        {
            $tablica=$_SESSION['tablica'];
        }
        if(isset($_SESSION['pokusaj']))
        {
            $pokusaj=$_SESSION['pokusaj'];
        }
        for ($i=0; $i < 36; $i++) { 
            if(isset($_POST[(string)$i]) && isValidNumber($_POST[(string)$i]))
            {
                $tablica[$i]=(int)$_POST[(string)$i];
            }
        }
    }
    else if($_POST['opcija']=="2")
    {
        if(isset($_SESSION['tablica']))
        {
            $tablica=$_SESSION['tablica'];
        }
        if(isset($_SESSION['pokusaj']))
        {
            $pokusaj=$_SESSION['pokusaj'];
        }
        if($original_tablica[((int)$_POST['red']-1)*6 + (int)$_POST['stupac']-1]==0)
            $tablica[((int)$_POST['red']-1)*6 + (int)$_POST['stupac']-1]=0;
        $pokusaj++;
    }
    else{

    }
    $_SESSION['tablica']=$tablica;
    $_SESSION['pokusaj']=$pokusaj;
}

?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Rokudoku</title>
    <style>table { border: solid 5px; height: 300px; width: 300px; border-collapse: collapse; border-spacing: 0;}</style>
    <style>tr { border: solid 3px; }</style>
    <style>td { border: solid 1px; text-align:center;height: 50px; width: 50px;}</style>
</head>
<body>
<h1>Rokudoku!</h1>
    <?php
    if(isset($username))
    {
        echo "Igrač: $username. <br />";
        echo "Pokušaj broj: $pokusaj. <br />";
        ?>
        <form action="rokudoku.php" method="post">
        <table>
            <?php
            for ($i=0; $i < 6; $i++) { 
                echo "<tr>";
                for ($j=0; $j < 6; $j++) { 
                    if($i%2==1)
                    {   
                        if($j%3==2)
                            echo '<td style="border-right: solid 5px; border-bottom: solid 5px;">';
                        else echo '<td style="border-bottom: solid 5px;">';
                    }
                    else
                    {
                        if($j%3==2)
                            echo '<td style="border-right: solid 5px;">';
                        else echo '<td>';
                    }
                    $ind=6*$i+$j;
                    if($tablica[$ind]=='0')
                    {
                        
                        ?>
                        <input type="text" maxlength="1" size="1" name= <?php echo $ind; ?> >
                        <?php //string ispod
                        $cpy=$tablica;
                        $pom="";
                        for ($k=1; $k <= 6; $k++) { 
                            $cpy[$ind]=(string)$k;                            
                            if(dobar($cpy,$ind))
                            {
                                $pom = $pom . (string)$k;
                            }
                        }
                        echo "<br/>";
                        echo '<span style="font-size: 10px;">'.$pom.'</span>';
                    }
                    else
                    {
                        if($original_tablica[$ind]!='0')
                        {
                            echo ' <b>' . $tablica[$ind] . ' </b>';
                        }
                        else if(dobar($tablica,$ind))
                        {
                            echo ' <span style="color:blue">'.$tablica[$ind].' </span>';
                        }
                        else
                        {
                            echo ' <span style="color:red">'.$tablica[$ind].' </span>';
                        }
                    }
                    echo "</td>";
                }
                echo "</tr>";
            }
            ?>
        </table>
        <br />
        <input type="radio" name="opcija" id="1" value="1" checked>
        <label for="1">Unos brojeva pomoću textboxeva.</label>
        <br /> <br />
        <input type="radio" name="opcija" id="2" value="2">
        <label for="2">Obriši broj iz retka </label>
        <select name="red" id="red">
            <option value="1">1</option>
            <option value="2">2</option>
            <option value="3">3</option>
            <option value="4">4</option>
            <option value="5">5</option>
            <option value="6">6</option>
        </select>
        <label for="red"> i stupca </label>
        <select name="stupac" id="stupac">
            <option value="1">1</option>
            <option value="2">2</option>
            <option value="3">3</option>
            <option value="4">4</option>
            <option value="5">5</option>
            <option value="6">6</option>
        </select>
        <br /> <br />
        <input type="radio" name="opcija" id="3" value="3">
        <label for="3">Želim sve ispočetka</label>
        <br /> <br />
        <input type="submit" name="submit" value="Izvrši akciju!">
        </form>
        <?php
        $flag=0;
        for ($i=0; $i < 36; $i++) { 
            if($tablica[$i]==0 || !dobar($tablica,$i))
            {
                $flag=1;
                break;
            }
        }
        if($flag==0)
            {
                echo "<h1>POBJEDA</h1>";
                session_unset(); session_destroy();
            }
        ?>
        <?php
    }
    else
    {
        ?>
        <form action="rokudoku.php" method="post">
        <label for="ime">Unesi svoje ime:</label>
        <input type="text" name="ime">
        <input type="submit" name="submit" value="Započni igru!">
        <select name="roku" id="roku">
            <option value="Rokudoku1">Rokudoku1</option>
            <option value="Rokudoku2">Rokudoku2</option>
        </select>
        </form>
        <?php
    }
    ?>
</body>
</html>