:- multifile r/5,implicit_updates/0,var2names/2,preds/2,preds/3,trans_preds/4,
   cube_size/1,start/2,error/2,error/3,refinement/1,cutpoint/1,invgen_template/2,
   invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,trans_preds/3,
   globals/2,bound_var/2,bounding_vars/2,int2pc/1,dec_data/3,transition_access/2,
   singleton/2.
refinement(inter).
cube_size(1).
var2names(p(_,data(B,C,D,E,F)), [(B,'X'),(C,b1),(D,b2),(E,x),(F,y)]).
dec_data(p(_,data(B,C,D,E,F)), [[B,C,D,E,F],[],[]], 2).
start(p(pc([[[1|1]],[[1|1]]]),data(_,_,_,_,_)), []).
error(p(pc([[[16|16]],_]),data(_,_,_,_,_)), [], 1).
error(p(pc([_,[[16|16]]]),data(_,_,_,_,_)), [], 2).
preds(_, p(_,data(_,_,_,_,_)), []).
trans_preds(_, p(_,data(_,_,_,_,_)), p(_,data(_,_,_,_,_)), []).
cutpoint([[[12|12]],_]).
cutpoint([[[10|10]],_]).
cutpoint([[[7|7]],_]).
cutpoint([[[1|1]],_]).
cutpoint([_,[[12|12]]]).
cutpoint([_,[[10|10]]]).
cutpoint([_,[[7|7]]]).
cutpoint([_,[[1|1]]]).

