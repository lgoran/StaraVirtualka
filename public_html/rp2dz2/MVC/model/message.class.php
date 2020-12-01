<?php

class Message
{
	protected $id, $id_user, $id_channel, $content, $thumbs_up, $date;
	//mozda jos button mu dodat

	function __construct( $id, $id_user, $id_channel, $content, $thumbs_up, $date )
	{
		$this->id = $id;
		$this->id_user = $id_user;
		$this->id_channel = $id_channel;
		$this->content = $content;
		$this->thumbs_up = $thumbs_up;
		$this->date = $date;
	}

	function __get( $prop ) { return $this->$prop; }
	function __set( $prop, $val ) { $this->$prop = $val; return $this; }
}

?>

