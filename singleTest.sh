#!/bin/sh

ADDTION='gdb --args'

if [ -z "$GDB" ]; then
	ADDTION= 
fi

if [ -z "$TARGET" ];then
	echo "You need to set target nanoapp"
else
	if [ -z "$WASM" ];then
		echo "Testing Wasm Nanoapp"
		$ADDTION ./out/google_x86_linux_debug/libchre --no_static_nanoapps --nanoapp ./apps/$TARGET/$TARGET.wasm
	else
		echo "Testing Native Nanoapp"
		$ADDTION ./out/google_x86_linux_debug/libchre --no_static_nanoapps --nanoapp ./apps/$TARGET/out/google_x86_linux/$TARGET.so
	fi
fi
		
