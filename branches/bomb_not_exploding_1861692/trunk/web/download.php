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
		"Bombermaaan_16pixels_rev294.zip",
		"Zip file for Win32",
		"6f2d56729cf0706e93dcc67f26ee5309",  // MD5
		"afab1b347282354c275510a3368b4b3a954182a6",  // SHA1
		"2008-03-02",
		),
		array(
		"Bombermaaan_32pixels_rev294.zip",
		"Zip file for Win32",
		"7da430500c0e0fc7d4287a6344c38e4b",  // MD5
		"176d070d4bec92cafe61593eb49e8b9c29e201c5",  // SHA1
		"2008-03-02",
		),
/***
		array(
		"Bombermaaan_16pixels_rev264_2.zip",
		"Zip file for Win32",
		"7d76897f720618c0d07f738a55e5acf7",  // MD5
		"e3c22b1ad1354dc1e30363fd40bd0a79cbee7cdc",  // SHA1
		"2008-02-11",
		),
		array(
		"Bombermaaan_32pixels_rev264_2.zip",
		"Zip file for Win32",
		"34e31b4f3fdde59a043816eb77c13a25",  // MD5
		"02dc2b9b76764b25000ff84185470148ef2d492f",  // SHA1
		"2008-02-11",
		),
		array(
		"Bombermaaan_16pixels_rev247.zip",
		"Zip file for Win32",
		"f8e2805b2412393938a797878913a107",  // MD5
		"c709932483ff95248855e9a3b70de80b6841aadf",  // SHA1
		"2008-01-08",
		),
		array(
		"Bombermaaan_32pixels_rev247.zip",
		"Zip file for Win32",
		"104d77c19a842bd32431152cc63c52d6",  // MD5
		"bf798be3603625ebc83ffdcfa207e51a422edb30",  // SHA1
		"2008-01-08",
		),
		array(
		"Bombermaaan_16pixels_rev153.zip",
		"Zip file for Win32",
		"1181367d3f2d981541ee83cb941a96cd",  // MD5
		"2e09f99b46e2bdb8b99359f31f2ee9d5f6f53731",  // SHA1
		"2008-01-02",
		),
		array(
		"Bombermaaan_32pixels_rev153.zip",
		"Zip file for Win32",
		"13c300843201b08bba3153122055e94e",  // MD5
		"3c0d513e7cf240a0609bfb36476ab1345a7defde",  // SHA1
		"2008-01-02",
		),
		array(
		"Bombermaaan_blocksize_32pixels_rev115.zip",
		"Zip file for Win32",
		"8719b863dae7e22e697354ba3c509a8f",  // MD5
		"36cbd33e892c95135914cf7ffbd5d707e0dac7d9",  // SHA1
		"2007-12-19",
		),
***/
	),
);

?>

<h1>Downloads for the Bombermaaan game project</h1>

<div id="content">

<div id="quicklinks">
<p style="float: right; margin-right: 0.8em; font-style: italic;">Quick links</p>
<ul>
<li><a href="#stable">Stable version</a></li>
<li><a href="#sourcecode">Sourcecode</a></li>
<li><a href="#experimental">Experimental releases</a></li>
</ul>
</div>

<h2><a id="stable">The current stable version is 1.02</a></h2>

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
You can view the <a href="https://sourceforge.net/project/shownotes.php?group_id=81520&amp;release_id=234468">release notes</a> on the <a href="https://sourceforge.net/project/showfiles.php?group_id=81520">download page</a> on SourceForge.net.
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

<h2><a id="sourcecode">Sourcecode</a></h2>

The sourcecode is hosted in the Subversion repository on SourceForge.net. 
If you have TortoiseSVN installed, you can check out the <a href="tsvn:https://bombermaaan.svn.sourceforge.net/svnroot/bombermaaan/trunk">whole sourcecode</a> by clicking on the weblink.

<h2><a id="experimental">Experimental releases</a></h2>

<p>
These packages have more features and bug fixes, but may also be unstable.
You can download the files if you want to try more recent builds but don't want to compile Bombermaaan on your own.
</p>

<table class="downloadbox">

<tr>
<th colspan="2">Package</th>
<th>Released</th>
<th>Checksums</th>
</tr>

<?php

foreach ( $downloads[ "experimental" ] as $item ) {

	$file = $item[ 0 ];
	$text = $item[ 1 ];
	$md5 = $item[ 2 ];
	$sha1 = $item[ 3 ];
	$reldate = $item[ 4 ];

?>	
<tr>
<td>
<a href="http://downloads.sourceforge.net/bombermaaan/<? echo htmlentities( $file ); ?>?download"><?php echo htmlentities( $file ); ?></a>
</td>
<td>
<?php echo htmlentities( $text ); ?>
</td>
<td><?php echo $reldate; ?></td>
<td>
<?php if ( ! empty( $md5 ) ) { echo "<small>MD5:&nbsp;</small><code>$md5</code><br />"; } ?>
<?php if ( ! empty( $sha1 ) ) { echo "<small>SHA1:&nbsp;</small><code>$sha1</code>"; } ?>&nbsp;
</td>
</tr>

<?

}  // foreach ( ... )

?>

</table>

<p>
You can view the <a href="https://sourceforge.net/project/showfiles.php?group_id=81520">release notes</a> on the download page on SourceForge.net by clicking on the <i>Release Notes</i> icon near a package.
</p>

<p>
This list shows the most recent/important file releases. You are looking for <a href="https://sourceforge.net/project/showfiles.php?group_id=81520&amp;package_id=256331">older experimental releases</a>?
</p>

</div>

<?php

$webpage->tail();

?>
