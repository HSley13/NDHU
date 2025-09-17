% ----- Gender Definitions -----
male(andy).
male(bob).
male(cecil).
male(dennis).
male(edward).
male(felix).
male(martin).
male(oscar).
male(quinn).
male(john).
male(adam).

female(gigi).
female(helen).
female(iris).
female(jane).
female(kate).
female(liz).
female(nancy).
female(pattie).
female(rebecca).
female(mary).
female(ben).

% ----- Marriage (bidirectional) -----
married(bob, helen).
married(helen, bob).
married(dennis, pattie).
married(pattie, dennis).
married(gigi, martin).
married(martin, gigi).

% ----- Parent-child -----
parent(andy, bob).
parent(bob, cecil).
parent(cecil, dennis).
parent(dennis, edward).
parent(edward, felix).

parent(gigi, helen).
parent(helen, iris).
parent(iris, jane).
parent(jane, kate).
parent(kate, liz).

parent(martin, nancy).
parent(nancy, oscar).
parent(oscar, pattie).
parent(pattie, quinn).
parent(quinn, rebecca).

% Additional cousin test setup
parent(cecil, john).
parent(cecil, mary).
parent(john, adam).
parent(mary, ben).

% ----- Derived Rules -----

% Rule 1: is_parent includes married partner
is_parent(X, Z) :-
    parent(X, Z);
    (parent(P, Z), married(P, X)).

% Rule 2: siblings if they share a parent (incl. married)
siblings(X, Y) :-
    X \= Y,
    is_parent(P, X),
    is_parent(P, Y).

% Rule 3: brothers
brothers(X, Y) :-
    siblings(X, Y),
    male(X), male(Y).

% Rule 4: sisters
sisters(X, Y) :-
    siblings(X, Y),
    female(X), female(Y).

% Rule 5: cousins: if their biological parents are siblings
cousins(X, Y) :-
    parent(PX, X),
    parent(PY, Y),
    siblings(PX, PY).

% ----- Test Queries -----
test :-
    (cousins(liz, rebecca) -> T1 = true ; T1 = false),
    format("Are Liz and Rebecca cousins: ~w~n", [T1]),

    (brothers(oscar, nancy) -> T2 = true ; T2 = false),
    format("Are Oscar and Nancy brothers: ~w~n", [T2]),

    (is_parent(helen, cecil), is_parent(bob, cecil) -> T3 = true ; T3 = false),
    format("Are Helen and Bob parents of Cecil: ~w~n", [T3]),

    (cousins(kate, nancy) -> T4 = true ; T4 = false),
    format("Are Kate and Nancy cousins: ~w~n", [T4]),

    (cousins(felix, liz) -> T5 = true ; T5 = false),
    format("Are Felix and Liz cousins: ~w~n", [T5]),

    (sisters(iris, helen) -> T6 = true ; T6 = false),
    format("Are Iris and Helen sisters: ~w~n", [T6]),

    (siblings(edward, quinn) -> T7 = true ; T7 = false),
    format("Are Edward and Quinn siblings: ~w~n", [T7]),

    (cousins(edward, quinn) -> T8 = true ; T8 = false),
    format("Are Edward and Quinn cousins: ~w~n", [T8]),

    (siblings(dennis, cecil) -> T9 = true ; T9 = false),
    format("Are Dennis and Cecil siblings: ~w~n", [T9]),

    (is_parent(cecil, dennis) -> T10 = true ; T10 = false),
    format("Are Cecil and Dennis parent/child: ~w~n", [T10]),

    (siblings(gigi, martin) -> T11 = true ; T11 = false),
    format("Are Gigi and Martin siblings: ~w~n", [T11]),

    (sisters(kate, liz) -> T12 = true ; T12 = false),
    format("Are Kate and Liz sisters: ~w~n", [T12]),

    (siblings(jane, iris) -> T13 = true ; T13 = false),
    format("Are Jane and Iris siblings: ~w~n", [T13]),

    (is_parent(jane, kate) -> T14 = true ; T14 = false),
    format("Are Jane and Kate parent/child: ~w~n", [T14]),

    (siblings(john, mary) -> T15 = true ; T15 = false),
    format("Are John and Mary siblings: ~w~n", [T15]),

    (cousins(adam, ben) -> T16 = true ; T16 = false),
    format("Are Adam and Ben cousins: ~w~n", [T16]).
