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


AnalyizePicture( "stunt-front-32.png" );
AnalyizePicture( "stunt-back-32.png" );
AnalyizePicture( "stunt-side-32.png" );


function AnalyizePicture( $fname ) {

	$img_in = ImageCreateFromPNG( $fname );

	$sizex = imagesx( $img_in );
	$sizey = imagesy( $img_in );

	for ( $x = 0; $x < $sizex; $x ++ ) {
		for ( $y = 0; $y < $sizey; $y++ ) {
		
			$color = imagecolorat( $img_in, $x, $y );
			$allcolors[ mydechex( $color ) ] ++;
			
		}
	}

	imagedestroy( $img_in );

	print_r( $allcolors );

}


function mydechex( $dec ) {

	$str = "000000" . dechex( $dec );
	return substr( $str, -6 );

}


?>

