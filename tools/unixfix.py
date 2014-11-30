import os
import os.path

def unixfix(path):
	for dirpath, dirnames, filenames in os.walk(path):
		for filename in filenames:
			abspath = os.path.join(dirpath, filename)
			os.system('sed -i.bak \'s.\\\.\/.g\' ' + abspath)

unixfix('include')
unixfix('src')
