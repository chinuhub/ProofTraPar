:- multifile r/5,implicit_updates/0,var2names/2,preds/2,preds/3,trans_preds/4,
   cube_size/1,start/2,error/2,error/3,refinement/1,cutpoint/1,invgen_template/2,
   invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,trans_preds/3,
   globals/2,bound_var/2,bounding_vars/2,int2pc/1,dec_data/3,transition_access/2,
   singleton/2.
refinement(inter).
cube_size(1).
var2names(p(_,data(B,C,D,E)), [(B,flag1),(C,flag2),(D,turn),(E,x)]).
dec_data(p(_,data(B,C,D,E)), [[B,C,D,E],[],[]], 2).
start(p(pc([[[1|1]],[[1|1]]]),data(A,B,_,_)), [A=0,B=0,A=0,B=0]).
error(p(pc([[[8|8]],_]),data(_,_,_,_)), [], 1).
error(p(pc([_,[[8|8]]]),data(_,_,_,_)), [], 2).
preds(_, p(_,data(_,_,_,_)), []).
trans_preds(_, p(_,data(_,_,_,_)), p(_,data(_,_,_,_)), []).
cutpoint([[[2|2]],_]).
cutpoint([_,[[2|2]]]).

r(p(pc([[[1|1]],A]),data(_,C,D,E)), p(pc([[[3|3]],A]),data(G,C,D,E)), [], [G=1], (1,1)).
stmtsrc((1,1), 'flag1=1;').
transition_access((1,1), [w,_,_,_]).
r(p(pc([[[3|3]],A]),data(B,C,_,E)), p(pc([[[2|2]],A]),data(B,C,I,E)), [], [I=1], (1,2)).
stmtsrc((1,2), 'turn=1;').
transition_access((1,2), [_,_,w,_]).
r(p(pc([[[5|5]],A]),data(B,C,D,E)), p(pc([[[2|2]],A]),data(B,C,D,E)), [D=1], [], (1,5)).
stmtsrc((1,5), 'assume(turn == 1);').
transition_access((1,5), [_,_,r,_]).
r(p(pc([[[4|4]],A]),data(B,C,D,_)), p(pc([[[6|6]],A]),data(B,C,D,J)), [], [J=0], (1,11)).
stmtsrc((1,11), 'x=0;').
transition_access((1,11), [_,_,_,w]).
r(p(pc([[[6|6]],A]),data(B,C,D,E)), p(pc([[[8|8]],A]),data(B,C,D,E)), [E>=1+0], [], (1,12)).
stmtsrc((1,12), 'assume(x > 0);').
transition_access((1,12), [_,_,_,r]).
r(p(pc([[[6|6]],A]),data(B,C,D,E)), p(pc([[[7|7]],A]),data(B,C,D,E)), [E=<0], [], (1,13)).
stmtsrc((1,13), 'assume(x <= 0);').
transition_access((1,13), [_,_,_,r]).
r(p(pc([[[2|2]],A]),data(B,C,D,E)), p(pc([[[5|5]],A]),data(B,C,D,E)), [C=1], [], (1,4)).
stmtsrc((1,4), 'assume(flag2 == 1);').
transition_access((1,4), [_,r,_,_]).
r(p(pc([[[7|7]],A]),data(_,C,D,E)), p(pc([[[9|9]],A]),data(G,C,D,E)), [], [G=0], (1,14)).
stmtsrc((1,14), 'flag1=0;').
transition_access((1,14), [w,_,_,_]).
r(p(pc([[[2|2]],A]),data(B,C,D,E)), p(pc([[[4|4]],A]),data(B,C,D,E)), [C+1=<1], [], (1,8)).
stmtsrc((1,8), 'assume(flag2 < 1);').
transition_access((1,8), [_,r,_,_]).
r(p(pc([[[2|2]],A]),data(B,C,D,E)), p(pc([[[4|4]],A]),data(B,C,D,E)), [C>=1+1], [], (1,9)).
stmtsrc((1,9), 'assume(flag2 > 1);').
transition_access((1,9), [_,r,_,_]).
r(p(pc([[[5|5]],A]),data(B,C,D,E)), p(pc([[[4|4]],A]),data(B,C,D,E)), [D+1=<1], [], (1,6)).
stmtsrc((1,6), 'assume(turn < 1);').
transition_access((1,6), [_,_,r,_]).
r(p(pc([[[5|5]],A]),data(B,C,D,E)), p(pc([[[4|4]],A]),data(B,C,D,E)), [D>=1+1], [], (1,7)).
stmtsrc((1,7), 'assume(turn > 1);').
transition_access((1,7), [_,_,r,_]).
r(p(pc([A,[[1|1]]]),data(B,_,D,E)), p(pc([A,[[3|3]]]),data(B,H,D,E)), [], [H=1], (2,1)).
stmtsrc((2,1), 'flag2=1;').
transition_access((2,1), [_,w,_,_]).
r(p(pc([A,[[3|3]]]),data(B,C,_,E)), p(pc([A,[[2|2]]]),data(B,C,I,E)), [], [I=0], (2,2)).
stmtsrc((2,2), 'turn=0;').
transition_access((2,2), [_,_,w,_]).
r(p(pc([A,[[5|5]]]),data(B,C,D,E)), p(pc([A,[[2|2]]]),data(B,C,D,E)), [D=0], [], (2,5)).
stmtsrc((2,5), 'assume(turn == 0);').
transition_access((2,5), [_,_,r,_]).
r(p(pc([A,[[4|4]]]),data(B,C,D,_)), p(pc([A,[[6|6]]]),data(B,C,D,J)), [], [J=1], (2,11)).
stmtsrc((2,11), 'x=1;').
transition_access((2,11), [_,_,_,w]).
r(p(pc([A,[[6|6]]]),data(B,C,D,E)), p(pc([A,[[8|8]]]),data(B,C,D,E)), [E+1=<1], [], (2,12)).
stmtsrc((2,12), 'assume(x < 1);').
transition_access((2,12), [_,_,_,r]).
r(p(pc([A,[[6|6]]]),data(B,C,D,E)), p(pc([A,[[7|7]]]),data(B,C,D,E)), [E>=1], [], (2,13)).
stmtsrc((2,13), 'assume(x >= 1);').
transition_access((2,13), [_,_,_,r]).
r(p(pc([A,[[2|2]]]),data(B,C,D,E)), p(pc([A,[[5|5]]]),data(B,C,D,E)), [B=1], [], (2,4)).
stmtsrc((2,4), 'assume(flag1 == 1);').
transition_access((2,4), [r,_,_,_]).
r(p(pc([A,[[7|7]]]),data(B,_,D,E)), p(pc([A,[[9|9]]]),data(B,H,D,E)), [], [H=0], (2,14)).
stmtsrc((2,14), 'flag2=0;').
transition_access((2,14), [_,w,_,_]).
r(p(pc([A,[[2|2]]]),data(B,C,D,E)), p(pc([A,[[4|4]]]),data(B,C,D,E)), [B+1=<1], [], (2,8)).
stmtsrc((2,8), 'assume(flag1 < 1);').
transition_access((2,8), [r,_,_,_]).
r(p(pc([A,[[2|2]]]),data(B,C,D,E)), p(pc([A,[[4|4]]]),data(B,C,D,E)), [B>=1+1], [], (2,9)).
stmtsrc((2,9), 'assume(flag1 > 1);').
transition_access((2,9), [r,_,_,_]).
r(p(pc([A,[[5|5]]]),data(B,C,D,E)), p(pc([A,[[4|4]]]),data(B,C,D,E)), [D+1=<0], [], (2,6)).
stmtsrc((2,6), 'assume(turn < 0);').
transition_access((2,6), [_,_,r,_]).
r(p(pc([A,[[5|5]]]),data(B,C,D,E)), p(pc([A,[[4|4]]]),data(B,C,D,E)), [D>=1+0], [], (2,7)).
stmtsrc((2,7), 'assume(turn > 0);').
transition_access((2,7), [_,_,r,_]).
