TEX=rubber -d
TEXs=$(wildcard *.tex)
PDFs=$(TEXs:.tex=.pdf)
default: $(PDFs)
clean:
	rm -f *.blg *.log *.out *.aux *.toc *.bbl *.mtc* *.maf *.lof *.lot *.som *.pdf chapters/*.aux
keeppdf:
	rm -f *.blg *.log *.out *.aux *.toc *.bbl *.mtc* *.maf *.lof *.lot *.som chapters/*.aux
%.pdf: %.tex
	$(TEX) $<
