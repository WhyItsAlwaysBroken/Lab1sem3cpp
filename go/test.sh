#!/bin/bash

EXE="./db"
DATA="file.data"

[ -f "$DATA" ] && rm "$DATA"

run() {
    echo ""
    echo "> $EXE --file $DATA --query \"$1\""
    $EXE --file "$DATA" --query "$1"
}

showfile() {
    echo ""
    echo "--- content of $DATA ---"
    if [ -f "$DATA" ]; then
        cat "$DATA"
    fi
    echo ""
}

echo "================ ARRAY ================"
run "MPUSH myarr 1"
run "MPUSH myarr 2"
run "MPUSH myarr 3"
run "MPUSH myarr 4"
run "MLEN myarr"
run "MINS myarr 1 15"
run "MGET myarr 1"
run "MSET myarr 1 25"
run "MDEL myarr 1"
run "MGET myarr 10"
run "MDEL myarr 10"
run "PRINT myarr"
showfile

echo "================ STACK ================"
run "SPUSH mystack 1"
run "SPUSH mystack 2"
run "SPUSH mystack 3"
run "SGET mystack"
run "STOP mystack"
run "SPOP mystack"
run "SPOP mystack"
run "SPOP mystack"
run "SPOP mystack"
run "SGET mystack"
run "SPUSH mystack 10"
run "SPUSH mystack 20"
run "PRINT mystack"
showfile

echo "================ QUEUE ================"
run "QPUSH myqueue 10"
run "QPUSH myqueue 20"
run "QPUSH myqueue 30"
run "QGET myqueue"
run "QFRONT myqueue"
run "QREAR myqueue"
run "QPOP myqueue"
run "QPOP myqueue"
run "QPOP myqueue"
run "QPOP myqueue"
run "QGET myqueue"
run "QPUSH myqueue 40"
run "PRINT myqueue"
showfile

echo "============ SINGLE LINKED LIST ============"
run "FPUSH mylist 1"
run "FPUSH mylist 2"
run "FPUSH mylist 3"
run "FPUSH mylist 4"
run "FGET mylist"
run "FPUSHFRONT mylist 0"
run "FGET mylist"
run "FINSBEFORE mylist 2 5"
run "FINSAFTER mylist 3 6"
run "FGET mylist"
run "FGETREC mylist"
run "FFIND mylist 6"
run "FFIND mylist 99"
run "FDEL mylist 6"
run "FGET mylist"
run "FDELFRONT mylist"
run "FDELBACK mylist"
run "FGET mylist"
run "FDELBEFORE mylist 5"
run "FDELAFTER mylist 2"
run "FGET mylist"
run "FDEL mylist 99"
run "PRINT mylist"
showfile

echo "============ DOUBLE LINKED LIST ============"
run "LPUSH mydlist 1"
run "LPUSH mydlist 2"
run "LPUSH mydlist 3"
run "LPUSH mydlist 4"
run "LGET mydlist"
run "LPUSHFRONT mydlist 0"
run "LGET mydlist"
run "LINSBEFORE mydlist 2 5"
run "LINSAFTER mydlist 3 6"
run "LGET mydlist"
run "LGETBACK mydlist"
run "LFIND mydlist 6"
run "LFIND mydlist 99"
run "LDEL mydlist 6"
run "LGET mydlist"
run "LDELFRONT mydlist"
run "LDELBACK mydlist"
run "LGET mydlist"
run "LDELBEFORE mydlist 5"
run "LDELAFTER mydlist 2"
run "LGET mydlist"
run "LGETBACK mydlist"
run "PRINT mydlist"
showfile

echo "================ ERRORS ================"
run "XYZ mystack 1"
run "SPUSH mystack"
run "SPUSH"

echo "================ FINAL FILE ================"
showfile

exit 0
