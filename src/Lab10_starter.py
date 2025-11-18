# Name:
# KUID:
# Lab session:
# Lab #10
# Description:
#
# Collaborators:
# Outside sources:

#This function is similar to Lab 9, but now get_matrix will always
# output a matrix full of strings. It will also make sure that you
# input a '*' or a '-' when for point (x,y) x == y. For example, (1,1)
# must be a '*' or a '-' for the line to be accepted.
def get_square_matrix():
    """ 
    Takes a square matrix of strings from the user. Each row can be 
    separated by commas and/or spaces. Automatically ends after the last row.

    Ensures that all diagonal entries (where x == y) are either '*' or '-'.
    """
    print("Enter your matrix:")
    matrix = []

    # Get the first row
    x = input()
    if not x.strip():
        return get_square_matrix()

    items = x.replace(",", " ").split()
    length = len(items)

    # Check first row's diagonal entry (0,0)
    if items[0] not in ['*', '-']:
        print("Error: diagonal entry (a,a) must be '*' or '-'. Try again:")
        return get_square_matrix()

    matrix.append(items)

    # Get the rest of the rows
    while True:
        x = input()
        items = x.replace(",", " ").split()
        if len(items) != length:
            print("Error: row lengths are mismatched! Try again:")
            continue  # re-try the line

        row_index = len(matrix)

        # Check diagonal position for this row
        if items[row_index] not in ['*', '-']:
            print(f"Error: diagonal entry at ({row_index+1},{row_index+1}) must be '*' or '-'. Try again:")
            continue  # re-try the line

        matrix.append(items)

        # Check if matrix has been completed (is square)
        if len(matrix) == length:
            return matrix

def get_vertices(n):
    """
    Prompts the user to enter two distinct letters (e.g., 'a b', 'A,B', 'a, b').
    The input can include spaces, commas, or both, and is case-insensitive.
    Returns the two letters in lowercase as a tuple (letter1, letter2).
    """
    valid_labels = [chr(ord('a') + i) for i in range(n)]
    while True:
        user_input = input("Enter two distinct letters: ").strip()

        # Remove commas and split by spaces
        parts = user_input.replace(",", " ").split()
        letters = [p.lower() for p in parts if p]

        # Validate that exactly two letters were entered
        if len(letters) != 2:
            print("Error: Please enter exactly two letters (e.g., a b or a,b).")
            continue

        # Validate that both are single alphabetic characters
        if not all(l.isalpha() and len(l) == 1 for l in letters):
            print("Error: Both inputs must be single alphabetic letters.")
            continue

        # Ensure they are distinct
        if letters[0] == letters[1]:
            print("Error: Letters must be distinct.")
            continue

        # Ensure both letters are valid for the given matrix
        if not all(l in valid_labels for l in letters):
            print(f"Error: Letters must be within the range {valid_labels}.")
            continue

        return letters[0], letters[1]


# Helper function to print a 2-D matrix
def print_matrix(m):
    n = len(m)
    # Create labels (a, b, c, ...)
    labels = [chr(ord('a') + i) for i in range(n)]
    
    # Print top header row
    print("  ", end="")  # space for corner
    for label in labels:
        print(label, end=" ")
    print()
    
    # Print each row with its corresponding label
    for i, row in enumerate(m):
        print(labels[i], end=" ")  # row label
        for item in row:
            print(item, end=" ")
        print()


def main():
    M_R = get_square_matrix()
    print("Got: ")
    print_matrix(M_R)
    v_1, v_2 = get_vertices(len(M_R))
    print(f"Got: {v_1} -> {v_2}")


if __name__ == "__main__":
    main()
