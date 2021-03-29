#!/bin/sh
bindir=$(pwd)
cd /mnt/d/Users/user/Documents/GitHub/IMAGINE1-S2/HMIN212/TP4_system/TP4_transformations/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		GDB_COMMAND-NOTFOUND -batch -command=$bindir/gdbscript  /mnt/d/Users/user/Documents/GitHub/IMAGINE1-S2/HMIN212/TP4_system/build/TP4_transformations 
	else
		"/mnt/d/Users/user/Documents/GitHub/IMAGINE1-S2/HMIN212/TP4_system/build/TP4_transformations"  
	fi
else
	"/mnt/d/Users/user/Documents/GitHub/IMAGINE1-S2/HMIN212/TP4_system/build/TP4_transformations"  
fi
