:- multifile r/5,implicit_updates/0,var2names/2,preds/2,trans_preds/3,
cube_size/1,start/1,error/1,refinement/1,cutpoint/1,invgen_template/2,
 invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,globals/3,
 bound_var/2,bounding_vars/2,transition_access/2,atomic/3.
refinement(inter).
cube_size(1).
preds(p(_, data(V3, V2, V1)), []).
trans_preds(p(_, data(V3, V2, V1)), p(_, data(V3p, V2p, V1p)), []).
var2names(p(pc(_), data(V3, V2, V1)), [(V3, 'x'), (V2, 'flag2'), (V1, 'flag1')]).
globals(p(pc(_), data(V3, V2, V1)), [(V3, 'x'), (V2, 'flag2'), (V1, 'flag1')], [V1=0, V2=0]).
% start location
start(pc(thr1-0-5)).
% error location
error(pc(thr1-err-0)).
% cutpoint locations
cutpoint(pc(thr1-20-19)). % line 19
cutpoint(pc(thr1-15-14)). % line 14
cutpoint(pc(thr1-11-11)). % line 11
cutpoint(pc(thr1-3-7)). % line 7
cutpoint(pc(thr1-0-5)). % line 5
% invariant templates
% bound var 
% bounding vars 
bounding_vars(data(V3, V2, V1), []).
% cfg loop exit relation
cfg_exit_relation([(pc(thr1-20-19), pc(thr1-0-5)), (pc(thr1-15-14), pc(thr1-20-19)), (pc(thr1-11-11), pc(thr1-15-14)), (pc(thr1-3-7), pc(thr1-11-11))]).
% 37 transitions
r(p(pc(thr1-0-5), data(V3, V2, V1)), p(pc(thr1-2-6), data(V3, V2, V1)), [], [], 1). % 
stmtsrc(1, 'skip;').
transition_access( 1, [_, _, _] ).
r(p(pc(thr1-2-6), data(V3, V2, V1)), p(pc(thr1-3-7), data(V3, V2, V1p)), [], [V1p = 1], 2). % flag1 := 1
stmtsrc(2, 'flag1=1;').
transition_access( 2, [_, _, w] ).
r(p(pc(thr1-3-7), data(V3, V2, V1)), p(pc(thr1-6-7), data(V3, V2, V1)), [], [], 3). % 
stmtsrc(3, 'skip;').
transition_access( 3, [_, _, _] ).
r(p(pc(thr1-6-7), data(V3, V2, V1)), p(pc(thr1-3-7), data(V3, V2, V1)), [(V2 >= 3)], [], 4). % flag2 >= 3
stmtsrc(4, 'assume(flag2 >= 3);').
transition_access( 4, [_, r, _] ).
r(p(pc(thr1-6-7), data(V3, V2, V1)), p(pc(thr1-7-7), data(V3, V2, V1)), [(V2 +1 =< 3)], [], 5). % flag2 < 3
stmtsrc(5, 'assume(flag2 < 3);').
transition_access( 5, [_, r, _] ).
r(p(pc(thr1-5-0), data(V3, V2, V1)), p(pc(thr1-4-8), data(V3, V2, V1)), [], [], 6). % 
stmtsrc(6, 'skip;').
transition_access( 6, [_, _, _] ).
r(p(pc(thr1-4-8), data(V3, V2, V1)), p(pc(thr1-8-9), data(V3, V2, V1p)), [], [V1p = 3], 7). % flag1 := 3
stmtsrc(7, 'flag1=3;').
transition_access( 7, [_, _, w] ).
r(p(pc(thr1-8-9), data(V3, V2, V1)), p(pc(thr1-10-10), data(V3, V2, V1)), [(V2 = 1)], [], 8). % flag2 == 1
stmtsrc(8, 'assume(flag2 == 1);').
transition_access( 8, [_, r, _] ).
r(p(pc(thr1-10-10), data(V3, V2, V1)), p(pc(thr1-11-11), data(V3, V2, V1p)), [], [V1p = 2], 9). % flag1 := 2
stmtsrc(9, 'flag1=2;').
transition_access( 9, [_, _, w] ).
r(p(pc(thr1-11-11), data(V3, V2, V1)), p(pc(thr1-13-11), data(V3, V2, V1)), [], [], 10). % 
stmtsrc(10, 'skip;').
transition_access( 10, [_, _, _] ).
r(p(pc(thr1-13-11), data(V3, V2, V1)), p(pc(thr1-11-11), data(V3, V2, V1)), [(V2 +1 =< 4)], [], 11). % flag2 < 4
stmtsrc(11, 'assume(flag2 < 4);').
transition_access( 11, [_, r, _] ).
r(p(pc(thr1-13-11), data(V3, V2, V1)), p(pc(thr1-11-11), data(V3, V2, V1)), [(V2 >= 1+ 4)], [], 12). % flag2 > 4
stmtsrc(12, 'assume(flag2 > 4);').
transition_access( 12, [_, r, _] ).
r(p(pc(thr1-13-11), data(V3, V2, V1)), p(pc(thr1-14-11), data(V3, V2, V1)), [(V2 = 4)], [], 13). % flag2 == 4
stmtsrc(13, 'assume(flag2 == 4);').
transition_access( 13, [_, r, _] ).
r(p(pc(thr1-12-0), data(V3, V2, V1)), p(pc(thr1-9-13), data(V3, V2, V1)), [], [], 14). % 
stmtsrc(14, 'skip;').
transition_access( 14, [_, _, _] ).
r(p(pc(thr1-8-9), data(V3, V2, V1)), p(pc(thr1-9-13), data(V3, V2, V1)), [(V2 +1 =< 1)], [], 15). % flag2 < 1
stmtsrc(15, 'assume(flag2 < 1);').
transition_access( 15, [_, r, _] ).
r(p(pc(thr1-8-9), data(V3, V2, V1)), p(pc(thr1-9-13), data(V3, V2, V1)), [(V2 >= 1+ 1)], [], 16). % flag2 > 1
stmtsrc(16, 'assume(flag2 > 1);').
transition_access( 16, [_, r, _] ).
r(p(pc(thr1-9-13), data(V3, V2, V1)), p(pc(thr1-15-14), data(V3, V2, V1p)), [], [V1p = 4], 17). % flag1 := 4
stmtsrc(17, 'flag1=4;').
transition_access( 17, [_, _, w] ).
r(p(pc(thr1-15-14), data(V3, V2, V1)), p(pc(thr1-18-14), data(V3, V2, V1)), [], [], 18). % 
stmtsrc(18, 'skip;').
transition_access( 18, [_, _, _] ).
r(p(pc(thr1-18-14), data(V3, V2, V1)), p(pc(thr1-15-14), data(V3, V2, V1)), [(V2 >= 2)], [], 19). % flag2 >= 2
stmtsrc(19, 'assume(flag2 >= 2);').
transition_access( 19, [_, r, _] ).
r(p(pc(thr1-18-14), data(V3, V2, V1)), p(pc(thr1-19-14), data(V3, V2, V1)), [(V2 +1 =< 2)], [], 20). % flag2 < 2
stmtsrc(20, 'assume(flag2 < 2);').
transition_access( 20, [_, r, _] ).
r(p(pc(thr1-17-0), data(V3, V2, V1)), p(pc(thr1-16-17), data(V3, V2, V1)), [], [], 21). % 
stmtsrc(21, 'skip;').
transition_access( 21, [_, _, _] ).
r(p(pc(thr1-16-17), data(V3, V2, V1)), p(pc(thr1-21-0), data(V3p, V2, V1)), [], [V3p = 0], 22). % x := 0
stmtsrc(22, 'x=0;').
transition_access( 22, [w, _, _] ).
r(p(pc(thr1-21-0), data(V3, V2, V1)), p(pc(thr1-err-0), data(V3, V2, V1)), [(V3 >= 1+ 0)], [], 23). % x > 0
stmtsrc(23, 'assume(x > 0);').
transition_access( 23, [r, _, _] ).
r(p(pc(thr1-21-0), data(V3, V2, V1)), p(pc(thr1-20-19), data(V3, V2, V1)), [(V3 =< 0)], [], 24). % x <= 0
stmtsrc(24, 'assume(x <= 0);').
transition_access( 24, [r, _, _] ).
r(p(pc(thr1-20-19), data(V3, V2, V1)), p(pc(thr1-24-19), data(V3, V2, V1)), [], [], 25). % 
stmtsrc(25, 'skip;').
transition_access( 25, [_, _, _] ).
r(p(pc(thr1-24-19), data(V3, V2, V1)), p(pc(thr1-25-19), data(V3, V2, V1)), [(2 =< V2)], [], 26). % 2 <= flag2
stmtsrc(26, 'assume(2 <= flag2);').
transition_access( 26, [_, r, _] ).
r(p(pc(thr1-25-19), data(V3, V2, V1)), p(pc(thr1-20-19), data(V3, V2, V1)), [(V2 =< 3)], [], 27). % flag2 <= 3
stmtsrc(27, 'assume(flag2 <= 3);').
transition_access( 27, [_, r, _] ).
r(p(pc(thr1-25-19), data(V3, V2, V1)), p(pc(thr1-27-19), data(V3, V2, V1)), [(V2 >= 1+ 3)], [], 28). % flag2 > 3
stmtsrc(28, 'assume(flag2 > 3);').
transition_access( 28, [_, r, _] ).
r(p(pc(thr1-24-19), data(V3, V2, V1)), p(pc(thr1-26-19), data(V3, V2, V1)), [(2 >= 1+ V2)], [], 29). % 2 > flag2
stmtsrc(29, 'assume(2 > flag2);').
transition_access( 29, [_, r, _] ).
r(p(pc(thr1-23-0), data(V3, V2, V1)), p(pc(thr1-22-20), data(V3, V2, V1)), [], [], 30). % 
stmtsrc(30, 'skip;').
transition_access( 30, [_, _, _] ).
r(p(pc(thr1-22-20), data(V3, V2, V1)), p(pc(thr1-0-5), data(V3, V2, V1p)), [], [V1p = 0], 31). % flag1 := 0
stmtsrc(31, 'flag1=0;').
transition_access( 31, [_, _, w] ).
r(p(pc(thr1-1-0), data(V3, V2, V1)), p(pc(thr1-ret-0), data(V3, V2, V1)), [], [], 32). % 
stmtsrc(32, 'skip;').
transition_access( 32, [_, _, _] ).
r(p(pc(thr1-26-19), data(V3, V2, V1)), p(pc(thr1-23-0), data(V3, V2, V1)), [], [], 33). % 
stmtsrc(33, 'skip;').
transition_access( 33, [_, _, _] ).
r(p(pc(thr1-27-19), data(V3, V2, V1)), p(pc(thr1-23-0), data(V3, V2, V1)), [], [], 34). % 
stmtsrc(34, 'skip;').
transition_access( 34, [_, _, _] ).
r(p(pc(thr1-19-14), data(V3, V2, V1)), p(pc(thr1-17-0), data(V3, V2, V1)), [], [], 35). % 
stmtsrc(35, 'skip;').
transition_access( 35, [_, _, _] ).
r(p(pc(thr1-14-11), data(V3, V2, V1)), p(pc(thr1-12-0), data(V3, V2, V1)), [], [], 36). % 
stmtsrc(36, 'skip;').
transition_access( 36, [_, _, _] ).
r(p(pc(thr1-7-7), data(V3, V2, V1)), p(pc(thr1-5-0), data(V3, V2, V1)), [], [], 37). % 
stmtsrc(37, 'skip;').
transition_access( 37, [_, _, _] ).
% Atomic blocks
% Strengthenings
