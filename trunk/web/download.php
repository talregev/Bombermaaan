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
	"08fd98b0bbe1d3a2020d7f36561869ac",  // MD5
	"347e222c2dd411d6529a816acf987531103f8e04",  // SHA1
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

<h1>Downloads for the Bombermaaan game project</h1>

<div id="content">

<div>

<p>
Download the files from here:
</p>

<ul>
<?php

foreach ( $downloads as $item ) {

	$url = $item[ 0 ];
	$text = $item[ 1 ];
	$md5 = $item[ 2 ];
	$sha1 = $item[ 3 ];

?>	
<li>
<a href="<? echo htmlentities( $url ); ?>"><?php echo htmlentities( $text ); ?></a>
<?php if ( ! empty( $md5 ) ) { echo "<br /><small>MD5:&nbsp;$md5</small>"; } ?>
<?php if ( ! empty( $sha1 ) ) { echo "<br /><small>SHA1:&nbsp;$sha1</small>"; } ?>
</li>

<?

}  // foreach ( ... )

?>
</ul>

<p>
Checkout the latest subversion revision with <br /><code>svn co https://bombermaaan.svn.sourceforge.net/svnroot/bombermaaan/trunk bombermaaan</code>.
</p>

<p>
Notes:
</p>

<p>
The installer was tested on Win XP with ServicePack 2 and Win Vista. Please note, if you install Bombermaaan on Vista to the default program files directory, the configuration and log file cannot be created. However, you can play the game. But the settings weren't remembered when you start the game the next time. To avoid this, you can install Bombermaaan to a different directory, for example &quot;C:\Bombermaaan&quot;.<br />
You need administrative rights for installing Bombermaaan. This is considered to be changed in the future.
<br />
The uninstaller was tested on Win XP with ServicePack 2 and Win Vista.
</p>

<p>
If you don't want to use the installer, you can also download the Zip file and unzip the folder somewhere and run Bombermaaan.exe from there. Please ensure to unzip the whole directory, not only Bombermaaan.exe.
</p>

</div>

</div>

<?php

$webpage->tail();

?>
