#
# Makefile to generate the HTML pages of the tutorial.
#

all :
	$(foreach file, $(wildcard *.gmd), make $(basename $(file)).html;)

%.html: %.gmd
	gmic it $< gmd2html strvar d strvar "{b}" out=\$$\{\} ot \$$out.html

clean:
	rm -f *.html *~
