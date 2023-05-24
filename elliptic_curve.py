import random
from sympy import isprime, mod_inverse

# Elliptic Curve Point
class ECPoint:
    def __init__(self, x, y, curve):
        self.x = x
        self.y = y
        self.curve = curve

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __add__(self, other):
        if self == ECPoint.infinity:
            return other
        elif other == ECPoint.infinity:
            return self
        elif self.x == other.x and self.y == -other.y:
            return ECPoint.infinity
        else:
            p = self.curve.p
            if self.x == other.x and self.y == other.y:
                l = (3 * self.x**2 + self.curve.a) * mod_inverse(2 * self.y, p) % p
            else:
                l = (self.y - other.y) * mod_inverse(self.x - other.x, p) % p
            x3 = (l**2 - self.x - other.x) % p
            y3 = (l * (self.x - x3) - self.y) % p
            return ECPoint(x3, y3, self.curve)

    def __mul__(self, scalar):
        result = ECPoint.infinity
        current = self
        while scalar > 0:
            if scalar & 1:
                result += current
            current += current
            scalar >>= 1
        return result

    def __sub__(self, other):
        other_inverse = ECPoint(other.x, -other.y, other.curve)
        return self + other_inverse

    def __str__(self):
        return f"({self.x}, {self.y})"

ECPoint.infinity = ECPoint(None, None, None)  # Add infinity attribute to ECPoint class

# Elliptic Curve
class ECCurve:
    def __init__(self, a, b, p, base_point):
        self.a = a
        self.b = b
        self.p = p
        self.base_point = base_point
        self.base_point.curve = self  # Set the curve attribute for the base point

    def is_on_curve(self, point):
        if point == ECPoint.infinity:
            return True
        x, y = point.x, point.y
        return (y**2) % self.p == (x**3 + self.a * x + self.b) % self.p

    def generate_random_point(self):
        while True:
            x = random.randint(0, self.p)
            y_squared = (x**3 + self.a * x + self.b) % self.p
            y = pow(y_squared, (self.p + 1) // 4, self.p)
            if (y**2) % self.p == y_squared:
                return ECPoint(x, y, self)

    def __str__(self):
        return f"y^2 = x^3 + {self.a}x + {self.b} mod {self.p}"

# ElGamal key generation
def elgamal_key_generation(curve):
    private_key = random.randint(1, curve.p - 1)
    public_key = curve.base_point * private_key
    return private_key, public_key

# ElGamal encryption
def elgamal_encryption(plain_text, curve, public_key):
    k = random.randint(1, curve.p - 1)
    c1 = curve.base_point * k
    c2 = curve.base_point * plain_text + public_key * k
    return c1, c2

# ElGamal decryption
def elgamal_decryption(c1, c2, curve, private_key):
    shared_secret = c1 * private_key
    decrypted_text = c2 - shared_secret
    return decrypted_text

# Example usage
plain_text = 42

# Elliptic Curve parameters
a = 2
b = 2
p = 751  # A prime number
base_point = ECPoint(0, 1, None)
curve = ECCurve(a, b, p, base_point)

# Key generation
private_key, public_key = elgamal_key_generation(curve)

# Encryption
c1, c2 = elgamal_encryption(plain_text, curve, public_key)

# Decryption
decrypted_text = elgamal_decryption(c1, c2, curve, private_key)

print(f"Plaintext: {plain_text}")
print(f"Ciphertext (c1): {c1}")
print(f"Ciphertext (c2): {c2}")
print(f"Decrypted text: {decrypted_text}")
