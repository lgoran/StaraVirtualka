<?php
interface iUpravljiv
{
    function idiRavno($k);
    function skreniDesno();
    function skeniLijevo();
}
class Vozilo implements iUpravljiv
{
    protected $ime,$smjer,$x,$y;
    protected $ukupno;
    function __constructor($_ime){
        $ime=$_ime;
        $smjer='N';
        $x=0;
        $y=0;
        $ukupno=0;
    }
    function gdjeSam()
    {
        echo $this->ime . $this->x . $this->y . "<br>";
    }
    function idiRavno($k)
    {
        if($this->smjer=='N')
        {
            $this->y+=$k;
        }
        else if($this->smjer=='S')
        {
            $this->y-=$k;
        }
        else if($this->smjer=='E')
        {
            $this->x-=$k;
        }
        else{
            $this->x+=$k;
        }
        $this->ukupno+=$k;
    }
    function skreniDesno()
    {
        if($this->smjer=='N')
        {
            $this->smjer='E';
        }
        else if($this->smjer=='S')
        {
            $this->smjer='W';
        }
        else if($this->smjer=='E')
        {
            $this->smjer='S';
        }
        else{
            $this->smjer='N';
        }
    }
    function skreniLijevo()
    {
        if($this->smjer=='N')
        {
            $this->smjer='W';
        }
        else if($this->smjer=='S')
        {
            $this->smjer='E';
        }
        else if($this->smjer=='E')
        {
            $this->smjer='N';
        }
        else{
            $this->smjer='S';
        }
    }
}
class Auto extends Vozilo
{
    function potrosenBenzin()
    {
        echo $this->ukupno*10 . "<br>";
    }
}
class Tramvaj extends Vozilo
{
    private $linija_broj;
    function __constructor($broj_linije)
    {
        $linija_broj=$broj_linije;
        parent::__constructor($linija_broj);
    }
    function linija()
    {
        return $this->linija;
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Jebi se</title>
</head>
<body>
    <?php
    function my_sort(&$polje)
    {
        for ($i=0; $i < count($polje)-1; $i++) { 
            for ($j=$i+1; $j < count($polje); $j++) { 
                if(strcmp($polje[$i],$polje[$j])>0)
                {
                    $str=$polje[$i];
                    $polje[$i]=$polje[$j];
                    $polje[$j]=$str;
                }
            }
        }  
    }
    //prvi zad
        echo "<table border=1>";         
        for ($i=1; $i <= 10; $i++) 
        {             
            echo "<tr>";
                for ($j=1; $j<=10; $j++) { 
                    echo "<td>" . $i*$j . "</td>";                    
                }
            echo "</tr>";
        }
        echo "</table>"; 
        echo "<br><br>";
    //drugi zad
        
        //$polje=[];
        for ($i=0; $i < 10; $i++) { 
            $slova="qwertzuiopasdfghjklyxcvbnm";
            $polje[$i]=chr(rand(65,90)) . chr(rand(65,90)) . chr(rand(65,90)) . chr(rand(65,90)) . chr(rand(65,90));
            echo $polje[$i] . " ";
        }
        my_sort($polje);
        echo "<br><br>";
        for ($i=0; $i < 10; $i++) { 
            echo $polje[$i] . " ";
        } 
        //treci zadatak
        unset($polje);
        $polje[0] = new Auto( 'yugo' );
        $polje[1] = new Tramvaj( 'petica', 5 );
        $polje[2] = new Auto( 'bmw' );

        for( $i = 3; $i < 7; ++$i )
            $polje[$i] = new Tramvaj( 'tramvaj broj ' . $i, $i );

        for( $i = 7; $i < 10; ++$i )
            $polje[$i] = new Auto( 'trabant #' . $i );


        // .. Iteriranje po polju. Može i običnom for-petljom.
        foreach( $polje as $vozilo )
        {
            $vozilo->idiRavno( 10 );
            $vozilo->skreniDesno();
            $vozilo->idiRavno( 10 );
            $vozilo->skreniDesno();
            $vozilo->idiRavno( 20 );
            $vozilo->skreniLijevo();
            $vozilo->skreniLijevo();
            $vozilo->skreniLijevo();
            $vozilo->idiRavno( 5 );
        }
        // Auto (yugo)
		echo '<p>';
		$polje[0]->gdjeSam();
		echo '<br />Potrošen benzin: ' . $polje[0]->potrosenBenzin();
		echo '</p>';
		
		// Tramvaj (petica)
		echo '<p>';
		$polje[1]->gdjeSam();
		echo '<br />Linija: ' . $polje[1]->linija();
		echo '</p>';

		// Auto (bmw)
		echo '<p>';
		echo $polje[2]; // Može i ovako jer postoji __toString().
		echo '<br />Potrošen benzin: ' . $polje[2]->potrosenBenzin();
		echo '</p>';

		// Ostala vozila
		for( $i = 3; $i < 10; ++$i )
		{
			echo '<p>';
			echo $polje[$i];
			
			if( $polje[$i] instanceof Auto ) // Detekcija tipa!
				echo '<br />Potrošen benzin: ' . $polje[$i]->potrosenBenzin();
			else if( $polje[$i] instanceof Tramvaj ) // Detekcija tipa!
				echo '<br />Linija: ' . $polje[$i]->linija();
			
			echo '</p>';
		}
    ?>
</body>
</html>