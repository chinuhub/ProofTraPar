:- multifile r/5,implicit_updates/0,var2names/2,preds/2,preds/3,trans_preds/4,
   cube_size/1,start/2,error/2,error/3,refinement/1,cutpoint/1,invgen_template/2,
   invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,trans_preds/3,
   globals/2,bound_var/2,bounding_vars/2,int2pc/1,dec_data/3,transition_access/2,
   singleton/2.
refinement(inter).
cube_size(1).
var2names(p(_,data(B,C,D)), [(B,flag1),(C,flag2),(D,x)]).
dec_data(p(_,data(B,C,D)), [[B,C,D],[],[]], 2).
start(p(pc([[[1|1]],[[1|1]]]),data(A,B,_)), [A=0,B=0,A=0,B=0]).
error(p(pc([[[14|14]],_]),data(_,_,_)), [], 1).
error(p(pc([_,[[14|14]]]),data(_,_,_)), [], 2).
preds(_, p(_,data(_,_,_)), []).
trans_preds(_, p(_,data(_,_,_)), p(_,data(_,_,_)), []).
cutpoint([[[10|10]],_]).
cutpoint([[[8|8]],_]).
cutpoint([[[7|7]],_]).
cutpoint([[[2|2]],_]).
cutpoint([[[1|1]],_]).
cutpoint([_,[[10|10]]]).
cutpoint([_,[[8|8]]]).
cutpoint([_,[[7|7]]]).
cutpoint([_,[[2|2]]]).
cutpoint([_,[[1|1]]]).

