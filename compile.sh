#!/bin/bash

log_message() {
    local message=$1
    echo "  >Log: $message" >&2
}

handle_empty_conf() {
    local id=$1
    local conf=$2

    if [ -z "$conf" ]; then
        log_message "<$id> -> NotFoundLine"
        case $id in
            3)
                log_message "<$id> -> Renamed to 'myApp'"
                conf="myApp"
            ;;
            4)
                log_message "<$id> -> Renamed to 'main.cpp'"
                conf="main.cpp"
            ;;
        esac
    fi

    log_message "CurrentLine<$id> ~ $conf"
    echo "$conf"
}

split_string_to_array() {
    local string=$1
    local -n array=$2
    IFS=' ' read -r -a array <<< "$string"
}

compile() {
    local include_paths=("${!1}")
    local libs_paths=("${!2}")
    local libs=("${!3}")
    local output_file=$4
    local main_file=$5

    echo "Compiling. Please wait..."
    log_message "Compile line ~ g++ ${include_paths[*]} -o $output_file $main_file ${libs_paths[*]} ${libs[*]}"
    g++ "${include_paths[@]}" -o "$output_file" "$main_file" "${libs_paths[@]}" "${libs[@]}"
}

compile_from_conf() {
    echo "Reading conf file..."

    if [[ ! -f .cconf ]]; then
        echo "Configuration file .cconf not found!"
        exit 1
    fi

    mapfile -t cclines < .cconf

    for i in "${!cclines[@]}"; do
        cclines[$i]=$(handle_empty_conf "$i" "${cclines[$i]}")
    done

    split_string_to_array "${cclines[0]}" include_paths
    split_string_to_array "${cclines[1]}" libs_paths
    split_string_to_array "${cclines[2]}" libs

    compile include_paths[@] libs_paths[@] libs[@] "${cclines[3]}" "${cclines[4]}"
}

compile_from_input() {
    echo -n "Write includes path: "
    read iP
    iP=$(handle_empty_conf 0 "$iP")

    echo -n "Write libs path: "
    read lP
    lP=$(handle_empty_conf 1 "$lP")

    echo -n "Write usage libs: "
    read uL
    uL=$(handle_empty_conf 2 "$uL")

    echo -n "Write program name: "
    read pN
    pN=$(handle_empty_conf 3 "$pN")

    echo -n "Write main file path: "
    read mP
    mP=$(handle_empty_conf 4 "$mP")

    split_string_to_array "$iP" include_paths
    split_string_to_array "$lP" libs_paths
    split_string_to_array "$uL" libs

    compile include_paths[@] libs_paths[@] libs[@] "$pN" "$mP"
}

if [ $# -eq 1 ]; then
    case $1 in
        "-f")
            compile_from_conf
        ;;
        "-r")
            compile_from_input
        ;;
        *)
            echo "Unknown command: $1"
            exit 1
        ;;
    esac
else
    echo -n "scf ~ "
    read command
    case $command in
        "-f")
            compile_from_conf
        ;;
        "-r")
            compile_from_input
        ;;
        *)
            echo "Unknown command: $command"
            exit 1
        ;;
    esac
fi

if [ $? -eq 0 ]; then
    echo "Compilation successful."
    clear
else
    echo "Compilation failed."
fi