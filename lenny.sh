#!/bin/bash
sup_son="( ͡° ͜ʖ ͡°)"
sup_sons=1
delay=${1:-0}


while [ $[($sup_sons + 1) * (1 + ${#sup_son})] -le $(tput cols) ]; do
        j=$[ ${#sup_son} - 1]
        m="" 
        while [ "$j" -ge 0 ]; do
                sleep $delay
                m="${sup_son:$j:1}$m"
                printf "$m\r" 
                j=$[j - 1]
        done

        j=0
        while [ "$j" -le $[$(tput cols) - (${#sup_son} + 1) * $sup_sons - $sup_sons] ]; do
                sleep $delay
                m=" $m"
                printf "$m\r"
                j=$[j + 1]
        done
        sup_sons=$[sup_sons + 1]
done

printf "\n\r"
