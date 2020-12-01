<!DOCTYPE html>
<html>
<head>
	<meta charset="utf8">
	<title>ChatApp</title>
	<link rel="stylesheet" href="css/style.css">
	<style>
	ul{
		list-style: none;
		font-size: 15px;
		font-family: 'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;
	}
	li{
		margin-top: 30px;
	}

	ul a{
		text-decoration: none;
		color: red;
		padding: 5px 20px;
		
	}
	ul a:hover{
		background: #fff;
		color: black;
		border-radius: 20px;
		box-shadow: blue 6px 6px 50px;
	}
	</style>
</head>
<body>
	<h1>Chat</h1>
	<?php if(isset($_SESSION['user'])) echo 'Dobrodošli @' . $_SESSION['user'].'!'; ?>
	<hr>
	<ul>
		<a href="index.php?rt=channels/userChannels">Vaši kanali</a>
		<a href="index.php?rt=channels/index">Svi kanali</a>
		<a href="index.php?rt=channels/create">Napravi novi kanal</a>
		<a href="index.php?rt=messages/searchByUser">Sve vaše poruke</a>
		<a href="index.php?rt=logout/logout">Odjavi se</a>
	</ul>
	<hr>
	<h1><?php echo $title; ?></h1>