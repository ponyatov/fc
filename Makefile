# var
MODULE = $(notdir $(CURDIR))

# version
KAITAI_VER = 0.10

# dir
CWD   = $(CURDIR)
DOC   = $(CWD)/doc
TMP   = $(CWD)/tmp
DISTR = $(HOME)/distr

# tool
CURL   = curl -L -o
KAITAI = kaitai-struct-compiler
PY     = bin/python3
PIP    = bin/pip3
JUPY   = bin/jupyter
LAB    = $(JUPY)-lab
DOT    = /usr/bin/dotnet

# package
KAITAI_DEB = $(KAITAI)_$(KAITAI_VER)_all.deb
KAITAI_URL = https://github.com/kaitai-io/$(KAITAI)/releases/download/$(KAITAI_VER)

# src
F += $(wildcard lib/*.fs)

# all
.PHONY: all
all:

.PHONY: build
build: $(F) $(MODULE).*proj
	dotnet build

.PHONY: test
test: $(F) $(MODULE).*proj
	dotnet test

# format
.PHONY: format
format: tmp/format_f
tmp/format_f: $(F)
	dotnet fantomas --force $? && touch $@

.PHONY: doc
doc: doc/PDF_ISO_32000-2.pdf

# install
.PHONY: install update ref gz
install: $(PY) $(PIP) $(LAB) $(DOT)
	$(DOT) tool install -v d -g Microsoft.dotnet-interactive
	$(DOT) tool list -g
	mkdir -p ~/.local/share/jupyter/kernels
	dotnet interactive jupyter install
	$(JUPY) kernelspec list && dotnet --version
update: $(PY) $(PIP) $(LAB) $(DOT)
	sudo apt update
	sudo apt install -uy `cat apt.txt`

$(LAB): $(PIP)
	$(PIP) install -U -r requirements.txt
$(PY) $(PIP):
	python3 -m venv .

.config/dotnet-tools.json:
	dotnet new  tool-manifest
	dotnet tool install fantomas

ref: kaitai ref/kaitai-pdf

.PHONY: pdf
pdf: tmp/pdf.html tmp/pdf.cpp

tmp/pdf.html: $(DOC)/pdf.ksy
	cd tmp ; $(KAITAI) $< -t html

tmp/pdf.cpp: $(DOC)/pdf.ksy
	cd tmp ; $(KAITAI) $< -t cpp_stl

.PHONY: kaitai
kaitai: /usr/bin/$(KAITAI) ref/kaitai-pdf

/usr/bin/$(KAITAI): $(DISTR)/SDK/$(KAITAI_DEB)
	sudo apt-get install $<
# sudo touch $@

$(DISTR)/SDK/$(KAITAI_DEB):
	$(CURL) $@ $(KAITAI_URL)/$(KAITAI_DEB)

ref/kaitai-pdf:
	git clone --depth 1 https://github.com/arlac77/kaitai-pdf.git $@

doc/PDF_ISO_32000-2.pdf:
	$(CURL) $@ https://developer.adobe.com/document-services/docs/assets/5b15559b96303194340b99820d3a70fa/PDF_ISO_32000-2.pdf
