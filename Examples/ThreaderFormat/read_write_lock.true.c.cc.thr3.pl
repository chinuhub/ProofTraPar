:- multifile r/5,implicit_updates/0,var2names/2,preds/2,trans_preds/3,
cube_size/1,start/1,error/1,refinement/1,cutpoint/1,invgen_template/2,
 invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,globals/3,
 bound_var/2,bounding_vars/2,transition_access/2,atomic/3.
refinement(inter).
cube_size(1).
preds(p(_, data(V3, V1, V2)), []).
trans_preds(p(_, data(V3, V1, V2)), p(_, data(V3p, V1p, V2p)), []).
var2names(p(pc(_), data(V3, V1, V2)), [(V3, 'x'), (V1, 'w'), (V2, 'r')]).
globals(p(pc(_), data(V3, V1, V2)), [(V3, 'x'), (V1, 'w'), (V2, 'r')], [(V2 = 0), (V1 = 0)]).
% start location
start(pc(thr3-0-0)).
% error location
error(pc(thr3-err-0)).
% cutpoint locations
% invariant templates
% bound var 
% bounding vars 
bounding_vars(data(V3, V1, V2), []).
% cfg loop exit relation
cfg_exit_relation([]).
% 8 transitions
r(p(pc(thr3-0-0), data(V3, V1, V2)), p(pc(thr3-2-0), data(V3, V1, V2)), [], [], 1). % 
stmtsrc(1, 'skip;').
transition_access( 1, [_, _, _] ).
r(p(pc(thr3-2-0), data(V3, V1, V2)), p(pc(thr3-1-32), data(V3, V1, V2)), [], [], 2). % 
stmtsrc(2, 'skip;').
transition_access( 2, [_, _, _] ).
r(p(pc(thr3-1-32), data(V3, V1, V2)), p(pc(thr3-4-0), data(V3, V1, V2)), [(V1 = 0)], [], 3). % w == 0
stmtsrc(3, 'assume(w == 0);').
transition_access( 3, [_, r, _] ).
r(p(pc(thr3-4-0), data(V3, V1, V2)), p(pc(thr3-5-0), data(V3, V1, V2)), [(V2 = 0)], [], 4). % r == 0
stmtsrc(4, 'assume(r == 0);').
transition_access( 4, [_, _, r] ).
r(p(pc(thr3-5-0), data(V3, V1, V2)), p(pc(thr3-3-35), data(V3, V1p, V2)), [], [V1p = 1], 5). % w := 1
stmtsrc(5, 'w=1;').
transition_access( 5, [_, w, _] ).
r(p(pc(thr3-3-35), data(V3, V1, V2)), p(pc(thr3-7-0), data(V3p, V1, V2)), [], [V3p = 3], 6). % x := 3
stmtsrc(6, 'x=3;').
transition_access( 6, [w, _, _] ).
r(p(pc(thr3-7-0), data(V3, V1, V2)), p(pc(thr3-6-36), data(V3, V1p, V2)), [], [V1p = 0], 7). % w := 0
stmtsrc(7, 'w=0;').
transition_access( 7, [_, w, _] ).
r(p(pc(thr3-6-36), data(V3, V1, V2)), p(pc(thr3-ret-0), data(V3, V1, V2)), [], [], 8). % 
stmtsrc(8, 'skip;').
transition_access( 8, [_, _, _] ).
% Atomic blocks
atomic(pc(thr3-1-32),pc(thr3-3-35),[5, 4, 3]).
% Strengthenings