r(p(pc([[[4|4]],A]),data(B,C,D,_,F)), p(pc([[[3|3]],A]),data(B,C,D,K,F)), [], [K=1], (1,3)).
stmtsrc((1,3), 'x=1;').
transition_access((1,3), [_,_,_,w,_]).
r(p(pc([[[3|3]],A]),data(B,C,D,E,F)), p(pc([[[6|6]],A]),data(B,C,D,E,F)), [F+1=<0], [], (1,4)).
stmtsrc((1,4), 'assume(y < 0);').
transition_access((1,4), [_,_,_,_,r]).
r(p(pc([[[3|3]],A]),data(B,C,D,E,F)), p(pc([[[6|6]],A]),data(B,C,D,E,F)), [F>=1+0], [], (1,5)).
stmtsrc((1,5), 'assume(y > 0);').
transition_access((1,5), [_,_,_,_,r]).
r(p(pc([[[6|6]],A]),data(B,_,D,E,F)), p(pc([[[7|7]],A]),data(B,I,D,E,F)), [], [I=0], (1,6)).
stmtsrc((1,6), 'b1=0;').
transition_access((1,6), [_,w,_,_,_]).
r(p(pc([[[3|3]],A]),data(B,C,D,E,F)), p(pc([[[5|5]],A]),data(B,C,D,E,F)), [F=0], [], (1,12)).
stmtsrc((1,12), 'assume(y == 0);').
transition_access((1,12), [_,_,_,_,r]).
r(p(pc([[[5|5]],A]),data(B,C,D,E,_)), p(pc([[[8|8]],A]),data(B,C,D,E,L)), [], [L=1], (1,13)).
stmtsrc((1,13), 'y=1;').
transition_access((1,13), [_,_,_,_,w]).
r(p(pc([[[8|8]],A]),data(B,C,D,E,F)), p(pc([[[9|9]],A]),data(B,C,D,E,F)), [E+1=<1], [], (1,14)).
stmtsrc((1,14), 'assume(x < 1);').
transition_access((1,14), [_,_,_,r,_]).
r(p(pc([[[8|8]],A]),data(B,C,D,E,F)), p(pc([[[9|9]],A]),data(B,C,D,E,F)), [E>=1+1], [], (1,15)).
stmtsrc((1,15), 'assume(x > 1);').
transition_access((1,15), [_,_,_,r,_]).
r(p(pc([[[9|9]],A]),data(B,_,D,E,F)), p(pc([[[10|10]],A]),data(B,I,D,E,F)), [], [I=0], (1,16)).
stmtsrc((1,16), 'b1=0;').
transition_access((1,16), [_,w,_,_,_]).
r(p(pc([[[11|11]],A]),data(B,C,D,E,F)), p(pc([[[12|12]],A]),data(B,C,D,E,F)), [F+1=<1], [], (1,21)).
stmtsrc((1,21), 'assume(y < 1);').
transition_access((1,21), [_,_,_,_,r]).
r(p(pc([[[11|11]],A]),data(B,C,D,E,F)), p(pc([[[12|12]],A]),data(B,C,D,E,F)), [F>=1+1], [], (1,22)).
stmtsrc((1,22), 'assume(y > 1);').
transition_access((1,22), [_,_,_,_,r]).
r(p(pc([[[2|2]],A]),data(_,C,D,E,F)), p(pc([[[13|13]],A]),data(H,C,D,E,F)), [], [H=0], (1,31)).
stmtsrc((1,31), 'X=0;').
transition_access((1,31), [w,_,_,_,_]).
r(p(pc([[[13|13]],A]),data(B,C,D,E,F)), p(pc([[[16|16]],A]),data(B,C,D,E,F)), [B>=1+0], [], (1,32)).
stmtsrc((1,32), 'assume(X > 0);').
transition_access((1,32), [r,_,_,_,_]).
r(p(pc([[[13|13]],A]),data(B,C,D,E,F)), p(pc([[[14|14]],A]),data(B,C,D,E,F)), [B=<0], [], (1,33)).
stmtsrc((1,33), 'assume(X <= 0);').
transition_access((1,33), [r,_,_,_,_]).
r(p(pc([[[14|14]],A]),data(B,C,D,E,_)), p(pc([[[15|15]],A]),data(B,C,D,E,L)), [], [L=0], (1,34)).
stmtsrc((1,34), 'y=0;').
transition_access((1,34), [_,_,_,_,w]).
r(p(pc([[[1|1]],A]),data(B,_,D,E,F)), p(pc([[[4|4]],A]),data(B,I,D,E,F)), [], [I=1], (1,2)).
stmtsrc((1,2), 'b1=1;').
transition_access((1,2), [_,w,_,_,_]).
r(p(pc([[[7|7]],A]),data(B,C,D,E,F)), p(pc([[[7|7]],A]),data(B,C,D,E,F)), [F+1=<0], [], (1,8)).
stmtsrc((1,8), 'assume(y < 0);').
transition_access((1,8), [_,_,_,_,r]).
r(p(pc([[[7|7]],A]),data(B,C,D,E,F)), p(pc([[[7|7]],A]),data(B,C,D,E,F)), [F>=1+0], [], (1,9)).
stmtsrc((1,9), 'assume(y > 0);').
transition_access((1,9), [_,_,_,_,r]).
r(p(pc([[[10|10]],A]),data(B,C,D,E,F)), p(pc([[[10|10]],A]),data(B,C,D,E,F)), [D>=1], [], (1,18)).
stmtsrc((1,18), 'assume(b2 >= 1);').
transition_access((1,18), [_,_,r,_,_]).
r(p(pc([[[12|12]],A]),data(B,C,D,E,F)), p(pc([[[12|12]],A]),data(B,C,D,E,F)), [F+1=<0], [], (1,24)).
stmtsrc((1,24), 'assume(y < 0);').
transition_access((1,24), [_,_,_,_,r]).
r(p(pc([[[12|12]],A]),data(B,C,D,E,F)), p(pc([[[12|12]],A]),data(B,C,D,E,F)), [F>=1+0], [], (1,25)).
stmtsrc((1,25), 'assume(y > 0);').
transition_access((1,25), [_,_,_,_,r]).
r(p(pc([[[15|15]],A]),data(B,_,D,E,F)), p(pc([[[17|17]],A]),data(B,I,D,E,F)), [], [I=0], (1,35)).
stmtsrc((1,35), 'b1=0;').
transition_access((1,35), [_,w,_,_,_]).
r(p(pc([[[11|11]],A]),data(B,C,D,E,F)), p(pc([[[2|2]],A]),data(B,C,D,E,F)), [F=1], [], (1,28)).
stmtsrc((1,28), 'assume(y == 1);').
transition_access((1,28), [_,_,_,_,r]).
r(p(pc([[[8|8]],A]),data(B,C,D,E,F)), p(pc([[[2|2]],A]),data(B,C,D,E,F)), [E=1], [], (1,29)).
stmtsrc((1,29), 'assume(x == 1);').
transition_access((1,29), [_,_,_,r,_]).
r(p(pc([[[12|12]],A]),data(B,C,D,E,F)), p(pc([[[1|1]],A]),data(B,C,D,E,F)), [F=0], [], (1,26)).
stmtsrc((1,26), 'assume(y == 0);').
transition_access((1,26), [_,_,_,_,r]).
r(p(pc([[[10|10]],A]),data(B,C,D,E,F)), p(pc([[[11|11]],A]),data(B,C,D,E,F)), [D+1=<1], [], (1,19)).
stmtsrc((1,19), 'assume(b2 < 1);').
transition_access((1,19), [_,_,r,_,_]).
r(p(pc([[[7|7]],A]),data(B,C,D,E,F)), p(pc([[[1|1]],A]),data(B,C,D,E,F)), [F=0], [], (1,10)).
stmtsrc((1,10), 'assume(y == 0);').
transition_access((1,10), [_,_,_,_,r]).
r(p(pc([A,[[4|4]]]),data(B,C,D,_,F)), p(pc([A,[[3|3]]]),data(B,C,D,K,F)), [], [K=2], (2,3)).
stmtsrc((2,3), 'x=2;').
transition_access((2,3), [_,_,_,w,_]).
r(p(pc([A,[[3|3]]]),data(B,C,D,E,F)), p(pc([A,[[6|6]]]),data(B,C,D,E,F)), [F+1=<0], [], (2,4)).
stmtsrc((2,4), 'assume(y < 0);').
transition_access((2,4), [_,_,_,_,r]).
r(p(pc([A,[[3|3]]]),data(B,C,D,E,F)), p(pc([A,[[6|6]]]),data(B,C,D,E,F)), [F>=1+0], [], (2,5)).
stmtsrc((2,5), 'assume(y > 0);').
transition_access((2,5), [_,_,_,_,r]).
r(p(pc([A,[[6|6]]]),data(B,C,_,E,F)), p(pc([A,[[7|7]]]),data(B,C,J,E,F)), [], [J=0], (2,6)).
stmtsrc((2,6), 'b2=0;').
transition_access((2,6), [_,_,w,_,_]).
r(p(pc([A,[[3|3]]]),data(B,C,D,E,F)), p(pc([A,[[5|5]]]),data(B,C,D,E,F)), [F=0], [], (2,12)).
stmtsrc((2,12), 'assume(y == 0);').
transition_access((2,12), [_,_,_,_,r]).
r(p(pc([A,[[5|5]]]),data(B,C,D,E,_)), p(pc([A,[[8|8]]]),data(B,C,D,E,L)), [], [L=2], (2,13)).
stmtsrc((2,13), 'y=2;').
transition_access((2,13), [_,_,_,_,w]).
r(p(pc([A,[[8|8]]]),data(B,C,D,E,F)), p(pc([A,[[9|9]]]),data(B,C,D,E,F)), [E+1=<2], [], (2,14)).
stmtsrc((2,14), 'assume(x < 2);').
transition_access((2,14), [_,_,_,r,_]).
r(p(pc([A,[[8|8]]]),data(B,C,D,E,F)), p(pc([A,[[9|9]]]),data(B,C,D,E,F)), [E>=1+2], [], (2,15)).
stmtsrc((2,15), 'assume(x > 2);').
transition_access((2,15), [_,_,_,r,_]).
r(p(pc([A,[[9|9]]]),data(B,C,_,E,F)), p(pc([A,[[10|10]]]),data(B,C,J,E,F)), [], [J=0], (2,16)).
stmtsrc((2,16), 'b2=0;').
transition_access((2,16), [_,_,w,_,_]).
r(p(pc([A,[[11|11]]]),data(B,C,D,E,F)), p(pc([A,[[12|12]]]),data(B,C,D,E,F)), [F+1=<2], [], (2,21)).
stmtsrc((2,21), 'assume(y < 2);').
transition_access((2,21), [_,_,_,_,r]).
r(p(pc([A,[[11|11]]]),data(B,C,D,E,F)), p(pc([A,[[12|12]]]),data(B,C,D,E,F)), [F>=1+2], [], (2,22)).
stmtsrc((2,22), 'assume(y > 2);').
transition_access((2,22), [_,_,_,_,r]).
r(p(pc([A,[[2|2]]]),data(_,C,D,E,F)), p(pc([A,[[13|13]]]),data(H,C,D,E,F)), [], [H=1], (2,31)).
stmtsrc((2,31), 'X=1;').
transition_access((2,31), [w,_,_,_,_]).
r(p(pc([A,[[13|13]]]),data(B,C,D,E,F)), p(pc([A,[[16|16]]]),data(B,C,D,E,F)), [B+1=<1], [], (2,32)).
stmtsrc((2,32), 'assume(X < 1);').
transition_access((2,32), [r,_,_,_,_]).
r(p(pc([A,[[13|13]]]),data(B,C,D,E,F)), p(pc([A,[[14|14]]]),data(B,C,D,E,F)), [B>=1], [], (2,33)).
stmtsrc((2,33), 'assume(X >= 1);').
transition_access((2,33), [r,_,_,_,_]).
r(p(pc([A,[[14|14]]]),data(B,C,D,E,_)), p(pc([A,[[15|15]]]),data(B,C,D,E,L)), [], [L=0], (2,34)).
stmtsrc((2,34), 'y=0;').
transition_access((2,34), [_,_,_,_,w]).
r(p(pc([A,[[1|1]]]),data(B,C,_,E,F)), p(pc([A,[[4|4]]]),data(B,C,J,E,F)), [], [J=1], (2,2)).
stmtsrc((2,2), 'b2=1;').
transition_access((2,2), [_,_,w,_,_]).
r(p(pc([A,[[7|7]]]),data(B,C,D,E,F)), p(pc([A,[[7|7]]]),data(B,C,D,E,F)), [F+1=<0], [], (2,8)).
stmtsrc((2,8), 'assume(y < 0);').
transition_access((2,8), [_,_,_,_,r]).
r(p(pc([A,[[7|7]]]),data(B,C,D,E,F)), p(pc([A,[[7|7]]]),data(B,C,D,E,F)), [F>=1+0], [], (2,9)).
stmtsrc((2,9), 'assume(y > 0);').
transition_access((2,9), [_,_,_,_,r]).
r(p(pc([A,[[10|10]]]),data(B,C,D,E,F)), p(pc([A,[[10|10]]]),data(B,C,D,E,F)), [C>=1], [], (2,18)).
stmtsrc((2,18), 'assume(b1 >= 1);').
transition_access((2,18), [_,r,_,_,_]).
r(p(pc([A,[[12|12]]]),data(B,C,D,E,F)), p(pc([A,[[12|12]]]),data(B,C,D,E,F)), [F+1=<0], [], (2,24)).
stmtsrc((2,24), 'assume(y < 0);').
transition_access((2,24), [_,_,_,_,r]).
r(p(pc([A,[[12|12]]]),data(B,C,D,E,F)), p(pc([A,[[12|12]]]),data(B,C,D,E,F)), [F>=1+0], [], (2,25)).
stmtsrc((2,25), 'assume(y > 0);').
transition_access((2,25), [_,_,_,_,r]).
r(p(pc([A,[[15|15]]]),data(B,C,_,E,F)), p(pc([A,[[17|17]]]),data(B,C,J,E,F)), [], [J=0], (2,35)).
stmtsrc((2,35), 'b2=0;').
transition_access((2,35), [_,_,w,_,_]).
r(p(pc([A,[[11|11]]]),data(B,C,D,E,F)), p(pc([A,[[2|2]]]),data(B,C,D,E,F)), [F=2], [], (2,28)).
stmtsrc((2,28), 'assume(y == 2);').
transition_access((2,28), [_,_,_,_,r]).
r(p(pc([A,[[8|8]]]),data(B,C,D,E,F)), p(pc([A,[[2|2]]]),data(B,C,D,E,F)), [E=2], [], (2,29)).
stmtsrc((2,29), 'assume(x == 2);').
transition_access((2,29), [_,_,_,r,_]).
r(p(pc([A,[[12|12]]]),data(B,C,D,E,F)), p(pc([A,[[1|1]]]),data(B,C,D,E,F)), [F=0], [], (2,26)).
stmtsrc((2,26), 'assume(y == 0);').
transition_access((2,26), [_,_,_,_,r]).
r(p(pc([A,[[10|10]]]),data(B,C,D,E,F)), p(pc([A,[[11|11]]]),data(B,C,D,E,F)), [C+1=<1], [], (2,19)).
stmtsrc((2,19), 'assume(b1 < 1);').
transition_access((2,19), [_,r,_,_,_]).
r(p(pc([A,[[7|7]]]),data(B,C,D,E,F)), p(pc([A,[[1|1]]]),data(B,C,D,E,F)), [F=0], [], (2,10)).
stmtsrc((2,10), 'assume(y == 0);').
transition_access((2,10), [_,_,_,_,r]).
