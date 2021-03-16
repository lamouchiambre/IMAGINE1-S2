#!/bin/sh
bindir=$(pwd)
cd /home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/TP4 - Transformations-20210316/TP4_code/TP4_transformations/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "xYES" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		/usr/bin/gdb -batch -command=$bindir/gdbscript --return-child-result /home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/TP4\ -\ Transformations-20210316/TP4_code/build/TP4_transformations 
	else
		"/home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/TP4\ -\ Transformations-20210316/TP4_code/build/TP4_transformations"  
	fi
else
	"/home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/TP4\ -\ Transformations-20210316/TP4_code/build/TP4_transformations"  
fi
