:- multifile r/5,implicit_updates/0,var2names/2,preds/2,trans_preds/3,
cube_size/1,start/1,error/1,refinement/1,cutpoint/1,invgen_template/2,
 invgen_template/1,cfg_exit_relation/1,stmtsrc/2,strengthening/2,globals/3,
 bound_var/2,bounding_vars/2,transition_access/2,atomic/3.
refinement(inter).
cube_size(1).
preds(p(_, data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), []).
trans_preds(p(_, data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(_, data(V7p, V6p, V8p, V3p, V5p, V4p, V9p, V2p, V1p)), []).
var2names(p(pc(_), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [(V7, 'readerprogress2'), (V6, 'readerprogress1'), (V8, 'mutex'), (V3, 'idx'), (V5, 'ctr2'), (V4, 'ctr1'), (V9, 'sum'), (V2, 'readerstart2'), (V1, 'readerstart1')]).
globals(p(pc(_), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [(V7, 'readerprogress2'), (V6, 'readerprogress1'), (V8, 'mutex'), (V3, 'idx'), (V5, 'ctr2'), (V4, 'ctr1')], [(V8 = 0), (V7 = 0), (V6 = 0), (V5 = 0), (V4 = 1), (V3 = 0)]).
% start location
start(pc(qrcu_updater-0-69)).
% error location
error(pc(qrcu_updater-err-0)).
% cutpoint locations
cutpoint(pc(qrcu_updater-32-92)). % line 92
cutpoint(pc(qrcu_updater-31-91)). % line 91
% invariant templates
% bound var 
% bounding vars 
bounding_vars(data(V7, V6, V8, V3, V5, V4, V9, V2, V1), []).
% cfg loop exit relation
cfg_exit_relation([(pc(qrcu_updater-31-91), pc(qrcu_updater-32-92))]).
% 59 transitions
r(p(pc(qrcu_updater-0-69), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-2-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1p)), [], [V1p = 1], 1). % readerstart1 := 1
stmtsrc(1, 'readerstart1=1;').
transition_access( 1, [_, _, _, _, _, _, _, _, w] ).
r(p(pc(qrcu_updater-2-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-3-0), data(V7, V6, V8, V3, V5, V4, V9, V2p, V1)), [], [V2p = 1], 2). % readerstart2 := 1
stmtsrc(2, 'readerstart2=1;').
transition_access( 2, [_, _, _, _, _, _, _, w, _] ).
r(p(pc(qrcu_updater-3-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-4-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [], [], 3). % 
stmtsrc(3, 'skip;').
transition_access( 3, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-4-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-5-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [], [], 4). % 
stmtsrc(4, 'skip;').
transition_access( 4, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-5-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-6-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [], [], 5). % 
stmtsrc(5, 'skip;').
transition_access( 5, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-6-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-7-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [], [], 6). % 
stmtsrc(6, 'skip;').
transition_access( 6, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-7-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-8-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [], [], 7). % 
stmtsrc(7, 'skip;').
transition_access( 7, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-8-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-1-85), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [], [], 8). % 
stmtsrc(8, 'skip;').
transition_access( 8, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-1-85), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-10-85), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [], [], 9). % 
stmtsrc(9, 'skip;').
transition_access( 9, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-10-85), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-12-0), data(V7, V6, V8, V3, V5, V4, V9p, V2, V1)), [], [V9p = V4], 10). % sum := ctr1
stmtsrc(10, 'sum=ctr1;').
transition_access( 10, [_, _, _, _, _, r, w, _, _] ).
r(p(pc(qrcu_updater-12-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-9-86), data(V7, V6, V8, V3, V5, V4, V9p, V2, V1)), [], [V9p = (V9 + V5)], 11). % sum := sum + ctr2
stmtsrc(11, 'sum=sum + ctr2;').
transition_access( 11, [_, _, _, _, r, _, w, _, _] ).
r(p(pc(qrcu_updater-1-85), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-11-85), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [], [], 12). % 
stmtsrc(12, 'skip;').
transition_access( 12, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-11-85), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-13-0), data(V7, V6, V8, V3, V5, V4, V9p, V2, V1)), [], [V9p = V5], 13). % sum := ctr2
stmtsrc(13, 'sum=ctr2;').
transition_access( 13, [_, _, _, _, r, _, w, _, _] ).
r(p(pc(qrcu_updater-13-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-9-86), data(V7, V6, V8, V3, V5, V4, V9p, V2, V1)), [], [V9p = (V9 + V4)], 14). % sum := sum + ctr1
stmtsrc(14, 'sum=sum + ctr1;').
transition_access( 14, [_, _, _, _, _, r, w, _, _] ).
r(p(pc(qrcu_updater-9-86), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-15-86), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [(V9 =< 1)], [], 15). % sum <= 1
stmtsrc(15, 'assume(sum <= 1);').
transition_access( 15, [_, _, _, _, _, _, r, _, _] ).
r(p(pc(qrcu_updater-15-86), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-16-86), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [], [], 16). % 
stmtsrc(16, 'skip;').
transition_access( 16, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-16-86), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-18-0), data(V7, V6, V8, V3, V5, V4, V9p, V2, V1)), [], [V9p = V4], 17). % sum := ctr1
stmtsrc(17, 'sum=ctr1;').
transition_access( 17, [_, _, _, _, _, r, w, _, _] ).
r(p(pc(qrcu_updater-18-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-14-87), data(V7, V6, V8, V3, V5, V4, V9p, V2, V1)), [], [V9p = (V9 + V5)], 18). % sum := sum + ctr2
stmtsrc(18, 'sum=sum + ctr2;').
transition_access( 18, [_, _, _, _, r, _, w, _, _] ).
r(p(pc(qrcu_updater-15-86), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-17-86), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [], [], 19). % 
stmtsrc(19, 'skip;').
transition_access( 19, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-17-86), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-19-0), data(V7, V6, V8, V3, V5, V4, V9p, V2, V1)), [], [V9p = V5], 20). % sum := ctr2
stmtsrc(20, 'sum=ctr2;').
transition_access( 20, [_, _, _, _, r, _, w, _, _] ).
r(p(pc(qrcu_updater-19-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-14-87), data(V7, V6, V8, V3, V5, V4, V9p, V2, V1)), [], [V9p = (V9 + V4)], 21). % sum := sum + ctr1
stmtsrc(21, 'sum=sum + ctr1;').
transition_access( 21, [_, _, _, _, _, r, w, _, _] ).
r(p(pc(qrcu_updater-9-86), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-14-87), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [(V9 >= 1+ 1)], [], 22). % sum > 1
stmtsrc(22, 'assume(sum > 1);').
transition_access( 22, [_, _, _, _, _, _, r, _, _] ).
r(p(pc(qrcu_updater-14-87), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-21-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [(V9 >= 1+ 1)], [], 23). % sum > 1
stmtsrc(23, 'assume(sum > 1);').
transition_access( 23, [_, _, _, _, _, _, r, _, _] ).
r(p(pc(qrcu_updater-21-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-22-89), data(V7, V6, V8p, V3, V5, V4, V9, V2, V1)), [(V8 = 0)], [V8p = 1], 24). % mutex == 0, mutex := 1
stmtsrc(24, 'acquire(mutex);').
transition_access( 24, [_, _, l, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-22-89), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-24-89), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [(V3 =< 0)], [], 25). % idx <= 0
stmtsrc(25, 'assume(idx <= 0);').
transition_access( 25, [_, _, _, r, _, _, _, _, _] ).
r(p(pc(qrcu_updater-24-89), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-26-0), data(V7, V6, V8, V3, V5p, V4, V9, V2, V1)), [], [V5p = (V5 + 1)], 26). % ctr2 := ctr2 + 1
stmtsrc(26, 'ctr2=ctr2 + 1;').
transition_access( 26, [_, _, _, _, w, _, _, _, _] ).
r(p(pc(qrcu_updater-26-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-27-0), data(V7, V6, V8, V3p, V5, V4, V9, V2, V1)), [], [V3p = 1], 27). % idx := 1
stmtsrc(27, 'idx=1;').
transition_access( 27, [_, _, _, w, _, _, _, _, _] ).
r(p(pc(qrcu_updater-27-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-23-91), data(V7, V6, V8, V3, V5, V4p, V9, V2, V1)), [], [V4p = (V4 - 1)], 28). % ctr1 := ctr1 - 1
stmtsrc(28, 'ctr1=ctr1 - 1;').
transition_access( 28, [_, _, _, _, _, w, _, _, _] ).
r(p(pc(qrcu_updater-22-89), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-25-90), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [(V3 >= 1+ 0)], [], 29). % idx > 0
stmtsrc(29, 'assume(idx > 0);').
transition_access( 29, [_, _, _, r, _, _, _, _, _] ).
r(p(pc(qrcu_updater-25-90), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-28-0), data(V7, V6, V8, V3, V5, V4p, V9, V2, V1)), [], [V4p = (V4 + 1)], 30). % ctr1 := ctr1 + 1
stmtsrc(30, 'ctr1=ctr1 + 1;').
transition_access( 30, [_, _, _, _, _, w, _, _, _] ).
r(p(pc(qrcu_updater-28-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-29-0), data(V7, V6, V8, V3p, V5, V4, V9, V2, V1)), [], [V3p = 0], 31). % idx := 0
stmtsrc(31, 'idx=0;').
transition_access( 31, [_, _, _, w, _, _, _, _, _] ).
r(p(pc(qrcu_updater-29-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-23-91), data(V7, V6, V8, V3, V5p, V4, V9, V2, V1)), [], [V5p = (V5 - 1)], 32). % ctr2 := ctr2 - 1
stmtsrc(32, 'ctr2=ctr2 - 1;').
transition_access( 32, [_, _, _, _, w, _, _, _, _] ).
r(p(pc(qrcu_updater-23-91), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-31-91), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [(V3 =< 0)], [], 33). % idx <= 0
stmtsrc(33, 'assume(idx <= 0);').
transition_access( 33, [_, _, _, r, _, _, _, _, _] ).
r(p(pc(qrcu_updater-31-91), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-34-91), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [], [], 34). % 
stmtsrc(34, 'skip;').
transition_access( 34, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-34-91), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-31-91), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [(V5 >= 1+ 0)], [], 35). % ctr2 > 0
stmtsrc(35, 'assume(ctr2 > 0);').
transition_access( 35, [_, _, _, _, r, _, _, _, _] ).
r(p(pc(qrcu_updater-34-91), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-35-91), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [(V5 =< 0)], [], 36). % ctr2 <= 0
stmtsrc(36, 'assume(ctr2 <= 0);').
transition_access( 36, [_, _, _, _, r, _, _, _, _] ).
r(p(pc(qrcu_updater-33-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-30-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [], [], 37). % 
stmtsrc(37, 'skip;').
transition_access( 37, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-23-91), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-32-92), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [(V3 >= 1+ 0)], [], 38). % idx > 0
stmtsrc(38, 'assume(idx > 0);').
transition_access( 38, [_, _, _, r, _, _, _, _, _] ).
r(p(pc(qrcu_updater-32-92), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-37-92), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [], [], 39). % 
stmtsrc(39, 'skip;').
transition_access( 39, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-37-92), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-32-92), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [(V4 >= 1+ 0)], [], 40). % ctr1 > 0
stmtsrc(40, 'assume(ctr1 > 0);').
transition_access( 40, [_, _, _, _, _, r, _, _, _] ).
r(p(pc(qrcu_updater-37-92), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-38-92), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [(V4 =< 0)], [], 41). % ctr1 <= 0
stmtsrc(41, 'assume(ctr1 <= 0);').
transition_access( 41, [_, _, _, _, _, r, _, _, _] ).
r(p(pc(qrcu_updater-36-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-30-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [], [], 42). % 
stmtsrc(42, 'skip;').
transition_access( 42, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-30-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-20-98), data(V7, V6, V8p, V3, V5, V4, V9, V2, V1)), [], [V8p = 0], 43). % mutex := 0
stmtsrc(43, 'release(mutex);').
transition_access( 43, [_, _, u, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-14-87), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-20-98), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [(V9 =< 1)], [], 44). % sum <= 1
stmtsrc(44, 'assume(sum <= 1);').
transition_access( 44, [_, _, _, _, _, _, r, _, _] ).
r(p(pc(qrcu_updater-20-98), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-40-101), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [], [], 45). % 
stmtsrc(45, 'skip;').
transition_access( 45, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-40-101), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-42-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [(V1 = 1)], [], 46). % readerstart1 == 1
stmtsrc(46, 'assume(readerstart1 == 1);').
transition_access( 46, [_, _, _, _, _, _, _, _, r] ).
r(p(pc(qrcu_updater-42-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-43-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [(V6 = 1)], [], 47). % readerprogress1 == 1
stmtsrc(47, 'assume(readerprogress1 == 1);').
transition_access( 47, [_, r, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-43-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-err-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [(0 = 0)], [], 48). % 0 == 0
stmtsrc(48, 'assume(0 == 0);').
transition_access( 48, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-43-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-39-120), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [(1 = 0)], [], 49). % 1 == 0
stmtsrc(49, 'assume(1 == 0);').
transition_access( 49, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-20-98), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-41-103), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [], [], 50). % 
stmtsrc(50, 'skip;').
transition_access( 50, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-41-103), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-44-106), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [], [], 51). % 
stmtsrc(51, 'skip;').
transition_access( 51, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-44-106), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-45-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [(V2 = 1)], [], 52). % readerstart2 == 1
stmtsrc(52, 'assume(readerstart2 == 1);').
transition_access( 52, [_, _, _, _, _, _, _, r, _] ).
r(p(pc(qrcu_updater-45-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-46-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [(V7 = 1)], [], 53). % readerprogress2 == 1
stmtsrc(53, 'assume(readerprogress2 == 1);').
transition_access( 53, [r, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-46-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-err-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [(0 = 0)], [], 54). % 0 == 0
stmtsrc(54, 'assume(0 == 0);').
transition_access( 54, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-46-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-39-120), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [(1 = 0)], [], 55). % 1 == 0
stmtsrc(55, 'assume(1 == 0);').
transition_access( 55, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-41-103), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-39-120), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [], [], 56). % 
stmtsrc(56, 'skip;').
transition_access( 56, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-39-120), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-ret-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [], [], 57). % 
stmtsrc(57, 'skip;').
transition_access( 57, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-38-92), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-36-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [], [], 58). % 
stmtsrc(58, 'skip;').
transition_access( 58, [_, _, _, _, _, _, _, _, _] ).
r(p(pc(qrcu_updater-35-91), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), p(pc(qrcu_updater-33-0), data(V7, V6, V8, V3, V5, V4, V9, V2, V1)), [], [], 59). % 
stmtsrc(59, 'skip;').
transition_access( 59, [_, _, _, _, _, _, _, _, _] ).
% Atomic blocks
atomic(pc(qrcu_updater-20-98),pc(qrcu_updater-39-120),[56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45]).
% Strengthenings
