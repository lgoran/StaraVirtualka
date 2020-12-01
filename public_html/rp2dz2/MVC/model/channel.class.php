<?php

class Channel
{
	protected $id, $id_user, $name;

	function __construct( $id, $id_user, $name )
	{
		$this->id = $id;
		$this->id_user = $id_user;
		$this->name = $name;
	}

	function __get( $prop ) { return $this->$prop; }
	function __set( $prop, $val ) { $this->$prop = $val; return $this; }
}

?>

