false :-
        [s_4218(A,B,C,D,E,F),s_2765(A,B,C,D,E,F),s_2803(A,B,C,D,E,F),s_1104(A,B,C,D,E,F)].
s_4218(A, B, C, D, E, F) :-
        [s_2659(A,B,C,D,E,F),A+1=<D].
s_2659(A, B, C, D, E, F) :-
        [s_1312(G,H,I,J,K,L),t_4_23(G,H,I,J,K,L,A,B,C,D,E,F),{K=E}].
t_4_23(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_13(A,B,C,D,E,F),J=3,L=F,K=E,I=C,H=B,G=A].
s_13(A, B, C, D, E, F) :-
        [s_3(A,B,I,D,E,F),C=rat(1,1),B=rat(0,1),I=rat(0,1)].
s_3(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_1312(A, B, C, D, E, F) :-
        [s_1044(G,H,I,J,K,L),t_4_123(G,H,I,J,K,L,A,B,C,D,E,F),{K=E}].
t_4_123(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_795(A,B,C,D,E,F),G=J,L=F,K=E,J=D,I=C,H=B].
s_795(A, B, C, D, E, F) :-
        [s_493(G,H,I,J,K,L),t_2_1(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_1(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_1(A,B,C,D,E,F),I=rat(1,1),H=rat(0,1),C=rat(0,1),L=F,K=E,J=D,H=B,G=A].
s_1(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_493(A, B, C, D, E, F) :-
        [s_308(G,H,I,J,K,L),t_2_79(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_79(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_301(A,B,C,D,E,F),H=L,L=F,K=E,J=D,I=C,G=A].
s_301(A, B, C, D, E, F) :-
        [s_163(G,H,I,J,K,L),t_4_29(G,H,I,J,K,L,A,B,C,D,E,F),{K=E}].
t_4_29(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_22(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_22(A, B, C, D, E, F) :-
        [s_2(G,H,I,J,K,L),t_2_11(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_11(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_4(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_163(A, B, C, D, E, F) :-
        [s_77(A,B,C,D,E,_),F=B-1].
s_77(A, B, C, D, E, F) :-
        [s_43(A,B,C,D,E,F),A=D].
s_43(A, B, C, D, E, F) :-
        [s_19(_,B,C,D,E,F),A=D].
s_19(A, B, C, D, E, F) :-
        [s_4(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_308(A, B, C, D, E, F) :-
        [s_168(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_168(A, B, C, D, E, F) :-
        [s_80(G,H,I,J,K,L),t_2_53(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_53(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_77(A,B,C,D,E,F),L=H-1,K=E,J=D,I=C,H=B,G=A].
s_77(A, B, C, D, E, F) :-
        [s_43(A,B,C,D,E,F),A=D].
s_43(A, B, C, D, E, F) :-
        [s_19(_,B,C,D,E,F),A=D].
s_19(A, B, C, D, E, F) :-
        [s_4(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_80(A, B, C, D, E, F) :-
        [s_46(G,H,I,J,K,L),t_2_42(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_42(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_43(A,B,C,D,E,F),G=J,L=F,K=E,J=D,I=C,H=B,G=A].
s_43(A, B, C, D, E, F) :-
        [s_19(_,B,C,D,E,F),A=D].
s_19(A, B, C, D, E, F) :-
        [s_4(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_46(A, B, C, D, E, F) :-
        [s_22(G,H,I,J,K,L),t_2_25(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_25(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_19(A,B,C,D,E,F),G=J,L=F,K=E,J=D,I=C,H=B].
s_19(A, B, C, D, E, F) :-
        [s_4(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_22(A, B, C, D, E, F) :-
        [s_2(G,H,I,J,K,L),t_2_11(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_11(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_4(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_1044(A, B, C, D, E, F) :-
        [s_569(_,B,C,D,E,F),A=D].
s_569(A, B, C, D, E, F) :-
        [s_350(G,H,I,J,K,L),t_4_9(G,H,I,J,K,L,A,B,C,D,E,F),{K=E}].
t_4_9(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_3(A,B,C,D,E,F),I=rat(1,1),H=rat(0,1),C=rat(0,1),L=F,K=E,J=D,H=B,G=A].
s_3(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_350(A, B, C, D, E, F) :-
        [s_231(G,H,I,J,K,L),t_4_70(G,H,I,J,K,L,A,B,C,D,E,F),{K=E}].
t_4_70(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_208(A,B,C,D,E,F),H=K,L=F,K=E,J=D,I=C,G=A].
s_208(A, B, C, D, E, F) :-
        [s_109(G,H,I,J,K,L),t_2_20(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_20(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_10(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_10(A, B, C, D, E, F) :-
        [s_4(G,H,I,J,K,L),t_4_6(G,H,I,J,K,L,A,B,C,D,E,F),{K=E}].
t_4_6(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_2(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_109(A, B, C, D, E, F) :-
        [s_63(A,B,C,D,_,F),E=B-1].
s_63(A, B, C, D, E, F) :-
        [s_29(A,B,C,D,E,F),A=D].
s_29(A, B, C, D, E, F) :-
        [s_9(_,B,C,D,E,F),A=D].
s_9(A, B, C, D, E, F) :-
        [s_2(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_231(A, B, C, D, E, F) :-
        [s_110(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_110(A, B, C, D, E, F) :-
        [s_10(G,H,I,J,K,L),t_4_48(G,H,I,J,K,L,A,B,C,D,E,F),{K=E}].
t_4_48(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_63(A,B,C,D,E,F),K=H-1,L=F,J=D,I=C,H=B,G=A].
s_63(A, B, C, D, E, F) :-
        [s_29(A,B,C,D,E,F),A=D].
s_29(A, B, C, D, E, F) :-
        [s_9(_,B,C,D,E,F),A=D].
s_9(A, B, C, D, E, F) :-
        [s_2(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_10(A, B, C, D, E, F) :-
        [s_4(G,H,I,J,K,L),t_4_6(G,H,I,J,K,L,A,B,C,D,E,F),{K=E}].
t_4_6(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_2(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_2765(A, B, C, D, E, F) :-
        [s_1943(G,H,I,J,K,L),t_1_166(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_1_166(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_1359(A,B,C,D,E,F),J=3,L=F,K=E,I=C,H=B,G=A].
s_1359(A, B, C, D, E, F) :-
        [s_831(G,H,I,J,K,L),t_3_122(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_3_122(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_795(A,B,C,D,E,F),G=J,L=F,K=E,J=D,I=C,H=B].
s_795(A, B, C, D, E, F) :-
        [s_493(G,H,I,J,K,L),t_2_1(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_1(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_1(A,B,C,D,E,F),I=rat(1,1),H=rat(0,1),C=rat(0,1),L=F,K=E,J=D,H=B,G=A].
s_1(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_493(A, B, C, D, E, F) :-
        [s_308(G,H,I,J,K,L),t_2_79(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_79(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_301(A,B,C,D,E,F),H=L,L=F,K=E,J=D,I=C,G=A].
s_301(A, B, C, D, E, F) :-
        [s_163(G,H,I,J,K,L),t_4_29(G,H,I,J,K,L,A,B,C,D,E,F),{K=E}].
t_4_29(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_22(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_22(A, B, C, D, E, F) :-
        [s_2(G,H,I,J,K,L),t_2_11(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_11(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_4(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_163(A, B, C, D, E, F) :-
        [s_77(A,B,C,D,E,_),F=B-1].
s_77(A, B, C, D, E, F) :-
        [s_43(A,B,C,D,E,F),A=D].
s_43(A, B, C, D, E, F) :-
        [s_19(_,B,C,D,E,F),A=D].
s_19(A, B, C, D, E, F) :-
        [s_4(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_308(A, B, C, D, E, F) :-
        [s_168(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_168(A, B, C, D, E, F) :-
        [s_80(G,H,I,J,K,L),t_2_53(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_53(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_77(A,B,C,D,E,F),L=H-1,K=E,J=D,I=C,H=B,G=A].
s_77(A, B, C, D, E, F) :-
        [s_43(A,B,C,D,E,F),A=D].
s_43(A, B, C, D, E, F) :-
        [s_19(_,B,C,D,E,F),A=D].
s_19(A, B, C, D, E, F) :-
        [s_4(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_80(A, B, C, D, E, F) :-
        [s_46(G,H,I,J,K,L),t_2_42(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_42(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_43(A,B,C,D,E,F),G=J,L=F,K=E,J=D,I=C,H=B,G=A].
s_43(A, B, C, D, E, F) :-
        [s_19(_,B,C,D,E,F),A=D].
s_19(A, B, C, D, E, F) :-
        [s_4(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_46(A, B, C, D, E, F) :-
        [s_22(G,H,I,J,K,L),t_2_25(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_25(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_19(A,B,C,D,E,F),G=J,L=F,K=E,J=D,I=C,H=B].
s_19(A, B, C, D, E, F) :-
        [s_4(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_22(A, B, C, D, E, F) :-
        [s_2(G,H,I,J,K,L),t_2_11(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_11(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_4(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_831(A, B, C, D, E, F) :-
        [s_553(G,H,I,J,K,L),t_3_95(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_3_95(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_493(A,B,C,D,E,F),G=J,L=F,K=E,J=D,I=C,H=B].
s_493(A, B, C, D, E, F) :-
        [s_308(G,H,I,J,K,L),t_2_79(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_79(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_301(A,B,C,D,E,F),H=L,L=F,K=E,J=D,I=C,G=A].
s_301(A, B, C, D, E, F) :-
        [s_163(G,H,I,J,K,L),t_4_29(G,H,I,J,K,L,A,B,C,D,E,F),{K=E}].
t_4_29(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_22(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_22(A, B, C, D, E, F) :-
        [s_2(G,H,I,J,K,L),t_2_11(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_11(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_4(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_163(A, B, C, D, E, F) :-
        [s_77(A,B,C,D,E,_),F=B-1].
s_77(A, B, C, D, E, F) :-
        [s_43(A,B,C,D,E,F),A=D].
s_43(A, B, C, D, E, F) :-
        [s_19(_,B,C,D,E,F),A=D].
s_19(A, B, C, D, E, F) :-
        [s_4(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_308(A, B, C, D, E, F) :-
        [s_168(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_168(A, B, C, D, E, F) :-
        [s_80(G,H,I,J,K,L),t_2_53(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_53(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_77(A,B,C,D,E,F),L=H-1,K=E,J=D,I=C,H=B,G=A].
s_77(A, B, C, D, E, F) :-
        [s_43(A,B,C,D,E,F),A=D].
s_43(A, B, C, D, E, F) :-
        [s_19(_,B,C,D,E,F),A=D].
s_19(A, B, C, D, E, F) :-
        [s_4(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_80(A, B, C, D, E, F) :-
        [s_46(G,H,I,J,K,L),t_2_42(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_42(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_43(A,B,C,D,E,F),G=J,L=F,K=E,J=D,I=C,H=B,G=A].
s_43(A, B, C, D, E, F) :-
        [s_19(_,B,C,D,E,F),A=D].
s_19(A, B, C, D, E, F) :-
        [s_4(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_46(A, B, C, D, E, F) :-
        [s_22(G,H,I,J,K,L),t_2_25(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_25(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_19(A,B,C,D,E,F),G=J,L=F,K=E,J=D,I=C,H=B].
s_19(A, B, C, D, E, F) :-
        [s_4(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_22(A, B, C, D, E, F) :-
        [s_2(G,H,I,J,K,L),t_2_11(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_11(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_4(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_553(A, B, C, D, E, F) :-
        [s_337(G,H,I,J,K,L),t_3_28(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_3_28(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_22(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_22(A, B, C, D, E, F) :-
        [s_2(G,H,I,J,K,L),t_2_11(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_11(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_4(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_337(A, B, C, D, E, F) :-
        [s_200(G,H,I,J,K,L),t_3_31(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_3_31(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_24(A,B,C,D,E,F),I=0,L=F,K=E,J=D,H=B,G=A].
s_24(A, B, C, D, E, F) :-
        [s_5(A,B,C,_,E,F),D=3].
s_5(A, B, C, D, E, F) :-
        [s_1(A,B,I,D,E,F),C=rat(1,1),B=rat(0,1),I=rat(0,1)].
s_1(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_200(A, B, C, D, E, F) :-
        [s_103(G,H,I,J,K,L),t_3_14(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_3_14(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_5(A,B,C,D,E,F),J=3,L=F,K=E,I=C,H=B,G=A].
s_5(A, B, C, D, E, F) :-
        [s_1(A,B,I,D,E,F),C=rat(1,1),B=rat(0,1),I=rat(0,1)].
s_1(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_103(A, B, C, D, E, F) :-
        [s_60(A,B,I,D,E,F),C=rat(1,1),B=rat(0,1),I=rat(0,1)].
s_60(A, B, C, D, E, F) :-
        [s_27(G,H,I,J,K,L),t_3_31(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_3_31(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_24(A,B,C,D,E,F),I=0,L=F,K=E,J=D,H=B,G=A].
s_24(A, B, C, D, E, F) :-
        [s_5(A,B,C,_,E,F),D=3].
s_5(A, B, C, D, E, F) :-
        [s_1(A,B,I,D,E,F),C=rat(1,1),B=rat(0,1),I=rat(0,1)].
s_1(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_27(A, B, C, D, E, F) :-
        [s_7(G,H,I,J,K,L),t_3_14(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_3_14(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_5(A,B,C,D,E,F),J=3,L=F,K=E,I=C,H=B,G=A].
s_5(A, B, C, D, E, F) :-
        [s_1(A,B,I,D,E,F),C=rat(1,1),B=rat(0,1),I=rat(0,1)].
s_1(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_7(A, B, C, D, E, F) :-
        [s_3(G,H,I,J,K,L),t_3_2(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_3_2(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_1(A,B,C,D,E,F),I=rat(1,1),H=rat(0,1),C=rat(0,1),L=F,K=E,J=D,H=B,G=A].
s_1(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_3(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_1943(A, B, C, D, E, F) :-
        [s_1022(G,H,I,J,K,L),t_1_27(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_1_27(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_22(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_22(A, B, C, D, E, F) :-
        [s_2(G,H,I,J,K,L),t_2_11(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_11(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_4(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_1022(A, B, C, D, E, F) :-
        [s_55(G,H,I,J,K,L),t_1_109(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_1_109(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_568(A,B,C,D,E,F),G=J,L=F,K=E,J=D,I=C,H=B].
s_568(A, B, C, D, E, F) :-
        [s_350(G,H,I,J,K,L),t_4_3(G,H,I,J,K,L,A,B,C,D,E,F),{K=E}].
t_4_3(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_1(A,B,C,D,E,F),I=rat(1,1),H=rat(0,1),C=rat(0,1),L=F,K=E,J=D,H=B,G=A].
s_1(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_350(A, B, C, D, E, F) :-
        [s_231(G,H,I,J,K,L),t_4_70(G,H,I,J,K,L,A,B,C,D,E,F),{K=E}].
t_4_70(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_208(A,B,C,D,E,F),H=K,L=F,K=E,J=D,I=C,G=A].
s_208(A, B, C, D, E, F) :-
        [s_109(G,H,I,J,K,L),t_2_20(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_20(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_10(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_10(A, B, C, D, E, F) :-
        [s_4(G,H,I,J,K,L),t_4_6(G,H,I,J,K,L,A,B,C,D,E,F),{K=E}].
t_4_6(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_2(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_109(A, B, C, D, E, F) :-
        [s_63(A,B,C,D,_,F),E=B-1].
s_63(A, B, C, D, E, F) :-
        [s_29(A,B,C,D,E,F),A=D].
s_29(A, B, C, D, E, F) :-
        [s_9(_,B,C,D,E,F),A=D].
s_9(A, B, C, D, E, F) :-
        [s_2(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_231(A, B, C, D, E, F) :-
        [s_110(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_110(A, B, C, D, E, F) :-
        [s_10(G,H,I,J,K,L),t_4_48(G,H,I,J,K,L,A,B,C,D,E,F),{K=E}].
t_4_48(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_63(A,B,C,D,E,F),K=H-1,L=F,J=D,I=C,H=B,G=A].
s_63(A, B, C, D, E, F) :-
        [s_29(A,B,C,D,E,F),A=D].
s_29(A, B, C, D, E, F) :-
        [s_9(_,B,C,D,E,F),A=D].
s_9(A, B, C, D, E, F) :-
        [s_2(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_10(A, B, C, D, E, F) :-
        [s_4(G,H,I,J,K,L),t_4_6(G,H,I,J,K,L,A,B,C,D,E,F),{K=E}].
t_4_6(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_2(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_55(A, B, C, D, E, F) :-
        [s_23(G,H,I,J,K,L),t_1_7(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_1_7(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_3(A,B,C,D,E,F),I=rat(1,1),H=rat(0,1),C=rat(0,1),L=F,K=E,J=D,H=B,G=A].
s_3(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_23(A, B, C, D, E, F) :-
        [s_1(G,H,I,J,K,L),t_1_10(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_1_10(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_4(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_1(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_2803(A, B, C, D, E, F) :-
        [s_1434(G,H,I,J,K,L),t_2_170(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_170(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_1366(A,B,C,D,E,F),I=0,L=F,K=E,J=D,H=B,G=A].
s_1366(A, B, C, D, E, F) :-
        [s_971(G,H,I,J,K,L),t_3_122(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_3_122(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_795(A,B,C,D,E,F),G=J,L=F,K=E,J=D,I=C,H=B].
s_795(A, B, C, D, E, F) :-
        [s_493(G,H,I,J,K,L),t_2_1(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_1(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_1(A,B,C,D,E,F),I=rat(1,1),H=rat(0,1),C=rat(0,1),L=F,K=E,J=D,H=B,G=A].
s_1(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_493(A, B, C, D, E, F) :-
        [s_308(G,H,I,J,K,L),t_2_79(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_79(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_301(A,B,C,D,E,F),H=L,L=F,K=E,J=D,I=C,G=A].
s_301(A, B, C, D, E, F) :-
        [s_163(G,H,I,J,K,L),t_4_29(G,H,I,J,K,L,A,B,C,D,E,F),{K=E}].
t_4_29(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_22(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_22(A, B, C, D, E, F) :-
        [s_2(G,H,I,J,K,L),t_2_11(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_11(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_4(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_163(A, B, C, D, E, F) :-
        [s_77(A,B,C,D,E,_),F=B-1].
s_77(A, B, C, D, E, F) :-
        [s_43(A,B,C,D,E,F),A=D].
s_43(A, B, C, D, E, F) :-
        [s_19(_,B,C,D,E,F),A=D].
s_19(A, B, C, D, E, F) :-
        [s_4(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_308(A, B, C, D, E, F) :-
        [s_168(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_168(A, B, C, D, E, F) :-
        [s_80(G,H,I,J,K,L),t_2_53(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_53(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_77(A,B,C,D,E,F),L=H-1,K=E,J=D,I=C,H=B,G=A].
s_77(A, B, C, D, E, F) :-
        [s_43(A,B,C,D,E,F),A=D].
s_43(A, B, C, D, E, F) :-
        [s_19(_,B,C,D,E,F),A=D].
s_19(A, B, C, D, E, F) :-
        [s_4(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_80(A, B, C, D, E, F) :-
        [s_46(G,H,I,J,K,L),t_2_42(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_42(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_43(A,B,C,D,E,F),G=J,L=F,K=E,J=D,I=C,H=B,G=A].
s_43(A, B, C, D, E, F) :-
        [s_19(_,B,C,D,E,F),A=D].
s_19(A, B, C, D, E, F) :-
        [s_4(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_46(A, B, C, D, E, F) :-
        [s_22(G,H,I,J,K,L),t_2_25(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_25(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_19(A,B,C,D,E,F),G=J,L=F,K=E,J=D,I=C,H=B].
s_19(A, B, C, D, E, F) :-
        [s_4(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_22(A, B, C, D, E, F) :-
        [s_2(G,H,I,J,K,L),t_2_11(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_11(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_4(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_971(A, B, C, D, E, F) :-
        [s_550(G,H,I,J,K,L),t_3_5(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_3_5(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_2(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_550(A, B, C, D, E, F) :-
        [s_336(G,H,I,J,K,L),t_3_31(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_3_31(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_24(A,B,C,D,E,F),I=0,L=F,K=E,J=D,H=B,G=A].
s_24(A, B, C, D, E, F) :-
        [s_5(A,B,C,_,E,F),D=3].
s_5(A, B, C, D, E, F) :-
        [s_1(A,B,I,D,E,F),C=rat(1,1),B=rat(0,1),I=rat(0,1)].
s_1(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_336(A, B, C, D, E, F) :-
        [s_199(G,H,I,J,K,L),t_3_14(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_3_14(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_5(A,B,C,D,E,F),J=3,L=F,K=E,I=C,H=B,G=A].
s_5(A, B, C, D, E, F) :-
        [s_1(A,B,I,D,E,F),C=rat(1,1),B=rat(0,1),I=rat(0,1)].
s_1(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_199(A, B, C, D, E, F) :-
        [s_103(A,B,C,_,E,F),D=3].
s_103(A, B, C, D, E, F) :-
        [s_60(A,B,I,D,E,F),C=rat(1,1),B=rat(0,1),I=rat(0,1)].
s_60(A, B, C, D, E, F) :-
        [s_27(G,H,I,J,K,L),t_3_31(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_3_31(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_24(A,B,C,D,E,F),I=0,L=F,K=E,J=D,H=B,G=A].
s_24(A, B, C, D, E, F) :-
        [s_5(A,B,C,_,E,F),D=3].
s_5(A, B, C, D, E, F) :-
        [s_1(A,B,I,D,E,F),C=rat(1,1),B=rat(0,1),I=rat(0,1)].
s_1(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_27(A, B, C, D, E, F) :-
        [s_7(G,H,I,J,K,L),t_3_14(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_3_14(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_5(A,B,C,D,E,F),J=3,L=F,K=E,I=C,H=B,G=A].
s_5(A, B, C, D, E, F) :-
        [s_1(A,B,I,D,E,F),C=rat(1,1),B=rat(0,1),I=rat(0,1)].
s_1(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_7(A, B, C, D, E, F) :-
        [s_3(G,H,I,J,K,L),t_3_2(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_3_2(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_1(A,B,C,D,E,F),I=rat(1,1),H=rat(0,1),C=rat(0,1),L=F,K=E,J=D,H=B,G=A].
s_1(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_3(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_1434(A, B, C, D, E, F) :-
        [s_796(G,H,I,J,K,L),t_2_22(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_22(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_13(A,B,C,D,E,F),J=3,L=F,K=E,I=C,H=B,G=A].
s_13(A, B, C, D, E, F) :-
        [s_3(A,B,I,D,E,F),C=rat(1,1),B=rat(0,1),I=rat(0,1)].
s_3(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_796(A, B, C, D, E, F) :-
        [s_493(G,H,I,J,K,L),t_2_8(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_8(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_3(A,B,C,D,E,F),I=rat(1,1),H=rat(0,1),C=rat(0,1),L=F,K=E,J=D,H=B,G=A].
s_3(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_493(A, B, C, D, E, F) :-
        [s_308(G,H,I,J,K,L),t_2_79(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_79(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_301(A,B,C,D,E,F),H=L,L=F,K=E,J=D,I=C,G=A].
s_301(A, B, C, D, E, F) :-
        [s_163(G,H,I,J,K,L),t_4_29(G,H,I,J,K,L,A,B,C,D,E,F),{K=E}].
t_4_29(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_22(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_22(A, B, C, D, E, F) :-
        [s_2(G,H,I,J,K,L),t_2_11(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_11(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_4(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_163(A, B, C, D, E, F) :-
        [s_77(A,B,C,D,E,_),F=B-1].
s_77(A, B, C, D, E, F) :-
        [s_43(A,B,C,D,E,F),A=D].
s_43(A, B, C, D, E, F) :-
        [s_19(_,B,C,D,E,F),A=D].
s_19(A, B, C, D, E, F) :-
        [s_4(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_308(A, B, C, D, E, F) :-
        [s_168(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_168(A, B, C, D, E, F) :-
        [s_80(G,H,I,J,K,L),t_2_53(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_53(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_77(A,B,C,D,E,F),L=H-1,K=E,J=D,I=C,H=B,G=A].
s_77(A, B, C, D, E, F) :-
        [s_43(A,B,C,D,E,F),A=D].
s_43(A, B, C, D, E, F) :-
        [s_19(_,B,C,D,E,F),A=D].
s_19(A, B, C, D, E, F) :-
        [s_4(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_80(A, B, C, D, E, F) :-
        [s_46(G,H,I,J,K,L),t_2_42(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_42(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_43(A,B,C,D,E,F),G=J,L=F,K=E,J=D,I=C,H=B,G=A].
s_43(A, B, C, D, E, F) :-
        [s_19(_,B,C,D,E,F),A=D].
s_19(A, B, C, D, E, F) :-
        [s_4(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_46(A, B, C, D, E, F) :-
        [s_22(G,H,I,J,K,L),t_2_25(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_25(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_19(A,B,C,D,E,F),G=J,L=F,K=E,J=D,I=C,H=B].
s_19(A, B, C, D, E, F) :-
        [s_4(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_22(A, B, C, D, E, F) :-
        [s_2(G,H,I,J,K,L),t_2_11(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_11(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_4(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_1104(A, B, C, D, E, F) :-
        [s_607(A,B,C,_,E,F),D=3].
s_607(A, B, C, D, E, F) :-
        [s_355(A,B,I,D,E,F),C=rat(1,1),B=rat(0,1),I=rat(0,1)].
s_355(A, B, C, D, E, F) :-
        [s_134(G,H,I,J,K,L),t_3_69(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_3_69(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_208(A,B,C,D,E,F),H=K,L=F,K=E,J=D,I=C,G=A].
s_208(A, B, C, D, E, F) :-
        [s_109(G,H,I,J,K,L),t_2_20(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_20(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_10(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_10(A, B, C, D, E, F) :-
        [s_4(G,H,I,J,K,L),t_4_6(G,H,I,J,K,L,A,B,C,D,E,F),{K=E}].
t_4_6(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_2(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_109(A, B, C, D, E, F) :-
        [s_63(A,B,C,D,_,F),E=B-1].
s_63(A, B, C, D, E, F) :-
        [s_29(A,B,C,D,E,F),A=D].
s_29(A, B, C, D, E, F) :-
        [s_9(_,B,C,D,E,F),A=D].
s_9(A, B, C, D, E, F) :-
        [s_2(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_134(A, B, C, D, E, F) :-
        [s_45(G,H,I,J,K,L),t_3_50(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_3_50(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_67(A,B,C,D,E,F),K=H-1,L=F,J=D,I=C,H=B,G=A].
s_67(A, B, C, D, E, F) :-
        [s_33(A,B,C,D,E,F),A=D].
s_33(A, B, C, D, E, F) :-
        [s_29(G,H,I,J,K,L),t_2_20(G,H,I,J,K,L,A,B,C,D,E,F),{L=F}].
t_2_20(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_10(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_10(A, B, C, D, E, F) :-
        [s_4(G,H,I,J,K,L),t_4_6(G,H,I,J,K,L,A,B,C,D,E,F),{K=E}].
t_4_6(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_2(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_29(A, B, C, D, E, F) :-
        [s_9(_,B,C,D,E,F),A=D].
s_9(A, B, C, D, E, F) :-
        [s_2(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_45(A, B, C, D, E, F) :-
        [s_21(G,H,I,J,K,L),t_3_26(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_3_26(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_19(A,B,C,D,E,F),G=J,L=F,K=E,J=D,I=C,H=B].
s_19(A, B, C, D, E, F) :-
        [s_4(A,H,C,D,E,F),H=rat(-1,1)+B,C=rat(0,1)].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_21(A, B, C, D, E, F) :-
        [s_11(G,H,I,J,K,L),t_3_12(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_3_12(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_4(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_4(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_11(A, B, C, D, E, F) :-
        [s_3(G,H,I,J,K,L),t_3_5(G,H,I,J,K,L,A,B,C,D,E,F),{L=F,K=E}].
t_3_5(A, B, C, D, E, F, G, H, I, J, K, L) :-
        [s_2(A,B,C,D,E,F),B=rat(-1,1)+H,I=rat(0,1),L=F,K=E,J=D,I=C,G=A].
s_2(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
s_3(_, B, C, _, _, _) :-
        [B=0,C=0,B=0,C=0].
