<?php
    $boja="white";
    if(isset($_COOKIE["boja"]))
        $boja=$_COOKIE["boja"];

    if(isset($_GET["text"]) && $_GET["text"]!=="")
    {
        $boja=$_GET["text"];
        
    }
    else if (isset($_GET["bojaselect"])) {

        $boja=$_GET["bojaselect"];
        
    }
    setcookie( "boja", $boja, time()+60*60*24 );
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>zad1_5</title>
    
</head>
<body style="background-color: <?php echo $boja;?>;">    
    <form action="zadatak1_prez5.php" method="GET">
        <input type="text" name="text">
        <select name="bojaselect" id="bojaselect">
            <option value="red">Crvena</option>
            <option value="blue">Plava</option>
            <option value="green" selected>Zelena</option>
            
        </select>
        <button type="submit">Submitaj</button>
    </form>
    
</body>
</html>