<?php
session_start();
require_once __DIR__ . '/db.class.php';
if(isset($_POST['projekt']))
{
    $_SESSION['imeigre']=$_POST['projekt'];
    try
		{
            
            $db = DB::getConnection();
			$st = $db->prepare( 'SELECT * FROM projekti WHERE projekt="'.$_POST['projekt'] .'"' );
			$st->execute();
		}
        catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }
        
        $arr = array();
		while( $row = $st->fetch() )
		{
			array_push($arr,array( $row['ime'], $row['projekt'] ));
        }
        if(count($arr)===0)
            echo "greška, nema projekta";
        else 
        {
            $_SESSION['arr']=$arr;
        }
        $_SESSION['tabla']=[];
}
else if(isset($_GET['dodaj']))
{
    $tabla=$_SESSION['tabla'];
    $arr=$_SESSION['arr'];
    $ime = $_GET['imena'];
    $posao = $_GET['dodajnivo'];
    array_push($tabla,[$ime,$posao,0]);
    $_SESSION['tabla']=$tabla;
}
else
{
    $tabla=$_SESSION['tabla'];
    for ($i=0; $i < count($tabla); $i++) { 
        if(isset($_GET[''.$i]))
        {
            $tabla[$i][2]=1;
            break;
        }
    }
    $_SESSION['tabla'] =$tabla;
    $arr=$_SESSION['arr'];
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Zadatak 1</title>
</head>
<body>
    
    
    <h1>Projekt <?php echo $_SESSION['imeigre']; ?></h1>
    <form action="zadatak1_poslovi.php" method="get">
    <table>
        <tr><th>Zaposlenik</th><th>Opis posla</th> <th>Obavi</th></tr>
        <?php
        if(isset($_SESSION['tabla']))
        {
            $tabla=$_SESSION['tabla'];
            for ($i=0; $i < count($tabla); $i++) { 
                if($tabla[$i][2]===0)
                echo '<tr><td>'. $tabla[$i][0].'</td><td>'. $tabla[$i][1].'</td>
                <td><button type="submit" name="'.$i.'" id="'.$i.'">Označi kao obavljen</button></td></tr>';
                else
                    echo '<tr style="background-color:gray;"><td>'. $tabla[$i][0].'</td><td>'. $tabla[$i][1].'</td>
                    <td>Obavljeno!</td></tr>';
                
            }
        }
        ?>
    </table>
    <select name="imena" id="imena">
        <?php
        for($i=0;$i<count($arr);$i++)
        {
            $flag=0;
            for($j=0;$j<$i;$j++)
            {
                if($arr[$i][0]===$arr[$j][0])
                {
                    $flag=1;
                    break;
                }
            }
            if($flag===0)
                echo '<option value="'.$arr[$i][0].'">'.$arr[$i][0].'</option>';
        }
        ?>
    </select>
    <input type="text" name="dodajnivo" id="dodajnivo">
    <button type="submit" name="dodaj" id="dodaj">Dodaj posao</button>
    </form>
</body>
</html>