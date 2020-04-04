trap 'clear; echo "mdrrr, genre tu croyais quoi ?"; sleep 5;' INT
while true; do
	COLOR1="\e[4$((( RANDOM % 7 ) + 1 ))m"
	COLOR2="\e[10$(((RANDOM % 6) + 0 ))m"
	NC="\e[0m" # No Color

	printf "${COLOR1}FERME${COLOR2} ta session :/${NC}"
#	COUNTER=0
#	while [  $COUNTER -lt $((( RANDOM % 20 ) + 1 )) ]; do
#		printf " "
#		let COUNTER=COUNTER+1
#	done;
	printf '\a'
	sleep 0.05
done
