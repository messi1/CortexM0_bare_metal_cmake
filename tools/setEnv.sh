#!/bin/bash

function generateProcessorList() {
    if [  -n "$SOURCE_DIR" ]
    then
        PROCESSOR_LIST=($(ls -d $SOURCE_DIR/cmake/processor/* | xargs basename -a | cut -d "." -f 1))
    else
        PROCESSOR_LIST="empty list"
    fi
}

function usage() {
    generateProcessorList

    echo "Bad or missing argument!" 
    echo "Usage: $0 -g <dir> -b <dir> -c compiler"
    echo "		-g <dir> : Source directory"
    echo "		-b <dir> : Build directory"
    echo "		-c <dir> : Path to the compiler"
    echo "		-p <processor> : "${PROCESSOR_LIST[*]}

}

if [ "$1" == "" ]; then
    usage
    exit 0
fi

while getopts ":g:b:c:p:" optname
  do
    case "$optname" in
        "g")
            SOURCE_DIR="$OPTARG"
            generateProcessorList
        ;;
        "b")
            BASE_BUILD_DIR="$OPTARG"
        ;;
        "c")
            COMPILER_PATH="$OPTARG"
        ;;
        "p")
            PROCESSOR="$OPTARG"
        ;;
        *)
            usage
            exit 0
        ;;
    esac
done

if [[ "${SOURCE_DIR:0:1}" != / && "${SOURCE_DIR:0:2}" != ~[/a-z] ]]
then
    SOURCE_DIR=$(realpath $SOURCE_DIR)
fi


if [ -d "$COMPILER_PATH" ];
then
    if [ -f "$COMPILER_PATH/bin/arm-none-eabi-g++" ];
    then
        COMPILER="gcc"
    elif [ -f "$COMPILER_PATH/bin/clang" ];
    then
        COMPILER="clang"
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
else
    echo "Path to the compiler does not exist"
    usage
    exit 0
fi

# Check if the entered processor is supported
for i in "${PROCESSOR_LIST[@]}"
do
    if [ "$i" == "$PROCESSOR" ] ; then
        PROCESSOR_FOUND="yes"
    fi
done

if [[ "$PROCESSOR_FOUND" != "yes" ]]
then
    echo "Processor $PROCESSOR is not supported"
    usage
    exit 0
fi

BUILD_DIR=$BASE_BUILD_DIR"_"$PROCESSOR"_"$COMPILER

if [ -d $BUILD_DIR ]; then
    rm -rf $BUILD_DIR/*
else
    mkdir $BUILD_DIR
    echo "Created directory "$BUILD_DIR
fi

cd $BUILD_DIR

echo "cmake -DPROCESSOR_CONFIG=$PROCESSOR -DCMAKE_TOOLCHAIN_FILE=$SOURCE_DIR/cmake/toolchain/$COMPILER-arm-toolchain.cmake $SOURCE_DIR"
cmake -DPROCESSOR_CONFIG=$PROCESSOR -DCMAKE_TOOLCHAIN_FILE=$SOURCE_DIR/cmake/toolchain/$COMPILER-arm-toolchain.cmake $SOURCE_DIR

exec bash

