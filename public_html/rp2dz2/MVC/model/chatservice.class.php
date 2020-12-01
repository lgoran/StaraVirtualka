<?php

require_once __DIR__ . '/../app/database/db.class.php';
require_once __DIR__ . '/user.class.php';
require_once __DIR__ . '/channel.class.php';
require_once __DIR__ . '/message.class.php';

class ChatService
{
	function getUserById( $id )
	{
		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'SELECT * FROM dz2_users WHERE id=:id' );
			$st->execute( array( 'id' => $id ) );
		}
		catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }

		$row = $st->fetch();
		
		if( $row === false )
			return null;
		else
			return new User( $row['id'], $row['username'], $row['password_hash'], $row['email'], $row['registration_sequence'], $row['has_registered'] );
	}
	function getUsernamesByMessagelist($messagelist)
	{
		$arr=array();
		foreach($messagelist as $msg)
		{
			$arr[]=$this->getUserById($msg->id_user)->username;
		}		
		return $arr;
	}
	function getUserByUsername( $username )
	{
		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'SELECT * FROM dz2_users WHERE username=:username' );
			$st->execute( array( 'username' => $username ) );
		}
		catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }

		$row = $st->fetch();
		
		if( $row === false )
			return null;
		else
			return new User( $row['id'], $row['username'], $row['password_hash'], $row['email'], $row['registration_sequence'], $row['has_registered'] );
	}


	function getAllUsers( )
	{
		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'SELECT * FROM dz2_users ORDER BY username' );
			$st->execute();
		}
		catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }

		$arr = array();
		while( $row = $st->fetch() )
		{
			$arr[] = new User( $row['id'], $row['username'], $row['password_hash'], $row['email'], $row['registration_sequence'], $row['has_registered'] );
		}

		return $arr;
	}
	function getAllChannelsByUser($username)
	{
		$id_user=$this->getUserByUsername($username)->id;
		if(!isset($id_user))
		{
			return;
		}
		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'SELECT * FROM dz2_channels WHERE id_user=:id_user');
			$st->execute(array('id_user' => $id_user));
		}
		catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }

		$arr = array();
		while( $row = $st->fetch() )
		{
			$arr[] = new Channel( $row['id'], $row['id_user'], $row['name'] );
		}

		return $arr;
	}
	function getAllChannels( )
	{
		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'SELECT * FROM dz2_channels' );
			$st->execute();
		}
		catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }

		$arr = array();
		while( $row = $st->fetch() )
		{
			$arr[] = new Channel( $row['id'], $row['id_user'], $row['name'] );
		}

		return $arr;
	}
	function getAllMessagesByChannel($id_channel)
	{
		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'SELECT * FROM dz2_messages WHERE id_channel=:id_channel ORDER BY date desc' );
			$st->execute(array('id_channel' => $id_channel));
		}
		catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }
		$arr = array();
		while( $row = $st->fetch() )
		{
			$arr[] = new Message( $row['id'], $row['id_user'], $row['id_channel'], $row['content'], $row['thumbs_up'],$row['date'] );
		}

		return $arr;
	}
	function getAllMessagesByUser($username)
	{
		$id_user=$this->getUserByUsername($username)->id;
		if(!isset($id_user))
		{
			return;
		}
		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'SELECT * FROM dz2_messages WHERE id_user=:id_user ORDER BY date desc' );
			$st->execute(array('id_user' => $id_user));
		}
		catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }
		$arr = array();
		while( $row = $st->fetch() )
		{
			$arr[] = new Message( $row['id'], $row['id_user'], $row['id_channel'], $row['content'], $row['thumbs_up'],$row['date'] );
		}

		return $arr;
	}

	function createChannel($username,$channelName)
	{
		$id_user=$this->getUserByUsername($username)->id;
		if(!isset($id_user))
		{
			return;
		}	
		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'INSERT INTO dz2_channels(id_user, name) VALUES (:id_user, :name)' );
			$st->execute( array( 'id_user' => $id_user, 'name' => $channelName ) ); 
		}
		catch( PDOException $e ) { exit( "PDO error [dz2_channels]: " . $e->getMessage() ); }

		echo "Ubacio u tablicu dz2_channels.<br />";
	}
	function createMessage($username,$id_channel,$content)
	{
		$id_user=$this->getUserByUsername($username)->id;
		if(!isset($id_user))
		{
			return;
		}	
		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'INSERT INTO dz2_messages(id_user, id_channel, content, thumbs_up, date) VALUES 
			(:id_user, :id_channel, :content, :thumbs_up, :date)' );
			$st->execute( array( 'id_user' => $id_user, 'id_channel' => $id_channel, 'content' => $content, 'thumbs_up' => 0, 'date' => date("Y-m-d") . ' ' . date("H:i:s") ) ); 
		}
		catch( PDOException $e ) { exit( "PDO error [dz2_messages]: " . $e->getMessage() ); }

		echo "Ubacio u tablicu dz2_messages.<br />";
	}
	function getMessageThumbsUpById($id)
	{
		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'SELECT thumbs_up FROM dz2_messages WHERE id=:id' );
			$st->execute( array( 'id' => $id ) );
		}
		catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }

		$row = $st->fetch();
		
		if( $row === false )
			return null;
		else
			return $row['thumbs_up'];
	}
	function incrementThumbsUp( $id )
	{
		$increment=(int)$this->getMessageThumbsUpById($id) +1;
		try
		{
			$db = DB::getConnection();
			$st = $db->prepare( 'UPDATE dz2_messages SET thumbs_up=:thumbs_up WHERE id=:id' );
			$st->execute( array( 'thumbs_up' => $increment ,'id' => $id ) );
		}
		catch( PDOException $e ) { exit( 'PDO error ' . $e->getMessage() ); }
	}
};

?>

