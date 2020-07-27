# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_script_asm.sh                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/10 22:48:52 by skpn              #+#    #+#              #
#    Updated: 2020/04/22 11:39:24 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


## ERROR MESSAGES

usage_msg="bash script_asm [options] path/to/file[s].s\n"
usage_msg+="options:\n"
usage_msg+="\t-mac     : use mac-compatible reference executable\n"
usage_msg+="\t-show_out: show what the exec prints to stdout\n"
usage_msg+="\t-show_err: show diff on error\n"

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'


## SET FOLDERS

output_dir=/tmp
parent_dir=.
exec_dir=$parent_dir
exec=$exec_dir/asm
ref_dir_cor=$parent_dir/checker/champ/cor_files
ref_exec=$parent_dir/resources/asm_ref_linux

if [ ! -d $ref_dir_cor ] || [ ! -f $ref_exec ]; then
	echo -e "Wrong path: this script must be launched from the repository's root folder.\n"\
		"If you did, please check script lines 33-34."
	exit
fi


## CHECK COMPILATION

make -C $exec_dir &> $output_dir/check_make

if grep -q -e "Error" -e "error" $output_dir/check_make; then
	cat $output_dir/check_make
	exit
else
	rm -rf $output_dir/check_make
fi


## PARSE ARGS

if [ "$#" -lt 2 ]; then
	echo -e $usage_msg
	exit 1
fi

args=("$@")
idx=0

while [ $idx -lt "$#" ]
do
##
	arg=${args[$idx]}
##
	if [ $arg == "-show_err" ]; then
		show_err=1
		echo show err: $show_err
##
	elif [ $arg == "-show_out" ]; then
		show_out=1
##
	elif [ $arg == "-mac" ]; then
		ref_exec=${ref_exec/linux/mac}
##
	elif [ ! -f $arg ]; then
		echo "File '"$arg"'" not found
		exit 1
##
	elif [ ${arg: -2} != ".s" ]; then
		echo bad file extension: $arg
##
	elif [ ${#arg} -lt 3 ]; then
		echo file name too short: $(arg $s_file)
##
	else
		s_files_array+=($arg)
##
	fi
##
	idx=$(($idx + 1))
##
done


## SET EXECS

if [ ! -d $parent_dir ] || [ ! -d $ref_dir_cor ] || [ ! -d $exec_dir ]; then
	echo "Wrong path, please check script lines 18-23"
	exit
fi


## LAUNCH CHECKS

rm -f $output_dir/failed_tests > /dev/null

current_check=0
max_check=${#s_files_array[@]}
if [ $max_check -lt 1 ]; then
	echo no valid test files
	exit
fi
score=0
echo "failed tests:" > $output_dir/failed_tests
failed_nb=0

while [ $current_check -lt $max_check ]
do
	s_file=${s_files_array[$current_check]}
	current_check=$(($current_check + 1))

## GET NAMES
	shortname=$(basename $s_file)
	shortname=${shortname%.*}
	cor_file="$shortname.cor"
	echo -ne "\n[$current_check / $max_check]: $shortname - "

## GET CURRENT FOLDERS
	ref_dir_s=${s_file%/*}
	check_dir=$output_dir/$shortname
	mkdir -p $check_dir
	rm -rf $check_dir/* &> /dev/null

## GET COR FILES
	$exec $s_file &> $check_dir/test_exec
	if grep -q -e "SEGV" -e "leak" $check_dir/test_exec; then
		cat $output_dir/test_exec
		exit
	fi
	mv $ref_dir_s/$cor_file $check_dir/test_cor
	$ref_exec $s_file &> $check_dir/ref_exec
	mv $ref_dir_s/$cor_file $check_dir/ref_cor

## GET HEXDUMPS
	hexdump $check_dir/test_cor > $check_dir/test_hex
	hexdump $check_dir/ref_cor > $check_dir/ref_hex

## CHECK RESULTS
	diff $check_dir/test_hex $check_dir/ref_hex > $check_dir/diff
	if [ -s $check_dir/diff ]; then
		echo -e $RED"ERROR"$NC
		echo " - " $s_file >> $output_dir/failed_tests
		failed_nb=$(($failed_nb + 1))
		if [ ! -z $show_err ]; then
			vim -O $check_dir/test_hex $check_dir/ref_hex $check_dir/diff
			if [ $current_check -lt $max_check ]; then
				read -p "Press y to continue: " answer
				if [ $answer != 'y' ]; then
					exit
				fi
			fi
		fi
	else
		echo -e $GREEN"OK"$NC
		score=$(($score + 1))
	fi
	if [ ! -z $show_out ]; then
		cat $check_dir/test_exec
	fi
	echo -e "\n"
##
done

echo final score: [ $score / $max_check ]
if [ $failed_nb -gt 0 ]; then
	echo -ne $failed_nb " "
	cat $output_dir/failed_tests
fi
