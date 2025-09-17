import java.util.*;

public class RelationshipChecker {
    static Map<String, String> gender = new HashMap<>();
    static Map<String, Set<String>> marriages = new HashMap<>();
    static Map<String, Set<String>> children = new HashMap<>();

    // Define marriages (bidirectional)
    static void addMarriage(String a, String b) {
        marriages.computeIfAbsent(a, k -> new HashSet<>()).add(b);
        marriages.computeIfAbsent(b, k -> new HashSet<>()).add(a);
    }

    // Define biological parent-child relationship
    static void addParent(String parent, String child) {
        children.computeIfAbsent(parent, k -> new HashSet<>()).add(child);
    }

    // Get biological parents of a child
    static Set<String> getBiologicalParentsOf(String child) {
        Set<String> parents = new HashSet<>();
        for (Map.Entry<String, Set<String>> entry : children.entrySet()) {
            if (entry.getValue().contains(child)) {
                parents.add(entry.getKey());
            }
        }
        return parents;
    }

    // Get all parents of a child (includes Rule 1 logic)
    static Set<String> getAllParentsOf(String child) {
        Set<String> parents = new HashSet<>();
        for (Map.Entry<String, Set<String>> entry : children.entrySet()) {
            if (entry.getValue().contains(child)) {
                String p = entry.getKey();
                parents.add(p);
                parents.addAll(marriages.getOrDefault(p, Set.of()));
            }
        }
        return parents;
    }

    // Rule 1: Parent relationship (with marriage)
    static boolean isParent(String x, String z) {
        return getAllParentsOf(z).contains(x);
    }

    // Rule 2: Siblings if they share at least one parent (incl. marital)
    static boolean areSiblings(String x, String y) {
        if (x.equals(y)) return false;
        Set<String> xParents = getAllParentsOf(x);
        Set<String> yParents = getAllParentsOf(y);
        for (String p : xParents) {
            if (yParents.contains(p)) return true;
        }
        return false;
    }

    // Rule 3: Male siblings
    static boolean areBrothers(String x, String y) {
        return areSiblings(x, y) && "male".equals(gender.get(x)) && "male".equals(gender.get(y));
    }

    // Rule 4: Female siblings
    static boolean areSisters(String x, String y) {
        return areSiblings(x, y) && "female".equals(gender.get(x)) && "female".equals(gender.get(y));
    }

    // Rule 5: Cousins if their biological parents are siblings
    static boolean areCousins(String x, String y) {
        Set<String> xParents = getBiologicalParentsOf(x);
        Set<String> yParents = getBiologicalParentsOf(y);
        for (String xp : xParents) {
            for (String yp : yParents) {
                if (areSiblings(xp, yp)) return true;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        // Define genders
        String[] males = {"Andy", "Bob", "Cecil", "Dennis", "Edward", "Felix", "Martin", "Oscar", "Quinn"};
        String[] females = {"Gigi", "Helen", "Iris", "Jane", "Kate", "Liz", "Nancy", "Pattie", "Rebecca"};
        for (String m : males) gender.put(m, "male");
        for (String f : females) gender.put(f, "female");

        // Marriages
        addMarriage("Bob", "Helen");
        addMarriage("Dennis", "Pattie");
        addMarriage("Gigi", "Martin");

        // Parent-child relationships
        addParent("Andy", "Bob");
        addParent("Bob", "Cecil");
        addParent("Cecil", "Dennis");
        addParent("Dennis", "Edward");
        addParent("Edward", "Felix");

        addParent("Gigi", "Helen");
        addParent("Helen", "Iris");
        addParent("Iris", "Jane");
        addParent("Jane", "Kate");
        addParent("Kate", "Liz");

        addParent("Martin", "Nancy");
        addParent("Nancy", "Oscar");
        addParent("Oscar", "Pattie");
        addParent("Pattie", "Quinn");
        addParent("Quinn", "Rebecca");

        // Cousin test setup
        addParent("Cecil", "John");
        addParent("Cecil", "Mary");      // John and Mary are siblings
        addParent("John", "Adam");
        addParent("Mary", "Ben");        // Adam and Ben are cousins

        // Core relationship validations
        System.out.println("Are Liz and Rebecca cousins? " + areCousins("Liz", "Rebecca"));         // false
        System.out.println("Are Oscar and Nancy brothers? " + areBrothers("Oscar", "Nancy"));       // false
        System.out.println("Are Helen and Bob parents of Cecil? " +
            (isParent("Helen", "Cecil") && isParent("Bob", "Cecil")));                              // true
        System.out.println("Are Kate and Nancy cousins? " + areCousins("Kate", "Nancy"));           // false
        System.out.println("Are Felix and Liz cousins? " + areCousins("Felix", "Liz"));             // false
        System.out.println("Are Iris and Helen sisters? " + areSisters("Iris", "Helen"));           // false
        System.out.println("Are Edward and Quinn siblings? " + areSiblings("Edward", "Quinn"));     // true
        System.out.println("Are Edward and Quinn cousins? " + areCousins("Edward", "Quinn"));       // false

        // Marriage checks
        System.out.println("Are Bob and Helen married? " + marriages.getOrDefault("Bob", Set.of()).contains("Helen"));      // true
        System.out.println("Are Dennis and Pattie married? " + marriages.getOrDefault("Dennis", Set.of()).contains("Pattie"));  // true
        System.out.println("Are Gigi and Martin married? " + marriages.getOrDefault("Gigi", Set.of()).contains("Martin"));      // true

        // Extra test cases
        System.out.println("Are Dennis and Cecil siblings? " + areSiblings("Dennis", "Cecil"));      // false
        System.out.println("Are Cecil and Dennis parent/child? " + isParent("Cecil", "Dennis"));     // true
        System.out.println("Are Gigi and Martin siblings? " + areSiblings("Gigi", "Martin"));        // false
        System.out.println("Are Kate and Liz sisters? " + areSisters("Kate", "Liz"));                // false
        System.out.println("Are Jane and Iris siblings? " + areSiblings("Jane", "Iris"));            // false
        System.out.println("Are Jane and Kate parent/child? " + isParent("Jane", "Kate"));           // true

        // Confirmed cousin pair
        System.out.println("Are John and Mary siblings? " + areSiblings("John", "Mary"));            // true
        System.out.println("Are Adam and Ben cousins? " + areCousins("Adam", "Ben"));                // true

        // Extra test case
        System.out.println("Are Adam and Mary cousins? " + areCousins("Adam", "Mary"));              // false
        

        // Extra test case
        System.out.println("Are Cecil and Iris siblings? " + areSiblings("Cecil", "Iris"));
    }
}
