:- multifile r/5,implicit_updates/0,var2names/2,preds/2,preds/3,trans_preds/4,
   cube_size/1,start/2,error/2,error/3,refinement/1,cutpoint/1,invgen_template/2,
   invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,trans_preds/3,
   globals/2,bound_var/2,bounding_vars/2,int2pc/1,dec_data/3,transition_access/2,
   singleton/2.
refinement(inter).
cube_size(1).
var2names(p(_,data(B,C,D,E)), [(B,flag1),(C,flag2),(D,turn),(E,x)]).
dec_data(p(_,data(B,C,D,E)), [[B,C,D,E],[],[]], 2).
start(p(pc([[[1|1]],[[1|1]]]),data(A,B,C,_)), [A=0,B=0,C=0,A=0,B=0,C=0]).
error(p(pc([[[11|11]],_]),data(_,_,_,_)), [], 1).
error(p(pc([_,[[11|11]]]),data(_,_,_,_)), [], 2).
preds(_, p(_,data(_,_,_,_)), []).
trans_preds(_, p(_,data(_,_,_,_)), p(_,data(_,_,_,_)), []).
cutpoint([[[6|6]],_]).
cutpoint([[[2|2]],_]).
cutpoint([_,[[6|6]]]).
cutpoint([_,[[2|2]]]).

