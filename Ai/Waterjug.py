def dfs_water_jug(a, b, goal_state):
    stack = [((0, 0), [])]
    visited = set()
    solutions = []

    while stack:
        (jug1, jug2), path = stack.pop()

        if (jug1, jug2) in visited:
            continue

        visited.add((jug1, jug2))

        if (jug1, jug2) == goal_state:
            solutions.append(path + [(jug1, jug2)])

        actions = [
            (a, jug2),
            (jug1, b),
            (0, jug2),
            (jug1, 0),
            (jug1 - min(jug1, b - jug2), jug2 + min(jug1, b - jug2)),
            (jug1 + min(jug2, a - jug1), jug2 - min(jug2, a - jug1))
        ]

        for state in actions:
            if state not in visited:
                stack.append((state, path + [(jug1, jug2)]))

    return solutions

a = int(input("Enter capacity of Jug 1: "))
b = int(input("Enter capacity of Jug 2: "))
goal_x = int(input("Enter goal state for Jug 1: "))
goal_y = int(input("Enter goal state for Jug 2: "))

goal_state = (goal_x, goal_y)
solutions = dfs_water_jug(a, b, goal_state)

if solutions:
    for i, solution in enumerate(solutions, 1):
        print(f"Solution {i}: {solution}")
else:
    print("No solution found.")
