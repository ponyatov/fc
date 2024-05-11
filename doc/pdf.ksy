# https://github.com/arlac77/kaitai-pdf/blob/master/pdf.ksy
meta:
  id: pdf
  title: Portable Document Format
  file-extension: pdf
  encoding: UTF-8
  endian: le
doc-ref:
  - https://www.iso.org/standard/75839.html
  - https://developer.adobe.com/document-services/docs/assets/5b15559b96303194340b99820d3a70fa/PDF_ISO_32000-2.pdf
seq:
  - id: header
    type: header
types:
  header:
    seq:
      - id: magic
        size: 5
        contents: "%PDF-"
      - id: version
        type: str
        size: 5
        terminator: 0x0D
