import matplotlib.pyplot as plt
import numpy as np


# Define the piecewise function
def vc(t):
    """
    Piecewise function defining v_c(t) for different time intervals.
    """
    if t <= 0:
        return 0
    if 0 < t <= 5:
        return (3 / 8) * t**2
    if 5 < t <= 10:
        return (75 / 8) - (10 / 4) * (t - 5)
    if 10 < t <= 12:
        return -25 / 8
    return 0


# Generate time values for each segment with reduced resolution
t1 = np.linspace(0, 5, 50)
t2 = np.linspace(5, 10, 50)
t3 = np.linspace(10, 12, 20)

# Compute v_c(t) for each segment
v1 = [(3 / 8) * t**2 for t in t1]
v2 = [(75 / 8) - (10 / 4) * (t - 5) for t in t2]
v3 = [-25 / 8 for _ in t3]

# Identify key points
key_points_t = [0, 5, 10, 12]
key_points_v = [vc(t) for t in key_points_t]

# Plot the function with '*' as markers for each segment
plt.figure(figsize=(10, 6))
plt.plot(t1, v1, "*", color="blue", markersize=6, label="0 ≤ t ≤ 5")
plt.plot(t2, v2, "*", color="orange", markersize=6, label="5 ≤ t ≤ 10")
plt.plot(t3, v3, "*", color="green", markersize=6, label="10 ≤ t ≤ 12")

# Highlight key points with larger '*' markers
plt.plot(
    key_points_t,
    key_points_v,
    "*",
    color="red",
    markersize=10,
    label="Key Points (Peaks/Changes)",
    zorder=5,
)

# Add labels, legend, and grid
plt.title("Plot of $v_c(t)$ with Key Points Highlighted", fontsize=14)
plt.xlabel("Time (t)", fontsize=12)
plt.ylabel("$v_c(t)$", fontsize=12)
plt.grid(alpha=0.3)
plt.legend(fontsize=10)
plt.show()
