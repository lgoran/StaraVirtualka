
<?php

// Stvaramo tablice u bazi (ako veÄ‡ ne postoje od ranije).
require_once __DIR__ . '/db.class.php';

create_table_users();
create_table_channels();
create_table_messages();

exit( 0 );

// --------------------------
function has_table( $tblname )
{
	$db = DB::getConnection();
	
	try
	{
		$st = $db->prepare( 
			'SHOW TABLES LIKE :tblname'
		);

		$st->execute( array( 'tblname' => $tblname ) );
		if( $st->rowCount() > 0 )
			return true;
	}
	catch( PDOException $e ) { exit( "PDO error [show tables]: " . $e->getMessage() ); }

	return false;
}


function create_table_users()
{
	$db = DB::getConnection();

	if( has_table( 'dz2_users' ) )
		exit( 'Tablica dz2_users vec postoji. Obrisite ju pa probajte ponovno.' );


	try
	{
		$st = $db->prepare( 
			'CREATE TABLE IF NOT EXISTS dz2_users (' .
			'id int NOT NULL PRIMARY KEY AUTO_INCREMENT,' .
			'username varchar(50) NOT NULL,' .
			'password_hash varchar(255) NOT NULL,'.
			'email varchar(50) NOT NULL,' .
			'registration_sequence varchar(20) NOT NULL,' .
			'has_registered int)'
		);

		$st->execute();
	}
	catch( PDOException $e ) { exit( "PDO error [create dz2_users]: " . $e->getMessage() ); }

	echo "Napravio tablicu dz2_users.<br />";
}


function create_table_channels()
{
	$db = DB::getConnection();

	if( has_table( 'dz2_channels' ) )
		exit( 'Tablica dz2_channels vec postoji. Obrisite ju pa probajte ponovno.' );

	try
	{
		$st = $db->prepare( 
			'CREATE TABLE IF NOT EXISTS dz2_channels (' .
			'id int NOT NULL PRIMARY KEY AUTO_INCREMENT,' .
			'id_user int NOT NULL,' .
			'name varchar(100) NOT NULL)'
		);

		$st->execute();
	}
	catch( PDOException $e ) { exit( "PDO error [create dz2_channels]: " . $e->getMessage() ); }

	echo "Napravio tablicu dz2_channels.<br />";
}


function create_table_messages()
{
	$db = DB::getConnection();

	if( has_table( 'dz2_messages' ) )
		exit( 'Tablica dz2_messages vec postoji. Obrisite ju pa probajte ponovno.' );

	try
	{
		$st = $db->prepare( 
			'CREATE TABLE IF NOT EXISTS dz2_messages (' .
			'id int NOT NULL PRIMARY KEY AUTO_INCREMENT,' .
			'id_user INT NOT NULL,' .
			'id_channel INT NOT NULL,' .
			'content varchar(1000) NOT NULL,' .
			'thumbs_up INT NOT NULL,' .
			'date DATETIME NOT NULL)'
		);

		$st->execute();
	}
	catch( PDOException $e ) { exit( "PDO error [create dz2_messages]: " . $e->getMessage() ); }

	echo "Napravio tablicu dz2_messages.<br />";
}
