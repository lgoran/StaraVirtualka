<?php
    $slucajni=rand(1,100);
    $min=101;
    $max=0;
    $broj=0;
    if(isset($_COOKIE["slucajni"]))
    {      
        $slucajni=(int)$_COOKIE["slucajni"];
        var_dump($slucajni);
    }
    else
    {
        setcookie("slucajni",$slucajni,time()+60*60*24);
    }
    if(isset($_GET["submit"]) && isset($_GET["text"]))
    {
        
        //validate number
        $broj=(int)$_GET["text"];
        if(isset($_COOKIE["min"]) && isset($_COOKIE["max"]))
        {
            $min=(int)$_COOKIE["min"];
            $max=(int)$_COOKIE["max"];
        }
          
        
        if($broj<$min && $broj>$slucajni)
            $min=$broj;
        if($broj>$max && $broj<$slucajni)
            $max=$broj;
            var_dump($max,$min);
    }
    setcookie("min",$min,time()+60*60*24);
    setcookie("max",$max,time()+60*60*24);
    
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Zadatak 3 prez 5</title>
</head>
<body>
    <form action="index.php" method="GET">
    <label for="text">Pogodi broj</label>
    <input type="text" name="text">
    <button type="submit" name="submit">Submit</button>
    
    <br>
    <?php
    if($broj===$slucajni)
    {
        $min=101;
        $max=0;
        
        echo "Pogodak!";
        setcookie("slucajni",$slucajni,1);
        setcookie("min",$min,1);
        setcookie("max",$max,1);
    }
    else 
        echo "Broj je između" . $max . " i " . $min;
    ?>
    </form>
</body>
</html>