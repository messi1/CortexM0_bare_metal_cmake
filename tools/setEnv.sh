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
    echo "Usage: $0 -s <dir> -b <dir> -c compiler"
    echo "		-s <dir> : Source directory"
    echo "		-b <dir> : Build directory"
    echo "		-c <dir> : Path to the compiler"
    echo "		-p <processor> : "${PROCESSOR_LIST[*]}

}

if [ "$1" == "" ]; then
    usage
    exit 0
fi

while getopts ":s:b:c:p:" optname
  do
    case "$optname" in
        "s")
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


if [ !-d "$COMPILER_PATH" ];
then
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

echo "cmake -DPROCESSOR_CONFIG=$PROCESSOR -DCROSS_COMPILER_PATH=$COMPILER_PATH $SOURCE_DIR"
cmake -DPROCESSOR_CONFIG=$PROCESSOR -DCROSS_COMPILER_PATH=$COMPILER_PATH $SOURCE_DIR

exec bash

