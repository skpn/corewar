# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_script_vm.sh                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/21 11:31:03 by sikpenou          #+#    #+#              #
#    Updated: 2020/04/24 23:59:24 by skpn             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## ERROR_MESSAGES
usage_msg="sh fight [options] path_to_champs/champs\n"
usage_msg="$usage_msg options:\n"
usage_msg="$usage_msg -mac  	: use mac-compatible executables\n"
usage_msg="$usage_msg -s		: do not print Aff output\n"
usage_msg="$usage_msg -d N		: dump at cycle N\n"
usage_msg="$usage_msg -v N		: verbose (Zaz-like) level N, default is 31\n"
usage_msg="$usage_msg -time N	: timeout after N seconds, default is 60\n"
usage_msg="$usage_msg -nb N		: number of champs per fight ( >= 1 )\n"
usage_msg="$usage_msg -max N	: max number of fights ( >= 1 )\n"
usage_msg="$usage_msg -rand		: fighters are selected randomly\n"

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

## GET INPUT FOLDERS

output_dir=/tmp
parent_dir=.
exec_dir=$parent_dir
exec=$exec_dir/vm
ref_dir=$parent_dir/resources
ref_exec_asm=$ref_dir/asm_ref_linux
ref_exec_vm=$ref_dir/vm_ref_linux

if [ ! -d $ref_dir ] || [ ! -f $ref_exec_asm ] || [ ! -f $ref_exec_vm ]; then
	echo -e "Wrong path: this script must be launched from the repository's root folder\n"\
		"If you did, please check script lines 35-37."
	exit
fi


## SET DEFAULTS
dump=-1
verbose=31
aff=1
nb_fighters=4
max_fight=0
time_limit=60
random=0


## CHECK COMPILATION

make -C $parent_dir &> $output_dir/check_make

if grep -q -e "Error" -e "error" $output_dir/check_make; then
	cat $output_dir/check_make
	exit
fi

command -v timeout > $output_dir/check_timeout
if [ -s $output_dir/check_timeout ]; then
	time_cmd="timeout"
else
	command -v gtimeout > $output_dir/check_timeout
	if [ -s $output_dir/check_timeout ]; then
		time_cmd="gtimeout"
	else
		echo "missing timeout/gtimeout command"
		echo "for macs  : coreutils package missing, download command: brew install coreutils"
		echo "for linux : I don't know, it should be there... timeout deactivated, some fights can be very long"
		time_limit=""
	fi
fi

rm -rf $output_dir/check_* > /dev/null


## PARSE ARGS

if [ "$#" -lt 1 ]; then
	echo No arguments given
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
	if [ $arg == "-v" ]; then
		verbose=${args[$(($idx+1))]}
		idx=$(($idx+1))
##
	elif [ $arg == "-d" ]; then
		dump=${args[$(($idx+1))]}
		idx=$(($idx+1))
		if [ $dump < 0 ]; then
			echo bad dump option: $dump
			echo -e $usage_msg
			exit
		fi
##
	elif [ $arg == "-nb" ]; then
		nb_fighters=${args[$(($idx+1))]}
		idx=$(($idx+1))
		if [ $nb_fighters -lt 1 ]; then
			echo bad nb option: $nb_fighters
			echo -e $usage_msg
			exit
		fi
##
	elif [ $arg == "-max" ]; then
		max_fight=${args[$(($idx+1))]}
		idx=$(($idx+1))
##
	elif [ $arg == "-mac" ]; then
		ref_exec_asm=${ref_exec_asm/linux/mac}
		ref_exec_vm=${ref_exec_vm/linux/mac}
##
	elif [ $arg == "-time" ]; then
		time_limit=${args[$(($idx+1))]}
		idx=$(($idx+1))
##
	elif [ $arg == "-s" ]; then
		aff=0
##
	elif [ $arg == "-rand" ]; then
		random=1
##
	elif [ ! -f $arg ]; then
		echo "File '"$arg"'" not found
##
	elif [ ${arg: -2} == ".s" ]; then
		s_champs+=($arg)
##
	elif [ ${arg: -4} == ".cor" ]; then
		cor_champs+=($arg)
##
	else
		echo bad arg: $arg
		echo -e $usage_msg
		exit
##
	fi
##
	idx=$(($idx + 1))
##
done


## COMPILE CHAMPS

idx=0

