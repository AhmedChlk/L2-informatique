from math import gcd
from collections import Counter
M = 26
def af(m): print(Counter(m.replace(" ","")))
def cinv(a,mod): return next((i for i in range(1,mod) if a*i % mod == 1),-1)



def normalisation(a,mod) : return (a + mod*mod) % mod

def char_to_num(c): return ord(c) - ord('a')
def resolution_systeme(cl1, ch1, cl2, ch2) -> tuple:
    dch = normalisation(ch1 - ch2, M)
    dcl = normalisation(cl1 - cl2, M)
    pgcd = gcd(dcl, M)
    if pgcd == 1:
        inv_d = cinv(dcl,M)
        a = normalisation(dch * inv_d, M)
        b = normalisation(ch1 - a * cl1, M)
        return (a, b)
    else:
        if dch % pgcd == 0:
            dcl //= pgcd
            dch //= pgcd
            mod = M // pgcd
            inv_d = cinv(dcl,mod)
            s = normalisation(dch * inv_d, mod)
            i = 0
            while (s + mod * i) < M:
                if gcd((s + mod * i), M) == 1:
                    a = s + mod * i
                    b = normalisation(ch1 - a * cl1, M)
                    return (a, b)
                i += 1
            print("Solution impossible")
            return None
        else:
            print("Solution impossible")
            return None
def chiffrement_affine(m,a,b):
    return "".join(chr(((ord(c) - 97)* a) + b % M + 97) for c in m)

def dechiffrement_affine (m,a,b):
    inv_a = cinv(a,M)  # Calcul de l'inverse de 'a' modulo 26
    return "".join(chr((inv_a * (ord(c) - 97 - b)) % M + 97) for c in m)


def vigenere(message, key):
    message_crypte = []
    key_length = len(key)
    i = 0
    for m in message:
        nouveau_car = chr(((ord(m) - 65 + ord(key[i])- 65) % 26) + 65)
        message_crypte.append(nouveau_car)
        i = (i + 1) % key_length
    print("".join(message_crypte))

def dech_vigenere(message, key):
    message_crypte = []
    key_length = len(key)
    i = 0
    for m in message:
        nouveau_car = chr(((ord(m) - 65 - ord(key[i])- 65) % 26) + 65)
        message_crypte.append(nouveau_car)
        i = (i + 1) % key_length
    print("".join(message_crypte))


def trouver_clef(cipher, plain):
    clef = ""
    for c, p in zip(cipher, plain):
        decalage = (ord(c) - ord(p)) % 26
        lettre_clef = chr(decalage + ord('A'))
        clef += lettre_clef
    return clef

def indice_co(m):
    somme = 0.0
    frequence = Counter(m)
    for v in frequence :
        somme += (frequence[v]*(frequence[v]-1)/(len(m)*(len(m) -1)))
    print(somme)
#vigenere("CETEXAMENESTFACILE","KEY")

indice_co("AHOXUREZZOSHIPSDHHDSHFLCPQAFPAMMDUF")
indice_co("BTEDHGHAOSRLNRQMLVXCAKWVGSGATSRICOI")
indice_co("CWOQKPUEGEJKHHTGOGPVGUVWPRGWRNWUUWT")
m = "EOJRVWVWXSKDGHULOWJHXDRUMFRQVVVVVCDPXIEETASRNZRJKOEGXOWITWIHWIEKHADHXGKGXAFQMSIGTBJOTQCDLGVVNDVUBSLUXOCDLWVQGSVWMCLWESWIHFKGXQVWMSTOTGJHXGKGXZVPISTKXFUHFCEWXF"
print(m[0:len(m):4])
print(m[1:len(m):4])
print(m[2:len(m):4])
print(m[3:len(m):4])




af("EVXGOXMVVXTNKXTWHXXMTTLNBXLGMEHXMTXXIXFX")
af("OWSHWDFVCIAZOOWIAGASBQGDSOWSCSFQSGGZSFCF")
af("JVKUJRRVDESREWIEDKFIJCVVLCVVLWKVTJKVTUE")
af("RWDLHUQVPERJGIHKHGQGODVUUDQWWIGWOHGPKHW")






print(chr((ord('X')-65 -ord('E')- 65)%26 + 65))
print(chr((ord('S')-65 -ord('E')- 65)%26 + 65))
print(chr((ord('V')-65 -ord('E')- 65)%26 + 65))
print(chr((ord('W')-65 -ord('E')- 65)%26 + 65))



dech_vigenere(m,"TORD")

print(cinv(3,26))