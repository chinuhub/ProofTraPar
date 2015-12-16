:- multifile r/5,implicit_updates/0,var2names/2,preds/2,trans_preds/3,
cube_size/1,start/1,error/1,refinement/1,cutpoint/1,invgen_template/2,
 invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,globals/3,
 bound_var/2,bounding_vars/2,transition_access/2,atomic/3.
refinement(inter).
cube_size(1).
preds(p(_, data(V1, V2, V3)), []).
trans_preds(p(_, data(V1, V2, V3)), p(_, data(V1p, V2p, V3p)), []).
var2names(p(pc(_), data(V1, V2, V3)), [(V1, 'm_busy'), (V2, 'busy'), (V3, 'block')]).
globals(p(pc(_), data(V1, V2, V3)), [(V1, 'm_busy'), (V2, 'busy'), (V3, 'block')], [V1=0]).
% start location
start(pc(thr2-0-0)).
% error location
error(pc(thr2-err-0)).
% cutpoint locations
% invariant templates
% bound var 
% bounding vars 
bounding_vars(data(V1, V2, V3), []).
% cfg loop exit relation
cfg_exit_relation([]).
% 10 transitions
r(p(pc(thr2-0-0), data(V1, V2, V3)), p(pc(thr2-1-23), data(V1p, V2, V3)), [(V1 = 0)], [V1p = 1], 1). % m_busy == 0, m_busy := 1
stmtsrc(1, 'acquire(m_busy);').
transition_access( 1, [l, _, _] ).
r(p(pc(thr2-1-23), data(V1, V2, V3)), p(pc(thr2-3-25), data(V1, V2, V3)), [(V2 = 0)], [], 2). % busy == 0
stmtsrc(2, 'assume(busy == 0);').
transition_access( 2, [_, r, _] ).
r(p(pc(thr2-3-25), data(V1, V2, V3)), p(pc(thr2-4-0), data(V1, V2, V3p)), [], [V3p = 0], 3). % block := 0
stmtsrc(3, 'block=0;').
transition_access( 3, [_, _, w] ).
r(p(pc(thr2-4-0), data(V1, V2, V3)), p(pc(thr2-err-0), data(V1, V2, V3)), [(V3 +1 =< 0)], [], 4). % block < 0
stmtsrc(4, 'assume(block < 0);').
transition_access( 4, [_, _, r] ).
r(p(pc(thr2-4-0), data(V1, V2, V3)), p(pc(thr2-err-0), data(V1, V2, V3)), [(V3 >= 1+ 0)], [], 5). % block > 0
stmtsrc(5, 'assume(block > 0);').
transition_access( 5, [_, _, r] ).
r(p(pc(thr2-4-0), data(V1, V2, V3)), p(pc(thr2-2-0), data(V1, V2, V3)), [(V3 = 0)], [], 6). % block == 0
stmtsrc(6, 'assume(block == 0);').
transition_access( 6, [_, _, r] ).
r(p(pc(thr2-1-23), data(V1, V2, V3)), p(pc(thr2-2-0), data(V1, V2, V3)), [(V2 +1 =< 0)], [], 7). % busy < 0
stmtsrc(7, 'assume(busy < 0);').
transition_access( 7, [_, r, _] ).
r(p(pc(thr2-1-23), data(V1, V2, V3)), p(pc(thr2-2-0), data(V1, V2, V3)), [(V2 >= 1+ 0)], [], 8). % busy > 0
stmtsrc(8, 'assume(busy > 0);').
transition_access( 8, [_, r, _] ).
r(p(pc(thr2-2-0), data(V1, V2, V3)), p(pc(thr2-5-28), data(V1p, V2, V3)), [], [V1p = 0], 9). % m_busy := 0
stmtsrc(9, 'release(m_busy);').
transition_access( 9, [u, _, _] ).
r(p(pc(thr2-5-28), data(V1, V2, V3)), p(pc(thr2-ret-0), data(V1, V2, V3)), [], [], 10). % 
stmtsrc(10, 'skip;').
transition_access( 10, [_, _, _] ).
% Atomic blocks
% Strengthenings
