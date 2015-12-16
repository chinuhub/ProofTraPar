:- multifile r/5,implicit_updates/0,var2names/2,preds/2,trans_preds/3,
cube_size/1,start/1,error/1,refinement/1,cutpoint/1,invgen_template/2,
 invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,globals/3,
 bound_var/2,bounding_vars/2,transition_access/2,atomic/3.
refinement(inter).
cube_size(1).
preds(p(_, data(V4, V3, V1, V2)), []).
trans_preds(p(_, data(V4, V3, V1, V2)), p(_, data(V4p, V3p, V1p, V2p)), []).
var2names(p(pc(_), data(V4, V3, V1, V2)), [(V4, 'x'), (V3, 'turn'), (V1, 'flag2'), (V2, 'flag1')]).
globals(p(pc(_), data(V4, V3, V1, V2)), [(V4, 'x'), (V3, 'turn'), (V1, 'flag2'), (V2, 'flag1')], [V2=0, V1=0, V3=0]).
% start location
start(pc(thr2-0-25)).
% error location
error(pc(thr2-err-0)).
% cutpoint locations
cutpoint(pc(thr2-8-29)). % line 29
cutpoint(pc(thr2-1-26)). % line 26
% invariant templates
% bound var 
% bounding vars 
bounding_vars(data(V4, V3, V1, V2), []).
% cfg loop exit relation
cfg_exit_relation([(pc(thr2-8-29), pc(thr2-1-26))]).
% 23 transitions
r(p(pc(thr2-0-25), data(V4, V3, V1, V2)), p(pc(thr2-1-26), data(V4, V3, V1p, V2)), [], [V1p = 1], 1). % flag2 := 1
stmtsrc(1, 'flag2=1;').
transition_access( 1, [_, _, w, _] ).
r(p(pc(thr2-1-26), data(V4, V3, V1, V2)), p(pc(thr2-4-26), data(V4, V3, V1, V2)), [], [], 2). % 
stmtsrc(2, 'skip;').
transition_access( 2, [_, _, _, _] ).
r(p(pc(thr2-4-26), data(V4, V3, V1, V2)), p(pc(thr2-5-27), data(V4, V3, V1, V2)), [(V2 >= 1)], [], 3). % flag1 >= 1
stmtsrc(3, 'assume(flag1 >= 1);').
transition_access( 3, [_, _, _, r] ).
r(p(pc(thr2-4-26), data(V4, V3, V1, V2)), p(pc(thr2-6-26), data(V4, V3, V1, V2)), [(V2 +1 =< 1)], [], 4). % flag1 < 1
stmtsrc(4, 'assume(flag1 < 1);').
transition_access( 4, [_, _, _, r] ).
r(p(pc(thr2-5-27), data(V4, V3, V1, V2)), p(pc(thr2-7-28), data(V4, V3, V1, V2)), [(V3 +1 =< 1)], [], 5). % turn < 1
stmtsrc(5, 'assume(turn < 1);').
transition_access( 5, [_, r, _, _] ).
r(p(pc(thr2-5-27), data(V4, V3, V1, V2)), p(pc(thr2-7-28), data(V4, V3, V1, V2)), [(V3 >= 1+ 1)], [], 6). % turn > 1
stmtsrc(6, 'assume(turn > 1);').
transition_access( 6, [_, r, _, _] ).
r(p(pc(thr2-7-28), data(V4, V3, V1, V2)), p(pc(thr2-8-29), data(V4, V3, V1p, V2)), [], [V1p = 0], 7). % flag2 := 0
stmtsrc(7, 'flag2=0;').
transition_access( 7, [_, _, w, _] ).
r(p(pc(thr2-8-29), data(V4, V3, V1, V2)), p(pc(thr2-11-29), data(V4, V3, V1, V2)), [], [], 8). % 
stmtsrc(8, 'skip;').
transition_access( 8, [_, _, _, _] ).
r(p(pc(thr2-11-29), data(V4, V3, V1, V2)), p(pc(thr2-8-29), data(V4, V3, V1, V2)), [(V3 +1 =< 1)], [], 9). % turn < 1
stmtsrc(9, 'assume(turn < 1);').
transition_access( 9, [_, r, _, _] ).
r(p(pc(thr2-11-29), data(V4, V3, V1, V2)), p(pc(thr2-8-29), data(V4, V3, V1, V2)), [(V3 >= 1+ 1)], [], 10). % turn > 1
stmtsrc(10, 'assume(turn > 1);').
transition_access( 10, [_, r, _, _] ).
r(p(pc(thr2-11-29), data(V4, V3, V1, V2)), p(pc(thr2-12-29), data(V4, V3, V1, V2)), [(V3 = 1)], [], 11). % turn == 1
stmtsrc(11, 'assume(turn == 1);').
transition_access( 11, [_, r, _, _] ).
r(p(pc(thr2-10-0), data(V4, V3, V1, V2)), p(pc(thr2-9-30), data(V4, V3, V1, V2)), [], [], 12). % 
stmtsrc(12, 'skip;').
transition_access( 12, [_, _, _, _] ).
r(p(pc(thr2-9-30), data(V4, V3, V1, V2)), p(pc(thr2-1-26), data(V4, V3, V1p, V2)), [], [V1p = 1], 13). % flag2 := 1
stmtsrc(13, 'flag2=1;').
transition_access( 13, [_, _, w, _] ).
r(p(pc(thr2-5-27), data(V4, V3, V1, V2)), p(pc(thr2-1-26), data(V4, V3, V1, V2)), [(V3 = 1)], [], 14). % turn == 1
stmtsrc(14, 'assume(turn == 1);').
transition_access( 14, [_, r, _, _] ).
r(p(pc(thr2-3-0), data(V4, V3, V1, V2)), p(pc(thr2-2-38), data(V4, V3, V1, V2)), [], [], 15). % 
stmtsrc(15, 'skip;').
transition_access( 15, [_, _, _, _] ).
r(p(pc(thr2-2-38), data(V4, V3, V1, V2)), p(pc(thr2-14-0), data(V4p, V3, V1, V2)), [], [V4p = 1], 16). % x := 1
stmtsrc(16, 'x=1;').
transition_access( 16, [w, _, _, _] ).
r(p(pc(thr2-14-0), data(V4, V3, V1, V2)), p(pc(thr2-err-0), data(V4, V3, V1, V2)), [(V4 +1 =< 1)], [], 17). % x < 1
stmtsrc(17, 'assume(x < 1);').
transition_access( 17, [r, _, _, _] ).
r(p(pc(thr2-14-0), data(V4, V3, V1, V2)), p(pc(thr2-15-0), data(V4, V3, V1, V2)), [(V4 >= 1)], [], 18). % x >= 1
stmtsrc(18, 'assume(x >= 1);').
transition_access( 18, [r, _, _, _] ).
r(p(pc(thr2-15-0), data(V4, V3, V1, V2)), p(pc(thr2-16-0), data(V4, V3p, V1, V2)), [], [V3p = 1], 19). % turn := 1
stmtsrc(19, 'turn=1;').
transition_access( 19, [_, w, _, _] ).
r(p(pc(thr2-16-0), data(V4, V3, V1, V2)), p(pc(thr2-13-39), data(V4, V3, V1p, V2)), [], [V1p = 0], 20). % flag2 := 0
stmtsrc(20, 'flag2=0;').
transition_access( 20, [_, _, w, _] ).
r(p(pc(thr2-13-39), data(V4, V3, V1, V2)), p(pc(thr2-ret-0), data(V4, V3, V1, V2)), [], [], 21). % 
stmtsrc(21, 'skip;').
transition_access( 21, [_, _, _, _] ).
r(p(pc(thr2-12-29), data(V4, V3, V1, V2)), p(pc(thr2-10-0), data(V4, V3, V1, V2)), [], [], 22). % 
stmtsrc(22, 'skip;').
transition_access( 22, [_, _, _, _] ).
r(p(pc(thr2-6-26), data(V4, V3, V1, V2)), p(pc(thr2-3-0), data(V4, V3, V1, V2)), [], [], 23). % 
stmtsrc(23, 'skip;').
transition_access( 23, [_, _, _, _] ).
% Atomic blocks
% Strengthenings
