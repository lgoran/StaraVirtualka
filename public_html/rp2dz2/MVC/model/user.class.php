<?php

class User
{
	protected $id, $username, $password, $email, $registration_sequence, $has_registered;

	function __construct( $id, $username, $password, $email, $registration_sequence, $has_registered )
	{
		$this->id = $id;
		$this->username = $username;
		$this->email = $email;
		$this->password = $password;
		$this->registration_sequence = $registration_sequence;
		$this->has_registered = $has_registered;
	}

	function __get( $prop ) { return $this->$prop; }
	function __set( $prop, $val ) { $this->$prop = $val; return $this; }
}

?>

