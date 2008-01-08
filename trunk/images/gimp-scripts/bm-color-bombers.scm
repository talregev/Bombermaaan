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

; This file sets the different colors for the bombers
; and generates a file for each color

; Usage: (for example)
; gimp-2.4.exe -f -i -b '(bm-color-bombers "arena_bomber_death_sprite0.xcf" "1")' -b '(gimp-quit 1)'


(define (bm-color-bombers filename)

   (let* (
			dummy
          )
		  
	(bm-change-color-in-file filename "2" '(255 0 0))
	
	)
	
)


(define (bm-change-color-in-file filename bnr color)

   (let* (
			(image (car (gimp-file-load RUN-NONINTERACTIVE filename filename)))
			(drawable (car (gimp-image-get-active-layer image)))
			(outfilename "")
          )
		
		(bm-fill-layer-with-color image "Helmet" color)
		(bm-fill-layer-with-color image "Anzug_DE" color)
		
		(set! outfilename (string-append "../_generated/_" (unbreakupstr (butlast (strbreakup filename ".")) ".") "_bomber-" bnr ".png"))
	
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