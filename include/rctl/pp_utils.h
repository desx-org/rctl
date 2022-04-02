#define PP_COUNT_IMPL(\
 _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, _10, _11, _12, _13, _14, _15, _16,\
_17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32,\
_33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48,\
_49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64,\
count, ...) count

#define BETTER_ENUMS_PP_COUNT(...) \
PP_COUNT_IMPL(__VA_ARGS__, \
64, 63, 62, 61, 60, \
59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
 9,  8,  7,  6,  5,  4,  3,  2,  1)

#define FE_00(N,WHAT)
#define FE_01(N,WHAT, X) WHAT(N,X) 
#define FE_02(N,WHAT, X, ...) WHAT(N,X)FE_01(N+1,WHAT, __VA_ARGS__)
#define FE_03(N,WHAT, X, ...) WHAT(N,X)FE_02(N+1,WHAT, __VA_ARGS__)
#define FE_04(N,WHAT, X, ...) WHAT(N,X)FE_03(N+1,WHAT, __VA_ARGS__)
#define FE_05(N,WHAT, X, ...) WHAT(N,X)FE_04(N+1,WHAT, __VA_ARGS__)
#define FE_06(N,WHAT, X, ...) WHAT(N,X)FE_05(N+1,WHAT, __VA_ARGS__)
#define FE_07(N,WHAT, X, ...) WHAT(N,X)FE_06(N+1,WHAT, __VA_ARGS__)
#define FE_08(N,WHAT, X, ...) WHAT(N,X)FE_07(N+1,WHAT, __VA_ARGS__)
#define FE_09(N,WHAT, X, ...) WHAT(N,X)FE_08(N+1,WHAT, __VA_ARGS__)
#define FE_10(N,WHAT, X, ...) WHAT(N,X)FE_09(N+1,WHAT, __VA_ARGS__)
#define FE_11(N,WHAT, X, ...) WHAT(N,X)FE_10(N+1,WHAT, __VA_ARGS__)
#define FE_12(N,WHAT, X, ...) WHAT(N,X)FE_11(N+1,WHAT, __VA_ARGS__)
#define FE_13(N,WHAT, X, ...) WHAT(N,X)FE_12(N+1,WHAT, __VA_ARGS__)
#define FE_14(N,WHAT, X, ...) WHAT(N,X)FE_13(N+1,WHAT, __VA_ARGS__)
#define FE_15(N,WHAT, X, ...) WHAT(N,X)FE_14(N+1,WHAT, __VA_ARGS__)
#define FE_16(N,WHAT, X, ...) WHAT(N,X)FE_15(N+1,WHAT, __VA_ARGS__)
#define FE_17(N,WHAT, X, ...) WHAT(N,X)FE_16(N+1,WHAT, __VA_ARGS__)
#define FE_18(N,WHAT, X, ...) WHAT(N,X)FE_17(N+1,WHAT, __VA_ARGS__)
#define FE_19(N,WHAT, X, ...) WHAT(N,X)FE_18(N+1,WHAT, __VA_ARGS__)
#define FE_20(N,WHAT, X, ...) WHAT(N,X)FE_19(N+1,WHAT, __VA_ARGS__)
#define FE_21(N,WHAT, X, ...) WHAT(N,X)FE_20(N+1,WHAT, __VA_ARGS__)
#define FE_22(N,WHAT, X, ...) WHAT(N,X)FE_21(N+1,WHAT, __VA_ARGS__)
#define FE_23(N,WHAT, X, ...) WHAT(N,X)FE_22(N+1,WHAT, __VA_ARGS__)
#define FE_24(N,WHAT, X, ...) WHAT(N,X)FE_23(N+1,WHAT, __VA_ARGS__)
#define FE_25(N,WHAT, X, ...) WHAT(N,X)FE_24(N+1,WHAT, __VA_ARGS__)
#define FE_26(N,WHAT, X, ...) WHAT(N,X)FE_25(N+1,WHAT, __VA_ARGS__)
#define FE_27(N,WHAT, X, ...) WHAT(N,X)FE_26(N+1,WHAT, __VA_ARGS__)
#define FE_28(N,WHAT, X, ...) WHAT(N,X)FE_27(N+1,WHAT, __VA_ARGS__)
#define FE_29(N,WHAT, X, ...) WHAT(N,X)FE_28(N+1,WHAT, __VA_ARGS__)
#define FE_30(N,WHAT, X, ...) WHAT(N,X)FE_29(N+1,WHAT, __VA_ARGS__)
#define FE_31(N,WHAT, X, ...) WHAT(N,X)FE_30(N+1,WHAT, __VA_ARGS__)
#define FE_32(N,WHAT, X, ...) WHAT(N,X)FE_31(N+1,WHAT, __VA_ARGS__)
#define FE_33(N,WHAT, X, ...) WHAT(N,X)FE_32(N+1,WHAT, __VA_ARGS__)
#define FE_34(N,WHAT, X, ...) WHAT(N,X)FE_33(N+1,WHAT, __VA_ARGS__)
#define FE_35(N,WHAT, X, ...) WHAT(N,X)FE_34(N+1,WHAT, __VA_ARGS__)
#define FE_36(N,WHAT, X, ...) WHAT(N,X)FE_35(N+1,WHAT, __VA_ARGS__)
#define FE_37(N,WHAT, X, ...) WHAT(N,X)FE_36(N+1,WHAT, __VA_ARGS__)
#define FE_38(N,WHAT, X, ...) WHAT(N,X)FE_37(N+1,WHAT, __VA_ARGS__)
#define FE_39(N,WHAT, X, ...) WHAT(N,X)FE_38(N+1,WHAT, __VA_ARGS__)
#define FE_40(N,WHAT, X, ...) WHAT(N,X)FE_39(N+1,WHAT, __VA_ARGS__)
#define FE_41(N,WHAT, X, ...) WHAT(N,X)FE_40(N+1,WHAT, __VA_ARGS__)
#define FE_42(N,WHAT, X, ...) WHAT(N,X)FE_41(N+1,WHAT, __VA_ARGS__)
#define FE_43(N,WHAT, X, ...) WHAT(N,X)FE_42(N+1,WHAT, __VA_ARGS__)
#define FE_44(N,WHAT, X, ...) WHAT(N,X)FE_43(N+1,WHAT, __VA_ARGS__)
#define FE_45(N,WHAT, X, ...) WHAT(N,X)FE_44(N+1,WHAT, __VA_ARGS__)
#define FE_46(N,WHAT, X, ...) WHAT(N,X)FE_45(N+1,WHAT, __VA_ARGS__)
#define FE_47(N,WHAT, X, ...) WHAT(N,X)FE_46(N+1,WHAT, __VA_ARGS__)
#define FE_48(N,WHAT, X, ...) WHAT(N,X)FE_47(N+1,WHAT, __VA_ARGS__)
#define FE_49(N,WHAT, X, ...) WHAT(N,X)FE_48(N+1,WHAT, __VA_ARGS__)
#define FE_50(N,WHAT, X, ...) WHAT(N,X)FE_49(N+1,WHAT, __VA_ARGS__)
#define FE_51(N,WHAT, X, ...) WHAT(N,X)FE_50(N+1,WHAT, __VA_ARGS__)
#define FE_52(N,WHAT, X, ...) WHAT(N,X)FE_51(N+1,WHAT, __VA_ARGS__)
#define FE_53(N,WHAT, X, ...) WHAT(N,X)FE_52(N+1,WHAT, __VA_ARGS__)
#define FE_54(N,WHAT, X, ...) WHAT(N,X)FE_53(N+1,WHAT, __VA_ARGS__)
#define FE_55(N,WHAT, X, ...) WHAT(N,X)FE_54(N+1,WHAT, __VA_ARGS__)
#define FE_56(N,WHAT, X, ...) WHAT(N,X)FE_55(N+1,WHAT, __VA_ARGS__)
#define FE_57(N,WHAT, X, ...) WHAT(N,X)FE_56(N+1,WHAT, __VA_ARGS__)
#define FE_58(N,WHAT, X, ...) WHAT(N,X)FE_57(N+1,WHAT, __VA_ARGS__)
#define FE_59(N,WHAT, X, ...) WHAT(N,X)FE_58(N+1,WHAT, __VA_ARGS__)
#define FE_60(N,WHAT, X, ...) WHAT(N,X)FE_59(N+1,WHAT, __VA_ARGS__)
#define FE_61(N,WHAT, X, ...) WHAT(N,X)FE_60(N+1,WHAT, __VA_ARGS__)
#define FE_62(N,WHAT, X, ...) WHAT(N,X)FE_61(N+1,WHAT, __VA_ARGS__)
#define FE_63(N,WHAT, X, ...) WHAT(N,X)FE_62(N+1,WHAT, __VA_ARGS__)
#define FE_64(N,WHAT, X, ...) WHAT(N,X)FE_63(N+1,WHAT, __VA_ARGS__)

