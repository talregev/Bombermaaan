<?php

include_once( "inc/webpage.php" );


$webpage = new WebPage();
$webpage->head();

$downloads = array(
	"stable" => array(
		array(
		"Bombermaaan_1.4.0.627_setup.exe",
		"Installer for Win32",
        "Installs Bombermaaan on your Windows system. An uninstaller is provided, too.",
		),
		array(
		"Bombermaaan_1.4.0.627_20081018_win32.zip",
		"Zip file for Win32",
        "Simply play Bombermaaan without installing it. Just extract all files to a folder and run Bombermaaan. No files are changed outside this directory.",
		),
		array(
		"bombermaaan_1.4.0-1_i386.deb",
		"Debian package for i386",
        "Installer package. The bombermaaan-data package is required, too.",
		),
		array(
		"bombermaaan-data_1.4.0-1_i386.deb",
		"Debian package for i386",
        "Installer package for the data files. The bombermaaan package is required, too.",
		),
		array(
		"bombermaaan_1.4.0-1_amd64.deb",
		"Debian package for AMD64",
        "Installer package. The bombermaaan-data package is required, too.",
		),
		array(
		"bombermaaan-data_1.4.0-1_amd64.deb",
		"Debian package for AMD64",
        "Installer package for the data files. The bombermaaan package is required, too.",
		),
		array(
		"Bombermaaan_1.4.0.627_20081018_linux32.tar.gz",
		"Tar.gz file for Linux 32 bit",
        "Simple play Bombermaaan without installing it. Just extract all files to a folder and run Bombermaaan.",
		),
		array(
		"Bombermaaan_1.4.0.627_20081018_linux64.tar.gz",
		"Tar.gz file for Linux 64 bit",
        "Simple play Bombermaaan without installing it. Just extract all files to a folder and run Bombermaaan.",
		),
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

<h2><a id="stable">The current stable version is 1.4</a></h2>

<table class="downloadbox">

<tr>
<th colspan="2">Package</th>
<th>Description</th>
</tr>

<?php

foreach ( $downloads[ "stable" ] as $item ) {

	$file = $item[ 0 ];
	$text = $item[ 1 ];
    $desc = $item[ 2 ];

?>	
<tr>
<td>
<a href="http://downloads.sourceforge.net/bombermaaan/<? echo htmlentities( $file ); ?>?download"><?php echo htmlentities( $file ); ?></a>
</td>
<td>
<?php echo htmlentities( $text ); ?>
</td>
<td>
<?php echo htmlentities( $desc ); ?>
</td>
</tr>

<?

}  // foreach ( ... )

?>

</table>

<p>
<strong>The Linux files will be added soon!</strong>
</p>

<p>
You can view the <a href="https://sourceforge.net/project/shownotes.php?release_id=634161&amp;group_id=81520">release notes</a> (including MD5 and SHA1 checksums) on the <a href="https://sourceforge.net/project/showfiles.php?group_id=81520">download page</a> on SourceForge.net.
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
You can view the release notes. Check for the <img src="https://s.fsdn.com/sf/images/phoneix/icons/tango/edit-paste.png" alt="Release notes icon" /> icon near the release name. 
You will also find the MD5 and SHA1 checksums there.
</p>

<h2><a id="sourcecode">Source code</a></h2>

<p>
The source code is hosted in the Subversion repository on SourceForge.net. 
If you have <a href="http://tortoisesvn.net/">TortoiseSVN</a> installed, you can check out the <a href="tsvn:https://bombermaaan.svn.sourceforge.net/svnroot/bombermaaan/trunk">whole sourcecode</a> by clicking on the weblink.
</p>

<p>
You can also download the source code of Bombermaaan in a single .zip and .tar.gz file. 
See the <code>*_src.zip</code> and <code>*_src.tar.gz</code> files
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
