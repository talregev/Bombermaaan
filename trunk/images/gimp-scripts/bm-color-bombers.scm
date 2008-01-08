;/************************************************************************************
;
;    Copyright (C) 2008 Bernd Arnold
;
;    This file is part of Bombermaaan.
;
;    Bombermaaan is free software: you can redistribute it and/or modify
;    it under the terms of the GNU General Public License as published by
;    the Free Software Foundation, either version 3 of the License, or
;    (at your option) any later version.
;
;    Bombermaaan is distributed in the hope that it will be useful,
;    but WITHOUT ANY WARRANTY; without even the implied warranty of
;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;    GNU General Public License for more details.
;
;    You should have received a copy of the GNU General Public License
;    along with Bombermaaan.  If not, see <http://www.gnu.org/licenses/>.
;
;************************************************************************************/


(define (bm-color-bombers filename outfilename)

   (let* (
			(image (car (gimp-file-load RUN-NONINTERACTIVE filename filename)))
			(drawable (car (gimp-image-get-active-layer image)))
          )
		  
		(bm-fill-layer-with-color image "Helmet" '(0 110 255))
		(bm-fill-layer-with-color image "Anzug_DE" '(0 110 255))
		
		(gimp-image-merge-visible-layers image CLIP-TO-BOTTOM-LAYER)
		(gimp-file-save RUN-NONINTERACTIVE image (car (gimp-image-get-active-drawable image)) outfilename outfilename)
		(gimp-image-delete image)
	)

)



(define (bm-fill-layer-with-color image fillLayerName fillColor)

   (let* (
		(drawable (car (gimp-image-get-active-layer image)))
		(allLayers (cadr (gimp-image-get-layers image)))
		(layersCount (car (gimp-image-get-layers image)))
		(index 0)
          )
		  
		(while (< index layersCount)
			(let*
				(
					(thisLayer (aref allLayers index))
					(layerName (car (gimp-drawable-get-name thisLayer)))
				)
				
				(if (equal? layerName fillLayerName)
				(begin
					(gimp-selection-layer-alpha thisLayer)
					(gimp-context-set-background fillColor)
					(gimp-edit-fill thisLayer BACKGROUND-FILL)
				)
				)

				(set! index (+ index 1))
				
			)
		)
		
	)

)