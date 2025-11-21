import subprocess
import re
import time
import sys

def run_dynamic_test():
    # Start the C program as a subprocess with pipes for input/output
    # bufsize=0 ensures we send/receive data immediately (unbuffered)
    cmd = "./main"  # Use "main.exe" if on Windows
    
    print(f"--- Launching {cmd} ---")
    try:
        process = subprocess.Popen(
            cmd,
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            bufsize=0 
        )
    except FileNotFoundError:
        print("Error: Could not find the executable. Make sure you compiled 'main.c' to 'main' (or 'main.exe').")
        return

    # Helper function to send data to the C program
    def send_input(text):
        print(f"[INPUT]  {text}")
        process.stdin.write(text + "\n")
        process.stdin.flush()
        time.sleep(0.1) # Small delay to ensure C program processes it

    # Helper function to read output until we find a specific pattern or run out of lines
    def read_until_matricula():
        captured_matricula = None
        print("[OUTPUT] (Listening for Matricula...)")
        
        # We read line by line. Note: This can hang if the C program stops outputting lines 
        # without asking for input, but for this flow it works.
        while True:
            line = process.stdout.readline()
            if not line: break
            
            # Print specific lines to console so we see what's happening
            # (Optional: filter this if too noisy)
            if "|" in line: 
                print(f"    C_STDOUT: {line.strip()}")

            # REGEX: Look for pattern like "V123" inside the table row
            # Your table format: ID | Vendedor | Matricula | ...
            # Example: 123 | Nome | V456 | ...
            match = re.search(r'\|\s*(V\d{3})\s*\|', line)
            if match:
                captured_matricula = match.group(1)
                print(f"\n[FOUND] Detected Matricula: {captured_matricula}\n")
                break
        
        return captured_matricula

    # --- STEP 1: CREATE FIRST SALE (New Seller) ---
    print("\n--- Step 1: Creating First Sale (New Seller) ---")
    send_input("1")              # Option 1: Insert
    send_input("Cliente One")    # Client Name
    send_input("n")              # Ja tem matricula? N (Generates new)
    send_input("Vendedor Orig")  # Seller Name
    send_input("01/01/2025")     # Date
    send_input("100.50")         # Value

    # --- STEP 2: LIST SALES TO CAPTURE MATRICULA ---
    print("\n--- Step 2: Listing to Find Generated Matricula ---")
    send_input("2")              # Option 2: List
    send_input("1")              # 1 = Crescente (or 0, doesn't matter)
    
    # Read the output until we find a matricula
    matricula = read_until_matricula()
    
    if not matricula:
        print("Error: Could not capture a valid matricula from the output.")
        process.kill()
        return

    # --- STEP 3: CREATE SECOND SALE (Repeated Seller) ---
    print(f"\n--- Step 3: Creating Second Sale using {matricula} ---")
    send_input("1")              # Option 1: Insert
    send_input("Cliente Two")    # Client Name
    send_input("S")              # Ja tem matricula? S (YES!)
    send_input(matricula)        # <--- We inject the DYNAMICALLY captured ID here
    send_input("02/01/2025")     # Date
    send_input("250.00")         # Value

    # --- STEP 4: LIST AGAIN TO VERIFY ---
    print("\n--- Step 4: Final List to Verify ---")
    send_input("2")

    # Let the output flush a bit
    time.sleep(1)
    
    # Kill process gracefully
    process.stdin.close()
    process.terminate()
    print("\n--- Test Finished ---")

if __name__ == "__main__":
    run_dynamic_test()