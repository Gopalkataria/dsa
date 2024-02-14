import random

def is_valid_level_order(num_nodes, values):
    # Check if the number of nodes matches the length of the values list
    if num_nodes != len(values):
        return False

    # Check if the input follows the level order traversal rules
    for i in range(num_nodes):
        if values[i] != 0 and values[i] != 1:
            return False
        if i * 2 + 1 < num_nodes and values[i] == 0 and values[i * 2 + 1] != 0:
            return False
        if i * 2 + 2 < num_nodes and values[i] == 0 and values[i * 2 + 2] != 0:
            return False

    return True

def generate_and_output_valid_input():
    while True:
        num_nodes = random.randint(5, 30)  # Adjust the range based on your requirements
        input_values = [random.choices([0, 1], weights=[0.4, 0.6])[0] for _ in range(num_nodes)]

        if is_valid_level_order(num_nodes, input_values):
            print(num_nodes, end = " ")
            print(*input_values)
            return 1 
        else:
            pass

# Generate and output a valid level order input
for x in range(20) :
    generate_and_output_valid_input()
