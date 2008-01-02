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


$transform_basic = array(
	"717171	ff4800",		// Eyes around
	"959595	ff9000",		// Eyes between
	"636363	fefefe",		// White of eyes
	"8b8b8b	00b0ff",		// Inner
	"676767	0068ff",		// Outer
	"2f2f2f	dfd8df",		// Color 1
	"4d4d4d	fff8ff",		// Color 2
	"979797	ff9400",
);

$colorarray = array();

// Player 0 - white
$colorarray[] = array(
	"dedede	dfd8df",		// Helmet bright 80%
	"b5b5b5	b0b0b0",		// Helmet bright 60%
	"fcfcfc	fdfdfd",		// Helmet bright 100%
	"949494	909090",		// Helmet bright 40%
	"707070	ff00b0",		// Shoes etc.
	"727272	ff00b0",		// Shoes etc.
);

// Player 1 - black
$colorarray[] = array(
	"dedede	000000",		// Helmet bright 80%
	"b5b5b5	000000",		// Helmet bright 60%
	"fcfcfc	000000",		// Helmet bright 100%
	"949494	000000",		// Helmet bright 40%
	"707070	00b521",		// Shoes etc.
	"727272	00b521",		// Shoes etc.
);

// Player 2 - red
$colorarray[] = array(
	"dedede	b50000",		// Helmet bright 80%
	"b5b5b5	b50000",		// Helmet bright 60%
	"fcfcfc	ff0000",		// Helmet bright 100%
	"949494	940000",		// Helmet bright 40%
	"707070	00b521",		// Shoes etc.
	"727272	00b521",		// Shoes etc.
);

// Player 3 - blue
$colorarray[] = array(
	"dedede	0000b5",		// Helmet bright 80%
	"b5b5b5	0000b5",		// Helmet bright 60%
	"fcfcfc	0000ff",		// Helmet bright 100%
	"949494	000094",		// Helmet bright 40%
	"707070	00b521",		// Shoes etc.
	"727272	00b521",		// Shoes etc.
);

// Player 4 - green
$colorarray[] = array(
	"dedede	00b500",		// Helmet bright 80%
	"b5b5b5	00b500",		// Helmet bright 60%
	"fcfcfc	00f000",		// Helmet bright 100%
	"949494	009400",		// Helmet bright 40%
	"707070	ff00b0",		// Shoes etc.
	"727272	ff00b0",		// Shoes etc.
);


$transparency_to_color = "00ff00";

$pictures = array(
	"stunt-front",
	"stunt-side",
	"stunt-back",
);


foreach ( $colorarray as $key => $colortable ) {

	$merge = array_merge($transform_basic, $colortable );
	
	foreach ( $pictures as $picname ) {
		TransFormPicture( "$picname-32.png", "output_$picname-$key-32.png", $merge, $transparency_to_color );
	}

}

function TransFormPicture( $inputfname, $outputfname, $transform, $backgroundcolor ) {

	$img_in = ImageCreateFromPNG( $inputfname );

	$sizex = imagesx( $img_in );
	$sizey = imagesy( $img_in );

	$img_out = @ImageCreateTrueColor( $sizex, $sizey )
	      or die ( "Cannot create image handle." );

    imagefill( $img_out, 0, 0, hexdec( $backgroundcolor ) );
	
	ImageCopy( $img_out, $img_in, 0, 0, 0, 0, $sizex, $sizey );

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

	ImagePNG( $img_out, "out/$outputfname" );

	imagedestroy( $img_in );
	imagedestroy( $img_out );

	print_r( $allcolors );

}

?>

