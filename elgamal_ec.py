import random


class EllipticCurve:
    def __init__(self, p, a, b, x, y):
        self.p = p
        self.a = a
        self.b = b
        self.x = x
        self.y = y

    def is_point_on_curve(self, x, y):
        return (y ** 2) % self.p == (x ** 3 + self.a * x + self.b) % self.p

    def point_addition(self, x1, y1, x2, y2):
        if x1 is None and y1 is None:
            return x2, y2
        if x2 is None and y2 is None:
            return x1, y1

        if x1 == x2 and (y1 != y2 or y1 == 0):
            return None, None

        if x1 == x2:
            m = (3 * x1 * x1 + self.a) * self.modular_inverse(2 * y1, self.p)
        else:
            m = (y1 - y2) * self.modular_inverse(x1 - x2, self.p)

        x3 = (m ** 2 - x1 - x2) % self.p
        y3 = (m * (x1 - x3) - y1) % self.p

        return x3, y3

    def point_scalar_multiplication(self, x, y, scalar):
        scalar %= self.p
        result_x = None
        result_y = None

        while scalar:
            if scalar & 1:
                result_x, result_y = self.point_addition(result_x, result_y, x, y)
            x, y = self.point_addition(x, y, x, y)
            scalar >>= 1

        return result_x, result_y

    def modular_inverse(self, a, m):
        if a < 0:
            a = a % m
        original_m = m
        x, y, u, v = 0, 1, 1, 0
        while a:
            q = m // a
            m, a = a, m % a
            x, u = u, x - q * u
            y, v = v, y - q * v
        if x < 0:
            x += original_m
        return x


def elgamal_encrypt(message, recipient_public_key):
    p = recipient_public_key[0]
    a = recipient_public_key[1]
    b = recipient_public_key[2]
    base_point = (recipient_public_key[3], recipient_public_key[4])
    public_key = base_point
    private_key = random.randint(1, p - 1)

    # Compute the shared secret point
    shared_secret_point = curve.point_scalar_multiplication(public_key[0], public_key[1], private_key)

    # Derive the shared secret x-coordinate
    shared_secret_x = shared_secret_point[0]

    # Convert the shared secret x-coordinate to an integer
    shared_secret_int = shared_secret_x

    # Encrypt the message
    byte_message = message.encode('utf-8')
    encrypted_bytes = bytes((byte + shared_secret_int) % 256 for byte in byte_message)
    encrypted_message = encrypted_bytes.decode('utf-8')

    return encrypted_message, private_key


def elgamal_decrypt(ciphertext, private_key):
    # Compute the shared secret point
    shared_secret_point = curve.point_scalar_multiplication(curve.x, curve.y, private_key)

    # Derive the shared secret x-coordinate
    shared_secret_x = shared_secret_point[0]

    # Convert the shared secret x-coordinate to an integer
    shared_secret_int = shared_secret_x

    # Decrypt the message
    byte_ciphertext = ciphertext.encode('utf-8')
    decrypted_bytes = bytes((byte - shared_secret_int) % 256 for byte in byte_ciphertext)
    decrypted_message = decrypted_bytes.decode('utf-8')

    return decrypted_message


# Define the elliptic curve parameters
p = 2455155546008943817740293915197451784769108058161191238065
a = -3
b = 2455155546008943817740293915197451784769108058161191238065
x = 602046282375688656758213480587526111916698976636884684818
y = 174050332293622031404857552280219410364023488927386650641

curve = EllipticCurve(p, a, b, x, y)

# Generate the recipient's private key
recipient_private_key = random.randint(1, p - 1)

# Compute the recipient's public key
recipient_public_key = (
    p,
    a,
    b,
    x,
    y,
    curve.point_scalar_multiplication(x, y, recipient_private_key),
)

# Encrypt the message
message = "Puppy"
encrypted_message, private_key = elgamal_encrypt(message, recipient_public_key)

# Decrypt the ciphertext
decrypted_message = elgamal_decrypt(encrypted_message, private_key)

print("Original Message:", message)
print("Encrypted Message:", encrypted_message)
print("Decrypted Message:", decrypted_message)
