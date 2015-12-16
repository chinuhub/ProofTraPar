:- multifile r/5,implicit_updates/0,var2names/2,preds/2,trans_preds/3,
cube_size/1,start/1,error/1,refinement/1,cutpoint/1,invgen_template/2,
 invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,globals/3,
 bound_var/2,bounding_vars/2,transition_access/2,atomic/3.
refinement(inter).
cube_size(1).
preds(p(_, data(V4, V2, V1, V3)), []).
trans_preds(p(_, data(V4, V2, V1, V3)), p(_, data(V4p, V2p, V1p, V3p)), []).
var2names(p(pc(_), data(V4, V2, V1, V3)), [(V4, 'x'), (V2, 'turn'), (V1, 'flag2'), (V3, 'flag1')]).
globals(p(pc(_), data(V4, V2, V1, V3)), [(V4, 'x'), (V2, 'turn'), (V1, 'flag2'), (V3, 'flag1')], [V3=0, V1=0]).
% start location
start(pc(thr2-0-18)).
% error location
error(pc(thr2-err-0)).
% cutpoint locations
cutpoint(pc(thr2-1-19)). % line 19
% invariant templates
% bound var 
% bounding vars 
bounding_vars(data(V4, V2, V1, V3), []).
% cfg loop exit relation
cfg_exit_relation([]).
% 17 transitions
r(p(pc(thr2-0-18), data(V4, V2, V1, V3)), p(pc(thr2-2-0), data(V4, V2, V1p, V3)), [], [V1p = 1], 1). % flag2 := 1
stmtsrc(1, 'flag2=1;').
transition_access( 1, [_, _, w, _] ).
r(p(pc(thr2-2-0), data(V4, V2, V1, V3)), p(pc(thr2-1-19), data(V4, V2p, V1, V3)), [], [V2p = 0], 2). % turn := 0
stmtsrc(2, 'turn=0;').
transition_access( 2, [_, w, _, _] ).
r(p(pc(thr2-1-19), data(V4, V2, V1, V3)), p(pc(thr2-5-19), data(V4, V2, V1, V3)), [], [], 3). % 
stmtsrc(3, 'skip;').
transition_access( 3, [_, _, _, _] ).
r(p(pc(thr2-5-19), data(V4, V2, V1, V3)), p(pc(thr2-6-19), data(V4, V2, V1, V3)), [(V3 = 1)], [], 4). % flag1 == 1
stmtsrc(4, 'assume(flag1 == 1);').
transition_access( 4, [_, _, _, r] ).
r(p(pc(thr2-6-19), data(V4, V2, V1, V3)), p(pc(thr2-1-19), data(V4, V2, V1, V3)), [(V2 = 0)], [], 5). % turn == 0
stmtsrc(5, 'assume(turn == 0);').
transition_access( 5, [_, r, _, _] ).
r(p(pc(thr2-6-19), data(V4, V2, V1, V3)), p(pc(thr2-8-19), data(V4, V2, V1, V3)), [(V2 +1 =< 0)], [], 6). % turn < 0
stmtsrc(6, 'assume(turn < 0);').
transition_access( 6, [_, r, _, _] ).
r(p(pc(thr2-6-19), data(V4, V2, V1, V3)), p(pc(thr2-8-19), data(V4, V2, V1, V3)), [(V2 >= 1+ 0)], [], 7). % turn > 0
stmtsrc(7, 'assume(turn > 0);').
transition_access( 7, [_, r, _, _] ).
r(p(pc(thr2-5-19), data(V4, V2, V1, V3)), p(pc(thr2-7-19), data(V4, V2, V1, V3)), [(V3 +1 =< 1)], [], 8). % flag1 < 1
stmtsrc(8, 'assume(flag1 < 1);').
transition_access( 8, [_, _, _, r] ).
r(p(pc(thr2-5-19), data(V4, V2, V1, V3)), p(pc(thr2-7-19), data(V4, V2, V1, V3)), [(V3 >= 1+ 1)], [], 9). % flag1 > 1
stmtsrc(9, 'assume(flag1 > 1);').
transition_access( 9, [_, _, _, r] ).
r(p(pc(thr2-4-0), data(V4, V2, V1, V3)), p(pc(thr2-3-24), data(V4, V2, V1, V3)), [], [], 10). % 
stmtsrc(10, 'skip;').
transition_access( 10, [_, _, _, _] ).
r(p(pc(thr2-3-24), data(V4, V2, V1, V3)), p(pc(thr2-10-0), data(V4p, V2, V1, V3)), [], [V4p = 1], 11). % x := 1
stmtsrc(11, 'x=1;').
transition_access( 11, [w, _, _, _] ).
r(p(pc(thr2-10-0), data(V4, V2, V1, V3)), p(pc(thr2-err-0), data(V4, V2, V1, V3)), [(V4 +1 =< 1)], [], 12). % x < 1
stmtsrc(12, 'assume(x < 1);').
transition_access( 12, [r, _, _, _] ).
r(p(pc(thr2-10-0), data(V4, V2, V1, V3)), p(pc(thr2-11-0), data(V4, V2, V1, V3)), [(V4 >= 1)], [], 13). % x >= 1
stmtsrc(13, 'assume(x >= 1);').
transition_access( 13, [r, _, _, _] ).
r(p(pc(thr2-11-0), data(V4, V2, V1, V3)), p(pc(thr2-9-25), data(V4, V2, V1p, V3)), [], [V1p = 0], 14). % flag2 := 0
stmtsrc(14, 'flag2=0;').
transition_access( 14, [_, _, w, _] ).
r(p(pc(thr2-9-25), data(V4, V2, V1, V3)), p(pc(thr2-ret-0), data(V4, V2, V1, V3)), [], [], 15). % 
stmtsrc(15, 'skip;').
transition_access( 15, [_, _, _, _] ).
r(p(pc(thr2-7-19), data(V4, V2, V1, V3)), p(pc(thr2-4-0), data(V4, V2, V1, V3)), [], [], 16). % 
stmtsrc(16, 'skip;').
transition_access( 16, [_, _, _, _] ).
r(p(pc(thr2-8-19), data(V4, V2, V1, V3)), p(pc(thr2-4-0), data(V4, V2, V1, V3)), [], [], 17). % 
stmtsrc(17, 'skip;').
transition_access( 17, [_, _, _, _] ).
% Atomic blocks
% Strengthenings
