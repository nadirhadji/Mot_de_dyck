tests_folder=tests
prog=motdedyck
help_first_line="Usage: ./motdedyck [HEIGHT,AREA] <LETTER 1> <LETTER 2> <WORD>"

# Normal usage

@test "test0 : Sans aucune entree, afficher aide" {
    skip
    run ./$prog
    [ "$status" -eq 0 ]
    [ "${lines[0]}" = "$help_first_line" ]
}

@test "test1 : Dessiner dyck ab" {
    skip
    run ./$prog < $tests_folder/test1
    [ "${lines[0]}" = "****/\/\****" ]
    [ "${lines[1]}" = "*/\/****\/\*" ]
}

@test "test2 : Dessiner dyck 01" {
    skip
    run ./$prog < $tests_folder/test2
    [ "${lines[0]}" = "****/\/\****" ]
    [ "${lines[1]}" = "*/\/****\/\*" ]
}

@test "test3 : mot non equilibre" {
    skip
    run ./$prog < $tests_folder/test3
    [ "${lines[0]}" = "mot non equilibre" ]
}

@test "test4 : mot trop long" {
    skip
    run ./$prog < $tests_folder/test4
    [ "${lines[0]}" = "mot trop long" ]
}

@test "test5 : mot non equilibre" {
    skip
    run ./$prog < $tests_folder/test5
    [ "${lines[0]}" = "mot non equilibre" ]
}

@test "test6 : lettre interdite" {
    skip
    run ./$prog < $tests_folder/test6
    [ "${lines[0]}" = "lettre interdite" ]
}

@test "test7 : parametre hauteur" {
    skip
    run ./$prog hauteur < $tests_folder/test7
    [ "$status" -eq 0 ]
    [ "$output" = "2" ]
}

@test "test8 : parametre aire" {
    skip
    run ./$prog aire < $tests_folder/test8
    [ "$status" -eq 0 ]
    [ "$output" = "12" ]
}

@test "test9 : argument invalide" {
    skip
    run ./$prog banane < $tests_folder/test9
    [ "${lines[0]}" = "argument invalide" ]
}

@test "test10 : donnees invalides" {
    skip
    run ./$prog < $tests_folder/test10
    [ "${lines[0]}" = "donnees invalides" ]
}
