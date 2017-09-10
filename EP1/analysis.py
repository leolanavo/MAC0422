import statistics as stat
import math as th

def conf(sample):

    t = 2.045
    conf = []
    
    stdv = stat.stdev(sample)
    mean = stat.mean(sample)

    conf.append(mean - t*(stdv/th.sqrt(30)))
    conf.append(mean + t*(stdv/th.sqrt(30)))
    conf.append(stat.variance(sample))
    conf.append(stat.median(sample))

    return conf    


def main():

    size = [10, 25, 50]
    
    for s in size:
        
        for id in range (1, 4):
            analysis_fl = "analysis" + str(s) + "_" + str(id) + ".txt"
            file_output = open(analysis_fl, 'w')
            
            mean_deadline = []
            context = []
            
            for i in range (1, 31):    
                sum_mean = 0.0

                result_fl = "result" + str(s) + "_" + str(id) + "_"+ str(i) + ".txt"
                file_input = open(result_fl, 'r')

                for j in range (1, s + 1):
                    sum_mean = sum_mean + float(file_input.readline())
                
                num_context = int(file_input.readline()) 
                
                if sum_mean < 0:
                    sum_mean = -sum_mean

                mean_deadline.append(sum_mean/s)  
                context.append(num_context)

                file_input.close()

            fn_dead_m = stat.mean(mean_deadline)
            fn_ctx_m = stat.mean(context)

            file_output.write("DL mean: " + str(fn_dead_m) + " CTX mean: " + str(fn_ctx_m) + "\n")
            conf_i = conf(mean_deadline)
            file_output.write(" IC:" + "[" + str(conf_i[0]) + "; " + str(conf_i[1]) + "]" + "\n")
            file_output.write("Variance: " + str(conf_i[2]) + "Median: " + str(conf_i[3]))

            file_output.close()
main()
