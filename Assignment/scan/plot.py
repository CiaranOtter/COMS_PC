import matplotlib.pyplot as plt

if __name__ == '__main__':

    filepath = 'outputs.txt' 
    names = ["basline-sequential scan", "openMP scan", "MPI scan"] 
    i = 8;
    x = [];
    while (i < 17000000):
        x.append(i);
        i = i * 2;
     # this is the range of input sizes tested
    with open(filepath, 'r') as file:
        for i, line in enumerate(file):
            y = list(map(float, line.split(',')))
            plt.plot(x, y, label=names[i])

    plt.xlabel('Input size')
    plt.ylabel('Time taken')
    plt.title('Comparison of time taken for Scan for input of size n')
    plt.legend()
    plt.savefig('scan_plot.pdf')
    plt.show()