#!/bin/bash
#make clean
make
function print(){
    echo $'\n'
    echo "------------------------------$1------------------------------"
}
for filename in ./samples/*.decaf; do
    ./dcc < $filename > ./parser_test.txt 2>&1
    EXE_ANS="${filename%.*}.out"
    DIFF_RES="$(diff -w ./parser_test.txt $EXE_ANS)"

    if [ ! -z "$DIFF_RES" ]; then
        echo "$filename failed the test !"
        print reference
        more $EXE_ANS

        print "your answer"
        more ./scanner_test.txt

        print "test file"
	echo $filename
        more $filename

        print "diff result"
        echo $DIFF_RES
        break
    fi
done
