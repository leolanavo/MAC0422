import statistics as stat
import math as th

def conf (sample):

    t = 2.045
    conf = []
    
    stdv = stat.stdev(sample)
    mean = stat.mean(sample)

    conf.append(mean - t*(stdv/th.sqrt(30)))
    conf.append(mean + t*(stdv/th.sqrt(30)))
    conf.append(stat.variance(sample))
    conf.append(stat.median(sample))

    return conf    


def memory ():
    
    analysis_fl = "analysis" + "_" + "500" + "_" + "5" + "_" + "20" + ".txt"
    file_output = open(analysis_fl, 'w')
                      
    result_fl = "mem" + "_" + "500" + "_" + "5" + "_"+ "20" + ".txt"
    file_input = open(result_fl, 'r')

    heap = []
    peak = []
    stack = []

    for j in range (1, 31):
        heap.append(int(file_input.readline()))
        peak.append(int(file_input.readline()))
        stack.append(int(file_input.readline()))
        control = str(file_input.readline())

    file_input.close()

    heap_mean = stat.mean(heap)
    peak_mean = stat.mean(peak)
    stack_mean = stat.mean(stack)

    conf_i_heap = conf(heap)
    conf_i_peak = conf(peak)
    conf_i_stack = conf(stack)


    file_output.write("Media do Uso Total(bytes): " + str(heap_mean) + "\n")
    file_output.write("IC:" + "[" + str(conf_i_heap[0]) + "; " + str(conf_i_heap[1]) + "]" + "\n")
    file_output.write("Variancia: " + str(conf_i_heap[2]) + "; "+ "Mediana: " + str(conf_i_heap[3]) + "\n")
            
    file_output.write("Media do Pico de Alocação(bytes): " + str(peak_mean) + "\n")
    file_output.write("IC:" + "[" + str(conf_i_peak[0]) + "; " + str(conf_i_peak[1]) + "]" + "\n")
    file_output.write("Variancia: " + str(conf_i_peak[2]) + "; "+ "Mediana: " + str(conf_i_peak[3]) + "\n")

    file_output.write("Média do Pico da Pilha de Execução(bytes): " + str(stack_mean) + "\n")
    file_output.write("IC:" + "[" + str(conf_i_stack[0]) + "; " + str(conf_i_stack[1]) + "]" + "\n")
    file_output.write("Variancia: " + str(conf_i_stack[2]) + "; "+ "Mediana: " + str(conf_i_stack[3]) + "\n")

    file_output.close()

def time ():
    
    analysis_fl = "time_analysis" + "_" + "250" + "_" + "100" + "_" + "20" + ".txt"
    file_output = open(analysis_fl, 'w')
                      
    result_fl = "time" + "_" + "250" + "_" + "100" + "_"+ "20" + ".txt"
    file_input = open(result_fl, 'r')

    time = []

    for j in range (1, 31):
        time.append((60 * float(file_input.readline())) + float(file_input.readline()))
        control = str(file_input.readline())

    file_input.close()

    time_mean = stat.mean(time)
    conf_i_time = conf(time)

    file_output.write("Média de Tempo de Execução(seg): " + str(time_mean) + "\n")
    file_output.write("IC:" + "[" + str(conf_i_time[0]) + "; " + str(conf_i_time[1]) + "]" + "\n")
    file_output.write("Variancia: " + str(conf_i_time[2]) + "; "+ "Mediana: " + str(conf_i_time[3]) + "\n")

    file_output.close()

def main ():
    time()
    memory()

main()
