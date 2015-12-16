:- multifile r/5,implicit_updates/0,var2names/2,preds/2,preds/3,trans_preds/4,
   cube_size/1,start/2,error/2,error/3,refinement/1,cutpoint/1,invgen_template/2,
   invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,trans_preds/3,
   globals/2,bound_var/2,bounding_vars/2,int2pc/1,dec_data/3,transition_access/2,
   singleton/2.
refinement(inter).
cube_size(1).
var2names(p(_,data(B,C,D,E,F,G,H,I,J,K,L)), [(B,mutex),(C,readerprogress2),(D,ctr1),(E,ctr2),(F,idx),(G,readerprogress1),(H,myidx1),(I,myidx2),(J,sum3),(K,readerstart23),(L,readerstart13)]).
dec_data(p(_,data(B,C,D,E,F,G,H,I,J,K,L)), [[B,C,D,E,F,G],[H],[I],[J,K,L]], 3).
start(p(pc([[[1|1]],[[1|1]],[[1|1]]]),data(A,B,C,D,E,F,_,_,_,_,_)), [A=0,B=0,F=0,D=0,C=1,E=0]).
error(p(pc([_,_,[[24|24]]]),data(_,_,_,_,_,_,_,_,_,_,_)), [], 3).
preds(_, p(_,data(_,_,_,_,_,_,_,_,_,_,_)), []).
trans_preds(_, p(_,data(_,_,_,_,_,_,_,_,_,_,_)), p(_,data(_,_,_,_,_,_,_,_,_,_,_)), []).
cutpoint([[[1|1]],_,_]).
cutpoint([_,[[1|1]],_]).
cutpoint([_,_,[[23|23]]]).
cutpoint([_,_,[[22|22]]]).