while [ $idx -lt ${#s_champs[@]} ]
do
##
	arg=${s_champs[$idx]}
##
	$ref_exec_asm $arg > $output_dir/check_asm
##
	if ! grep -q "Writing" $output_dir/check_asm; then
		echo "champ "$arg" is invalid"
		cat $output_dir/check_asm
	else
		cor_file=${arg/\.s/\.cor}
		mv $cor_file $parent_dir/checker/champ/cor_files
		cor_file=$(basename $cor_file)
		cor_file="$parent_dir/checker/champ/cor_files/$cor_file"
		cor_champs+=($cor_file)
	fi
##
	idx=$(($idx + 1))
##
done

if [ ${#cor_champs[@]} -lt 1 ]; then
	echo "no valid champion"
	exit
elif [ ${#cor_champs[@]} -lt $nb_fighters ]; then
	echo "Not enough valid champs to use $nb_fighters fighters per fight."
	nb_fighters=${#cor_champs[@]}
fi

rm -rf $output_dir/check_*


######## LAUNCH FIGHTS #########

idx=0
current_fight=0
nb_cor_champs=${#cor_champs[@]}
ordered_launch=0

if [ $max_fight -eq 0 ]; then
	max_fight=$(($nb_cor_champs / $nb_fighters))
fi

rm -f $output_dir/failed > /dev/null

while [ $current_fight -lt $max_fight ]
do
	current_fight=$(($current_fight + 1))
	fight_dir=$output_dir/fight_$current_fight
	mkdir -p $fight_dir
	rm -rf $fight_dir/*

## GET FIGHTERS
	fighters=()
	current_fighter=0
	while [ $current_fighter -lt $nb_fighters ]
	do
		if [ $random -eq 0 ]; then
			fighters+=${cor_champs[$idx]}
		else
			fighters+=${cor_champs[$(($RANDOM % $nb_cor_champs))]}
		fi
		fighters+=" "
		idx=$(($idx + 1))
		if [ $idx -eq $nb_cor_champs ]; then
			idx=$((0 + $ordered_launch))
			ordered_launch=$(($ordered_launch + 1))
		fi
		current_fighter=$(($current_fighter + 1))
	done
	echo -ne "\nfight [$current_fight / $max_fight]\n$(basename -a ${fighters[@]}) -> "

## GET ARGS
	vm_args=""
	if [ $aff == 1 ]; then
		vm_args="${vm_args}-a "
	fi
	if [ $dump -gt 0 ]; then
		vm_args="${vm_args}-d $dump "
	fi
	if [ $verbose -gt 0 ]; then
		vm_args="${vm_args}-v $verbose "
	fi
	vm_args="${vm_args}${fighters[@]}"


## GET OUTPUT
	timedout=0
	$time_cmd $time_limit $ref_exec_vm $vm_args > $fight_dir/ref
	if [ -z $time_cmd -a $? == 124 ]; then
		echo "reference exec timed out"
		timedout=1
	fi
	$time_cmd $time_limit $exec $vm_args > $fight_dir/exec
	if [ -z $time_cmd -a $? == 124 ]; then
		echo "vm exec timed out"
		timedout=1
	fi

## GET DIFF
	lines_ref=$(wc -l < $fight_dir/ref)
	lines_exec=$(wc -l < $fight_dir/exec)
	if [[ $line_ref == 0 ]]; then
		exit
	elif [[ $line_exec == 0 ]]; then
		echo $RED "empty output for exec" $NC
		exit
	fi
	if [ $lines_ref -lt $lines_exec ]; then
		lines_diff=$lines_ref
	else
		lines_diff=$lines_exec
	fi
	head -n $lines_diff $fight_dir/exec > $fight_dir/exec
	head -n $lines_diff $fight_dir/ref > $fight_dir/ref
	diff $fight_dir/exec $fight_dir/ref > $fight_dir/diff


## DISPLAY RESULTS
	if [ -s $fight_dir/diff ]; then
		echo -e $RED"ERROR"$NC
		echo " - fight $current_fight: " ${fighters[@]} >> $output_dir/failed
	else
		echo -e $GREEN"OK"$NC
	fi

##
done


######## DISPLAY FAILED TESTS #########

if [ -s $output_dir/failed ]; then
	echo failed:
	cat $fight_dir/failed
fi


######## CLEAN OUTPUT #########

rm -rf $output_dir/fight_* > /dev/null
