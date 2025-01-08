import numpy as np

aug_matrix = np.array([[2, 3, -1, 5], [1, -2, 3, 6], [4, 1, -2, 0]], dtype=float)

N = len(aug_matrix)

# Forward elimination
for i in range(N):

    # Make the diagonal element 1 (pivot normalization)
    aug_matrix[i] = aug_matrix[i] / aug_matrix[i, i]

    # Eliminate elements below the pivot
    for j in range(i + 1, N):
        aug_matrix[j] = aug_matrix[j] - aug_matrix[j, i] * aug_matrix[i]

# Back substitution
solution = np.zeros(N)
for i in range(N - 1, -1, -1):
    solution[i] = aug_matrix[i, -1] - np.sum(
        aug_matrix[i, i + 1 : N] * solution[i + 1 : N]
    )

a, b, c = solution
print(f"a = {a}, b = {b}, c = {c}")
