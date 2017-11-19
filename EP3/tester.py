import random as rd
import subprocess as sp
import os

def main():

    trace_fl = "trace" + "_" + ".txt"
    result_fl = "result" + "_" + ".txt"

    file_output = open(result_fl, 'w')
    file_output.close()

    file_input = open(trace_fl, 'w')
    file_input.write("50 " + "200 " + "5" + " 10" + "\n")


    for i in range (1, 50, 1):
        t0 = i + rd.uniform(i,i+1)
        tf = 
        b = 
        nome = "p" + str(i)
                		
        file_input.write(str(round(t0,1)) + " " + str(round(dt,1)) + " " + str(round(dead,1)) + " p" + str(i) + "\n")

    file_input.close()

    sp.run(["./bin/ep3", str(id), trace_fl, result_fl])
main()
