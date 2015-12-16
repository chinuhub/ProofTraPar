:- multifile r/5,implicit_updates/0,var2names/2,preds/2,trans_preds/3,
cube_size/1,start/1,error/1,refinement/1,cutpoint/1,invgen_template/2,
 invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,globals/3,
 bound_var/2,bounding_vars/2,transition_access/2,atomic/3.
refinement(inter).
cube_size(1).
preds(p(_, data(V3, V4, V1, V2, V5)), []).
trans_preds(p(_, data(V3, V4, V1, V2, V5)), p(_, data(V3p, V4p, V1p, V2p, V5p)), []).
var2names(p(pc(_), data(V3, V4, V1, V2, V5)), [(V3, 'm_inode'), (V4, 'm_busy'), (V1, 'inode'), (V2, 'busy'), (V5, 'block')]).
globals(p(pc(_), data(V3, V4, V1, V2, V5)), [(V3, 'm_inode'), (V4, 'm_busy'), (V1, 'inode'), (V2, 'busy'), (V5, 'block')], [V4=0, V3=0, (V1 = V2)]).
% start location
start(pc(thr1-0-0)).
% error location
error(pc(thr1-err-0)).
% cutpoint locations
% invariant templates
% bound var 
% bounding vars 
bounding_vars(data(V3, V4, V1, V2, V5), []).
% cfg loop exit relation
cfg_exit_relation([]).
% 15 transitions
r(p(pc(thr1-0-0), data(V3, V4, V1, V2, V5)), p(pc(thr1-2-0), data(V3, V4, V1, V2, V5)), [], [], 1). % 
stmtsrc(1, 'skip;').
transition_access( 1, [_, _, _, _, _] ).
r(p(pc(thr1-2-0), data(V3, V4, V1, V2, V5)), p(pc(thr1-1-10), data(V3p, V4, V1, V2, V5)), [(V3 = 0)], [V3p = 1], 2). % m_inode == 0, m_inode := 1
stmtsrc(2, 'acquire(m_inode);').
transition_access( 2, [l, _, _, _, _] ).
r(p(pc(thr1-1-10), data(V3, V4, V1, V2, V5)), p(pc(thr1-4-14), data(V3, V4, V1, V2, V5)), [(V1 = 0)], [], 3). % inode == 0
stmtsrc(3, 'assume(inode == 0);').
transition_access( 3, [_, _, r, _, _] ).
r(p(pc(thr1-4-14), data(V3, V4, V1, V2, V5)), p(pc(thr1-5-0), data(V3, V4p, V1, V2, V5)), [(V4 = 0)], [V4p = 1], 4). % m_busy == 0, m_busy := 1
stmtsrc(4, 'acquire(m_busy);').
transition_access( 4, [_, l, _, _, _] ).
r(p(pc(thr1-5-0), data(V3, V4, V1, V2, V5)), p(pc(thr1-6-0), data(V3, V4, V1, V2p, V5)), [], [V2p = 1], 5). % busy := 1
stmtsrc(5, 'busy=1;').
transition_access( 5, [_, _, _, w, _] ).
r(p(pc(thr1-6-0), data(V3, V4, V1, V2, V5)), p(pc(thr1-7-0), data(V3, V4p, V1, V2, V5)), [], [V4p = 0], 6). % m_busy := 0
stmtsrc(6, 'release(m_busy);').
transition_access( 6, [_, u, _, _, _] ).
r(p(pc(thr1-7-0), data(V3, V4, V1, V2, V5)), p(pc(thr1-3-17), data(V3, V4, V1p, V2, V5)), [], [V1p = 1], 7). % inode := 1
stmtsrc(7, 'inode=1;').
transition_access( 7, [_, _, w, _, _] ).
r(p(pc(thr1-1-10), data(V3, V4, V1, V2, V5)), p(pc(thr1-3-17), data(V3, V4, V1, V2, V5)), [(V1 +1 =< 0)], [], 8). % inode < 0
stmtsrc(8, 'assume(inode < 0);').
transition_access( 8, [_, _, r, _, _] ).
r(p(pc(thr1-1-10), data(V3, V4, V1, V2, V5)), p(pc(thr1-3-17), data(V3, V4, V1, V2, V5)), [(V1 >= 1+ 0)], [], 9). % inode > 0
stmtsrc(9, 'assume(inode > 0);').
transition_access( 9, [_, _, r, _, _] ).
r(p(pc(thr1-3-17), data(V3, V4, V1, V2, V5)), p(pc(thr1-9-0), data(V3, V4, V1, V2, V5p)), [], [V5p = 1], 10). % block := 1
stmtsrc(10, 'block=1;').
transition_access( 10, [_, _, _, _, w] ).
r(p(pc(thr1-9-0), data(V3, V4, V1, V2, V5)), p(pc(thr1-err-0), data(V3, V4, V1, V2, V5)), [(V5 +1 =< 1)], [], 11). % block < 1
stmtsrc(11, 'assume(block < 1);').
transition_access( 11, [_, _, _, _, r] ).
r(p(pc(thr1-9-0), data(V3, V4, V1, V2, V5)), p(pc(thr1-err-0), data(V3, V4, V1, V2, V5)), [(V5 >= 1+ 1)], [], 12). % block > 1
stmtsrc(12, 'assume(block > 1);').
transition_access( 12, [_, _, _, _, r] ).
r(p(pc(thr1-9-0), data(V3, V4, V1, V2, V5)), p(pc(thr1-10-0), data(V3, V4, V1, V2, V5)), [(V5 = 1)], [], 13). % block == 1
stmtsrc(13, 'assume(block == 1);').
transition_access( 13, [_, _, _, _, r] ).
r(p(pc(thr1-10-0), data(V3, V4, V1, V2, V5)), p(pc(thr1-8-19), data(V3p, V4, V1, V2, V5)), [], [V3p = 0], 14). % m_inode := 0
stmtsrc(14, 'release(m_inode);').
transition_access( 14, [u, _, _, _, _] ).
r(p(pc(thr1-8-19), data(V3, V4, V1, V2, V5)), p(pc(thr1-ret-0), data(V3, V4, V1, V2, V5)), [], [], 15). % 
stmtsrc(15, 'skip;').
transition_access( 15, [_, _, _, _, _] ).
% Atomic blocks
% Strengthenings
