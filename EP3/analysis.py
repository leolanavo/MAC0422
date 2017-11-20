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

    analysis_fl = "analysis" + ".txt"
    file_output = open(analysis_fl, 'w')
            
    mean_deadline = []
    context = []
            
    for i in range (1, 31):    
        sum_mean = 0.0

        result_fl = "result" + "_" + str(i) + ".txt"
        file_input = open(result_fl, 'r')

        for j in range (1, 30):
            sum_mean = sum_mean + float(file_input.readline())
                
        num_context = int(file_input.readline()) 

        mean_deadline.append(sum_mean/30)  
        context.append(num_context)

        file_input.close()

    fn_dead_m = stat.mean(mean_deadline)
    fn_ctx_m = stat.mean(context)

    conf_i = conf(mean_deadline)
    conf_i_c = conf(context)

    file_output.write("Media de Tempo de Alocação: " + str(fn_dead_m) + "\n")
    file_output.write("IC:" + "[" + str(conf_i[0]) + "; " + str(conf_i[1]) + "]" + "\n")
    file_output.write("Variancia: " + str(conf_i[2]) + "; "+ "Mediana: " + str(conf_i[3]) + "\n")
            
    file_output.write("Media de Page Faults: " + str(fn_ctx_m) + "\n")
    file_output.write("IC:" + "[" + str(conf_i_c[0]) + "; " + str(conf_i_c[1]) + "]" + "\n")
    file_output.write("Variancia: " + str(conf_i_c[2]) + "; "+ "Mediana: " + str(conf_i_c[3]) + "\n")

    file_output.close()
main()
