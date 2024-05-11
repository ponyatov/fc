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

# package
KAITAI_DEB = $(KAITAI)_$(KAITAI_VER)_all.deb
KAITAI_URL = https://github.com/kaitai-io/$(KAITAI)/releases/download/$(KAITAI_VER)

# src
F += $(wildcard lib/*.fs)

# all
.PHONY: all
all: $(F) $(MODULE).*proj
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
install: .config/dotnet-tools.json doc ref
	dotnet tool install fantomas
	dotnet tool update -v d \
		--ignore-failed-sources \
		--global Microsoft.dotnet-interactive \
		--add-source https://api.nuget.org/v3/index.json
.config/dotnet-tools.json:
	dotnet new  tool-manifest

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
