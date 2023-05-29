import numpy as np

# Names of files to read
files = ['berlin52.tsp', 'br17.atsp', 'ch130.tsp', 'ftv70.atsp']

# Best results for each file
best_results = [7542, 39, 6110, 1950]

# Read files
open('analysis.txt', 'w')
for file in files:
    
    # Read results from csv file
    results = np.genfromtxt(f'results.{file}.csv', delimiter=',', skip_header=1)

    # Get the best result
    best_result = np.min(results[:, 0])

    # Get the worst result
    worst_result = np.max(results[:, 0])

    # Get the average result
    average_result = np.mean(results[:, 0])

    # Get the standard deviation
    standard_deviation = np.std(results[:, 0])

    # Write results to file
    with open('analysis.txt', 'a') as f:
        f.write(f'File: {file}\n')
        f.write(f'Best result: {best_result:.2f}\n')
        f.write(f'Worst result: {worst_result:.2f}\n')
        f.write(f'Average result: {average_result:.2f}\n')
        f.write(f'Standard deviation: {standard_deviation:.2f}\n')
        f.write(f'Best result from literature: {best_results[files.index(file)]}\n')
        f.write(f'Relative error: {((best_result - best_results[files.index(file)]) / best_results[files.index(file)]):.2f}\n')
        f.write('\n')