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
<td>Blocks where bombs start moving/change direction</td>
<td>0 %</td>
<td>Noticed</td>
<td>There are certain blocks in the arena. When a bomber puts a bomb there or when a moving bomb arrives there, the bomb begins moving or changes the direction.</td>
<td>2007-12-10</td>
<td>2007-12-10</td>
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
<td>More than two keyboard inputs</td>
<td>0 %</td>
<td>Noticed</td>
<td>Since you can plug many USB keyboards, it could be possible to have five human players in the same game.</td>
<td>2007-12-10</td>
<td>2007-12-10</td>
</tr>

<tr>
<td>Team mode</td>
<td>0 %</td>
<td>Noticed</td>
<td>Players can be assigned to teams. The match is finished if there is only one team alive. In addition, there could be an option if item effects are shared in a team.</td>
<td>2007-12-11</td>
<td>2007-12-11</td>
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
<td>Remote control lets bombs explode</td>
<td>0 %</td>
<td>Noticed</td>
<td>A new item can be picked up by the bombers to let the players decide whether they want their bomb explode before the default time ends. This shouldn't work when the bomber is contaminated with the &quot;long bomb explode time&quot; and the "short bomb explode time&quot;.</td>
<td>2007-12-13</td>
<td>2007-12-13</td>
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
