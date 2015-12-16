:- multifile r/5,implicit_updates/0,var2names/2,preds/2,trans_preds/3,
cube_size/1,start/1,error/1,refinement/1,cutpoint/1,invgen_template/2,
 invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,globals/3,
 bound_var/2,bounding_vars/2,transition_access/2,atomic/3.
refinement(inter).
cube_size(1).
preds(p(_, data(V5, V2, V4, V3, V1)), []).
trans_preds(p(_, data(V5, V2, V4, V3, V1)), p(_, data(V5p, V2p, V4p, V3p, V1p)), []).
var2names(p(pc(_), data(V5, V2, V4, V3, V1)), [(V5, 'readerprogress1'), (V2, 'idx'), (V4, 'ctr2'), (V3, 'ctr1'), (V1, 'myidx')]).
globals(p(pc(_), data(V5, V2, V4, V3, V1)), [(V5, 'readerprogress1'), (V2, 'idx'), (V4, 'ctr2'), (V3, 'ctr1')], []).
% start location
start(pc(qrcu_reader1-0-14)).
% error location
error(pc(qrcu_reader1-err-0)).
% cutpoint locations
cutpoint(pc(qrcu_reader1-0-14)). % line 14
% invariant templates
% bound var 
% bounding vars 
bounding_vars(data(V5, V2, V4, V3, V1), []).
% cfg loop exit relation
cfg_exit_relation([]).
% 22 transitions
r(p(pc(qrcu_reader1-0-14), data(V5, V2, V4, V3, V1)), p(pc(qrcu_reader1-3-15), data(V5, V2, V4, V3, V1)), [], [], 1). % 
stmtsrc(1, 'skip;').
transition_access( 1, [_, _, _, _, _] ).
r(p(pc(qrcu_reader1-3-15), data(V5, V2, V4, V3, V1)), p(pc(qrcu_reader1-4-16), data(V5, V2, V4, V3, V1p)), [], [V1p = V2], 2). % myidx := idx
stmtsrc(2, 'myidx=idx;').
transition_access( 2, [_, r, _, _, w] ).
r(p(pc(qrcu_reader1-4-16), data(V5, V2, V4, V3, V1)), p(pc(qrcu_reader1-5-20), data(V5, V2, V4, V3, V1)), [], [], 3). % 
stmtsrc(3, 'skip;').
transition_access( 3, [_, _, _, _, _] ).
r(p(pc(qrcu_reader1-5-20), data(V5, V2, V4, V3, V1)), p(pc(qrcu_reader1-8-0), data(V5, V2, V4, V3, V1)), [(V1 =< 0)], [], 4). % myidx <= 0
stmtsrc(4, 'assume(myidx <= 0);').
transition_access( 4, [_, _, _, _, r] ).
r(p(pc(qrcu_reader1-8-0), data(V5, V2, V4, V3, V1)), p(pc(qrcu_reader1-9-0), data(V5, V2, V4, V3, V1)), [(V3 >= 1+ 0)], [], 5). % ctr1 > 0
stmtsrc(5, 'assume(ctr1 > 0);').
transition_access( 5, [_, _, _, r, _] ).
r(p(pc(qrcu_reader1-9-0), data(V5, V2, V4, V3, V1)), p(pc(qrcu_reader1-7-22), data(V5, V2, V4, V3p, V1)), [], [V3p = (V3 + 1)], 6). % ctr1 := ctr1 + 1
stmtsrc(6, 'ctr1=ctr1 + 1;').
transition_access( 6, [_, _, _, w, _] ).
r(p(pc(qrcu_reader1-4-16), data(V5, V2, V4, V3, V1)), p(pc(qrcu_reader1-6-24), data(V5, V2, V4, V3, V1)), [], [], 7). % 
stmtsrc(7, 'skip;').
transition_access( 7, [_, _, _, _, _] ).
r(p(pc(qrcu_reader1-6-24), data(V5, V2, V4, V3, V1)), p(pc(qrcu_reader1-10-28), data(V5, V2, V4, V3, V1)), [], [], 8). % 
stmtsrc(8, 'skip;').
transition_access( 8, [_, _, _, _, _] ).
r(p(pc(qrcu_reader1-10-28), data(V5, V2, V4, V3, V1)), p(pc(qrcu_reader1-12-0), data(V5, V2, V4, V3, V1)), [(V1 >= 1+ 0)], [], 9). % myidx > 0
stmtsrc(9, 'assume(myidx > 0);').
transition_access( 9, [_, _, _, _, r] ).
r(p(pc(qrcu_reader1-12-0), data(V5, V2, V4, V3, V1)), p(pc(qrcu_reader1-13-0), data(V5, V2, V4, V3, V1)), [(V4 >= 1+ 0)], [], 10). % ctr2 > 0
stmtsrc(10, 'assume(ctr2 > 0);').
transition_access( 10, [_, _, r, _, _] ).
r(p(pc(qrcu_reader1-13-0), data(V5, V2, V4, V3, V1)), p(pc(qrcu_reader1-11-30), data(V5, V2, V4p, V3, V1)), [], [V4p = (V4 + 1)], 11). % ctr2 := ctr2 + 1
stmtsrc(11, 'ctr2=ctr2 + 1;').
transition_access( 11, [_, _, w, _, _] ).
r(p(pc(qrcu_reader1-6-24), data(V5, V2, V4, V3, V1)), p(pc(qrcu_reader1-0-14), data(V5, V2, V4, V3, V1)), [], [], 12). % 
stmtsrc(12, 'skip;').
transition_access( 12, [_, _, _, _, _] ).
r(p(pc(qrcu_reader1-2-0), data(V5, V2, V4, V3, V1)), p(pc(qrcu_reader1-1-47), data(V5, V2, V4, V3, V1)), [], [], 13). % 
stmtsrc(13, 'skip;').
transition_access( 13, [_, _, _, _, _] ).
r(p(pc(qrcu_reader1-1-47), data(V5, V2, V4, V3, V1)), p(pc(qrcu_reader1-15-0), data(V5p, V2, V4, V3, V1)), [], [V5p = 1], 14). % readerprogress1 := 1
stmtsrc(14, 'readerprogress1=1;').
transition_access( 14, [w, _, _, _, _] ).
r(p(pc(qrcu_reader1-15-0), data(V5, V2, V4, V3, V1)), p(pc(qrcu_reader1-14-51), data(V5p, V2, V4, V3, V1)), [], [V5p = 2], 15). % readerprogress1 := 2
stmtsrc(15, 'readerprogress1=2;').
transition_access( 15, [w, _, _, _, _] ).
r(p(pc(qrcu_reader1-14-51), data(V5, V2, V4, V3, V1)), p(pc(qrcu_reader1-17-51), data(V5, V2, V4, V3, V1)), [(V1 =< 0)], [], 16). % myidx <= 0
stmtsrc(16, 'assume(myidx <= 0);').
transition_access( 16, [_, _, _, _, r] ).
r(p(pc(qrcu_reader1-17-51), data(V5, V2, V4, V3, V1)), p(pc(qrcu_reader1-16-54), data(V5, V2, V4, V3p, V1)), [], [V3p = (V3 - 1)], 17). % ctr1 := ctr1 - 1
stmtsrc(17, 'ctr1=ctr1 - 1;').
transition_access( 17, [_, _, _, w, _] ).
r(p(pc(qrcu_reader1-14-51), data(V5, V2, V4, V3, V1)), p(pc(qrcu_reader1-18-52), data(V5, V2, V4, V3, V1)), [(V1 >= 1+ 0)], [], 18). % myidx > 0
stmtsrc(18, 'assume(myidx > 0);').
transition_access( 18, [_, _, _, _, r] ).
r(p(pc(qrcu_reader1-18-52), data(V5, V2, V4, V3, V1)), p(pc(qrcu_reader1-16-54), data(V5, V2, V4p, V3, V1)), [], [V4p = (V4 - 1)], 19). % ctr2 := ctr2 - 1
stmtsrc(19, 'ctr2=ctr2 - 1;').
transition_access( 19, [_, _, w, _, _] ).
r(p(pc(qrcu_reader1-16-54), data(V5, V2, V4, V3, V1)), p(pc(qrcu_reader1-ret-0), data(V5, V2, V4, V3, V1)), [], [], 20). % 
stmtsrc(20, 'skip;').
transition_access( 20, [_, _, _, _, _] ).
r(p(pc(qrcu_reader1-11-30), data(V5, V2, V4, V3, V1)), p(pc(qrcu_reader1-2-0), data(V5, V2, V4, V3, V1)), [], [], 21). % 
stmtsrc(21, 'skip;').
transition_access( 21, [_, _, _, _, _] ).
r(p(pc(qrcu_reader1-7-22), data(V5, V2, V4, V3, V1)), p(pc(qrcu_reader1-2-0), data(V5, V2, V4, V3, V1)), [], [], 22). % 
stmtsrc(22, 'skip;').
transition_access( 22, [_, _, _, _, _] ).
% Atomic blocks
atomic(pc(qrcu_reader1-14-51),pc(qrcu_reader1-16-54),[19, 18, 17, 16]).
atomic(pc(qrcu_reader1-10-28),pc(qrcu_reader1-11-30),[11, 10, 9]).
atomic(pc(qrcu_reader1-5-20),pc(qrcu_reader1-7-22),[6, 5, 4]).
% Strengthenings
