divide() {
	if [ $2 -eq 0 ]; then echo division by 0; exit; fi
	local p=12  								# precision
	local c=${c:-0}								# precision counter	
	local d=.									# decimal seperator
	local r=$(($1/$2)); echo -n $r				#result of division
	local m=$(($r*$2))
	[ $c -eq 0 ] && [ $m -ne $1 ] && echo -n $d
	[ $1 -eq $m ] || [ $c -eq $p ] && return
	local e=$(($1-$m))
	c=$(($c+1))									#increment counter
	divide $(($e*10)) $2
}
