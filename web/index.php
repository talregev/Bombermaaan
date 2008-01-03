<?php

include_once( "inc/webpage.php" );


$webpage = new WebPage();
$webpage->head();

?>

<h1>Bombermaaan game project on sourceforge.net</h1>

<div id="content">

<h2>Introduction</h2>

<p>
Bombermaaan is a classic bomberman game. Thibaut Tollemer started this
project on July 2000. He's been using this project as a demo of what he 
could do as a game programmer, in order to be hired.
</p>

<p>
As he was hired, he published the source code and created a project space on sourceforge.net on May 2003. Unfortunately, he doesn't have so much time for programming new features now. Therefore, Bernd Arnold is going to enhance Bombermaaan and develop new features in his spare time. He joined the project in the end of 2007.
</p>

<h2>Resources</h2>

You may want to view ...

<ul>
<li><a href="http://fury94.free.fr/">Thibaut's original project page</a></li>
<li>the <a href="https://sourceforge.net/projects/bombermaaan/">project page on sourceforge.net</a></li>
<li>the <a href="https://sourceforge.net/project/showfiles.php?group_id=81520">download section on sourceforge.net</a></li>
<li>the <a href="http://bombermaaan.svn.sourceforge.net/viewvc/bombermaaan/">subversion repository</a> on sourceforge.net</li>
<li>the <a href="http://bombermaaan.svn.sourceforge.net/viewvc/*checkout*/bombermaaan/trunk/docs/Readme.html?revision=5&amp;pathrev=5">README file</a> (very latest version out of the subversion repository)</li>
</ul>

<h2>Stay informed</h2>

<p>
<a href="http://sourceforge.net/export/rss2_projnews.php?group_id=81520" class="feed">News releases</a><br />
<a href="http://sourceforge.net/export/rss2_projfiles.php?group_id=81520" class="feed">File releases</a><br />
</p>

<p>
You can also view the full <a href="https://sourceforge.net/export/rss2_project.php?group_id=81520">list of RSS feeds</a>.
</p>

</div>

<?php

$webpage->tail();

?>
