import matplotlib.pyplot as plt

def read_data(file_path):
    with open(file_path, 'r') as file:
        data = [float(line.strip()) for line in file.readlines()]
    return data

def plot_data(data1, data2):
    plt.figure(figsize=(10, 6))
    plt.plot(data1, 'b-', label='Raw Data')
    plt.plot(data2, 'r-', label='Filtered Data')
    # plt.title('Comparison of Two Datasets')
    plt.xlabel('Time')
    plt.ylabel('Altitude')
    plt.legend()
    plt.grid(True)
    plt.show()

# Replace 'path_to_file1.txt' and 'path_to_file2.txt' with the actual paths to your files
data1 = read_data('output.txt')
data2 = read_data('filtered.txt')

plot_data(data1, data2)
