#!/bin/bash

function usage() {
    echo "Bad or missing argument!" 
    echo "Usage: $0 -g <dir> -b <dir> -c compiler"
    echo "		-g <dir> : Git Base directory"
    echo "		-b <dir> : Build directory."
    echo "		-c [gcc/clang] : Set the cross compiler"
}

if [ "$1" == "" ]; then
    usage
    exit 0
fi

while getopts ":g:b:c:p:" optname
  do
	case "$optname" in
	  "g")    
	        PROJECT_DIR="$OPTARG"
	  	;;
	  "b")   
            BUILD_DIR="$OPTARG"
	  	;;
	  "c")    
            COMPILER="$OPTARG"
	  	;;
        "p")
            COMPILER_PATH="$OPTARG"
          ;;
	   *) 
	        usage
	   exit 0
	    ;;
	esac
done

if [ ! -d "$COMPILER_PATH" ]; then
    echo "Path to the compiler does not exist"
    exit 0
fi

if [[ $COMPILER =~ ^(gcc|clang)$ ]]; then
    if [ $COMPILER == "gcc" ]; then
        export CROSS_GCC_COMPILER_PATH=$COMPILER_PATH
    elif [ $COMPILER == "clang" ]; then
        export CROSS_LLVM_COMPILER_PATH=$COMPILER_PATH
    fi
else
    echo "Either no compiler or an unsupported one was entered"
	usage
	exit 0
fi

if [ -d "$BUILD_$COMPILER" ]; then
	rm -rf "$BUILD_DIR_$COMPILER"/*
else
	mkdir "$BUILD_DIR_$COMPILER"
fi

cd $BUILD_DIR

cmake -DCMAKE_TOOLCHAIN_FILE=$PROJECT_DIR/cmake/toolchain/$COMPILER-arm-toolchain.cmake $PROJECT_DIR

