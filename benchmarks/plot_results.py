import pandas as pd
import matplotlib.pyplot as plt
import os

# Set the path to your CSV file
csv_path = 'benchmarks/nqueens_results.csv'

if not os.path.exists(csv_path):
    print(f"Error: {csv_path} not found! Run the benchmark.sh script first.")
    exit()

# Load the data
df = pd.read_csv(csv_path)

# Create the plot
plt.figure(figsize=(10, 6))

# Plot each solver separately
for solver in df['solver'].unique():
    solver_data = df[df['solver'] == solver]
    plt.plot(solver_data['n'], solver_data['time_seconds'], marker='o', label=solver)

# Formatting the chart
plt.title('N-Queens Solver Performance Comparison', fontsize=14)
plt.xlabel('Board Size (N)', fontsize=12)
plt.ylabel('Execution Time (seconds)', fontsize=12)

# Use logarithmic scale because N-Queens grows exponentially
plt.yscale('log')
plt.grid(True, which="both", ls="-", alpha=0.5)
plt.legend()

# Save the plot
output_image = 'benchmarks/performance_chart.png'
plt.savefig(output_image)
print(f"Chart saved successfully as {output_image}")

# Show the plot
plt.show()