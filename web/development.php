<?php

include_once( "inc/webpage.php" );


$webpage = new WebPage();
$webpage->head();

?>

<h1>Contact</h1>

<div id="content">

<h2>Development</h2>

<p>
Bombermaaan is written in C++ and hosted on SourceForge.net.
</p>

<h2>Links to SourceForge.net</h2>

<ul>
<li><a href="https://sourceforge.net/projects/bombermaaan/">Project page</a></li>
<li><a href="https://sourceforge.net/project/showfiles.php?group_id=81520">Download section</a></li>
<li><a href="http://bombermaaan.svn.sourceforge.net/viewvc/bombermaaan/">Subversion repository</a></li>
</ul>

</div>

<?php

$webpage->tail();

?>