r(p(pc([[[3|3]],A]),data(_,C,D)), p(pc([[[4|4]],A]),data(F,C,D)), [], [F=3], (1,7)).
stmtsrc((1,7), 'flag1=3;').
transition_access((1,7), [w,_,_]).
r(p(pc([[[4|4]],A]),data(B,C,D)), p(pc([[[6|6]],A]),data(B,C,D)), [C=1], [], (1,8)).
stmtsrc((1,8), 'assume(flag2 == 1);').
transition_access((1,8), [_,r,_]).
r(p(pc([[[6|6]],A]),data(_,C,D)), p(pc([[[7|7]],A]),data(F,C,D)), [], [F=2], (1,9)).
stmtsrc((1,9), 'flag1=2;').
transition_access((1,9), [w,_,_]).
r(p(pc([[[4|4]],A]),data(B,C,D)), p(pc([[[5|5]],A]),data(B,C,D)), [C+1=<1], [], (1,15)).
stmtsrc((1,15), 'assume(flag2 < 1);').
transition_access((1,15), [_,r,_]).
r(p(pc([[[4|4]],A]),data(B,C,D)), p(pc([[[5|5]],A]),data(B,C,D)), [C>=1+1], [], (1,16)).
stmtsrc((1,16), 'assume(flag2 > 1);').
transition_access((1,16), [_,r,_]).
r(p(pc([[[5|5]],A]),data(_,C,D)), p(pc([[[8|8]],A]),data(F,C,D)), [], [F=4], (1,17)).
stmtsrc((1,17), 'flag1=4;').
transition_access((1,17), [w,_,_]).
r(p(pc([[[9|9]],A]),data(B,C,_)), p(pc([[[11|11]],A]),data(B,C,H)), [], [H=0], (1,22)).
stmtsrc((1,22), 'x=0;').
transition_access((1,22), [_,_,w]).
r(p(pc([[[11|11]],A]),data(B,C,D)), p(pc([[[14|14]],A]),data(B,C,D)), [D>=1+0], [], (1,23)).
stmtsrc((1,23), 'assume(x > 0);').
transition_access((1,23), [_,_,r]).
r(p(pc([[[11|11]],A]),data(B,C,D)), p(pc([[[10|10]],A]),data(B,C,D)), [D=<0], [], (1,24)).
stmtsrc((1,24), 'assume(x <= 0);').
transition_access((1,24), [_,_,r]).
r(p(pc([[[13|13]],A]),data(B,C,D)), p(pc([[[10|10]],A]),data(B,C,D)), [C=<3], [], (1,27)).
stmtsrc((1,27), 'assume(flag2 <= 3);').
transition_access((1,27), [_,r,_]).
r(p(pc([[[12|12]],A]),data(_,C,D)), p(pc([[[1|1]],A]),data(F,C,D)), [], [F=0], (1,31)).
stmtsrc((1,31), 'flag1=0;').
transition_access((1,31), [w,_,_]).
r(p(pc([[[1|1]],A]),data(_,C,D)), p(pc([[[2|2]],A]),data(F,C,D)), [], [F=1], (1,2)).
stmtsrc((1,2), 'flag1=1;').
transition_access((1,2), [w,_,_]).
r(p(pc([[[2|2]],A]),data(B,C,D)), p(pc([[[2|2]],A]),data(B,C,D)), [C>=3], [], (1,4)).
stmtsrc((1,4), 'assume(flag2 >= 3);').
transition_access((1,4), [_,r,_]).
r(p(pc([[[7|7]],A]),data(B,C,D)), p(pc([[[7|7]],A]),data(B,C,D)), [C+1=<4], [], (1,11)).
stmtsrc((1,11), 'assume(flag2 < 4);').
transition_access((1,11), [_,r,_]).
r(p(pc([[[7|7]],A]),data(B,C,D)), p(pc([[[7|7]],A]),data(B,C,D)), [C>=1+4], [], (1,12)).
stmtsrc((1,12), 'assume(flag2 > 4);').
transition_access((1,12), [_,r,_]).
r(p(pc([[[8|8]],A]),data(B,C,D)), p(pc([[[8|8]],A]),data(B,C,D)), [C>=2], [], (1,19)).
stmtsrc((1,19), 'assume(flag2 >= 2);').
transition_access((1,19), [_,r,_]).
r(p(pc([[[10|10]],A]),data(B,C,D)), p(pc([[[13|13]],A]),data(B,C,D)), [2=<C], [], (1,26)).
stmtsrc((1,26), 'assume(2 <= flag2);').
transition_access((1,26), [_,r,_]).
r(p(pc([[[10|10]],A]),data(B,C,D)), p(pc([[[12|12]],A]),data(B,C,D)), [2>=1+C], [], (1,29)).
stmtsrc((1,29), 'assume(2 > flag2);').
transition_access((1,29), [_,r,_]).
r(p(pc([[[13|13]],A]),data(B,C,D)), p(pc([[[12|12]],A]),data(B,C,D)), [C>=1+3], [], (1,28)).
stmtsrc((1,28), 'assume(flag2 > 3);').
transition_access((1,28), [_,r,_]).
r(p(pc([[[8|8]],A]),data(B,C,D)), p(pc([[[9|9]],A]),data(B,C,D)), [C+1=<2], [], (1,20)).
stmtsrc((1,20), 'assume(flag2 < 2);').
transition_access((1,20), [_,r,_]).
r(p(pc([[[7|7]],A]),data(B,C,D)), p(pc([[[5|5]],A]),data(B,C,D)), [C=4], [], (1,13)).
stmtsrc((1,13), 'assume(flag2 == 4);').
transition_access((1,13), [_,r,_]).
r(p(pc([[[2|2]],A]),data(B,C,D)), p(pc([[[3|3]],A]),data(B,C,D)), [C+1=<3], [], (1,5)).
stmtsrc((1,5), 'assume(flag2 < 3);').
transition_access((1,5), [_,r,_]).
r(p(pc([A,[[3|3]]]),data(B,_,D)), p(pc([A,[[4|4]]]),data(B,G,D)), [], [G=3], (2,7)).
stmtsrc((2,7), 'flag2=3;').
transition_access((2,7), [_,w,_]).
r(p(pc([A,[[4|4]]]),data(B,C,D)), p(pc([A,[[6|6]]]),data(B,C,D)), [B=1], [], (2,8)).
stmtsrc((2,8), 'assume(flag1 == 1);').
transition_access((2,8), [r,_,_]).
r(p(pc([A,[[6|6]]]),data(B,_,D)), p(pc([A,[[7|7]]]),data(B,G,D)), [], [G=2], (2,9)).
stmtsrc((2,9), 'flag2=2;').
transition_access((2,9), [_,w,_]).
r(p(pc([A,[[4|4]]]),data(B,C,D)), p(pc([A,[[5|5]]]),data(B,C,D)), [B+1=<1], [], (2,15)).
stmtsrc((2,15), 'assume(flag1 < 1);').
transition_access((2,15), [r,_,_]).
r(p(pc([A,[[4|4]]]),data(B,C,D)), p(pc([A,[[5|5]]]),data(B,C,D)), [B>=1+1], [], (2,16)).
stmtsrc((2,16), 'assume(flag1 > 1);').
transition_access((2,16), [r,_,_]).
r(p(pc([A,[[5|5]]]),data(B,_,D)), p(pc([A,[[8|8]]]),data(B,G,D)), [], [G=4], (2,17)).
stmtsrc((2,17), 'flag2=4;').
transition_access((2,17), [_,w,_]).
r(p(pc([A,[[9|9]]]),data(B,C,_)), p(pc([A,[[11|11]]]),data(B,C,H)), [], [H=1], (2,22)).
stmtsrc((2,22), 'x=1;').
transition_access((2,22), [_,_,w]).
r(p(pc([A,[[11|11]]]),data(B,C,D)), p(pc([A,[[14|14]]]),data(B,C,D)), [D+1=<1], [], (2,23)).
stmtsrc((2,23), 'assume(x < 1);').
transition_access((2,23), [_,_,r]).
r(p(pc([A,[[11|11]]]),data(B,C,D)), p(pc([A,[[10|10]]]),data(B,C,D)), [D>=1], [], (2,24)).
stmtsrc((2,24), 'assume(x >= 1);').
transition_access((2,24), [_,_,r]).
r(p(pc([A,[[13|13]]]),data(B,C,D)), p(pc([A,[[10|10]]]),data(B,C,D)), [B=<3], [], (2,27)).
stmtsrc((2,27), 'assume(flag1 <= 3);').
transition_access((2,27), [r,_,_]).
r(p(pc([A,[[12|12]]]),data(B,_,D)), p(pc([A,[[1|1]]]),data(B,G,D)), [], [G=0], (2,31)).
stmtsrc((2,31), 'flag2=0;').
transition_access((2,31), [_,w,_]).
r(p(pc([A,[[1|1]]]),data(B,_,D)), p(pc([A,[[2|2]]]),data(B,G,D)), [], [G=1], (2,2)).
stmtsrc((2,2), 'flag2=1;').
transition_access((2,2), [_,w,_]).
r(p(pc([A,[[2|2]]]),data(B,C,D)), p(pc([A,[[2|2]]]),data(B,C,D)), [B>=3], [], (2,4)).
stmtsrc((2,4), 'assume(flag1 >= 3);').
transition_access((2,4), [r,_,_]).
r(p(pc([A,[[7|7]]]),data(B,C,D)), p(pc([A,[[7|7]]]),data(B,C,D)), [B+1=<4], [], (2,11)).
stmtsrc((2,11), 'assume(flag1 < 4);').
transition_access((2,11), [r,_,_]).
r(p(pc([A,[[7|7]]]),data(B,C,D)), p(pc([A,[[7|7]]]),data(B,C,D)), [B>=1+4], [], (2,12)).
stmtsrc((2,12), 'assume(flag1 > 4);').
transition_access((2,12), [r,_,_]).
r(p(pc([A,[[8|8]]]),data(B,C,D)), p(pc([A,[[8|8]]]),data(B,C,D)), [B>=2], [], (2,19)).
stmtsrc((2,19), 'assume(flag1 >= 2);').
transition_access((2,19), [r,_,_]).
r(p(pc([A,[[10|10]]]),data(B,C,D)), p(pc([A,[[13|13]]]),data(B,C,D)), [2=<B], [], (2,26)).
stmtsrc((2,26), 'assume(2 <= flag1);').
transition_access((2,26), [r,_,_]).
r(p(pc([A,[[10|10]]]),data(B,C,D)), p(pc([A,[[12|12]]]),data(B,C,D)), [2>=1+B], [], (2,29)).
stmtsrc((2,29), 'assume(2 > flag1);').
transition_access((2,29), [r,_,_]).
r(p(pc([A,[[13|13]]]),data(B,C,D)), p(pc([A,[[12|12]]]),data(B,C,D)), [B>=1+3], [], (2,28)).
stmtsrc((2,28), 'assume(flag1 > 3);').
transition_access((2,28), [r,_,_]).
r(p(pc([A,[[8|8]]]),data(B,C,D)), p(pc([A,[[9|9]]]),data(B,C,D)), [B+1=<2], [], (2,20)).
stmtsrc((2,20), 'assume(flag1 < 2);').
transition_access((2,20), [r,_,_]).
r(p(pc([A,[[7|7]]]),data(B,C,D)), p(pc([A,[[5|5]]]),data(B,C,D)), [B=4], [], (2,13)).
stmtsrc((2,13), 'assume(flag1 == 4);').
transition_access((2,13), [r,_,_]).
r(p(pc([A,[[2|2]]]),data(B,C,D)), p(pc([A,[[3|3]]]),data(B,C,D)), [B+1=<3], [], (2,5)).
stmtsrc((2,5), 'assume(flag1 < 3);').
transition_access((2,5), [r,_,_]).
