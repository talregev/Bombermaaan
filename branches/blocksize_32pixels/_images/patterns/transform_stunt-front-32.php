<?php

/************************************************************************************

    Copyright (C) 2007 Bernd Arnold

    This file is part of Bombermaaan.

    Bombermaaan is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Bombermaaan is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Bombermaaan.  If not, see <http://www.gnu.org/licenses/>.

************************************************************************************/


$img_in = ImageCreateFromPNG( "stunt-front-32.png" );

$sizex = imagesx( $img_in );
$sizey = imagesy( $img_in );

$img_out = @ImageCreateTrueColor( $sizex, $sizey )
      or die ( "Cannot create image handle." );


ImageCopy( $img_out, $img_in, 0, 0, 0, 0, $sizex, $sizey );

$transform = array(
 "ff0000	00ff00",		// Transparency
 "dbdbdb	dfd8df",		// Helmet bright 80%
 "b0b0b0	b0b0b0",		// Helmet bright 60%
 "fcfcfc	fdfdfd",		// Helmet bright 100%
 "909090	909090",		// Helmet bright 40%
 "717171	ff4800",		// Eyes around
 "959595	ff9000",		// Eyes between
 "707070	ff00b0",		// Shoes etc.
 "949494	fefefe",		// White of eyes
 "8b8b8b	00b0ff",		// Inner
 "676767	0068ff",		// Outer
 "2f2f2f	dfd8df",		// Color 1
 "4d4d4d	fff8ff",		// Color 2
);



for ( $x = 0; $x < $sizex; $x ++ ) {
	for ( $y = 0; $y < $sizey; $y++ ) {

		$color = imagecolorat( $img_in, $x, $y );
		$allcolors[ dechex( $color ) ] ++;

		$blue = 0x0000ff & $color;
		$green = ( 0x00ff00 & $color ) >> 8;
		$red = (0xff0000 & $color ) >> 16;

		foreach ( $transform as $line ) {

			list ( $from, $to ) = split( "\t", $line );
			list ( $fr, $fg, $fb ) = sscanf( $from, '%2x%2x%2x' );

			if ( $blue == $fb and $red == $fr and $green == $fg ) {
				imagesetpixel( $img_out, $x, $y, hexdec( $to ) );
			}
		}
	}
}

ImagePNG( $img_out, "output_stunt-front-32.png" );

imagedestroy( $img_in );
imagedestroy( $img_out );

print_r( $allcolors );

?>

