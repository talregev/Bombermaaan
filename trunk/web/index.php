<?php

include_once( "inc/webpage.php" );


$webpage = new WebPage();
$webpage->head();

?>

<h1>Bombermaaan game project on sourceforge.net</h1>

<div id="content">

<h2>Introduction</h2>

<p>
Bombermaaan is a classic bomberman game. It runs stable on Win32 and - very soon - on Linux, too. You can 
already try the experimental release on Linux.
</p>

<p>
<a href="download.php">Download Bombermaaan now!</a>
</p>

<h2>Stay informed</h2>

<p>
<a href="http://sourceforge.net/export/rss2_projnews.php?group_id=81520" class="feed">News releases</a><br />
<a href="http://sourceforge.net/export/rss2_projfiles.php?group_id=81520" class="feed">File releases</a><br />
</p>

<p>
You can also view the full <a href="https://sourceforge.net/export/rss2_project.php?group_id=81520">list of RSS feeds</a>.
</p>

<p>
SourceForge.net provides <strong>monitoring</strong> of discussion forums, tracker items and file releases.
If you would like to monitor new file releases of Bombermaaan, just go to the <a href="https://sourceforge.net/project/showfiles.php?group_id=81520">download page</a> and click on the <i>Monitor this package</i> icon.
You can read further informations and view your current monitored items on <a href="https://sourceforge.net/my/monitor.php">your SourceForge.net page</a>.
</p>

</div>

<?php

$webpage->tail();

?>
