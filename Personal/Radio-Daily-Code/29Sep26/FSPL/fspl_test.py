import math
# 1. input for variable 
freq_mhz = float(input("Enter Frequency (MHz): "))
distance_km = float(input("Enter Distance (Km): "))

# 2. FSPL calculator
fspl_db = 20 * math.log10(distance_km) + 20 * math.log10(freq_mhz) + 32.44

# 3. Output
print(f"---RF SIGNAL ANALYSIS---")
print(f"Frequency: {freq_mhz} MHz")
print(f"Distance: {distance_km} km")
print(f"Free Space Path Loss: {fspl_db:.2f} dB")

with open("rf_log.txt", "a") as log_file:
    log_file.write(f"[PYTHON] FREQ: {freq_mhz} MHz | DIST: {distance_km} | FSPL: {fspl_db:.2f} dB\n")

print("[SUCCESS] aved Python log to rf_log.txt")