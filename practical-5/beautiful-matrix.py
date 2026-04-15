matrix = []
for _ in range(5):
    row = list(map(int, input().split()))
    matrix.append(row)

# Find position of '1'
for i in range(5):
    for j in range(5):
        if matrix[i][j] == 1:
            r, c = i, j

moves = abs(r - 2) + abs(c - 2)
print(moves)