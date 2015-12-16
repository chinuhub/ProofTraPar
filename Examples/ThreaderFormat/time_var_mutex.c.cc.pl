:- multifile r/5,implicit_updates/0,var2names/2,preds/2,preds/3,trans_preds/4,
   cube_size/1,start/2,error/2,error/3,refinement/1,cutpoint/1,invgen_template/2,
   invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,trans_preds/3,
   globals/2,bound_var/2,bounding_vars/2,int2pc/1,dec_data/3,transition_access/2,
   singleton/2.
refinement(inter).
cube_size(1).
var2names(p(_,data(B,C,D,E,F)), [(B,block),(C,busy),(D,inode),(E,m_busy),(F,m_inode)]).
dec_data(p(_,data(B,C,D,E,F)), [[B,C,D,E,F],[],[]], 2).
start(p(pc([[[2|2]],[[1|1]]]),data(_,B,C,D,E)), [D=0,E=0,C=B,D=0]).
error(p(pc([[[10|10]],_]),data(_,_,_,_,_)), [], 1).
error(p(pc([_,[[6|6]]]),data(_,_,_,_,_)), [], 2).
preds(_, p(_,data(_,_,_,_,_)), []).
trans_preds(_, p(_,data(_,_,_,_,_)), p(_,data(_,_,_,_,_)), []).

