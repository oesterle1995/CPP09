#!/bin/bash

EXEC="./a.out"

if [ ! -f "$EXEC" ]; then
    echo "Erreur : l'exécutable $EXEC n'existe pas."
    exit 1
fi

TEST_SIZES=(0 1 2 3 4 5 6 7 100 1000 3000 100000)
NB_TESTS=100

GREEN="\033[32m"
RED="\033[31m"
RESET="\033[0m"

echo -e "=== Début de la suite de tests (100 tests par catégorie) ===\n"

# --- PARTIE 1 : TESTS DE TRI DE TABLEAUX ---
for size in "${TEST_SIZES[@]}"; do
    echo -n "Taille $size ($NB_TESTS tests) : "
    
    FIRST_OUTPUT=""
    
    for i in $(seq 1 $NB_TESTS); do
        if [ $size -eq 0 ]; then
            ARG=""
        else
            ARG=$(shuf -i 1-2000000 -n $size | tr '\n' ' ')
        fi

        OUTPUT=$($EXEC $ARG 2>&1 | tr -d '\r')
        EXIT_CODE=$?

        # 1. Cas spécifique : Taille 0 (doit renvoyer strictement "Error")
        if [ $size -eq 0 ]; then
            CLEAN_OUT=$(echo "$OUTPUT" | tr -d '\n')
            if [ "$CLEAN_OUT" != "Error" ]; then
                echo -e "${RED}[FAIL]${RESET}"
                echo -e "${RED}  -> Échec au test $i (Taille 0) !${RESET}"
                echo "  - Argument : (aucun)"
                echo "  - Sortie   : \"$CLEAN_OUT\" (Attendu: \"Error\")"
                exit 1
            fi
        # 2. Cas standard (taille > 0)
        else
            if [ $EXIT_CODE -ne 0 ] || ! echo "$OUTPUT" | grep -q "\[OK\]"; then
                echo -e "${RED}[FAIL]${RESET}"
                echo -e "${RED}  -> Échec au test $i (Taille $size) !${RESET}"
                echo "  - Argument : \"$ARG\""
                echo "  - Sortie   : \"$OUTPUT\""
                exit 1
            fi

            # Stockage de la première sortie pour comparer l'identité absolue avec les suivantes
            if [ $i -eq 1 ]; then
                FIRST_OUTPUT="$OUTPUT"
            else
                if [ "$OUTPUT" != "$FIRST_OUTPUT" ]; then
                    echo -e "${RED}[FAIL OUTPUT INCONSISTENT]${RESET}"
                    echo -e "${RED}  -> La sortie du test $i diffère du premier test pour la taille $size !${RESET}"
                    echo "  - Sortie référence (Test 1) : \"$FIRST_OUTPUT\""
                    echo "  - Sortie actuelle  (Test $i) : \"$OUTPUT\""
                    exit 1
                fi
            fi
        fi
    done

    if [ $size -gt 0 ]; then
        echo -e "${GREEN}[OK groupé]${RESET} (Sortie identique : $(echo "$FIRST_OUTPUT" | tr '\n' ' '))"
    else
        echo -e "${GREEN}[OK groupé]${RESET} (Sortie : Error)"
    fi
done

# --- PARTIE 2 : FUZZING TEXTE / CHIFFRES CORROMPUS ---
echo -n "Fuzzing texte random ($NB_TESTS tests) : "

for i in $(seq 1 $NB_TESTS); do
    N=$((RANDOM % 1000))
    TYPE=$((RANDOM % 5))

    case $TYPE in
        0) PREFIX=$(tr -dc 'a-zA-Z!@#$%^&*' < /dev/urandom | head -c $((1 + RANDOM % 4)))
           RANDOM_ARG="${PREFIX}${N}" ;;
        1) SUFFIX=$(tr -dc 'a-zA-Z!@#$%^&*' < /dev/urandom | head -c $((1 + RANDOM % 4)))
           RANDOM_ARG="${N}${SUFFIX}" ;;
        2) SEP=$([ $((RANDOM % 2)) -eq 0 ] && echo "." || echo ",")
           DEC=$((RANDOM % 99))
           RANDOM_ARG="${N}${SEP}${DEC}" ;;
        3) TXT=$(tr -dc 'a-zA-Z,' < /dev/urandom | head -c $((1 + RANDOM % 3)))
           RANDOM_ARG="12 ${N}${TXT} 84" ;;
        4) RANDOM_ARG=$(tr -dc 'a-zA-Z0-9!@#$%^&*()_+-=[]{}|;:,.<>?/' < /dev/urandom | head -c $((5 + RANDOM % 30))) ;;
    esac
    
    OUTPUT=$($EXEC "$RANDOM_ARG" 2>&1 | tr -d '\r\n')

    if [ "$OUTPUT" != "Error" ]; then
        echo -e "${RED}[FAIL]${RESET}"
        echo -e "${RED}  -> Échec du fuzzing au test $i !${RESET}"
        echo "  - Argument : \"$RANDOM_ARG\""
        echo "  - Sortie   : \"$OUTPUT\" (Attendu: \"Error\")"
        exit 1
    fi
done

echo -e "${GREEN}[OK groupé]${RESET} (Sortie : Error)"

echo -e "\n${GREEN}=====================================================${RESET}"
echo -e "${GREEN} SUCCESS: TOUS LES TESTS SONT VALIDES ET IDENTIQUES ! ${RESET}"
echo -e "${GREEN}=====================================================${RESET}"