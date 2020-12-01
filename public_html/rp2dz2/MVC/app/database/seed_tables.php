<?php

// Popunjavamo tablice u bazi "probnim" podacima.
require_once __DIR__ . '/db.class.php';

seed_table_users();
seed_table_channels();
seed_table_messages();

exit( 0 );

// ------------------------------------------
function seed_table_users()
{
	$db = DB::getConnection();

	// Ubaci neke korisnike unutra
	try
	{
		$st = $db->prepare( 'INSERT INTO dz2_users(username, password_hash, email, registration_sequence, has_registered) VALUES (:username, :password, \'a@b.com\', \'abc\', \'1\')' );

		$st->execute( array( 'username' => 'mirko', 'password' => password_hash( 'mirkovasifra', PASSWORD_DEFAULT ) ) );
		$st->execute( array( 'username' => 'slavko', 'password' => password_hash( 'slavkovasifra', PASSWORD_DEFAULT ) ) );
		$st->execute( array( 'username' => 'ana', 'password' => password_hash( 'aninasifra', PASSWORD_DEFAULT ) ) );
		$st->execute( array( 'username' => 'maja', 'password' => password_hash( 'majinasifra', PASSWORD_DEFAULT ) ) );
		$st->execute( array( 'username' => 'pero', 'password' => password_hash( 'perinasifra', PASSWORD_DEFAULT ) ) );
	}
	catch( PDOException $e ) { exit( "PDO error [insert dz2_users]: " . $e->getMessage() ); }

	echo "Ubacio u tablicu dz2_users.<br />";
}


// ------------------------------------------
function seed_table_channels()
{
	$db = DB::getConnection();

	// Ubaci neke kanale unutra (ovo nije bas pametno ovako raditi, preko hardcodiranih id-eva usera)
	try
	{
		$st = $db->prepare( 'INSERT INTO dz2_channels(id_user, name) VALUES (:id_user, :name)' );

		$st->execute( array( 'id_user' => 1, 'name' => 'Baze - VjeĹľbe u petak' ) ); // mirko
		$st->execute( array( 'id_user' => 2, 'name' => 'Intraf - Predavanja u ponedjeljak' ) ); // slavko
		$st->execute( array( 'id_user' => 1, 'name' => 'Baze - VjeĹľbe u ÄŤetvrtak' ) ); // mirko
		$st->execute( array( 'id_user' => 3, 'name' => 'ODJ - Predavanja u srijedu' ) ); // ana
	}
	catch( PDOException $e ) { exit( "PDO error [dz2_channels]: " . $e->getMessage() ); }

	echo "Ubacio u tablicu dz2_channels.<br />";
}


// ------------------------------------------
function seed_table_messages()
{
	$db = DB::getConnection();

	// Ubaci neke poruke unutra (ovo nije bas pametno ovako raditi, preko hardcodiranih id-eva usera)
	try
	{
		$st = $db->prepare( 'INSERT INTO dz2_messages(id_channel, id_user, content, date, thumbs_up) VALUES (:id_channel, :id_user, :content, :date, :thumbs_up)' );

		$st->execute( array( 'id_channel' => 1, 'id_user' => 1, 'content' => 'Dragi studenti! Dobro doĹˇli na online vjeĹľbe iz Baza.', 'date' => '2020-04-17 12:15:00', 'thumbs_up' => 5 ) );
		$st->execute( array( 'id_channel' => 1, 'id_user' => 1, 'content' => 'Ovdje moĹľete postavljati pitanja u vezi gradiva.', 'date' => '2020-04-17 12:20:00', 'thumbs_up' => 3 ) );
		$st->execute( array( 'id_channel' => 1, 'id_user' => 5, 'content' => 'Imam pitanje u vezi Zadatka 3.', 'date' => '2020-04-17 12:25:00', 'thumbs_up' => 0 ) );
		$st->execute( array( 'id_channel' => 1, 'id_user' => 4, 'content' => 'I ja isto, da li moĹľe odgovoriti @mirko?.', 'date' => '2020-04-17 12:27:00', 'thumbs_up' => 4 ) );
		$st->execute( array( 'id_channel' => 1, 'id_user' => 1, 'content' => '@maja, @pero: evo odgovora!', 'date' => '2020-04-17 12:29:00', 'thumbs_up' => 5 ) );

		$st->execute( array( 'id_channel' => 2, 'id_user' => 5, 'content' => 'Je li ovo kanal za ODJ?', 'date' => '2020-04-12 09:15:00', 'thumbs_up' => 0 ) );
		$st->execute( array( 'id_channel' => 2, 'id_user' => 4, 'content' => 'Nije, ovo je za Intraf, pitaj @ana za ODJ.', 'date' => '2020-04-12 10:15:00', 'thumbs_up' => 5 ) );

		$st->execute( array( 'id_channel' => 3, 'id_user' => 1, 'content' => 'Ovo su vjeĹľbe iz Baza za grupu u ÄŤetvrtak.', 'date' => '2020-04-16 11:15:00', 'thumbs_up' => 0 ) );

		$st->execute( array( 'id_channel' => 4, 'id_user' => 5, 'content' => 'PoĹˇtovana prof. @ana, kada poÄŤinju predavanja iz ODJ?', 'date' => '2020-04-12 10:15:00', 'thumbs_up' => 0 ) );
		$st->execute( array( 'id_channel' => 4, 'id_user' => 3, 'content' => '@pero: PoÄŤinju u srijedu u 16h.', 'date' => '2020-04-12 12:15:00', 'thumbs_up' => 5 ) );
		$st->execute( array( 'id_channel' => 4, 'id_user' => 3, 'content' => 'Dobar dan, ovo su predavanja iz ODJ.', 'date' => '2020-04-15 16:15:00', 'thumbs_up' => 5 ) );
	}
	catch( PDOException $e ) { exit( "PDO error [dz2_messages]: " . $e->getMessage() ); }

	echo "Ubacio u tablicu dz2_messages.<br />";
}

?> 
