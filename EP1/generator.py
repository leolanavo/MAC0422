import random as rd
import subprocess as sp

def main():

    size = [20, 50, 100]

    for s in size:
        for id in range (1, 4):
            for i in range (1, 31):
                trace_fl = "trace" + str(s) + "_" + str(i) + ".txt"
                result_fl = "result" + str(s) + "_" + str(id) + "_"+ str(i) + ".txt"
                print(trace_fl)

                file_input = open(trace_fl, 'w')
                file_output = open(result_fl, 'w')
                file_output.close()

                for i in range (1, s+1):
                    t0 = i + rd.uniform(i,i+1)
                    dt = rd.uniform(1, 30)
                    dead = t0 + dt + rd.uniform(1, 30)
        
                    file_input.write(str(round(t0,1)) + " " + str(round(dt,1)) + " " + str(round(dead,1)) + " p" + str(i) + "\n")

                file_input.close()

                sp.run(["./bin/ep1", str(id), trace_fl, result_fl])
main()