r(p(pc([[[1|1]],A]),data(_,C,D,E)), p(pc([[[2|2]],A]),data(G,C,D,E)), [], [G=1], (1,1)).
stmtsrc((1,1), 'flag1=1;').
transition_access((1,1), [w,_,_,_]).
r(p(pc([[[4|4]],A]),data(B,C,D,E)), p(pc([[[5|5]],A]),data(B,C,D,E)), [D+1=<0], [], (1,5)).
stmtsrc((1,5), 'assume(turn < 0);').
transition_access((1,5), [_,_,r,_]).
r(p(pc([[[4|4]],A]),data(B,C,D,E)), p(pc([[[5|5]],A]),data(B,C,D,E)), [D>=1+0], [], (1,6)).
stmtsrc((1,6), 'assume(turn > 0);').
transition_access((1,6), [_,_,r,_]).
r(p(pc([[[5|5]],A]),data(_,C,D,E)), p(pc([[[6|6]],A]),data(G,C,D,E)), [], [G=0], (1,7)).
stmtsrc((1,7), 'flag1=0;').
transition_access((1,7), [w,_,_,_]).
r(p(pc([[[7|7]],A]),data(_,C,D,E)), p(pc([[[2|2]],A]),data(G,C,D,E)), [], [G=1], (1,13)).
stmtsrc((1,13), 'flag1=1;').
transition_access((1,13), [w,_,_,_]).
r(p(pc([[[4|4]],A]),data(B,C,D,E)), p(pc([[[2|2]],A]),data(B,C,D,E)), [D=0], [], (1,14)).
stmtsrc((1,14), 'assume(turn == 0);').
transition_access((1,14), [_,_,r,_]).
r(p(pc([[[3|3]],A]),data(B,C,D,_)), p(pc([[[8|8]],A]),data(B,C,D,J)), [], [J=0], (1,16)).
stmtsrc((1,16), 'x=0;').
transition_access((1,16), [_,_,_,w]).
r(p(pc([[[8|8]],A]),data(B,C,D,E)), p(pc([[[11|11]],A]),data(B,C,D,E)), [E>=1+0], [], (1,17)).
stmtsrc((1,17), 'assume(x > 0);').
transition_access((1,17), [_,_,_,r]).
r(p(pc([[[8|8]],A]),data(B,C,D,E)), p(pc([[[9|9]],A]),data(B,C,D,E)), [E=<0], [], (1,18)).
stmtsrc((1,18), 'assume(x <= 0);').
transition_access((1,18), [_,_,_,r]).
r(p(pc([[[9|9]],A]),data(B,C,_,E)), p(pc([[[10|10]],A]),data(B,C,I,E)), [], [I=1], (1,19)).
stmtsrc((1,19), 'turn=1;').
transition_access((1,19), [_,_,w,_]).
r(p(pc([[[2|2]],A]),data(B,C,D,E)), p(pc([[[4|4]],A]),data(B,C,D,E)), [C>=1], [], (1,3)).
stmtsrc((1,3), 'assume(flag2 >= 1);').
transition_access((1,3), [_,r,_,_]).
r(p(pc([[[6|6]],A]),data(B,C,D,E)), p(pc([[[6|6]],A]),data(B,C,D,E)), [D+1=<0], [], (1,9)).
stmtsrc((1,9), 'assume(turn < 0);').
transition_access((1,9), [_,_,r,_]).
r(p(pc([[[6|6]],A]),data(B,C,D,E)), p(pc([[[6|6]],A]),data(B,C,D,E)), [D>=1+0], [], (1,10)).
stmtsrc((1,10), 'assume(turn > 0);').
transition_access((1,10), [_,_,r,_]).
r(p(pc([[[10|10]],A]),data(_,C,D,E)), p(pc([[[12|12]],A]),data(G,C,D,E)), [], [G=0], (1,20)).
stmtsrc((1,20), 'flag1=0;').
transition_access((1,20), [w,_,_,_]).
r(p(pc([[[6|6]],A]),data(B,C,D,E)), p(pc([[[7|7]],A]),data(B,C,D,E)), [D=0], [], (1,11)).
stmtsrc((1,11), 'assume(turn == 0);').
transition_access((1,11), [_,_,r,_]).
r(p(pc([[[2|2]],A]),data(B,C,D,E)), p(pc([[[3|3]],A]),data(B,C,D,E)), [C+1=<1], [], (1,4)).
stmtsrc((1,4), 'assume(flag2 < 1);').
transition_access((1,4), [_,r,_,_]).
r(p(pc([A,[[1|1]]]),data(B,_,D,E)), p(pc([A,[[2|2]]]),data(B,H,D,E)), [], [H=1], (2,1)).
stmtsrc((2,1), 'flag2=1;').
transition_access((2,1), [_,w,_,_]).
r(p(pc([A,[[4|4]]]),data(B,C,D,E)), p(pc([A,[[5|5]]]),data(B,C,D,E)), [D+1=<1], [], (2,5)).
stmtsrc((2,5), 'assume(turn < 1);').
transition_access((2,5), [_,_,r,_]).
r(p(pc([A,[[4|4]]]),data(B,C,D,E)), p(pc([A,[[5|5]]]),data(B,C,D,E)), [D>=1+1], [], (2,6)).
stmtsrc((2,6), 'assume(turn > 1);').
transition_access((2,6), [_,_,r,_]).
r(p(pc([A,[[5|5]]]),data(B,_,D,E)), p(pc([A,[[6|6]]]),data(B,H,D,E)), [], [H=0], (2,7)).
stmtsrc((2,7), 'flag2=0;').
transition_access((2,7), [_,w,_,_]).
r(p(pc([A,[[7|7]]]),data(B,_,D,E)), p(pc([A,[[2|2]]]),data(B,H,D,E)), [], [H=1], (2,13)).
stmtsrc((2,13), 'flag2=1;').
transition_access((2,13), [_,w,_,_]).
r(p(pc([A,[[4|4]]]),data(B,C,D,E)), p(pc([A,[[2|2]]]),data(B,C,D,E)), [D=1], [], (2,14)).
stmtsrc((2,14), 'assume(turn == 1);').
transition_access((2,14), [_,_,r,_]).
r(p(pc([A,[[3|3]]]),data(B,C,D,_)), p(pc([A,[[8|8]]]),data(B,C,D,J)), [], [J=1], (2,16)).
stmtsrc((2,16), 'x=1;').
transition_access((2,16), [_,_,_,w]).
r(p(pc([A,[[8|8]]]),data(B,C,D,E)), p(pc([A,[[11|11]]]),data(B,C,D,E)), [E+1=<1], [], (2,17)).
stmtsrc((2,17), 'assume(x < 1);').
transition_access((2,17), [_,_,_,r]).
r(p(pc([A,[[8|8]]]),data(B,C,D,E)), p(pc([A,[[9|9]]]),data(B,C,D,E)), [E>=1], [], (2,18)).
stmtsrc((2,18), 'assume(x >= 1);').
transition_access((2,18), [_,_,_,r]).
r(p(pc([A,[[9|9]]]),data(B,C,_,E)), p(pc([A,[[10|10]]]),data(B,C,I,E)), [], [I=1], (2,19)).
stmtsrc((2,19), 'turn=1;').
transition_access((2,19), [_,_,w,_]).
r(p(pc([A,[[2|2]]]),data(B,C,D,E)), p(pc([A,[[4|4]]]),data(B,C,D,E)), [B>=1], [], (2,3)).
stmtsrc((2,3), 'assume(flag1 >= 1);').
transition_access((2,3), [r,_,_,_]).
r(p(pc([A,[[6|6]]]),data(B,C,D,E)), p(pc([A,[[6|6]]]),data(B,C,D,E)), [D+1=<1], [], (2,9)).
stmtsrc((2,9), 'assume(turn < 1);').
transition_access((2,9), [_,_,r,_]).
r(p(pc([A,[[6|6]]]),data(B,C,D,E)), p(pc([A,[[6|6]]]),data(B,C,D,E)), [D>=1+1], [], (2,10)).
stmtsrc((2,10), 'assume(turn > 1);').
transition_access((2,10), [_,_,r,_]).
r(p(pc([A,[[10|10]]]),data(B,_,D,E)), p(pc([A,[[12|12]]]),data(B,H,D,E)), [], [H=0], (2,20)).
stmtsrc((2,20), 'flag2=0;').
transition_access((2,20), [_,w,_,_]).
r(p(pc([A,[[6|6]]]),data(B,C,D,E)), p(pc([A,[[7|7]]]),data(B,C,D,E)), [D=1], [], (2,11)).
stmtsrc((2,11), 'assume(turn == 1);').
transition_access((2,11), [_,_,r,_]).
r(p(pc([A,[[2|2]]]),data(B,C,D,E)), p(pc([A,[[3|3]]]),data(B,C,D,E)), [B+1=<1], [], (2,4)).
stmtsrc((2,4), 'assume(flag1 < 1);').
transition_access((2,4), [r,_,_,_]).
