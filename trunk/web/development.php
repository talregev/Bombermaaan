<?php

include_once( "inc/webpage.php" );


$webpage = new WebPage();
$webpage->head();

?>

<h1>Development</h1>

<div id="content">

<h2>General</h2>

<p>
Bombermaaan is written in C++ and hosted on SourceForge.net. Bombermaaan should run on all 32-bit MS Windows operating systems.
</p>

<h2>Links to SourceForge.net</h2>

<ul>
<li><a href="https://sourceforge.net/projects/bombermaaan/">Project page</a></li>
<li><a href="https://sourceforge.net/project/showfiles.php?group_id=81520">Download section</a></li>
<li><a href="http://bombermaaan.svn.sourceforge.net/viewvc/bombermaaan/">Subversion repository</a></li>
</ul>

<h2>Compile Bombermaaan by yourself</h2>

<p>
There is a (incomplete so far) <a href="http://bombermaaan.svn.sourceforge.net/viewvc/*checkout*/bombermaaan/trunk/docs/how-to-compile.txt?revision=152">how-to guide</a> you can use if you want to compile Bombermaaan by yourself.
Unfortunately, the image and sound files are not in the subversion repository yet. You can get them from the source package, though.
This is true for the small sprites (16 pixels per block). You can delete the RES32 project from your VC++ solution to get Bombermaaan compiled.
The RES32 project generates the DLL for the larger sprites (32 pixels per block).
</p>

</div>

<?php

$webpage->tail();

?>
