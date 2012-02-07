TEMPLATE = subdirs
SUBDIRS = daemon client

rules.path = $$(DESTDIR)/etc/smack/accesses.d
rules.files = smack-demo.rules

INSTALLS += rules
