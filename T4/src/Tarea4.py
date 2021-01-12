import threading
from threading import Thread
from threading import Semaphore
from time import sleep
from datetime import datetime

sem_sacar=Semaphore(1)
sem_sirviendo=Semaphore(1)
sem_servir=Semaphore(1)
sem_pedir_ayuda=Semaphore(1)

class Ayuda():
    def __init__(self):
        self.lista_ayuda=1

    def ayuda_disponible(self):
        if self.lista_ayuda>0:
            self.lista_ayuda-=1
            return True
        else:
            return False
    
    def ofrecerse(self):
        self.lista_ayuda+=1

class Juan(Thread):

    def __init__(self):
        super().__init__()

    def run(self):
        while True:
            pass
    
    def servir(self,cliente):
        arc=open('Juan.txt','a')
        now=datetime.now()
        arc.write('Sirviendo almuerzo a '+ cliente + '('+str(now.hour)+':'+str(now.minute)+':'+str(now.second)+')\n')
        arc.close()
        print('Sirviendo almuerzo a '+cliente)

    def rellenar_bandejas(self):
        arc=open('Juan.txt','a')
        now=datetime.now()
        arc.write('Rellenando Bandejas ('+str(now.hour)+':'+str(now.minute)+':'+str(now.second)+')\n')
        arc.close()
        global sem_servir
        sem_servir.acquire()
        sleep(5)
        sem_servir.release()


class Cliente(Thread):

    def __init__(self,nombre,bandejero,fila,juan,ayuda):
        super().__init__()
        global sem_sacar
        global sem_sirviendo
        global sem_pedir_ayuda
        self.nombre=nombre
        self.bandejero=bandejero
        self.fila=fila
        self.juan=juan
        self.sem_sirviendo=sem_sirviendo
        self.sem_sacar=sem_sacar
        self.ayuda=ayuda
        self.sem_pedir_ayuda=sem_pedir_ayuda
    
    def run(self):
        arc=open('Clientes.txt','a')
        sem_pedir_ayuda.acquire()
        now=datetime.now()
        arc.write(self.nombre+' -> Esperando ayuda ('+str(now.hour)+':'+str(now.minute)+':'+str(now.second)+')\n')
        while self.ayuda.ayuda_disponible()==False:
            pass
        sem_pedir_ayuda.release()
        self.sem_sacar.acquire()
        now=datetime.now()
        arc.write(self.nombre+' -> Acompañante recogiendo bandeja ('+str(now.hour)+':'+str(now.minute)+':'+str(now.second)+')\n')
        self.bandeja=self.fila.sacar_bandeja()
        print(self.bandeja)
        self.sem_sacar.release()
        self.sem_sirviendo.acquire()
        now=datetime.now()
        arc.write(self.nombre+' -> Recibiendo comida ('+str(now.hour)+':'+str(now.minute)+':'+str(now.second)+')\n')
        self.juan.servir(self.nombre)
        self.sem_sirviendo.release()
        now=datetime.now()
        arc.write(self.nombre+' -> Comiendo ('+str(now.hour)+':'+str(now.minute)+':'+str(now.second)+')\n')
        self.comer()
        now=datetime.now()
        arc.write(self.nombre+' -> Dejando Bandeja ('+str(now.hour)+':'+str(now.minute)+':'+str(now.second)+')\n')
        self.bandejero.colocar_bandeja(self.bandeja)
        now=datetime.now()
        arc.write(self.nombre+' -> Esperando a quien ayudar ('+str(now.hour)+':'+str(now.minute)+':'+str(now.second)+')\n')
        self.ayuda.ofrecerse()
        arc.close()
    
    #Tiempo que demora el cliente en comer
    def comer(self):
        sleep(5)



class Bandejero():
    def __init__(self,capacidad):
        self.listabandejas=[]
        self.capacidad=capacidad

    def colocar_bandeja(self,bandeja):
        if len(self.listabandejas)<self.capacidad:
            self.listabandejas.append(bandeja)
        else:
            pass
            

class FilaAlmuerzo():
    def __init__(self,cantidad_bandejas,cantidad_clientes,juan,bandejero):
        self.listabandejas=[]
        self.listaclientes=[]
        self.juan=juan
        self.bandejero=bandejero
        for x in range(1,cantidad_bandejas+1):
            self.listabandejas.append('Bandeja Nº'+str(x))
        for x in range(1,cantidad_clientes+1):
            self.listaclientes.append('Cliente Nº'+str(x))
    
    #Retorna una bandeja y la saca de la fila
    def sacar_bandeja(self):
        bandeja=self.listabandejas.pop()
        if len(self.listabandejas)>0:
            return bandeja
        elif len(self.listabandejas)==0:
            self.juan.rellenar_bandejas()
            self.bandejerotofila()
            sleep(3)
            return bandeja

    #Envia las bandejas desde el bandejero a la fila
    def bandejerotofila(self):
        self.listabandejas+=self.bandejero.listabandejas

        

def main():
    arc_juan=open('Juan.txt','w')
    arc_juan.close()
    arc_clientes=open('Clientes.txt','w')
    arc_clientes.close()
    juan=Juan()
    ayuda=Ayuda()
    nbandejas=int(input('Cantidad de bandejas: '))
    nclientes=int(input('Cantidad de clientes: '))
    bandejero=Bandejero(nbandejas/2)
    fila=FilaAlmuerzo(nbandejas,nclientes,juan,bandejero)
    for x in fila.listaclientes:
        c=Cliente(x,bandejero,fila,juan,ayuda)
        c.start()




if __name__ == "__main__":
    
    main()
