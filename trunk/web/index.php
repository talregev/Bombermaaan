<?php

include_once( "inc/webpage.php" );


header("Vary: Accept");
#if (stristr($_SERVER["HTTP_ACCEPT"], "application/xhtml+xml")) 
    header("Content-Type: application/xhtml+xml; charset=utf-8");
#else
#    header("Content-Type: text/html; charset=utf-8");

$downloads = array(
	array(
	"http://downloads.sourceforge.net/bombermaaan/Bombermaaan_1.02_Setup.exe?modtime=1197055380&big_mirror=0",
	"Installer for Win32 - Version 1.02",
	"4a708baed1d671be6ff0ba14bcd851e2", // MD5
	"d57361ee3c83f4cd03bee0d881f14a02b6a953ad"  // SHA1
	),
	array(
	"http://downloads.sourceforge.net/bombermaaan/Bombermaaan_1.02.zip?modtime=1197405778&big_mirror=0",
	"Zip file for Win32 - Version 1.02",
	),
	array(
	"http://downloads.sourceforge.net/bombermaaan/Bombermaaan_102_src.zip?modtime=1083110400&big_mirror=0",
	"Source files - Version 1.02",
	),
);


?>
<?php echo '<?' . 'xml version="1.0" encoding="UTF-8"?>' . "\n"; ?>
<?php echo '<!' . 'DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">' . "\n"; ?>

<?php

$webpage = new WebPage();
$webpage->head();

?>

<h1>Bombermaaan game project on sourceforge.net</h1>

<div id="content">

<h2>Introduction</h2>

Bombermaaan is a classic bomberman game. Thibaut Tollemer started this
project on July 2000. He's been using this project as a demo of what he 
could do as a game programmer, in order to be hired.

As he was hired, he published the source code and created a project space on sourceforge.net.

</div>

<?php

$webpage->tail();

?>
