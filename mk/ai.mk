.PHONY: ai tmp/$(APP).ai.md
ai: tmp/$(APP).ai.md
tmp/$(APP).ai.md:
	-cat doc/*.md                       > $@
	-cat inc/* src/*                   >> $@
	-cat vscode/*.json                 >> $@
	-cat os/linux/inc/* os/linux/src/* >> $@
