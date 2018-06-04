./dcc < samples/baddouble.frag > samples/mybaddouble.out
./dcc < samples/badbool.frag > samples/mybadbool.out
./dcc < samples/badident.frag > samples/mybadident.out
./dcc < samples/badint.frag > samples/mybadint.out
./dcc < samples/badop.frag > samples/mybadop.out
./dcc < samples/badpre.frag > samples/mybadpre.out
./dcc < samples/badreserve.frag > samples/mybadreserve.out
./dcc < samples/badstring.frag > samples/mybadstring.out
./dcc < samples/comment.frag > samples/mycomment.out
./dcc < samples/define.frag > samples/mydefine.out
./dcc < samples/ident.frag > samples/myident.out
./dcc < samples/number.frag > samples/mynumber.out
./dcc < samples/program2.decaf > samples/myprogram2.out
./dcc < samples/program3.decaf > samples/myprogram3.out
./dcc < samples/reserve_op.frag > samples/myreserve_op.out
./dcc < samples/string.frag > samples/mystring.out

diff -w samples/baddouble.out samples/mybaddouble.out -I "*** "[^]*
diff -w samples/badbool.out samples/mybadbool.out
diff -w samples/badident.out samples/mybadident.out -I "*** "[^]*
diff -w samples/badint.out samples/mybadint.out
diff -w samples/badop.out samples/mybadop.out
diff -w samples/badpre.out samples/mybadpre.out
diff -w samples/badreserve.out samples/mybadreserve.out
diff -w samples/badstring.out samples/mybadstring.out
diff -w samples/comment.out samples/mycomment.out
diff -w samples/define.out samples/mydefine.out
diff -w samples/ident.out samples/myident.out
diff -w samples/number.out samples/mynumber.out
diff -w samples/program2.out samples/myprogram2.out
diff -w samples/program3.out samples/myprogram3.out
diff -w samples/reserve_op.out samples/myreserve_op.out
diff -w samples/string.out samples/mystring.out
