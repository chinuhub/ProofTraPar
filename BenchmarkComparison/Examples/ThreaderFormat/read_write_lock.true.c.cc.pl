:- multifile r/5,implicit_updates/0,var2names/2,preds/2,preds/3,trans_preds/4,
   cube_size/1,start/2,error/2,error/3,refinement/1,cutpoint/1,invgen_template/2,
   invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,trans_preds/3,
   globals/2,bound_var/2,bounding_vars/2,int2pc/1,dec_data/3,transition_access/2,
   singleton/2.
refinement(inter).
cube_size(1).
var2names(p(_,data(B,C,D,E)), [(B,y),(C,r),(D,w),(E,x)]).
dec_data(p(_,data(B,C,D,E)), [[B,C,D,E],[],[],[],[]], 4).
start(p(pc([[[1|1]],[[1|1]],[[1|1]],[[1|1]]]),data(_,B,C,_)), [B=0,C=0,B=0,C=0]).
error(p(pc([_,[[5|5]],_,_]),data(_,_,_,_)), [], 2).
error(p(pc([_,_,_,[[5|5]]]),data(_,_,_,_)), [], 4).
preds(_, p(_,data(_,_,_,_)), []).
trans_preds(_, p(_,data(_,_,_,_)), p(_,data(_,_,_,_)), []).

r(p(pc([[[2|2]],A,B,C]),data(D,E,F,_)), p(pc([[[3|3]],A,B,C]),data(D,E,F,N)), [], [N=3], (1,6)).
stmtsrc((1,6), 'x=3;').
transition_access((1,6), [_,_,_,w]).
r(p(pc([[[1|1]],A,B,C]),data(D,E,F,G)), p(pc([[[2|2]],A,B,C]),data(D,E,M,G)), [], [F=rat(0,1),E=rat(0,1),M=rat(1,1)], (1,path([5,4,3]))).
stmtsrc((1,path([5,4,3])), 'assume(w == 0);assume(r == 0);w=1;').
transition_access((1,path([5,4,3])), [_,r,w,_]).
r(p(pc([[[3|3]],A,B,C]),data(D,E,_,G)), p(pc([[[4|4]],A,B,C]),data(D,E,M,G)), [], [M=0], (1,7)).
stmtsrc((1,7), 'w=0;').
transition_access((1,7), [_,_,w,_]).
r(p(pc([A,[[2|2]],B,C]),data(_,E,F,G)), p(pc([A,[[3|3]],B,C]),data(K,E,F,G)), [], [K=G], (2,3)).
stmtsrc((2,3), 'y=x;').
transition_access((2,3), [w,_,_,r]).
r(p(pc([A,[[3|3]],B,C]),data(D,E,F,G)), p(pc([A,[[5|5]],B,C]),data(D,E,F,G)), [D+1=<G], [], (2,4)).
stmtsrc((2,4), 'assume(y < x);').
transition_access((2,4), [r,_,_,r]).
r(p(pc([A,[[3|3]],B,C]),data(D,E,F,G)), p(pc([A,[[5|5]],B,C]),data(D,E,F,G)), [D>=1+G], [], (2,5)).
stmtsrc((2,5), 'assume(y > x);').
transition_access((2,5), [r,_,_,r]).
r(p(pc([A,[[3|3]],B,C]),data(D,E,F,G)), p(pc([A,[[4|4]],B,C]),data(D,E,F,G)), [D=G], [], (2,6)).
stmtsrc((2,6), 'assume(y == x);').
transition_access((2,6), [r,_,_,r]).
r(p(pc([A,[[1|1]],B,C]),data(D,E,F,G)), p(pc([A,[[2|2]],B,C]),data(D,L,F,G)), [], [F=rat(0,1),E=rat(-1,1)+L], (2,path([2,1]))).
stmtsrc((2,path([2,1])), 'assume(w == 0);r=r + 1;').
transition_access((2,path([2,1])), [_,w,r,_]).
r(p(pc([A,[[4|4]],B,C]),data(D,E,F,G)), p(pc([A,[[6|6]],B,C]),data(D,L,F,G)), [], [L=E-1], (2,7)).
stmtsrc((2,7), 'r=r - 1;').
transition_access((2,7), [_,w,_,_]).
r(p(pc([A,B,[[2|2]],C]),data(D,E,F,_)), p(pc([A,B,[[3|3]],C]),data(D,E,F,N)), [], [N=3], (3,6)).
stmtsrc((3,6), 'x=3;').
transition_access((3,6), [_,_,_,w]).
r(p(pc([A,B,[[1|1]],C]),data(D,E,F,G)), p(pc([A,B,[[2|2]],C]),data(D,E,M,G)), [], [F=rat(0,1),E=rat(0,1),M=rat(1,1)], (3,path([5,4,3]))).
stmtsrc((3,path([5,4,3])), 'assume(w == 0);assume(r == 0);w=1;').
transition_access((3,path([5,4,3])), [_,r,w,_]).
r(p(pc([A,B,[[3|3]],C]),data(D,E,_,G)), p(pc([A,B,[[4|4]],C]),data(D,E,M,G)), [], [M=0], (3,7)).
stmtsrc((3,7), 'w=0;').
transition_access((3,7), [_,_,w,_]).
r(p(pc([A,B,C,[[2|2]]]),data(_,E,F,G)), p(pc([A,B,C,[[3|3]]]),data(K,E,F,G)), [], [K=G], (4,3)).
stmtsrc((4,3), 'y=x;').
transition_access((4,3), [w,_,_,r]).
r(p(pc([A,B,C,[[3|3]]]),data(D,E,F,G)), p(pc([A,B,C,[[5|5]]]),data(D,E,F,G)), [D+1=<G], [], (4,4)).
stmtsrc((4,4), 'assume(y < x);').
transition_access((4,4), [r,_,_,r]).
r(p(pc([A,B,C,[[3|3]]]),data(D,E,F,G)), p(pc([A,B,C,[[5|5]]]),data(D,E,F,G)), [D>=1+G], [], (4,5)).
stmtsrc((4,5), 'assume(y > x);').
transition_access((4,5), [r,_,_,r]).
r(p(pc([A,B,C,[[3|3]]]),data(D,E,F,G)), p(pc([A,B,C,[[4|4]]]),data(D,E,F,G)), [D=G], [], (4,6)).
stmtsrc((4,6), 'assume(y == x);').
transition_access((4,6), [r,_,_,r]).
r(p(pc([A,B,C,[[1|1]]]),data(D,E,F,G)), p(pc([A,B,C,[[2|2]]]),data(D,L,F,G)), [], [F=rat(0,1),E=rat(-1,1)+L], (4,path([2,1]))).
stmtsrc((4,path([2,1])), 'assume(w == 0);r=r + 1;').
transition_access((4,path([2,1])), [_,w,r,_]).
r(p(pc([A,B,C,[[4|4]]]),data(D,E,F,G)), p(pc([A,B,C,[[6|6]]]),data(D,L,F,G)), [], [L=E-1], (4,7)).
stmtsrc((4,7), 'r=r - 1;').
transition_access((4,7), [_,w,_,_]).
