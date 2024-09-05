import random
import time


def generate_random_list(size, lrange):
    return [random.randint(0, lrange) for _ in range(size)]

def generate_middle_sorted_list(size, sorted_percentage):
    n_sorted = int(size * sorted_percentage)
    lista = sorted([random.randint(0, 10**4) for _ in range(n_sorted)])
    lista.extend([random.randint(0, 10**4) for _ in range(size - n_sorted)])
    random.shuffle(lista)
    return lista


lista = generate_random_list(10**4, 10**4)


inicio = time.time()
with open('/home/gxuseppe/Tareasolol/ALGOCO/Datasets/Middle_sorted_sorted.txt', 'w') as archivo:
    for i in range(100):
        tamano= random.randint(1, 10**5)
        porcentaje= random.randint(1, 80)
        lista = generate_middle_sorted_list(tamano, porcentaje/100)
        archivo.write(str(tamano) + '\n')
        for elemento in lista:
            archivo.write(str(elemento)+ ' ')
        archivo.write('\n')
final= time.time()

print("listo")
print(final-inicio)