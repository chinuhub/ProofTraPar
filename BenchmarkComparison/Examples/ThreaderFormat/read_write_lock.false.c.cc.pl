:- multifile r/5,implicit_updates/0,var2names/2,preds/2,preds/3,trans_preds/4,
   cube_size/1,start/2,error/2,error/3,refinement/1,cutpoint/1,invgen_template/2,
   invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,trans_preds/3,
   globals/2,bound_var/2,bounding_vars/2,int2pc/1,dec_data/3,transition_access/2,
   singleton/2.
refinement(inter).
cube_size(1).
var2names(p(_,data(B,C,D,E,F,G)), [(B,y),(C,r),(D,w),(E,x),(F,l2),(G,l4)]).
dec_data(p(_,data(B,C,D,E,F,G)), [[B,C,D,E],[],[F],[],[G]], 4).
start(p(pc([[[1|1]],[[1|1]],[[1|1]],[[1|1]]]),data(_,B,C,_,_,_)), [B=0,C=0,B=0,C=0]).
error(p(pc([_,[[6|6]],_,_]),data(_,_,_,_,_,_)), [], 2).
error(p(pc([_,_,_,[[6|6]]]),data(_,_,_,_,_,_)), [], 4).
preds(_, p(_,data(_,_,_,_,_,_)), []).
trans_preds(_, p(_,data(_,_,_,_,_,_)), p(_,data(_,_,_,_,_,_)), []).