#define GET_MACRO(\
 _00\
,_01,_02,_03,_04,_05,_06,_07,_08,_09,_0a,_0b,_0c,_0d,_0e,_0f,_10\
,_11,_12,_13,_14,_15,_16,_17,_18,_19,_1a,_1b,_1c,_1d,_1e,_1f,_20\
,_21,_22,_23,_24,_25,_26,_27,_28,_29,_2a,_2b,_2c,_2d,_2e,_2f,_30\
,_31,_32,_33,_34,_35,_36,_37,_38,_39,_3a,_3b,_3c,_3d,_3e,_3f,_40\
,NAME,...) NAME 

#define FOR_EACH(action,...) \
GET_MACRO(_0,__VA_ARGS__\
,FE_30,FE_3f,FE_3e,FE_3d,FE_3c,FE_3b,FE_3a,FE_39,FE_38,FE_37,FE_36,FE_35,FE_34,FE_33,FE_32,FE_31\
,FE_30,FE_2f,FE_2e,FE_2d,FE_2c,FE_2b,FE_2a,FE_29,FE_28,FE_27,FE_26,FE_25,FE_24,FE_23,FE_22,FE_21\
,FE_20,FE_1f,FE_1e,FE_1d,FE_1c,FE_1b,FE_1a,FE_19,FE_18,FE_17,FE_16,FE_15,FE_14,FE_13,FE_12,FE_11\
,FE_10,FE_0f,FE_0e,FE_0d,FE_0c,FE_0b,FE_0a,FE_09,FE_08,FE_07,FE_06,FE_05,FE_04,FE_03,FE_02,FE_01\
,FE_00)(00,action,__VA_ARGS__)
