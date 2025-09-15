# Program sederhana memasak mie instan
def masak_mie(jenis):
    print("1. siapkan air 500ml")
    print("2. panaskan air hingga mendidih")
    print("3. Masukkan mie ke dalam air mendidih")
    
    if jenis == "kuah":
        print("4. Masukkan bumbu ke dalam mangkuk")
        print("5. Tuang mie beserta air ke mangkuk")
        print("6. Aduk rata dan siap disajikan")
    elif jenis == "goreng":
        print("4. Masak mie 3 menit, lalu tiriskan")
        print("5. Campur mie dengan bumbu di piring")
        print("6. Aduk rata dan siap disajikan")
    else:
        print("Jenis mie tidak dikenali (pilih: kuah/goreng)")

# Eksekusi program
masak_mie("goreng")   # bisa ganti "kuah"