r(p(pc([[[2|2]],A,B,C]),data(D,E,F,_,H,I)), p(pc([[[3|3]],A,B,C]),data(D,E,F,P,H,I)), [], [P=3], (1,6)).
stmtsrc((1,6), 'x=3;').
transition_access((1,6), [_,_,_,w,_,_]).
r(p(pc([[[1|1]],A,B,C]),data(D,E,F,G,H,I)), p(pc([[[2|2]],A,B,C]),data(D,E,O,G,H,I)), [], [F=rat(0,1),E=rat(0,1),O=rat(1,1)], (1,path([5,4,3]))).
stmtsrc((1,path([5,4,3])), 'assume(w == 0);assume(r == 0);w=1;').
transition_access((1,path([5,4,3])), [_,r,w,_,_,_]).
r(p(pc([[[3|3]],A,B,C]),data(D,E,_,G,H,I)), p(pc([[[4|4]],A,B,C]),data(D,E,O,G,H,I)), [], [O=0], (1,7)).
stmtsrc((1,7), 'w=0;').
transition_access((1,7), [_,_,w,_,_,_]).
r(p(pc([A,[[2|2]],B,C]),data(_,E,F,G,H,I)), p(pc([A,[[3|3]],B,C]),data(M,E,F,G,H,I)), [], [M=G], (2,3)).
stmtsrc((2,3), 'y=x;').
transition_access((2,3), [w,_,_,r,_,_]).
r(p(pc([A,[[3|3]],B,C]),data(D,E,F,G,H,I)), p(pc([A,[[6|6]],B,C]),data(D,E,F,G,H,I)), [D+1=<G], [], (2,4)).
stmtsrc((2,4), 'assume(y < x);').
transition_access((2,4), [r,_,_,r,_,_]).
r(p(pc([A,[[3|3]],B,C]),data(D,E,F,G,H,I)), p(pc([A,[[6|6]],B,C]),data(D,E,F,G,H,I)), [D>=1+G], [], (2,5)).
stmtsrc((2,5), 'assume(y > x);').
transition_access((2,5), [r,_,_,r,_,_]).
r(p(pc([A,[[3|3]],B,C]),data(D,E,F,G,H,I)), p(pc([A,[[4|4]],B,C]),data(D,E,F,G,H,I)), [D=G], [], (2,6)).
stmtsrc((2,6), 'assume(y == x);').
transition_access((2,6), [r,_,_,r,_,_]).
r(p(pc([A,[[4|4]],B,C]),data(D,E,F,G,_,I)), p(pc([A,[[5|5]],B,C]),data(D,E,F,G,Q,I)), [], [Q=E-1], (2,7)).
stmtsrc((2,7), 'l=r - 1;').
transition_access((2,7), [_,r,_,_,w,_]).
r(p(pc([A,[[1|1]],B,C]),data(D,E,F,G,H,I)), p(pc([A,[[2|2]],B,C]),data(D,N,F,G,H,I)), [], [F=rat(0,1),E=rat(-1,1)+N], (2,path([2,1]))).
stmtsrc((2,path([2,1])), 'assume(w == 0);r=r + 1;').
transition_access((2,path([2,1])), [_,w,r,_,_,_]).
r(p(pc([A,[[5|5]],B,C]),data(D,_,F,G,H,I)), p(pc([A,[[7|7]],B,C]),data(D,N,F,G,H,I)), [], [N=H], (2,8)).
stmtsrc((2,8), 'r=l;').
transition_access((2,8), [_,w,_,_,r,_]).
r(p(pc([A,B,[[2|2]],C]),data(D,E,F,_,H,I)), p(pc([A,B,[[3|3]],C]),data(D,E,F,P,H,I)), [], [P=3], (3,6)).
stmtsrc((3,6), 'x=3;').
transition_access((3,6), [_,_,_,w,_,_]).
r(p(pc([A,B,[[1|1]],C]),data(D,E,F,G,H,I)), p(pc([A,B,[[2|2]],C]),data(D,E,O,G,H,I)), [], [F=rat(0,1),E=rat(0,1),O=rat(1,1)], (3,path([5,4,3]))).
stmtsrc((3,path([5,4,3])), 'assume(w == 0);assume(r == 0);w=1;').
transition_access((3,path([5,4,3])), [_,r,w,_,_,_]).
r(p(pc([A,B,[[3|3]],C]),data(D,E,_,G,H,I)), p(pc([A,B,[[4|4]],C]),data(D,E,O,G,H,I)), [], [O=0], (3,7)).
stmtsrc((3,7), 'w=0;').
transition_access((3,7), [_,_,w,_,_,_]).
r(p(pc([A,B,C,[[2|2]]]),data(_,E,F,G,H,I)), p(pc([A,B,C,[[3|3]]]),data(M,E,F,G,H,I)), [], [M=G], (4,3)).
stmtsrc((4,3), 'y=x;').
transition_access((4,3), [w,_,_,r,_,_]).
r(p(pc([A,B,C,[[3|3]]]),data(D,E,F,G,H,I)), p(pc([A,B,C,[[6|6]]]),data(D,E,F,G,H,I)), [D+1=<G], [], (4,4)).
stmtsrc((4,4), 'assume(y < x);').
transition_access((4,4), [r,_,_,r,_,_]).
r(p(pc([A,B,C,[[3|3]]]),data(D,E,F,G,H,I)), p(pc([A,B,C,[[6|6]]]),data(D,E,F,G,H,I)), [D>=1+G], [], (4,5)).
stmtsrc((4,5), 'assume(y > x);').
transition_access((4,5), [r,_,_,r,_,_]).
r(p(pc([A,B,C,[[3|3]]]),data(D,E,F,G,H,I)), p(pc([A,B,C,[[4|4]]]),data(D,E,F,G,H,I)), [D=G], [], (4,6)).
stmtsrc((4,6), 'assume(y == x);').
transition_access((4,6), [r,_,_,r,_,_]).
r(p(pc([A,B,C,[[4|4]]]),data(D,E,F,G,H,_)), p(pc([A,B,C,[[5|5]]]),data(D,E,F,G,H,R)), [], [R=E-1], (4,7)).
stmtsrc((4,7), 'l=r - 1;').
transition_access((4,7), [_,r,_,_,_,w]).
r(p(pc([A,B,C,[[1|1]]]),data(D,E,F,G,H,I)), p(pc([A,B,C,[[2|2]]]),data(D,N,F,G,H,I)), [], [F=rat(0,1),E=rat(-1,1)+N], (4,path([2,1]))).
stmtsrc((4,path([2,1])), 'assume(w == 0);r=r + 1;').
transition_access((4,path([2,1])), [_,w,r,_,_,_]).
r(p(pc([A,B,C,[[5|5]]]),data(D,_,F,G,H,I)), p(pc([A,B,C,[[7|7]]]),data(D,N,F,G,H,I)), [], [N=I], (4,8)).
stmtsrc((4,8), 'r=l;').
transition_access((4,8), [_,w,_,_,_,r]).
