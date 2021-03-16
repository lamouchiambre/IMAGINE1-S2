#!/bin/sh
bindir=$(pwd)
cd /home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/TP3 - Pipeline graphique/TP3 - Pipeline graphique-20210209/TP3_GLSL/TP3_shaders/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "xYES" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		/usr/bin/gdb -batch -command=$bindir/gdbscript --return-child-result /home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/TP3\ -\ Pipeline\ graphique/TP3\ -\ Pipeline\ graphique-20210209/TP3_GLSL/build/TP3_shaders 
	else
		"/home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/TP3\ -\ Pipeline\ graphique/TP3\ -\ Pipeline\ graphique-20210209/TP3_GLSL/build/TP3_shaders"  
	fi
else
	"/home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/TP3\ -\ Pipeline\ graphique/TP3\ -\ Pipeline\ graphique-20210209/TP3_GLSL/build/TP3_shaders"  
fi
