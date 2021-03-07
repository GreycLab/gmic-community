#
# Makefile to generate the HTML pages of the tutorial.
#

all :
	$(foreach file, $(wildcard *.gmd), make $(basename $(file)).html;)

%.html: %.gmd
	gmic it $< gmd2html 2 ot {n}

clean:
	rm -f *.html *~
