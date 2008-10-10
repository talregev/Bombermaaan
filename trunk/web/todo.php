<?php

include_once( "inc/webpage.php" );


$webpage = new WebPage();
$webpage->head();

?>

<h1>Bombermaaan To-Do list</h1>

<div id="content">

<p>
This list shows the ideas we had and don't want to forget.
</p>

<p>
You can also browse a list of already <a href="http://sourceforge.net/tracker2/?func=browse&amp;group_id=81520&amp;atid=563213&amp;status=1&amp;category=531297">opened feature requests</a> at the SourceForge.net tracker.
</p>

<table>

<tr>
<th>Item</th>
<th>Progress</th>
<th>Status&nbsp;<sup>1</sup></th>
<th>Description</th>
<th>Added&nbsp;<sup>2</sup></th>
<th>Last changed <sup>2</sup></th>
</tr>

<tr>
<td>Adjustable items in walls and bomber skills on a per-level basis</td>
<td>100 %</td>
<td>Completed</td>
<td>The amount of items in walls and the initial bomber skills can set in each level file.<br />Tracker items 1847047 and 1847048.</td>
<td>2007-12</td>
<td>2007-12-18</td>
</tr>

<tr>
<td>Blocks where bombs start moving/change direction</td>
<td>100 %</td>
<td>Completed</td>
<td>There are certain blocks in the arena. When a bomber puts a bomb there or when a moving bomb arrives there, the bomb begins moving or changes the direction. Tracker item <a href="https://sourceforge.net/tracker/index.php?func=detail&amp;aid=1908105&amp;group_id=81520&amp;atid=563213">1908105</a>.<br />Available in version 1.3 (stable), released 2008-05-07.</td>
<td>2007-12-10</td>
<td>2008-03-20</td>
</tr>

<tr>
<td>More than two keyboard inputs</td>
<td>100 %</td>
<td>Completed</td>
<td>Since you can plug many USB keyboards, it could be possible to have five human players in the same game. So allow Keyboard 3 to Keyboard 5 in the input selection screen.See tracker item <a href="https://sourceforge.net/tracker/index.php?func=detail&amp;aid=2150405&amp;group_id=81520&amp;atid=563213">2150405</a>.</td>
<td>2007-12-10</td>
<td>2008-10-10</td>
</tr>

<tr>
<td>Remote control lets bombs explode</td>
<td>100 %</td>
<td>Completed</td>
<td>A new item can be picked up by the bombers to let the players decide whether they want their bomb explode before the default time ends. This shouldn't work when the bomber is contaminated with the &quot;long bomb explode time&quot; and the "short bomb explode time&quot;.</td>
<td>2007-12-13</td>
<td>2008-10-10</td>
</tr>

<tr>
<td>Share maps</td>
<td>100 %</td>
<td>Completed</td>
<td>A common place where maps can be shared. (by Hugues, see tracker item <a href="https://sourceforge.net/tracker/index.php?func=detail&amp;aid=1941534&amp;group_id=81520&amp;atid=563213">1941534</a>). Have a look at the web-site.</td>
<td>2008-04-16</td>
<td>2008-10-10</td>
</tr>

<tr>
<td>Skins</td>
<td>0 %</td>
<td>Noticed</td>
<td>Skins with different images.</td>
<td>2007-12-10</td>
<td>2007-12-10</td>
</tr>

<tr>
<td>Team mode</td>
<td>0 %</td>
<td>Noticed</td>
<td>Players can be assigned to teams. The match is finished if there is only one team alive. In addition, there could be an option if item effects are shared in a team.<br />The disease could be shared, too. (by Hugues, see tracker item <a href="https://sourceforge.net/tracker/index.php?func=detail&amp;aid=1941534&amp;group_id=81520&amp;atid=563213">1941534</a>)</td>
<td>2007-12-11</td>
<td>2008-04-16</td>
</tr>

<tr>
<td>Retain bomber skills between matches</td>
<td>0 %</td>
<td>Noticed</td>
<td>Bomber skills are reset each time a match starts. What about an option where the bombers keep their skills between matches?</td>
<td>2007-12-13</td>
<td>2007-12-13</td>
</tr>

<tr>
<td>Wormhole / Teleport square</td>
<td>0 %</td>
<td>Noticed</td>
<td>Wormhole: There could be blocks when a bomber gets on it, the bomber vanishes from there and about 
half a second later it re-appears on another block.<br />
Teleport square: When bomb / users on this special square it teleports/transport the bomb/users to 
another square (random or otherwise).
(by Di, see tracker item <a href="https://sourceforge.net/tracker/index.php?func=detail&amp;aid=1949707&amp;group_id=81520&amp;atid=563213">1949707</a>)</td>
<td>2007-12-28</td>
<td>2007-12-28</td>
</tr>

</table>

<p>
Notes:
<br />
<sup>1</sup>
Noticed: idea is written down, but it isn't intended to be implemented (until now),
Planned: idea is intended to be implemented,
In Progress: currently working on implementation,
Completed: idea is implemented,
Rejected: idea will not be implemented.
<br />
<sup>2</sup>
Date is given in <a href="http://en.wikipedia.org/wiki/ISO_8601">ISO 8601</a> format, this is yyyy-mm-dd.
</p>

</div>

<?php

$webpage->tail();

?>