r(p(pc([[[2|2]],A,B]),data(C,D,E,F,G,_,I,J,K,L,M)), p(pc([[[5|5]],A,B]),data(C,D,E,F,G,U,I,J,K,L,M)), [], [U=1], (1,14)).
stmtsrc((1,14), 'readerprogress1=1;').
transition_access((1,14), [_,_,_,_,_,w,_,_,_,_,_]).
r(p(pc([[[5|5]],A,B]),data(C,D,E,F,G,_,I,J,K,L,M)), p(pc([[[4|4]],A,B]),data(C,D,E,F,G,U,I,J,K,L,M)), [], [U=2], (1,15)).
stmtsrc((1,15), 'readerprogress1=2;').
transition_access((1,15), [_,_,_,_,_,w,_,_,_,_,_]).
r(p(pc([[[1|1]],A,B]),data(C,D,E,F,G,H,_,J,K,L,M)), p(pc([[[3|3]],A,B]),data(C,D,E,F,G,H,V,J,K,L,M)), [], [V=G], (1,2)).
stmtsrc((1,2), 'myidx=idx;').
transition_access((1,2), [_,_,_,_,r,_,w,_,_,_,_]).
r(p(pc([[[3|3]],A,B]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([[[1|1]],A,B]),data(C,D,E,F,G,H,I,J,K,L,M)), [], [], (1,12)).
stmtsrc((1,12), 'skip;').
transition_access((1,12), [_,_,_,_,_,_,_,_,_,_,_]).
r(p(pc([[[4|4]],A,B]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([[[6|6]],A,B]),data(C,D,R,F,G,H,I,J,K,L,M)), [], [E=rat(1,1)+R,I=<rat(0,1)], (1,path([17,16]))).
stmtsrc((1,path([17,16])), 'assume(myidx <= 0);ctr1=ctr1 - 1;').
transition_access((1,path([17,16])), [_,_,w,_,_,_,r,_,_,_,_]).
r(p(pc([[[4|4]],A,B]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([[[6|6]],A,B]),data(C,D,E,S,G,H,I,J,K,L,M)), [], [F=rat(1,1)+S,I>=rat(1,1)], (1,path([19,18]))).
stmtsrc((1,path([19,18])), 'assume(myidx > 0);ctr2=ctr2 - 1;').
transition_access((1,path([19,18])), [_,_,_,w,_,_,r,_,_,_,_]).
r(p(pc([[[3|3]],A,B]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([[[2|2]],A,B]),data(C,D,E,S,G,H,I,J,K,L,M)), [], [F=rat(-1,1)+S,S>=rat(2,1),I>=rat(1,1)], (1,path([11,10,9]))).
stmtsrc((1,path([11,10,9])), 'assume(myidx > 0);assume(ctr2 > 0);ctr2=ctr2 + 1;').
transition_access((1,path([11,10,9])), [_,_,_,w,_,_,r,_,_,_,_]).
r(p(pc([[[3|3]],A,B]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([[[2|2]],A,B]),data(C,D,R,F,G,H,I,J,K,L,M)), [], [E=rat(-1,1)+R,R>=rat(2,1),I=<rat(0,1)], (1,path([6,5,4]))).
stmtsrc((1,path([6,5,4])), 'assume(myidx <= 0);assume(ctr1 > 0);ctr1=ctr1 + 1;').
transition_access((1,path([6,5,4])), [_,_,w,_,_,_,r,_,_,_,_]).
r(p(pc([A,[[2|2]],B]),data(C,_,E,F,G,H,I,J,K,L,M)), p(pc([A,[[5|5]],B]),data(C,Q,E,F,G,H,I,J,K,L,M)), [], [Q=1], (2,14)).
stmtsrc((2,14), 'readerprogress2=1;').
transition_access((2,14), [_,w,_,_,_,_,_,_,_,_,_]).
r(p(pc([A,[[5|5]],B]),data(C,_,E,F,G,H,I,J,K,L,M)), p(pc([A,[[4|4]],B]),data(C,Q,E,F,G,H,I,J,K,L,M)), [], [Q=2], (2,15)).
stmtsrc((2,15), 'readerprogress2=2;').
transition_access((2,15), [_,w,_,_,_,_,_,_,_,_,_]).
r(p(pc([A,[[1|1]],B]),data(C,D,E,F,G,H,I,_,K,L,M)), p(pc([A,[[3|3]],B]),data(C,D,E,F,G,H,I,W,K,L,M)), [], [W=G], (2,2)).
stmtsrc((2,2), 'myidx=idx;').
transition_access((2,2), [_,_,_,_,r,_,_,w,_,_,_]).
r(p(pc([A,[[3|3]],B]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,[[1|1]],B]),data(C,D,E,F,G,H,I,J,K,L,M)), [], [], (2,12)).
stmtsrc((2,12), 'skip;').
transition_access((2,12), [_,_,_,_,_,_,_,_,_,_,_]).
r(p(pc([A,[[4|4]],B]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,[[6|6]],B]),data(C,D,R,F,G,H,I,J,K,L,M)), [], [E=rat(1,1)+R,J=<rat(0,1)], (2,path([17,16]))).
stmtsrc((2,path([17,16])), 'assume(myidx <= 0);ctr1=ctr1 - 1;').
transition_access((2,path([17,16])), [_,_,w,_,_,_,_,r,_,_,_]).
r(p(pc([A,[[4|4]],B]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,[[6|6]],B]),data(C,D,E,S,G,H,I,J,K,L,M)), [], [F=rat(1,1)+S,J>=rat(1,1)], (2,path([19,18]))).
stmtsrc((2,path([19,18])), 'assume(myidx > 0);ctr2=ctr2 - 1;').
transition_access((2,path([19,18])), [_,_,_,w,_,_,_,r,_,_,_]).
r(p(pc([A,[[3|3]],B]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,[[2|2]],B]),data(C,D,E,S,G,H,I,J,K,L,M)), [], [F=rat(-1,1)+S,S>=rat(2,1),J>=rat(1,1)], (2,path([11,10,9]))).
stmtsrc((2,path([11,10,9])), 'assume(myidx > 0);assume(ctr2 > 0);ctr2=ctr2 + 1;').
transition_access((2,path([11,10,9])), [_,_,_,w,_,_,_,r,_,_,_]).
r(p(pc([A,[[3|3]],B]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,[[2|2]],B]),data(C,D,R,F,G,H,I,J,K,L,M)), [], [E=rat(-1,1)+R,R>=rat(2,1),J=<rat(0,1)], (2,path([6,5,4]))).
stmtsrc((2,path([6,5,4])), 'assume(myidx <= 0);assume(ctr1 > 0);ctr1=ctr1 + 1;').
transition_access((2,path([6,5,4])), [_,_,w,_,_,_,_,r,_,_,_]).
r(p(pc([A,B,[[1|1]]]),data(C,D,E,F,G,H,I,J,K,L,_)), p(pc([A,B,[[3|3]]]),data(C,D,E,F,G,H,I,J,K,L,Z)), [], [Z=1], (3,1)).
stmtsrc((3,1), 'readerstart1=1;').
transition_access((3,1), [_,_,_,_,_,_,_,_,_,_,w]).
r(p(pc([A,B,[[5|5]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[4|4]]]),data(C,D,E,F,G,H,I,J,X,L,M)), [], [X=K+F], (3,11)).
stmtsrc((3,11), 'sum=sum + ctr2;').
transition_access((3,11), [_,_,_,r,_,_,_,_,w,_,_]).
r(p(pc([A,B,[[6|6]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[4|4]]]),data(C,D,E,F,G,H,I,J,X,L,M)), [], [X=K+E], (3,14)).
stmtsrc((3,14), 'sum=sum + ctr1;').
transition_access((3,14), [_,_,r,_,_,_,_,_,w,_,_]).
r(p(pc([A,B,[[4|4]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[8|8]]]),data(C,D,E,F,G,H,I,J,K,L,M)), [K=<1], [], (3,15)).
stmtsrc((3,15), 'assume(sum <= 1);').
transition_access((3,15), [_,_,_,_,_,_,_,_,r,_,_]).
r(p(pc([A,B,[[9|9]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[7|7]]]),data(C,D,E,F,G,H,I,J,X,L,M)), [], [X=K+F], (3,18)).
stmtsrc((3,18), 'sum=sum + ctr2;').
transition_access((3,18), [_,_,_,r,_,_,_,_,w,_,_]).
r(p(pc([A,B,[[10|10]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[7|7]]]),data(C,D,E,F,G,H,I,J,X,L,M)), [], [X=K+E], (3,21)).
stmtsrc((3,21), 'sum=sum + ctr1;').
transition_access((3,21), [_,_,r,_,_,_,_,_,w,_,_]).
r(p(pc([A,B,[[4|4]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[7|7]]]),data(C,D,E,F,G,H,I,J,K,L,M)), [K>=1+1], [], (3,22)).
stmtsrc((3,22), 'assume(sum > 1);').
transition_access((3,22), [_,_,_,_,_,_,_,_,r,_,_]).
r(p(pc([A,B,[[7|7]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[12|12]]]),data(C,D,E,F,G,H,I,J,K,L,M)), [K>=1+1], [], (3,23)).
stmtsrc((3,23), 'assume(sum > 1);').
transition_access((3,23), [_,_,_,_,_,_,_,_,r,_,_]).
r(p(pc([A,B,[[12|12]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[13|13]]]),data(P,D,E,F,G,H,I,J,K,L,M)), [C=0], [P=1], (3,24)).
stmtsrc((3,24), 'acquire(mutex);').
transition_access((3,24), [l,_,_,_,_,_,_,_,_,_,_]).
r(p(pc([A,B,[[13|13]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[15|15]]]),data(C,D,E,F,G,H,I,J,K,L,M)), [G=<0], [], (3,25)).
stmtsrc((3,25), 'assume(idx <= 0);').
transition_access((3,25), [_,_,_,_,r,_,_,_,_,_,_]).
r(p(pc([A,B,[[15|15]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[17|17]]]),data(C,D,E,S,G,H,I,J,K,L,M)), [], [S=F+1], (3,26)).
stmtsrc((3,26), 'ctr2=ctr2 + 1;').
transition_access((3,26), [_,_,_,w,_,_,_,_,_,_,_]).
r(p(pc([A,B,[[17|17]]]),data(C,D,E,F,_,H,I,J,K,L,M)), p(pc([A,B,[[18|18]]]),data(C,D,E,F,T,H,I,J,K,L,M)), [], [T=1], (3,27)).
stmtsrc((3,27), 'idx=1;').
transition_access((3,27), [_,_,_,_,w,_,_,_,_,_,_]).
r(p(pc([A,B,[[18|18]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[14|14]]]),data(C,D,R,F,G,H,I,J,K,L,M)), [], [R=E-1], (3,28)).
stmtsrc((3,28), 'ctr1=ctr1 - 1;').
transition_access((3,28), [_,_,w,_,_,_,_,_,_,_,_]).
r(p(pc([A,B,[[13|13]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[16|16]]]),data(C,D,E,F,G,H,I,J,K,L,M)), [G>=1+0], [], (3,29)).
stmtsrc((3,29), 'assume(idx > 0);').
transition_access((3,29), [_,_,_,_,r,_,_,_,_,_,_]).
r(p(pc([A,B,[[16|16]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[19|19]]]),data(C,D,R,F,G,H,I,J,K,L,M)), [], [R=E+1], (3,30)).
stmtsrc((3,30), 'ctr1=ctr1 + 1;').
transition_access((3,30), [_,_,w,_,_,_,_,_,_,_,_]).
r(p(pc([A,B,[[19|19]]]),data(C,D,E,F,_,H,I,J,K,L,M)), p(pc([A,B,[[20|20]]]),data(C,D,E,F,T,H,I,J,K,L,M)), [], [T=0], (3,31)).
stmtsrc((3,31), 'idx=0;').
transition_access((3,31), [_,_,_,_,w,_,_,_,_,_,_]).
r(p(pc([A,B,[[20|20]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[14|14]]]),data(C,D,E,S,G,H,I,J,K,L,M)), [], [S=F-1], (3,32)).
stmtsrc((3,32), 'ctr2=ctr2 - 1;').
transition_access((3,32), [_,_,_,w,_,_,_,_,_,_,_]).
r(p(pc([A,B,[[14|14]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[22|22]]]),data(C,D,E,F,G,H,I,J,K,L,M)), [G=<0], [], (3,33)).
stmtsrc((3,33), 'assume(idx <= 0);').
transition_access((3,33), [_,_,_,_,r,_,_,_,_,_,_]).
r(p(pc([A,B,[[14|14]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[23|23]]]),data(C,D,E,F,G,H,I,J,K,L,M)), [G>=1+0], [], (3,38)).
stmtsrc((3,38), 'assume(idx > 0);').
transition_access((3,38), [_,_,_,_,r,_,_,_,_,_,_]).
r(p(pc([A,B,[[21|21]]]),data(_,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[11|11]]]),data(P,D,E,F,G,H,I,J,K,L,M)), [], [P=0], (3,43)).
stmtsrc((3,43), 'release(mutex);').
transition_access((3,43), [u,_,_,_,_,_,_,_,_,_,_]).
r(p(pc([A,B,[[7|7]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[11|11]]]),data(C,D,E,F,G,H,I,J,K,L,M)), [K=<1], [], (3,44)).
stmtsrc((3,44), 'assume(sum <= 1);').
transition_access((3,44), [_,_,_,_,_,_,_,_,r,_,_]).
r(p(pc([A,B,[[11|11]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[24|24]]]),data(C,D,E,F,G,H,I,J,K,L,M)), [], [H=rat(1,1),M=rat(1,1)], (3,path([48,47,46,45]))).
stmtsrc((3,path([48,47,46,45])), 'skip;assume(readerstart1 == 1);assume(readerprogress1 == 1);assume(0 == 0);').
transition_access((3,path([48,47,46,45])), [_,_,_,_,_,r,_,_,_,_,r]).
r(p(pc([A,B,[[11|11]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[24|24]]]),data(C,D,E,F,G,H,I,J,K,L,M)), [], [D=rat(1,1),L=rat(1,1)], (3,path([54,53,52,51,50]))).
stmtsrc((3,path([54,53,52,51,50])), 'skip;skip;assume(readerstart2 == 1);assume(readerprogress2 == 1);assume(0 == 0);').
transition_access((3,path([54,53,52,51,50])), [_,r,_,_,_,_,_,_,_,r,_]).
r(p(pc([A,B,[[3|3]]]),data(C,D,E,F,G,H,I,J,K,_,M)), p(pc([A,B,[[2|2]]]),data(C,D,E,F,G,H,I,J,K,Y,M)), [], [Y=1], (3,2)).
stmtsrc((3,2), 'readerstart2=1;').
transition_access((3,2), [_,_,_,_,_,_,_,_,_,w,_]).
r(p(pc([A,B,[[2|2]]]),data(C,D,E,F,G,H,I,J,_,L,M)), p(pc([A,B,[[5|5]]]),data(C,D,E,F,G,H,I,J,X,L,M)), [], [X=E], (3,10)).
stmtsrc((3,10), 'sum=ctr1;').
transition_access((3,10), [_,_,r,_,_,_,_,_,w,_,_]).
r(p(pc([A,B,[[2|2]]]),data(C,D,E,F,G,H,I,J,_,L,M)), p(pc([A,B,[[6|6]]]),data(C,D,E,F,G,H,I,J,X,L,M)), [], [X=F], (3,13)).
stmtsrc((3,13), 'sum=ctr2;').
transition_access((3,13), [_,_,_,r,_,_,_,_,w,_,_]).
r(p(pc([A,B,[[8|8]]]),data(C,D,E,F,G,H,I,J,_,L,M)), p(pc([A,B,[[9|9]]]),data(C,D,E,F,G,H,I,J,X,L,M)), [], [X=E], (3,17)).
stmtsrc((3,17), 'sum=ctr1;').
transition_access((3,17), [_,_,r,_,_,_,_,_,w,_,_]).
r(p(pc([A,B,[[8|8]]]),data(C,D,E,F,G,H,I,J,_,L,M)), p(pc([A,B,[[10|10]]]),data(C,D,E,F,G,H,I,J,X,L,M)), [], [X=F], (3,20)).
stmtsrc((3,20), 'sum=ctr2;').
transition_access((3,20), [_,_,_,r,_,_,_,_,w,_,_]).
r(p(pc([A,B,[[22|22]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[22|22]]]),data(C,D,E,F,G,H,I,J,K,L,M)), [F>=1+0], [], (3,35)).
stmtsrc((3,35), 'assume(ctr2 > 0);').
transition_access((3,35), [_,_,_,r,_,_,_,_,_,_,_]).
r(p(pc([A,B,[[23|23]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[23|23]]]),data(C,D,E,F,G,H,I,J,K,L,M)), [E>=1+0], [], (3,40)).
stmtsrc((3,40), 'assume(ctr1 > 0);').
transition_access((3,40), [_,_,r,_,_,_,_,_,_,_,_]).
r(p(pc([A,B,[[11|11]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[25|25]]]),data(C,D,E,F,G,H,I,J,K,L,M)), [], [], (3,path([56,50]))).
stmtsrc((3,path([56,50])), 'skip;skip;').
transition_access((3,path([56,50])), [_,_,_,_,_,_,_,_,_,_,_]).
r(p(pc([A,B,[[23|23]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[21|21]]]),data(C,D,E,F,G,H,I,J,K,L,M)), [E=<0], [], (3,41)).
stmtsrc((3,41), 'assume(ctr1 <= 0);').
transition_access((3,41), [_,_,r,_,_,_,_,_,_,_,_]).
r(p(pc([A,B,[[22|22]]]),data(C,D,E,F,G,H,I,J,K,L,M)), p(pc([A,B,[[21|21]]]),data(C,D,E,F,G,H,I,J,K,L,M)), [F=<0], [], (3,36)).
stmtsrc((3,36), 'assume(ctr2 <= 0);').
transition_access((3,36), [_,_,_,r,_,_,_,_,_,_,_]).
