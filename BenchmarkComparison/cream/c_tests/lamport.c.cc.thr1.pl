:- multifile r/5,implicit_updates/0,var2names/2,preds/2,trans_preds/3,
cube_size/1,start/1,error/1,refinement/1,cutpoint/1,invgen_template/2,
 invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,globals/3,
 bound_var/2,bounding_vars/2,transition_access/2,atomic/3.
refinement(inter).
cube_size(1).
preds(p(_, data(V3, V2, V4, V1, V5)), []).
trans_preds(p(_, data(V3, V2, V4, V1, V5)), p(_, data(V3p, V2p, V4p, V1p, V5p)), []).
var2names(p(pc(_), data(V3, V2, V4, V1, V5)), [(V3, 'y'), (V2, 'x'), (V4, 'b2'), (V1, 'b1'), (V5, 'X')]).
globals(p(pc(_), data(V3, V2, V4, V1, V5)), [(V3, 'y'), (V2, 'x'), (V4, 'b2'), (V1, 'b1'), (V5, 'X')], []).
% start location
start(pc(thr1-0-7)).
% error location
error(pc(thr1-err-0)).
% cutpoint locations
cutpoint(pc(thr1-21-20)). % line 20
cutpoint(pc(thr1-16-18)). % line 18
cutpoint(pc(thr1-8-12)). % line 12
cutpoint(pc(thr1-0-7)). % line 7
% invariant templates
% bound var 
% bounding vars 
bounding_vars(data(V3, V2, V4, V1, V5), []).
% cfg loop exit relation
cfg_exit_relation([(pc(thr1-21-20), pc(thr1-0-7)), (pc(thr1-16-18), pc(thr1-21-20)), (pc(thr1-8-12), pc(thr1-16-18))]).
% 42 transitions
r(p(pc(thr1-0-7), data(V3, V2, V4, V1, V5)), p(pc(thr1-3-9), data(V3, V2, V4, V1, V5)), [], [], 1). % 
stmtsrc(1, 'skip;').
transition_access( 1, [_, _, _, _, _] ).
r(p(pc(thr1-3-9), data(V3, V2, V4, V1, V5)), p(pc(thr1-5-0), data(V3, V2, V4, V1p, V5)), [], [V1p = 1], 2). % b1 := 1
stmtsrc(2, 'b1=1;').
transition_access( 2, [_, _, _, w, _] ).
r(p(pc(thr1-5-0), data(V3, V2, V4, V1, V5)), p(pc(thr1-4-10), data(V3, V2p, V4, V1, V5)), [], [V2p = 1], 3). % x := 1
stmtsrc(3, 'x=1;').
transition_access( 3, [_, w, _, _, _] ).
r(p(pc(thr1-4-10), data(V3, V2, V4, V1, V5)), p(pc(thr1-7-11), data(V3, V2, V4, V1, V5)), [(V3 +1 =< 0)], [], 4). % y < 0
stmtsrc(4, 'assume(y < 0);').
transition_access( 4, [r, _, _, _, _] ).
r(p(pc(thr1-4-10), data(V3, V2, V4, V1, V5)), p(pc(thr1-7-11), data(V3, V2, V4, V1, V5)), [(V3 >= 1+ 0)], [], 5). % y > 0
stmtsrc(5, 'assume(y > 0);').
transition_access( 5, [r, _, _, _, _] ).
r(p(pc(thr1-7-11), data(V3, V2, V4, V1, V5)), p(pc(thr1-8-12), data(V3, V2, V4, V1p, V5)), [], [V1p = 0], 6). % b1 := 0
stmtsrc(6, 'b1=0;').
transition_access( 6, [_, _, _, w, _] ).
r(p(pc(thr1-8-12), data(V3, V2, V4, V1, V5)), p(pc(thr1-11-12), data(V3, V2, V4, V1, V5)), [], [], 7). % 
stmtsrc(7, 'skip;').
transition_access( 7, [_, _, _, _, _] ).
r(p(pc(thr1-11-12), data(V3, V2, V4, V1, V5)), p(pc(thr1-8-12), data(V3, V2, V4, V1, V5)), [(V3 +1 =< 0)], [], 8). % y < 0
stmtsrc(8, 'assume(y < 0);').
transition_access( 8, [r, _, _, _, _] ).
r(p(pc(thr1-11-12), data(V3, V2, V4, V1, V5)), p(pc(thr1-8-12), data(V3, V2, V4, V1, V5)), [(V3 >= 1+ 0)], [], 9). % y > 0
stmtsrc(9, 'assume(y > 0);').
transition_access( 9, [r, _, _, _, _] ).
r(p(pc(thr1-11-12), data(V3, V2, V4, V1, V5)), p(pc(thr1-12-12), data(V3, V2, V4, V1, V5)), [(V3 = 0)], [], 10). % y == 0
stmtsrc(10, 'assume(y == 0);').
transition_access( 10, [r, _, _, _, _] ).
r(p(pc(thr1-10-0), data(V3, V2, V4, V1, V5)), p(pc(thr1-9-13), data(V3, V2, V4, V1, V5)), [], [], 11). % 
stmtsrc(11, 'skip;').
transition_access( 11, [_, _, _, _, _] ).
r(p(pc(thr1-4-10), data(V3, V2, V4, V1, V5)), p(pc(thr1-6-15), data(V3, V2, V4, V1, V5)), [(V3 = 0)], [], 12). % y == 0
stmtsrc(12, 'assume(y == 0);').
transition_access( 12, [r, _, _, _, _] ).
r(p(pc(thr1-6-15), data(V3, V2, V4, V1, V5)), p(pc(thr1-13-16), data(V3p, V2, V4, V1, V5)), [], [V3p = 1], 13). % y := 1
stmtsrc(13, 'y=1;').
transition_access( 13, [w, _, _, _, _] ).
r(p(pc(thr1-13-16), data(V3, V2, V4, V1, V5)), p(pc(thr1-15-17), data(V3, V2, V4, V1, V5)), [(V2 +1 =< 1)], [], 14). % x < 1
stmtsrc(14, 'assume(x < 1);').
transition_access( 14, [_, r, _, _, _] ).
r(p(pc(thr1-13-16), data(V3, V2, V4, V1, V5)), p(pc(thr1-15-17), data(V3, V2, V4, V1, V5)), [(V2 >= 1+ 1)], [], 15). % x > 1
stmtsrc(15, 'assume(x > 1);').
transition_access( 15, [_, r, _, _, _] ).
r(p(pc(thr1-15-17), data(V3, V2, V4, V1, V5)), p(pc(thr1-16-18), data(V3, V2, V4, V1p, V5)), [], [V1p = 0], 16). % b1 := 0
stmtsrc(16, 'b1=0;').
transition_access( 16, [_, _, _, w, _] ).
r(p(pc(thr1-16-18), data(V3, V2, V4, V1, V5)), p(pc(thr1-19-18), data(V3, V2, V4, V1, V5)), [], [], 17). % 
stmtsrc(17, 'skip;').
transition_access( 17, [_, _, _, _, _] ).
r(p(pc(thr1-19-18), data(V3, V2, V4, V1, V5)), p(pc(thr1-16-18), data(V3, V2, V4, V1, V5)), [(V4 >= 1)], [], 18). % b2 >= 1
stmtsrc(18, 'assume(b2 >= 1);').
transition_access( 18, [_, _, r, _, _] ).
r(p(pc(thr1-19-18), data(V3, V2, V4, V1, V5)), p(pc(thr1-20-18), data(V3, V2, V4, V1, V5)), [(V4 +1 =< 1)], [], 19). % b2 < 1
stmtsrc(19, 'assume(b2 < 1);').
transition_access( 19, [_, _, r, _, _] ).
r(p(pc(thr1-18-0), data(V3, V2, V4, V1, V5)), p(pc(thr1-17-19), data(V3, V2, V4, V1, V5)), [], [], 20). % 
stmtsrc(20, 'skip;').
transition_access( 20, [_, _, _, _, _] ).
r(p(pc(thr1-17-19), data(V3, V2, V4, V1, V5)), p(pc(thr1-21-20), data(V3, V2, V4, V1, V5)), [(V3 +1 =< 1)], [], 21). % y < 1
stmtsrc(21, 'assume(y < 1);').
transition_access( 21, [r, _, _, _, _] ).
r(p(pc(thr1-17-19), data(V3, V2, V4, V1, V5)), p(pc(thr1-21-20), data(V3, V2, V4, V1, V5)), [(V3 >= 1+ 1)], [], 22). % y > 1
stmtsrc(22, 'assume(y > 1);').
transition_access( 22, [r, _, _, _, _] ).
r(p(pc(thr1-21-20), data(V3, V2, V4, V1, V5)), p(pc(thr1-24-20), data(V3, V2, V4, V1, V5)), [], [], 23). % 
stmtsrc(23, 'skip;').
transition_access( 23, [_, _, _, _, _] ).
r(p(pc(thr1-24-20), data(V3, V2, V4, V1, V5)), p(pc(thr1-21-20), data(V3, V2, V4, V1, V5)), [(V3 +1 =< 0)], [], 24). % y < 0
stmtsrc(24, 'assume(y < 0);').
transition_access( 24, [r, _, _, _, _] ).
r(p(pc(thr1-24-20), data(V3, V2, V4, V1, V5)), p(pc(thr1-21-20), data(V3, V2, V4, V1, V5)), [(V3 >= 1+ 0)], [], 25). % y > 0
stmtsrc(25, 'assume(y > 0);').
transition_access( 25, [r, _, _, _, _] ).
r(p(pc(thr1-24-20), data(V3, V2, V4, V1, V5)), p(pc(thr1-25-20), data(V3, V2, V4, V1, V5)), [(V3 = 0)], [], 26). % y == 0
stmtsrc(26, 'assume(y == 0);').
transition_access( 26, [r, _, _, _, _] ).
r(p(pc(thr1-23-0), data(V3, V2, V4, V1, V5)), p(pc(thr1-22-21), data(V3, V2, V4, V1, V5)), [], [], 27). % 
stmtsrc(27, 'skip;').
transition_access( 27, [_, _, _, _, _] ).
r(p(pc(thr1-17-19), data(V3, V2, V4, V1, V5)), p(pc(thr1-14-24), data(V3, V2, V4, V1, V5)), [(V3 = 1)], [], 28). % y == 1
stmtsrc(28, 'assume(y == 1);').
transition_access( 28, [r, _, _, _, _] ).
r(p(pc(thr1-13-16), data(V3, V2, V4, V1, V5)), p(pc(thr1-14-24), data(V3, V2, V4, V1, V5)), [(V2 = 1)], [], 29). % x == 1
stmtsrc(29, 'assume(x == 1);').
transition_access( 29, [_, r, _, _, _] ).
r(p(pc(thr1-2-0), data(V3, V2, V4, V1, V5)), p(pc(thr1-1-31), data(V3, V2, V4, V1, V5)), [], [], 30). % 
stmtsrc(30, 'skip;').
transition_access( 30, [_, _, _, _, _] ).
r(p(pc(thr1-1-31), data(V3, V2, V4, V1, V5)), p(pc(thr1-27-0), data(V3, V2, V4, V1, V5p)), [], [V5p = 0], 31). % X := 0
stmtsrc(31, 'X=0;').
transition_access( 31, [_, _, _, _, w] ).
r(p(pc(thr1-27-0), data(V3, V2, V4, V1, V5)), p(pc(thr1-err-0), data(V3, V2, V4, V1, V5)), [(V5 >= 1+ 0)], [], 32). % X > 0
stmtsrc(32, 'assume(X > 0);').
transition_access( 32, [_, _, _, _, r] ).
r(p(pc(thr1-27-0), data(V3, V2, V4, V1, V5)), p(pc(thr1-28-0), data(V3, V2, V4, V1, V5)), [(V5 =< 0)], [], 33). % X <= 0
stmtsrc(33, 'assume(X <= 0);').
transition_access( 33, [_, _, _, _, r] ).
r(p(pc(thr1-28-0), data(V3, V2, V4, V1, V5)), p(pc(thr1-29-0), data(V3p, V2, V4, V1, V5)), [], [V3p = 0], 34). % y := 0
stmtsrc(34, 'y=0;').
transition_access( 34, [w, _, _, _, _] ).
r(p(pc(thr1-29-0), data(V3, V2, V4, V1, V5)), p(pc(thr1-26-32), data(V3, V2, V4, V1p, V5)), [], [V1p = 0], 35). % b1 := 0
stmtsrc(35, 'b1=0;').
transition_access( 35, [_, _, _, w, _] ).
r(p(pc(thr1-26-32), data(V3, V2, V4, V1, V5)), p(pc(thr1-ret-0), data(V3, V2, V4, V1, V5)), [], [], 36). % 
stmtsrc(36, 'skip;').
transition_access( 36, [_, _, _, _, _] ).
r(p(pc(thr1-14-24), data(V3, V2, V4, V1, V5)), p(pc(thr1-2-0), data(V3, V2, V4, V1, V5)), [], [], 37). % 
stmtsrc(37, 'skip;').
transition_access( 37, [_, _, _, _, _] ).
r(p(pc(thr1-22-21), data(V3, V2, V4, V1, V5)), p(pc(thr1-0-7), data(V3, V2, V4, V1, V5)), [], [], 38). % 
stmtsrc(38, 'skip;').
transition_access( 38, [_, _, _, _, _] ).
r(p(pc(thr1-25-20), data(V3, V2, V4, V1, V5)), p(pc(thr1-23-0), data(V3, V2, V4, V1, V5)), [], [], 39). % 
stmtsrc(39, 'skip;').
transition_access( 39, [_, _, _, _, _] ).
r(p(pc(thr1-20-18), data(V3, V2, V4, V1, V5)), p(pc(thr1-18-0), data(V3, V2, V4, V1, V5)), [], [], 40). % 
stmtsrc(40, 'skip;').
transition_access( 40, [_, _, _, _, _] ).
r(p(pc(thr1-9-13), data(V3, V2, V4, V1, V5)), p(pc(thr1-0-7), data(V3, V2, V4, V1, V5)), [], [], 41). % 
stmtsrc(41, 'skip;').
transition_access( 41, [_, _, _, _, _] ).
r(p(pc(thr1-12-12), data(V3, V2, V4, V1, V5)), p(pc(thr1-10-0), data(V3, V2, V4, V1, V5)), [], [], 42). % 
stmtsrc(42, 'skip;').
transition_access( 42, [_, _, _, _, _] ).
% Atomic blocks
% Strengthenings
