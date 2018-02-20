#!/bin/bash

# This is an entirely bash script based tic-tac-toe game.
# I wrote it just to see if something like this could be
# done purely using Bash. Maybe I'll add some additional
# features later, but for now it is in it's simplest working
# form. Please enjoy, especially the graphics :)

moves_count=0
select='1 2 3 4 5 6 7 8 9 quit'

reset_game () {
	pos1=1
	pos2=2
	pos3=3
	pos4=4
	pos5=5
	pos6=6
	pos7=7
	pos8=8
	pos9=9
}

set_position () {
	if [ $( expr $moves_count % 2 ) -eq 0 ]
	then
		case $1 in
			1)	pos1=X ;;
			2)	pos2=X ;;
			3)	pos3=X ;;
			4)	pos4=X ;;
			5)	pos5=X ;;
			6)	pos6=X ;;
			7)	pos7=X ;;
			8)	pos8=X ;;
			9)	pos9=X ;;
		esac

	else
		case $1 in
			1)	pos1=O ;;
			2)	pos2=O ;;
			3)	pos3=O ;;
			4)	pos4=O ;;
			5)	pos5=O ;;
			6)	pos6=O ;;
			7)	pos7=O ;;
			8)	pos8=O ;;
			9)	pos9=O ;;
		esac
	fi
}

draw_grid () {
	echo -e "$pos1\t$pos2\t$pos3"
	echo " "
	echo -e "$pos4\t$pos5\t$pos6"
	echo " "
	echo -e "$pos7\t$pos8\t$pos9"
	echo " "
}

init_game () {
	reset_game
	clear
	draw_grid
}

check_nums () {
	if [ $1 == $2 ] && [ $2 == $3 ]
	then
		return 0
	else
		return 1
	fi
}

check_for_matches () {
	if $(check_nums $pos1 $pos2 $pos3) || \
	$(check_nums $pos4 $pos5 $pos6) || \
	$(check_nums $pos7 $pos8 $pos9) || \
	$(check_nums $pos1 $pos4 $pos7) || \
	$(check_nums $pos2 $pos5 $pos8) || \
	$(check_nums $pos3 $pos6 $pos9) || \
	$(check_nums $pos1 $pos5 $pos9) || \
	$(check_nums $pos3 $pos5 $pos7)
	then
		return 0
	else
		return 1
	fi
}

print_win_message () {
	if [ $( expr $moves_count % 2 ) -eq 0 ]
	then
		echo "O wins!"
	else
		echo "X wins!"
	fi
	echo "The game took $moves_count moves and $SECONDS seconds to finish."
}

progress_game () {
	clear
	draw_grid
	check_for_matches
	if [ $? -eq 0 ]
	then
		print_win_message
		exit
	fi
}

init_game

PS3='Select [1-9] to move or 10 to quit: '

select sel in $select
do
	case $sel in
		1)
			if [ $pos1 != 1  ]
			then
				echo "Position already set!"
				continue
			else
				set_position 1
				let moves_count++
			fi

			progress_game	;;

		2)
			if [ $pos2 != 2  ]
			then
				echo "Position already set!"
				continue
			else
				set_position 2
				let moves_count++

			fi
			
			progress_game	;;
		3)
			if [ $pos3 != 3  ]
			then
				echo "Position already set!"
				continue
			else
				set_position 3
				let moves_count++

			fi
			
			progress_game	;;

		4)
			if [ $pos4 != 4  ]
			then
				echo "Position already set!"
				continue
			else
				set_position 4
				let moves_count++

			fi
			
			progress_game	;;

		5)
			if [ $pos5 != 5  ]
			then
				echo "Position already set!"
				continue
			else
				set_position 5
				let moves_count++

			fi
			
			progress_game	;;

		6)
			if [ $pos6 != 6  ]
			then
				echo "Position already set!"
				continue
			else
				set_position 6
				let moves_count++

			fi
			
			progress_game	;;

		7)
			if [ $pos7 != 7  ]
			then
				echo "Position already set!"
				continue
			else
				set_position 7
				let moves_count++

			fi
			
			progress_game	;;

		8)
			if [ $pos8 != 8  ]
			then
				echo "Position already set!"
				continue
			else
				set_position 8
				let moves_count++

			fi
			
			progress_game	;;

		9)
			if [ $pos9 != 9  ]
			then
				echo "Position already set!"
				continue
			else
				set_position 9
				let moves_count++

			fi
			
			progress_game	;;

		quit)
			echo "Bye!"
			break
			;;
		*)
			echo "Invalid input"
			;;
	esac
	
done
		
