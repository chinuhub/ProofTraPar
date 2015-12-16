:- multifile r/5,implicit_updates/0,var2names/2,preds/2,trans_preds/3,
cube_size/1,start/1,error/1,refinement/1,cutpoint/1,invgen_template/2,
 invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,globals/3,
 bound_var/2,bounding_vars/2,transition_access/2,atomic/3.
refinement(inter).
cube_size(1).
preds(p(_, data(V4, V2, V3, V1)), []).
trans_preds(p(_, data(V4, V2, V3, V1)), p(_, data(V4p, V2p, V3p, V1p)), []).
var2names(p(pc(_), data(V4, V2, V3, V1)), [(V4, 'x'), (V2, 'turn'), (V3, 'flag2'), (V1, 'flag1')]).
globals(p(pc(_), data(V4, V2, V3, V1)), [(V4, 'x'), (V2, 'turn'), (V3, 'flag2'), (V1, 'flag1')], [V1=0, V3=0]).
% start location
start(pc(thr1-0-7)).
% error location
error(pc(thr1-err-0)).
% cutpoint locations
cutpoint(pc(thr1-1-8)). % line 8
% invariant templates
% bound var 
% bounding vars 
bounding_vars(data(V4, V2, V3, V1), []).
% cfg loop exit relation
cfg_exit_relation([]).
% 17 transitions
r(p(pc(thr1-0-7), data(V4, V2, V3, V1)), p(pc(thr1-2-0), data(V4, V2, V3, V1p)), [], [V1p = 1], 1). % flag1 := 1
stmtsrc(1, 'flag1=1;').
transition_access( 1, [_, _, _, w] ).
r(p(pc(thr1-2-0), data(V4, V2, V3, V1)), p(pc(thr1-1-8), data(V4, V2p, V3, V1)), [], [V2p = 1], 2). % turn := 1
stmtsrc(2, 'turn=1;').
transition_access( 2, [_, w, _, _] ).
r(p(pc(thr1-1-8), data(V4, V2, V3, V1)), p(pc(thr1-5-8), data(V4, V2, V3, V1)), [], [], 3). % 
stmtsrc(3, 'skip;').
transition_access( 3, [_, _, _, _] ).
r(p(pc(thr1-5-8), data(V4, V2, V3, V1)), p(pc(thr1-6-8), data(V4, V2, V3, V1)), [(V3 = 1)], [], 4). % flag2 == 1
stmtsrc(4, 'assume(flag2 == 1);').
transition_access( 4, [_, _, r, _] ).
r(p(pc(thr1-6-8), data(V4, V2, V3, V1)), p(pc(thr1-1-8), data(V4, V2, V3, V1)), [(V2 = 1)], [], 5). % turn == 1
stmtsrc(5, 'assume(turn == 1);').
transition_access( 5, [_, r, _, _] ).
r(p(pc(thr1-6-8), data(V4, V2, V3, V1)), p(pc(thr1-8-8), data(V4, V2, V3, V1)), [(V2 +1 =< 1)], [], 6). % turn < 1
stmtsrc(6, 'assume(turn < 1);').
transition_access( 6, [_, r, _, _] ).
r(p(pc(thr1-6-8), data(V4, V2, V3, V1)), p(pc(thr1-8-8), data(V4, V2, V3, V1)), [(V2 >= 1+ 1)], [], 7). % turn > 1
stmtsrc(7, 'assume(turn > 1);').
transition_access( 7, [_, r, _, _] ).
r(p(pc(thr1-5-8), data(V4, V2, V3, V1)), p(pc(thr1-7-8), data(V4, V2, V3, V1)), [(V3 +1 =< 1)], [], 8). % flag2 < 1
stmtsrc(8, 'assume(flag2 < 1);').
transition_access( 8, [_, _, r, _] ).
r(p(pc(thr1-5-8), data(V4, V2, V3, V1)), p(pc(thr1-7-8), data(V4, V2, V3, V1)), [(V3 >= 1+ 1)], [], 9). % flag2 > 1
stmtsrc(9, 'assume(flag2 > 1);').
transition_access( 9, [_, _, r, _] ).
r(p(pc(thr1-4-0), data(V4, V2, V3, V1)), p(pc(thr1-3-13), data(V4, V2, V3, V1)), [], [], 10). % 
stmtsrc(10, 'skip;').
transition_access( 10, [_, _, _, _] ).
r(p(pc(thr1-3-13), data(V4, V2, V3, V1)), p(pc(thr1-10-0), data(V4p, V2, V3, V1)), [], [V4p = 0], 11). % x := 0
stmtsrc(11, 'x=0;').
transition_access( 11, [w, _, _, _] ).
r(p(pc(thr1-10-0), data(V4, V2, V3, V1)), p(pc(thr1-err-0), data(V4, V2, V3, V1)), [(V4 >= 1+ 0)], [], 12). % x > 0
stmtsrc(12, 'assume(x > 0);').
transition_access( 12, [r, _, _, _] ).
r(p(pc(thr1-10-0), data(V4, V2, V3, V1)), p(pc(thr1-11-0), data(V4, V2, V3, V1)), [(V4 =< 0)], [], 13). % x <= 0
stmtsrc(13, 'assume(x <= 0);').
transition_access( 13, [r, _, _, _] ).
r(p(pc(thr1-11-0), data(V4, V2, V3, V1)), p(pc(thr1-9-14), data(V4, V2, V3, V1p)), [], [V1p = 0], 14). % flag1 := 0
stmtsrc(14, 'flag1=0;').
transition_access( 14, [_, _, _, w] ).
r(p(pc(thr1-9-14), data(V4, V2, V3, V1)), p(pc(thr1-ret-0), data(V4, V2, V3, V1)), [], [], 15). % 
stmtsrc(15, 'skip;').
transition_access( 15, [_, _, _, _] ).
r(p(pc(thr1-7-8), data(V4, V2, V3, V1)), p(pc(thr1-4-0), data(V4, V2, V3, V1)), [], [], 16). % 
stmtsrc(16, 'skip;').
transition_access( 16, [_, _, _, _] ).
r(p(pc(thr1-8-8), data(V4, V2, V3, V1)), p(pc(thr1-4-0), data(V4, V2, V3, V1)), [], [], 17). % 
stmtsrc(17, 'skip;').
transition_access( 17, [_, _, _, _] ).
% Atomic blocks
% Strengthenings
