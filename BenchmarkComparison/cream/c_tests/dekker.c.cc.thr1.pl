:- multifile r/5,implicit_updates/0,var2names/2,preds/2,trans_preds/3,
cube_size/1,start/1,error/1,refinement/1,cutpoint/1,invgen_template/2,
 invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,globals/3,
 bound_var/2,bounding_vars/2,transition_access/2,atomic/3.
refinement(inter).
cube_size(1).
preds(p(_, data(V4, V3, V2, V1)), []).
trans_preds(p(_, data(V4, V3, V2, V1)), p(_, data(V4p, V3p, V2p, V1p)), []).
var2names(p(pc(_), data(V4, V3, V2, V1)), [(V4, 'x'), (V3, 'turn'), (V2, 'flag2'), (V1, 'flag1')]).
globals(p(pc(_), data(V4, V3, V2, V1)), [(V4, 'x'), (V3, 'turn'), (V2, 'flag2'), (V1, 'flag1')], [V1=0, V2=0, V3=0]).
% start location
start(pc(thr1-0-8)).
% error location
error(pc(thr1-err-0)).
% cutpoint locations
cutpoint(pc(thr1-8-12)). % line 12
cutpoint(pc(thr1-1-9)). % line 9
% invariant templates
% bound var 
% bounding vars 
bounding_vars(data(V4, V3, V2, V1), []).
% cfg loop exit relation
cfg_exit_relation([(pc(thr1-8-12), pc(thr1-1-9))]).
% 23 transitions
r(p(pc(thr1-0-8), data(V4, V3, V2, V1)), p(pc(thr1-1-9), data(V4, V3, V2, V1p)), [], [V1p = 1], 1). % flag1 := 1
stmtsrc(1, 'flag1=1;').
transition_access( 1, [_, _, _, w] ).
r(p(pc(thr1-1-9), data(V4, V3, V2, V1)), p(pc(thr1-4-9), data(V4, V3, V2, V1)), [], [], 2). % 
stmtsrc(2, 'skip;').
transition_access( 2, [_, _, _, _] ).
r(p(pc(thr1-4-9), data(V4, V3, V2, V1)), p(pc(thr1-5-10), data(V4, V3, V2, V1)), [(V2 >= 1)], [], 3). % flag2 >= 1
stmtsrc(3, 'assume(flag2 >= 1);').
transition_access( 3, [_, _, r, _] ).
r(p(pc(thr1-4-9), data(V4, V3, V2, V1)), p(pc(thr1-6-9), data(V4, V3, V2, V1)), [(V2 +1 =< 1)], [], 4). % flag2 < 1
stmtsrc(4, 'assume(flag2 < 1);').
transition_access( 4, [_, _, r, _] ).
r(p(pc(thr1-5-10), data(V4, V3, V2, V1)), p(pc(thr1-7-11), data(V4, V3, V2, V1)), [(V3 +1 =< 0)], [], 5). % turn < 0
stmtsrc(5, 'assume(turn < 0);').
transition_access( 5, [_, r, _, _] ).
r(p(pc(thr1-5-10), data(V4, V3, V2, V1)), p(pc(thr1-7-11), data(V4, V3, V2, V1)), [(V3 >= 1+ 0)], [], 6). % turn > 0
stmtsrc(6, 'assume(turn > 0);').
transition_access( 6, [_, r, _, _] ).
r(p(pc(thr1-7-11), data(V4, V3, V2, V1)), p(pc(thr1-8-12), data(V4, V3, V2, V1p)), [], [V1p = 0], 7). % flag1 := 0
stmtsrc(7, 'flag1=0;').
transition_access( 7, [_, _, _, w] ).
r(p(pc(thr1-8-12), data(V4, V3, V2, V1)), p(pc(thr1-11-12), data(V4, V3, V2, V1)), [], [], 8). % 
stmtsrc(8, 'skip;').
transition_access( 8, [_, _, _, _] ).
r(p(pc(thr1-11-12), data(V4, V3, V2, V1)), p(pc(thr1-8-12), data(V4, V3, V2, V1)), [(V3 +1 =< 0)], [], 9). % turn < 0
stmtsrc(9, 'assume(turn < 0);').
transition_access( 9, [_, r, _, _] ).
r(p(pc(thr1-11-12), data(V4, V3, V2, V1)), p(pc(thr1-8-12), data(V4, V3, V2, V1)), [(V3 >= 1+ 0)], [], 10). % turn > 0
stmtsrc(10, 'assume(turn > 0);').
transition_access( 10, [_, r, _, _] ).
r(p(pc(thr1-11-12), data(V4, V3, V2, V1)), p(pc(thr1-12-12), data(V4, V3, V2, V1)), [(V3 = 0)], [], 11). % turn == 0
stmtsrc(11, 'assume(turn == 0);').
transition_access( 11, [_, r, _, _] ).
r(p(pc(thr1-10-0), data(V4, V3, V2, V1)), p(pc(thr1-9-13), data(V4, V3, V2, V1)), [], [], 12). % 
stmtsrc(12, 'skip;').
transition_access( 12, [_, _, _, _] ).
r(p(pc(thr1-9-13), data(V4, V3, V2, V1)), p(pc(thr1-1-9), data(V4, V3, V2, V1p)), [], [V1p = 1], 13). % flag1 := 1
stmtsrc(13, 'flag1=1;').
transition_access( 13, [_, _, _, w] ).
r(p(pc(thr1-5-10), data(V4, V3, V2, V1)), p(pc(thr1-1-9), data(V4, V3, V2, V1)), [(V3 = 0)], [], 14). % turn == 0
stmtsrc(14, 'assume(turn == 0);').
transition_access( 14, [_, r, _, _] ).
r(p(pc(thr1-3-0), data(V4, V3, V2, V1)), p(pc(thr1-2-21), data(V4, V3, V2, V1)), [], [], 15). % 
stmtsrc(15, 'skip;').
transition_access( 15, [_, _, _, _] ).
r(p(pc(thr1-2-21), data(V4, V3, V2, V1)), p(pc(thr1-14-0), data(V4p, V3, V2, V1)), [], [V4p = 0], 16). % x := 0
stmtsrc(16, 'x=0;').
transition_access( 16, [w, _, _, _] ).
r(p(pc(thr1-14-0), data(V4, V3, V2, V1)), p(pc(thr1-err-0), data(V4, V3, V2, V1)), [(V4 >= 1+ 0)], [], 17). % x > 0
stmtsrc(17, 'assume(x > 0);').
transition_access( 17, [r, _, _, _] ).
r(p(pc(thr1-14-0), data(V4, V3, V2, V1)), p(pc(thr1-15-0), data(V4, V3, V2, V1)), [(V4 =< 0)], [], 18). % x <= 0
stmtsrc(18, 'assume(x <= 0);').
transition_access( 18, [r, _, _, _] ).
r(p(pc(thr1-15-0), data(V4, V3, V2, V1)), p(pc(thr1-16-0), data(V4, V3p, V2, V1)), [], [V3p = 1], 19). % turn := 1
stmtsrc(19, 'turn=1;').
transition_access( 19, [_, w, _, _] ).
r(p(pc(thr1-16-0), data(V4, V3, V2, V1)), p(pc(thr1-13-22), data(V4, V3, V2, V1p)), [], [V1p = 0], 20). % flag1 := 0
stmtsrc(20, 'flag1=0;').
transition_access( 20, [_, _, _, w] ).
r(p(pc(thr1-13-22), data(V4, V3, V2, V1)), p(pc(thr1-ret-0), data(V4, V3, V2, V1)), [], [], 21). % 
stmtsrc(21, 'skip;').
transition_access( 21, [_, _, _, _] ).
r(p(pc(thr1-12-12), data(V4, V3, V2, V1)), p(pc(thr1-10-0), data(V4, V3, V2, V1)), [], [], 22). % 
stmtsrc(22, 'skip;').
transition_access( 22, [_, _, _, _] ).
r(p(pc(thr1-6-9), data(V4, V3, V2, V1)), p(pc(thr1-3-0), data(V4, V3, V2, V1)), [], [], 23). % 
stmtsrc(23, 'skip;').
transition_access( 23, [_, _, _, _] ).
% Atomic blocks
% Strengthenings
