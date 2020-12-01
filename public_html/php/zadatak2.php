<?php 

// Npr. $memory["PRVA"][0][2] je "B"
$memory = array
(
    "PRVA" => array( "AABB", 
                     "DDEE",
                     "GGHH",
                     "MMNN" ),

    "DRUGA" => array( "LCIAFDZ", 
                      "HKBEQHW",
                      "ENQDKGX",
                      "MAPJCMZ",
                      "JRNGLOX",
                      "PFIOBRW" ),

    "TRECA" => array( "ACEB", 
                      "HDCF",
                      "GAHE",
                      "DFGB" )
);

function sendJSONandExit( $message )
{
    // Kao izlaz skripte pošalji $message u JSON formatu i prekini izvođenje.
    header( 'Content-type:application/json;charset=utf-8' );
    echo json_encode( $message );
    flush();
    exit( 0 );
}
$odg=[];
if(isset($_GET['novaigra']))
{
    if($_GET['novaigra']==="PRVA")
    {
        $odg["x"]=strlen($memory['PRVA'][0]);
        $odg["y"]=count($memory['PRVA']);
    }
    else if($_GET['novaigra']==="DRUGA")
    {
        $odg["x"]=strlen($memory['DRUGA'][0]);
        $odg["y"]=count($memory['DRUGA']);
    }
    else if($_GET['novaigra']==="TRECA")
    {
        $odg["x"]=strlen($memory['TRECA'][0]);
        $odg["y"]=count($memory['TRECA']);
    }
    else{
        $odg["error"]="nema igre";
    }
    sendJSONandExit($odg);
}
else if(isset($_GET['x'])&& isset($_GET['y']) && isset($_GET['igra']))
{
    $odg["slovo"]=$memory[$_GET['igra']][(int)$_GET['x']][(int)$_GET['y']];
    $odg["x"]=$_GET['x'];
    $odg["y"]=$_GET['y'];
    sendJSONandExit($odg);
}
?>