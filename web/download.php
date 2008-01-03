<?php

include_once( "inc/webpage.php" );


$webpage = new WebPage();
$webpage->head();

$downloads = array(
	"stable" => array(
		array(
		"Bombermaaan_1.02_Setup.exe",
		"Installer for Win32",
		"4a708baed1d671be6ff0ba14bcd851e2", // MD5
		"d57361ee3c83f4cd03bee0d881f14a02b6a953ad"  // SHA1
		),
		array(
		"Bombermaaan_1.02.zip",
		"Zip file for Win32",
		"08fd98b0bbe1d3a2020d7f36561869ac",  // MD5
		"347e222c2dd411d6529a816acf987531103f8e04",  // SHA1
		),
		array(
		"Bombermaaan_102_src.zip",
		"Source",
		),
	),
	"experimental" => array(
		array(
		"Bombermaaan_16pixels_rev153.zip",
		"Zip file for Win32",
		"1181367d3f2d981541ee83cb941a96cd",  // MD5
		"2e09f99b46e2bdb8b99359f31f2ee9d5f6f53731",  // SHA1
		),
		array(
		"Bombermaaan_32pixels_rev153.zip",
		"Zip file for Win32",
		"13c300843201b08bba3153122055e94e",  // MD5
		"3c0d513e7cf240a0609bfb36476ab1345a7defde",  // SHA1
		),
		array(
		"Bombermaaan_blocksize_32pixels_rev115.zip",
		"Zip file for Win32",
		"8719b863dae7e22e697354ba3c509a8f",  // MD5
		"36cbd33e892c95135914cf7ffbd5d707e0dac7d9",  // SHA1
		),
	),
);

?>

<h1>Downloads for the Bombermaaan game project</h1>

<div id="content">

<h2>The current version is 1.02</h2>

<table class="downloadbox">

<tr>
<th colspan="2">Package</th>
<th>Checksums</th>
</tr>

<?php

foreach ( $downloads[ "stable" ] as $item ) {

	$file = $item[ 0 ];
	$text = $item[ 1 ];
	$md5 = $item[ 2 ];
	$sha1 = $item[ 3 ];

?>	
<tr>
<td>
<a href="http://downloads.sourceforge.net/bombermaaan/<? echo htmlentities( $file ); ?>?download"><?php echo htmlentities( $file ); ?></a>
</td>
<td>
<?php echo htmlentities( $text ); ?>
</td>
<td>
<?php if ( ! empty( $md5 ) ) { echo "<small>MD5:&nbsp;</small><code>$md5</code><br />"; } ?>
<?php if ( ! empty( $sha1 ) ) { echo "<small>SHA1:&nbsp;</small><code>$sha1</code><br />"; } ?>
</td>
</tr>

<?

}  // foreach ( ... )

?>

</table>

<p>
You can view the <a href="https://sourceforge.net/project/shownotes.php?group_id=81520&release_id=234468">release notes</a> on the <a href="https://sourceforge.net/project/showfiles.php?group_id=81520">download page</a> on SourceForge.net.
</p>

<p>
There is also a <a href="http://bombermaaan.svn.sourceforge.net/viewvc/*checkout*/bombermaaan/trunk/docs/Readme.html?revision=5&amp;pathrev=5">README file</a> available (very latest version out of the subversion repository).
</p>

<h2>Notes</h2>

<p>
The installer was tested on Win XP with ServicePack 2 and Win Vista. Please note, if you install Bombermaaan on Vista to the default program files directory, the configuration and log file cannot be created. However, you can play the game. But the settings weren't remembered when you start the game the next time. To avoid this, you can install Bombermaaan to a different directory, for example &quot;C:\Bombermaaan&quot;.<br />
You need administrative rights for installing Bombermaaan. This is considered to be changed in the future.
<br />
The uninstaller was tested on Win XP with ServicePack 2 and Win Vista.
</p>

<p>
If you don't want to use the installer, you can also download the Zip file and unzip the folder somewhere and run Bombermaaan.exe from there. Please ensure to unzip the whole directory, not only Bombermaaan.exe.
</p>

<h2>Sourcecode</h2>

The sourcecode is hosted in the Subversion repository on SourceForge.net. 
If you have TortoiseSVN installed, you can check out the <a href="tsvn:https://bombermaaan.svn.sourceforge.net/svnroot/bombermaaan/trunk">whole sourcecode</a> by clicking on the weblink.

<h2>Experimental releases</h2>

<p>
These packages have more features and bug fixes, but may also be unstable.
You can download the files if you want to try more recent builds but don't want to compile Bombermaaan on your own.
</p>

<table class="downloadbox">

<tr>
<th colspan="2">Package</th>
<th>Checksums</th>
</tr>

<?php

foreach ( $downloads[ "experimental" ] as $item ) {

	$file = $item[ 0 ];
	$text = $item[ 1 ];
	$md5 = $item[ 2 ];
	$sha1 = $item[ 3 ];

?>	
<tr>
<td>
<a href="http://downloads.sourceforge.net/bombermaaan/<? echo htmlentities( $file ); ?>?download"><?php echo htmlentities( $file ); ?></a>
</td>
<td>
<?php echo htmlentities( $text ); ?>
</td>
<td>
<?php if ( ! empty( $md5 ) ) { echo "<small>MD5:&nbsp;</small><code>$md5</code><br />"; } ?>
<?php if ( ! empty( $sha1 ) ) { echo "<small>SHA1:&nbsp;</small><code>$sha1</code><br />"; } ?>
</td>
</tr>

<?

}  // foreach ( ... )

?>

</table>

<p>
You can view the <a href="https://sourceforge.net/project/showfiles.php?group_id=81520">release notes</a> on the download page on SourceForge.net by clicking on the <i>Release Notes</i> icon near a package.
</p>

</div>

<?php

$webpage->tail();

?>
