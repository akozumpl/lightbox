#! /usr/bin/python

import glib
from gi.importer import DynamicImporter

lb = DynamicImporter("lb").load_module(".lb")

print lb.get_test_value()
