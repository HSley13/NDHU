(* Gender definitions *)
val male = ["andy", "bob", "cecil", "dennis", "edward", "felix", "martin", "oscar", "quinn", "john", "adam"];
val female = ["gigi", "helen", "iris", "jane", "kate", "liz", "nancy", "pattie", "rebecca", "mary", "ben"];

(* Marriages (bidirectional) *)
val married = [
    ("bob", "helen"), ("helen", "bob"),
    ("dennis", "pattie"), ("pattie", "dennis"),
    ("gigi", "martin"), ("martin", "gigi")
];

(* Parent-child relationships *)
val parent = [
    ("andy", "bob"), ("bob", "cecil"), ("cecil", "dennis"), ("dennis", "edward"), ("edward", "felix"),
    ("gigi", "helen"), ("helen", "iris"), ("iris", "jane"), ("jane", "kate"), ("kate", "liz"),
    ("martin", "nancy"), ("nancy", "oscar"), ("oscar", "pattie"), ("pattie", "quinn"), ("quinn", "rebecca"),
    ("cecil", "john"), ("cecil", "mary"), ("john", "adam"), ("mary", "ben")
];

(* Helper to remove duplicates from a list *)
fun removeDuplicates lst =
    let
        fun add (x, seen) = if List.exists (fn y => y = x) seen then seen else x :: seen
    in
        List.foldr add [] lst
    end;

(* Get list of spouses for a person *)
fun getSpouses p =
    List.map #2 (List.filter (fn (a, _) => a = p) married);

(* Get biological parents of a child *)
fun getBiologicalParents c =
    List.map #1 (List.filter (fn (_, ch) => ch = c) parent);

(* Get all parents, including spouses of biological parents *)
fun getAllParents c =
    let
        val bio = getBiologicalParents c;
        val spouses = List.concat (List.map getSpouses bio)
    in
        removeDuplicates (bio @ spouses)
    end;

(* Rule 1: isParent(x, z) *)
fun isParent x z = List.exists (fn p => p = x) (getAllParents z);

(* Rule 2: siblings(x, y) *)
fun siblings x y =
    if x = y then false
    else
        let
            val px = getAllParents x
            val py = getAllParents y
        in
            List.exists (fn p => List.exists (fn q => p = q) py) px
        end;

(* Rule 3: brothers(x, y) *)
fun isBrother x y =
    siblings x y andalso List.exists (fn m => m = x) male andalso List.exists (fn m => m = y) male;

(* Rule 4: sisters(x, y) *)
fun isSister x y =
    siblings x y andalso List.exists (fn f => f = x) female andalso List.exists (fn f => f = y) female;

(* Rule 5: cousins(x, y) *)
fun isCousin x y =
    let
        val px = getBiologicalParents x
        val py = getBiologicalParents y
    in
        List.exists (fn a => List.exists (fn b => siblings a b) py) px
    end;

(* Test Cases *)
fun test (label, result) = print (label ^ ": " ^ Bool.toString result ^ "\n");

val _ = (
  test ("Are Liz and Rebecca cousins", isCousin "liz" "rebecca");          (* false *)
  test ("Are Oscar and Nancy brothers", isBrother "oscar" "nancy");       (* false *)
  test ("Are Helen and Bob parents of Cecil", isParent "helen" "cecil" andalso isParent "bob" "cecil"); (* true *)
  test ("Are Kate and Nancy cousins", isCousin "kate" "nancy");           (* false *)
  test ("Are Felix and Liz cousins", isCousin "felix" "liz");             (* false *)
  test ("Are Iris and Helen sisters", isSister "iris" "helen");           (* false *)
  test ("Are Edward and Quinn siblings", siblings "edward" "quinn");      (* true *)
  test ("Are Edward and Quinn cousins", isCousin "edward" "quinn");       (* false *)
  test ("Are Dennis and Cecil siblings", siblings "dennis" "cecil");      (* false *)
  test ("Are Cecil and Dennis parent/child", isParent "cecil" "dennis");  (* true *)
  test ("Are Gigi and Martin siblings", siblings "gigi" "martin");        (* false *)
  test ("Are Kate and Liz sisters", isSister "kate" "liz");               (* false *)
  test ("Are Jane and Iris siblings", siblings "jane" "iris");            (* false *)
  test ("Are Jane and Kate parent/child", isParent "jane" "kate");        (* true *)
  test ("Are John and Mary siblings", siblings "john" "mary");            (* true *)
  test ("Are Liz and Rebecca cousins", isCousin "liz" "rebecca")                (* true *)
);
