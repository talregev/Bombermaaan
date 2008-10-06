<?php

include_once( "inc/webpage.php" );


$webpage = new WebPage();
$webpage->head();

$downloads = array(
	"stable" => array(
		array(
		"Bombermaaan_1.3.1.476_setup.exe",
		"Installer for Win32",
		"ae7d8bdefb90a7b01692f3f7f652cbe0", // MD5
		"d5397092732f21a2f1febced85d1fe7777e19d7a"  // SHA1
		),
		array(
		"Bombermaaan_1.3.1_2008-07-27.zip",
		"Zip file for Win32",
		"1918c688f0ba318ea58e39ed69e15565",  // MD5
		"1c278a34cc94ec853a04b140e2aafa40067047ce",  // SHA1
		),
		/** not available yet
		array(
		"Bombermaaan_102_src.zip",
		"Source",
		),
		**/
	),
	"experimental" => array(
		array(
		"Bombermaaan_rev528.zip",
		"Zip file for Win32",
		"51f8a9ae12caf278d07a8472aa2c5fce",  // MD5
		"b553e783076ee2ce902908103b40d9a1595a1dbf",  // SHA1
		"2008-09-21",
		),
		array(
		"Bombermaaan_rev528_src.zip",
		"Zip file for Win32 with source code",
		"27affe053d4f9842968bcbe0e04ba4f5",  // MD5
		"bdab20e124b7a9c40aedfe29aef17f3d938dd374",  // SHA1
		"2008-09-21",
		),
		array(
		"Bombermaaan-080917.tar.bz2",
		"Zip file for Debian Linux",
		"b5c19bc649830f254801b92534c417ed",  // MD5
		"e8cfe19883caacce252381bb2b4ccf4fb66e67d4",  // SHA1
		"2008-09-18",
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
<li><a href="#experimental">Experimental releases</a></li>
<li><a href="#sourcecode">Sourcecode</a></li>
</ul>
</div>

<h2><a id="stable">The current stable version is 1.3.1</a></h2>

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
You can view the <a href="https://sourceforge.net/project/shownotes.php?release_id=615987&amp;group_id=81520">release notes</a> on the <a href="https://sourceforge.net/project/showfiles.php?group_id=81520">download page</a> on SourceForge.net.
</p>

<p>
There is also a <a href="http://bombermaaan.svn.sourceforge.net/viewvc/*checkout*/bombermaaan/trunk/docs/Readme.html">README file</a> available (very latest version out of the subversion repository).
</p>

<h2><a id="experimental">Experimental releases</a></h2>

<p>
The experimental package releases have more features and bug fixes, but may also be unstable.
You can download the files if you want to try more recent builds but don't want to compile Bombermaaan on your own.
We release new packages from time to time. There is no fix time table.
</p>

<p>
<a href="https://sourceforge.net/project/showfiles.php?group_id=81520&amp;package_id=256331">Download experimental releases</a>.
</p>

<p>
Looking for Linux files?<br />
You can download <a href="https://sourceforge.net/project/showfiles.php?group_id=81520&amp;package_id=256331&amp;release_id=627216">Debian Linux package files</a> for x86 and AMD64.
</p>

<p>
You can view the release notes. Check for the <img src="https://s.fsdn.com/sf/images/phoneix/icons/tango/edit-paste.png" alt="Release notes icon" /> icon near the release name. 
You will also find the MD5 and SHA1 checksums there.
</p>

<h2><a id="sourcecode">Sourcecode</a></h2>

<p>
The sourcecode is hosted in the Subversion repository on SourceForge.net. 
If you have <a href="http://tortoisesvn.net/">TortoiseSVN</a> installed, you can check out the <a href="tsvn:https://bombermaaan.svn.sourceforge.net/svnroot/bombermaaan/trunk">whole sourcecode</a> by clicking on the weblink.
</p>

<p>
The source code is also available as a package, see the <code>*_src.zip</code> and <code>*_src.tar.gz</code> files
in the <a href="https://sourceforge.net/project/showfiles.php?group_id=81520&amp;package_id=83430">stable</a>
and
<a href="https://sourceforge.net/project/showfiles.php?group_id=81520&amp;package_id=256331">experimental</a>
package sections.
</p>

<p>
The source documentation and resource files can be found in the <a href="https://sourceforge.net/project/showfiles.php?group_id=81520&amp;package_id=293941">DevelTools section</a>.
</p>

</div>

<?php

$webpage->tail();

?>
