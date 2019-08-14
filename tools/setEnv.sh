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

while [ "$1" != "" ]; do
    PARAM=`echo $1 | awk -F= '{print $1}'`
    VALUE=`echo $1 | awk -F= '{print $2}'`
    case $PARAM in
        -h | --help)
            usage
            exit
            ;;
        -g)
            PROJECT_DIR=$VALUE
            ;;
        -b)
            BUILD_DIR=$VALUE
            ;;
        -c)
            COMPILER=$VALUE
            ;;
        *)
            echo "ERROR: unknown parameter \"$PARAM\""
            usage
            exit 1
            ;;
    esac
    shift
done

while getopts ":g:b:c" optname
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
	   *) 
	        usage
	   exit 0
	    ;;
	esac
done


# Change the path of the cross toolchain to the path of your system 
export CROSS_GCC_COMPILER_PATH=/usr/local/gcc-arm-none-eabi-8-2018-q4-major
export CROSS_LLVM_COMPILER_PATH=/usr/local/clang_8.0.0/

if [ $COMPILER != "gcc" ] || [ $COMPILER != "clang" ]; then
	usage
	exit 0
fi


if [ -d "$BUILD_$COMPILER" ]; then
	rm -rf "$BUILD_DIR_$COMPILER"/*
else
	mkdir "$BUILD_DIR_$COMPILER"
fi

cmake -DCMAKE_TOOLCHAIN_FILE=$PROJECT_DIR/cmake/$COMPILER-arm-toolchain.cmake $BUILD_DIR