r(p(pc([[[2|2]],A]),data(B,C,D,E,F)), p(pc([[[1|1]],A]),data(B,C,D,E,L)), [F=0], [L=1], (1,2)).
stmtsrc((1,2), 'acquire(m_inode);').
transition_access((1,2), [_,_,_,_,l]).
r(p(pc([[[1|1]],A]),data(B,C,D,E,F)), p(pc([[[4|4]],A]),data(B,C,D,E,F)), [D=0], [], (1,3)).
stmtsrc((1,3), 'assume(inode == 0);').
transition_access((1,3), [_,_,r,_,_]).
r(p(pc([[[4|4]],A]),data(B,C,D,E,F)), p(pc([[[5|5]],A]),data(B,C,D,K,F)), [E=0], [K=1], (1,4)).
stmtsrc((1,4), 'acquire(m_busy);').
transition_access((1,4), [_,_,_,l,_]).
r(p(pc([[[5|5]],A]),data(B,_,D,E,F)), p(pc([[[6|6]],A]),data(B,I,D,E,F)), [], [I=1], (1,5)).
stmtsrc((1,5), 'busy=1;').
transition_access((1,5), [_,w,_,_,_]).
r(p(pc([[[6|6]],A]),data(B,C,D,_,F)), p(pc([[[7|7]],A]),data(B,C,D,K,F)), [], [K=0], (1,6)).
stmtsrc((1,6), 'release(m_busy);').
transition_access((1,6), [_,_,_,u,_]).
r(p(pc([[[7|7]],A]),data(B,C,_,E,F)), p(pc([[[3|3]],A]),data(B,C,J,E,F)), [], [J=1], (1,7)).
stmtsrc((1,7), 'inode=1;').
transition_access((1,7), [_,_,w,_,_]).
r(p(pc([[[1|1]],A]),data(B,C,D,E,F)), p(pc([[[3|3]],A]),data(B,C,D,E,F)), [D+1=<0], [], (1,8)).
stmtsrc((1,8), 'assume(inode < 0);').
transition_access((1,8), [_,_,r,_,_]).
r(p(pc([[[1|1]],A]),data(B,C,D,E,F)), p(pc([[[3|3]],A]),data(B,C,D,E,F)), [D>=1+0], [], (1,9)).
stmtsrc((1,9), 'assume(inode > 0);').
transition_access((1,9), [_,_,r,_,_]).
r(p(pc([[[3|3]],A]),data(_,C,D,E,F)), p(pc([[[8|8]],A]),data(H,C,D,E,F)), [], [H=1], (1,10)).
stmtsrc((1,10), 'block=1;').
transition_access((1,10), [w,_,_,_,_]).
r(p(pc([[[8|8]],A]),data(B,C,D,E,F)), p(pc([[[10|10]],A]),data(B,C,D,E,F)), [B+1=<1], [], (1,11)).
stmtsrc((1,11), 'assume(block < 1);').
transition_access((1,11), [r,_,_,_,_]).
r(p(pc([[[8|8]],A]),data(B,C,D,E,F)), p(pc([[[10|10]],A]),data(B,C,D,E,F)), [B>=1+1], [], (1,12)).
stmtsrc((1,12), 'assume(block > 1);').
transition_access((1,12), [r,_,_,_,_]).
r(p(pc([[[8|8]],A]),data(B,C,D,E,F)), p(pc([[[9|9]],A]),data(B,C,D,E,F)), [B=1], [], (1,13)).
stmtsrc((1,13), 'assume(block == 1);').
transition_access((1,13), [r,_,_,_,_]).
r(p(pc([[[9|9]],A]),data(B,C,D,E,_)), p(pc([[[11|11]],A]),data(B,C,D,E,L)), [], [L=0], (1,14)).
stmtsrc((1,14), 'release(m_inode);').
transition_access((1,14), [_,_,_,_,u]).
r(p(pc([A,[[1|1]]]),data(B,C,D,E,F)), p(pc([A,[[2|2]]]),data(B,C,D,K,F)), [E=0], [K=1], (2,1)).
stmtsrc((2,1), 'acquire(m_busy);').
transition_access((2,1), [_,_,_,l,_]).
r(p(pc([A,[[2|2]]]),data(B,C,D,E,F)), p(pc([A,[[4|4]]]),data(B,C,D,E,F)), [C=0], [], (2,2)).
stmtsrc((2,2), 'assume(busy == 0);').
transition_access((2,2), [_,r,_,_,_]).
r(p(pc([A,[[4|4]]]),data(_,C,D,E,F)), p(pc([A,[[5|5]]]),data(H,C,D,E,F)), [], [H=0], (2,3)).
stmtsrc((2,3), 'block=0;').
transition_access((2,3), [w,_,_,_,_]).
r(p(pc([A,[[5|5]]]),data(B,C,D,E,F)), p(pc([A,[[6|6]]]),data(B,C,D,E,F)), [B+1=<0], [], (2,4)).
stmtsrc((2,4), 'assume(block < 0);').
transition_access((2,4), [r,_,_,_,_]).
r(p(pc([A,[[5|5]]]),data(B,C,D,E,F)), p(pc([A,[[6|6]]]),data(B,C,D,E,F)), [B>=1+0], [], (2,5)).
stmtsrc((2,5), 'assume(block > 0);').
transition_access((2,5), [r,_,_,_,_]).
r(p(pc([A,[[5|5]]]),data(B,C,D,E,F)), p(pc([A,[[3|3]]]),data(B,C,D,E,F)), [B=0], [], (2,6)).
stmtsrc((2,6), 'assume(block == 0);').
transition_access((2,6), [r,_,_,_,_]).
r(p(pc([A,[[2|2]]]),data(B,C,D,E,F)), p(pc([A,[[3|3]]]),data(B,C,D,E,F)), [C+1=<0], [], (2,7)).
stmtsrc((2,7), 'assume(busy < 0);').
transition_access((2,7), [_,r,_,_,_]).
r(p(pc([A,[[2|2]]]),data(B,C,D,E,F)), p(pc([A,[[3|3]]]),data(B,C,D,E,F)), [C>=1+0], [], (2,8)).
stmtsrc((2,8), 'assume(busy > 0);').
transition_access((2,8), [_,r,_,_,_]).
r(p(pc([A,[[3|3]]]),data(B,C,D,_,F)), p(pc([A,[[7|7]]]),data(B,C,D,K,F)), [], [K=0], (2,9)).
stmtsrc((2,9), 'release(m_busy);').
transition_access((2,9), [_,_,_,u,_]).
