:- multifile r/5,implicit_updates/0,var2names/2,preds/2,trans_preds/3,
cube_size/1,start/1,error/1,refinement/1,cutpoint/1,invgen_template/2,
 invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,globals/3,
 bound_var/2,bounding_vars/2,transition_access/2,atomic/3.
refinement(inter).
cube_size(1).
preds(p(_, data(V3, V2, V1, V4, V5)), []).
trans_preds(p(_, data(V3, V2, V1, V4, V5)), p(_, data(V3p, V2p, V1p, V4p, V5p)), []).
var2names(p(pc(_), data(V3, V2, V1, V4, V5)), [(V3, 'y'), (V2, 'x'), (V1, 'b2'), (V4, 'b1'), (V5, 'X')]).
globals(p(pc(_), data(V3, V2, V1, V4, V5)), [(V3, 'y'), (V2, 'x'), (V1, 'b2'), (V4, 'b1'), (V5, 'X')], []).
% start location
start(pc(thr2-0-35)).
% error location
error(pc(thr2-err-0)).
% cutpoint locations
cutpoint(pc(thr2-21-48)). % line 48
cutpoint(pc(thr2-16-46)). % line 46
cutpoint(pc(thr2-8-40)). % line 40
cutpoint(pc(thr2-0-35)). % line 35
% invariant templates
% bound var 
% bounding vars 
bounding_vars(data(V3, V2, V1, V4, V5), []).
% cfg loop exit relation
cfg_exit_relation([(pc(thr2-21-48), pc(thr2-0-35)), (pc(thr2-16-46), pc(thr2-21-48)), (pc(thr2-8-40), pc(thr2-16-46))]).
% 42 transitions
r(p(pc(thr2-0-35), data(V3, V2, V1, V4, V5)), p(pc(thr2-3-37), data(V3, V2, V1, V4, V5)), [], [], 1). % 
stmtsrc(1, 'skip;').
transition_access( 1, [_, _, _, _, _] ).
r(p(pc(thr2-3-37), data(V3, V2, V1, V4, V5)), p(pc(thr2-5-0), data(V3, V2, V1p, V4, V5)), [], [V1p = 1], 2). % b2 := 1
stmtsrc(2, 'b2=1;').
transition_access( 2, [_, _, w, _, _] ).
r(p(pc(thr2-5-0), data(V3, V2, V1, V4, V5)), p(pc(thr2-4-38), data(V3, V2p, V1, V4, V5)), [], [V2p = 2], 3). % x := 2
stmtsrc(3, 'x=2;').
transition_access( 3, [_, w, _, _, _] ).
r(p(pc(thr2-4-38), data(V3, V2, V1, V4, V5)), p(pc(thr2-7-39), data(V3, V2, V1, V4, V5)), [(V3 +1 =< 0)], [], 4). % y < 0
stmtsrc(4, 'assume(y < 0);').
transition_access( 4, [r, _, _, _, _] ).
r(p(pc(thr2-4-38), data(V3, V2, V1, V4, V5)), p(pc(thr2-7-39), data(V3, V2, V1, V4, V5)), [(V3 >= 1+ 0)], [], 5). % y > 0
stmtsrc(5, 'assume(y > 0);').
transition_access( 5, [r, _, _, _, _] ).
r(p(pc(thr2-7-39), data(V3, V2, V1, V4, V5)), p(pc(thr2-8-40), data(V3, V2, V1p, V4, V5)), [], [V1p = 0], 6). % b2 := 0
stmtsrc(6, 'b2=0;').
transition_access( 6, [_, _, w, _, _] ).
r(p(pc(thr2-8-40), data(V3, V2, V1, V4, V5)), p(pc(thr2-11-40), data(V3, V2, V1, V4, V5)), [], [], 7). % 
stmtsrc(7, 'skip;').
transition_access( 7, [_, _, _, _, _] ).
r(p(pc(thr2-11-40), data(V3, V2, V1, V4, V5)), p(pc(thr2-8-40), data(V3, V2, V1, V4, V5)), [(V3 +1 =< 0)], [], 8). % y < 0
stmtsrc(8, 'assume(y < 0);').
transition_access( 8, [r, _, _, _, _] ).
r(p(pc(thr2-11-40), data(V3, V2, V1, V4, V5)), p(pc(thr2-8-40), data(V3, V2, V1, V4, V5)), [(V3 >= 1+ 0)], [], 9). % y > 0
stmtsrc(9, 'assume(y > 0);').
transition_access( 9, [r, _, _, _, _] ).
r(p(pc(thr2-11-40), data(V3, V2, V1, V4, V5)), p(pc(thr2-12-40), data(V3, V2, V1, V4, V5)), [(V3 = 0)], [], 10). % y == 0
stmtsrc(10, 'assume(y == 0);').
transition_access( 10, [r, _, _, _, _] ).
r(p(pc(thr2-10-0), data(V3, V2, V1, V4, V5)), p(pc(thr2-9-41), data(V3, V2, V1, V4, V5)), [], [], 11). % 
stmtsrc(11, 'skip;').
transition_access( 11, [_, _, _, _, _] ).
r(p(pc(thr2-4-38), data(V3, V2, V1, V4, V5)), p(pc(thr2-6-43), data(V3, V2, V1, V4, V5)), [(V3 = 0)], [], 12). % y == 0
stmtsrc(12, 'assume(y == 0);').
transition_access( 12, [r, _, _, _, _] ).
r(p(pc(thr2-6-43), data(V3, V2, V1, V4, V5)), p(pc(thr2-13-44), data(V3p, V2, V1, V4, V5)), [], [V3p = 2], 13). % y := 2
stmtsrc(13, 'y=2;').
transition_access( 13, [w, _, _, _, _] ).
r(p(pc(thr2-13-44), data(V3, V2, V1, V4, V5)), p(pc(thr2-15-45), data(V3, V2, V1, V4, V5)), [(V2 +1 =< 2)], [], 14). % x < 2
stmtsrc(14, 'assume(x < 2);').
transition_access( 14, [_, r, _, _, _] ).
r(p(pc(thr2-13-44), data(V3, V2, V1, V4, V5)), p(pc(thr2-15-45), data(V3, V2, V1, V4, V5)), [(V2 >= 1+ 2)], [], 15). % x > 2
stmtsrc(15, 'assume(x > 2);').
transition_access( 15, [_, r, _, _, _] ).
r(p(pc(thr2-15-45), data(V3, V2, V1, V4, V5)), p(pc(thr2-16-46), data(V3, V2, V1p, V4, V5)), [], [V1p = 0], 16). % b2 := 0
stmtsrc(16, 'b2=0;').
transition_access( 16, [_, _, w, _, _] ).
r(p(pc(thr2-16-46), data(V3, V2, V1, V4, V5)), p(pc(thr2-19-46), data(V3, V2, V1, V4, V5)), [], [], 17). % 
stmtsrc(17, 'skip;').
transition_access( 17, [_, _, _, _, _] ).
r(p(pc(thr2-19-46), data(V3, V2, V1, V4, V5)), p(pc(thr2-16-46), data(V3, V2, V1, V4, V5)), [(V4 >= 1)], [], 18). % b1 >= 1
stmtsrc(18, 'assume(b1 >= 1);').
transition_access( 18, [_, _, _, r, _] ).
r(p(pc(thr2-19-46), data(V3, V2, V1, V4, V5)), p(pc(thr2-20-46), data(V3, V2, V1, V4, V5)), [(V4 +1 =< 1)], [], 19). % b1 < 1
stmtsrc(19, 'assume(b1 < 1);').
transition_access( 19, [_, _, _, r, _] ).
r(p(pc(thr2-18-0), data(V3, V2, V1, V4, V5)), p(pc(thr2-17-47), data(V3, V2, V1, V4, V5)), [], [], 20). % 
stmtsrc(20, 'skip;').
transition_access( 20, [_, _, _, _, _] ).
r(p(pc(thr2-17-47), data(V3, V2, V1, V4, V5)), p(pc(thr2-21-48), data(V3, V2, V1, V4, V5)), [(V3 +1 =< 2)], [], 21). % y < 2
stmtsrc(21, 'assume(y < 2);').
transition_access( 21, [r, _, _, _, _] ).
r(p(pc(thr2-17-47), data(V3, V2, V1, V4, V5)), p(pc(thr2-21-48), data(V3, V2, V1, V4, V5)), [(V3 >= 1+ 2)], [], 22). % y > 2
stmtsrc(22, 'assume(y > 2);').
transition_access( 22, [r, _, _, _, _] ).
r(p(pc(thr2-21-48), data(V3, V2, V1, V4, V5)), p(pc(thr2-24-48), data(V3, V2, V1, V4, V5)), [], [], 23). % 
stmtsrc(23, 'skip;').
transition_access( 23, [_, _, _, _, _] ).
r(p(pc(thr2-24-48), data(V3, V2, V1, V4, V5)), p(pc(thr2-21-48), data(V3, V2, V1, V4, V5)), [(V3 +1 =< 0)], [], 24). % y < 0
stmtsrc(24, 'assume(y < 0);').
transition_access( 24, [r, _, _, _, _] ).
r(p(pc(thr2-24-48), data(V3, V2, V1, V4, V5)), p(pc(thr2-21-48), data(V3, V2, V1, V4, V5)), [(V3 >= 1+ 0)], [], 25). % y > 0
stmtsrc(25, 'assume(y > 0);').
transition_access( 25, [r, _, _, _, _] ).
r(p(pc(thr2-24-48), data(V3, V2, V1, V4, V5)), p(pc(thr2-25-48), data(V3, V2, V1, V4, V5)), [(V3 = 0)], [], 26). % y == 0
stmtsrc(26, 'assume(y == 0);').
transition_access( 26, [r, _, _, _, _] ).
r(p(pc(thr2-23-0), data(V3, V2, V1, V4, V5)), p(pc(thr2-22-49), data(V3, V2, V1, V4, V5)), [], [], 27). % 
stmtsrc(27, 'skip;').
transition_access( 27, [_, _, _, _, _] ).
r(p(pc(thr2-17-47), data(V3, V2, V1, V4, V5)), p(pc(thr2-14-52), data(V3, V2, V1, V4, V5)), [(V3 = 2)], [], 28). % y == 2
stmtsrc(28, 'assume(y == 2);').
transition_access( 28, [r, _, _, _, _] ).
r(p(pc(thr2-13-44), data(V3, V2, V1, V4, V5)), p(pc(thr2-14-52), data(V3, V2, V1, V4, V5)), [(V2 = 2)], [], 29). % x == 2
stmtsrc(29, 'assume(x == 2);').
transition_access( 29, [_, r, _, _, _] ).
r(p(pc(thr2-2-0), data(V3, V2, V1, V4, V5)), p(pc(thr2-1-59), data(V3, V2, V1, V4, V5)), [], [], 30). % 
stmtsrc(30, 'skip;').
transition_access( 30, [_, _, _, _, _] ).
r(p(pc(thr2-1-59), data(V3, V2, V1, V4, V5)), p(pc(thr2-27-0), data(V3, V2, V1, V4, V5p)), [], [V5p = 1], 31). % X := 1
stmtsrc(31, 'X=1;').
transition_access( 31, [_, _, _, _, w] ).
r(p(pc(thr2-27-0), data(V3, V2, V1, V4, V5)), p(pc(thr2-err-0), data(V3, V2, V1, V4, V5)), [(V5 +1 =< 1)], [], 32). % X < 1
stmtsrc(32, 'assume(X < 1);').
transition_access( 32, [_, _, _, _, r] ).
r(p(pc(thr2-27-0), data(V3, V2, V1, V4, V5)), p(pc(thr2-28-0), data(V3, V2, V1, V4, V5)), [(V5 >= 1)], [], 33). % X >= 1
stmtsrc(33, 'assume(X >= 1);').
transition_access( 33, [_, _, _, _, r] ).
r(p(pc(thr2-28-0), data(V3, V2, V1, V4, V5)), p(pc(thr2-29-0), data(V3p, V2, V1, V4, V5)), [], [V3p = 0], 34). % y := 0
stmtsrc(34, 'y=0;').
transition_access( 34, [w, _, _, _, _] ).
r(p(pc(thr2-29-0), data(V3, V2, V1, V4, V5)), p(pc(thr2-26-60), data(V3, V2, V1p, V4, V5)), [], [V1p = 0], 35). % b2 := 0
stmtsrc(35, 'b2=0;').
transition_access( 35, [_, _, w, _, _] ).
r(p(pc(thr2-26-60), data(V3, V2, V1, V4, V5)), p(pc(thr2-ret-0), data(V3, V2, V1, V4, V5)), [], [], 36). % 
stmtsrc(36, 'skip;').
transition_access( 36, [_, _, _, _, _] ).
r(p(pc(thr2-14-52), data(V3, V2, V1, V4, V5)), p(pc(thr2-2-0), data(V3, V2, V1, V4, V5)), [], [], 37). % 
stmtsrc(37, 'skip;').
transition_access( 37, [_, _, _, _, _] ).
r(p(pc(thr2-22-49), data(V3, V2, V1, V4, V5)), p(pc(thr2-0-35), data(V3, V2, V1, V4, V5)), [], [], 38). % 
stmtsrc(38, 'skip;').
transition_access( 38, [_, _, _, _, _] ).
r(p(pc(thr2-25-48), data(V3, V2, V1, V4, V5)), p(pc(thr2-23-0), data(V3, V2, V1, V4, V5)), [], [], 39). % 
stmtsrc(39, 'skip;').
transition_access( 39, [_, _, _, _, _] ).
r(p(pc(thr2-20-46), data(V3, V2, V1, V4, V5)), p(pc(thr2-18-0), data(V3, V2, V1, V4, V5)), [], [], 40). % 
stmtsrc(40, 'skip;').
transition_access( 40, [_, _, _, _, _] ).
r(p(pc(thr2-9-41), data(V3, V2, V1, V4, V5)), p(pc(thr2-0-35), data(V3, V2, V1, V4, V5)), [], [], 41). % 
stmtsrc(41, 'skip;').
transition_access( 41, [_, _, _, _, _] ).
r(p(pc(thr2-12-40), data(V3, V2, V1, V4, V5)), p(pc(thr2-10-0), data(V3, V2, V1, V4, V5)), [], [], 42). % 
stmtsrc(42, 'skip;').
transition_access( 42, [_, _, _, _, _] ).
% Atomic blocks
% Strengthenings
