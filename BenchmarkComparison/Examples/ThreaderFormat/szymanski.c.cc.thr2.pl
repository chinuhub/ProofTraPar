:- multifile r/5,implicit_updates/0,var2names/2,preds/2,trans_preds/3,
cube_size/1,start/1,error/1,refinement/1,cutpoint/1,invgen_template/2,
 invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,globals/3,
 bound_var/2,bounding_vars/2,transition_access/2,atomic/3.
refinement(inter).
cube_size(1).
preds(p(_, data(V3, V1, V2)), []).
trans_preds(p(_, data(V3, V1, V2)), p(_, data(V3p, V1p, V2p)), []).
var2names(p(pc(_), data(V3, V1, V2)), [(V3, 'x'), (V1, 'flag2'), (V2, 'flag1')]).
globals(p(pc(_), data(V3, V1, V2)), [(V3, 'x'), (V1, 'flag2'), (V2, 'flag1')], [V2=0, V1=0]).
% start location
start(pc(thr2-0-25)).
% error location
error(pc(thr2-err-0)).
% cutpoint locations
cutpoint(pc(thr2-20-39)). % line 39
cutpoint(pc(thr2-15-34)). % line 34
cutpoint(pc(thr2-11-31)). % line 31
cutpoint(pc(thr2-3-27)). % line 27
cutpoint(pc(thr2-0-25)). % line 25
% invariant templates
% bound var 
% bounding vars 
bounding_vars(data(V3, V1, V2), []).
% cfg loop exit relation
cfg_exit_relation([(pc(thr2-20-39), pc(thr2-0-25)), (pc(thr2-15-34), pc(thr2-20-39)), (pc(thr2-11-31), pc(thr2-15-34)), (pc(thr2-3-27), pc(thr2-11-31))]).
% 37 transitions
r(p(pc(thr2-0-25), data(V3, V1, V2)), p(pc(thr2-2-26), data(V3, V1, V2)), [], [], 1). % 
stmtsrc(1, 'skip;').
transition_access( 1, [_, _, _] ).
r(p(pc(thr2-2-26), data(V3, V1, V2)), p(pc(thr2-3-27), data(V3, V1p, V2)), [], [V1p = 1], 2). % flag2 := 1
stmtsrc(2, 'flag2=1;').
transition_access( 2, [_, w, _] ).
r(p(pc(thr2-3-27), data(V3, V1, V2)), p(pc(thr2-6-27), data(V3, V1, V2)), [], [], 3). % 
stmtsrc(3, 'skip;').
transition_access( 3, [_, _, _] ).
r(p(pc(thr2-6-27), data(V3, V1, V2)), p(pc(thr2-3-27), data(V3, V1, V2)), [(V2 >= 3)], [], 4). % flag1 >= 3
stmtsrc(4, 'assume(flag1 >= 3);').
transition_access( 4, [_, _, r] ).
r(p(pc(thr2-6-27), data(V3, V1, V2)), p(pc(thr2-7-27), data(V3, V1, V2)), [(V2 +1 =< 3)], [], 5). % flag1 < 3
stmtsrc(5, 'assume(flag1 < 3);').
transition_access( 5, [_, _, r] ).
r(p(pc(thr2-5-0), data(V3, V1, V2)), p(pc(thr2-4-28), data(V3, V1, V2)), [], [], 6). % 
stmtsrc(6, 'skip;').
transition_access( 6, [_, _, _] ).
r(p(pc(thr2-4-28), data(V3, V1, V2)), p(pc(thr2-8-29), data(V3, V1p, V2)), [], [V1p = 3], 7). % flag2 := 3
stmtsrc(7, 'flag2=3;').
transition_access( 7, [_, w, _] ).
r(p(pc(thr2-8-29), data(V3, V1, V2)), p(pc(thr2-10-30), data(V3, V1, V2)), [(V2 = 1)], [], 8). % flag1 == 1
stmtsrc(8, 'assume(flag1 == 1);').
transition_access( 8, [_, _, r] ).
r(p(pc(thr2-10-30), data(V3, V1, V2)), p(pc(thr2-11-31), data(V3, V1p, V2)), [], [V1p = 2], 9). % flag2 := 2
stmtsrc(9, 'flag2=2;').
transition_access( 9, [_, w, _] ).
r(p(pc(thr2-11-31), data(V3, V1, V2)), p(pc(thr2-13-31), data(V3, V1, V2)), [], [], 10). % 
stmtsrc(10, 'skip;').
transition_access( 10, [_, _, _] ).
r(p(pc(thr2-13-31), data(V3, V1, V2)), p(pc(thr2-11-31), data(V3, V1, V2)), [(V2 +1 =< 4)], [], 11). % flag1 < 4
stmtsrc(11, 'assume(flag1 < 4);').
transition_access( 11, [_, _, r] ).
r(p(pc(thr2-13-31), data(V3, V1, V2)), p(pc(thr2-11-31), data(V3, V1, V2)), [(V2 >= 1+ 4)], [], 12). % flag1 > 4
stmtsrc(12, 'assume(flag1 > 4);').
transition_access( 12, [_, _, r] ).
r(p(pc(thr2-13-31), data(V3, V1, V2)), p(pc(thr2-14-31), data(V3, V1, V2)), [(V2 = 4)], [], 13). % flag1 == 4
stmtsrc(13, 'assume(flag1 == 4);').
transition_access( 13, [_, _, r] ).
r(p(pc(thr2-12-0), data(V3, V1, V2)), p(pc(thr2-9-33), data(V3, V1, V2)), [], [], 14). % 
stmtsrc(14, 'skip;').
transition_access( 14, [_, _, _] ).
r(p(pc(thr2-8-29), data(V3, V1, V2)), p(pc(thr2-9-33), data(V3, V1, V2)), [(V2 +1 =< 1)], [], 15). % flag1 < 1
stmtsrc(15, 'assume(flag1 < 1);').
transition_access( 15, [_, _, r] ).
r(p(pc(thr2-8-29), data(V3, V1, V2)), p(pc(thr2-9-33), data(V3, V1, V2)), [(V2 >= 1+ 1)], [], 16). % flag1 > 1
stmtsrc(16, 'assume(flag1 > 1);').
transition_access( 16, [_, _, r] ).
r(p(pc(thr2-9-33), data(V3, V1, V2)), p(pc(thr2-15-34), data(V3, V1p, V2)), [], [V1p = 4], 17). % flag2 := 4
stmtsrc(17, 'flag2=4;').
transition_access( 17, [_, w, _] ).
r(p(pc(thr2-15-34), data(V3, V1, V2)), p(pc(thr2-18-34), data(V3, V1, V2)), [], [], 18). % 
stmtsrc(18, 'skip;').
transition_access( 18, [_, _, _] ).
r(p(pc(thr2-18-34), data(V3, V1, V2)), p(pc(thr2-15-34), data(V3, V1, V2)), [(V2 >= 2)], [], 19). % flag1 >= 2
stmtsrc(19, 'assume(flag1 >= 2);').
transition_access( 19, [_, _, r] ).
r(p(pc(thr2-18-34), data(V3, V1, V2)), p(pc(thr2-19-34), data(V3, V1, V2)), [(V2 +1 =< 2)], [], 20). % flag1 < 2
stmtsrc(20, 'assume(flag1 < 2);').
transition_access( 20, [_, _, r] ).
r(p(pc(thr2-17-0), data(V3, V1, V2)), p(pc(thr2-16-37), data(V3, V1, V2)), [], [], 21). % 
stmtsrc(21, 'skip;').
transition_access( 21, [_, _, _] ).
r(p(pc(thr2-16-37), data(V3, V1, V2)), p(pc(thr2-21-0), data(V3p, V1, V2)), [], [V3p = 1], 22). % x := 1
stmtsrc(22, 'x=1;').
transition_access( 22, [w, _, _] ).
r(p(pc(thr2-21-0), data(V3, V1, V2)), p(pc(thr2-err-0), data(V3, V1, V2)), [(V3 +1 =< 1)], [], 23). % x < 1
stmtsrc(23, 'assume(x < 1);').
transition_access( 23, [r, _, _] ).
r(p(pc(thr2-21-0), data(V3, V1, V2)), p(pc(thr2-20-39), data(V3, V1, V2)), [(V3 >= 1)], [], 24). % x >= 1
stmtsrc(24, 'assume(x >= 1);').
transition_access( 24, [r, _, _] ).
r(p(pc(thr2-20-39), data(V3, V1, V2)), p(pc(thr2-24-39), data(V3, V1, V2)), [], [], 25). % 
stmtsrc(25, 'skip;').
transition_access( 25, [_, _, _] ).
r(p(pc(thr2-24-39), data(V3, V1, V2)), p(pc(thr2-25-39), data(V3, V1, V2)), [(2 =< V2)], [], 26). % 2 <= flag1
stmtsrc(26, 'assume(2 <= flag1);').
transition_access( 26, [_, _, r] ).
r(p(pc(thr2-25-39), data(V3, V1, V2)), p(pc(thr2-20-39), data(V3, V1, V2)), [(V2 =< 3)], [], 27). % flag1 <= 3
stmtsrc(27, 'assume(flag1 <= 3);').
transition_access( 27, [_, _, r] ).
r(p(pc(thr2-25-39), data(V3, V1, V2)), p(pc(thr2-27-39), data(V3, V1, V2)), [(V2 >= 1+ 3)], [], 28). % flag1 > 3
stmtsrc(28, 'assume(flag1 > 3);').
transition_access( 28, [_, _, r] ).
r(p(pc(thr2-24-39), data(V3, V1, V2)), p(pc(thr2-26-39), data(V3, V1, V2)), [(2 >= 1+ V2)], [], 29). % 2 > flag1
stmtsrc(29, 'assume(2 > flag1);').
transition_access( 29, [_, _, r] ).
r(p(pc(thr2-23-0), data(V3, V1, V2)), p(pc(thr2-22-40), data(V3, V1, V2)), [], [], 30). % 
stmtsrc(30, 'skip;').
transition_access( 30, [_, _, _] ).
r(p(pc(thr2-22-40), data(V3, V1, V2)), p(pc(thr2-0-25), data(V3, V1p, V2)), [], [V1p = 0], 31). % flag2 := 0
stmtsrc(31, 'flag2=0;').
transition_access( 31, [_, w, _] ).
r(p(pc(thr2-1-0), data(V3, V1, V2)), p(pc(thr2-ret-0), data(V3, V1, V2)), [], [], 32). % 
stmtsrc(32, 'skip;').
transition_access( 32, [_, _, _] ).
r(p(pc(thr2-26-39), data(V3, V1, V2)), p(pc(thr2-23-0), data(V3, V1, V2)), [], [], 33). % 
stmtsrc(33, 'skip;').
transition_access( 33, [_, _, _] ).
r(p(pc(thr2-27-39), data(V3, V1, V2)), p(pc(thr2-23-0), data(V3, V1, V2)), [], [], 34). % 
stmtsrc(34, 'skip;').
transition_access( 34, [_, _, _] ).
r(p(pc(thr2-19-34), data(V3, V1, V2)), p(pc(thr2-17-0), data(V3, V1, V2)), [], [], 35). % 
stmtsrc(35, 'skip;').
transition_access( 35, [_, _, _] ).
r(p(pc(thr2-14-31), data(V3, V1, V2)), p(pc(thr2-12-0), data(V3, V1, V2)), [], [], 36). % 
stmtsrc(36, 'skip;').
transition_access( 36, [_, _, _] ).
r(p(pc(thr2-7-27), data(V3, V1, V2)), p(pc(thr2-5-0), data(V3, V1, V2)), [], [], 37). % 
stmtsrc(37, 'skip;').
transition_access( 37, [_, _, _] ).
% Atomic blocks
% Strengthenings
