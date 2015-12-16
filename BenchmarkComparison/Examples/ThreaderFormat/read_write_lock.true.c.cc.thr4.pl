:- multifile r/5,implicit_updates/0,var2names/2,preds/2,trans_preds/3,
cube_size/1,start/1,error/1,refinement/1,cutpoint/1,invgen_template/2,
 invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,globals/3,
 bound_var/2,bounding_vars/2,transition_access/2,atomic/3.
refinement(inter).
cube_size(1).
preds(p(_, data(V3, V4, V1, V2)), []).
trans_preds(p(_, data(V3, V4, V1, V2)), p(_, data(V3p, V4p, V1p, V2p)), []).
var2names(p(pc(_), data(V3, V4, V1, V2)), [(V3, 'y'), (V4, 'x'), (V1, 'w'), (V2, 'r')]).
globals(p(pc(_), data(V3, V4, V1, V2)), [(V3, 'y'), (V4, 'x'), (V1, 'w'), (V2, 'r')], []).
% start location
start(pc(thr4-0-41)).
% error location
error(pc(thr4-err-0)).
% cutpoint locations
% invariant templates
% bound var 
% bounding vars 
bounding_vars(data(V3, V4, V1, V2), []).
% cfg loop exit relation
cfg_exit_relation([]).
% 8 transitions
r(p(pc(thr4-0-41), data(V3, V4, V1, V2)), p(pc(thr4-2-0), data(V3, V4, V1, V2)), [(V1 = 0)], [], 1). % w == 0
stmtsrc(1, 'assume(w == 0);').
transition_access( 1, [_, _, r, _] ).
r(p(pc(thr4-2-0), data(V3, V4, V1, V2)), p(pc(thr4-1-45), data(V3, V4, V1, V2p)), [], [V2p = (V2 + 1)], 2). % r := r + 1
stmtsrc(2, 'r=r + 1;').
transition_access( 2, [_, _, _, w] ).
r(p(pc(thr4-1-45), data(V3, V4, V1, V2)), p(pc(thr4-4-0), data(V3p, V4, V1, V2)), [], [V3p = V4], 3). % y := x
stmtsrc(3, 'y=x;').
transition_access( 3, [w, r, _, _] ).
r(p(pc(thr4-4-0), data(V3, V4, V1, V2)), p(pc(thr4-err-0), data(V3, V4, V1, V2)), [(V3 +1 =< V4)], [], 4). % y < x
stmtsrc(4, 'assume(y < x);').
transition_access( 4, [r, r, _, _] ).
r(p(pc(thr4-4-0), data(V3, V4, V1, V2)), p(pc(thr4-err-0), data(V3, V4, V1, V2)), [(V3 >= 1+ V4)], [], 5). % y > x
stmtsrc(5, 'assume(y > x);').
transition_access( 5, [r, r, _, _] ).
r(p(pc(thr4-4-0), data(V3, V4, V1, V2)), p(pc(thr4-5-0), data(V3, V4, V1, V2)), [(V3 = V4)], [], 6). % y == x
stmtsrc(6, 'assume(y == x);').
transition_access( 6, [r, r, _, _] ).
r(p(pc(thr4-5-0), data(V3, V4, V1, V2)), p(pc(thr4-3-46), data(V3, V4, V1, V2p)), [], [V2p = (V2 - 1)], 7). % r := r - 1
stmtsrc(7, 'r=r - 1;').
transition_access( 7, [_, _, _, w] ).
r(p(pc(thr4-3-46), data(V3, V4, V1, V2)), p(pc(thr4-ret-0), data(V3, V4, V1, V2)), [], [], 8). % 
stmtsrc(8, 'skip;').
transition_access( 8, [_, _, _, _] ).
% Atomic blocks
atomic(pc(thr4-0-41),pc(thr4-1-45),[2, 1]).
% Strengthenings
