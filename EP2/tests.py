import os
import subprocess as sb

def main():
    ncycli = [5, 25, 50]
    nlaps =  [20, 80, 160]
    nleng =  [250, 350, 500]

    for i in nclycli:
        for j in nlaps:
            for k in nleng:
                for a in range(1, 30):
                    sb.run(["memusage", "./bin/ep2", str(k), str(i), str(j)])
                    sb.run(["time", "./bin/ep2", str(k), str(i), str(j)])

main()
