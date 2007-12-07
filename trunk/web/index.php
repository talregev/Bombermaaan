<?php

header("Vary: Accept");
#if (stristr($_SERVER["HTTP_ACCEPT"], "application/xhtml+xml")) 
    header("Content-Type: application/xhtml+xml; charset=utf-8");
#else
#    header("Content-Type: text/html; charset=utf-8");

$downloadurl = "http://downloads.sourceforge.net/bombermaaan/Bombermaaan_1.02_Setup.exe?modtime=1197055380&big_mirror=0";
$filemd5 = "4a708baed1d671be6ff0ba14bcd851e2";
$filesha1 = "d57361ee3c83f4cd03bee0d881f14a02b6a953ad";
	
?>
<?php echo '<?' . 'xml version="1.0" encoding="UTF-8"?>' . "\n"; ?>
<?php echo '<!' . 'DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">' . "\n"; ?>

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<head>
<meta name="Title" content="Bomberman game project" />
<meta name="Author" content="Fury" />
<meta name="Revisit" content="After 15 days" />
<meta name="Keywords" content="bomberman bomber man bombermaaan maaan fury game windows download arena bomb explosion item wall victory player players play" />
<meta name="Description" content="Bomberman game project. A DirectX Bomberman game for Windows 95 and later. Original and classic game play. Up to 5 players on the same computer..." />
<meta name="Abstract" content="Bomberman game project. A DirectX Bomberman game for Windows 95 and later. Original and classic game play. Up to 5 players on the same computer..." />
<meta name="Robots" content="INDEX,FOLLOW" />
<meta name="Language" content="English" />
<link rel="icon" href="/favicon.ico" type="image/ico" />
<link rel="shortcut icon" href="/favicon.ico" type="image/ico" />
<title>Bomberman game project</title>
</head>

<body>
<h1>Bomberman game project on sourceforge.net</h1>


<div style="float: left; width: 40%;">

<p>
You may want to view ...
</p>

<ul>
<li>the <a href="http://fury94.free.fr/">current project page</a></li>
<li>the <a href="https://sourceforge.net/projects/bombermaaan/">project page on sourceforge.net</a></li>
<li>the <a href="https://sourceforge.net/project/showfiles.php?group_id=81520">download section on sourceforge.net</a></li>
<li>the <a href="http://bombermaaan.svn.sourceforge.net/viewvc/bombermaaan/">subversion repository</a> on sourceforge.net</li>
<li>the <a href="http://bombermaaan.svn.sourceforge.net/viewvc/*checkout*/bombermaaan/trunk/docs/Readme.html?revision=5&amp;pathrev=5">README file</a> (very latest version out of the subversion repository)</li>
</ul>

<p>
Download the files from here:
</p>

<ul>
<li><a href="<?php echo htmlentities( $downloadurl ); ?>">Installer for Win32 - Version 1.02</a><br /><small>MD5:&nbsp;<?php echo $filemd5; ?>, SHA1:&nbsp;<?php echo $filesha1; ?></small></li>
<li><a href="http://downloads.sourceforge.net/bombermaaan/Bombermaaan_102_src.zip?modtime=1083110400&amp;big_mirror=0">Source files - Version 1.02</a></li>
</ul>

<p>
The installer was tested on Win XP with ServicePack 2 and Win Vista. Please note, if you install Bombermaaan on Vista to the default program files directory, the configuration and log file cannot be created. However, you can play the game. But the settings weren't remembered when you start the game the next time. To avoid this, you can install Bombermaaan to a different directory, for example &quot;C:\Bombermaaan&quot;.<br />
You need administrative rights for installing Bombermaaan. This is considered to be changed in the future.
<br />
The uninstaller was tested on Win XP with ServicePack 2 and Win Vista.
</p>

<p style="margin-top: 5em;">
<a href="http://sourceforge.net"><img style="border: 0px;" src="http://sflogo.sourceforge.net/sflogo.php?group_id=81520&amp;type=4" width="125" height="37" alt="SourceForge.net Logo" /></a>
<a href="http://validator.w3.org/check?uri=referer"><img style="border: 0px;" src="http://www.w3.org/Icons/valid-xhtml11-blue" alt="Valid XHTML 1.1" height="31" width="88" /></a>
</p>

</div>

<div>

<p>

<img style="padding-left: 2em;" src="screenshots/screen1.png" alt="Screenshot #1" />
<img style="padding-left: 2em;" src="screenshots/screen7.png" alt="Screenshot #2" />
<img style="padding-left: 2em;" src="screenshots/screen8.png" alt="Screenshot #3" />

</p>

</div>

</body>

</html>
