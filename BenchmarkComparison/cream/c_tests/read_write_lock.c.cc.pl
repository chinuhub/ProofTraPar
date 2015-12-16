:- multifile r/5,implicit_updates/0,var2names/2,preds/2,preds/3,trans_preds/4,
   cube_size/1,start/2,error/2,error/3,refinement/1,cutpoint/1,invgen_template/2,
   invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,trans_preds/3,
   globals/2,bound_var/2,bounding_vars/2,int2pc/1,dec_data/3,transition_access/2,
   singleton/2.
refinement(inter).
cube_size(1).
var2names(p(_,data(B,C,D,E)), [(B,y),(C,r),(D,w),(E,x)]).
dec_data(p(_,data(B,C,D,E)), [[B,C,D,E],[],[]], 2).
start(p(pc([[[1|1]],[[1|1]]]),data(_,B,C,_)), [B=0,C=0]).
error(p(pc([_,[[5|5]]]),data(_,_,_,_)), [], 2).
preds(_, p(_,data(_,_,_,_)), []).
trans_preds(_, p(_,data(_,_,_,_)), p(_,data(_,_,_,_)), []).

r(p(pc([[[2|2]],A]),data(B,C,D,_)), p(pc([[[3|3]],A]),data(B,C,D,J)), [], [J=3], (1,6)).
stmtsrc((1,6), 'x=3;').
transition_access((1,6), [_,_,_,w]).
r(p(pc([[[1|1]],A]),data(B,C,D,E)), p(pc([[[2|2]],A]),data(B,C,I,E)), [], [D=rat(0,1),C=rat(0,1),I=rat(1,1)], (1,path([5,4,3]))).
stmtsrc((1,path([5,4,3])), 'assume(w == 0);assume(r == 0);w=1;').
transition_access((1,path([5,4,3])), [_,r,w,_]).
r(p(pc([[[3|3]],A]),data(B,C,_,E)), p(pc([[[4|4]],A]),data(B,C,I,E)), [], [I=0], (1,7)).
stmtsrc((1,7), 'w=0;').
transition_access((1,7), [_,_,w,_]).
r(p(pc([A,[[2|2]]]),data(_,C,D,E)), p(pc([A,[[3|3]]]),data(G,C,D,E)), [], [G=E], (2,3)).
stmtsrc((2,3), 'y=x;').
transition_access((2,3), [w,_,_,r]).
r(p(pc([A,[[3|3]]]),data(B,C,D,E)), p(pc([A,[[5|5]]]),data(B,C,D,E)), [B+1=<E], [], (2,4)).
stmtsrc((2,4), 'assume(y < x);').
transition_access((2,4), [r,_,_,r]).
r(p(pc([A,[[3|3]]]),data(B,C,D,E)), p(pc([A,[[5|5]]]),data(B,C,D,E)), [B>=1+E], [], (2,5)).
stmtsrc((2,5), 'assume(y > x);').
transition_access((2,5), [r,_,_,r]).
r(p(pc([A,[[3|3]]]),data(B,C,D,E)), p(pc([A,[[4|4]]]),data(B,C,D,E)), [B=E], [], (2,6)).
stmtsrc((2,6), 'assume(y == x);').
transition_access((2,6), [r,_,_,r]).
r(p(pc([A,[[1|1]]]),data(B,C,D,E)), p(pc([A,[[2|2]]]),data(B,H,D,E)), [], [D=rat(0,1),C=rat(-1,1)+H], (2,path([2,1]))).
stmtsrc((2,path([2,1])), 'assume(w == 0);r=r + 1;').
transition_access((2,path([2,1])), [_,w,r,_]).
r(p(pc([A,[[4|4]]]),data(B,C,D,E)), p(pc([A,[[6|6]]]),data(B,H,D,E)), [], [H=C-1], (2,7)).
stmtsrc((2,7), 'r=r - 1;').
transition_access((2,7), [_,w,_,_]).
