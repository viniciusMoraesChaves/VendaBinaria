import random

def create_input_file(filename="input_vendas.txt"):
    # List to store the sequence of inputs
    inputs = []

    # Helper to add a line to inputs
    def add(val):
        inputs.append(str(val))

    # --- PHASE 1: POPULATE DATA (15 Success Cases) ---
    # We use 'N' for matricula to ensure flow continues without guessing random IDs
    
    names_clients = ["Alice", "Bob", "Charlie", "Diana", "Evan", "Fiona", "George", "Hannah", "Ian", "Julia", "Kevin", "Laura", "Mike", "Nina", "Oscar"]
    names_sellers = ["Rui", "Ana", "Carlos", "Mariana", "Pedro", "Sofia", "Luiz", "Beatriz", "Joao", "Fernanda", "Ricardo", "Paula", "Gabriel", "Elena", "Lucas"]
    
    for i in range(15):
        add("1")                        # Op: Create Venda
        add(names_clients[i])           # Client Name
        add("n")                        # Has Matricula? (n = No, generates new)
        add(names_sellers[i])           # Seller Name
        
        # Generate valid date
        day = random.randint(1, 28)
        month = random.randint(1, 12)
        year = random.randint(2020, 2025)
        add(f"{day:02d}/{month:02d}/{year}")
        
        # Generate valid value
        val = round(random.uniform(10.0, 1000.0), 2)
        add(f"{val}")

    # --- PHASE 2: TEST VALIDATIONS (Edge Cases) ---

    # Case 16: Invalid Option in Menu -> then Correct
    add("99") # Invalid Op
    add("1")  # Back to Insert

    # Case 17: Empty Client Name Validation
    add("\n")           # Empty name (just enter)
    add("Cliente Teste") # Valid name retry
    add("n")            # No matricula
    add("Vendedor Y")   # Seller
    add("10/10/2023")   # Date
    add("100.00")       # Value

    # Case 18: Invalid 'Has Matricula' Option
    add("1")            # Op: Insert
    add("Cliente Valid")
    add("x")            # Invalid char (not S or N)
    add("n")            # Valid 'n'
    add("Vendedor Z")
    add("01/01/2024")
    add("200.00")

    # Case 19: Date Validations (Day, Month, Year)
    add("1")
    add("Cliente Data")
    add("n")
    add("Vendedor Data")
    add("32/01/2023")   # Invalid Day
    add("15/13/2023")   # Invalid Month
    add("10/10/1800")   # Invalid Year (Too old)
    add("05/05/2025")   # Valid Date
    add("300.00")

    # Case 20: Value Validation (Negative and Zero)
    add("1")
    add("Cliente Valor")
    add("n")
    add("Vendedor Valor")
    add("12/12/2023")
    add("-50.00")       # Negative
    add("0.00")         # Zero
    add("50.00")        # Valid

    # --- PHASE 3: TEST OPERATIONS ---

    # List Tree (Option 2)
    add("2") # Call List
    add("1") # 1 = Crescente (Ascending) based on your code
    
    add("2") # Call List again
    add("0") # 0 = Decrescente (Descending)

    # Search by Name (Option 3 -> 0)
    add("3")            # Op: Search
    add("0")            # Search by Name
    add("Carlos")       # Name to search (from the list above)

    # Search by Matricula (Option 3 -> 1)
    # Note: This will likely fail to find anything because we don't know the random IDs (Vxxx)
    # but it tests the flow.
    add("3")            # Op: Search
    add("1")            # Search by Matricula
    add("V999")         # Guessing a matricula

    # Search by Value (Option 4)
    # WARNING: Your C code has a bug at 'scanf("%d", valor)' inside case 4. 
    # It expects float pointer but gets uninitialized value as address. It might crash here.
    add("4")            # Op: Search Value
    add("500")          # Value
    add("0")            # 0 = Acima (Above)

    # Write to file
    with open(filename, "w") as f:
        f.write("\n".join(inputs))
        f.write("\n") # Final newline

    print(f"Successfully created '{filename}' with {len(inputs)} input lines.")
    print("Use it with: ./main < input_vendas.txt")

if __name__ == "__main__":
    create_input_file()