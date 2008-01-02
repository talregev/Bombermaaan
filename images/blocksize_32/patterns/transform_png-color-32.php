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


if ( count( $_SERVER["argv"] ) != 5 ) {
	die( "Usage: transform_png-color-32.php  file-in.png  file-out.png  color-from  color-to\nExample: transform_png-color-32.php  pic.png  out.png  ff0000  ee9999\n" );
}
	

$transform = array(
	$_SERVER["argv"][3] . "	" . $_SERVER["argv"][4],
);


TransformPicture( $_SERVER["argv"][1], $_SERVER["argv"][2], $transform );


function TransformPicture( $inputfname, $outputfname, $transform ) {

	$img = ImageCreateFromPNG( $inputfname );
    Imagesavealpha( $img, true );
	
	$sizex = imagesx( $img );
	$sizey = imagesy( $img );

	for ( $x = 0; $x < $sizex; $x ++ ) {
		for ( $y = 0; $y < $sizey; $y++ ) {

			$color = imagecolorat( $img, $x, $y );
			$allcolors[ dechex( $color ) ] ++;

			$blue = 0x0000ff & $color;
			$green = ( 0x00ff00 & $color ) >> 8;
			$red = (0xff0000 & $color ) >> 16;

			foreach ( $transform as $line ) {

				list ( $from, $to ) = split( "\t", $line );
				list ( $fr, $fg, $fb ) = sscanf( $from, '%2x%2x%2x' );

				if ( $blue == $fb and $red == $fr and $green == $fg ) {
					imagesetpixel( $img, $x, $y, hexdec( $to ) );
				}
			}
		}
	}

	ImagePNG( $img, "$outputfname" );

	imagedestroy( $img );

	print_r( $allcolors );

}

?>

